#pragma once
#include <string.h>

class CBuffer
{
public:
    enum {MIN_BUF_SIZE=4096};

public:
    CBuffer(void)
        : m_data(NULL)
        , m_bufSize(MIN_BUF_SIZE)
    {
        m_data = (char*)malloc(m_bufSize);
    }

    ~CBuffer(void)
    {
        if(m_data)
            free(m_data);
    }
    
    bool Append(const void *pData, long nSize)
    {
        long newLength = nSize+m_curPos-m_data;
        if(newLength > m_bufSize)
        {
            m_bufSize = (newLength/MIN_BUF_SIZE+1)*MIN_BUF_SIZE;

            char *newData = (char*)malloc(m_bufSize);
            memcpy(newData, m_data, m_curPos-m_data);
            free(m_data);
            
            m_curPos = newData + (m_curPos - m_data);
            m_data = newData;
        }

        memcpy(m_curPos, pData, nSize);
        m_curPos += nSize;
        return true;
    }
    
    int GetSize()
    {  
        return m_curPos-m_data; 
    };
    
    char* GetBuffer() 
    {
        return m_data;
    };

private:
    char        *m_data;
    long        m_bufSize;
    char        *m_curPos;
};