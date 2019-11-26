// DaclControl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Aclapi.h"


int _tmain(int argc, _TCHAR* argv[])
{
	PACL pDACL = NULL;
	PSECURITY_DESCRIPTOR pSD = NULL;

	// Get file security info
	if (GetNamedSecurityInfo(L"C:\\\\Temp\\test.txt", SE_FILE_OBJECT,
		DACL_SECURITY_INFORMATION, NULL, NULL, &pDACL, NULL,
		&pSD) != ERROR_SUCCESS) 
	{
		printf("Get security information error");
		return 0;
	}

	if (pDACL == NULL)
	{
		printf("ACL list is empty");
		return 0;
	}

	// Get ACL info
	ACL_SIZE_INFORMATION aclInfo;
	if (!GetAclInformation(pDACL, &aclInfo, sizeof(aclInfo), 
		AclSizeInformation))
	{
		printf("Can't get ACL info");
		return 0;
	}

	// Search for SID of Everyone account
	DWORD sidLength = 0;
	DWORD sidLengthDomain = 0;
	SID_NAME_USE sidType;
	LookupAccountName(NULL, L"Гость", NULL, &sidLength, NULL, &sidLengthDomain, &sidType);

	PSID sidValue = (PSID)new BYTE[sidLength];
	LPTSTR wszDomainName = new WCHAR[sidLengthDomain];

	if (!LookupAccountName(NULL, L"Гость", sidValue, &sidLength, wszDomainName, &sidLengthDomain, &sidType))
	{
		printf("Account do not found");
		return 0;
	}

	// Initialize new ACL
	DWORD cbAcl = aclInfo.AclBytesInUse + sizeof(ACCESS_ALLOWED_ACE) + GetLengthSid(sidValue);
 	PACL pNewDACL = NULL;

	pNewDACL = (ACL*)LocalAlloc(LPTR, cbAcl);
	if (!pNewDACL)
	{
		printf("Can't allocate memory");
		return 0;
	}

	if (!InitializeAcl(pNewDACL, cbAcl, ACL_REVISION))
	{
		printf("Can't initialize new DACL");
		return 0;
	}

	// Fill new ACL with existing data
	for (DWORD i = 0; i < aclInfo.AceCount; i++)
	{
		void *ace;
		if (!GetAce(pDACL, i, &ace))
		{
			printf("Can't get ACE");
			return 0;
		}

		if (!AddAce(pNewDACL, 2, MAXWORD, ace, ((ACCESS_ALLOWED_ACE *) ace)->Header.AceSize))
		{
			printf("Add ACE error");
			return 0;
		}
	}

 
	if (!AddAccessAllowedAce(pNewDACL, 2, GENERIC_ALL, sidValue))
	{
		printf("AddAccessAllowedAce error");
		return 0;
	}

	// Инициализируем новый дескриптор
	PSECURITY_DESCRIPTOR pNewSD = PSECURITY_DESCRIPTOR(LocalAlloc(LPTR, SECURITY_DESCRIPTOR_MIN_LENGTH));
	if (!InitializeSecurityDescriptor(pNewSD, SECURITY_DESCRIPTOR_REVISION))
	{
		printf("InitializeSecurityDescriptor error");
		return 0;
	}
	
	// Устанавливаем дескриптору новый ACL список
	if (!SetSecurityDescriptorDacl(pNewSD, TRUE, pNewDACL, FALSE))
	{
		printf("InitializeSecurityDescriptor error");
		return 0;
	}

	// Устанавливаем дескриптор файлу 
	if (!SetFileSecurity(L"C:\\\\Temp\\test.txt", DACL_SECURITY_INFORMATION, pNewSD))
	{
		printf("InitializeSecurityDescriptor error");
		return 0;
	}

	printf("It's all right");
	return 0;
}

