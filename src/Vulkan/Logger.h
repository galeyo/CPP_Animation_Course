#pragma once
#include <cstdio>

class Logger
{
public:
	enum LogLevel : unsigned int
	{
		FATAL,
		ERROR,
		WARN,
		INFO,
		DEBUG,
		TRACE
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
		logLevel <= LogLevel::TRACE ? m_LogLevel = logLevel : m_LogLevel = LogLevel::TRACE;	
	}
private:
	static unsigned int m_LogLevel;
};