// BufferOverflow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "string.h"
#include "tchar.h"


int _tmain(int argc, _TCHAR* argv[])
{
	char buf[1024];
	char input[2048];

	//strcpy(buf, input); // Никогда не делайте так

	_TCHAR bufw[10];
	printf("Buffer size: %d\n", sizeof(bufw));
	printf("Buffer size: %d\n", sizeof(bufw) / sizeof(bufw[0]));

	return 0;
}

