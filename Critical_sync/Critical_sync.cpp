#include "stdafx.h"
#include <Windows.h>

/************
	���÷�Χ����ֻ��ͬ��һ�������е��̣߳����ܿ����ͬ����һ�������������������ڵĴ����ͬ��,Ч�ʱȽϸߡ�

	��֤��ĳһʱ��ֻ��һ���߳��ܷ������ݵļ��취��
		������ʱ��ֻ����һ���̶߳Թ�����Դ���з��ʡ�
		����ж���߳���ͼͬʱ�����ٽ�������ô ����һ���߳̽��������������ͼ���ʴ��ٽ������߳̽������𣬲�һֱ�����������ٽ������߳��뿪��
		�ٽ����ڱ��ͷź������߳̿��Լ�����ռ�����Դ˴ﵽ��ԭ�ӷ�ʽ�� ��������Դ��Ŀ�ġ� 

	ͬһ���߳����ٽ������Խ�����
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

