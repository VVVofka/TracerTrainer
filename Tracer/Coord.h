#pragma once
#pragma warning(disable : 26451)
const double Okr = 0.5f;
class CCoord  
{
public:
	CCoord();
	virtual ~CCoord();
	
	CRect rc;
	void SetXY(long XMin, long XMax,
						double YMin, double YMax);

	LONG xc(int x)//��� ����� �- � ��������
		{return rc.left + (LONG)(Okr + ((double)x - (double)xmin) * kx); }
	LONG yc(double y) //��� ����� �- � ��������
		{return rc.bottom -(LONG)(Okr + (y - ymin) * ky);};

	int lxx(LONG xc)	//�������� ����� � - � ����������
		{return (int)((double)xmin + Okr + ((double)xc- (double)rc.left)/kx);}
	double lyy(LONG yc)	//�������� ����� y - � ����������
		{return ymin + ((double)rc.bottom - (double)yc) / ky;}
	
	int xmin, xmax;
	double ymin, ymax;

private:
	double kx, ky;
};

