#include "Window.h"
#include "Logger.h"

bool Window::Init(unsigned int width, unsigned int height, std::string title)
{
	if (!glfwInit())
	{
		Logger::Log(Logger::ERROR, "%s: glfwInit() error\n", __FUNCTION__);
		return false;
	}
	// set a "hint" for the NEXT window created
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		Logger::Log(Logger::ERROR, "%s: Could not create window\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}

	Logger::Log(Logger::INFO, "%s: Window successfully initialized\n", __FUNCTION__);
	return true;
}

void Window::MainLoop()
{
	while(!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
	}
}


void Window::Cleanup()
{
	Logger::Log(Logger::INFO, "%s: Terminating Window\n", __FUNCTION__);
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}