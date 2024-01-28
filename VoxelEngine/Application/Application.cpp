#include "Application.hpp"
#include "../Core/Voxel/Voxel.hpp"
#include <vector>
#include <random>
#include <glm/vec3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Core/Rendering/ShaderProgram.hpp"

Voxel* createRandomVoxelGrid(int x, int y, int z)
{
	int size = x * y * z;

	Voxel* grid = new Voxel[size];

	for (int i = 0; i < size; i++)
	{
		if (rand() % 2)
			grid[i].rgba = { 1 ,0, 0, 0 };
	}

	return grid;
}

Application::Application(int wnd_width, int wnd_height)
{
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
	std::cout << sizeof(Voxel)<<"\n";
	std::cout << sizeof(float)<<"\n";

	glm::ivec3 gridDim = { 100, 100, 100 };
	int gridSize = gridDim.x * gridDim.y * gridDim.z;
	Voxel* grid = createRandomVoxelGrid(gridDim.x, gridDim.y, gridDim.z);

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
	glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(Voxel) * gridSize, grid, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);

	glBindVertexArray(0);

	ShaderProgram shad1("Core/Rendering/Shaders/first.vert", "Core/Rendering/Shaders/first.frag");

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		shad1.bind();

		GLint camPosLoc = glGetUniformLocation(shad1.getId(), "camPos");
		glUniform3f(camPosLoc, 0.0f, 0.0f, 5.0f);

		GLint gridOriginLoc = glGetUniformLocation(shad1.getId(), "gridOrigin");
		glUniform3f(gridOriginLoc, 0.0f, 0.0f, 0.0f);

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		runUI();
		
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
