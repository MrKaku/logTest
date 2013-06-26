#pragma once

#include "Buffer.h"
#include <string>
#include "Utils.h"

class CMemStream
{
public:
    CMemStream(void);
    ~CMemStream(void);

    CMemStream& operator<<( bool b )
    {
        m_buf.Append(b?"1":"0", 1);
        return *this;
    }

    CMemStream& operator<<( char c )
    {
        m_buf.Append(&c, sizeof(char));
        return *this;
    }

    CMemStream& operator<<( unsigned char uc )
    {
        m_buf.Append(&uc, sizeof(unsigned char));
        return *this;
    }

    CMemStream& operator<<( short s )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%hd", s);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( unsigned short us )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%hu", us);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( int i )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%d", i);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( unsigned int ui )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%u", ui);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( long l )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%ld", l);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( unsigned long ul )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%lu", ul);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( long long ll )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%I64d", ll);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( unsigned long long ull )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%I64u", ull);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( float f )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%f", f);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( double d )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "%lf", d);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( const char* str )
    {
        m_buf.Append(str, strlen(str));
        return *this;
    }

    CMemStream& operator<<( const std::string& s )
    {
        m_buf.Append(s.c_str(), s.size());
        return *this;
    }

    CMemStream& operator<<( const void* pVoid )
    {
        char str[128]={0};
        _snprintf(str, sizeof(str), "0x%p", pVoid);
        m_buf.Append(str, strlen(str));
        return *this;
    }

    const char* GetBuffer()
    {
        return m_buf.GetBuffer();
    }

    int GetSize()
    {
        return m_buf.GetSize();
    }


private:
    CBuffer         m_buf;
};
