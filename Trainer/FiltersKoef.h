#if !defined(AFX_FILTERSKOEF_H__D1B3366E_AD61_425E_940F_A7DB5148A293__INCLUDED_)
#define AFX_FILTERSKOEF_H__D1B3366E_AD61_425E_940F_A7DB5148A293__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSP.h"
#include <STDIO.H>
#include "Vector.h"
#include <io.h>
#include <FCNTL.H>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

class CFiltersKoef  
{
public:
	CFiltersKoef(int min_T,
               int max_T,
               double k_Len = 1.75,
               int A_1 = 40,
							 double dRiple = 0.08,
               double kDelay = 0);
	CFiltersKoef();
	virtual ~CFiltersKoef();
	
	void Create(int min_T=8,
              int max_T=150,
							double k_Len = 1.75,
              int A_1 = 40,
							double dRiple = 0.08,
              double kDelay = 0);

	int size(int t){return vsize.p[t - minT];};
	double* koef(int t);

	int minT;	//min частота среза фильтра(10)
	int maxT;	//max частота среза фильтра(100)
	double kLen;
	int A1;
	double Riple;
	double kDelay;

	int CountAll;	//общее кол-во доступных фильтров

private:
	char FileName[255];
	TVector<int> vsize;
	TVector<int> vofs;
	TVector<double> vkoef;
	TVector<int>P1;
	TVector<int>D1;
	void load();
	void save();
};
#endif // !defined(AFX_FILTERSKOEF_H__D1B3366E_AD61_425E_940F_A7DB5148A293__INCLUDED_)
