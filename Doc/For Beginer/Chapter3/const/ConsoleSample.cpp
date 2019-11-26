// ConsoleSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_ARRAY 12

int _tmain(int argc, _TCHAR* argv[])
{
	int profit[MAX_ARRAY];
    
	for (int i=0; i<MAX_ARRAY; i++)
        profit[i] = i;

	for (i=0; i<MAX_ARRAY; i++)
		printf("profit[%i] = %i\n", i, profit[i]);
	
	return 0;
}
