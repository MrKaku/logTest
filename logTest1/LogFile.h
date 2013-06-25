#pragma once
#include <string>
#include <windows.h>
#include "Buffer.h"

class CLogFile
{
public:
    CLogFile(const char *pszFilePath=NULL);
    ~CLogFile(void);

    void Append(const char *buf, int size);

private:
    std::string GetRotatedFilePath();
    std::string GetDefaultLogFilePath();
    std::string GetFilePath(int fileNo);

    void OpenNewFile();
    void FlushFile();
private:
    FILE                    *m_pFile;
    std::string             m_sPath;
    int                     m_fileNo;
    CRITICAL_SECTION        m_cs;
    char                    m_cookie[16];
    char                    m_buf[64*1024];
    time_t                  m_lastFlushStamp;
};

