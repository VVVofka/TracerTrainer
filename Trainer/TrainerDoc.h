// TrainerDoc.h : interface of the CTrainerDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAINERDOC_H__E5F3E201_72A0_4C83_A7BD_1D93E7E07FBB__INCLUDED_)
#define AFX_TRAINERDOC_H__E5F3E201_72A0_4C83_A7BD_1D93E7E07FBB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BarChart.h"
#include <float.h>
#include <math.h>
#include <minmax.h>
#include "DSP.h"
#include "FiltersKoef.h"
#include "ALine.h"
#include "Order.h"
#include "Orders.h"

#define   strSection  ("Options")

enum EMode
{
  AfterReset,
  ShowVisible,
  ShowInVisible
};

class CTrainerDoc : public CDocument
{
protected: // create from serialization only
	CTrainerDoc();
	DECLARE_DYNCREATE(CTrainerDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrainerDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	COrders ords;
  EMode mode;
	double* GetALine(int N, int J);
  CBarChart bchart;
  char fname[255];
  int Bal;
  int Cnt;
  int LastRes;
  int BarsVisible;
  int BarsInvisible;
	int Bars(){return BarsVisible + BarsInvisible;};
	int Bars1(){return BarsVisible + BarsInvisible + 1;};
	int kDigit(){return (int)pow(10, (double)bchart.Digits());};
	double SL;	//Stop Loss
  CString LastFile;
	CTime HST_StartDT;
	int SATL;
	int FATL;
	int BarStop;
	double kAutoSL;
	double AutoSL;
//	double AvgSL;	//среднее отклонение
	double LevelStop;
	void Reset();
	int OrderSell(double Stop_Loss=0);
	int OrderBuy(double Stop_Loss=0);
	virtual ~CTrainerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	double GetStDevMaxOtkl(int len=56);
  CFiltersKoef filterkoefs;

// Generated message map functions
protected:
	//{{AFX_MSG(CTrainerDoc)
	afx_msg void OnHome();
	afx_msg void OnEnd();
	afx_msg void OnPgdn();
	afx_msg void OnPgup();
	afx_msg void OnPrevBar();
	afx_msg void OnNextBar();
	afx_msg void OnFileNew();
	afx_msg void OnOrderBuy();
	afx_msg void OnOrderSell();
	afx_msg void OnNavigRnd();
	afx_msg void OnOrderClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTime Navigation(int dn, int n = -1);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAINERDOC_H__E5F3E201_72A0_4C83_A7BD_1D93E7E07FBB__INCLUDED_)
