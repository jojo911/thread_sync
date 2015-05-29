#include "stdafx.h"
#include <Windows.h>

/************
	适用范围：它只能同步一个进程中的线程，不能跨进程同步。一般用它来做单个进程内的代码快同步,效率比较高。

	保证在某一时刻只有一个线程能访问数据的简便办法。
		在任意时刻只允许一个线程对共享资源进行访问。
		如果有多个线程试图同时访问临界区，那么 在有一个线程进入后其他所有试图访问此临界区的线程将被挂起，并一直持续到进入临界区的线程离开。
		临界区在被释放后，其他线程可以继续抢占，并以此达到用原子方式操 作共享资源的目的。 

	同一个线程内临界区可以进入多次
************/

CRITICAL_SECTION g_cs;

DWORD CALLBACK thread_proc(LPVOID params)
{
	EnterCriticalSection(&g_cs);

	printf("this is thread %d doing\n", *((int*)params));
	
	for(char c = 'A'; c <= 'Z'; ++c)
	{
		EnterCriticalSection(&g_cs);
		printf("%c",c);
		LeaveCriticalSection(&g_cs);
	}
	printf("\n");
	
	LeaveCriticalSection(&g_cs);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	InitializeCriticalSection(&g_cs);

	int a[10] = {0};
	for (int i=0; i<10; i++)
	{
		a[i] = i+1;
		CreateThread(0, 0, thread_proc, (LPVOID)&a[i], 0, 0);
	}

	getchar();

	DeleteCriticalSection(&g_cs);

	return 0;
}

