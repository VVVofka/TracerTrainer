#if !defined(AFX_OPTIMIZER_H__B9418088_05F4_4592_A653_614601FBC910__INCLUDED_)
#define AFX_OPTIMIZER_H__B9418088_05F4_4592_A653_614601FBC910__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Opti.h"

#include "Trace.h"
extern CTrace trace;

// Optimizer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptimizer dialog

class COptimizer : public CDialog
{
// Construction
public:
	COptimizer(CWnd* pParent = NULL);   // standard constructor
  void Create(COpti* p_opti);

  // Dialog Data
	//{{AFX_DATA(COptimizer)
	enum { IDD = IDD_OPTIMAZER };
	CStatic	m_OptiRes;
	double	m_Res;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptimizer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  COpti* popti;

	// Generated message map functions
	//{{AFX_MSG(COptimizer)
	afx_msg void OnOptiRun();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIMIZER_H__B9418088_05F4_4592_A653_614601FBC910__INCLUDED_)
