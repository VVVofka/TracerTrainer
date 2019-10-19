#if !defined(AFX_ORDERS_H__0C1FE0AB_1FF0_4FC8_AE19_2558D2CC782E__INCLUDED_)
#define AFX_ORDERS_H__0C1FE0AB_1FF0_4FC8_AE19_2558D2CC782E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"
#include "Order.h"

class COrders  
{
public:
	COrders();
	virtual ~COrders();

  int Count(){return ords.Count;};
  int LastN(){return ords.Count - 1;};
  int CloseLast(){return Close(LastN());};
  int Close(int n){return ords.p[n].Close(n);};

	int OpenSell(double price, double SL=0);
	int OpenBuy(double price, double SL=0);

private:
  TVector<COrder> ords;

};

#endif // !defined(AFX_ORDERS_H__0C1FE0AB_1FF0_4FC8_AE19_2558D2CC782E__INCLUDED_)
