#include "stdafx.h"
#include "SyslogLogger.h"

SyslogLogger::SyslogLogger(void) :BaseLogger()
{
	m_logType = LOG_TYPE_SYSLOG;
#ifdef WIN32
	fprintf(stderr, "syslog supports linux only.");
	return;
#else
	m_FacilityCode = LOG_USER; //default LOG_USER
	m_LogOpt = LOG_OID;
#endif
}

SyslogLogger::~SyslogLogger(void)
{

}

void SyslogLogger::SetFacilityCode(int facilityCode)
{
	m_FacilityCode = facilityCode;
}
void SyslogLogger::SetLogOpt(int logOpt)
{
	m_LogOpt = logOpt;
}

void SyslogLogger::Log(E_LOG_LEVEL level, const char * strMsg, const char * file, const unsigned long line, const char * function)
{
	char logMsg[MAX_LOG_LENGTH];
	memset(logMsg, 0, sizeof(logMsg));

#ifdef WIN32
	fprintf(stderr, "syslog supports linux only.");
	return;
#else
	snprintf(logMsg, MAX_LOG_LENGTH, "[%s] %s, File: %s, Line: %lu, Function: %s\n",
		//GetSystemTime(),
		BaseLogger::LEVEL_STRING[level], strMsg,
		file, line, function);
	//int logmask;
	openlog(file, m_LogOpt, m_FacilityCode);
	syslog(level, logMsg);
	//syslog(LOG_DEBUG,"debug message, should appear");   /*��¼����־��Ϣ��*/
	//logmask = setlogmask(LOG_UPTO(LOG_NOTICE));     /*�������ε���NOTICE�������־��Ϣ��*/
	//syslog(LOG_DEBUG, "debug message, should not appear");  /*����־��Ϣ�����Σ�����¼��*/
	closelog();
#endif
}

