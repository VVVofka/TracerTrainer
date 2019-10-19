// TracerDoc.cpp : implementation of the CTracerDoc class
//

#include "stdafx.h"
#include "Tracer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "TracerDoc.h"
/////////////////////////////////////////////////////////////////////////////
// CTracerDoc
IMPLEMENT_DYNCREATE(CTracerDoc, CDocument)

BEGIN_MESSAGE_MAP(CTracerDoc, CDocument)
	//{{AFX_MSG_MAP(CTracerDoc)
	ON_COMMAND(ID_OPTI, OnOpti)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTracerDoc construction/destruction
CTracerDoc::CTracerDoc()
{	ALineFast = 2.0;
  ALineSlow = 7.5;
}
CTracerDoc::~CTracerDoc()
{}
BOOL CTracerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	
  CString LastFile = AfxGetApp()->GetProfileString("Options", "LastFile", "");
  if(LastFile != "")
    OnOpenDocument(LastFile);
	return TRUE;
}/////////////////////////////////////////////////////////////////////////////
// CTracerDoc serialization
void CTracerDoc::Serialize(CArchive& ar)
{	if (ar.IsStoring())
	{	}
	else
	{	}
}/////////////////////////////////////////////////////////////////////////////
// CTracerDoc diagnostics
#ifdef _DEBUG
void CTracerDoc::AssertValid() const
{	CDocument::AssertValid();
}
void CTracerDoc::Dump(CDumpContext& dc) const
{	CDocument::Dump(dc);
}
#endif //_DEBUG
////////////////////////////////////////////////////////////////////////////////////////
BOOL CTracerDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	// TODO: Add your specialized creation code here
  trace.LoadData(lpszPathName);
  trace.LoadALines(ALineFast, ALineSlow);
  UpdateAllViews(NULL);
  AfxGetApp()->WriteProfileString("Options", "LastFile", lpszPathName);
  CTracerDoc::SetPathName(lpszPathName, FALSE);
	return TRUE;
}////////////////////////////////////////////////////////////////////////////////////////
void CTracerDoc::OnOpti() 
{
  double res = 10000 * trace.OptiRun();
  CString s;   s.Format("%g", res);
  UpdateAllViews(NULL);
  AfxMessageBox(s);
}////////////////////////////////////////////////////////////////////////////////////////

