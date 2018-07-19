// ServerDlg.h : header file
//

#if !defined(AFX_SERVERDLG_H__97F3E0E8_8216_4B7D_8494_54CB6CF57D46__INCLUDED_)
#define AFX_SERVERDLG_H__97F3E0E8_8216_4B7D_8494_54CB6CF57D46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CServerDlg dialog

#include "winsock.h"

#define WM_MYNID   (WM_USER + 5)
#define WM_WINSOCK (WM_USER + 100)

#pragma comment(lib, "ws2_32.lib")
#define MAX_SOCKET 1024

typedef struct _CLIENT
{
    SOCKET MY_SOCKET;
	SOCKADDR_IN clientAddr;
}STCLIENT;

class CServerDlg : public CDialog
{
// Construction
public:
	CStringList m_AllUser;
    STCLIENT MY_CLIENT[MAX_SOCKET];
    SOCKET m_serverSock;
    SOCKADDR_IN m_InternetAddr;
	CServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CServerDlg)
	enum { IDD = IDD_SERVER_DIALOG };
	CString	m_counter;
	CString	m_szInfo;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
//private:

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg void OnWINSOCK(WPARAM wParam, LPARAM lParam);
    afx_msg void OnClose();
	afx_msg void OnButtonClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERDLG_H__97F3E0E8_8216_4B7D_8494_54CB6CF57D46__INCLUDED_)
