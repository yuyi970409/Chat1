// ChatLSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRServer.h"
#include "ChatLSocket.h"

#include "ChatRServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatLSocket

CChatLSocket::CChatLSocket(CChatRServerDlg * pDlg)
{
	//初始化对话框类指针成员变量
	m_pDlg=pDlg;
}

CChatLSocket::~CChatLSocket()
{
	//程序结束时释放对话框类指针成员变量
	m_pDlg=NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatLSocket, CSocket)
	//{{AFX_MSG_MAP(CChatLSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatLSocket member functions
//FD_ACCEPT事件处理函数
void CChatLSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//先执行基类的OnAccept函数
	CSocket::OnAccept(nErrorCode);
	//再调用对话框类的OnAccept函数
	m_pDlg->OnAccept();
}

IMPLEMENT_DYNAMIC(CChatLSocket,CSocket)
