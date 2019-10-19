#include "stdafx.h"
#include "FiltersKoef.h"
#pragma warning(disable : 4996)
const char DirName[255] = "DSPFilters\\";
CFiltersKoef::CFiltersKoef(int min_T, int max_T,
						 double k_Len, int A_1,
						 double dRiple, double k_Delay)
{
	Create(min_T, max_T, k_Len, A_1, dRiple, k_Delay);
}
CFiltersKoef::CFiltersKoef()
{
	minT = maxT = A1 = 0;
	kLen = 	Riple = kDelay = 0;
}
CFiltersKoef::~CFiltersKoef()
{}////////////////////////////////////////////////////////////////////////////////////////
void CFiltersKoef::Create(int min_T, int max_T,
						 double k_Len, int A_1,
						 double dRiple, double k_Delay)
{
	if(	minT == min_T && maxT == max_T &&
			kLen == k_Len && A1 == A_1 &&
			Riple == dRiple && kDelay == k_Delay) return;

	minT = min_T;
	maxT = max_T;
	kLen = k_Len;
	A1 = A_1;
	Riple = dRiple;
	kDelay = k_Delay;
	sprintf(FileName,"%sLP%02d%03d%03d%02d%03d%02d%s",DirName,
		minT,maxT,(int)(100*kLen),A1,(int)(100*Riple),(int)(100*kDelay),".fltr");
	load();
}
double* CFiltersKoef::koef(int t)
{
	double* ret = vkoef.p + vofs.p[t - minT];
	return ret;
}////////////////////////////////////////////////////////////////////////////////////////
void CFiltersKoef::load()
{
	int f=_open(FileName,_O_BINARY | _O_RDONLY);
	if(f==-1) 
	{	save();
		f=_open(FileName,_O_BINARY | _O_RDONLY);
	}
	_read(f, &minT, sizeof(minT));
	_read(f, &maxT, sizeof(maxT));
	CountAll = maxT - minT + 1;
	vofs.LoadFromFile(f);
	vsize.LoadFromFile(f);
	P1.LoadFromFile(f);
	D1.LoadFromFile(f);
	vkoef.LoadFromFile(f);
	_ASSERTE(vofs.Count==CountAll && vsize.Count==CountAll && P1.Count==CountAll && D1.Count==CountAll && vkoef.Count==vofs.p[vofs.Count-1]+vsize.p[vsize.Count-1]);
	_close(f);
}////////////////////////////////////////////////////////////////////////////////////////

void CFiltersKoef::save(){
	typedef int (CALLBACK* lpDigitalFilter)(int, int, int, int, int, int, int, double, int, double*);
	HINSTANCE hLibrary = LoadLibrary("DF.dll"); // Load the DLL now	lpDigitalFilter Func1;
	if (hLibrary == NULL) return;
	int maxsize;
	lpDigitalFilter Func1=(lpDigitalFilter)GetProcAddress(hLibrary,"DigitalFilter");
	if(Func1 == NULL) return;
	CountAll = maxT - minT + 1;
	vsize.Create(CountAll);
	vofs.Create(CountAll);
	P1.Create(CountAll);
	D1.Create(CountAll);
	TVector<double> kf(CountAll * 1500);
	int shift=0;
	for(int n=minT; n<=maxT; n++)
	{	int m = n-minT;
		maxsize = (int)(n * kLen + 0.5);
		for(int d1=1,d2=0;;)
		{	P1.p[m] = n+d1+shift;
			D1.p[m] = n-d2-shift;
			int delay = (int)(kDelay*(P1.p[m]+D1.p[m])/2);
			vsize.p[m] = ((Func1)(0, P1.p[m], D1.p[m], A1,	//Type, P1,D1,A1
								 0,       0,       0,		//P2,D2,A2
								 Riple, delay, kf.p + m * 1500));//Riple,Delay,*Koefs
			_ASSERTE(vsize.p[m]<=1500);
			if(vsize.p[m] <= maxsize && vsize.p[m] > 0) 
				break;
			if(d1==d2) d1++;
			else 
			{	if(n-d2 != 4)
					d2++;
				else
					d1++;
			}
			_ASSERTE(n-d2 >= 4); /*Не удаётся создать фильтр */
		}
		shift = (P1.p[m] - D1.p[m] - 1) / 2;
	//_RPT4(_CRT_WARN,"%d %d %d %d\n",n,P1.p[m],D1.p[m], vsize.p[m]);
	}
	FreeLibrary(hLibrary);         // Unload DLL from memory

	vofs.p[0] = 0;
	for(int n=1; n<CountAll; n++)
		vofs.p[n] = vofs.p[n-1] + vsize.p[n-1];

	vkoef.Create(vofs.p[CountAll-1] + vsize.p[CountAll-1]);
	double* pkoef=vkoef.p;
	for(int n=0; n<CountAll; n++)
		for(int m=0; m<vsize.p[n]; m++)
		{	*pkoef = kf[1500 * n + m];
			pkoef++;
		}
	int f=_open(FileName,_O_BINARY | _O_WRONLY | _O_CREAT);
	_ASSERTE(f != -1);
	if(f==-1) return;
	_write(f, &minT, sizeof(minT));
	_write(f, &maxT, sizeof(maxT));
	vofs.SaveToFile(f);
	vsize.SaveToFile(f);
	P1.SaveToFile(f);
	D1.SaveToFile(f);
	vkoef.SaveToFile(f);
	_close(f);
}////////////////////////////////////////////////////////////////////////////////////////

