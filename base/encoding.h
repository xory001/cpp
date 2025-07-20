#pragma once

#include <string>

#ifdef WIN32

namespace Encoding
{
	//Functions declaration
	std::string Utf16ToUtf8( const std::wstring& strUtf16 );
	std::wstring Utf8ToUtf16( const std::string& strUtf16 );
	std::string Utf16ToMultiByte( const std::wstring& strUtf16 );
	std::wstring MultiByteToUtf16( const std::string& strMultiByte );
	std::string MultiByteToUtf8( const std::string& strMultiByte );
	std::string Utf8ToMultiByte( const std::string& strUtf8 );
	std::string FromHex( const std::string& hex );
	std::string ToHex( const std::string& str );
	uint32_t ColorFromHex( const std::string& str );
	std::string ColorToHex(uint32_t rgb );

    //////////////////////////////////////////////////////////////////////////

    //Functions implementation
	inline std::string Utf16ToUtf8( const std::wstring& strUtf16 )
	{
        if ( strUtf16.empty() ) 
		{
            return std::string();
        }

        int nUtf8Size = WideCharToMultiByte( CP_UTF8, 0, strUtf16.c_str(), -1, nullptr, 0, nullptr, nullptr );
        if ( 0 == nUtf8Size )
		{
			return std::string();
        }

        std::string strUtf8( nUtf8Size, 0 );
		// C++11 or above: &strUtf8[0] is safe for contiguous buffer access
        int nConvertedSize = WideCharToMultiByte( CP_UTF8, 0, strUtf16.c_str(), -1, &strUtf8[0], nUtf8Size, nullptr, nullptr );
        if ( 0 == nConvertedSize ) 
		{
			return std::string();
        }

		strUtf8.resize( nUtf8Size - 1 ); // remove null at tail, std::string don't need it.
        return strUtf8;
	}

	inline std::wstring Utf8ToUtf16( const std::string& strUtf16 )
	{
        if ( strUtf16.empty() ) 
		{
            return std::wstring();
        }

        int nUtf16Size = MultiByteToWideChar( CP_UTF8, 0, strUtf16.c_str(), -1, nullptr, 0 );
        if ( 0 == nUtf16Size )
		{
			return std::wstring();
        }

        std::wstring strUtf16Out( nUtf16Size, 0 );
        int nConvertedSize = MultiByteToWideChar( CP_UTF8, 0, strUtf16.c_str(), -1, &strUtf16Out[0], nUtf16Size );
        if ( 0 == nConvertedSize ) 
		{
			return std::wstring();
        }

		strUtf16Out.resize( nUtf16Size - 1 );
        return strUtf16Out;
	}

	inline std::string Utf16ToMultiByte( const std::wstring& strUtf16 )
    {
        if ( strUtf16.empty() )
        {
            return std::string();
        }

        int nAsciiSize = WideCharToMultiByte( CP_ACP, 0, strUtf16.c_str(), -1, nullptr, 0, nullptr, nullptr );
        if ( 0 == nAsciiSize )
        {
            return std::string();
        }

        std::string strAscii( nAsciiSize, 0 );
        int nConvertedSize = WideCharToMultiByte( CP_ACP, 0, strUtf16.c_str(), -1, &strAscii[0], nAsciiSize, nullptr, nullptr );
        if ( 0 == nConvertedSize )
        {
            return std::string();
        }

        strAscii.resize( nAsciiSize - 1 );
        return strAscii;
    }

	inline std::wstring MultiByteToUtf16( const std::string& strMultiByte )
	{
        if ( strMultiByte.empty() ) 
		{
            return std::wstring();
        }

        int nUtf16Size = MultiByteToWideChar( CP_ACP, 0, strMultiByte.c_str(), -1, nullptr, 0 );
        if ( 0 == nUtf16Size == 0 )
		{
			return std::wstring();
        }

        std::wstring strUtf16( nUtf16Size, 0 );
        int nConvetedSize = MultiByteToWideChar( CP_ACP, 0, strMultiByte.c_str(), -1, &strUtf16[0], nUtf16Size );
        if ( 0 == nConvetedSize ) 
		{
			return std::wstring();
        }

        strUtf16.resize( nUtf16Size - 1 );
        return strUtf16;
    }

	inline std::string MultiByteToUtf8( const std::string& strMultiByte )
	{
        if ( strMultiByte.empty() )
		{
            return std::string();
        }

        int nUtf16Size = MultiByteToWideChar( CP_ACP, 0, strMultiByte.c_str(), -1, nullptr, 0 );
        if ( 0 == nUtf16Size ) 
		{
			return std::string();
        }

        std::wstring strUtf16( nUtf16Size, 0 );
        int nUtf16ConvertedSize = MultiByteToWideChar( CP_ACP, 0, strMultiByte.c_str(), -1, &strUtf16[0], nUtf16Size );
        if ( 0 == nUtf16ConvertedSize ) 
		{
			return std::string();
        }

        int nUtf8Size = WideCharToMultiByte( CP_UTF8, 0, strUtf16.c_str(), -1, nullptr, 0, nullptr, nullptr );
        if ( 0 == nUtf8Size ) 
		{
			return std::string();
        }

        std::string strUtf8( nUtf8Size, 0 );
        int nUtf8ConvertedSize = WideCharToMultiByte( CP_UTF8, 0, strUtf16.c_str(), -1, &strUtf8[0], nUtf8Size, nullptr, nullptr );
        if ( 0 == nUtf8ConvertedSize )
		{
			return std::string();
        }

        strUtf8.resize( nUtf8Size - 1 );
        return strUtf8;
    }

    inline std::string Utf8ToMultiByte( const std::string& strUtf8 ) 
	{
        if ( strUtf8.empty() ) 
		{
            return std::string();
        }

        int nUtf16Size = MultiByteToWideChar( CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0 );
        if ( 0 == nUtf16Size )
		{
			return std::string();
        }

        std::wstring strUtf16( nUtf16Size, 0 );
        int nUtf16ConvertedSize = MultiByteToWideChar( CP_UTF8, 0, strUtf8.c_str(), -1, &strUtf16[0], nUtf16Size );
        if ( 0 == nUtf16ConvertedSize )
		{
			return std::string();
        }

        int nMultiByteSize = WideCharToMultiByte( CP_ACP, 0, strUtf16.c_str(), -1, nullptr, 0, nullptr, nullptr );
        if ( 0 == nMultiByteSize ) 
		{
			return std::string();
        }

        std::string strMultiByte( nMultiByteSize, 0 );
        int nMultiByteConvertedSize = WideCharToMultiByte( CP_ACP, 0, strUtf16.c_str(), -1, &strMultiByte[0], nMultiByteSize, nullptr, nullptr );
        if ( 0 == nMultiByteConvertedSize )
		{
			return std::string();
        }

        strMultiByte.resize( nMultiByteSize - 1 );
        return strMultiByte;
    }

	inline std::string FromHex(const std::string& hex)
	{
		std::string tmp;
		for(size_t i=0; i<hex.length()/2; ++i)
		{
			unsigned char r = 0;
			char x1 = hex.at(i*2);
			char x2 = hex.at(i*2+1);
			
			if(x1>='0' && x1<='9')
				r = (x1-'0')<<4;
			else if(x1>='a' && x1<='f')
				r = (x1-'a'+10)<<4;
			
			if(x2>='0' && x2<='9')
				r += (x2-'0');
			else if(x2>='a' && x2<='f')
				r += (x2-'a'+10);
			
			tmp += r;
		}
		return tmp;
	}

	inline std::string ToHex(const std::string& str)
	{
		static char dict[] = "0123456789abcdef ";
		std::string tmp;
		for(size_t i=0; i<str.size(); ++i)
		{
			unsigned char r = str.at(i);
			tmp += dict[(r>>4)&0x0f];
			tmp += dict[ r & 0x0f ];
		}
		return tmp;
	}

	inline uint32_t ColorFromHex(const std::string& str)
	{
		const char * val = str.c_str();
		if(NULL == val)
			return 0;
		if(str.length() < 7)
			return 0;
		const char* color = strrchr(val, '#');
		if(NULL == color || strlen(color)<6)
			return 0;

		uint32_t rgb = 0;
		char buff[7] = {0};
		memcpy(buff, color+5, 2);
		memcpy(buff+2, color+3, 2);
		memcpy(buff+4, color+1, 2);
		sscanf_s(buff, "%X", &rgb);

		const char* alpha = strrchr(color, ',');
		if(alpha && strlen(alpha)>1)
		{
			uint32_t a = 0;
			char abuff[4] = {0};
			strcpy_s(abuff, 3, alpha+1);
			sscanf_s(abuff, "%X", &a);
			rgb |= (a<<24);
		}
		else
			rgb |= 0xff000000;

		return rgb;
	}

	inline std::string ColorToHex(uint32_t rgb)
	{
		static char dict[] = "0123456789ABCDEF ";
		std::string tmp;
		tmp += "#";
		tmp += dict[(rgb&0x000000f0)>>4];
		tmp += dict[rgb&0x0000000f];
		tmp += dict[(rgb&0x0000f000)>>12];
		tmp += dict[(rgb&0x00000f00)>>8];
		tmp += dict[(rgb&0x00f00000)>>20];
		tmp += dict[(rgb&0x000f0000)>>16];
		return tmp;
	}
}

#endif