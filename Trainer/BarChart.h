#if !defined(AFX_BARCHART_H__5DB90FFF_FA4A_4308_B1DB_0A2E745398C8__INCLUDED_)
#define AFX_BARCHART_H__5DB90FFF_FA4A_4308_B1DB_0A2E745398C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DSP.h"
#include <STDIO.H>
#include "Vector.h"
#include <io.h>
#include <FCNTL.H>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

class CBarChart  
{
public:
	CTime last_sync();	// время последней синхронизации
	CTime timesign();	// временной отпечаток создания базы
	int Period();
	CString Symbol();
	CBarChart();
	virtual ~CBarChart();
  int LoadHST(char* fname, CTime Date_Start);

  int FindDT(time_t t);

  time_t GetDate(int Index);
  double GetOpen(int Index) {return v.p[IndexBase + Index0 + Index].open;};
  double GetHigh(int Index) {return v.p[IndexBase + Index0 + Index].high;};
  double GetLow(int Index)  {return v.p[IndexBase + Index0 + Index].low;};
  double GetClose(int Index){return v.p[IndexBase + Index0 + Index].close;};
  double GetVol(int Index)  {return v.p[IndexBase + Index0 + Index].vol;};
	RateInfo* GetRate(int Index)	{return &v.p[IndexBase + Index0 + Index];};
	RateInfo* GetThrow(int j)	{return &v.p[j];};
	__int64 GetThrowCount(){return v.Count;};

  int GetIndex(){return IndexBase+Index0;};
	int Index0;
  __int64 Count(){return v.Count - IndexBase;};
  int Digits();
  TVector<RateInfo> v;

private:
  int LoadHST(char* fname);
	HistoryHeader hdr;

	int IndexBase;
};

#endif // !defined(AFX_BARCHART_H__5DB90FFF_FA4A_4308_B1DB_0A2E745398C8__INCLUDED_)
