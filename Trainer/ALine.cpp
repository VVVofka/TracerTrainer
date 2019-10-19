// Строим DSP линию с фиксированным отклонением Lev,
// на интервале t(переменный).
// Отклонение задаётся в попугаях.
// (GetDev)Один попугай равен StDev(Open,Close) на интервале t(переменный).
// (GetParrot)Один попугай равен StDev(FATL(7),Close) на интервале t(переменный).
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "ALine.h"
#pragma warning(push)
#pragma warning(disable:26495) 

CALine::CALine()
{}
CALine::~CALine()
{}////////////////////////////////////////////////////////////////////////////////////////
int CALine::Run(
					CFiltersKoef* f_ks,
					int const bars, 
					RateInfo* Rate,			//bars-1 - новейший
					double* Res,				//отклик
					double const Level,	//номинальный уровень отклонения
					int const Sglazh			//период сглаживания
				          )
{ int t, t0, j, j0;
	Rate0 = Rate;
	fks = f_ks;
  Lev = Level;
	SetParrot();
	t0 = fks->minT * Sglazh;
	if(t0 < fks->minT) t0 = fks->minT;
	if(t0 > fks->maxT) t0 = fks->maxT;
	j0 = t0 + fks->size(t0);
	t = defT(t0, Rate + j0);
  for(j=j0; ; )
  { if(j > 2*t)
		{	RateInfo* rt = Rate + j;
			double* koef = fks->koef(t);
			int size = fks->size(t);
			double resp = 0;
			for(int i=0; i<size; i++)
				resp += rt[-i].close * koef[i];
			Res[j] = resp;
		}else
			Res[j] = NOTHING_VAL;
    if(++j >= bars) break;
    t = defT(t, Rate+j);
  }
  return Smoothing(f_ks, bars, j0, Res, Sglazh);	/* Сглаживаем */
}////////////////////////////////////////////////////////////////////////////////////////
int CALine::Run(
					CFiltersKoef* f_ks,
					int const bars,
					int const countedbars,
					int* tprev,
					RateInfo* Rate,			//bars-1 - новейший
					double* Res,				//отклик
					double const Level,	//номинальный уровень отклонения
					int const Sglazh			//период сглаживания
				          )
{ int t, t0, j, j0;
	Rate0 = Rate;
	fks = f_ks;
  Lev = Level;
	SetParrot();
	t0 = *tprev;
	if(t0 < fks->minT) t0 = fks->minT;
	if(t0 > fks->maxT) t0 = fks->maxT;
	j0 = t0 + fks->size(t0);
	if(j0 < countedbars) 
		j0 = countedbars;
	t = defT(t0, Rate + j0);
  for(j=j0; ; )
  { if(j > 2*t)
		{	RateInfo* rt = Rate + j;
			double* koef = fks->koef(t);
			int size = fks->size(t);
			double resp = 0;
			for(int i=0; i<size; i++)
				resp += rt[-i].close * koef[i];
//			_ASSERTE(j>=0 && j<3084);
			Res[j] = resp;
		}else
		{
			Res[j] = NOTHING_VAL;
		}
    if(++j >= bars) break;
    t = defT(t, Rate+j);
  }
	*tprev = t;
  return Smoothing(f_ks, bars, j0, Res, Sglazh);	/* Сглаживаем */
}////////////////////////////////////////////////////////////////////////////////////////
int CALine::RunMom(
					CFiltersKoef* f_ks,
					CFiltersKoef* f_ks_mom,
					int const bars, 
					RateInfo* Rate,			//bars-1 - новейший
					double* Res,				//отклик
					double const Level,	//номинальный уровень отклонения
					int const Sglazh			    //период сглаживания
          )
{ 
	int t, t0, j, j0;
	Rate0 = Rate;
	fks = f_ks;
  Lev = Level;
	SetParrot();
	int minT = max(fks->minT, f_ks_mom->minT);
	int maxT = max(fks->maxT, f_ks_mom->maxT);
	t0 = minT * Sglazh;
	if(t0 < minT) t0 = minT;
	if(t0 > maxT) t0 = maxT;
	int size = max(fks->size(t0), f_ks_mom->size(t0));
	j0 = t0 + size;
	t = defT(t0, Rate + j0);
  for(j=j0; ; )
  { if(j > 2*t)
		{	
			RateInfo* rt = Rate + j;
			double* koef = fks->koef(t);
			size = fks->size(t);
			double resp = 0;
			for(int i=0; i<size; i++)
				resp += rt[-i].close * koef[i];

			koef = f_ks_mom->koef(t);
			size = f_ks_mom->size(t);
			double respmom = 0;
			for(int i=0; i<size; i++)
				respmom += rt[-i].close * koef[i];

      Res[j] = resp - respmom;
		}else
  		Res[j] = NOTHING_VAL;
    if(++j >= bars) break;
    t = defT(t, Rate+j);
  }
  return Smoothing(f_ks, bars, j0, Res, Sglazh);	/* Сглаживаем */
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

		if(rt - sizeparrot < Rate0)	return 0;
		if(rt - size < Rate0) 			return 0;
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
double CALine::Run1(
						CFiltersKoef* f_ks,
						int const bars, 
						RateInfo* Rate,					//bars-1 - новейший
						double const Level,			//номинальный уровень отклонения
						int* t									//предварительное значение Т
						)
{	RateInfo* rt = Rate + bars - 1;
	fks = f_ks;
  Lev = Level;
	SetParrot();
	if(*t <= fks->minT || *t >= fks->maxT) 
		*t = defT((fks->minT + fks->maxT)/2, rt);
	else
		*t = defT(*t, rt);
	double* koef = fks->koef(*t);
	int size = fks->size(*t);
	double resp = 0;
	for(int i=0; i<size; i++)
		resp += rt[-i].close * koef[i];
	return resp;
}////////////////////////////////////////////////////////////////////////////////////////
void CALine::SetParrot()
{	tparrot = 2 * fks->minT;
	koefparrot = fks->koef(tparrot);
	sizeparrot = fks->size(tparrot);
}////////////////////////////////////////////////////////////////////////////////////////
int CALine::Smoothing(	// Сглаживаем 
					CFiltersKoef* f_ks,
					int const bars, 
					int const j0,
					double* Res,				//отклик
					int const Sglazh		//период сглаживания
                       )
{
	if(Sglazh >= fks->minT)
	{	int szparrotLevel = fks->size(Sglazh);
		double* koefparrotLevel = fks->koef(Sglazh);
		for(int j=bars-1; j>=j0 + szparrotLevel; j--)
		{	double resp = 0;
			for(int i=0; i < szparrotLevel; i++)
			{	if(Res[j-i] == NOTHING_VAL)
					return j - i + szparrotLevel;
				resp += Res[j-i] * koefparrotLevel[i];
			}
			Res[j] = resp;
		}		//	for(int j=bars-1; j>=j0 + szparrotLevel; j--)
		return j0 + szparrotLevel;
	}		//	if(Sglazh >= fks->minT)
  return j0;
}////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(pop)

