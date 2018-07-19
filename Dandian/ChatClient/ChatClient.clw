; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatClientDlg
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatClient.h"

ClassCount=3
Class1=CChatClientApp
Class2=CChatClientDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CChatSocket
Resource2=IDD_CHATCLIENT_DIALOG

[CLS:CChatClientApp]
Type=0
HeaderFile=ChatClient.h
ImplementationFile=ChatClient.cpp
Filter=N

[CLS:CChatClientDlg]
Type=0
HeaderFile=ChatClientDlg.h
ImplementationFile=ChatClientDlg.cpp
Filter=D
LastObject=IDC_BUTTON_SEND
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_CHATCLIENT_DIALOG]
Type=1
Class=CChatClientDlg
ControlCount=13
Control1=IDC_STATIC_SERVERNAME,static,1342308352
Control2=IDC_STATIC_SERVERPORT,static,1342308352
Control3=IDC_STATIC_SENDMSG,static,1342308352
Control4=IDC_STATIC_MSG,button,1342177287
Control5=IDC_STATIC_SERVER,button,1342177287
Control6=IDC_EDIT_SERVERNAME,edit,1350631552
Control7=IDC_EDIT_SERVERPORT,edit,1350631552
Control8=IDC_EDIT_SENDMSG,edit,1350631552
Control9=IDC_BUTTON_CONNECT,button,1342242816
Control10=IDC_BUTTON_DISCONNECT,button,1342242816
Control11=IDC_BUTTON_SEND,button,1342242816
Control12=IDC_BUTTON_EXIT,button,1342242816
Control13=IDC_LIST_MSG,listbox,1353777409

[CLS:CChatSocket]
Type=0
HeaderFile=ChatSocket.h
ImplementationFile=ChatSocket.cpp
BaseClass=CAsyncSocket
Filter=N
LastObject=CChatSocket
VirtualFilter=q

