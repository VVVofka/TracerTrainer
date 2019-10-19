#if !defined(AFX_INFO_H__CD63CD1E_D10A_4FDA_B53A_1D46DCF77BD2__INCLUDED_)
#define AFX_INFO_H__CD63CD1E_D10A_4FDA_B53A_1D46DCF77BD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Info.h : header file
//
#include "TrainerDoc.h"
#include "DSP.h"

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog

class CInfo : public CDialog
{
// Construction
public:
	void SetDoc(CTrainerDoc* pDoc);
	CInfo(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CInfo)
	enum { IDD = IDD_DIALOG_INFO };
	CString	m_Info;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInfo)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INFO_H__CD63CD1E_D10A_4FDA_B53A_1D46DCF77BD2__INCLUDED_)
