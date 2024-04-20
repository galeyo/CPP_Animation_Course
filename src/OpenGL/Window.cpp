#include <vector>

#include "Window.h"
#include "Logger.h"

bool Window::Init(unsigned int width, unsigned int height, std::string title)
{
	if (!glfwInit())
	{
		Logger::Log(Logger::ERROR, "%s: glfwInit() error\n", __FUNCTION__);
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		Logger::Log(Logger::ERROR, "%s: Could not create window\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}

	// Test OpenGL availability
	glfwMakeContextCurrent(m_Window);
	Logger::Log(Logger::INFO, "%s: Window successfully initialized\n", __FUNCTION__);
	// Logger::Log(Logger::DEBUG, "%s: OpenGL version: %s\n", __FUNCTION__, glGetString(GL_VERSION));
	m_Renderer = std::make_unique<OGLRenderer>();
	if (!m_Renderer->Init(width, height))
	{
		glfwTerminate();
		return false;
	}
	m_Model = std::make_unique<Model>();
	m_Model->Init();

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetWindowCloseCallback(
		m_Window,
		[](GLFWwindow *window)
		{
			auto thisWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
			thisWindow->handleWindowCloseEvent(); 
		});
	glfwSetKeyCallback(
		m_Window,
		[](GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			auto thisWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
			thisWindow->handleKeyEvents(key, scancode, action, mods);
		});
	glfwSetMouseButtonCallback(
		m_Window,
		[](GLFWwindow *window, int button, int action, int mods)
		{
			auto thisWindow = static_cast<Window *>(glfwGetWindowUserPointer(window));
			thisWindow->handleMouseButtonEvents(button, action, mods);
		});

	glfwSetWindowUserPointer(m_Window, m_Renderer.get());
	glfwSetWindowSizeCallback(
		m_Window,
		[](GLFWwindow* win, int width, int height)
		{
			auto renderer = static_cast<OGLRenderer*>(glfwGetWindowUserPointer(win));
			renderer->SetSize(width, height);
		});
	return true;
}

void Window::MainLoop()
{
	// Test OpenGL
	// Same as vertical synchronization
	glfwSwapInterval(1);
	m_Renderer->UploadData(m_Model->GetVertexData());
	while(!glfwWindowShouldClose(m_Window))
	{
		m_Renderer->Draw();
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
}

void Window::Cleanup()
{
	Logger::Log(Logger::INFO, "%s: Terminating Window\n", __FUNCTION__);
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Window::handleWindowCloseEvent()
{
	Logger::Log(Logger::INFO, "%s: Window got close event ...\n", __FUNCTION__);
}

void Window::handleKeyEvents(int key, int scancode, int action, int mods)
{
	std::string actionName;
	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	case GLFW_REPEAT:
		actionName = "repeated";
		break;
	default:
		actionName = "invalid";
		break;
	}
	const char *keyName = glfwGetKeyName(key, 0);
	Logger::Log(Logger::INFO, "%s: key %s (key %i, scancode %i) %s\n", __FUNCTION__, keyName, key, action, actionName.c_str());
}

void Window::handleMouseButtonEvents(int button, int action, int mods)
{
	std::string actionName;
	switch (action)
	{
	case GLFW_PRESS:
		actionName = "pressed";
		break;
	case GLFW_RELEASE:
		actionName = "released";
		break;
	default:
		actionName = "invalid";
		break;
	}
	std::string mouseButtonName;
	switch(button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
			mouseButtonName = "left";
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			mouseButtonName = "middle";
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			mouseButtonName = "right";
			break;
		default:
			mouseButtonName = "other";
			break;
	}
	Logger::Log(Logger::INFO, "%s: %s mouse button (%i) %s\n", __FUNCTION__, mouseButtonName.c_str(), button, actionName.c_str());
}