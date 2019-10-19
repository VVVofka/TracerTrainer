#if !defined(AFX_OPTIONS_H__03D37EC0_BB56_4C23_8101_9E6D5B3C23ED__INCLUDED_)
#define AFX_OPTIONS_H__03D37EC0_BB56_4C23_8101_9E6D5B3C23ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Options.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// COptions dialog

class COptions : public CDialog
{
// Construction
public:
	COptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptions)
	enum { IDD = IDD_OPTIONS };
	CListBox	m_ListBar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptions)
	afx_msg void OnBtnOptionsTest();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONS_H__03D37EC0_BB56_4C23_8101_9E6D5B3C23ED__INCLUDED_)
