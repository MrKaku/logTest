#include "StdAfx.h"
#include "Logger.h"
#include "Utils.h"
#include <process.h>
#include "LogFile.h"

using namespace std;

CLogger::LogLevel CLogger::m_baseLevel = CLogger::LEVEL_DEBUG;

CLogFile g_logFile;

CLogger::CLogger( const char* pszFileName, int nLine, LogLevel level )
    : m_nLine(nLine)
    , m_level(level)
{
    strncpy(szFilepath, pszFileName, sizeof(szFilepath)/sizeof(szFilepath[0]));
}

CLogger::~CLogger(void)
{
    LogFinish();
    g_logFile.Append(m_stream.GetBuffer(), m_stream.GetSize());
}

CMemStream& CLogger::LogStart()
{
    char buf[32] = {0};
    m_stream << "[" << Utils::GetFormatTimeStamp(buf, sizeof(buf)) 
             << " pid=" << Utils::GetPid() << " tid=" << Utils::GetTid()<<"]" 
             << " [" << GetLogLevelName(m_level) <<"] ";
    return m_stream;
}

void CLogger::LogFinish()
{
    m_stream << " - " << Utils::GetBaseName(szFilepath) << "(" << m_nLine << ")\n";
}

const char* CLogger::GetLogLevelName( LogLevel level )
{
    static const char* aryLoglevelName[] = { "DEBUG", "INFO", "ERROR"};
    if (level < 0 || level >= NUM_LOG_LEVELS)
    {
        return "UNKOWN";
    }
    return aryLoglevelName[level];
}
