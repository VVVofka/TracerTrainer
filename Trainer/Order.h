#if !defined(AFX_ORDER_H__D076A8C8_DC5D_4268_9412_10DE8038B808__INCLUDED_)
#define AFX_ORDER_H__D076A8C8_DC5D_4268_9412_10DE8038B808__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum TypeOrder
{ 
  Buy     = 1,
  Sell    = 2
};

class COrder : protected CObject  
{
public:
	COrder();
	virtual ~COrder();

  int Open(TypeOrder type, double price, double SL);
	int Close(int n);
};

#endif // !defined(AFX_ORDER_H__D076A8C8_DC5D_4268_9412_10DE8038B808__INCLUDED_)
