#include <windows.h>
#include <stdio.h>


BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// ��������һ�����ڣ�����ΪWorkerW��������
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}

int main(int argc, char* argv[])
{

	// ��Ƶ·����1920��1080��Ҫ����ʵ������ġ�����ʹ��GetSystemMetrics������ȡ�ֱ�������
	int choose;
	scanf_s("%d", &choose);
		LPCWSTR lpParameter = L" D:\\ffmpeg\\videoplayback1.mp4  -noborder -x 1920 -y 1080  -loop 0";
		switch (choose) {
		case 2:  lpParameter = L" D:\\ffmpeg\\videoplayback2.mp4  -noborder -x 1920 -y 1080  -loop 0"; break;
		case 3:  lpParameter = L" D:\\ffmpeg\\videoplayback3.mp4  -noborder -x 1920 -y 1080  -loop 0"; break;
		case 4:  lpParameter = L" D:\\ffmpeg\\videoplayback4.mp4  -noborder -x 1920 -y 1080  -loop 0"; break;
		case 5:  lpParameter = L" D:\\ffmpeg\\videoplayback5.mp4  -noborder -x 1920 -y 1080  -loop 0"; break;
		}			
	STARTUPINFO si{ 0 };
	PROCESS_INFORMATION pi{ 0 };

	// �������ҵ�����ffplay��·����Ҫ����ʵ�������
	if (CreateProcess(L"D:\\ffmpeg\\ffmpeg-master-latest-win64-lgpl-shared\\bin\\ffplay.exe", (LPWSTR)lpParameter, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		Sleep(400);												// �ȴ���Ƶ������������ɡ�����ѭ����ȡ���ڳߴ�������Sleep()
		HWND hProgman = FindWindow(L"Progman", 0);				// �ҵ�PM����
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);	// ������������Ϣ
		HWND hFfplay = FindWindow(L"SDL_app", 0);				// �ҵ���Ƶ����
		SetParent(hFfplay, hProgman);							// ����Ƶ��������ΪPM���Ӵ���
		SetWindowPos(hFfplay, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE);
		EnumWindows(EnumWindowsProc, 0);						// �ҵ��ڶ���WorkerW���ڲ�������

	}
	/*int x, y;
	x = GetSystemMetrics(SM_CXSCREEN); //��Ļ���
	y = GetSystemMetrics(SM_CYSCREEN); //��Ļ�߶�
	printf("x=%d, y=%d", x, y);
	return 0;*/
}
