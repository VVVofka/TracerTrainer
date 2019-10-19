// ������ DSP ����� � ������������� ����������� Lev,
// �� ��������� t(����������).
// ���������� ������� � ��������.
// ���� ������� ����� StDev(Open,Close) �� ��������� t(����������).
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
					RateInfo* Rate,				//���������!!!
					int const cnt,        //�������� � �������
					int* tprev,
					double const Lev			//����������� ������� ����������
          );
  double Out(int n){return out.p[n];};
  double OutBars(int nbars){return out.p[nbars - 2*fks->maxT];};
  int RecCnt(){return out.Count;};

private:
	CFiltersKoef* fks = nullptr;
	double Lev = 0.;
	int defT(int t, RateInfo* rt);		//���������� �����(�����������) ������� ����� �������
	double GetParrot(int t, RateInfo* rt);
	void SetParrot();
	int tparrot = 0;
	double* koefparrot = nullptr;
	int sizeparrot = 0;
	RateInfo* Rate0 = nullptr;	//��� �������� �������� �� �������
  TVector<double> out;  	//������
};
#endif // !defined(AFX_ALINE_H__87BBD3B7_624E_4410_8AB8_54F4E6078794__INCLUDED_)
