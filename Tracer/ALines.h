#if !defined(AFX_ALINES_H__55260B16_B35C_4E5A_8857_20DE6C79389B__INCLUDED_)
#define AFX_ALINES_H__55260B16_B35C_4E5A_8857_20DE6C79389B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"
#include "ALine.h"
#include "DSP.h"
#include "FiltersKoef.h"

#define MAX_T 299 
#define MIN_T 5

class CALines  
{
public:
	double GetVal(int line, int bar);
	CALines();
	virtual ~CALines();

  int Create(RateInfo* rt, int bars, double line1, double line2, double line3, double line4);
  int BegPoint(){return 2*MAX_T;};
  double Val(int index, int n){return lns.p[index].Out(n);};
  double ValBars(int index, int n){return lns.p[index].OutBars(n);};
  int Count(){return lns.Count;};
  int RecCnt(){return lns.p[0].RecCnt();};

private:
	CFiltersKoef fks;
  TVector<CALine> lns;
  int tprev;
	TVector<double> vln;
};

#endif // !defined(AFX_ALINES_H__55260B16_B35C_4E5A_8857_20DE6C79389B__INCLUDED_)
