#pragma once
#include <cstdio>

class Logger
{
public:
	enum LogLevel : unsigned int
	{
		TRACE,
		DEBUG,
		INFO,
		WARN,
		ERROR,
		FATAL
	};

	template <typename... Args>
	static void Log(LogLevel logLevel, Args ... args)
	{
		if (logLevel <= m_LogLevel) 
		{
			std::printf(args ...);
			// force output, i.e. for Eclipse
			std::fflush(stdout);
		}
	}

	static void SetLogLevel(LogLevel logLevel)
	{
		// Max log level is 6
		logLevel <= LogLevel::FATAL ? m_LogLevel = logLevel : m_LogLevel = LogLevel::FATAL;	
	}
private:
	static unsigned int m_LogLevel;
};