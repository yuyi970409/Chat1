// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
extern CClientDlg theApp;
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
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
    m_szIP = _T("127.0.0.1");
	m_szHistory = _T("");
	m_szMsg = _T("");
	m_szNikename = _T("");
	m_bFlag = TRUE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_ONLINEUSER, m_OnlineUserList);
	DDX_Control(pDX, IDC_EDIT_HISTORY, m_edtHistory);
	DDX_Control(pDX, IDC_EDIT_MSG, m_edtMsg);
	DDX_Control(pDX, IDC_EDIT_NIKENAME, m_edtNikename);
	DDX_Control(pDX, IDOK, m_btnSend);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_IPADDRESS, m_ipaddrctrl);
	DDX_Text(pDX, IDC_EDIT_HISTORY, m_szHistory);
	DDX_Text(pDX, IDC_EDIT_MSG, m_szMsg);
	DDX_Text(pDX, IDC_EDIT_NIKENAME, m_szNikename);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
    ON_MESSAGE(WM_WINSOCK, OnWinsock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
    //SetFocus(hwndIPAddr);
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

    cnt = 0;
    m_btnSend.EnableWindow(FALSE);
    m_edtMsg.EnableWindow(FALSE);
    m_edtHistory.EnableWindow(FALSE);
    m_ipaddrctrl.SetAddress(127, 0, 0, 1);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnOK() 
{
	// TODO: Add extra validation here
    CString t;
    LPSTR ps;
    UpdateData(TRUE);
    t = m_szNikename + "(" + SystemTime() + ") \r\n" + m_szMsg;
    ps = t.GetBuffer(1024);
    sendto(mysocket, ps, strlen(ps), 0, (PSOCKADDR) &m_InternetAddr, sizeof(SOCKADDR));
    m_szMsg = "";
    UpdateData(FALSE);
}

void CClientDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
    
    if (MessageBox(_T("你想退出吗?"), _T("提示"), MB_OKCANCEL) == 1)
    {
        CString s = "SYSTEM(" + SystemTime() + "): " + m_szNikename + " 离开\r\n";
        LPSTR lp = s.GetBuffer(1024);
        sendto(mysocket, lp, strlen(lp), 0, (PSOCKADDR) &m_InternetAddr, sizeof(SOCKADDR));
        closesocket(mysocket);
        
        WSACleanup();
        
        CDialog::OnCancel();
    }
}

void CClientDlg::OnClose()
//直接最小化到托盘
{
	// TODO: Add your message handler code here and/or call default
    //if (mysocket != INVALID_SOCKET)
    //if (MessageBox(_T("Do you really want to exit?"), _T("Tips"), MB_OKCANCEL)
    //    == 1)

    CString s = "SYSTEM(" + SystemTime() + "): " + m_szNikename + " 离开\r\n";
    LPSTR lp = s.GetBuffer(1024);
    sendto(mysocket, lp, strlen(lp), 0, (PSOCKADDR) &m_InternetAddr, sizeof(SOCKADDR));
    closesocket(mysocket);
    
    WSACleanup();
    
    CDialog::OnCancel();

}

void CClientDlg::OnButtonConnect() 
{
	// TODO: Add your control notification handler code here
    BOOL flag;
    WSAData wsadata;
    SOCKADDR_IN InternetAddr;
    int i;
    CString m_counter;
    UpdateData(TRUE);

    unsigned char *pIP;
    DWORD   dwIP;

    
    cnt = m_ipaddrctrl.GetAddress(dwIP);
    pIP = (unsigned char*)&dwIP;
    m_szIP.Format("%u.%u.%u.%u", *(pIP+3), *(pIP+2), *(pIP+1), *pIP);
    
    if (cnt != 4) {
        AfxMessageBox("Invalid IP Address!");
        return;
    }
    
    if (m_szNikename.IsEmpty()) {
        AfxMessageBox("Nikename cannot be empty!");
        return;
    }
    flag = TRUE;
    if ((i = WSAStartup(MAKEWORD(2, 2), &wsadata)) != 0) {
        AfxMessageBox("初始化失败");
        flag = FALSE;
        goto myexit;
    }
    
    if ((mysocket = socket (AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        AfxMessageBox("Can't build up Winsock");
        flag = FALSE;
        goto myexit;
    }

    //Get the ip address from the control


    m_InternetAddr.sin_family = AF_INET;
    m_InternetAddr.sin_addr.s_addr = inet_addr(m_szIP);
    m_InternetAddr.sin_port = htons(2000);

    i = WSAAsyncSelect(mysocket, AfxGetMainWnd()->m_hWnd,
        WM_WINSOCK, FD_CLOSE | FD_READ);
    if (i == SOCKET_ERROR) {
        AfxMessageBox("Can't connect to server!");
        return;
    }
    
myexit:
    
    if (!flag) {
        CDialog::OnCancel();
    }
    else {
        m_edtHistory.EnableWindow(TRUE);
        m_edtMsg.EnableWindow(TRUE);
        m_btnSend.EnableWindow(TRUE);
        m_btnConnect.SetWindowText("Connected");
        m_ipaddrctrl.EnableWindow(FALSE);
        m_edtNikename.EnableWindow(FALSE);
        m_btnConnect.EnableWindow(FALSE);
        
        SetWindowText(m_szNikename);
        
        CString s = "SYSTEM(" + SystemTime() + "): " + m_szNikename + " 加入\r\n";
        LPSTR lp = s.GetBuffer(0);

		sendto(mysocket, lp, strlen(lp), 0, (PSOCKADDR) &m_InternetAddr, sizeof(SOCKADDR));
	}
}

void CClientDlg::OnWinsock(WPARAM wParam, LPARAM lParam)
{
    char buffer[1024];
    UpdateData(TRUE);
    if (WSAGETSELECTERROR(lParam)) {
        closesocket(SOCKET(wParam));
    }
    else {
        switch(WSAGETSELECTEVENT(lParam))
        {
        case FD_READ:
            {   
                memset(buffer, 0, 1024);

				SOCKADDR_IN serverAddr;
				int nLen = sizeof(SOCKADDR);
                recvfrom(SOCKET(wParam), (char*)buffer, 1024, 0, (PSOCKADDR) &serverAddr, &nLen);
                CString msg = buffer;
                
                int pos = 0, pos1, pos2;
                while((pos=msg.Find("\r\n", 0)) != -1)
                {
                    pos1 = msg.Find("): ");
                    pos2 = msg.Find(" 加入");
                    if (pos1!=-1 && pos2!=-1) {
                        pos1 += 3;
                        CString user = msg.Mid(pos1, pos2-pos1);
                        m_OnlineUserList.InsertItem(0, user);
                    }
                    pos2 = msg.Find(" 离开");
                    if (pos1!=-1 && pos2!=-1) {
                        pos1 += 3;
                        CString leaveuser = msg.Mid(pos1, pos2-pos1);
                        LVFINDINFO lf={0};
                        lf.flags = LVFI_STRING;
                        lf.psz = leaveuser.GetBuffer(0);
                        lf.vkDirection = VK_DOWN;
                        int nIndex = m_OnlineUserList.FindItem(&lf, -1);
                        if (-1 != nIndex) {
                            m_OnlineUserList.DeleteItem(nIndex);
                        }
                    }
                    pos += 2;
                    msg = msg.Mid(pos);
                }
                m_szHistory += CString(buffer);
                UpdateData(FALSE);
            }
            break;
            
        case FD_CLOSE:
            closesocket(mysocket);
            break;
        }
    }
}

CString CClientDlg::SystemTime()
{
    CTime time = CTime::GetCurrentTime();
    int year   = time.GetYear();
    int month  = time.GetMonth();
    int day    = time.GetDay();
    int hour   = time.GetHour();
    int minute = time.GetMinute();
    int second = time.GetSecond();
    
    CString yy, mm, dd, hh, min, ss, stime;
    yy.Format("%d", year);
    mm.Format("%d", month);
    dd.Format("%d", day);
    
    hh.Format("%d", hour);
    if (hour < 10) hh  = "0" + hh;
    
    min.Format("%d", minute);
    if (minute < 10) min  = "0" + min;
    
    ss.Format("%d", second);
    if (second < 10) ss = "0" + ss;
    
    stime = yy + "-" + mm + "-" + dd + "  " + hh + ":" + min + ":" + ss;

    return stime;
}

char* CClientDlg::GetLocalIPAddress()
{
    char szHost[256];
    
    gethostname(szHost, 256); // 取得本地主机名称
    
    hostent *pHost = gethostbyname(szHost); // 通过主机名得到地址信息
    
    in_addr addr;
    char *p = pHost->h_addr_list[0];
    if(p == NULL)
    {
        return NULL;
    }
    memcpy(&addr.S_un.S_addr, p, pHost->h_length);

    szIp = inet_ntoa(addr);

    return szIp;
}

void CClientDlg::SetIPAddress()
{
    GetLocalIPAddress();
    m_ipaddrctrl.SetAddress(*(szIp), *(szIp + 1), *(szIp + 2), *(szIp + 3));
}
