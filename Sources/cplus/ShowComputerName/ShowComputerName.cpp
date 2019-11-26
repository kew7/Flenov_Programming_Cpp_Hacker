// ShowComputerName.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <winsock2.h>

int _tmain(int argc, _TCHAR* argv[])
{
	for (int i=ComputerNameNetBIOS; i<ComputerNamePhysicalDnsFullyQualified; i++)
	{
		TCHAR szName[256];
		DWORD dwLen = sizeof szName / sizeof TCHAR;

		TCHAR *cnf;
		switch (i)
		{
			case 0: cnf = _T("ComputerNameNetBIOS"); break;
			case 1: cnf = _T("ComputerNameDnsHostname"); break;
			case 2: cnf = _T("ComputerNameDnsDomain"); break;
			case 3: cnf = _T("ComputerNameDnsFullyQualified"); break;
			case 4: cnf = _T("ComputerNamePhysicalNetBIOS"); break;
			case 5: cnf = _T("ComputerNamePhysicalDnsHostname"); break;
			case 6: cnf = _T("ComputerNamePhysicalDnsDomain"); break;
			case 7: cnf = _T("ComputerNamePhysicalDnsFullyQualified"); break;
			default: cnf = _T("Unknown"); break;
		}

		BOOL fRet = GetComputerNameEx((COMPUTER_NAME_FORMAT)i, szName, &dwLen);
		if (fRet){
			printf("%s has format %s \n", szName, cnf);
		} else {
			printf("Error %d \n", GetLastError());
		}
	}
	return 0;
}

