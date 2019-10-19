#if !defined(AFX_TRACERDOC_H__118F43C1_707E_4EF4_A66F_FFD062E7B98B__INCLUDED_)
#define AFX_TRACERDOC_H__118F43C1_707E_4EF4_A66F_FFD062E7B98B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Data.h"

#include "Trace.h"
extern CTRace trace;

#include "Opti.h"

class CTracerDoc : public CDocument
{
protected: // create from serialization only
	CTracerDoc();
	DECLARE_DYNCREATE(CTracerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTracerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	double ALineFast;
	double ALineSlow;
	virtual ~CTracerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTracerDoc)
	afx_msg void OnOpti();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACERDOC_H__118F43C1_707E_4EF4_A66F_FFD062E7B98B__INCLUDED_)
