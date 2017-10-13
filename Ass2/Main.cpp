/*
HEADER
*/

#define STRICT
#include <Windows.h>
#include <stdio.h>

#include "Header.h"
#include "StdAfx.h"
#include "SkyeTekAPI.h"
#include "SkyeTekProtocol.h"


char Name[] = "C3980 Asn 2";
HWND hwnd;

FILE* fp = NULL;

void debug(TCHAR* msg);
void output(TCHAR* sz, ...);
SKYETEK_STATUS ReadTagData(LPSKYETEK_READER lpReader, LPSKYETEK_TAG lpTag);

HANDLE readThread;
BOOL reading = FALSE;
char inputBuffer[512];


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
DWORD WINAPI ReadRFID(LPVOID);

/*
WinMain() header
*/
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hprevInstance, LPSTR lspszCmdParam, int nCmdShow) 
{
	MSG Msg;
	WNDCLASSEX Wcl;

	//COPY PAASASSTA
	LPSKYETEK_DEVICE *devices = NULL;
	LPSKYETEK_READER *readers = NULL;
	LPSKYETEK_TAG *lpTags = NULL;
	LPSKYETEK_DATA lpData = NULL;
	SKYETEK_STATUS st;
	unsigned short count;
	unsigned int numDevices;
	unsigned int numReaders;
	int loops = 100;
	int totalReads = 0;
	int failedReads = 0;
	int failedLoops = 0;
	//

	Wcl.cbSize = sizeof(WNDCLASSEX);
	Wcl.style = CS_HREDRAW | CS_VREDRAW;
	Wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wcl.hIconSm = NULL;
	Wcl.hCursor = LoadCursor(NULL, IDC_ARROW);

	Wcl.lpfnWndProc = WndProc;
	Wcl.hInstance = hInst;
	Wcl.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wcl.lpszClassName = Name;

	Wcl.lpszMenuName = "CommandMenu";
	Wcl.cbClsExtra = 0;
	Wcl.cbWndExtra = 0;

	if (!RegisterClassEx(&Wcl))
		return 0;

	hwnd = CreateWindow(Name, Name, WS_OVERLAPPEDWINDOW, 10, 10, 800, 600, NULL, NULL, hInst, NULL);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);





	// Discover reader
	output(_T("Discovering reader...\n"));
	numDevices = SkyeTek_DiscoverDevices(&devices);
	if (numDevices == 0)
	{
		output(_T("*** ERROR: No devices found.\n"));
		fclose(fp);
		return 0;
	}
	output(_T("Discovered %d devices\n"), numDevices);
	numReaders = SkyeTek_DiscoverReaders(devices, numDevices, &readers);
	if (numReaders == 0)
	{
		SkyeTek_FreeDevices(devices, numDevices);
		output(_T("*** ERROR: No readers found.\n"));
		fclose(fp);
		return 0;
	}
	output(_T("Found reader: %s\n"), readers[0]->friendly);
	output(_T("On device: %s [%s]\n"), readers[0]->lpDevice->type, readers[0]->lpDevice->address);
	//





	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return Msg.wParam;
}

/*
WndProc() Header
*/
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT paintstruct;

	switch (Message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case (MENU_FINDREADER):
			// look for RFID reader
			break;
		case (MENU_START):
			// When START menu button is clicked
			// TODO: start reading
			break;
		case (MENU_STOP):
			// When STOP menu button is clicked
			// TODO: close handle(?) of RFID reader
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &paintstruct);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

