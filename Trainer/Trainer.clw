; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CTrainerView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Trainer.h"
LastPage=0

ClassCount=7
Class1=CTrainerApp
Class2=CTrainerDoc
Class3=CTrainerView
Class4=CMainFrame

ResourceCount=6
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDR_MAINFRAME (English (U.S.))
Class5=CAboutDlg
Resource4=IDD_DIALOG_OPTIONS
Class6=CDlgOptions
Resource5=IDD_ABOUTBOX (English (U.S.))
Class7=CInfo
Resource6=IDD_DIALOG_INFO

[CLS:CTrainerApp]
Type=0
HeaderFile=Trainer.h
ImplementationFile=Trainer.cpp
Filter=N

[CLS:CTrainerDoc]
Type=0
HeaderFile=TrainerDoc.h
ImplementationFile=TrainerDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CTrainerDoc

[CLS:CTrainerView]
Type=0
HeaderFile=TrainerView.h
ImplementationFile=TrainerView.cpp
Filter=C
LastObject=CTrainerView
BaseClass=CView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=MENU_OPTIONS
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=Trainer.cpp
ImplementationFile=Trainer.cpp
Filter=D

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
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
CommandCount=16
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command16=ID_APP_ABOUT

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
CommandCount=14
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE


[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_MRU_FILE1
Command4=ID_APP_EXIT
Command5=ID_EDIT_UNDO
Command6=UN_HIDE
Command7=RESET_STAT
Command8=MENU_PREV_BAR
Command9=MENU_NEXT_BAR
Command10=MENU_NAVIG_RND
Command11=MENU_HOME
Command12=MENU_END
Command13=MENU_PGUP
Command14=MENU_PGDN
Command15=ID_VIEW_TOOLBAR
Command16=ID_VIEW_STATUS_BAR
Command17=MENU_VOLUME_VISIBLE
Command18=MENU_VIEW_ORDERS
Command19=MENU_VIEW_BAR_MODE1
Command20=MENU_VIEW_BAR_MODE2
Command21=MENU_VIEW_BAR_MODE3
Command22=MENU_FILE_INFO
Command23=MENU_OPTIONS
Command24=ID_APP_ABOUT
Command25=OREDE_BUY
Command26=ORDER_SELL
Command27=ORDER_CLOSE
CommandCount=27

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=MENU_VIEW_BAR_MODE1
Command2=MENU_VIEW_BAR_MODE2
Command3=MENU_VIEW_BAR_MODE3
Command4=ID_EDIT_COPY
Command5=MENU_VIEW_ORDERS
Command6=MENU_FILE_INFO
Command7=MENU_VOLUME_VISIBLE
Command8=ID_FILE_NEW
Command9=MENU_OPTIONS
Command10=ID_FILE_OPEN
Command11=RESET_STAT
Command12=UN_HIDE
Command13=ID_EDIT_UNDO
Command14=ORDER_SELL
Command15=MENU_END
Command16=ID_APP_EXIT
Command17=MENU_HOME
Command18=MENU_PREV_BAR
Command19=MENU_PGDN
Command20=MENU_PGUP
Command21=MENU_NEXT_BAR
Command22=ORDER_CLOSE
Command23=NEXT_SERIES
Command24=OREDE_BUY
Command25=ID_EDIT_UNDO
CommandCount=25

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_DIALOG_OPTIONS]
Type=1
Class=CDlgOptions
ControlCount=15
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_VISIBLE_BARS,edit,1350639746
Control4=IDC_STATIC,static,1342308354
Control5=IDC_HIDDEN_BARS,edit,1350639746
Control6=IDC_STATIC,static,1342308354
Control7=IDC_VOL_VISIBLE,button,1342243075
Control8=IDC_MONTHCALENDAR1,SysMonthCal32,1342242832
Control9=IDC_STATIC,static,1342308354
Control10=IDC_AUTO_SL,edit,1350631426
Control11=IDC_STATIC,static,1342308352
Control12=IDC_FATL,edit,1350639746
Control13=IDC_STATIC,static,1342308354
Control14=IDC_SATL,edit,1350639746
Control15=IDC_STATIC,static,1342308354

[CLS:CDlgOptions]
Type=0
HeaderFile=DlgOptions.h
ImplementationFile=DlgOptions.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DSP_LINE_FAST

[DLG:IDD_DIALOG_INFO]
Type=1
Class=CInfo
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_INFO,edit,1350633668

[CLS:CInfo]
Type=0
HeaderFile=Info.h
ImplementationFile=Info.cpp
BaseClass=CDialog
Filter=D
LastObject=CInfo
VirtualFilter=dWC

