#pragma once

#include "BaseLogger.h"

class StdOutLogger : public BaseLogger
{
public:
	StdOutLogger(void);
	~StdOutLogger(void);
	void Log(E_LOG_LEVEL, const char* strMsg, const char* file, const unsigned long line, const char* function);
};