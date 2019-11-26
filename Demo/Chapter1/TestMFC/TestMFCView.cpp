// TestMFCView.cpp : implementation of the CTestMFCView class
//

#include "stdafx.h"
#include "TestMFC.h"

#include "TestMFCDoc.h"
#include "TestMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestMFCView

IMPLEMENT_DYNCREATE(CTestMFCView, CView)

BEGIN_MESSAGE_MAP(CTestMFCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTestMFCView construction/destruction

CTestMFCView::CTestMFCView()
{
	// TODO: add construction code here

}

CTestMFCView::~CTestMFCView()
{
}

BOOL CTestMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTestMFCView drawing

void CTestMFCView::OnDraw(CDC* /*pDC*/)
{
	CTestMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CTestMFCView printing

BOOL CTestMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTestMFCView diagnostics

#ifdef _DEBUG
void CTestMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CTestMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestMFCDoc* CTestMFCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestMFCDoc)));
	return (CTestMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestMFCView message handlers
