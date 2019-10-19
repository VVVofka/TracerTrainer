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

class CALine  
{
public:
	CALine();
	virtual ~CALine();
	int Run(
  					CFiltersKoef* f_ks,
						int const bars, 
						RateInfo* Rate,				//bars-1 - новейший
						double* Res,					//отклик
						double const Lev,			//номинальный уровень отклонения
						int const Sglazh			      //период сглаживания
            );
	int Run(
  					CFiltersKoef* f_ks,
						int const bars,
						int const countedbars,
						int* tprev,
						RateInfo* Rate,				//bars-1 - новейший
						double* Res,					//отклик
						double const Lev,			//номинальный уровень отклонения
						int const Sglazh			      //период сглаживания
            );
	int RunMom(
  					CFiltersKoef* f_ks,
						CFiltersKoef* f_ks_mom,
						int const bars, 
						RateInfo* Rate,				//bars-1 - новейший
						double* Res,					//отклик
						double const Lev,			//номинальный уровень отклонения
						int const Sglazh			      //период сглаживания
            );
	double Run1(
  					CFiltersKoef* f_ks,
						int const bars, 
						RateInfo* Rate,				//bars-1 - новейший
						double const Lev,			//номинальный уровень отклонения
						int* t0								//предварительное значение Т
						);
  int Smoothing(                 // Сглаживаем 
					  CFiltersKoef* f_ks,
					  int const bars, 
						int const j0,
					  double* Res,				//отклик
					  int const Sglazh			    //период сглаживания
            );

private:
	CFiltersKoef* fks;
  double Lev;
	int defT(int t, RateInfo* rt);		//определяем новую(оптимальную) чвстоту среза фильтра
	double GetParrot(int t, RateInfo* rt);
	void SetParrot();
	int tparrot;
	double* koefparrot;
	int sizeparrot;
	RateInfo* Rate0;	//для проверки невыхода за границу
};
#endif // !defined(AFX_ALINE_H__87BBD3B7_624E_4410_8AB8_54F4E6078794__INCLUDED_)
