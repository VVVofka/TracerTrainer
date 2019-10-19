#include "stdafx.h"
#include "Tracer.h"
#include "Opti.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
COpti::COpti()
{data= NULL;
 lns = NULL;
}
COpti::~COpti()
{}////////////////////////////////////////////////////////////////////////////////////////
void COpti::Create(CData* cdata, CALines* calines)
{
  data = cdata;
  lns = calines;
  ords.Create(lns->RecCnt());
}////////////////////////////////////////////////////////////////////////////////////////
double COpti::Run()
{ 
  int cnt = lns->RecCnt() - 1;
  for(int j=0; j < cnt; j++)
    OneDay(j);
  if(!ords.IsClosed())
    ords.Close(cnt, data->dt(cnt), close(cnt));
  return ords.Avg();
}////////////////////////////////////////////////////////////////////////////////////////
void COpti::OneDay(int j)
{ 
  time_t dt = data->dt(j);
  double C = close(j);

    //---- Check close ------
  if(!ords.IsClosed())
    if(CheckForClose(j))
     ords.Close(j, dt, C);
  
    //---- Check open ------
  if(ords.IsClosed())
  { if(CheckForOpenLong(j))
      ords.OpenLong(j, dt, C);
    else if(CheckForOpenShort(j))
      ords.OpenShort(j, dt, C);
  }
}////////////////////////////////////////////////////////////////////////////////////////
//////////// C L O S E /////////////////////////////////////////////////////////////////////////
BOOL COpti::CheckForClose(int j)
{ BOOL ret = FALSE;
  if(ords.IsLong())
    ret = CheckForCloseLong(j);
  else if(ords.IsShort())
    ret = CheckForCloseShort(j);
  return ret;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COpti::CheckForCloseLong(int j)
{ double C = close(j);
  double line = lns->GetVal(0, j);
  if(C > line)
    return TRUE;
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COpti::CheckForCloseShort(int j)
{ double C = close(j);
  double line = lns->GetVal(0, j);
  if(C < line)
    return TRUE;
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
/////////// O P E N /////////////////////////////////////////////////////////////////////////////
BOOL COpti::CheckForOpenLong(int j)
{ double C = close(j);
  double line = lns->GetVal(0, j);
  if(C < line)
    return TRUE;
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COpti::CheckForOpenShort(int j)
{ double C = close(j);
  double line = lns->GetVal(0, j);
  if(C > line)
    return TRUE;
  return FALSE;
}////////////////////////////////////////////////////////////////////////////////////////
double COpti::close(int bar)
{ double c = data->close(bar + lns->BegPoint());
  return c;
}////////////////////////////////////////////////////////////////////////////////////////
void COpti::Dump()
{  ords.Dump();
}////////////////////////////////////////////////////////////////////////////////////////

