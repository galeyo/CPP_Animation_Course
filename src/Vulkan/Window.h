#pragma once
#include <string>
// include Vulkan header BEFORE GLFW
#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	bool Init(unsigned int width, unsigned int height, std::string title);
	bool InitVulkan();
	void MainLoop();
	void Cleanup();
private:
	void handleWindowCloseEvent();
	void handleKeyEvents(int key, int scancode, int action, int mods);
	void handleMouseButtonEvents(int button, int action, int mods);
private:
	GLFWwindow * m_Window = nullptr;
	std::string m_ApplicationName{};
	VkInstance m_Instance{};
	VkSurfaceKHR m_Surface{};
};