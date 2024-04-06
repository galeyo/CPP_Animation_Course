#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public:
	bool Init(unsigned int width, unsigned int height, std::string title);
	void MainLoop();
	void Cleanup();
private:
	void handleWindowCloseEvent();
	void handleKeyEvents(int key, int scancode, int action, int mods);
	void handleMouseButtonEvents(int button, int action, int mods);
private:
	GLFWwindow * m_Window = nullptr;
};