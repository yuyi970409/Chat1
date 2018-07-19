; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatRClientDlg
LastTemplate=CSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ChatRClient.h"

ClassCount=3
Class1=CChatRClientApp
Class2=CChatRClientDlg

ResourceCount=2
Resource1=IDR_MAINFRAME
Class3=CChatCSocket
Resource2=IDD_CHATRCLIENT_DIALOG

[CLS:CChatRClientApp]
Type=0
HeaderFile=ChatRClient.h
ImplementationFile=ChatRClient.cpp
Filter=N

[CLS:CChatRClientDlg]
Type=0
HeaderFile=ChatRClientDlg.h
ImplementationFile=ChatRClientDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_BUTTON_DISCONNECT



[DLG:IDD_CHATRCLIENT_DIALOG]
Type=1
Class=CChatRClientDlg
ControlCount=15
Control1=IDC_STATIC_SERVERNAME,static,1342308352
Control2=IDC_STATIC_SERVERPORT,static,1342308352
Control3=IDC_STATIC_SENDMSG,static,1342308352
Control4=IDC_STATIC_NICKNAME,static,1342308352
Control5=IDC_EDIT_NICKNAME,edit,1350631552
Control6=IDC_STATIC_SERVER,button,1342177287
Control7=IDC_EDIT_SERVERNAME,edit,1350631552
Control8=IDC_EDIT_SERVERPORT,edit,1350631552
Control9=IDC_STATIC_MSG,button,1342177287
Control10=IDC_EDIT_SENDMSG,edit,1350631552
Control11=IDC_BUTTON_CONNECT,button,1342242816
Control12=IDC_BUTTON_DISCONNECT,button,1342242816
Control13=IDC_BUTTON_SEND,button,1342242816
Control14=IDC_BUTTON_EXIT,button,1342242816
Control15=IDC_LIST_MSG,listbox,1353777409

[CLS:CChatCSocket]
Type=0
HeaderFile=ChatCSocket.h
ImplementationFile=ChatCSocket.cpp
BaseClass=CSocket
Filter=N
LastObject=CChatCSocket
VirtualFilter=uq

