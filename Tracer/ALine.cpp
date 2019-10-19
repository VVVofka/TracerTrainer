// Строим DSP линию с фиксированным отклонением Lev,
// на интервале t(переменный).
// Отклонение задаётся в попугаях.
// (GetDev)Один попугай равен StDev(Open,Close) на интервале t(переменный).
// (GetParrot)Один попугай равен StDev(FATL(7),Close) на интервале t(переменный).
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ALine.h"
CALine::CALine()
{
	Lev = 0.;
}
CALine::~CALine()
{}////////////////////////////////////////////////////////////////////////////////////////
int CALine::Run(
					CFiltersKoef* f_ks,
					RateInfo* Rate,			//начальный!!!
					int const bars,      //отсчётов в отклике
					int* tprev,
					double const Level	//номинальный уровень отклонения
				          )
{	fks = f_ks;
  Rate0 = Rate;
  Lev = Level;
  int start = 2*fks->maxT;
  if (start >= bars) return 0;
  out.Create(bars - start);
	SetParrot();
	int t = *tprev;
	if(t < fks->minT) t = fks->minT;
	if(t > fks->maxT) t = fks->maxT;
  for(int j=start; j<bars ; j++)
  {	RateInfo* rt = Rate + j;
    t = defT(t, rt);
		double* koef = fks->koef(t);
		int size = fks->size(t);
		register double resp = 0;
		for(int i=0; i<size; i++)
			resp += rt[-i].close * koef[i];
		out.p[j-start] = resp;
  }
	*tprev = t;
  return start;
}////////////////////////////////////////////////////////////////////////////////////////
#define RETVAL0 (fks->minT)
int CALine::defT(int t, RateInfo* rt)		//определяем новую(оптимальную) чвстоту среза фильтра
{	double devprev, devcur;
	if(t >= fks->maxT) return fks->maxT;
	devcur = GetParrot(t, rt);
	if(devcur == 0) return RETVAL0;
	if(devcur < Lev)
	{	for(;;)
		{	if(++t >= fks->maxT) return fks->maxT;
			devprev = devcur;
			devcur = GetParrot(t, rt);
			if(devcur == 0) return RETVAL0;
			if(devcur >= Lev)
				if(devcur-Lev <= Lev-devprev) return t;
				else return --t;
		}	//	for(;;)
	}else if(devcur > Lev)
	{	for(;;)
		{	if(--t <= fks->minT) return fks->minT;
			devprev = devcur;
			devcur = GetParrot(t, rt);
			if(devcur == 0) return RETVAL0;
			if(devcur <= Lev)
				if(Lev-devcur <= devprev-Lev) return t;
				else return ++t;
		}	//	for(;;)
	}
	return t;	//(devcur == Lev)
}////////////////////////////////////////////////////////////////////////////////////////
double CALine::GetParrot(int t, RateInfo* Rate)
{	double stdevparrot=0, dev=0;
	double* koef = fks->koef(t);
	int size = fks->size(t);
	double k=2.0;
	int lent= t * 2;
	double dk = k/lent;
	for(int j=0; j<lent; j++)
	{	RateInfo* rt = Rate - j;

//		if(rt - sizeparrot < Rate0)	return 0;
//		if(rt - size < Rate0) 			return 0;
		double respparrot = 0;
		for(int i=0; i<sizeparrot; i++)
			respparrot += rt[-i].close * koefparrot[i];
		double cmd = rt->close - respparrot;
		stdevparrot += (cmd * cmd) * k;

		double resp = 0;
		for(int i=0; i<size; i++)
			resp += rt[-i].close * koef[i];
		cmd = resp - rt->close;
		dev += (cmd * cmd) * k;
		k -= dk;
	}		//for(int j=0; j<t; j++)
	return dev / stdevparrot;
}////////////////////////////////////////////////////////////////////////////////////////
void CALine::SetParrot()
{	tparrot = 2 * fks->minT;
	koefparrot = fks->koef(tparrot);
	sizeparrot = fks->size(tparrot);
}////////////////////////////////////////////////////////////////////////////////////////

