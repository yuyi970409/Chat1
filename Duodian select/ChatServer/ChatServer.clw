; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatServerDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatServer.h"

ClassCount=3
Class1=CChatServerApp
Class2=CChatServerDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CChatSocket
Resource2=IDD_CHATSERVER_DIALOG

[CLS:CChatServerApp]
Type=0
HeaderFile=ChatServer.h
ImplementationFile=ChatServer.cpp
Filter=N

[CLS:CChatServerDlg]
Type=0
HeaderFile=ChatServerDlg.h
ImplementationFile=ChatServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_STOP



[DLG:IDD_CHATSERVER_DIALOG]
Type=1
Class=CChatServerDlg
ControlCount=13
Control1=IDC_EDIT_SERVERPORT,edit,1350631552
Control2=IDC_EDIT_SERVERNAME,edit,1350631552
Control3=IDC_EDIT_SENDMSG,edit,1350631552
Control4=IDC_STATIC_SERVERNAME,static,1342308352
Control5=IDC_STATIC_SERVERPORT,static,1342308352
Control6=IDC_STATIC_SENDMSG,static,1342308352
Control7=IDC_STATIC_MSG,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_BUTTON_START,button,1342242816
Control10=IDC_BUTTON_STOP,button,1342242816
Control11=IDC_BUTTON_SEND,button,1342242816
Control12=IDC_BUTTON_EXIT,button,1342242816
Control13=IDC_LIST_MSG,listbox,1353777409

[CLS:CChatSocket]
Type=0
HeaderFile=ChatSocket.h
ImplementationFile=ChatSocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CChatSocket

