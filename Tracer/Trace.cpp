#include "stdafx.h"
#include "Tracer.h"
#include "Trace.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CTRace::CTRace()
{ BegPoint = 0;
  LastPos = 0;
  rt = NULL;
}
CTRace::~CTRace()
{}////////////////////////////////////////////////////////////////////////////////////////
int CTRace::LoadData(CString FileName)
{ int ret = data.Load(FileName);
  return ret;
}////////////////////////////////////////////////////////////////////////////////////////
int CTRace::LoadALines(double line_fast, double line_slow)
{
  double dline = (line_slow - line_fast) / 3.0;
  BegPoint = alines.Create( data.vret.p, data.vret.Count,
                            line_fast,        line_fast+dline, 
                            line_slow-dline,  line_slow);
  LastPos = Count();
  rt = data.vret.p + BegPoint;
  opti.Create(&data, &alines);
  return BegPoint;
}////////////////////////////////////////////////////////////////////////////////////////
int CTRace::Count()
{ 
  return data.vret.Count - BegPoint;
}////////////////////////////////////////////////////////////////////////////////////////
double CTRace::OptiRun()
{ double ret = opti.Run();
//  opti.Dump();
  return ret;
}////////////////////////////////////////////////////////////////////////////////////////

