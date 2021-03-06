//
// skulk@ioc.ninja
//



class X_OS_API_TRAITS
{
protected:
	X_OS_API_TRAITS()
	{
	}

public:
	// Advapi32
	X_OS_API_MODULE_BEGIN(Advapi32, X_OBFUSCATED_STRING_W(L"Advapi32.dll"))
		X_OS_API_MODULE_FUNCTION_1(LONG, RegCloseKey, HKEY)
#ifdef _UNICODE
			// UNICODE API's
			X_OS_API_MODULE_FUNCTION_3(LONG, RegOpenKeyW, HKEY, LPCWSTR, PHKEY)
			X_OS_API_MODULE_FUNCTION_5(LONG, RegOpenKeyExW, HKEY, LPCWSTR, DWORD, REGSAM, PHKEY)
			X_OS_API_MODULE_FUNCTION_6(LONG, RegSetValueExW, HKEY, LPCWSTR, DWORD, DWORD, const uint8_t*, DWORD)
#else
			// ANSI API's
			X_OS_API_MODULE_FUNCTION_3(LONG, RegOpenKeyA, HKEY, LPCSTR, PHKEY)
			X_OS_API_MODULE_FUNCTION_5(LONG, RegOpenKeyExA, HKEY, LPCSTR, DWORD, REGSAM, PHKEY)
			X_OS_API_MODULE_FUNCTION_6(LONG, RegSetValueExA, HKEY, LPCWSTR, DWORD, DWORD, const uint8_t*, DWORD)
#endif
		X_OS_API_MODULE_END(Advapi32)

		// Iphlpapi
		X_OS_API_MODULE_BEGIN(Iphlpapi, X_OBFUSCATED_STRING_W(L"Iphlpapi.dll"))
			X_OS_API_MODULE_FUNCTION_1(BOOL, IcmpCloseHandle, HANDLE)
			X_OS_API_MODULE_FUNCTION_0(HANDLE, IcmpCreateFile)
			X_OS_API_MODULE_FUNCTION_8(DWORD, IcmpSendEcho, HANDLE, IPAddr, LPVOID, WORD, PIP_OPTION_INFORMATION, LPVOID, DWORD, DWORD)
		X_OS_API_MODULE_END(Iphlpapi)

		// Kernel32
		X_OS_API_MODULE_BEGIN(Kernel32, X_OBFUSCATED_STRING_W(L"Kernel32.dll"))
			X_OS_API_MODULE_FUNCTION_2(PVOID, AddVectoredExceptionHandler, ULONG, PVECTORED_EXCEPTION_HANDLER)
			X_OS_API_MODULE_FUNCTION_1(BOOL, CloseHandle, HANDLE)
			X_OS_API_MODULE_FUNCTION_6(HANDLE, CreateThread, LPSECURITY_ATTRIBUTES, SIZE_T, LPTHREAD_START_ROUTINE, LPVOID, DWORD, LPDWORD)
			X_OS_API_MODULE_FUNCTION_1(void, DeleteCriticalSection, LPCRITICAL_SECTION)
			X_OS_API_MODULE_FUNCTION_1(void, EnterCriticalSection, LPCRITICAL_SECTION)
			X_OS_API_MODULE_FUNCTION_1(void, ExitProcess, DWORD)
			X_OS_API_MODULE_FUNCTION_1(BOOL, FindClose, HANDLE)
			X_OS_API_MODULE_FUNCTION_0(HANDLE, GetCurrentProcess)
			X_OS_API_MODULE_FUNCTION_2(BOOL, GetFileSizeEx, HANDLE, PLARGE_INTEGER)
			X_OS_API_MODULE_FUNCTION_0(DWORD, GetLastError)
			X_OS_API_MODULE_FUNCTION_1(void, GetNativeSystemInfo, LPSYSTEM_INFO)
			X_OS_API_MODULE_FUNCTION_0(HANDLE, GetProcessHeap)
			X_OS_API_MODULE_FUNCTION_0(LCID, GetThreadLocale)
			X_OS_API_MODULE_FUNCTION_0(DWORD, GetTickCount)
			X_OS_API_MODULE_FUNCTION_3(LPVOID, HeapAlloc, HANDLE, DWORD, SIZE_T)
			X_OS_API_MODULE_FUNCTION_3(BOOL, HeapFree, HANDLE, DWORD, LPVOID)
			X_OS_API_MODULE_FUNCTION_1(void, InitializeCriticalSection, LPCRITICAL_SECTION)
			X_OS_API_MODULE_FUNCTION_2(BOOL, IsBadReadPtr, const VOID*, UINT_PTR)
			X_OS_API_MODULE_FUNCTION_1(void, LeaveCriticalSection, LPCRITICAL_SECTION)
			X_OS_API_MODULE_FUNCTION_2(HGLOBAL, LoadResource, HMODULE, HRSRC)
			X_OS_API_MODULE_FUNCTION_5(BOOL, ReadFile, HANDLE, LPVOID, DWORD, LPDWORD, LPOVERLAPPED)
			X_OS_API_MODULE_FUNCTION_1(ULONG, RemoveVectoredExceptionHandler, PVOID)
			X_OS_API_MODULE_FUNCTION_1(DWORD, ResumeThread, HANDLE)
			X_OS_API_MODULE_FUNCTION_2(BOOL, SetPriorityClass, HANDLE, DWORD)
			X_OS_API_MODULE_FUNCTION_2(BOOL, SetThreadPriority, HANDLE, DWORD)
			X_OS_API_MODULE_FUNCTION_1(void, Sleep, DWORD)
			X_OS_API_MODULE_FUNCTION_1(void, SetLastError, DWORD)
			X_OS_API_MODULE_FUNCTION_4(LPVOID, VirtualAlloc, LPVOID, SIZE_T, DWORD, DWORD)
			X_OS_API_MODULE_FUNCTION_3(BOOL, VirtualFree, LPVOID, SIZE_T, DWORD)
			X_OS_API_MODULE_FUNCTION_4(BOOL, VirtualProtect, LPVOID, SIZE_T, DWORD, PDWORD)
			X_OS_API_MODULE_FUNCTION_2(DWORD, WaitForSingleObject, HANDLE, DWORD)
			X_OS_API_MODULE_FUNCTION_5(BOOL, WriteFile, HANDLE, LPCVOID, DWORD, LPDWORD, LPOVERLAPPED)
#ifdef _UNICODE
			// UNICODE API's
			X_OS_API_MODULE_FUNCTION_7(HANDLE, CreateFileW, LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)
			X_OS_API_MODULE_FUNCTION_2(HANDLE, FindFirstFileW, LPCWSTR, LPWIN32_FIND_DATAW)
			X_OS_API_MODULE_FUNCTION_2(BOOL, FindNextFileW, HANDLE, LPWIN32_FIND_DATAW)
			X_OS_API_MODULE_FUNCTION_3(HRSRC, FindResourceW, HMODULE, LPCWSTR, LPCWSTR)
			X_OS_API_MODULE_FUNCTION_3(BOOL, GetComputerNameExW, COMPUTER_NAME_FORMAT, LPWSTR, LPDWORD)
			X_OS_API_MODULE_FUNCTION_2(DWORD, GetCurrentDirectoryW, DWORD, LPWSTR)
			X_OS_API_MODULE_FUNCTION_1(DWORD, GetFileAttributesW, LPCWSTR)
			X_OS_API_MODULE_FUNCTION_3(DWORD, GetModuleFileNameW, HMODULE, LPWSTR, DWORD)
			X_OS_API_MODULE_FUNCTION_1(HMODULE, GetModuleHandleW, LPCWSTR)
			X_OS_API_MODULE_FUNCTION_2(UINT, GetSystemDirectoryW, LPWSTR, UINT)
			X_OS_API_MODULE_FUNCTION_1(void, OutputDebugStringW, LPCWSTR)
#else
			// ANSI API's
			X_OS_API_MODULE_FUNCTION_7(HANDLE, CreateFileA, LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE)
			X_OS_API_MODULE_FUNCTION_2(HANDLE, FindFirstFileA, LPCSTR, LPWIN32_FIND_DATAA)
			X_OS_API_MODULE_FUNCTION_2(BOOL, FindNextFileA, HANDLE, LPWIN32_FIND_DATAA)
			X_OS_API_MODULE_FUNCTION_3(HRSRC, FindResourceA, HMODULE, LPCSTR, LPCSTR)
			X_OS_API_MODULE_FUNCTION_3(BOOL, GetComputerNameExA, COMPUTER_NAME_FORMAT, LPSTR, LPDWORD)
			X_OS_API_MODULE_FUNCTION_2(DWORD, GetCurrentDirectoryA, DWORD, LPSTR)
			X_OS_API_MODULE_FUNCTION_1(DWORD, GetFileAttributesA, LPCSTR)
			X_OS_API_MODULE_FUNCTION_3(DWORD, GetModuleFileNameA, HMODULE, LPSTR, DWORD)
			X_OS_API_MODULE_FUNCTION_1(HMODULE, GetModuleHandleA, LPCSTR)
			X_OS_API_MODULE_FUNCTION_2(UINT, GetSystemDirectoryA, LPSTR, UINT)
			X_OS_API_MODULE_FUNCTION_1(void, OutputDebugStringA, LPCSTR)
#endif
		X_OS_API_MODULE_END(Kernel32)

		// Ole32
		X_OS_API_MODULE_BEGIN(Ole32, X_OBFUSCATED_STRING_W(L"Ole32.dll"))
			X_OS_API_MODULE_FUNCTION_5(HRESULT, CoCreateInstance, REFCLSID, LPUNKNOWN, DWORD, REFIID, LPVOID*)
			X_OS_API_MODULE_FUNCTION_1(HRESULT, CoInitialize, LPVOID)
			X_OS_API_MODULE_FUNCTION_0(void, CoUninitialize)
		X_OS_API_MODULE_END(Ole32)

		// OleAut32
		X_OS_API_MODULE_BEGIN(OleAut32, X_OBFUSCATED_STRING_W(L"OleAut32.dll"))
		X_OS_API_MODULE_FUNCTION_1(BSTR, SysAllocString, const OLECHAR*)
		X_OS_API_MODULE_FUNCTION_1(void, SysFreeString, BSTR)
		X_OS_API_MODULE_END(OleAut32)

		// User32
		X_OS_API_MODULE_BEGIN(User32, X_OBFUSCATED_STRING_W(L"User32.dll"))
		X_OS_API_MODULE_FUNCTION_1(BOOL, DestroyWindow, HWND)
		X_OS_API_MODULE_FUNCTION_1(void, PostQuitMessage, int)
		X_OS_API_MODULE_FUNCTION_1(BOOL, TranslateMessage, LPMSG)
#ifdef _UNICODE
			// UNICODE API's
			X_OS_API_MODULE_FUNCTION_12(HWND, CreateWindowExW, DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID)
			X_OS_API_MODULE_FUNCTION_4(LRESULT, DefWindowProcW, HWND, UINT, WPARAM, LPARAM)
			X_OS_API_MODULE_FUNCTION_1(LRESULT, DispatchMessageW, LPMSG)
			X_OS_API_MODULE_FUNCTION_4(BOOL, GetMessageW, LPMSG, HWND, UINT, UINT)
			X_OS_API_MODULE_FUNCTION_4(BOOL, MeesageBoxW, HWND, LPCWSTR, LPCWSTR, UINT)
			X_OS_API_MODULE_FUNCTION_1(ATOM, RegisterClassExW, const WNDCLASSEX*)
			X_OS_API_MODULE_FUNCTION_4(ATOM, SystemParametersInfoW, UINT, UINT, PVOID, UINT)
#else
			// ANSI API's
			X_OS_API_MODULE_FUNCTION_12(LRESULT, CreateWindowExA, DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID)
			X_OS_API_MODULE_FUNCTION_4(LRESULT, DefWindowProcA, HWND, UINT, WPARAM, LPARAM)
			X_OS_API_MODULE_FUNCTION_1(LRESULT, DispatchMessageA, LPMSG)
			X_OS_API_MODULE_FUNCTION_4(BOOL, GetMessageA, LPMSG, HWND, UINT, UINT)
			X_OS_API_MODULE_FUNCTION_4(BOOL, MeesageBoxA, HWND, LPCSTR, LPCSTR, UINT)
			X_OS_API_MODULE_FUNCTION_1(ATOM, RegisterClassExA, const WNDCLASSEX*)
			X_OS_API_MODULE_FUNCTION_4(ATOM, SystemParametersInfoA, UINT, UINT, PVOID, UINT)
#endif
		X_OS_API_MODULE_END(User32)

		// Wininet
		X_OS_API_MODULE_BEGIN(Wininet, X_OBFUSCATED_STRING_W(L"Wininet.dll"))
#ifdef _UNICODE
			// UNICODE API's
			X_OS_API_MODULE_FUNCTION_5(HINTERNET, InternetOpen, LPCWSTR, DWORD, LPCWSTR, LPCWSTR, DWORD)
			X_OS_API_MODULE_FUNCTION_6(HINTERNET, InternetOpenUrl, HINTERNET, LPCWSTR, LPCWSTR, DWORD, DWORD, DWORD)
#else
			// ANSI API's
			X_OS_API_MODULE_FUNCTION_5(HINTERNET, InternetOpen, LPCSTR, DWORD, LPCSTR, LPCSTR, DWORD)
			X_OS_API_MODULE_FUNCTION_6(HINTERNET, InternetOpenUrl, HINTERNET, LPCSTR, LPCSTR, DWORD, DWORD, DWORD)
#endif
			X_OS_API_MODULE_FUNCTION_1(BOOL, InternetCloseHandle, HINTERNET)
			X_OS_API_MODULE_FUNCTION_4(BOOL, InternetReadFile, HINTERNET, LPVOID, DWORD, LPDWORD)
		X_OS_API_MODULE_END(Wininet)
			
		// Ws2_32
		X_OS_API_MODULE_BEGIN(Ws2_32, X_OBFUSCATED_STRING_W(L"Ws2_32.dll"))
			X_OS_API_MODULE_FUNCTION_1(int, closesocket, SOCKET)
			X_OS_API_MODULE_FUNCTION_3(int, connect, SOCKET, const struct sockaddr*, int)
			X_OS_API_MODULE_FUNCTION_1(u_short, htons, u_short)
			X_OS_API_MODULE_FUNCTION_1(unsigned long, inet_addr, const char*)
			X_OS_API_MODULE_FUNCTION_3(int, ioctlsocket, SOCKET, long, u_long*)
			X_OS_API_MODULE_FUNCTION_5(int, select, int, fd_set*, fd_set*, fd_set*, const struct timeval*)
			X_OS_API_MODULE_FUNCTION_3(SOCKET, socket, int, int, int)
			X_OS_API_MODULE_FUNCTION_0(int, WSACleanup)
			X_OS_API_MODULE_FUNCTION_2(int, WSAStartup, WORD, LPWSADATA)
		X_OS_API_MODULE_END(Ws2_32)
};
