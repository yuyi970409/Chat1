// ChatServerDlg.h : header file
//

#if !defined(AFX_CHATSERVERDLG_H__85B184F2_2DB8_4C42_AFD1_71024F1C5DD0__INCLUDED_)
#define AFX_CHATSERVERDLG_H__85B184F2_2DB8_4C42_AFD1_71024F1C5DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ChatSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CChatServerDlg dialog

class CChatServerDlg : public CDialog
{
// Construction
public:
	void OnClose();
	void OnReceive();
	void OnAccept();

	CChatSocket m_sConnectSocket;
	CChatSocket m_sListenSocket;
	CChatServerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatServerDlg)
	enum { IDD = IDD_CHATSERVER_DIALOG };
	CListBox	m_Msg;
	CString	m_SendMsg;
	int		m_ServerPort;
	CString	m_ServerName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonExit();
	afx_msg void OnButtonSend();
	afx_msg void OnButtonStart();
	afx_msg void OnButtonStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSERVERDLG_H__85B184F2_2DB8_4C42_AFD1_71024F1C5DD0__INCLUDED_)
