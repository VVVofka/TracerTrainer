// Optimizer.cpp : implementation file
//

#include "stdafx.h"
//#include "Tracer.h"
#include "Optimizer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptimizer dialog


COptimizer::COptimizer(CWnd* pParent /*=NULL*/)
	: CDialog(COptimizer::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptimizer)
	m_Res = 0.0;
	//}}AFX_DATA_INIT
}


void COptimizer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptimizer)
	DDX_Control(pDX, IDC_RES_OPTI, m_OptiRes);
	DDX_Text(pDX, IDC_RES, m_Res);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptimizer, CDialog)
	//{{AFX_MSG_MAP(COptimizer)
	ON_BN_CLICKED(IDC_OPTI_RUN, OnOptiRun)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptimizer message handlers

void COptimizer::Create(COpti* p_opti)
{
  popti = p_opti;
}////////////////////////////////////////////////////////////////////////////////////////
void COptimizer::OnOptiRun() 
{
  double resopt = popti->Run();
  CString s;
  s.Format("%g", resopt);
  m_OptiRes.SetWindowText(s); 
}////////////////////////////////////////////////////////////////////////////////////////

