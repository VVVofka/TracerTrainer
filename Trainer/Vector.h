#pragma once
#pragma warning(push)
#pragma warning(disable:26495) 
#pragma warning(disable:6031) 

// use: TVector<float> v(5); v.Item(1);
//or: typedef TVector<int> INTVECTOR; 
//		INTVECTOR v(5);
// for files
#define VECTOR_COUNT	0x1A
#define VECTOR_DATA		0x1B
#define VECTOR_CLOSE	0x1C
#include <stdio.h>
#include <io.h>

template <class T>
class TVector  
{
public:
	T *p;
	int Count;

	T MAXVAL;
	T Max;	//min значение(после выз GetMax())
	T Min;	//max значение(после выз GetMin())
	int MaxN = 0;	//№ max значения(после выз GetMax())
	int MinN = 0;	//№ min значения(после выз GetMin())

////////////////////////////////////////////////////////////////////////////////////////
	TVector()
	{	
		Count = intcnt = 0;
		p = ptr0 = NULL;
	};

	TVector(int uCount)
	{	
		Count = intcnt = 0;
		p = ptr0 = NULL;
		Create(uCount);
	};

	TVector(TVector& R)	//copy
	{	
		Count = intcnt = 0;
		p = ptr0 = NULL;
		copyclass(R);
	};			
	virtual ~TVector()
	{//		_RPT2(0,"Delete Vector %X %d\n", ptr0, Count);
	finish();
	};

	TVector& operator=(TVector &R)	//copy
		{	copyclass(R);	return *this;};

	T operator[](int j){return ptr0[j];};
	double operator & (TVector& R){return sqrt(Evklid(R));};	//расстояниt между векторами
	double operator && (TVector& R){return Evklid(R);};	//квадрат расстояния между векторами
/////////////////////////////////////////////////////////////////////////////////	
	void Create(int uCount)	//create vector array
{ 
	if (uCount == 0 && intcnt != 0)
		finish();
	else if (uCount > intcnt)
	{	
		if (intcnt) finish();
		if (uCount)
			p = ptr0 = new T[(int)(intcnt = uCount)];	
		else
		{
			p = ptr0 = NULL;	
			intcnt = 0;
		}
	}
	Count = uCount;
};
////////////////////////////////////////////////////////////////////////////////////////
	void Create(int uCount, int MemoryReserv)	//create vector array,с резервированием памяти
{ 
	if(uCount > MemoryReserv)
		MemoryReserv = uCount;
	Create(MemoryReserv);
	Count = uCount;
//	ReSize(uCount);
};
////////////////////////////////////////////////////////////////////////////////////////
	void CreateD(double uCount)	//create vector array
{ Create((int)(uCount + 0.5f)) ;
};
////////////////////////////////////////////////////////////////////////////////////////
	void CreateF(float uCount)	//create vector array
{ Create((int)(uCount + 0.5f)) ;};
////////////////////////////////////////////////////////////////////////////////////////
	T* p0()	{	return ptr0;};
////////////////////////////////////////////////////////////////////////////////////////
	void Fill(T StartNum, T Step) //заполн с арифм прогрессией
		{	for(int j=0;j<Count;++j)	
			{	ptr0[j]=StartNum;
				StartNum += Step;
			}
		};
////////////////////////////////////////////////////////////////////////////////////////
	void Add(T Val)
	{	int j;
		if(Count >= intcnt) 
		{
			if(intcnt > 0)
			{
				p = new T[intcnt += intcnt];	
//				_RPT2(0,"Add: %d %d\n", intcnt, Count);
			}
			else
			{
				p = new T[intcnt = 1];
//				_RPT2(0,"Add: %d %d\n", intcnt, Count);
			}
			for(j=0; j < Count; j++)
				p[j] = ptr0[j];
			if(intcnt != 1) 
				delete[] ptr0;
			ptr0 = p;
		}
		p[Count++] = Val;
	};
////////////////////////////////////////////////////////////////////////////////////////

	void Fill0(){for(int j=0;j<Count;++j)	
		{	ptr0[j]=(T)0;}};
////////////////////////////////////////////////////////////////////////////////////////
	double GetMax()
	{	Max = -MAXVAL;
		for(int j=0; j<Count; j++)
			if(ptr0[j] >= Max) 
			{	Max=ptr0[j];
				MaxN = j;
			}
		return Max;
}////////////////////////////////////////////////////////////////////////////////////////
	double GetMin()
	{	Min = MAXVAL;
		for(int j=0; j<Count; j++)
			if(ptr0[j] <= Min) 
			{	Min=ptr0[j];
				MinN = j;
			}
		return Min;
}////////////////////////////////////////////////////////////////////////////////////////
	void GetMaxMin()
	{	Max = -(Min = MAXVAL);
		for(int j=0; j<Count; j++)
		{	if(ptr0[j] <= Min) 
			{	Min=ptr0[j];
				MinN = j;
			}
			if(ptr0[j] >= Max) 
			{	Max=ptr0[j];
				MaxN = j;
			}
		}	//for(int j=0; j<Count; j++)
}////////////////////////////////////////////////////////////////////////////////////////
	double Sum() //Сумма всех элементов
		{	double ret = 0;
			for(int j=0; j<Count; ++j)	
				ret += ptr0[j];
			return ret;
		};
////////////////////////////////////////////////////////////////////////////////////////
	double Avg() //Среднее всех элементов
		{	return Sum() / Count;
		};
////////////////////////////////////////////////////////////////////////////////////////
void Normalize(T MinLevel = (T)0, T MaxLevel = (T)1)
{
	GetMaxMin();
	T maxmin = (Max - Min)/(MaxLevel - MinLevel);
	T min = MinLevel - Min;
	for(int j=0; j<Count; j++)
		ptr0[j] = (ptr0[j] + min) / maxmin;	//конец нормализации
}
////////////////////////////////////////////////////////////////////////////////////////
	void FillRnd(T xmin, T xmax)
	{	//CVVVRnd crnd;
#ifdef _DEBUG
		srand(1);
#else
		srand( (int)time( NULL ) );
#endif
		T len = xmax - xmin;
		for(int j=0;j<Count;j++)
			ptr0[j] = xmin + len * (T)rand()/RAND_MAX;	// crnd.genrand_real2();
	}
/////////////////////////////////////////////////////////////////////////////////
	void Load(T *ptr, int Size) //load 1 dim array
	{	
		Create(Size);
		for(int j=0; j<Count; j++) 
			ptr0[j] = ptr[j];
		p = ptr0;
	}
////////////////////////////////////////////////////////////////////////////////////////
	void Intermix(void)	//перемешать
	{	int r,l;
		T cmd;
		for (l = Count; l>0; ) 
		{	r =(int)(l * (float)rand()/(RAND_MAX+1)); //1
	//	{	r =(int)(l * crnd.genrand_real2()); //1
			cmd = ptr0[r];	//2
			ptr0[r] = ptr0[--l];	//3
			ptr0[l] = cmd;	//4
		}
	}
////////////////////////////////////////////////////////////////////////////////////////
	void Invert()
	{	int Cnt2 = Count/2;
		for(int i=0; i<Cnt2; i++)
		{	T cmd = ptr0[i];
			int ib = Count-i-1;
			ptr0[i] = ptr0[ib];
			ptr0[ib] = cmd;
		}
	}
////////////////////////////////////////////////////////////////////////////////////////
	void ReSize(int NewSize)
	{
		_ASSERTE(NewSize >= 0);
		if(NewSize == 0) 
			finish();
		else if(intcnt==0)
			Create(NewSize);
		else if(NewSize <= intcnt)
			Count = NewSize;
		else	//NewSize > intcnt
		{ p = ptr0;
			ptr0 = new T[intcnt = NewSize];	
			for(int j=0; j<Count; j++) //копируются только старые!
				ptr0[j] = p[j];
			delete[] p;
			p = ptr0;		
			Count = NewSize;
		}
	};
////////////////////////////////////////////////////////////////////////////////////////
/*TVectorF v(5);
	TVectorU s;
	v.p[0]=15.0f; v.p[1]=3.1f; v.p[2]=5.0f; v.p[3]=9.3f; v.p[4]=6.4f;
	v.SortBubleDesc(&s);
	return 0;		*/
void SortBuble(TVector<int> *R)
{	R->Create(Count);
	R->Fill(0, 1);
	for(int i = Count; i>1; i--)
	{	bool k = true;	//Условия Айверсона
		for(int j=1; j<i; j++)
		if(ptr0[R->p[j]] < ptr0[R->p[j-1]])
		{	int n = R->p[j];
			R->p[j] = R->p[j-1];
			R->p[j-1] = n;
			k = false;
		}
		if(k) return;
	}
}
////////////////////////////////////////////////////////////////////////////////////////
void SortBubleDesc(TVector<int> *R)
{	R->Create(Count);
	R->Fill(0, 1);
	for(int i = Count; i>1; i--)
	{	bool k = true;	//Условия Айверсона
		for(int j=1; j<i; j++)
		if(ptr0[R->p[j]] > ptr0[R->p[j-1]])
		{	int n = R->p[j];
			R->p[j] = R->p[j-1];
			R->p[j-1] = n;
			k = false;
		}
		if(k) return;
	}
}////////////////////////////////////////////////////////////////////////////////////////
	void SaveToFile(int IdFile)
	{
		_write(IdFile, &Count, sizeof(Count));
		_write(IdFile, ptr0, sizeof(T) * Count);
	}
///////////////////////////////////////////////////////////////////////////////
	void LoadFromFile(int IdFile)
	{		
		_read(IdFile, &Count, sizeof(Count));
		Create(Count);
		_read(IdFile, ptr0, sizeof(T) * Count);
	}
///////////////////////////////////////////////////////////////////////////////
	void finish()
	{
		if(intcnt) 
			delete[] ptr0;
		Count = intcnt = 0;
		p = ptr0 = NULL;
	};
////////////////////////////////////////////////////////////////////////////////////////
	double Evklid(TVector& R);
////////////////////////////////////////////////////////////////////////////////////////
protected:
	T *ptr0;	
private:
	int intcnt;
	void copyclass(TVector& R)
	{	
//		_ASSERTE(R.Count >= 0);
		if(R.Count==0)
		{ finish();
			return;
		}
		if(R.Count > intcnt)
		{	if (intcnt) delete[] ptr0;
			ptr0 = new T[intcnt = R.Count];
		}
		Count = R.Count;
		for(int j=0; j < R.Count; j++) 
				ptr0[j] = R.p0()[j];
		p = ptr0;
	}
};//// end of class//////////////////////////////////////////////////////////////////////////////////////
template <class T>
double TVector<T>::Evklid(TVector& R)
{	double ret=0, cmd;
	for (int j=0; j<Count; j++)
		{	cmd = ptr0[j] - R[j];
			ret += cmd * cmd;
		}
	return ret;
}
/////////////////////////////////////////////////////////////////////////////////
typedef TVector<int> TVectorI;
typedef TVector<long> TVectorL;
typedef TVector<int> TVectorU;
typedef TVector<float> TVectorF;
typedef TVector<double> TVectorD;

////////////////////////////////////////////////////////////////////////////////////////
#pragma warning(pop)