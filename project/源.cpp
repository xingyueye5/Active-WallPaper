#include <windows.h>
#include <stdio.h>


BOOL CALLBACK EnumWindowsProc(_In_ HWND hwnd, _In_ LPARAM Lparam)
{
	HWND hDefView = FindWindowEx(hwnd, 0, L"SHELLDLL_DefView", 0);
	if (hDefView != 0) {
		// 找它的下一个窗口，类名为WorkerW，隐藏它
		HWND hWorkerw = FindWindowEx(0, hwnd, L"WorkerW", 0);
		ShowWindow(hWorkerw, SW_HIDE);

		return FALSE;
	}
	return TRUE;
}

int main(int argc, char* argv[])
{

	// 视频路径、1920和1080，要根据实际情况改。建议使用GetSystemMetrics函数获取分辨率属性
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

	// 下面是我电脑上ffplay的路径，要根据实际情况改
	if (CreateProcess(L"D:\\ffmpeg\\ffmpeg-master-latest-win64-lgpl-shared\\bin\\ffplay.exe", (LPWSTR)lpParameter, 0, 0, 0, 0, 0, 0, &si, &pi))
	{
		Sleep(400);												// 等待视频播放器启动完成。可用循环获取窗口尺寸来代替Sleep()
		HWND hProgman = FindWindow(L"Progman", 0);				// 找到PM窗口
		SendMessageTimeout(hProgman, 0x52C, 0, 0, 0, 100, 0);	// 给它发特殊消息
		HWND hFfplay = FindWindow(L"SDL_app", 0);				// 找到视频窗口
		SetParent(hFfplay, hProgman);							// 将视频窗口设置为PM的子窗口
		SetWindowPos(hFfplay, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE);
		EnumWindows(EnumWindowsProc, 0);						// 找到第二个WorkerW窗口并隐藏它

	}
	/*int x, y;
	x = GetSystemMetrics(SM_CXSCREEN); //屏幕宽度
	y = GetSystemMetrics(SM_CYSCREEN); //屏幕高度
	printf("x=%d, y=%d", x, y);
	return 0;*/
}
