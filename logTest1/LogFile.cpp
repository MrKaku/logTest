#include "StdAfx.h"
#include "LogFile.h"
#include "Utils.h"
#include <io.h>
#include <time.h>

using namespace std;

const int LOGFILE_MAXSIZE = 1024*1024*30;       //每个日志文件最大为30M
const int LOGFILE_MAXNUM  = 8;                  //一个进程最多有8个日志文件

CLogFile::CLogFile(const char *pszFilePath/*=NULL*/)
    : m_fileNo(-1)
    , m_pFile(NULL)
    , m_lastFlushStamp(time(NULL))
{
    if(!pszFilePath)
    {
        m_sPath = GetDefaultLogFilePath();
    }
    else
    {
        m_sPath = pszFilePath;
    }
    
    strncpy(m_cookie, "_log_buf_cookie", sizeof(m_cookie)/sizeof(m_cookie[0]));

    InitializeCriticalSection(&m_cs);
}


CLogFile::~CLogFile(void)
{
    if(m_pFile)
    {
        fclose(m_pFile);
        m_pFile = NULL;
    }
    DeleteCriticalSection(&m_cs);
}

string CLogFile::GetDefaultLogFilePath()
{
    char szPid[64] = {0};
    sprintf(szPid, "%d", Utils::GetPid());
    string sImagePath = Utils::GetProcessImageFilePath();
    string sLogFileName = string(Utils::GetBaseName(sImagePath.c_str())) + "_" + szPid + "@"\
        + Utils::GetHostName() + ".log";
    string sPath = Utils::GetParentPath(sImagePath.c_str()) + sLogFileName;
    return sPath;
}

void CLogFile::Append(const char *buf, int size )
{
    EnterCriticalSection(&m_cs);
    if(!m_pFile)
    {
        OpenNewFile();
    }
    static long sizeWritten = 0;
    _fwrite_nolock(buf, size, 1, m_pFile); // 由Write函数做锁保护
    sizeWritten += size+1;  // \r\n occupies 2 bytes
    if (sizeWritten >= LOGFILE_MAXSIZE)
    {
        fclose(m_pFile);
        OpenNewFile();
        sizeWritten = 0;
    }
    FlushFile();
    LeaveCriticalSection(&m_cs);
}

std::string CLogFile::GetRotatedFilePath()
{
    if( m_fileNo == LOGFILE_MAXNUM )
    {
        string sFirstFilePath = GetFilePath(0);
        remove(sFirstFilePath.c_str());
        for(int i=0; i<LOGFILE_MAXNUM; ++i)
        {
            rename(GetFilePath(i+1).c_str(), GetFilePath(i).c_str());
        }
    }
    else
    {
        m_fileNo ++;
    }
    return GetFilePath(m_fileNo);
}

std::string CLogFile::GetFilePath(int fileNo)
{
    char szFileNo[16] = {0};
    _snprintf(szFileNo, sizeof(szFileNo)/sizeof(szFileNo[0]), "_%02d", fileNo);

    string sParentPath = Utils::GetParentPath(m_sPath.c_str());
    string sBaseName = Utils::GetBaseName(m_sPath.c_str());
    size_t pos = sBaseName.find_last_of('.');
    if (string::npos != pos)
    {
        sBaseName.insert(pos, szFileNo);
    }
    else
    {
        sBaseName.append(szFileNo);
    }

    return sParentPath+sBaseName;
}

void CLogFile::OpenNewFile()
{
    m_pFile = fopen(GetRotatedFilePath().c_str(), "a+");
    setvbuf(m_pFile, m_buf, _IOLBF, sizeof(m_buf));
}

void CLogFile::FlushFile()
{
    if(!m_pFile)
        return;

    time_t curStamp = time(NULL);
    if(curStamp-m_lastFlushStamp >= 1)
    {
        ::fflush(m_pFile);
        m_lastFlushStamp = curStamp;
    }
}