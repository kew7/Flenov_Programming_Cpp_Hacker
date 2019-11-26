// TestMFCDoc.h : interface of the CTestMFCDoc class
//


#pragma once

class CTestMFCDoc : public CDocument
{
protected: // create from serialization only
	CTestMFCDoc();
	DECLARE_DYNCREATE(CTestMFCDoc)

// Attributes
public:

// Operations
public:

// Overrides
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CTestMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};


