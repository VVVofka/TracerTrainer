#include "stdafx.h"
#include "Tracer.h"
#include "OptiAg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
COptiAg::COptiAg()
{ 
  prevprog=preprevprog=0;
  preprevres = prevres = 0;
}
COptiAg::~COptiAg()
{}////////////////////////////////////////////////////////////////////////////////////////
void COptiAg::Create(CData* cdata, CALines* calines)
{ COpti::Create(cdata, calines);
  prevprog=preprevprog=0;
  preprevres = prevres = 0;
  data = cdata;
  lns = calines;
  ords.Create(lns->RecCnt());
}////////////////////////////////////////////////////////////////////////////////////////
/////////// O P E N /////////////////////////////////////////////////////////////////////////////
BOOL COptiAg::CheckForOpenLong(int j) //волатильность
{ double C = close(j);
  double line = lns->GetVal(0, j);
  BOOL cond = (C < line);
  BOOL lastloss = LastLoss();
  if((!lastloss && cond) || (lastloss && !cond))
  { preprevprog = prevprog;
    prevprog = cond;
    return TRUE;
  }
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COptiAg::CheckForOpenShort(int j) //волатильность
{ double C = close(j);
  double line = lns->GetVal(0, j);
  BOOL cond = (C > line);
  BOOL lastloss = LastLoss();
  if((!lastloss && cond) || (lastloss && !cond))
  { preprevprog = prevprog;
    prevprog = cond;
    return TRUE;
  }
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
//////////// C L O S E ////////////////////////////////////////////////////////////////////////////
BOOL COptiAg::CheckForCloseLong(int j) //волатильность
{ double C = close(j);
  double line = lns->GetVal(0, j);
  BOOL cond = (C > line);
  if(cond)
  { preprevres = prevres;
    int CurOrd = ords.Count() - 1;
    if(prevprog == 1)
      prevres = ords.orders[CurOrd].PriceClose - ords.orders[CurOrd].PriceOpen;
    else if(prevprog == -1)
      prevres = ords.orders[CurOrd].PriceOpen - ords.orders[CurOrd].PriceClose;
    return TRUE;
  }
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COptiAg::CheckForCloseShort(int j) //волатильность
{ double C = close(j);
  double line = lns->GetVal(0, j);
  BOOL cond = (C < line);
  if(cond)
  { preprevres = prevres;
    int CurOrd = ords.Count() - 1;
    if(prevprog == 1)
      prevres = ords.orders[CurOrd].PriceClose - ords.orders[CurOrd].PriceOpen;
    else if(prevprog == -1)
      prevres = ords.orders[CurOrd].PriceOpen - ords.orders[CurOrd].PriceClose;
    return TRUE;
  }
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COptiAg::LastLoss()
{ 
  return (prevres > 0);
}////////////////////////////////////////////////////////////////////////////////////////
