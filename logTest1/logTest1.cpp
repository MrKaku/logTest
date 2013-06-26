// logTest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include "Utils.h"
#include "logger.h"
#include <windows.h>
#include <assert.h>
//#include <TimeCounter.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    CLogger::m_baseLevel = CLogger::LEVEL_INFO;
//     CTimeCounter tc;
//     tc.Begin("Log");
    int n;
    int *p = &n;
    for (int i=0; i<50000; ++i)
    {
        LOG_INFO << "m_ServerGroup.GetTotalNodeCount() SetType = SC_REDU_SEND_TYPE_BROADCAST" << "result:" << p;
        LOG_INFO << "m_ServerGroup.GeaTotalNodeCount() SetType = SC_REDU_SEND_TYPE_BROADCAST" << "result:" << p;
    }
//    tc.End();
	return 0;
}