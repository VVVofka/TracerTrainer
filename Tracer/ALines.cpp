#include "stdafx.h"
#include "ALines.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
CALines::CALines()
{
	fks.Create(MIN_T, MAX_T);
  tprev = 2 * MIN_T;
}
CALines::~CALines()
{}////////////////////////////////////////////////////////////////////////////////////////
int CALines::Create(RateInfo* rt, int bars, double line1, double line2, double line3, double line4)
{ int n=0;
  lns.Create(4);
	lns.p[n++].Run(&fks, rt, bars, &tprev, line1);
	lns.p[n++].Run(&fks, rt, bars, &tprev, line2);
	lns.p[n++].Run(&fks, rt, bars, &tprev, line3);
	lns.p[n  ].Run(&fks, rt, bars, &tprev, line4);
  return BegPoint();
}////////////////////////////////////////////////////////////////////////////////////////
double CALines::GetVal(int line, int bar)
{
  return lns.p[line].Out(bar);
}////////////////////////////////////////////////////////////////////////////////////////

