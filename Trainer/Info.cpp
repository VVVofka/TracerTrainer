// Info.cpp : implementation file
//

#include "stdafx.h"
#include "Trainer.h"
#include "Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInfo dialog


CInfo::CInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInfo)
	m_Info = _T("");
	//}}AFX_DATA_INIT
}


void CInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInfo)
	DDX_Text(pDX, IDC_INFO, m_Info);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInfo, CDialog)
	//{{AFX_MSG_MAP(CInfo)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInfo message handlers
#define DT_FORMAT "%d.%m.%Y  %H:%M"
void CInfo::SetDoc(CTrainerDoc *pDoc)
{ 
	CString s1, s2;
	CString fname(pDoc->GetPathName());
	int count = (int)pDoc->bchart.GetThrowCount();
	int digits = pDoc->bchart.Digits();
	CTime DTCreate = pDoc->bchart.timesign();
	CTime DTSync(/*DTCreate.GetTime() + */pDoc->bchart.last_sync().GetTime());
	s1.Format("Файл: %s\r\nВсего записей: %d\r\nРазрядов: %d\r\nСоздан: %s\r\nПоследняя модификация: %s",
		fname, count, digits, DTCreate.Format(DT_FORMAT), DTSync.Format(DT_FORMAT));
	RateInfo* rt;
	rt = pDoc->bchart.GetThrow(0);
	CTime DTbar0(rt->ctm);
	double Openbar0 = rt->open;

	rt = pDoc->bchart.GetThrow(count-1);
	CTime DTbarLast(rt->ctm);
	double CloseBarLast = rt->close;
	CString sformat("\r\nПервый отсчёт: %s\t=\t%.");
	CString dig;
	dig.Format("%d", digits);
	sformat += dig + "f\r\nПоследний отсчёт: %s\t=\t%.";
	sformat += dig + "f";
	s2.Format(sformat,
		DTbar0.Format(DT_FORMAT), Openbar0, DTbarLast.Format(DT_FORMAT), CloseBarLast);
	m_Info =  _T(s1 + s2);
}
