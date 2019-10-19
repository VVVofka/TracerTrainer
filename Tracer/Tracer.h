// Tracer.h : main header file for the TRACER application
//

#if !defined(AFX_TRACER_H__1567AB52_FD83_422E_B9B6_64AC9DF35D0E__INCLUDED_)
#define AFX_TRACER_H__1567AB52_FD83_422E_B9B6_64AC9DF35D0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTracerApp:
// See Tracer.cpp for the implementation of this class
//

class CTracerApp : public CWinApp
{
public:
	CTracerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTracerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTracerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRACER_H__1567AB52_FD83_422E_B9B6_64AC9DF35D0E__INCLUDED_)
