// ServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"

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
// CServerDlg dialog

CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerDlg)
	m_counter = _T("0");
	m_szInfo = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerDlg)
	DDX_Text(pDX, IDC_COUNTER, m_counter);
	DDX_Text(pDX, IDC_EDIT_CNTINFO, m_szInfo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialog)
	//{{AFX_MSG_MAP(CServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
    ON_MESSAGE(WM_WINSOCK, OnWINSOCK)
    ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerDlg message handlers

BOOL CServerDlg::OnInitDialog()
{
    BOOL flag;
    WSAData wsadata;
    int i;

    m_szInfo = "";

	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

    flag=TRUE;
    if ((i = WSAStartup(MAKEWORD(2, 2), &wsadata)) != 0) {
        AfxMessageBox("初始化失败");
        flag=FALSE;
        goto myexit;
    }
    //
    if ( (m_serverSock=socket(AF_INET,SOCK_DGRAM,0))==INVALID_SOCKET ) {
        AfxMessageBox("不能建立套接字!");
        flag=FALSE;
        goto myexit;
    }
    
    WSAAsyncSelect(m_serverSock,AfxGetMainWnd()->m_hWnd,WM_WINSOCK,FD_CLOSE|FD_READ);
    m_InternetAddr.sin_family=AF_INET;
    m_InternetAddr.sin_addr.s_addr=htonl(INADDR_ANY);
    m_InternetAddr.sin_port=htons(2000);
    
    if (bind(m_serverSock,(PSOCKADDR) &m_InternetAddr,sizeof(SOCKADDR))==SOCKET_ERROR) {
		int ret=WSAGetLastError();
		CString str;
		str.Format("%d", ret);
        AfxMessageBox(str);
        flag=FALSE;
        goto myexit;
    }
    
    for (i=0;i<MAX_SOCKET;i++) {
        MY_CLIENT[i].MY_SOCKET=INVALID_SOCKET;
    }
    m_counter="0";
    
myexit:
	// TODO: Add extra initialization here
    if (!flag) {
        CDialog::OnCancel();
    }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint() 
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CServerDlg::OnWINSOCK(WPARAM wParam, LPARAM lParam)
{
    int i,counter;
    char buffer[1024];

    UpdateData(TRUE);

    if (WSAGETSELECTERROR(lParam))
    {
        closesocket(SOCKET(wParam));
    }
    else
    {
        switch(WSAGETSELECTEVENT(lParam))
        {
        case FD_READ:
        {    
            UpdateData(TRUE);
            memset(buffer, 0, 1024);
			SOCKADDR_IN addrClient;
			int nLen = sizeof(SOCKADDR);
            recvfrom(SOCKET(wParam), buffer, 1024, 0, (PSOCKADDR) &addrClient, &nLen);

			CString strRecv(buffer);
			int posAdd = strRecv.Find(" 加入");
			int posRemove = strRecv.Find(" 离开");

			strcat(buffer, "\r\n");
			m_szInfo += CString(buffer);

			if(posAdd != -1)
			{
				for (i = 0; i < MAX_SOCKET; i++)
				{
					if (MY_CLIENT[i].MY_SOCKET == INVALID_SOCKET)
					{
						MY_CLIENT[i].MY_SOCKET = SOCKET(wParam);
						MY_CLIENT[i].clientAddr = addrClient;
						break;
					}
				}

				if (i == MAX_SOCKET)
				{
					break;
				}

				WSAAsyncSelect(MY_CLIENT[i].MY_SOCKET, AfxGetMainWnd()->m_hWnd,
					WM_WINSOCK, FD_READ | FD_CLOSE);
				counter = atoi(m_counter);
				counter++;
				m_counter.Format("%d", counter);

				//发送登陆消息
				POSITION pos;
            
				for( pos = m_AllUser.GetHeadPosition(); pos != NULL; )
				{
					CString s = "SYSTEM( Online ): " + m_AllUser.GetNext( pos ) + " 加入\r\n";
					LPSTR lp = s.GetBuffer(0);
					sendto(MY_CLIENT[i].MY_SOCKET, lp, strlen(lp), 0,
						(PSOCKADDR) &MY_CLIENT[i].clientAddr, sizeof(SOCKADDR));
				}
			}
			else if(posRemove != -1)
			{
				for (i = 0; i <MAX_SOCKET; ++i)
				{
					if (MY_CLIENT[i].MY_SOCKET == SOCKET(wParam))
					{
						MY_CLIENT[i].MY_SOCKET = INVALID_SOCKET;
					}
				}

				counter = atoi(m_counter);
				counter--;
				m_counter.Format("%d", counter);
			}

			UpdateData(FALSE);
			for (i = 0; i <MAX_SOCKET; ++i)
			{
				if (MY_CLIENT[i].MY_SOCKET != INVALID_SOCKET)
				{
					sendto(MY_CLIENT[i].MY_SOCKET, buffer, strlen(buffer), 0,
						(PSOCKADDR) &MY_CLIENT[i].clientAddr, sizeof(SOCKADDR));
				}
			}
            
			CString msg = buffer;
			int pos1 = msg.Find("): ");
			int pos2 = msg.Find(" 加入");
			if (pos1!=-1 && pos2!=-1) {
				pos1 += 3;
				CString user = msg.Mid(pos1, pos2-pos1);
				m_AllUser.AddTail(user);
			}
			pos2 = msg.Find(" 离开");
			if (pos1!=-1 && pos2!=-1) {
				pos1 += 3;
				CString leaveuser = msg.Mid(pos1, pos2-pos1);
				POSITION pos = m_AllUser.Find(leaveuser);
				if (NULL != pos) {
					m_AllUser.RemoveAt(pos);
				}
			}
        }
            break;

        case FD_CLOSE:
            for (i = 0; i<MAX_SOCKET; ++i)
            {
                if (MY_CLIENT[i].MY_SOCKET == INVALID_SOCKET)
                {
                    break;
                }
            }
            if (i == MAX_SOCKET)
            {
                break;
            }
            closesocket(MY_CLIENT[i].MY_SOCKET);
            MY_CLIENT[i].MY_SOCKET = INVALID_SOCKET;
            counter = atoi(m_counter);
            counter--;
            m_counter.Format("%d", counter);
            UpdateData(FALSE);
            break;
        }
    }
}

void CServerDlg::OnClose()
{
    
    int i;
    for (i = 0; i < MAX_SOCKET; i++)
    {
        if (MY_CLIENT[i].MY_SOCKET != INVALID_SOCKET)
        {
            closesocket(MY_CLIENT[i].MY_SOCKET);
        }
    }
    if (m_serverSock)
    {
        closesocket(m_serverSock);
    }
    WSACleanup();
    CDialog::OnClose();
}

void CServerDlg::OnButtonClear() 
{
	// TODO: Add your control notification handler code here
	m_szInfo = "";
    UpdateData(FALSE);
}
