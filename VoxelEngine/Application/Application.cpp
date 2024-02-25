#include "Application.hpp"
#include "../Core/Voxel/Voxel.hpp"
#include <vector>
#include <random>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Core/Rendering/ShaderProgram.hpp"

#include "../Core/CA/CellGrid.hpp"
#include "../Core/CA/Sand.hpp"
#include "../Core/CA/Stone.hpp"

struct VoxelGrid
{
	glm::ivec3 gridDimensions;
	std::vector<Voxel> voxels;
};

struct SSBO_data
{
	glm::ivec2 gridDimensions;
	glm::vec4* grid;
};

CellGrid* createCellGrid1(int dimensions)
{
	CellGrid* grid = new CellGrid(dimensions);

	for (int i = 0; i < dimensions; i++)
	{
		grid->insertCell(i, dimensions / 2, new Stone(0.5f));
	}

	for (int x = 0; x < dimensions; x++)
	{
		for (int y = dimensions / 2; y < dimensions / 2 + 5; y++)
		{
			grid->insertCell(x, y, new Stone((float)(rand() % 50) / 100));
		}
	}
	return grid;
}

VoxelGrid createRandomVoxelGrid(int x, int y, int z)
{
	VoxelGrid grid;
	grid.gridDimensions = { x, y, z };

	int size = x * y * z;
	grid.voxels.resize(size);

	for (int i = 0; i < size; i++)
	{
		if (rand() % 2)
			grid.voxels[i].rgba = { 1 ,1, 1, 1 };
		else
			grid.voxels[i].rgba = { 1 ,0, 0, 1 };
	}

	return grid;
}

glm::vec4* createRandomVoxelGrid2(int x, int y, int z)
{
	int size = x * y * z;
	glm::vec4* grid = new glm::vec4[size];

	for (int i = 0; i < size; i++)
	{
		if (rand() % 2)
			grid[i] = { 1 ,1, 1, 1 };
		else
			grid[i] = { 0 ,1, 0, 1 };
	}

	return grid;
}

glm::vec4* createRandomColorGrid(int gridSize)
{
	glm::vec4* grid = new glm::vec4[gridSize];
	for (int i = 0; i < gridSize; i++)
	{
		grid[i].r = (float)(rand() % 255) / 255;
		grid[i].g = (float)(rand() % 255) / 255;
		grid[i].b = (float)(rand() % 255) / 255;
		grid[i].a = 1.0f;
	}
	return grid;
}

Application::Application(int wnd_width, int wnd_height)
{
	this->wndSize = { wnd_width, wnd_height };
	this->viewPortSize = { wnd_width, wnd_height };

	srand(time(0));

	glfwInit();
	window = glfwCreateWindow(wnd_width, wnd_height, "VoxelEngine", NULL, NULL);
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, wnd_width, wnd_height);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Application::run()
{
	int dimX = 125;
	int dimY = 125;
	SSBO_data data;
	data.gridDimensions = { dimX, dimY };
	data.grid = createRandomColorGrid(dimX * dimY);

	std::vector<float> vertices =
	{
		1, 1,
		-1, 1,
		-1, -1,
		1, -1
	};

	std::vector<int> indices =
	{
		0, 1, 2,
		0, 3, 2
	};

	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VAO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), &indices[0], GL_DYNAMIC_DRAW);

	GLuint ssbo;
	glGenBuffers(1, &ssbo);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4) + sizeof(glm::vec4) * data.gridDimensions.x * data.gridDimensions.y, nullptr, GL_DYNAMIC_DRAW);

	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(glm::vec4), &data.gridDimensions);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4) * data.gridDimensions.x * data.gridDimensions.y, data.grid);

	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

	glBindVertexArray(0);

	ShaderProgram shad1("Core/Rendering/Shaders/first.vert", "Core/Rendering/Shaders/first.frag");

	int cellSize = 8;
	while (!glfwWindowShouldClose(window))
	{
		//Rendering
		glClear(GL_COLOR_BUFFER_BIT);

		shad1.bind();

		GLint viewPortSizeLoc = glGetUniformLocation(shad1.getId(), "viewPortSize");
		glUniform2i(viewPortSizeLoc, 0, 0);

		GLint cellSizeLoc = glGetUniformLocation(shad1.getId(), "cellSize");
		glUniform1i(cellSizeLoc, cellSize);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		//UI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Test");
		ImGui::InputInt("CellSize", &cellSize);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}

void Application::runUI()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Test");
	ImGui::Button("btn1");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void Application::render()
{
}

void Application::updateLogic()
{
}
