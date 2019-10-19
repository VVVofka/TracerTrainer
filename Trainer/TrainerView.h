// TrainerView.h : interface of the CTrainerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAINERVIEW_H__95635D09_3440_4FA1_9BE4_16DB2F6EB188__INCLUDED_)
#define AFX_TRAINERVIEW_H__95635D09_3440_4FA1_9BE4_16DB2F6EB188__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Coord.h"
#include <float.h>
#include <math.h>
#include "DlgOptions.h"
#include "Info.h"
#include "Orders.h"	// Added by ClassView

#define COLOR_SL (RGB(150,0,150))
#define COLOR_BACK (RGB(0,0,0))
#define COLOR_VOL (RGB(130,130,0))
#define COLOR_BAR_BODY_UP (0)
#define COLOR_BAR_BODY_DN (0xFFFFFF)
#define COLOR_BAR (RGB(0,255,0))
#define COLOR_BAR_HIDDEN (RGB(0,200,200))
#define COLOR_WIN (RGB(100,100,255))
#define COLOR_LOSS (RGB(255,100,100))

#define COLOR_ALINE1 (RGB(0,0,255))
#define COLOR_ALINE2 (RGB(0,255,255))
#define COLOR_ALINE3 (RGB(250,250,0))
#define COLOR_ALINE4 (RGB(255,0,0))

#define WIDTH_ALINE 2

#define ZAZOR_UP 0.01
#define ZAZOR_DN 0


#define K_VOL (1.0/16)

enum ViewBarMode
{	Candle	=	1,
	Chart		=	2,
	Column	=	3
};

extern CStatusBar* pStatBar;

class CTrainerView : public CView
{
protected: // create from serialization only
	CTrainerView();
	DECLARE_DYNCREATE(CTrainerView)

// Attributes
public:
	CTrainerDoc* GetDocument();

// Operations
public:
  CCoord crdChart;
//	CCoord crdVolUp;
	CCoord crdVolDn;

  void ShowVisibleBars();
  void ShowInVisibleBars();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrainerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool viewOrder;
	BOOL bShowLastPrice;
	void ReDraw();
	virtual ~CTrainerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTrainerView)
	afx_msg void OnResetStat();
	afx_msg void OnMenuOptions();
	afx_msg void OnVolumeVisible();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnFileInfo();
	afx_msg void OnViewBarMode1();
	afx_msg void OnViewBarMode2();
	afx_msg void OnViewBarMode3();
	afx_msg void OnViewOrders();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ViewBarMode viewBarMode;
	void StatBarText(CString s="");
	BOOL VolVisible;
	BOOL newload;
	void DrawALines(int cnt);
	void DrawALine(int N,  COLORREF color, int cnt);
};

#ifndef _DEBUG  // debug version in TrainerView.cpp
inline CTrainerDoc* CTrainerView::GetDocument()
   { return (CTrainerDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAINERVIEW_H__95635D09_3440_4FA1_9BE4_16DB2F6EB188__INCLUDED_)
