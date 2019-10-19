#include "stdafx.h"
#include "FilterLP.h"

CFilterLP::CFilterLP()
{	Size = 0;}
CFilterLP::~CFilterLP()
{}///////////////////////////////////////////////////////////////////////
void CFilterLP::Create(int size, double* koefs)
{	koef = koefs;
	Size = size;
}///////////////////////////////////////////////////////////////////////
void CFilterLP::Create(CFiltersKoef* fltr_koef , int T_1)
{	koef = fltr_koef->koef(T_1);
	Size = fltr_koef->size(T_1);
}///////////////////////////////////////////////////////////////////////
void CFilterLP::Create(CFilterKoefsDel* fltr_koef , int Delay)
{	koef = fltr_koef->koef(Delay);
	Size = fltr_koef->size(Delay);
}///////////////////////////////////////////////////////////////////////
double CFilterLP::Resp(double* inp)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += inp[-j] * koef[j];
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
double CFilterLP::Resp(RateInfo* rate)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += rate[-j].close * koef[j];
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
double CFilterLP::RespH(RateInfo* rate)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += rate[-j].high * koef[j];
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
double CFilterLP::RespL(RateInfo* rate)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += rate[-j].low * koef[j];
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
double CFilterLP::RespCHL(RateInfo* rate)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += koef[j] * (rate[-j].close + rate[-j].high + rate[-j].low) / 3;
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
double CFilterLP::RespCCHL(RateInfo* rate)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += koef[j] * (2*rate[-j].close + rate[-j].high + rate[-j].low) / 4;
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
double CFilterLP::RespOHLC(RateInfo* rate)	//отклик для одной точки(inp-новейший)
{ double ret=0;
	for(int j=0; j<Size; j++)
		ret += koef[j] * (rate[-j].close + rate[-j].high + rate[-j].low +  + rate[-j].open) / 4;
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
