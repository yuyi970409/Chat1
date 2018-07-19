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
//初始化成员变量
CChatCSocket::CChatCSocket(CChatRServerDlg * pDlg)
{
	m_pDlg=pDlg;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

//程序结束时释放各成员变量
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

//FD_READ事件处理函数
void CChatCSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	//先执行基类的OnReceive函数
	CSocket::OnReceive(nErrorCode);
	//再调用对话框类的OnReceive函数
	m_pDlg->OnReceive(this);
}

//初始化
void CChatCSocket::Initialize()
{
	//在此套接字与CSocketFile对象间建立关联
	m_pFile=new CSocketFile(this,TRUE);
	//在CSocketFile对象与CArchive对象间建立关联，实现读操作
	m_pArchiveIn = new CArchive(m_pFile,CArchive::load);
	//在CSocketFile对象与CArchive对象间建立关联，实现写操作
	m_pArchiveOut = new CArchive(m_pFile,CArchive::store);
}

//发送消息
void CChatCSocket::SendMsg(CMsg *pMsg)
{
	if(m_pArchiveOut!=NULL){
		//调用消息类的序列化函数，发送消息
		pMsg->Serialize(* m_pArchiveOut);
		//将CArchive对象中的数据强制性写入CSocketFile文件中
		m_pArchiveOut->Flush();
	}
}

//接收消息
void CChatCSocket::ReceiveMsg(CMsg *pMsg)
{
	//调用消息类的序列化函数，接收消息
	pMsg->Serialize(* m_pArchiveIn);
}

IMPLEMENT_DYNAMIC(CChatCSocket,CSocket)