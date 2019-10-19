// Options.cpp : implementation file
//

#include "stdafx.h"
#include "Tracer.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptions dialog


COptions::COptions(CWnd* pParent /*=NULL*/)
	: CDialog(COptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptions)
	DDX_Control(pDX, IDC_LIST_BAR, m_ListBar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	//{{AFX_MSG_MAP(COptions)
	ON_BN_CLICKED(IDC_BTN_OPTIONS_TEST, OnBtnOptionsTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptions message handlers
void COptions::OnBtnOptionsTest() 
{
	CString s;
//	int item = m_ListBar.GetCaretIndex();
	int item = m_ListBar.GetCurSel();
	m_ListBar.SetCurSel(item+1);
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COptions::OnInitDialog() 
{	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_ListBar.AddString("Candle");
	m_ListBar.AddString("Column");
	m_ListBar.AddString("Grafic");
CString s = AfxGetApp()->GetProfileString("Options", "ViewBar", "Candle");
	m_ListBar.SelectString(0,s);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}////////////////////////////////////////////////////////////////////////////////////////
void COptions::OnOK() 
{	// TODO: Add extra validation here

	CString s;
	int item = m_ListBar.GetCurSel();
	m_ListBar.GetText(item, s);
  AfxGetApp()->WriteProfileString("Options", "ViewBar", s);	
	
	CDialog::OnOK();
}////////////////////////////////////////////////////////////////////////////////////////
