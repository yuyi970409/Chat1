// ChatRClientDlg.h : header file
//

#if !defined(AFX_CHATRCLIENTDLG_H__9E24F50A_1ADB_4553_8439_A8F48A92E907__INCLUDED_)
#define AFX_CHATRCLIENTDLG_H__9E24F50A_1ADB_4553_8439_A8F48A92E907__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatRClientDlg dialog
class CChatCSocket;

class CChatRClientDlg : public CDialog
{
// Construction
public:
	void SendMsg(CString& strText,BOOL st);
	void ReceiveMsg();
	void OnReceive();

	CChatRClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatRClientDlg)
	enum { IDD = IDD_CHATRCLIENT_DIALOG };
	CListBox	m_Msg;
	CString	m_ServerName;
	int		m_ServerPort;
	CString	m_SendMsg;
	CString	m_NickName;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CArchive * m_pArchiveOut;
	CArchive * m_pArchiveIn;
	CSocketFile * m_pFile;
	CChatCSocket * m_pSocket;

	// Generated message map functions
	//{{AFX_MSG(CChatRClientDlg)
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

#endif // !defined(AFX_CHATRCLIENTDLG_H__9E24F50A_1ADB_4553_8439_A8F48A92E907__INCLUDED_)
