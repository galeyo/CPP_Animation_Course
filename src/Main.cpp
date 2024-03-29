#include <memory>
#include "Window.h"
#include "Logger.h"


int main(int argc, char *argv[])
{
	std::unique_ptr<Window> window = std::make_unique<Window>();

	if (!window->Init(640, 480, "Test window"))
	{
		Logger::Log(Logger::ERROR, "%s error: Window init error\n", __FUNCTION__);
		return -1;
	}
	window->MainLoop();
	window->Cleanup();
	return 0;
}