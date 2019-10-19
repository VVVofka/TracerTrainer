#include "stdafx.h"
#include "Coord.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CCoord::CCoord()
{	kx = ky = 1;
}
CCoord::~CCoord()
{}////////////////////////////////////////////////////////////////////////////////////////
void CCoord::SetXY(	long  XMin, long XMax,
										double YMin, double YMax)
{	xmin = XMin;	xmax = XMax;
	ymin = YMin;	ymax = YMax;
	kx = (double)(rc.right - rc.left)/(double)(xmax - xmin);
	ky = (rc.bottom - rc.top)/(ymax - ymin);
}
/////////////////////////////////////////////////////////////////////////////////
