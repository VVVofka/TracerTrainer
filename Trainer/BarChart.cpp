#include "stdafx.h"
#include "Trainer.h"
#include "BarChart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#pragma warning(push)
#pragma warning(disable:4996) 
#pragma warning(disable:26495) 

CBarChart::CBarChart()
{
  IndexBase = Index0 = 0;
}
CBarChart::~CBarChart()
{}////////////////////////////////////////////////////////////////////////////////
int CBarChart::LoadHST(char* fname)
{
	int ret=0;
	int f;
	f=_open(fname,_O_BINARY | _O_RDONLY);
	if(f==-1) return 0;
	__int64 lenfile = _lseeki64(f, 0, SEEK_END);
	_lseeki64(f, 0, SEEK_SET);
	_read(f, &hdr, sizeof(hdr));
	ret = ((int)lenfile - sizeof(hdr)) / sizeof(RateInfo);
	v.Create(ret);
	_read(f, v.p, (int)(sizeof(RateInfo)*ret));
	_close(f);
	return ret;
}///////////////////////////////////////////////////////////////////////////////
int CBarChart::LoadHST(char* fname, CTime Date_Start)
{
	int ret=LoadHST(fname);
	IndexBase = FindDT(Date_Start.GetTime());
	return IndexBase;
}///////////////////////////////////////////////////////////////////////////////
int CBarChart::FindDT(time_t t)
{
	if(v.p[0].ctm >= t)
		return 0;
	for(int j=0; j < v.Count; j++)
	{
		if(v.p[j].ctm >= t)
			return j;
	}
	return 0;
}////////////////////////////////////////////////////////////////////////////////////////
time_t CBarChart::GetDate(int Index)
{	time_t ret=v.p[IndexBase + Index0 + Index].ctm;
//	_RPT1(_CRT_WARN,"%s\n", ctime(&ret));
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
int CBarChart::Digits()
{	
	return hdr.digits;
}////////////////////////////////////////////////////////////////////////////////////////
CString CBarChart::Symbol()
{
	CString s(hdr.symbol);
	return s;
}////////////////////////////////////////////////////////////////////////////////////////
int CBarChart::Period()
{
	return hdr.period;
}////////////////////////////////////////////////////////////////////////////////////////
CTime CBarChart::timesign()	// временной отпечаток создания базы
{
	return hdr.timesign;
}////////////////////////////////////////////////////////////////////////////////////////
CTime CBarChart::last_sync()	// время последней синхронизации
{
	return hdr.last_sync;
}////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(pop)
