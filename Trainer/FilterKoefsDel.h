#pragma once

#include "DSP.h"
#include <STDIO.H>
#include "Vector.h"
#include <io.h>
#include <FCNTL.H>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

class CFilterKoefsDel
{
public:
	CFilterKoefsDel(int T,
							double k_Len = 1.75,
              int A_1 = 40,
							double dRiple = 0.08);
	CFilterKoefsDel();
	virtual ~CFilterKoefsDel();
	
	void Create(int T,
							double k_Len = 1.75,
              int A_1 = 40,
							double dRiple = 0.08);

	int size(int t){return vsize.p[t];};
	double* koef(int t);

	int _T;	//частота среза фильтра(24)
	double kLen;
	int A1;
	double Riple;

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
