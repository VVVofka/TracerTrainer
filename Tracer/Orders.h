#if !defined(AFX_ORDERS_H__5C1D67C9_9C01_42BD_9CAE_A22A1813EEFD__INCLUDED_)
#define AFX_ORDERS_H__5C1D67C9_9C01_42BD_9CAE_A22A1813EEFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Order.h"
#include "Vector.h"
#include <afxtempl.h>

class COrders  
{
public:
	COrders();
	virtual ~COrders();

	void Create(int count);
  void Dump();

	void OpenLong (int j, time_t dt, double price);
	void OpenShort(int j, time_t dt, double price);
	void Close(int j, time_t dt, double price);

  BOOL IsClosed();
	BOOL IsOpen();
	BOOL IsLong();
	BOOL IsShort();

  int Count(){return curOrd+1;};
  COrder* GetOrder(int bar);

  double Bal(); //итоговый баланс
  double Avg(); //средний выйгрыш


  CArray<COrder, COrder&> orders;
private:
  int curOrd; //текущий ордер
};

#endif // !defined(AFX_ORDERS_H__5C1D67C9_9C01_42BD_9CAE_A22A1813EEFD__INCLUDED_)
