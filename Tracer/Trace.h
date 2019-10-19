#if !defined(AFX_TRACE_H__D5117B76_874D_45D7_8B92_750EB555D790__INCLUDED_)
#define AFX_TRACE_H__D5117B76_874D_45D7_8B92_750EB555D790__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Data.h"
#include "ALines.h"
#include "Opti.h"
#include "OptiAg.h"
#include "DSP.h"

class CTRace 
{
public:
	double OptiRun();
	CTRace();
	virtual ~CTRace();

  int LoadData(CString FileName);
  int LoadALines(double line_fast, double line_slow);

	int Count();
  double open(int bar){return rt[bar].open;};
  double close(int bar){return rt[bar].close;};
  double high(int bar){return rt[bar].high;};
  double low(int bar){return rt[bar].low;};
  time_t dt(int bar){return rt[bar].ctm;};
  double vol(int bar){return rt[bar].vol;};

  CData data;
  CALines alines;

  int LastPos;
  //COpti opti;
  COptiAg opti;

  RateInfo* rt;   //ptr на рабочее начало данных
private:
  int BegPoint;
};

#endif // !defined(AFX_TRACE_H__D5117B76_874D_45D7_8B92_750EB555D790__INCLUDED_)
