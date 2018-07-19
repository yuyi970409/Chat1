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
	//���򵼶Կؼ�������ʼ��
	m_ServerName = _T("");
	m_ServerPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//��Ա������ʼ��
	m_sListenSocket=NULL;
}

void CChatRServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatRServerDlg)
	//�����ڿؼ�����Ӧ����֮�佨��ӳ��
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
	//�����ڿؼ���Ϣ����Ӧ���¼�������֮�佨��ӳ��
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
	//��ʼ����������Ϊ��localhost��
	m_ServerName="localhost";
	//��ʼ���������˿�Ϊ3030
	m_ServerPort=3030;
	//ˢ�³����������Ͽؼ���ʾ������
	UpdateData(FALSE);
	//���÷�������������ؼ�
	GetDlgItem(IDC_EDIT_SERVERNAME)->EnableWindow(FALSE);
	//���á���ֹ����ť
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

//����������������ť�ĵ����¼�
void CChatRServerDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	//��ȡ�Ի�������
	UpdateData(TRUE);
	//���������׽���
	m_sListenSocket=new CChatLSocket(this);
	//��ָ���˿��ϴ��������׽��ֶ���ĵײ��׽���
	if(!m_sListenSocket->Create(m_ServerPort)){
		//������
		delete m_sListenSocket;
		m_sListenSocket=NULL;
		AfxMessageBox("���������׽��ִ���");
		return;
	}
	//��ʼ�����ͻ��˵���������
	if(!m_sListenSocket->Listen()){
		delete m_sListenSocket;
		m_sListenSocket=NULL;
		AfxMessageBox("������������");
		return;
	}
	//���á���������ť
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(FALSE);
	//���÷������˿�����ؼ�
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(FALSE);
	//�����ֹ����ť
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(TRUE);
}

//���������˳�����ť�ĵ����¼�
void CChatRServerDlg::OnButtonExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

//����������ֹ����ť�ĵ����¼�
void CChatRServerDlg::OnButtonStop() 
{
	// TODO: Add your control notification handler code here
	CMsg msg;
	msg.m_strText="��������ֹ����";
	//ɾ�������׽���
	delete m_sListenSocket;
	m_sListenSocket=NULL;
	
	//�������б���д���
	while(!m_cList.IsEmpty()){
		//֪ͨ���������ӵĿͻ��˷���������ֹ���ͷ�����
		CChatCSocket * pSocket=(CChatCSocket *)m_cList.RemoveHead();
		pSocket->SendMsg(&msg);
		delete pSocket;
	}
	
	//���������Ϣ��
	while(m_Msg.GetCount()!=0)
		m_Msg.DeleteString(0);

	//���á���ֹ����ť
	GetDlgItem(IDC_BUTTON_STOP)->EnableWindow(FALSE);
	//�����������ť
	GetDlgItem(IDC_BUTTON_START)->EnableWindow(TRUE);
	//����������˿�����ؼ�
	GetDlgItem(IDC_EDIT_SERVERPORT)->EnableWindow(TRUE);
}

//���յ���������ʱ���׽������OnAccept���������ô˺���
void CChatRServerDlg::OnAccept()
{
	//���������׽��ֶ���
	CChatCSocket * pSocket=new CChatCSocket(this);
	//���տͻ�����������
	if(m_sListenSocket->Accept(* pSocket)){
		//��ʼ�������׽��ֶ���
		pSocket->Initialize();
		//���������׽��ֶ�������׽����б�
		m_cList.AddTail(pSocket);

		//ˢ����������
		CString strTemp;
		strTemp.Format("����������%d",m_cList.GetCount());
		m_Num.SetWindowText(strTemp);
	}else{
		//ʧ��ʱ�ͷ���Դ
		delete pSocket;
	}
}

//���յ�����ʱ���׽������OnReceive���������ô˺���
void CChatRServerDlg::OnReceive(CChatCSocket *pSocket)
{
	static CMsg msg;
	do{
		//���տͻ��˷�������Ϣ
		pSocket->ReceiveMsg(&msg);
		//������Ϣ��ʾ��������Ϣ��
		m_Msg.AddString(msg.m_strText);
		//������Ϣת���������ͻ���
		ForwardMsg(pSocket,&msg);

		//����ͻ����ѹرգ�����б���ɾ����˿ͻ��˵�����
		if(msg.m_bClose){
			pSocket->Close();
			POSITION pos,temp;

			//���б��в�����Ӧ����
			for(pos=m_cList.GetHeadPosition();pos!=NULL;){
				temp=pos;
				CChatCSocket * pSock = (CChatCSocket *)m_cList.GetNext(pos);

				//�ж��Ƿ��ҵ�
				if(pSock == pSocket){
					//���ҵ�������б���ɾ��������
					m_cList.RemoveAt(temp);
					CString strTemp;

					//ˢ����������
					strTemp.Format("����������%d",m_cList.GetCount());
					m_Num.SetWindowText(strTemp);
					break;
				}
			}
			//ͬʱ�ͷ���Դ
			delete pSocket;
			break;
		}
	}while(!pSocket->m_pArchiveIn->IsBufferEmpty());
}

//���յ�����Ϣת���������ͻ���
void CChatRServerDlg::ForwardMsg(CChatCSocket *pSocket, CMsg *pMsg)
{
	for(POSITION pos=m_cList.GetHeadPosition();pos!=NULL;){
		//���ζ�ȡ��������
		CChatCSocket * pSock=(CChatCSocket *)m_cList.GetNext(pos);
		//�жϵ�ǰ���ӵĿͻ����ǲ�����ϢԴ
		if(pSock!=pSocket)
			//�����ǣ���ת����Ϣ
			pSock->SendMsg(pMsg);
	}
}
