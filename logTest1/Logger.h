#pragma once
#include "MemStream.h"
#include <string>

class CLogger
{
public:
    enum LogLevel
    {
        LEVEL_DEBUG,
        LEVEL_INFO,
        LEVEL_ERROR,
        NUM_LOG_LEVELS,
    };

public:
    CLogger(const char* pszFileName, int nLine, LogLevel level);
    ~CLogger(void);
    CMemStream& LogStart();

private:
    void LogFinish();
    const char* GetLogLevelName(LogLevel level);

public:
    static LogLevel      m_baseLevel;

private:
    CMemStream           m_stream;
    char                 szFilepath[512];
    int                  m_nLine;
    LogLevel             m_level;
};

#define LOG_DEBUG if (CLogger::LEVEL_DEBUG >= CLogger::m_baseLevel)\
    (CLogger(__FILE__, __LINE__, CLogger::LEVEL_DEBUG).LogStart()

#define LOG_INFO if (CLogger::LEVEL_INFO >= CLogger::m_baseLevel)\
    CLogger(__FILE__, __LINE__, CLogger::LEVEL_INFO).LogStart()

#define LOG_ERROR if (CLogger::LEVEL_ERROR >= CLogger::m_baseLevel)\
    CLogger(__FILE__, __LINE__, CLogger::LEVEL_ERROR).LogStart()