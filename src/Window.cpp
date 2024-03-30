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

	if (!glfwVulkanSupported())
	{
		Logger::Log(Logger::ERROR, "%s: Vulkan is not supported\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}

	m_ApplicationName = title;
	// set a "hint" for the NEXT window created
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Vulkan needs no context
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!m_Window)
	{
		Logger::Log(Logger::ERROR, "%s: Could not create window\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}

	if (!InitVulkan())
	{
		Logger::Log(Logger::ERROR, "%s: Could not init Vulkan\n", __FUNCTION__);
		glfwTerminate();
		return false;
	}
	// Test OpenGL availability
	// glfwMakeContextCurrent(m_Window);
	Logger::Log(Logger::INFO, "%s: Window successfully initialized\n", __FUNCTION__);

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
	return true;
}

bool Window::InitVulkan()
{
	VkResult result = VK_ERROR_UNKNOWN;
	VkApplicationInfo appInfo{};
	// These three is required
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pNext = nullptr;
	appInfo.apiVersion = VK_MAKE_API_VERSION(0, 1, 1, 0);
	// ---
	appInfo.pApplicationName = m_ApplicationName.c_str();
	appInfo.applicationVersion = VK_MAKE_API_VERSION(0, 0, 0, 1);
	appInfo.pEngineName = "Game Animation Programming";
	appInfo.engineVersion = VK_MAKE_API_VERSION(0, 1, 0, 0);

	uint32_t extensionsCount = 0;
	const char **extensions = glfwGetRequiredInstanceExtensions(&extensionsCount);
	if (extensionsCount == 0)
	{
		Logger::Log(Logger::ERROR, "%s: error: no Vulkan extension found", __FUNCTION__);
		return false;
	}

	Logger::Log(Logger::INFO, "%s: Found %u Vulkan extension(s)\n", __FUNCTION__, extensionsCount);
	for (int i = 0; i < extensionsCount; ++i)
	{
		Logger::Log(Logger::INFO, "%s: %s\n", __FUNCTION__, extensions[i]);
	}

	VkInstanceCreateInfo createInstance{};
	createInstance.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInstance.pNext = nullptr;
	createInstance.pApplicationInfo = &appInfo;
	createInstance.enabledExtensionCount = extensionsCount;
	createInstance.ppEnabledExtensionNames = extensions;
	createInstance.enabledLayerCount = 0;

	result = vkCreateInstance(&createInstance, nullptr, &m_Instance);
	if (result != VK_SUCCESS)
	{
		Logger::Log(Logger::ERROR, "%s: Could not create Vulkan instance (%i)\n", __FUNCTION__, result);
		return false;
	}

	uint32_t physicalDeviceCount = 0;
	std::vector<VkPhysicalDevice> devices;
	vkEnumeratePhysicalDevices(m_Instance, &physicalDeviceCount, devices.data());
	if (physicalDeviceCount == 0)
	{
		Logger::Log(Logger::ERROR, "%s: No Vulkan capable GPU found\n", __FUNCTION__);
		return false;
	}

	Logger::Log(Logger::INFO, "%s: Found %u physical device(s)\n", __FUNCTION__, physicalDeviceCount);

	result = glfwCreateWindowSurface(m_Instance, m_Window, nullptr, &m_Surface);
	if (result != VK_SUCCESS)
	{
		Logger::Log(Logger::ERROR, "%s: Could not create Vulkan surface\n", __FUNCTION__);
		return false;
	}

	return true;
}

void Window::MainLoop()
{
	// Test OpenGL
	// // Same as vertical synchronization
	// glfwSwapInterval(1);
	// float color = 0.0f;
	// while(!glfwWindowShouldClose(m_Window))
	// {
	// 	color <= 1.0f ? color += 0.1f : color = 0.0f;
	// 	glClearColor(color, color, color, 1.0f);
	// 	glClear(GL_COLOR_BUFFER_BIT);
	// 	glfwSwapBuffers(m_Window);
	// 	glfwPollEvents();
	// }
	while (!glfwWindowShouldClose(m_Window))
	{
		glfwPollEvents();
	}
}

void Window::Cleanup()
{
	Logger::Log(Logger::INFO, "%s: Terminating Window\n", __FUNCTION__);
	vkDestroySurfaceKHR(m_Instance, m_Surface, nullptr);
	vkDestroyInstance(m_Instance, nullptr);
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