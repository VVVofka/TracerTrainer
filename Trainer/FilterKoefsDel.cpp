#include "stdafx.h"
#include "FilterKoefsDel.h"
#pragma warning(push)
#pragma warning(disable:4996) 
#pragma warning(disable:6031) 

const char DirName[255] = "DSPFilters\\";
CFilterKoefsDel::CFilterKoefsDel(int T,
								double k_Len, int A_1,
								double dRiple){
	Create(T, k_Len, A_1, dRiple);
}
CFilterKoefsDel::CFilterKoefsDel(){
	_T = A1 = 0;
	kLen = 	Riple = 0;
}
CFilterKoefsDel::~CFilterKoefsDel()
{}////////////////////////////////////////////////////////////////////////////////////////
void CFilterKoefsDel::Create(int _T1,
							double k_Len, int A_1,
							double dRiple){
	if(_T == _T1 && kLen == k_Len && A1 == A_1 && Riple == dRiple)
    return;
	_T = _T1;
	kLen = k_Len;
	A1 = A_1;
	Riple = dRiple;
	sprintf(FileName,"%sLPD%03d%03d%02d%03d%s",DirName,
		_T,(int)(100*kLen),A1,(int)(100*Riple),".fltr");
	load();
}////////////////////////////////////////////////////////////////////////////////////////
double* CFilterKoefsDel::koef(int t){
	double* ret = vkoef.p + vofs.p[t];
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
void CFilterKoefsDel::load(){
	int f=_open(FileName,_O_BINARY | _O_RDONLY);
	if(f==-1) 
	{	save();
		f=_open(FileName,_O_BINARY | _O_RDONLY);
	}
	_read(f, &_T, sizeof(_T));
	CountAll = _T/2 + 1;
	vofs.LoadFromFile(f);
	vsize.LoadFromFile(f);
	P1.LoadFromFile(f);
	D1.LoadFromFile(f);
	vkoef.LoadFromFile(f);
	_ASSERTE(vofs.Count==CountAll && vsize.Count==CountAll && P1.Count==CountAll && D1.Count==CountAll && vkoef.Count==vofs.p[vofs.Count-1]+vsize.p[vsize.Count-1]);
	_close(f);
}////////////////////////////////////////////////////////////////////////////////////////
void CFilterKoefsDel::save(){
	typedef int (CALLBACK* lpDigitalFilter)(int, int, int, int, int, int, int, double, int, double*);
	HINSTANCE hLibrary = LoadLibrary("DF.dll"); // Load the DLL now	lpDigitalFilter Func1;
	if (hLibrary == NULL) return;
	lpDigitalFilter Func1=(lpDigitalFilter)GetProcAddress(hLibrary,"DigitalFilter");
	if(Func1 == NULL) return;
	CountAll = _T/2  + 1;
	vsize.Create(CountAll);
	vofs.Create(CountAll);
	P1.Create(CountAll);
	D1.Create(CountAll);
	TVector<double> kf(CountAll * 1500);
  int n = _T;
  int maxsize = (int)(n * kLen + 0.5);
	for(int delay=0,shift=0; delay<CountAll; delay++)
	{	
		for(int d1=1,d2=0;;)
		{	P1.p[delay] = n+d1+shift;
			D1.p[delay] = n-d2-shift;
			vsize.p[delay] = ((Func1)(0, P1.p[delay], D1.p[delay], A1,	//Type, P1,D1,A1
															 0,       0,       0,		//P2,D2,A2
															 Riple, delay, kf.p + delay * 1500));//Riple,Delay,*Koefs
			_ASSERTE(vsize.p[delay]<=1500);
			if(vsize.p[delay] <= maxsize && vsize.p[delay] > 0) 
				break;
			if(d1==d2) d1++;
			else 
			{	if(n-d2 != 5)
					d2++;
				else
					d1++;
			}
			_ASSERTE(n-d2 > 4); /*Не удаётся создать фильтр */
		}
		shift = (P1.p[delay] - D1.p[delay] - 1) / 2;
	//	_RPT4(_CRT_WARN,"%d %d %d %d\n",n,P1.p[m],D1.p[m], vsize.p[m]);
	}
	FreeLibrary(hLibrary);         // Unload DLL from memory

	vofs.p[0] = 0;
	for(n=1; n<CountAll; n++)
		vofs.p[n] = vofs.p[n-1] + vsize.p[n-1];

	vkoef.Create(vofs.p[CountAll-1] + vsize.p[CountAll-1]);
	double* pkoef=vkoef.p;
	for(n=0; n<CountAll; n++)
		for(int m=0; m<vsize.p[n]; m++)
		{	*pkoef = kf[1500 * n + m];
			pkoef++;
		}
	int f=_open(FileName,_O_BINARY | _O_WRONLY | _O_CREAT);
	_ASSERTE(f != -1);
	if(f==-1) return;
	_write(f, &_T, sizeof(_T));
	vofs.SaveToFile(f);
	vsize.SaveToFile(f);
	P1.SaveToFile(f);
	D1.SaveToFile(f);
	vkoef.SaveToFile(f);
	_close(f);
}////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(pop)
