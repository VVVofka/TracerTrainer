#if !defined(AFX_OPTI_H__095FF5E4_5E57_4861_8685_BD9E4CE3F81B__INCLUDED_)
#define AFX_OPTI_H__095FF5E4_5E57_4861_8685_BD9E4CE3F81B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSP.h"
#include "ALines.h"
#include "Data.h"
#include "Orders.h"
#include "Order.h"

class COpti  
{
public:
	COpti();
	virtual ~COpti();

  void Create(CData* cdata, CALines* calines);
	virtual double Run();
	virtual void OneDay(int j);
  void Dump();

  COrders ords;

private:

protected:
	virtual BOOL CheckForClose(int j);
	virtual BOOL CheckForOpenLong(int j);
	virtual BOOL CheckForOpenShort(int j);
	virtual BOOL CheckForCloseLong(int j);
	virtual BOOL CheckForCloseShort(int j);
  
  double close(int bar);
  CData* data;
  CALines* lns;
};

#endif // !defined(AFX_OPTI_H__095FF5E4_5E57_4861_8685_BD9E4CE3F81B__INCLUDED_)
