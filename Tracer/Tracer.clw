; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTracerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Tracer.h"
LastPage=0

ClassCount=7
Class1=CTracerApp
Class2=CTracerDoc
Class3=CTracerView
Class4=CMainFrame

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class5=CAboutDlg
Resource3=IDD_ABOUTBOX (English (U.S.))
Class6=COptimizer
Resource4=IDR_MAINFRAME (English (U.S.))
Class7=COptions
Resource5=IDD_OPTIONS

[CLS:CTracerApp]
Type=0
HeaderFile=Tracer.h
ImplementationFile=Tracer.cpp
Filter=N
LastObject=CTracerApp

[CLS:CTracerDoc]
Type=0
HeaderFile=TracerDoc.h
ImplementationFile=TracerDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CTracerDoc

[CLS:CTracerView]
Type=0
HeaderFile=TracerView.h
ImplementationFile=TracerView.cpp
Filter=C
LastObject=CTracerView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_TST
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Tracer.cpp
ImplementationFile=Tracer.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Class=CAboutDlg

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_APP_ABOUT
CommandCount=12
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
CommandCount=13
Command4=ID_EDIT_UNDO
Command13=ID_PREV_PANE


[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_EDIT_UNDO
Command8=ID_EDIT_CUT
Command9=ID_EDIT_COPY
Command10=ID_EDIT_PASTE
Command11=ID_VIEW_STATUS_BAR
Command12=ID_ZOOM_DN
Command13=ID_ZOOM_UP
Command14=ID_JUMP_LEFT
Command15=ID_MOVE_LEFT
Command16=ID_MOVE_RIGHT
Command17=ID_JUMP_RIGHT
Command18=ID_JUMP_END
Command19=ID_OPTI
Command20=ID_APP_ABOUT
Command21=ID_TST
Command22=ID_OPTIONS
CommandCount=22

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_UNDO
Command5=ID_EDIT_CUT
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_EDIT_COPY
Command11=ID_EDIT_PASTE
Command12=ID_NEXT_PANE
Command13=ID_PREV_PANE
CommandCount=13

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[CLS:COptimizer]
Type=0
HeaderFile=Optimizer.h
ImplementationFile=Optimizer.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RES_OPTI
VirtualFilter=dWC

[DLG:IDD_OPTIONS]
Type=1
Class=COptions
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST_BAR,listbox,1352728833
Control4=IDC_BTN_OPTIONS_TEST,button,1342242816

[CLS:COptions]
Type=0
HeaderFile=Options.h
ImplementationFile=Options.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTN_OPTIONS_TEST

