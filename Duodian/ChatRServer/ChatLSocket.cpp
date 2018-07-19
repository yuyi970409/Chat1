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
	//��ʼ���Ի�����ָ���Ա����
	m_pDlg=pDlg;
}

CChatLSocket::~CChatLSocket()
{
	//�������ʱ�ͷŶԻ�����ָ���Ա����
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
//FD_ACCEPT�¼�������
void CChatLSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//��ִ�л����OnAccept����
	CSocket::OnAccept(nErrorCode);
	//�ٵ��öԻ������OnAccept����
	m_pDlg->OnAccept();
}

IMPLEMENT_DYNAMIC(CChatLSocket,CSocket)
