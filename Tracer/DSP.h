#pragma once
#define WIN32_LEAN_AND_MEAN  // Exclude rarely-used stuff from Windows headers

#define MT4_EXPFUNC __declspec(dllexport)
#include <time.h>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <malloc.h>

#define MAXPERIOD 300
//#define EMPTY_POINT 2147483647.0000
#define NOTHING_VAL 0x7FFFFFFF
#define FILTER_KOEF_CNT 1500
#define ID_ERR 567890

#define MINFILTER 7
#define MAXFILTER 200

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
__declspec(dllimport) int __stdcall DigitalFilter(int const F_Type,
	int const P1,int const D1,int const A1,int const P2,int const D2,int const A2,
  double const Ripple,int const Delay, double* arr); 
#ifdef __cplusplus
}
#endif  /* __cplusplus */

#pragma pack(push,1)
struct RateInfo
  {
	 UINT							 ctm;
   double            open;
   double            low;
   double            high;
   double            close;
   double            vol;
  };
#pragma pack(pop)

struct HistoryHeader
{
  int               version;            // версия базы
  char              copyright[64];      // копирайт
  char              symbol[12];         // инструмент
  int               period;             // период инструмента
  int               digits;             // число знаков после запятой в инструменте
  UINT            timesign;           // временной отпечаток создания базы
  UINT            last_sync;          // время последней синхронизации
  int               unused[13];         // для будущего использования
};

//----
struct MqlStr
  {
   int               len;
   char             *string;
  };

enum RateType
	{
 TIME_INDEX   =0,
 OPEN_INDEX   =1,
 LOW_INDEX    =2,
 HIGH_INDEX   =3,
 CLOSE_INDEX  =4,
 VOLUME_INDEX =5,
	};