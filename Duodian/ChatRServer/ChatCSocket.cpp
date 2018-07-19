// ChatCSocket.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRServer.h"
#include "ChatCSocket.h"

#include "ChatRServerDlg.h"
#include "Msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatCSocket
//��ʼ����Ա����
CChatCSocket::CChatCSocket(CChatRServerDlg * pDlg)
{
	m_pDlg=pDlg;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

//�������ʱ�ͷŸ���Ա����
CChatCSocket::~CChatCSocket()
{
	m_pDlg=NULL;
	if(m_pArchiveOut!=NULL) delete m_pArchiveOut;
	if(m_pArchiveIn!=NULL) delete m_pArchiveIn;
	if(m_pFile!=NULL) delete m_pFile;
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

//FD_READ�¼�������
void CChatCSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//��ִ�л����OnReceive����
	CSocket::OnReceive(nErrorCode);
	//�ٵ��öԻ������OnReceive����
	m_pDlg->OnReceive(this);
}

//��ʼ��
void CChatCSocket::Initialize()
{
	//�ڴ��׽�����CSocketFile����佨������
	m_pFile=new CSocketFile(this,TRUE);
	//��CSocketFile������CArchive����佨��������ʵ�ֶ�����
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	//��CSocketFile������CArchive����佨��������ʵ��д����
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
}

//������Ϣ
void CChatCSocket::SendMsg(CMsg *pMsg)
{
	if(m_pArchiveOut!=NULL){
		//������Ϣ������л�������������Ϣ
		pMsg->Serialize(* m_pArchiveOut);
		//��CArchive�����е�����ǿ����д��CSocketFile�ļ���
		m_pArchiveOut->Flush();
	}
}

//������Ϣ
void CChatCSocket::ReceiveMsg(CMsg *pMsg)
{
	//������Ϣ������л�������������Ϣ
	pMsg->Serialize(* m_pArchiveIn);
}

IMPLEMENT_DYNAMIC(CChatCSocket,CSocket)