#if !defined(AFX_OPTIAG_H__DC15CE0D_1A6B_4301_BECF_75AECDE3EEF8__INCLUDED_)
#define AFX_OPTIAG_H__DC15CE0D_1A6B_4301_BECF_75AECDE3EEF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Opti.h"

class COptiAg : public COpti  
{
public:
	COptiAg();
	virtual ~COptiAg();

  void Create(CData* cdata, CALines* calines);

protected:
	virtual BOOL CheckForOpenLong(int j);
	virtual BOOL CheckForOpenShort(int j);
	virtual BOOL CheckForCloseLong(int j);
	virtual BOOL CheckForCloseShort(int j);

  int prevprog;
  int preprevprog;
  double prevres;
  double preprevres;
  BOOL LastLoss();
};

#endif // !defined(AFX_OPTIAG_H__DC15CE0D_1A6B_4301_BECF_75AECDE3EEF8__INCLUDED_)
