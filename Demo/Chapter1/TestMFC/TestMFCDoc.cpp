// TestMFCDoc.cpp : implementation of the CTestMFCDoc class
//

#include "stdafx.h"
#include "TestMFC.h"

#include "TestMFCDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMFCDoc

IMPLEMENT_DYNCREATE(CTestMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestMFCDoc, CDocument)
END_MESSAGE_MAP()


// CTestMFCDoc construction/destruction

CTestMFCDoc::CTestMFCDoc()
{
	// TODO: add one-time construction code here

}

CTestMFCDoc::~CTestMFCDoc()
{
}

BOOL CTestMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CTestMFCDoc serialization

void CTestMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CTestMFCDoc diagnostics

#ifdef _DEBUG
void CTestMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestMFCDoc commands
