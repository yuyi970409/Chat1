// ChatClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg dialog

CChatClientDlg::CChatClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatClientDlg)
	m_ServerName = _T("");
	m_ServerPort = 0;
	m_SendMsg = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatClientDlg)
	DDX_Control(pDX, IDC_LIST_MSG, m_Msg);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_ServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_ServerPort);
	DDX_Text(pDX, IDC_EDIT_SENDMSG, m_SendMsg);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialog)
	//{{AFX_MSG_MAP(CChatClientDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_DISCONNECT, OnButtonDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_SEND, OnButtonSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg message handlers

BOOL CChatClientDlg::OnInitDialog()
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
	m_sConnectSocket.SetParent(this);
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatClientDlg::OnPaint() 
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
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CChatClientDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);	
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(TRUE);
	m_sConnectSocket.Create();
	m_sConnectSocket.Connect(m_ServerName,m_ServerPort);
}

void CChatClientDlg::OnButtonDisconnect() 
{
	// TODO: Add your control notification handler code here
	OnClose();
}

void CChatClientDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CChatClientDlg::OnButtonSend() 
{
	// TODO: Add your control notification handler code here
	int nLen;
	int nSent;
	UpdateData(TRUE);
	if(!m_SendMsg.IsEmpty()){
		nLen=m_SendMsg.GetLength();
		nSent=m_sConnectSocket.Send(LPCTSTR(m_SendMsg),nLen);
		if(nSent!=SOCKET_ERROR){
			m_Msg.AddString("�ͻ���:"+m_SendMsg);
			UpdateData(FALSE);
		}else{
			AfxMessageBox("����ʧ�ܣ�",MB_OK|MB_ICONSTOP);
		}
		m_SendMsg.Empty();
		UpdateData(FALSE);
	}
}

void CChatClientDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(TRUE);
	m_Msg.AddString("���������ͨ�������Ѿ�����");
}

void CChatClientDlg::OnClose()
{
	// TODO: Add your control notification handler code here
	m_sConnectSocket.Close();
	GetDlgItem(IDC_EDIT_SENDMSG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_SEND)->EnableWindow(FALSE);	
	GetDlgItem(IDC_BUTTON_DISCONNECT)->EnableWindow(FALSE);
	while(m_Msg.GetCount()!=0) m_Msg.DeleteString(0);
	GetDlgItem(IDC_BUTTON_CONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
}

void CChatClientDlg::OnReceive() 
{
	// TODO: Add your control notification handler code here
	char * pBuf = new char[1025];
	int nBufSize = 1024;
	int nReceived;
	CString strReceived;

/*	nReceived=m_sConnectSocket.Receive(pBuf,nBufSize);
	if(nReceived!=SOCKET_ERROR){
		pBuf[nReceived]=NULL;
		strReceived=pBuf;
		m_Msg.AddString("�����:"+strReceived);
		UpdateData(FALSE);
	}else{
		AfxMessageBox("����ʧ��!",MB_OK|MB_ICONSTOP);
	}*/
	
	fd_set readfds;
	int ret;

	FD_ZERO(&readfds);
	FD_SET(m_sConnectSocket,&readfds);
	if((ret=select(0,&readfds,NULL,NULL,NULL))==SOCKET_ERROR){
		AfxMessageBox("����ʧ�ܣ�",MB_OK|MB_ICONSTOP);
	}

	if(ret>0){
		if(FD_ISSET(m_sConnectSocket,&readfds)){
			nReceived=m_sConnectSocket.Receive(pBuf,nBufSize);

			if(nReceived!=SOCKET_ERROR){
				pBuf[nReceived]=NULL;
				strReceived=pBuf;
				m_Msg.AddString("�����:"+strReceived);

				UpdateData(FALSE);
			}else{
				AfxMessageBox("����ʧ�ܣ�",MB_OK|MB_ICONSTOP);
			}
		}
	}
}