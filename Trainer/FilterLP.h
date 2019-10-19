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

	int Size;	//����������� �������

	void Create(int size, double* koefs);
	void Create(CFiltersKoef* fltr_koef , int T_1);
	void Create(CFilterKoefsDel* fltr_koef , int Delay=0);

	double Resp(double* inp);	//������ ��� ����� �����(inp-��������)

	double Resp(RateInfo* rate);	//������ ��� ����� �����(inp-��������)
	double RespCHL(RateInfo* rate);	//������ ��� ����� �����(inp-��������)
	double RespCCHL(RateInfo* rate);	//������ ��� ����� �����(inp-��������)
	double RespOHLC(RateInfo* rate);	//������ ��� ����� �����(inp-��������)
	double RespH(RateInfo* rate);	//������ ��� ����� �����(inp-��������)
	double RespL(RateInfo* rate);	//������ ��� ����� �����(inp-��������)

private:
	double* koef;
};
#endif // !defined(AFX_FILTERLP_H__413AC5F7_09A1_41E7_A249_50A433569E39__INCLUDED_)
