#include "StdAfx.h"
#include "MemStream.h"
#include "Buffer.h"
#include <stdio.h>


CMemStream::CMemStream(void)
    :m_buf(NULL)
{
    m_buf = new CBuffer;
}


CMemStream::~CMemStream(void)
{
    delete m_buf;
}