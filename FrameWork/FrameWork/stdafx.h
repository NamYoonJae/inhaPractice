// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once



#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string.h>
#include <stdio.h>

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include <d3dx9.h>
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

extern HWND g_hWnd;

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#define Singletone(class_name)\
	private:\
	class_name(void);\
	~class_name(void);\
	public:\
	static class_name* GetInstance()\
	{\
		static class_name instance;\
	return &instance;\
	}

#define SafeRelease(p)	{if(p) p->Release(); p = NULL;}
#define SafeDelete(p) {if(p) delete p; p = NULL;}
#define SafeDeleteArray(p) {if(p) delete[] p; p = NULL;}

extern HWND g_hWnd;

#include "cDeviceManage.h"
#include "Logger.h"
#include "EventManager.h"


#pragma region json
#ifndef _MSC_VER // json������� �䱸
#define _CRT_SECURE_NO_WARNINGS
#endif
#include "json parson.h"
#include "json additional code.h"
#pragma endregion 