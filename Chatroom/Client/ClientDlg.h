// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__5046BD58_1117_473A_9B3E_1F984EE6D879__INCLUDED_)
#define AFX_CLIENTDLG_H__5046BD58_1117_473A_9B3E_1F984EE6D879__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "ClientDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

#include "winsock.h"
#pragma comment(lib,"WS2_32")

#define WM_WINSOCK (WM_USER + 100)
#define MAX_SOCKET 1024

//extern CClientDlg theApp;
class CClientDlg : public CDialog
{
// Construction
private:
    CString SystemTime();
    void SetIPAddress();
    char* GetLocalIPAddress();

public:
    HINSTANCE m_hInstance;
    HACCEL m_hAccel;
    SOCKET mysocket;
    SOCKADDR_IN m_InternetAddr;
    CString   m_szIP;
    unsigned cnt;
    char* szIp;
    BOOL m_bFlag;

public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	CListCtrl	m_OnlineUserList;
	CEdit	m_edtHistory;
	CEdit	m_edtMsg;
	CEdit	m_edtNikename;
	CButton	m_btnSend;
	CButton	m_btnConnect;
	CIPAddressCtrl	m_ipaddrctrl;
	CString	m_szHistory;
	CString	m_szMsg;
	CString	m_szNikename;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	afx_msg void OnButtonConnect();
    afx_msg void OnWinsock(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__5046BD58_1117_473A_9B3E_1F984EE6D879__INCLUDED_)
