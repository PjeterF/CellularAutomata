#include "Application.hpp"
#include "../Core/Voxel/Voxel.hpp"
#include <vector>
#include <chrono>
#include <thread>
#include <random>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Core/Rendering/ShaderProgram.hpp"

#include "../Core/CA/CellGrid.hpp"
#include "../Core/CA/Elements/Sand.hpp"
#include "../Core/CA/Elements/Stone.hpp"
#include "../Core/CA/Elements/Water.hpp"
#include "../Core/CA/Elements/Acid.hpp"

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

	float scale = 0.3f;
	int width = 10;
	for (int x = 0; x < dimensions; x++)
	{
		for (int y = scale * dimensions; y < scale * dimensions + width; y++)
		{
			if(x % 20 > 10)
				grid->insertCell(x, y, new Stone((float)(rand() % 50) / 100));
		}
	}

	for (int x = 0; x < dimensions; x++)
	{
		for (int y = 0; y < 5 + width; y++)
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

	GLFWInputManager::initialize(window);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}

void Application::run()
{
	int dimensions = 125;
	CellGrid* cellGrid = createCellGrid1(dimensions);

	SSBO_data data;
	data.gridDimensions = { dimensions, dimensions };
	data.grid = cellGrid->getColorGrid();

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
	int iteration = 0;
	bool paused = true;
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
		static bool allowStep = false;
		if (ImGui::Button("Step"))
		{
			allowStep = true;
		}
		if (ImGui::Button("Sand"))
		{
			cellGrid->insertCell(dimensions / 2, dimensions - 1, new Sand({ 1, 0.9, 0.3, 1 }));
		}
		if (ImGui::Button("Water"))
		{
			cellGrid->insertCell(dimensions / 2, dimensions - 1, new Water({ 0.25, 0.4, 0.9, 1 }));
		}
		ImGui::Checkbox("Paused", &paused);
		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		//Logic
		if (allowStep || !paused)
		{
			allowStep = false;
			bool darken = rand() % 10;
			float scale;
			if (!darken)
				scale = 0.8f;
			else
				scale = 1.0f;
			if (rand() % 100 < 50)
			{
				cellGrid->insertCell(dimensions / 2 + rand() % dimensions/2 - dimensions/4, dimensions - 1, new Water(glm::vec4(0.1, 0.4, 0.9, 1)));
			}
			else
			{
				cellGrid->insertCell(dimensions / 2 + rand() % dimensions / 2 - dimensions / 4, dimensions - 1, new Sand(scale * glm::vec4( 1, 0.9, 0.3, 1 )));
			}

			cellGrid->updateAll();
		}


		data.grid = cellGrid->getColorGrid();
		glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(glm::vec4), sizeof(glm::vec4) * data.gridDimensions.x * data.gridDimensions.y, data.grid);

		if (GLFWInputManager::getInstance().mouseKeyDown[ZE_MOUSE_BUTTON_1])
		{
			glm::vec2 cursorPos = GLFWInputManager::getInstance().getCursorPos();
			cursorPos =  (1.0f/cellSize) * cursorPos;
			if (cellGrid->getCell(cursorPos.x, cursorPos.y) != nullptr)
				cellGrid->insertCell(cursorPos.x, cursorPos.y, new Acid(glm::vec4(0, 0.9, 0.3, 1)));
				//cellGrid->insertCell(cursorPos.x, cursorPos.y, new Sand(glm::vec4(1, 0.9, 0.3, 1)));
		}

		glfwSwapBuffers(window);
		GLFWInputManager::getInstance().update();

		std::this_thread::sleep_for(std::chrono::milliseconds(5));

		iteration++;
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
