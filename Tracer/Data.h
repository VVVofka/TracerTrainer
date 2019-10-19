#if !defined(AFX_DATA_H__81958274_E34A_426D_8239_99C844F670E3__INCLUDED_)
#define AFX_DATA_H__81958274_E34A_426D_8239_99C844F670E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afx.h>
#include "DSP.h"
#include <STDIO.H>
#include "Vector.h"
#include <io.h>
#include <FCNTL.H>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <float.h>
#include <minmax.h>

#define TMPFILE "C:\\Tr\\Temp\\DataTrace.dat"

class CData
{
public:
	CData();
	virtual ~CData();

	int Load(CString f_name);

	time_t dt(int n);
	double close(int n);
	double open(int n);
	double high(int n);
	double low(int n);

	HistoryHeader hdr;
	TVector<RateInfo> vret;

private:

};
#endif // !defined(AFX_DATA_H__81958274_E34A_426D_8239_99C844F670E3__INCLUDED_)
