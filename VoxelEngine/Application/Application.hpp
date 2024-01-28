#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
public:
	Application(int wnd_width, int wnd_height);
	void run();
private:
	void runUI();
	void render();
	void updateLogic();
	GLFWwindow* window;
};