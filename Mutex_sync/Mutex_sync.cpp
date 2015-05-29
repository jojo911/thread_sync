// Mutex_sync.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

HANDLE hMutex;

DWORD CALLBACK thread_proc(LPVOID params)
{
	WaitForSingleObject(hMutex,INFINITE);

	printf("this is thread %d doing\n", *((int*)params));

	for(char c = 'A'; c <= 'Z'; ++c)
	{
		//WaitForSingleObject(hMutex,INFINITE);
		printf("%c",c);
		//ReleaseMutex(hMutex);
	}
	printf("\n");

	//ReleaseMutex(hMutex);

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	hMutex = CreateMutex(NULL,true,NULL);

	
	int a[10] = {0};
	for (int i=0; i<10; i++)
	{
		a[i] = i+1;
		CreateThread(0, 0, thread_proc, (LPVOID)&a[i], 0, 0);
	}

	WaitForSingleObject(hMutex,INFINITE);
	ReleaseMutex(hMutex);
	ReleaseMutex(hMutex);

	getchar();

	return 0;
}