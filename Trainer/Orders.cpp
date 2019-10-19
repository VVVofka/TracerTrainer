#include "stdafx.h"
#include "Trainer.h"
#include "Orders.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

COrders::COrders()
{
  ords.Create(0, 1024);
}
COrders::~COrders()
{}////////////////////////////////////////////////////////////////////////////////////////
int COrders::OpenBuy(double price, double SL)
{
  return ords.p[LastN()].Open(Buy, price, SL);
}////////////////////////////////////////////////////////////////////////////////////////
int COrders::OpenSell(double price, double SL)
{
  return ords.p[LastN()].Open(Sell, price, SL);
}////////////////////////////////////////////////////////////////////////////////////////

