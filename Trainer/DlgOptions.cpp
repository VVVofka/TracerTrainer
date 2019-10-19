// DlgOptions.cpp : implementation file
//

#include "stdafx.h"
#include "Trainer.h"
#include "DlgOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions dialog

CDlgOptions::CDlgOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOptions)
	m_HST_StartDT = 0;
	m_autoSL = 0.0;
	m_FATL = 0;
	m_SATL = 0;
	//}}AFX_DATA_INIT
  CWinApp* pApp = AfxGetApp();
	m_HiddenBars = pApp->GetProfileInt(strSection, "VolumeVisible", 90);
	m_VisibleBars = pApp->GetProfileInt(strSection, "VolumeVisible", 1);
  m_VolVisible = pApp->GetProfileInt(strSection, "VolumeVisible", 0);
	int yy=pApp->GetProfileInt(strSection, "HST_StartDT_Year", 2000);
	int mm=pApp->GetProfileInt(strSection, "HST_StartDT_Month", 1);
	int dd=pApp->GetProfileInt(strSection, "HST_StartDT_Day", 1);
	CTime t(yy,mm,dd,0,0,0);
	m_HST_StartDT = t;
  CString sAutoSL = pApp->GetProfileString(strSection, "Auto_SL", "0");
  m_autoSL = atof(sAutoSL);
  m_FATL = pApp->GetProfileInt(strSection, "FATL", 16);
  m_SATL = pApp->GetProfileInt(strSection, "SATL", 64);
}////////////////////////////////////////////////////////////////////////////////////////
void CDlgOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOptions)
	DDX_Text(pDX, IDC_HIDDEN_BARS, m_HiddenBars);
	DDV_MinMaxInt(pDX, m_HiddenBars, 1, 35);
	DDX_Text(pDX, IDC_VISIBLE_BARS, m_VisibleBars);
	DDV_MinMaxInt(pDX, m_VisibleBars, 36, 512);
	DDX_Check(pDX, IDC_VOL_VISIBLE, m_VolVisible);
	DDX_MonthCalCtrl(pDX, IDC_MONTHCALENDAR1, m_HST_StartDT);
	DDX_Text(pDX, IDC_AUTO_SL, m_autoSL);
	DDV_MinMaxDouble(pDX, m_autoSL, 0., 9.9);
	DDX_Text(pDX, IDC_FATL, m_FATL);
	DDV_MinMaxInt(pDX, m_FATL, 0, 300);
	DDX_Text(pDX, IDC_SATL, m_SATL);
	DDV_MinMaxInt(pDX, m_SATL, 7, 300);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOptions, CDialog)
	//{{AFX_MSG_MAP(CDlgOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOptions message handlers

void CDlgOptions::OnOK() 
{
	CDialog::OnOK();
  CWinApp* pApp = AfxGetApp();
  pApp->WriteProfileInt(strSection, "BarsVisible", m_VisibleBars);
  pApp->WriteProfileInt(strSection, "BarsHidden", m_HiddenBars);
  pApp->WriteProfileInt(strSection, "VolumeVisible", m_VolVisible);
  pApp->WriteProfileInt(strSection, "HST_StartDT_Year", m_HST_StartDT.GetYear());
  pApp->WriteProfileInt(strSection, "HST_StartDT_Month", m_HST_StartDT.GetMonth());
  pApp->WriteProfileInt(strSection, "HST_StartDT_Day", m_HST_StartDT.GetDay());
  CString s;  s.Format("%f", m_autoSL);
  pApp->WriteProfileString(strSection, "Auto_SL", s);
  pApp->WriteProfileInt(strSection, "FATL", m_FATL);
  pApp->WriteProfileInt(strSection, "SATL", m_SATL);
}
