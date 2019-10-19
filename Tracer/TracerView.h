#if !defined(AFX_TRACERVIEW_H__A6E4B1EA_FE9A_40AF_92FC_94DB1FCA680C__INCLUDED_)
#define AFX_TRACERVIEW_H__A6E4B1EA_FE9A_40AF_92FC_94DB1FCA680C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <float.h>

#include "Data.h"
#include "ALines.h"
#include "Order.h"
#include "DSP.h"
#include "Coord.h"
#include "Opti.h"

#include "Trace.h"
extern CTRace trace;

#define COLOR_BACK 0
#define COLOR_BAR 0x00FF00
#define COLOR_BAR_BODY_UP 0x000000
#define COLOR_BAR_BODY_DN 0xFFFFFF
#define COLOR_BAR_COLUMN_UP RGB(0,  200,  100)
#define COLOR_BAR_COLUMN_DN RGB(0,  110,  190)
#define ALINE0_COLOR RGB(  0,  0,255)
#define ALINE1_COLOR RGB(  0,25,25)
#define ALINE2_COLOR RGB(25,25,  0)
#define ALINE3_COLOR RGB(25,  0,  0)
#define OPTI_LONG_COLOR   RGB(0,  255,  255)
#define OPTI_SHORT_COLOR  RGB(255,  255,  0)
#define WIDTH_OPTI  2

#define ZAZOR_DN 0.02
#define ZAZOR_UP 0.02
#define K_WIDTH_BAR 0.78
#define WIDTH_ALINE 1

class CTracerView : public CView
{
protected: // create from serialization only
	CTracerView();
	DECLARE_DYNCREATE(CTracerView)

// Attributes
public:
	CTracerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTracerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	protected:
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	void StatBarText(CString str);
	void DrawBarsColumn(int start, int end);
	void DrawBarsGrafic(int start, int end);
	void DrawBarsCandle(int start, int end);
	virtual ~CTracerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
  CCoord crdChart;

// Generated message map functions
protected:
	int BarsVisible;
	int ViewBarMode;

	void ReDraw();
	void DefMaxMin(int start, int end);
  void DrawBars(int start, int end);
  void DrawALines(int start, int end, int NLine, COLORREF color);
	void DrawOpti(int start, int end);
	//{{AFX_MSG(CTracerView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnZoomUp();
	afx_msg void OnZoomDn();
	afx_msg void OnMoveLeft();
	afx_msg void OnMoveRight();
	afx_msg void OnJumpLeft();
	afx_msg void OnJumpRight();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnJumpEnd();
	afx_msg void OnTst();
	afx_msg void OnOptions();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Clear();
};

#ifndef _DEBUG  // debug version in TracerView.cpp
inline CTracerDoc* CTracerView::GetDocument()
   { return (CTracerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACERVIEW_H__A6E4B1EA_FE9A_40AF_92FC_94DB1FCA680C__INCLUDED_)
