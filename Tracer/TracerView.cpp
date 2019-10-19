#include "stdafx.h"
#include "Tracer.h"

#include "TracerDoc.h"
#include "TracerView.h"
#include "Options.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CStatusBar* pStatBar;

#define VIEW_MODE_CANDLE 0
#define VIEW_MODE_COLUMN 1
#define VIEW_MODE_GRAFIC 2
/////////////////////////////////////////////////////////////////////////////
// CTracerView
IMPLEMENT_DYNCREATE(CTracerView, CView)

BEGIN_MESSAGE_MAP(CTracerView, CView)
	//{{AFX_MSG_MAP(CTracerView)
	ON_WM_SIZE()
	ON_COMMAND(ID_ZOOM_UP, OnZoomUp)
	ON_COMMAND(ID_ZOOM_DN, OnZoomDn)
	ON_COMMAND(ID_MOVE_LEFT, OnMoveLeft)
	ON_COMMAND(ID_MOVE_RIGHT, OnMoveRight)
	ON_COMMAND(ID_JUMP_LEFT, OnJumpLeft)
	ON_COMMAND(ID_JUMP_RIGHT, OnJumpRight)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_JUMP_END, OnJumpEnd)
	ON_COMMAND(ID_TST, OnTst)
	ON_COMMAND(ID_OPTIONS, OnOptions)
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTracerView construction/destruction
CTracerView::CTracerView()
{
  BarsVisible = 90;
	CString sViewBarMode =  AfxGetApp()->GetProfileString("Options", "ViewBar", "Candle");
	if(sViewBarMode == "Candle") 
		ViewBarMode = VIEW_MODE_CANDLE;
	else if(sViewBarMode == "Column")
		ViewBarMode = VIEW_MODE_COLUMN;
	else if(sViewBarMode == "Grafic")
		ViewBarMode = VIEW_MODE_GRAFIC;
	else
		_ASSERTE(0);
}
CTracerView::~CTracerView()
{}////////////////////////////////////////////////////////////////////////////////////////
// CTracerView drawing
void CTracerView::OnDraw(CDC* pDC)
{	CTracerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
  ReDraw();
}/////////////////////////////////////////////////////////////////////////////
// CTracerView diagnostics
#ifdef _DEBUG
void CTracerView::AssertValid() const
{	CView::AssertValid();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::Dump(CDumpContext& dc) const
{	CView::Dump(dc);
}////////////////////////////////////////////////////////////////////////////////////////
CTracerDoc* CTracerView::GetDocument() // non-debug version is inline
{ ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTracerDoc)));
	return (CTracerDoc*)m_pDocument;
}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CTracerView message handlers
void CTracerView::Clear()
{	RECT rc;
	CView::GetClientRect(&rc);
	CView::GetDC()->FillSolidRect(&rc, COLOR_BACK); //Clear screen
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnSize(UINT nType, int cx, int cy) 
{	CView::OnSize(nType, cx, cy);
	if(nType != SIZE_MINIMIZED)
  { crdChart.rc.top = 0;
	  crdChart.rc.bottom = cy;
	  crdChart.rc.left = 0;
	  crdChart.rc.right = cx;
  }
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::ReDraw()
{	Clear();
  int end = trace.LastPos;
  if (end <= 0) return;
  int start = end - BarsVisible;
  DefMaxMin(start, end);
  DrawBars(start, end);
  int n=0;
  DrawALines(start, end, n++, ALINE0_COLOR);
  DrawALines(start, end, n++, ALINE1_COLOR);
  DrawALines(start, end, n++, ALINE2_COLOR);
  DrawALines(start, end, n  , ALINE3_COLOR);
  DrawOpti(start, end);
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::DrawALines(int start, int end, int NLine, COLORREF color)
{	CDC* pDC = CView::GetDC();
	CPen pen(0, WIDTH_ALINE, color);
  pDC->SelectObject(&pen);
  int final = min(end, trace.Count());
  for(int j=start; j<final; j++)
  { double res = trace.alines.GetVal(NLine, j);
    int x = crdChart.xc(j);
		if(j!=start)
			pDC->LineTo(x, crdChart.yc(res));
		else
			pDC->MoveTo(x, crdChart.yc(res));
  }
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::DefMaxMin(int start, int end)
{ double minv = DBL_MAX;
  double maxv = -minv;
	double low, high;
  int final = min(end, trace.Count());
  for(int j=start; j<final; j++)
  { for(int a=0; a<trace.alines.Count(); a++)  
    { double x = trace.alines.GetVal(a, j);
      if(x < minv)  minv = x;
      if(x > maxv)  maxv = x;
    }
		if(ViewBarMode == VIEW_MODE_CANDLE || ViewBarMode == VIEW_MODE_COLUMN)
		{	low = trace.low(j);
			high = trace.high(j);
		}else
			low = high = trace.close(j);
    if(low < minv)      minv = low;
    if(high > maxv)     maxv = high;
  }
  double rangebar = maxv - minv;
	double DnBorder = minv - ZAZOR_DN * rangebar;
	double UpBorder = maxv + ZAZOR_UP * rangebar;
  crdChart.SetXY(start, end, DnBorder, UpBorder); 
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnZoomUp() 
{	int bv =  (int)(0.5 + BarsVisible * 1.25);
	int allcnt = trace.Count();
	if(bv > allcnt)
		trace.LastPos = BarsVisible = allcnt;
	else
	{	BarsVisible = bv;
		if(bv > trace.LastPos)	
			trace.LastPos = bv;
	}
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnZoomDn() 
{	
	BarsVisible = (int)(0.5 + BarsVisible / 1.25);
  if(BarsVisible < 20) BarsVisible = 20;
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnMoveLeft() 
{	if(trace.LastPos-BarsVisible <= 0) return ;
  trace.LastPos--;
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnMoveRight() 
{
	if(trace.Count() < trace.LastPos * 1.0) return;
	trace.LastPos++;
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnJumpLeft() 
{	int step = BarsVisible - 2;
  if(trace.LastPos-BarsVisible <= step) 
    trace.LastPos = BarsVisible;
  else
    trace.LastPos -= step;
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnJumpRight() 
{	
	if(trace.Count() < trace.LastPos * 1.0) return;
	trace.LastPos += BarsVisible - 2;
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
BOOL CTracerView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{ double speed;
  switch(nFlags)
  { case MK_CONTROL:
      speed = (BarsVisible * 0.5) / 120.0;
      break;
    case MK_SHIFT:
      speed = 1.0/120.0;
      break;
    default:
      speed = 5.0 / 120.0;
  }
  int step = (int)(0.5 + zDelta*speed);
	int allcnt = trace.Count();
	if(step>0 &&  allcnt< trace.LastPos * 1.0)
		goto exit_OnMouseWheel;
  if(trace.LastPos-BarsVisible <= -step) 
    trace.LastPos = BarsVisible;
  else
	  trace.LastPos += step;
  ReDraw();
exit_OnMouseWheel:
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnJumpEnd() 
{	trace.LastPos = trace.Count()+1;
  ReDraw();
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::DrawOpti(int start, int end)
{	CDC* pDC = CView::GetDC();
  CPen penlong,penshort;
  penlong.CreatePen(0, WIDTH_OPTI, OPTI_LONG_COLOR);
  penshort.CreatePen(0, WIDTH_OPTI, OPTI_SHORT_COLOR);
  int final = min(end, trace.Count());
  for(int o=0; o<trace.opti.ords.Count(); o++)
  { COrder* ord = trace.opti.ords.GetOrder(o);
    int beg = ord->BarBeg;
    int end = ord->BarEnd;
    double prOpen = ord->PriceOpen;
    double prClose = ord->PriceClose;
    BOOL blong = ord->TypeBuy;
    int x0 = crdChart.xc(beg);
    int y0 = crdChart.yc(prOpen);
    int x1 = crdChart.xc(end);
    int y1 = crdChart.yc(prClose);
    if (x1<0 || x0>crdChart.rc.right)       continue;
    if(blong)			pDC->SelectObject(&penlong);
    else				pDC->SelectObject(&penshort);
		pDC->MoveTo(x0, y0);
		pDC->LineTo(x1, y1);
  }   // for(int o=0; o<trace.opti.ords.Count(); o++)
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnTst() 
{ int end = trace.LastPos;
  if (end <= 0) return;
  int start = end - BarsVisible;
  CDC* pDC = CView::GetDC();
	CPen penlong (0, WIDTH_OPTI, OPTI_SHORT_COLOR);
	CPen penshort(0, WIDTH_OPTI,OPTI_LONG_COLOR );
  int final = min(end, trace.Count());
  for(int o=0; o<trace.opti.ords.Count(); o++)
  { COrder* ord = trace.opti.ords.GetOrder(o);
    int beg = ord->BarBeg;
    int end = ord->BarEnd;
    double prOpen = ord->PriceOpen;
    double prClose = ord->PriceClose;
    BOOL blong = ord->IsBuy();
    int x0 = crdChart.xc(beg);
    int y0 = crdChart.yc(prOpen);
    int x1 = crdChart.xc(end);
    int y1 = crdChart.yc(prClose);
    if (x1<0 || x0>crdChart.rc.right)       continue;
    if(blong)
      pDC->SelectObject(&penlong);
    else
      pDC->SelectObject(&penshort);
		pDC->MoveTo(x0, y0);
		pDC->LineTo(x1, y1);
  }   // for(int o=0; o<trace.opti.ords.Count(); o++)
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::OnOptions() 
{	COptions options;
	if(options.DoModal()==IDOK)
	{	CString sViewBarMode =  AfxGetApp()->GetProfileString("Options", "ViewBar", "Candle");
		if(sViewBarMode == "Candle") 
			ViewBarMode = VIEW_MODE_CANDLE;
		else if(sViewBarMode == "Column")
			ViewBarMode = VIEW_MODE_COLUMN;
		else if(sViewBarMode == "Grafic")
			ViewBarMode = VIEW_MODE_GRAFIC;
		else
			_ASSERTE(0);
		ReDraw();
	}
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::DrawBars(int start, int end)
{ if(trace.Count() == 0) return ;
	switch(ViewBarMode)
	{	case VIEW_MODE_CANDLE:
			DrawBarsCandle(start, end);
			break;
		case VIEW_MODE_COLUMN:
			DrawBarsColumn(start, end);
			break;
		case VIEW_MODE_GRAFIC:
			DrawBarsGrafic(start, end);
			break;
		default:
			_ASSERTE(0);
	}
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerView::DrawBarsCandle(int start, int end)
{ CDC* pDC = CView::GetDC();
  int bars = end - start;
  int widthbar = (int)(K_WIDTH_BAR * crdChart.rc.Width() / bars);
  if(widthbar & 1)  widthbar++;
  int widthbar2 = widthbar / 2;
	CBrush brushup, brushdn;
	brushup.CreateSolidBrush(COLOR_BAR_BODY_UP);
	brushdn.CreateSolidBrush(COLOR_BAR_BODY_DN);
  CPen penBar(0,1,COLOR_BAR);
  int final = min(end, trace.Count());
  for(int j=start; j<final; j++)
  { double O = trace.open(j);
    double H = trace.high(j);
    double L = trace.low(j);
    double C = trace.close(j);
    int co=crdChart.yc(O);
    int cc=crdChart.yc(C);
	  pDC->SelectObject(&penBar);
    int x = crdChart.xc(j);
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
}////////////// end DrawBarsCandle //////////////////////////////////////////////////////////////////////////
void CTracerView::DrawBarsColumn(int start, int end)
{ CDC* pDC = CView::GetDC();
  int bars = end - start;
  int widthbar = (int)(K_WIDTH_BAR * crdChart.rc.Width() / bars);
  if(widthbar & 1)  widthbar++;
  int widthbar2 = widthbar / 2;
	CPen penup, pendn;
	penup.CreatePen(0,1,COLOR_BAR_COLUMN_UP);
	pendn.CreatePen(0,1,COLOR_BAR_COLUMN_DN);
  int final = min(end, trace.Count());
  for(int j=start; j<final; j++)
  { double O = trace.open(j);
    double H = trace.high(j);
    double L = trace.low(j);
    double C = trace.close(j);
    int co=crdChart.yc(O);
    int cc=crdChart.yc(C);
    int x = crdChart.xc(j);
    if(co>cc) //Up
			pDC->SelectObject(&penup);
    else
      pDC->SelectObject(&pendn);
    pDC->MoveTo(x , crdChart.yc(L)); //High - Low (¬ерт.палка)
    pDC->LineTo(x , crdChart.yc(H)); //High - Low (¬ерт.палка)
    pDC->MoveTo(x-widthbar2 , co); //(полка открыти€)
    pDC->LineTo(x , co); //(полка открыти€)
    pDC->MoveTo(x+widthbar2 , cc); //(полка закрыти€)
    pDC->LineTo(x , cc); //(полка закрыти€)
  }
}////////////////// end DrawBarsColumn //////////////////////////////////////////////////////////////////////
void CTracerView::DrawBarsGrafic(int start, int end)
{ CDC* pDC = CView::GetDC();
  int bars = end - start;
  CPen penBar(0,1,COLOR_BAR);
	pDC->SelectObject(&penBar);
  int final = min(end, trace.Count());
	double C = trace.close(start);
	int cc = crdChart.yc(C);
  int x =  crdChart.xc(start);
  pDC->MoveTo(x , cc); 
  for(int j=start+1; j<final; j++)
  { C = trace.close(j);
    cc=crdChart.yc(C);
    x = crdChart.xc(j);
    pDC->LineTo(x , cc); 
  }
}/////////////// end DrawBarsGrafic /////////////////////////////////////////////////////////////////////////
void CTracerView::OnMouseMove(UINT nFlags, CPoint point) {
	int x = crdChart.lxx(point.x);
	double y = crdChart.lyy(point.y);

	if(trace.rt) {
		double O = trace.open(x);
		double C = trace.close(x);
		double H = trace.high(x);
		double L = trace.low(x);
		double V = trace.vol(x);
		CTime D = trace.dt(x);
		CString s;
		s.Format("%d %0.4f %s\tO:%0.4f  H:%0.4f  L:%0.4f  C:%0.4f  V:%.6d",
			x, y, (LPCSTR)D.Format("%d.%m.%Y"), O, H, L, C, (int)V);
		StatBarText(s);
	}
	CView::OnMouseMove(nFlags, point);
} // //////////////////////////////////////////////////////////////////////////////////////
void CTracerView::StatBarText(CString str)
{  pStatBar->SetWindowText(str);
} // //////////////////////////////////////////////////////////////////////////////////////


