// ChatRClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRClient.h"
#include "ChatRClientDlg.h"
#include "Msg.h"
#include "ChatCSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatRClientDlg dialog

CChatRClientDlg::CChatRClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatRClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatRClientDlg)
	m_ServerName = _T("");
	m_ServerPort = 0;
	m_SendMsg = _T("");
	m_NickName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pSocket=NULL;
	m_pFile=NULL;
	m_pArchiveIn=NULL;
	m_pArchiveOut=NULL;
}

void CChatRClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatRClientDlg)
	DDX_Control(pDX, IDC_LIST_MSG, m_Msg);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_ServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT_SENDMSG, m_SendMsg);
	DDX_Text(pDX, IDC_EDIT_NICKNAME, m_NickName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatRClientDlg, CDialog)
	//{{AFX_MSG_MAP(CChatRClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatRClientDlg message handlers

BOOL CChatRClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_NickName="游客";
	//初始化服务名称为“localhost”
	m_ServerName="localhost";
	//初始化服务器端口为3030
	m_ServerPort=3030;
	//刷新程序主界面上控件显示的数据
	UpdateData(FALSE);
	
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatRClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatRClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatRClientDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	//创建侦听套接字
	m_pSocket=new CChatCSocket(this);
	//在指定端口上创建侦听套接字对象的底层套接字
	if(!m_pSocket->Create()){
		//出错处理
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox("套接字创建错误！");
		return;
	}
	//开始侦听客户端的连接请求
	if(!m_pSocket->Connect(m_ServerName,m_ServerPort)){
		delete m_pSocket;
		m_pSocket=NULL;
		AfxMessageBox("连接服务器错误！");
		return;
	}

	m_pFile=new CSocketFile(m_pSocket);
	m_pArchiveIn=new CArchive(m_pFile,CArchive::load);
	m_pArchiveOut=new CArchive(m_pFile,CArchive::store);

	UpdateData(TRUE);
	CString strTemp;
	strTemp=m_NickName+":进入聊天室!";
	SendMsg(strTemp,FALSE);
	m_Msg.AddString(strTemp);

	
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_NICKNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
}

void CChatRClientDlg::OnButtonDisconnect() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	strTemp=m_NickName+":离开聊天室!";
	SendMsg(strTemp,TRUE);
	delete m_pArchiveOut;
	m_pArchiveOut=NULL;
	delete m_pArchiveIn;
	m_pArchiveIn=NULL;
	delete m_pFile;
	m_pFile=NULL;
	m_pSocket->Close();
	delete m_pSocket;
	m_pSocket=NULL;

	while(m_Msg.GetCount()!=0){
		m_Msg.DeleteString(0);
	}

	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);

	while(m_Msg.GetCount()!=0) m_Msg.DeleteString(0);

	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_NICKNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);


}


void CChatRClientDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	if((m_pSocket!=NULL)&&(m_pFile!=NULL)&&(m_pArchiveOut!=NULL)){
		CMsg msg;
		msg.m_bClose=TRUE;
		msg.m_strText=m_NickName+":离开聊天室!";
		msg.Serialize(* m_pArchiveOut);
		m_pArchiveOut->Flush();
	}

	delete m_pArchiveOut;
	m_pArchiveOut=NULL;
	delete m_pArchiveIn;
	m_pArchiveIn=NULL;
	delete m_pFile;
	m_pFile=NULL;
	if(m_pSocket!=NULL){
		m_pSocket->Close();
	}
	delete m_pSocket;
	m_pSocket=NULL;

	CDialog::OnOK();
}

void CChatRClientDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	if(!m_SendMsg.IsEmpty()){
		CString strTemp;
		strTemp=m_NickName+":"+m_SendMsg;
		this->SendMsg(strTemp,FALSE);
		m_Msg.AddString(strTemp);
		m_SendMsg=_T("");
		UpdateData(FALSE);
	}
}

void CChatRClientDlg::OnReceive()
{
	do{
		ReceiveMsg();
		if(m_pSocket==NULL) return;
	}while(!m_pArchiveIn->IsBufferEmpty());
}

void CChatRClientDlg::ReceiveMsg()
{
	CMsg msg;
	TRY{
		msg.Serialize(* m_pArchiveIn);
		m_Msg.AddString(msg.m_strText);
	}
	CATCH(CFileException,e){
		CString strTemp;
		strTemp="与服务器的连接被关闭!";
		m_Msg.AddString(strTemp);
		msg.m_bClose=TRUE;
		m_pArchiveOut->Abort();

		delete m_pArchiveOut;
		m_pArchiveOut=NULL;
		delete m_pArchiveIn;
		m_pArchiveIn=NULL;
		delete m_pFile;
		m_pFile=NULL;
		m_pSocket->Close();
		delete m_pSocket;
		m_pSocket=NULL;
	}
	END_CATCH
}

void CChatRClientDlg::SendMsg(CString &strText, BOOL st)
{
	if(m_pArchiveOut!=NULL){
		CMsg msg;
		msg.m_strText=strText;
		msg.m_bClose=st;
		msg.Serialize(* m_pArchiveOut);
		m_pArchiveOut->Flush();
	}
}
