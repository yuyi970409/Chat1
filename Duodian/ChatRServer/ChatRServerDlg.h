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
	//�Զ����Ա����
	void ForwardMsg(CChatCSocket * pSocket,CMsg * pMsg);
	void OnReceive(CChatCSocket * pSocket);
	void OnAccept();
	//�Զ����Ա����
	CPtrList m_cList;							//���������б����	
	CChatLSocket * m_sListenSocket;				//���������׽���ָ�����
	
	CChatRServerDlg(CWnd* pParent = NULL);		// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatRServerDlg)
	enum { IDD = IDD_CHATRSERVER_DIALOG };		
	CStatic	m_Num;								//���ڲ�����ʾ���������ľ�̬�ı���
	CListBox	m_Msg;							//���ڲ���������Ϣ�б��
	CString	m_ServerName;						//���ڷ��ʷ���������
	int		m_ServerPort;						//���ڷ��ʷ������˿�
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
	//���������ɵĴ���ť�����¼�����Ϣӳ�亯��
	afx_msg void OnButtonStart();			//������������ť����ʱ����
	afx_msg void OnButtonExit();			//�����˳�����ť����ʱ����
	afx_msg void OnButtonStop();			//������ֹ����ť����ʱ����
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATRSERVERDLG_H__B26BAAEE_604B_4357_837A_95D1E5F9B0F8__INCLUDED_)
