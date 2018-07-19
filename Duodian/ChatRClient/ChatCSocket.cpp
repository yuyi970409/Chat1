// ChatCSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRClient.h"
#include "ChatCSocket.h"
#include "ChatRClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatCSocket

IMPLEMENT_DYNAMIC(CChatCSocket,CSocket)

CChatCSocket::CChatCSocket(CChatRClientDlg * pDlg)
{
	m_pDlg=pDlg;
}

CChatCSocket::~CChatCSocket()
{
	m_pDlg=NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CChatCSocket, CSocket)
	//{{AFX_MSG_MAP(CChatCSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CChatCSocket member functions

void CChatCSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	CSocket::OnReceive(nErrorCode);
	m_pDlg->OnReceive();
}
