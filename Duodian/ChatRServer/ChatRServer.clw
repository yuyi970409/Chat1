; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatRServerDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatRServer.h"

ClassCount=5
Class1=CChatRServerApp
Class2=CChatRServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CChatLSocket
Class5=CChatCSocket
Resource3=IDD_CHATRSERVER_DIALOG

[CLS:CChatRServerApp]
Type=0
HeaderFile=ChatRServer.h
ImplementationFile=ChatRServer.cpp
Filter=N
LastObject=CChatRServerApp

[CLS:CChatRServerDlg]
Type=0
HeaderFile=ChatRServerDlg.h
ImplementationFile=ChatRServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_STOP

[CLS:CAboutDlg]
Type=0
HeaderFile=ChatRServerDlg.h
ImplementationFile=ChatRServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATRSERVER_DIALOG]
Type=1
Class=CChatRServerDlg
ControlCount=11
Control1=IDC_BUTTON_START,button,1342242816
Control2=IDC_BUTTON_STOP,button,1342242816
Control3=IDC_BUTTON_EXIT,button,1342242816
Control4=IDC_STATIC_SERVERNAME,static,1342308352
Control5=IDC_STATIC_MSG,button,1342177287
Control6=IDC_STATIC_SERVER,button,1342177287
Control7=IDC_EDIT_SERVERNAME,edit,1350631552
Control8=IDC_EDIT_SERVERPORT,edit,1350631552
Control9=IDC_STATIC_SERVERPORT,static,1342308352
Control10=IDC_STATIC_NUM,static,1342308352
Control11=IDC_LIST_MSG,listbox,1353777409

[CLS:CChatLSocket]
Type=0
HeaderFile=ChatLSocket.h
ImplementationFile=ChatLSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CChatLSocket

[CLS:CChatCSocket]
Type=0
HeaderFile=ChatCSocket.h
ImplementationFile=ChatCSocket.cpp
BaseClass=CSocket
Filter=N
VirtualFilter=uq
LastObject=CChatCSocket

