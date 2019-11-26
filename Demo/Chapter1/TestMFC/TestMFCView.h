// TestMFCView.h : interface of the CTestMFCView class
//


#pragma once


class CTestMFCView : public CView
{
protected: // create from serialization only
	CTestMFCView();
	DECLARE_DYNCREATE(CTestMFCView)

// Attributes
public:
	CTestMFCDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestMFCView.cpp
inline CTestMFCDoc* CTestMFCView::GetDocument() const
   { return reinterpret_cast<CTestMFCDoc*>(m_pDocument); }
#endif

