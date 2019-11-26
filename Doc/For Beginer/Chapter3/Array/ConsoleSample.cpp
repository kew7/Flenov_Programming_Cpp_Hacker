// ConsoleSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
int profit[2];
profit[0] = 10;
profit[1] = 11;

int i[] = {10, 20, 30};
char name[]="Flenov";

printf("profit: %i, %i \n", profit[0], profit[1]);
printf("i: %i, %i, %i \n", i[0], i[1], i[2]);
printf(name);
return 0;
}
