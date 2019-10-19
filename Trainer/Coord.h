#pragma once
#pragma warning(push)
#pragma warning(disable:26451) 

const float Okr = 0.5f;
class CCoord  
{
public:
	CCoord();
	virtual ~CCoord();
	
	CRect rc;
	void SetXY(long XMin, long XMax,
						double YMin, double YMax);

	long xc(long x)//��� ����� �- � ��������
		{return rc.left + (long)(Okr + (x - xmin) * kx);};
	long yc(double y) //��� ����� �- � ��������
		{return rc.bottom -(long)(Okr + (y - ymin) * ky);};

	long lxx(long xc)	//�������� ����� � - � ����������
		{return (long)(xmin + Okr + (xc-rc.left)/kx);};
	double lyy(long yc)	//�������� ����� y - � ����������
		{return ymin + (rc.bottom - yc) / ky;};
	
	long xmin, xmax;
	double ymin, ymax;

private:
	double kx, ky;
};
#pragma warning(pop)
