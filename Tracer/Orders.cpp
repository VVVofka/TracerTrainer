#include "stdafx.h"
#include "Tracer.h"
#include "Orders.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#pragma warning(disable : 4996)
COrders::COrders()
{
  curOrd = -1;
}
COrders::~COrders()
{}////////////////////////////////////////////////////////////////////////////////////////
void COrders::Create(int count)
{ curOrd = -1;
  orders.SetSize(count);    //ords.Create(count); 
}////////////////////////////////////////////////////////////////////////////////////////
double COrders::Bal()
{ double sum=0;
  int cnt = Count();
  for(int j=0; j<cnt; j++)
    sum += orders[j].Bal();
  return sum;
}////////////////////////////////////////////////////////////////////////////////////////
double COrders::Avg()
{  return Bal() / Count();
}////////////////////////////////////////////////////////////////////////////////////////
void COrders::OpenLong(int j, time_t dt, double price)
{ //_ASSERTE(curOrd < ords.Count);
  orders[++curOrd].OpenBuy(j, dt, price);
}////////////////////////////////////////////////////////////////////////////////////////
void COrders::OpenShort(int j, time_t dt, double price)
{ //_ASSERTE(curOrd < ords.Count);
  orders[++curOrd].OpenSell(j, dt, price);
}////////////////////////////////////////////////////////////////////////////////////////
void COrders::Close(int j, time_t dt, double price)
{ if(curOrd < 0) 
    {AfxMessageBox("Нет открытых ордеров!"); return;}
  if(orders[curOrd].IsBuy())
    orders[curOrd].CloseBuy(j, dt, price);
  else if(orders[curOrd].IsSell())
    orders[curOrd].CloseSell(j, dt, price);
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COrders::IsClosed()
{ if(curOrd < 0) return TRUE;
  return orders[curOrd].IsClosed();
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COrders::IsOpen()
{ if(curOrd < 0) return FALSE;
  return orders[curOrd].IsOpen();
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COrders::IsLong()
{ //_ASSERTE(curOrd < ords.Count); 
  if(curOrd < 0) return FALSE;
  return orders[curOrd].IsBuy();
}////////////////////////////////////////////////////////////////////////////////////////
BOOL COrders::IsShort()
{ //_ASSERTE(curOrd < ords.Count);
  if(curOrd < 0) return FALSE;
  return orders[curOrd].IsSell();
}////////////////////////////////////////////////////////////////////////////////////////
COrder* COrders::GetOrder(int bar)
{ COrder* ret = &orders.GetAt(bar);
  return ret;
}////////////////////////////////////////////////////////////////////////////////////////
void COrders::Dump()
{ FILE* f=fopen("C:\\Tr\\Temp\\DumpOpti.csv", "w");
  fprintf(f, "Order;Beg;End;Open;Close;\n");
  for(int o=0; o<Count(); o++)
  { CString s;
    if(orders[o].IsBuy())
      s = "Long";
    else
      s = "Short";
    fprintf(f, "%d;%s;%d;%d;%g;%g;\n", o, (LPCSTR)s,
        orders[o].BarBeg, orders[o].BarEnd,
        orders[o].PriceOpen, orders[o].PriceClose);
  }
  fclose(f);
}////////////////////////////////////////////////////////////////////////////////////////

