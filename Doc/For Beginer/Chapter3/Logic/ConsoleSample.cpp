// ConsoleSample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
int i=1;
switch (i)
{
 case 1: 
   printf("i = 1");
 case 2: 
   printf("i < 2");
 break;

 case 3: 
   printf("i =3");
 break;
}

printf("i: %i", i);
return 0;
}
