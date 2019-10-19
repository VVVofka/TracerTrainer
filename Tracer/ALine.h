// Строим DSP линию с фиксированным отклонением Lev,
// на интервале t(переменный).
// Отклонение задаётся в попугаях.
// Один попугай равен StDev(Open,Close) на интервале t(переменный).
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_ALINE_H__87BBD3B7_624E_4410_8AB8_54F4E6078794__INCLUDED_)
#define AFX_ALINE_H__87BBD3B7_624E_4410_8AB8_54F4E6078794__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSP.h"
#include "FiltersKoef.h"
#include "Vector.h"

class CALine  
{
public:
	CALine();
	virtual ~CALine();
	int Run(
  				CFiltersKoef* f_ks,
					RateInfo* Rate,				//начальный!!!
					int const cnt,        //отсчётов в отклике
					int* tprev,
					double const Lev			//номинальный уровень отклонения
          );
  double Out(int n){return out.p[n];};
  double OutBars(int nbars){return out.p[nbars - 2*fks->maxT];};
  int RecCnt(){return out.Count;};

private:
	CFiltersKoef* fks = nullptr;
	double Lev = 0.;
	int defT(int t, RateInfo* rt);		//определяем новую(оптимальную) чвстоту среза фильтра
	double GetParrot(int t, RateInfo* rt);
	void SetParrot();
	int tparrot = 0;
	double* koefparrot = nullptr;
	int sizeparrot = 0;
	RateInfo* Rate0 = nullptr;	//для проверки невыхода за границу
  TVector<double> out;  	//отклик
};
#endif // !defined(AFX_ALINE_H__87BBD3B7_624E_4410_8AB8_54F4E6078794__INCLUDED_)
