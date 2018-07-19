// ChatServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg dialog

CChatServerDlg::CChatServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatServerDlg)
	m_SendMsg = _T("");
	m_ServerPort = 0;
	m_ServerName = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatServerDlg)
	DDX_Control(pDX, IDC_LIST_MSG, m_Msg);
	DDX_Text(pDX, IDC_EDIT_SENDMSG, m_SendMsg);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_ServerName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialog)
	//{{AFX_MSG_MAP(CChatServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg message handlers

BOOL CChatServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_ServerName="localhost";
	m_ServerPort=3030;
	UpdateData(FALSE);
	m_sListenSocket.SetParent(this);
	m_sConnectSocket.SetParent(this);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatServerDlg::OnPaint() 
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatServerDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CChatServerDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	int nLen;
	int nSent;
	UpdateData(TRUE);
	if(!m_SendMsg.IsEmpty()){
		nLen=m_SendMsg.GetLength();
		nSent=m_sConnectSocket.Send(LPCTSTR(m_SendMsg),nLen);
		if(nSent!=SOCKET_ERROR){
			m_Msg.AddString("服务端:"+m_SendMsg);
			UpdateData(FALSE);
		}else{
			AfxMessageBox("发送失败！",MB_OK|MB_ICONSTOP);
		}
		m_SendMsg.Empty();
		UpdateData(FALSE);
	}
}

void CChatServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);	
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
	m_sListenSocket.Create(m_ServerPort);
	m_sListenSocket.Listen();
}

void CChatServerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	m_sListenSocket.Close();
	m_sConnectSocket.Close();
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	while(m_Msg.GetCount()!=0) m_Msg.DeleteString(0);
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
}

void CChatServerDlg::OnAccept() 
{
	// TODO: Add your control notification handler code here
	m_sListenSocket.Accept(m_sConnectSocket);
	m_Msg.AddString("客户端与服务器的通信已经建立");
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
}

void CChatServerDlg::OnReceive()
{
	char * pBuf = new char[1025];
	int nBufSize = 1024;
	int nReceived;
	CString strReceived;
	nReceived=m_sConnectSocket.Receive(pBuf,nBufSize);
	if(nReceived!=SOCKET_ERROR){
		pBuf[nReceived]=NULL;
		strReceived=pBuf;
		m_Msg.AddString("客户端:("+")"+strReceived);
		UpdateData(FALSE);
	}else{
		AfxMessageBox("接收失败！",MB_OK|MB_ICONSTOP);
	}
}

void CChatServerDlg::OnClose()
{
	m_sConnectSocket.Close();
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);	
	while(m_Msg.GetCount()!=0) m_Msg.DeleteString(0);
}
