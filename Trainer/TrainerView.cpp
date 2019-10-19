// TrainerView.cpp : implementation of the CTrainerView class
//

#include "stdafx.h"
#include "Trainer.h"

#include "TrainerDoc.h"
#include "TrainerView.h"
#include <minmax.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrainerView
IMPLEMENT_DYNCREATE(CTrainerView, CView)

BEGIN_MESSAGE_MAP(CTrainerView, CView)
	//{{AFX_MSG_MAP(CTrainerView)
	ON_COMMAND(RESET_STAT, OnResetStat)
	ON_COMMAND(MENU_OPTIONS, OnMenuOptions)
	ON_COMMAND(MENU_VOLUME_VISIBLE, OnVolumeVisible)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(MENU_FILE_INFO, OnFileInfo)
	ON_COMMAND(MENU_VIEW_BAR_MODE1, OnViewBarMode1)
	ON_COMMAND(MENU_VIEW_BAR_MODE2, OnViewBarMode2)
	ON_COMMAND(MENU_VIEW_BAR_MODE3, OnViewBarMode3)
	ON_COMMAND(MENU_VIEW_ORDERS, OnViewOrders)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrainerView construction/destruction

CTrainerView::CTrainerView()
{
  CWinApp* pApp = AfxGetApp();
  VolVisible = pApp->GetProfileInt(strSection, "VolumeVisible", 0);
	newload = TRUE;
	bShowLastPrice = TRUE;
	viewBarMode = Candle;
	viewOrder = TRUE;
}
CTrainerView::~CTrainerView()
{
  CWinApp* pApp = AfxGetApp();
  pApp->WriteProfileInt(strSection, "VolumeVisible", VolVisible);
}
BOOL CTrainerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}
/////////////////////////////////////////////////////////////////////////////
// CTrainerView drawing
void CTrainerView::OnDraw(CDC* pDC)
{
	int ret =0;
	if(newload)
	{	
		ShowVisibleBars();
		StatBarText("New Loads");
		newload = FALSE;
	}
  else
    ReDraw();
}
/////////////////////////////////////////////////////////////////////////////
void CTrainerView::ShowVisibleBars()
{ CDC* pDC = CView::GetDC();
	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
  double min = DBL_MAX;
  double max = -min;
  double maxv = max;
	if(pDoc->bchart.v.p==NULL) return;
  for(int j=0; j<pDoc->BarsVisible; j++)
  { double L = pDoc->bchart.GetLow(j);
    if(L < min)      min = L;
    double H = pDoc->bchart.GetHigh(j);
    if(H > max)      max = H;
    double V = pDoc->bchart.GetVol(j);
    if(V > maxv)      maxv = V;
  }
	RECT rc;
	CView::GetClientRect(&rc);
	pDC->FillSolidRect(&rc, COLOR_BACK); //Clear screen

  /* Рисуем объёмы */
  if(VolVisible)
  { 
		crdVolDn.SetXY(0, pDoc->Bars1(),  0, maxv);
    CPen penVol(0, 5, COLOR_VOL);
    pDC->SelectObject(&penVol);
    int v0 = crdVolDn.yc(0);
    for(int j=0; j<pDoc->BarsVisible; j++)
    { int x = crdVolDn.xc(j+1);
      double V = pDoc->bchart.GetVol(j);
      int vc = crdVolDn.yc(V);
      pDC->MoveTo(x, v0);
      pDC->LineTo(x, vc);
    }
    penVol.DeleteObject();
  }

	double price = pDoc->bchart.GetClose(pDoc->BarsVisible-1);	//цена закрытия последнего бара
	double DnBorder = min(price - pDoc->AutoSL - ZAZOR_DN*(max-min), min-ZAZOR_DN*(max-min));
	double UpBorder = max(price + pDoc->AutoSL + ZAZOR_UP*(max-min), max+ZAZOR_UP*(max-min));
  crdChart.SetXY(0, pDoc->Bars1(), DnBorder, UpBorder); 

  /* Рисуем две линии Auto Stop loss и центральную*/
  if(pDoc->kAutoSL > 0)
  { CPen pen(PS_DASH, 1, COLOR_SL);
    pDC->SelectObject(&pen);
    int sl_y = crdChart.yc(price + pDoc->AutoSL);
    pDC->MoveTo(crdChart.rc.left, sl_y);
    pDC->LineTo(crdChart.rc.right, sl_y);
    sl_y = crdChart.yc(price - pDoc->AutoSL);
    pDC->MoveTo(crdChart.rc.left, sl_y);
    pDC->LineTo(crdChart.rc.right, sl_y);
	}
	if(bShowLastPrice)
  { CPen pen(PS_DASHDOT, 1, COLOR_SL);
    pDC->SelectObject(&pen);
    double price = pDoc->bchart.GetClose(pDoc->BarsVisible-1);
    int sl_y = crdChart.yc(price);
		pDC->MoveTo(crdChart.rc.left, sl_y);
    pDC->LineTo(crdChart.rc.right, sl_y);
	}
  /* Рисуем бары */ 
  int widthbar = (int)(0.6 * crdChart.rc.Width() / pDoc->Bars1());
  if(widthbar & 1)  widthbar++;
  int widthbar2 = widthbar / 2;
	CBrush brushup, brushdn;
	brushup.CreateSolidBrush(COLOR_BAR_BODY_UP);
	brushdn.CreateSolidBrush(COLOR_BAR_BODY_DN);
  CPen penBar(0,1,COLOR_BAR);
  for(int j=0; j<pDoc->BarsVisible; j++)
  { int x = crdChart.xc(j+1);
    double O = pDoc->bchart.GetOpen(j);
    double H = pDoc->bchart.GetHigh(j);
    double L = pDoc->bchart.GetLow(j);
    double C = pDoc->bchart.GetClose(j);
    int co=crdChart.yc(O);
    int cc=crdChart.yc(C);
	  pDC->SelectObject(&penBar);
    pDC->MoveTo(x , crdChart.yc(L)); //High - Low (Shadow)
    pDC->LineTo(x , crdChart.yc(H)); //High - Low (Shadow)
    if(co!=cc)    //Body
    { if(co>cc) //Up
				pDC->SelectObject(&brushup);
      else
        pDC->SelectObject(&brushdn);
      pDC->Rectangle(x-widthbar2, co, x+widthbar2, cc);
    }else //dodj
    { pDC->SelectObject(&penBar);
			pDC->MoveTo(x-widthbar2, co);
      pDC->LineTo(x+widthbar2, co);
    }	
  }
  DrawALines(pDoc->BarsVisible); /* Рисуем ALine */ 
}/////////////////////////////////////////////////////////////////////////////
void CTrainerView::DrawALines(int cnt)
{	if(true)
	{	
		DrawALine(1, COLOR_ALINE1, cnt);
		DrawALine(2, COLOR_ALINE2, cnt);
		DrawALine(3, COLOR_ALINE3, cnt);
		DrawALine(4, COLOR_ALINE4, cnt);
	}
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::DrawALine(int N, COLORREF color, int cnt)
{	CDC* pDC = CView::GetDC();
	CPen pen(0, WIDTH_ALINE, color);
  pDC->SelectObject(&pen);
	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	double* res =  pDoc->GetALine(N, 0);
  for(int j=0; j<cnt; j++)
  { int x = crdChart.xc(j+1);
		double a = res[j];
		if(j)
			pDC->LineTo(x, crdChart.yc(a));
		else
			pDC->MoveTo(x, crdChart.yc(a));
  }
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::ShowInVisibleBars()
{	CDC* pDC = CView::GetDC();
	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	double min = DBL_MAX;
  double max = -min;
  double maxv = max;
  for(int j=0; j<pDoc->Bars(); j++)
  { double L = pDoc->bchart.GetLow(j);
    if(L < min)      min = L;
    double H = pDoc->bchart.GetHigh(j);
    if(H > max)      max = H;
    double V = pDoc->bchart.GetVol(j);
    if(V > maxv)      maxv = V;
  }
  RECT rc;
	CView::GetClientRect(&rc);
	pDC->FillSolidRect(&rc, COLOR_BACK); //Clear screen

	double price = pDoc->bchart.GetClose(pDoc->BarsVisible-1);	//цена закрытия последнего видимого бара
	double DnBorder = min(price - pDoc->AutoSL - ZAZOR_DN*(max-min), min-ZAZOR_DN*(max-min));
	double UpBorder = max(price + pDoc->AutoSL + ZAZOR_UP*(max-min), max+ZAZOR_UP*(max-min));
  crdChart.SetXY(0, pDoc->Bars1(), DnBorder, UpBorder); 

  /* Рисуем объёмы */
  if(VolVisible)
  { 
		crdVolDn.SetXY(0, pDoc->Bars1(),  0, maxv);
    CPen penVol(0, 5, COLOR_VOL);
    pDC->SelectObject(&penVol);
    int v0 = crdVolDn.yc(0);
    for(int j=0; j<pDoc->Bars(); j++)
    { int x = crdVolDn.xc(j+1);
      double V = pDoc->bchart.GetVol(j);
      int vc = crdVolDn.yc(V);
      pDC->MoveTo(x, v0);
      pDC->LineTo(x, vc);
    }
    penVol.DeleteObject();
  }
  
  /* Рисуем линию Stop loss */
  if(pDoc->SL != 0)
  { CPen pen(0, 1, COLOR_SL);
    pDC->SelectObject(&pen);
    int sl_y = crdChart.yc(pDoc->SL);
    pDC->MoveTo(crdChart.rc.left, sl_y);
    pDC->LineTo(crdChart.rc.right, sl_y);
  }

	if(bShowLastPrice)
  { CPen pen(PS_DASHDOT, 1, COLOR_SL);
    pDC->SelectObject(&pen);
    
    int sl_y = crdChart.yc(price);
		pDC->MoveTo(crdChart.rc.left, sl_y);
    pDC->LineTo(crdChart.rc.right, sl_y);
	}
  /* Рисуем бары */ 
  int widthbar = (int)(0.6 * crdChart.rc.Width() / pDoc->Bars1());
  if(widthbar & 1)  widthbar++;
  int widthbar2 = widthbar / 2;
  CPen pen(0,1,COLOR_BAR);
  pDC->SelectObject(&pen);
  int j = 0;
  for(; j<pDoc->BarsVisible; j++)
  { int x = crdChart.xc(j+1);
    double O = pDoc->bchart.GetOpen(j);
    double H = pDoc->bchart.GetHigh(j);
    double L = pDoc->bchart.GetLow(j);
    double C = pDoc->bchart.GetClose(j);
    double V = pDoc->bchart.GetVol(j);
    int co = crdChart.yc(O);
    int cc = crdChart.yc(C);
    pDC->MoveTo(x, crdChart.yc(L)); //High - Low (Shadow)
    pDC->LineTo(x, crdChart.yc(H)); //High - Low (Shadow)
    if(co!=cc)    //Body
    { CBrush brush;
      if(co>cc) //Up
        brush.CreateSolidBrush(COLOR_BAR_BODY_UP);
      else
        brush.CreateSolidBrush(COLOR_BAR_BODY_DN);
      pDC->SelectObject(&brush);
      pDC->Rectangle(x-widthbar2, co, x+widthbar2, cc);
    }else //dodj
    { pDC->MoveTo(x-widthbar2, co);
      pDC->LineTo(x+widthbar2, co);
    }
  }
  pen.DeleteObject();
  CPen penh;
  penh.CreatePen(0, 1, COLOR_BAR_HIDDEN);
  pDC->SelectObject(&penh);
  for(; j<pDoc->Bars(); j++)
  { int x = crdChart.xc(j+1);
    double O = pDoc->bchart.GetOpen(j);
    double H = pDoc->bchart.GetHigh(j);
    double L = pDoc->bchart.GetLow(j);
    double C = pDoc->bchart.GetClose(j);
    int co = crdChart.yc(O);
    int cc = crdChart.yc(C);
    pDC->MoveTo(x , crdChart.yc(L)); //High - Low (Shadow)
    pDC->LineTo(x , crdChart.yc(H)); //High - Low (Shadow)
    if(co!=cc)    //Body
    { CBrush brush;
      if(co>cc) //Up
        brush.CreateSolidBrush(COLOR_BAR_BODY_UP);
      else
        brush.CreateSolidBrush(COLOR_BAR_BODY_DN);
      pDC->SelectObject(&brush);
      pDC->Rectangle(x-widthbar2, co, x+widthbar2, cc);
    }else //dodj
    { pDC->MoveTo(x-widthbar2, co);
      pDC->LineTo(x+widthbar2, co);
    }
  }
  CPen penres;
  if(pDoc->LastRes > 0)
  { pDC->SetTextColor(COLOR_WIN);
    penres.CreatePen(PS_DOT, 1, COLOR_WIN);
  }else
  { pDC->SetTextColor(COLOR_LOSS);
    penres.CreatePen(PS_DOT, 1, COLOR_LOSS);
  }
  CString s;
  s.Format("%d", pDoc->LastRes);
  pDC->TextOut(1,1,s);
  pDC->SelectObject(&penres);
//  double price = pDoc->bchart.GetClose(pDoc->BarsVisible-1);
  int x = crdChart.xc(pDoc->BarsVisible);
  int y = crdChart.yc(price);
  pDC->MoveTo(x, y);
  x = crdChart.xc(pDoc->BarStop + 1);
  y = crdChart.yc(pDoc->LevelStop);
  pDC->LineTo(x, y);
	DrawALines(pDoc->Bars());
}/////////////////////////////////////////////////////////////////////////////
// CTrainerView diagnostics
#ifdef _DEBUG
void CTrainerView::AssertValid() const
{	CView::AssertValid();}
void CTrainerView::Dump(CDumpContext& dc) const
{	CView::Dump(dc);}
CTrainerDoc* CTrainerView::GetDocument() // non-debug version is inline
{	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTrainerDoc)));
	return (CTrainerDoc*)m_pDocument;}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CTrainerView message handlers
void CTrainerView::OnResetStat() 
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
  pDoc->Reset();
  StatBarText("Reset statistic complete.");
}///////////////////////////////////////////////////////////////////////////
void CTrainerView::OnMenuOptions() 
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	CDlgOptions dlg;
  dlg.m_VisibleBars = pDoc->BarsVisible;
  dlg.m_HiddenBars = pDoc->BarsInvisible;
  dlg.m_VolVisible = VolVisible;
  if(dlg.DoModal() == IDOK)
  { pDoc->BarsVisible = dlg.m_VisibleBars;
    pDoc->BarsInvisible = dlg.m_HiddenBars;
    VolVisible = dlg.m_VolVisible;
		pDoc->HST_StartDT = dlg.m_HST_StartDT;
    pDoc->kAutoSL = dlg.m_autoSL;
    pDoc->FATL = dlg.m_FATL;
    pDoc->SATL = dlg.m_SATL;
    pDoc->OnOpenDocument(pDoc->GetPathName());
		StatBarText("New options");
    ReDraw();
  }
}//////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnVolumeVisible() 
{
  VolVisible = !VolVisible;
  ReDraw();
}//////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnLButtonDown(UINT nFlags, CPoint point) 
{ int res;
	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	if(pDoc->mode == ShowVisible)  
	{ CDC* pDC = CView::GetDC();
		CPen pen(0, 1, COLOR_SL);
		pDC->SelectObject(&pen);
  
		pDC->MoveTo(crdChart.rc.left, point.y);
		pDC->LineTo(crdChart.rc.right, point.y);

		pDoc->SL = crdChart.lyy(point.y);
		if(pDoc->SL < pDoc->bchart.GetClose(pDoc->BarsVisible-1))
			res = pDoc->OrderBuy(pDoc->SL);
		else if(pDoc->SL > pDoc->bchart.GetClose(pDoc->BarsVisible-1))
			res = pDoc->OrderSell(pDoc->SL);
		//OnUnHide();
	}//else if(pDoc->mode == ShowInVisible)
		//pDoc->NextBar();
	CView::OnLButtonDown(nFlags, point);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnSize(UINT nType, int cx, int cy) 
{	CView::OnSize(nType, cx, cy);
	
//	crdChart.rc.top = (int)(cy * K_VOL);
	crdChart.rc.top = 0;
	crdChart.rc.bottom = (int)(cy - (cy * K_VOL) - 1);
	crdChart.rc.left = 0;
	crdChart.rc.right = cx;

	crdVolDn.rc.top = crdChart.rc.bottom + 2;
	crdVolDn.rc.bottom = cy;
	crdVolDn.rc.left = 0;
	crdVolDn.rc.right = cx;
}//////////////////////////////////////////////////////////////////////////
int CTrainerView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
//	OnFileNew();
	return 0;
}//////////////////////////////////////////////////////////////////////////
void CTrainerView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	if(pDoc->GetPathName() != pDoc->LastFile && pDoc->LastFile.GetLength() != 0)
		pDoc->SetPathName(pDoc->LastFile, false);	
	CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}//////////////////////////////////////////////////////////////////////////
void CTrainerView::StatBarText(CString str)
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	if(pDoc->bchart.v.p==NULL) return;
	int res = pDoc->LastRes;
	int cnt = pDoc->Cnt;
	int bal = pDoc->Bal;
	double avg = 0;
	if(cnt) avg = (double)bal/cnt;
  CTime T = pDoc->bchart.GetDate(pDoc->Bars()-1);
  CString s, st = T.Format("%d %m %Y");
  s.Format("Balance:  %d, Count: %d,  Avg: %g,  Last result: %d\t%s\t%s",
						bal,cnt, avg, res, st, str);
  pStatBar->SetWindowText(s);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnRButtonDown(UINT nFlags, CPoint point) 
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
//	pDoc->NextBar();
	CView::OnRButtonDown(nFlags, point);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnFileInfo() 
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	CInfo dlg;
	dlg.SetDoc(pDoc);
	dlg.DoModal();
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::ReDraw()
{	CTrainerDoc* pDoc = GetDocument();	ASSERT_VALID(pDoc);
	if(pDoc->bchart.v.p==NULL) return;
	if(pDoc->mode == ShowVisible)
		ShowVisibleBars();
	else
		ShowInVisibleBars();
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{	OnDraw(CView::GetDC());
	StatBarText("");
}//////////////////////////////////////////////////////////////////////////
void CTrainerView::OnViewBarMode1() 
{	viewBarMode = Candle;
	OnDraw(CView::GetDC());
	StatBarText("Candle bars");
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnViewBarMode2() 
{	viewBarMode = Chart;
	OnDraw(CView::GetDC());
	StatBarText("Chart bars");
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnViewBarMode3() 
{	viewBarMode = Column;
	OnDraw(CView::GetDC());
	StatBarText("Column bars");
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerView::OnViewOrders() 
{	viewOrder = !viewOrder;
	OnDraw(CView::GetDC());
	StatBarText("Show orders");
}////////////////////////////////////////////////////////////////////////////////////////

