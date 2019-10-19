#if !defined(AFX_ORDER_H__DBF5DCC1_2AE7_40EE_9A29_9B54BDC16599__INCLUDED_)
#define AFX_ORDER_H__DBF5DCC1_2AE7_40EE_9A29_9B54BDC16599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COrder  
{
public:
	COrder();
	virtual ~COrder();

  void OpenBuy(int j, time_t dt, double price);
  void OpenSell(int j, time_t dt, double price);
  void CloseBuy(int j, time_t dt, double price);
  void CloseSell(int j, time_t dt, double price);

  BOOL IsSell() {return TypeSell;};
  BOOL IsBuy()  {return TypeBuy; };
	BOOL IsClosed();
	BOOL IsOpen();

	double Bal();     //итоговый баланс
	void Clear();

	time_t DTOpen;    //врем€ открыти€
	time_t DTClose;   //врем€ закрыти€
	double PriceOpen; //цена открыти€
	double PriceClose;//цена закрыти€
  int BarBeg;       //є бара открыти€
  int BarEnd;       //є бара закрыти€
	BOOL TypeSell;
	BOOL TypeBuy;

protected:
};

#endif // !defined(AFX_ORDER_H__DBF5DCC1_2AE7_40EE_9A29_9B54BDC16599__INCLUDED_)
