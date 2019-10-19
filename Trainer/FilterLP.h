#if !defined(AFX_FILTERLP_H__413AC5F7_09A1_41E7_A249_50A433569E39__INCLUDED_)
#define AFX_FILTERLP_H__413AC5F7_09A1_41E7_A249_50A433569E39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DSP.h"
#include "FiltersKoef.h"
#include "FilterKoefsDel.h"

//extern CFiltersKoef gFiltersKoef;

class CFilterLP  
{
public:
	CFilterLP();
	virtual ~CFilterLP();

	int Size;	//размерность фильтра

	void Create(int size, double* koefs);
	void Create(CFiltersKoef* fltr_koef , int T_1);
	void Create(CFilterKoefsDel* fltr_koef , int Delay=0);

	double Resp(double* inp);	//отклик для одной точки(inp-новейший)

	double Resp(RateInfo* rate);	//отклик для одной точки(inp-новейший)
	double RespCHL(RateInfo* rate);	//отклик для одной точки(inp-новейший)
	double RespCCHL(RateInfo* rate);	//отклик для одной точки(inp-новейший)
	double RespOHLC(RateInfo* rate);	//отклик для одной точки(inp-новейший)
	double RespH(RateInfo* rate);	//отклик для одной точки(inp-новейший)
	double RespL(RateInfo* rate);	//отклик для одной точки(inp-новейший)

private:
	double* koef;
};
#endif // !defined(AFX_FILTERLP_H__413AC5F7_09A1_41E7_A249_50A433569E39__INCLUDED_)
