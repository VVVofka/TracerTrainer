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

class CALine  
{
public:
	CALine();
	virtual ~CALine();
	int Run(
  					CFiltersKoef* f_ks,
						int const bars, 
						RateInfo* Rate,				//bars-1 - ��������
						double* Res,					//������
						double const Lev,			//����������� ������� ����������
						int const Sglazh			      //������ �����������
            );
	int Run(
  					CFiltersKoef* f_ks,
						int const bars,
						int const countedbars,
						int* tprev,
						RateInfo* Rate,				//bars-1 - ��������
						double* Res,					//������
						double const Lev,			//����������� ������� ����������
						int const Sglazh			      //������ �����������
            );
	int RunMom(
  					CFiltersKoef* f_ks,
						CFiltersKoef* f_ks_mom,
						int const bars, 
						RateInfo* Rate,				//bars-1 - ��������
						double* Res,					//������
						double const Lev,			//����������� ������� ����������
						int const Sglazh			      //������ �����������
            );
	double Run1(
  					CFiltersKoef* f_ks,
						int const bars, 
						RateInfo* Rate,				//bars-1 - ��������
						double const Lev,			//����������� ������� ����������
						int* t0								//��������������� �������� �
						);
  int Smoothing(                 // ���������� 
					  CFiltersKoef* f_ks,
					  int const bars, 
						int const j0,
					  double* Res,				//������
					  int const Sglazh			    //������ �����������
            );

private:
	CFiltersKoef* fks;
  double Lev;
	int defT(int t, RateInfo* rt);		//���������� �����(�����������) ������� ����� �������
	double GetParrot(int t, RateInfo* rt);
	void SetParrot();
	int tparrot;
	double* koefparrot;
	int sizeparrot;
	RateInfo* Rate0;	//��� �������� �������� �� �������
};
#endif // !defined(AFX_ALINE_H__87BBD3B7_624E_4410_8AB8_54F4E6078794__INCLUDED_)
