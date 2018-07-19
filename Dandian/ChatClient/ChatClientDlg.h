// ChatClientDlg.h : header file
//

#if !defined(AFX_CHATCLIENTDLG_H__1BEA1A48_F282_4885_812C_0C63B4A40C0A__INCLUDED_)
#define AFX_CHATCLIENTDLG_H__1BEA1A48_F282_4885_812C_0C63B4A40C0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChatSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CChatClientDlg dialog

class CChatClientDlg : public CDialog
{
// Construction
public:
	void OnDisConnect();
	void OnClose();
	void OnConnect();
	void OnReceive();

	CChatClientDlg(CWnd* pParent = NULL);	// standard constructor
	CChatSocket m_sConnectSocket;
// Dialog Data
	//{{AFX_DATA(CChatClientDlg)
	enum { IDD = IDD_CHATCLIENT_DIALOG };
	CListBox	m_Msg;
	CString	m_ServerName;
	int		m_ServerPort;
	CString	m_SendMsg;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnButtonDisconnect();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCLIENTDLG_H__1BEA1A48_F282_4885_812C_0C63B4A40C0A__INCLUDED_)
