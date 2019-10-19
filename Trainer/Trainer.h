// Trainer.h : main header file for the TRAINER application
//

#if !defined(AFX_TRAINER_H__6D641BFD_028D_4505_8135_F6683CDABCA3__INCLUDED_)
#define AFX_TRAINER_H__6D641BFD_028D_4505_8135_F6683CDABCA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "ALine.h"
#include "FiltersKoef.h"

/////////////////////////////////////////////////////////////////////////////
// CTrainerApp:
// See Trainer.cpp for the implementation of this class
//

class CTrainerApp : public CWinApp
{
public:
	CTrainerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrainerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTrainerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAINER_H__6D641BFD_028D_4505_8135_F6683CDABCA3__INCLUDED_)
