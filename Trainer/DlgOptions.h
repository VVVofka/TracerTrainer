#if !defined(AFX_DLGOPTIONS_H__7E09CA3A_978F_4E96_8161_7119200B3FCE__INCLUDED_)
#define AFX_DLGOPTIONS_H__7E09CA3A_978F_4E96_8161_7119200B3FCE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOptions.h : header file
//
#define   strSection  ("Options")

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog

class CDlgOptions : public CDialog
{
// Construction
public:
	CDlgOptions(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgOptions)
	enum { IDD = IDD_DIALOG_OPTIONS };
	int		m_HiddenBars;
	int		m_VisibleBars;
	BOOL	m_VolVisible;
	CTime	m_HST_StartDT;
	double	m_autoSL;
	int		m_FATL;
	int		m_SATL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOptions)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOptions)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOPTIONS_H__7E09CA3A_978F_4E96_8161_7119200B3FCE__INCLUDED_)
