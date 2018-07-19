// ChatRServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChatRServer.h"
#include "ChatRServerDlg.h"

#include "Msg.h"
#include "ChatCSocket.h"
#include "ChatLSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatRServerDlg dialog

CChatRServerDlg::CChatRServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatRServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatRServerDlg)
	//类向导对控件变量初始化
	m_ServerName = _T("");
	m_ServerPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//成员变量初始化
	m_sListenSocket=NULL;
}

void CChatRServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatRServerDlg)
	//类向导在控件与相应变量之间建立映射
	DDX_Control(pDX, IDC_STATIC_NUM, m_Num);
	DDX_Control(pDX, IDC_LIST_MSG, m_Msg);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_ServerName);
	DDX_Text(pDX, IDC_EDIT_SERVERPORT, m_ServerPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatRServerDlg, CDialog)
	//{{AFX_MSG_MAP(CChatRServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//类向导在控件消息与相应的事件处理函数之间建立映射
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_STOP, OnButtonStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatRServerDlg message handlers

BOOL CChatRServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//初始化服务名称为“localhost”
	m_ServerName="localhost";
	//初始化服务器端口为3030
	m_ServerPort=3030;
	//刷新程序主界面上控件显示的数据
	UpdateData(FALSE);
	//禁用服务器名称输入控件
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	//禁用“终止”按钮
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatRServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatRServerDlg::OnPaint() 
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
HCURSOR CChatRServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//用来处理“启动”按钮的单击事件
void CChatRServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	//获取对话框数据
	UpdateData(TRUE);
	//创建侦听套接字
	m_sListenSocket=new CChatLSocket(this);
	//在指定端口上创建侦听套接字对象的底层套接字
	if(!m_sListenSocket->Create(m_ServerPort)){
		//出错处理
		delete m_sListenSocket;
		m_sListenSocket=NULL;
		AfxMessageBox("创建侦听套接字错误！");
		return;
	}
	//开始侦听客户端的连接请求
	if(!m_sListenSocket->Listen()){
		delete m_sListenSocket;
		m_sListenSocket=NULL;
		AfxMessageBox("启动侦听错误！");
		return;
	}
	//禁用“启动”按钮
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//禁用服务器端口输入控件
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	//激活“终止”按钮
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

//用来处理“退出”按钮的单击事件
void CChatRServerDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

//用来处理“终止”按钮的单击事件
void CChatRServerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	CMsg msg;
	msg.m_strText="服务器终止服务！";
	//删除侦听套接字
	delete m_sListenSocket;
	m_sListenSocket=NULL;
	
	//对连接列表进行处理
	while(!m_cList.IsEmpty()){
		//通知所有已连接的客户端服务器已终止并释放连接
		CChatCSocket * pSocket=(CChatCSocket *)m_cList.RemoveHead();
		pSocket->SendMsg(&msg);
		delete pSocket;
	}
	
	//清空聊天信息栏
	while(m_Msg.GetCount()!=0)
		m_Msg.DeleteString(0);

	//禁用“终止”按钮
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	//激活“启动”按钮
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	//激活服务器端口输入控件
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
}

//当收到连接请求时，套接字类的OnAccept函数将调用此函数
void CChatRServerDlg::OnAccept()
{
	//创建连接套接字对象
	CChatCSocket * pSocket=new CChatCSocket(this);
	//接收客户的连接请求
	if(m_sListenSocket->Accept(* pSocket)){
		//初始化连接套接字对象
		pSocket->Initialize();
		//将此连接套接字对象加入套接字列表
		m_cList.AddTail(pSocket);

		//刷新在线人数
		CString strTemp;
		strTemp.Format("在线人数：%d",m_cList.GetCount());
		m_Num.SetWindowText(strTemp);
	}else{
		//失败时释放资源
		delete pSocket;
	}
}

//当收到数据时，套接字类的OnReceive函数将调用此函数
void CChatRServerDlg::OnReceive(CChatCSocket *pSocket)
{
	static CMsg msg;
	do{
		//接收客户端发来的信息
		pSocket->ReceiveMsg(&msg);
		//将此信息显示在聊天信息栏
		m_Msg.AddString(msg.m_strText);
		//将此信息转发给其他客户端
		ForwardMsg(pSocket,&msg);

		//如果客户端已关闭，则从列表中删除与此客户端的连接
		if(msg.m_bClose){
			pSocket->Close();
			POSITION pos,temp;

			//在列表中查找相应连接
			for(pos=m_cList.GetHeadPosition();pos!=NULL;){
				temp=pos;
				CChatCSocket * pSock = (CChatCSocket *)m_cList.GetNext(pos);

				//判断是否找到
				if(pSock == pSocket){
					//若找到，则从列表中删除此连接
					m_cList.RemoveAt(temp);
					CString strTemp;

					//刷新在线人数
					strTemp.Format("在线人数：%d",m_cList.GetCount());
					m_Num.SetWindowText(strTemp);
					break;
				}
			}
			//同时释放资源
			delete pSocket;
			break;
		}
	}while(!pSocket->m_pArchiveIn->IsBufferEmpty());
}

//将收到的信息转发给其他客户端
void CChatRServerDlg::ForwardMsg(CChatCSocket *pSocket, CMsg *pMsg)
{
	for(POSITION pos=m_cList.GetHeadPosition();pos!=NULL;){
		//依次读取各个连接
		CChatCSocket * pSock=(CChatCSocket *)m_cList.GetNext(pos);
		//判断当前连接的客户端是不是信息源
		if(pSock!=pSocket)
			//若不是，则转发信息
			pSock->SendMsg(pMsg);
	}
}
