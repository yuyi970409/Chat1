// ChatRServerDlg.h : header file
//

#if !defined(AFX_CHATRSERVERDLG_H__B26BAAEE_604B_4357_837A_95D1E5F9B0F8__INCLUDED_)
#define AFX_CHATRSERVERDLG_H__B26BAAEE_604B_4357_837A_95D1E5F9B0F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CChatRServerDlg dialog

class CChatCSocket;
class CChatLSocket;
class CMsg;

class CChatRServerDlg : public CDialog
{
// Construction
public:
	//自定义成员函数
	void ForwardMsg(CChatCSocket * pSocket,CMsg * pMsg);
	void OnReceive(CChatCSocket * pSocket);
	void OnAccept();
	//自定义成员变量
	CPtrList m_cList;							//定义连接列表变量	
	CChatLSocket * m_sListenSocket;				//定义侦听套接字指针变量
	
	CChatRServerDlg(CWnd* pParent = NULL);		// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatRServerDlg)
	enum { IDD = IDD_CHATRSERVER_DIALOG };		
	CStatic	m_Num;								//用于操作显示在线人数的静态文本框
	CListBox	m_Msg;							//用于操作聊天信息列表框
	CString	m_ServerName;						//用于访问服务器名称
	int		m_ServerPort;						//用于访问服务器端口
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatRServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//由类向导生成的处理按钮单击事件的消息映射函数
	afx_msg void OnButtonStart();			//当“启动”按钮按下时调用
	afx_msg void OnButtonExit();			//当“退出”按钮按下时调用
	afx_msg void OnButtonStop();			//当“终止”按钮按下时调用
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATRSERVERDLG_H__B26BAAEE_604B_4357_837A_95D1E5F9B0F8__INCLUDED_)
