#pragma once
#include <string.h>
#include <process.h>
#include <windows.h>
#include <string>
#include <psapi.h>
#include <algorithm>

namespace Utils
{
    using namespace std;
    inline const char* GetBaseName(const char* pszFilepath)
    {
        const char *pBackSlash = strrchr(pszFilepath, '\\');
        if (pBackSlash)
        {
            return pBackSlash + 1;
        }
        return "";
    }

    inline string GetParentPath(const char* pszFilepath)
    {
        string sParentPath;
        const char* pBackSlash = strrchr(pszFilepath, '\\');
        if(pBackSlash)
        {
            sParentPath.assign(pszFilepath, pBackSlash-pszFilepath+1);
        }
        return sParentPath;
    }

    inline string GetProcessImageFilePath()
    {
        HANDLE hProcess = GetCurrentProcess();
        HMODULE aryModule[1024] = {0};
        DWORD ncbSize = 0;
        EnumProcessModules(hProcess, aryModule, 1024, &ncbSize);
        char szImagePath[1024] = {0};
        GetModuleFileName(aryModule[0], szImagePath, 1024);
        return szImagePath;
    }

    inline string GetHostName()
    {
        char buf[256];
        DWORD bufLen = sizeof(buf)/sizeof(buf[0]);
        ::GetComputerName(buf, &bufLen);
#if _MSC_VER >= 1600
        for_each(buf, buf+strlen(buf), [](char &c){c = tolower(c);});
#endif
        return buf;
    }
//     inline const char* GetFormatTimeStamp(char *buf, int len)
//     {
//         if (len < 32)
//         {
//             return NULL;
//         }
//         SYSTEMTIME localTime;
//         ::GetLocalTime(&localTime);
//         _snprintf(buf, len, "%02d/%02d/%4d %02d:%02d:%02d.%03d", 
//             localTime.wMonth, localTime.wDay, localTime.wYear,
//             localTime.wHour, localTime.wMinute, localTime.wSecond, localTime.wMilliseconds);
//         return buf;
//     }
    
    inline int GetPid()
    {
        static int pid = 0;
        if(0 == pid)
        {
            pid = _getpid();
        }
        return pid;
    }

    inline int GetTid()
    {
        __declspec(thread) static unsigned long tid = 0;
        if(0 == tid)
        {
            tid = GetCurrentThreadId();
        }
        return tid;
    }

    /* return a 64-bit value representing the number of 
     * 100-nanosecond intervals since January 1, 1601 (UTC)
     */
    inline __int64 GetUTCTime()
    {
        SYSTEMTIME localTime;
        ::GetSystemTime(&localTime);
        FILETIME fileTime;
        ::SystemTimeToFileTime(&localTime, &fileTime);
        return *((__int64*)(&fileTime));
    }

    inline const char* GetFormatTimeStamp(char *buf, int bufSize)
    {
        if (bufSize < 32)
        {
            return NULL;
        }

        static FILETIME lastTime = {0};
        static char secBuf[19] = {0};
        FILETIME curTime;
        SYSTEMTIME localTime;
        ::GetLocalTime(&localTime);
        SystemTimeToFileTime(&localTime, &curTime);
        if( *((__int64*)(&curTime))/(1000*1000*10) - *((__int64*)(&lastTime))/(1000*1000*10) >= 1)
        {
            _snprintf(secBuf, sizeof(secBuf)/sizeof(secBuf[0]), "%02hu/%02hu/%4hu %02hu:%02hu:%02hu", 
                localTime.wMonth, localTime.wDay, localTime.wYear,
                localTime.wHour, localTime.wMinute, localTime.wSecond);
            lastTime = curTime;
        }
        
        memcpy(buf, secBuf, bufSize);
        _snprintf(buf+19, bufSize-19, ".%03d", localTime.wMilliseconds);
        return buf;
    }
};

