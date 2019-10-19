#include "stdafx.h"
#include "Tracer.h"
#include "Order.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//#define ORDER_TRACE

COrder::COrder()
{
  Clear();
}
COrder::~COrder()
{}////////////////////////////////////////////////////////////////////////////////////////
void COrder::OpenBuy(int j, time_t dt, double price)
{ TypeBuy = TRUE;  TypeSell = FALSE;
  DTOpen = dt;
  PriceOpen = price;
  BarBeg = j;
#ifdef ORDER_TRACE
  _RPT2(0,"%d Open long: %g\n", j, price);
#endif
}////////////////////////////////////////////////////////////////////////////////////////
void COrder::OpenSell(int j, time_t dt, double price)
{ TypeSell = TRUE;  TypeBuy = FALSE;
  DTOpen = dt;
  PriceOpen = price;
  BarBeg = j;
#ifdef ORDER_TRACE
  _RPT2(0,"%d Open short: %g\n", j, price);
#endif
}////////////////////////////////////////////////////////////////////////////////////////
void COrder::CloseBuy(int j, time_t dt, double price)
{ DTClose = dt;
  PriceClose = price;
  BarEnd = j;
#ifdef ORDER_TRACE
  _RPT2(0,"%d Close long: %g\n", j, price);
#endif
}////////////////////////////////////////////////////////////////////////////////////////
void COrder::CloseSell(int j, time_t dt, double price)
{ DTClose = dt;
  PriceClose = price;
  BarEnd = j;
#ifdef ORDER_TRACE
  _RPT2(0,"%d Close short: %g\n", j, price);
#endif
}////////////////////////////////////////////////////////////////////////////////////////
void COrder::Clear()
{
  TypeSell = TypeBuy = FALSE;
  DTOpen = DTClose = 0;
  PriceOpen = PriceClose = 0;
}////////////////////////////////////////////////////////////////////////////////////////
double COrder::Bal()
{ if(TypeBuy) return PriceClose - PriceOpen;
  return PriceOpen - PriceClose;
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COrder::IsClosed()
{ return (PriceClose != 0);
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COrder::IsOpen()
{ return (PriceClose == 0);
}////////////////////////////////////////////////////////////////////////////////////////

