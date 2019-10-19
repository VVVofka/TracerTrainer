// TrainerDoc.cpp : implementation of the CTrainerDoc class
//

#include "stdafx.h"
#include "Trainer.h"

#include "TrainerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrainerDoc

IMPLEMENT_DYNCREATE(CTrainerDoc, CDocument)

BEGIN_MESSAGE_MAP(CTrainerDoc, CDocument)
	//{{AFX_MSG_MAP(CTrainerDoc)
	ON_COMMAND(MENU_HOME, OnHome)
	ON_COMMAND(MENU_END, OnEnd)
	ON_COMMAND(MENU_PGDN, OnPgdn)
	ON_COMMAND(MENU_PGUP, OnPgup)
	ON_COMMAND(MENU_PREV_BAR, OnPrevBar)
	ON_COMMAND(MENU_NEXT_BAR, OnNextBar)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(OREDE_BUY, OnOrderBuy)
	ON_COMMAND(ORDER_SELL, OnOrderSell)
	ON_COMMAND(MENU_NAVIG_RND, OnNavigRnd)
	ON_COMMAND(ORDER_CLOSE, OnOrderClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CTrainerDoc construction/destruction
CTrainerDoc::CTrainerDoc()
{ CWinApp* pApp = AfxGetApp();
  Reset();
  LastFile = pApp->GetProfileString("Recent File List","File1","");
	Cnt = pApp->GetProfileInt("Last statistic", "Cnt", 0);
	Bal = pApp->GetProfileInt("Last statistic", "Bal", 0);
	LastRes = pApp->GetProfileInt("Last statistic", "LastRes", 0);
  BarsVisible = pApp->GetProfileInt(strSection, "BarsVisible", 94);
  BarsInvisible = pApp->GetProfileInt(strSection, "BarsHidden", 1);
	
	int yy=pApp->GetProfileInt(strSection, "HST_StartDT_Year", 2000);
	int mm=pApp->GetProfileInt(strSection, "HST_StartDT_Month", 1);
	int dd=pApp->GetProfileInt(strSection, "HST_StartDT_Day", 1);
	CTime t(yy,mm,dd,0,0,0);
	HST_StartDT = t;
  CString sAutoSL(pApp->GetProfileString(strSection, "Auto_SL", "0"));
  kAutoSL = atof(sAutoSL);
  BarStop = 0;

	bchart.Index0 = pApp->GetProfileInt(strSection, "bchart_Index0", 0);
  FATL = pApp->GetProfileInt(strSection, "FATL", 16);
  SATL = pApp->GetProfileInt(strSection, "SATL", 64);
  filterkoefs.Create(5,299);
}////////////////////////////////////////////////////////////////////////////////////////
CTrainerDoc::~CTrainerDoc()
{ CWinApp* pApp = AfxGetApp();
  pApp->WriteProfileInt("Last statistic", "Cnt", Cnt);
  pApp->WriteProfileInt("Last statistic", "Bal", Bal);
  pApp->WriteProfileInt("Last statistic", "LastRes", LastRes);
  pApp->WriteProfileInt(strSection, "BarsVisible", BarsVisible);
  pApp->WriteProfileInt(strSection, "BarsHidden", BarsInvisible);
  pApp->WriteProfileInt(strSection, "HST_StartDT_Year", HST_StartDT.GetYear());
  pApp->WriteProfileInt(strSection, "HST_StartDT_Month", HST_StartDT.GetMonth());
  pApp->WriteProfileInt(strSection, "HST_StartDT_Day", HST_StartDT.GetDay());
  pApp->WriteProfileInt(strSection, "bchart_Index0", bchart.Index0);
  CString s;  s.Format("%f", kAutoSL);
  pApp->WriteProfileString(strSection, "Auto_SL", s);
  pApp->WriteProfileInt(strSection, "FATL", FATL);
  pApp->WriteProfileInt(strSection, "SATL", SATL);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::Reset()
{	Cnt = Bal = LastRes = 0;
  SL = 0;
	srand((unsigned)time(NULL));
}////////////////////////////////////////////////////////////////////////////////////////
BOOL CTrainerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}/////////////////////////////////////////////////////////////////////////////
// CTrainerDoc serialization
void CTrainerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
  } 
}
/////////////////////////////////////////////////////////////////////////////
// CTrainerDoc diagnostics
#ifdef _DEBUG
void CTrainerDoc::AssertValid() const
{	CDocument::AssertValid();}
void CTrainerDoc::Dump(CDumpContext& dc) const
{	CDocument::Dump(dc);}
#endif //_DEBUG
/////////////////////////////////////////////////////////////////////////////
// CTrainerDoc commands
BOOL CTrainerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO: Add your specialized creation code here
  strcpy(fname, lpszPathName);
	int ret = bchart.LoadHST(fname, HST_StartDT);
  if (ret == 0) 
    return FALSE;
  if(kAutoSL > 0) 
    AutoSL = GetStDevMaxOtkl();
	return TRUE;
}/////////////////////////////////////////////////////////////////////////////
int CTrainerDoc::OrderSell(double Stop_Loss)
{ int j, start, finish;
  BarStop = 0;
  Cnt++;
  SL = 0;
  if(Stop_Loss > 0)
    SL = Stop_Loss;
  else if(kAutoSL > 0 && AutoSL > 0)
    SL = bchart.GetClose(BarsVisible-1) + AutoSL;
	start = (int)(kDigit() * bchart.GetClose(BarsVisible-1));
  if(SL != 0)
  { for(j=BarsVisible; j<Bars(); j++)
    { if(SL <= bchart.GetHigh(j))
      { if(SL < bchart.GetOpen(j))  //ãýï
          LevelStop = bchart.GetOpen(j);
        else
          LevelStop = SL;
        BarStop = j;
        finish = (int)(kDigit() * LevelStop + 0.5);
        goto Exit_OrderSell;
      }
    }
  }
  BarStop = Bars()-1;
  LevelStop = bchart.GetClose(BarStop);
  finish = (int)(kDigit() * LevelStop);
Exit_OrderSell:
	LastRes = start - finish;
	Bal += LastRes;
	return LastRes;
}/////////////////////////////////////////////////////////////////////////////
int CTrainerDoc::OrderBuy(double Stop_Loss)
{ int j, start, finish;
  BarStop = 0;
  Cnt++;
  SL = 0;
  if(Stop_Loss > 0)
    SL = Stop_Loss;
  else if(kAutoSL > 0 && AutoSL > 0)
    SL = bchart.GetClose(BarsVisible-1) - AutoSL;
	start = (int)(kDigit() * bchart.GetClose(BarsVisible-1));
  if(SL != 0)
  { for(j=BarsVisible; j<Bars(); j++)
    { if(SL >= bchart.GetLow(j))
      { if(SL > bchart.GetOpen(j))  //ãýï
          LevelStop = bchart.GetOpen(j);
        else
          LevelStop = SL;
        BarStop = j;
        finish = (int)(kDigit() * LevelStop + 0.5);
        goto Exit_OrderBuy;
      }
    }
  }
  BarStop = Bars()-1;
  LevelStop = bchart.GetClose(BarStop);
  finish = (int)(kDigit() * LevelStop);
Exit_OrderBuy:
	LastRes = finish - start;
	Bal += LastRes;
  return LastRes;
}/////////////////////////////////////////////////////////////////////////////
double CTrainerDoc::GetStDevMaxOtkl(int LenInt)
{ double cmd, avg = 0, sum = 0;
  for(int j=0; j<LenInt; j++)
  { int i = BarsVisible-j-1;
		double open = bchart.GetOpen(i);
		double close = bchart.GetClose(i);
		double high = bchart.GetHigh(i);
		double low = bchart.GetLow(i);
    if(open < close)  // Up
      avg += open - low;
    else
      avg += high - open;  
  }
  avg /= LenInt;
  
  for(int j=0; j<LenInt; j++)
  { int i = BarsVisible-j-1; 
		double open = bchart.GetOpen(i);
		double close = bchart.GetClose(i);
		double high = bchart.GetHigh(i);
		double low = bchart.GetLow(i);
    if(open < close)  // Up
      cmd = avg - (open - low);
    else
      cmd = avg - (high - open);
    sum += cmd * cmd;
  }
  return  avg + kAutoSL * sqrt(sum/LenInt);
}//+------------------------------------------------------------------+
#define MAX_T 299 
#define MIN_T 5
double* CTrainerDoc::GetALine(int N, int J)
{	static double nn[5]={0, 2, 3.5, 6, 9};
	static CFiltersKoef fks;
	if(fks.minT == 0) fks.Create(MIN_T, MAX_T);

	static TVector<double> vres;
	RateInfo* rate;
	rate = bchart.GetThrow(J);
	int bars = bchart.GetIndex() + Bars();
	int cntbars = bchart.GetIndex();
	vres.Create((int)bars);
	static int tprev = 20;
	static CALine aline;
	aline.Run(&fks, bars, cntbars, &tprev, rate, vres.p, nn[N], 0);
	return &vres.p[cntbars];
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnNavigRnd() 
{
	int ir = rand();
	if(ir & 0xF == 0)
	{ srand((unsigned)time(NULL));
		ir = rand();
	}
	ir = ir << 4;
	ir += (time(NULL) & 4);
	double r = 2 * ir / (double)((RAND_MAX << 5) -1);
	r *= bchart.Count() - Bars();
	Navigation(0, (int)r);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnHome() 
{	Navigation(0, 0);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnEnd() 
{	Navigation(0, (int)(bchart.Count() - Bars()) + 1);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnPgdn() 
{Navigation(Bars());
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnPgup() 
{Navigation(-Bars());
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnNextBar() 
{Navigation(BarsInvisible);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnPrevBar() 
{Navigation(-BarsInvisible);
}////////////////////////////////////////////////////////////////////////////////////////
CTime CTrainerDoc::Navigation(int dn, int n)
{	if(n >= 0)
		bchart.Index0 = n;
	else
		bchart.Index0 += dn;
	
	if(bchart.Index0 < 0)
		bchart.Index0 = 0;

	int BegLastScr = (int)(bchart.Count() - Bars()) + 1;
	if(bchart.Index0 > BegLastScr)
		bchart.Index0 = BegLastScr;
  
	if(kAutoSL > 0) 
    AutoSL = GetStDevMaxOtkl();
	
	UpdateAllViews(NULL);
	CTime ret = bchart.GetDate(BarsVisible-1);
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnFileNew() 
{	
  CString sd = GetPathName();
  mode = ShowVisible;
  if(sd == "")
    if(LastFile != "")
    { OnOpenDocument(LastFile);
      SetPathName(LastFile, false); 
    }
  UpdateAllViews(NULL);
}////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnOrderBuy() 
{	OrderBuy();
  UpdateAllViews(NULL);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnOrderSell() 
{	OrderSell();	
  UpdateAllViews(NULL);
}////////////////////////////////////////////////////////////////////////////////////////
void CTrainerDoc::OnOrderClose() 
{
	ords.CloseLast();
  UpdateAllViews(NULL);
}////////////////////////////////////////////////////////////////////////////////////////

