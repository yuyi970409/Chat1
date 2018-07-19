#if !defined(AFX_CHATCSOCKET_H__C626E150_451F_4452_B29F_B6B93B8F44BB__INCLUDED_)
#define AFX_CHATCSOCKET_H__C626E150_451F_4452_B29F_B6B93B8F44BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatCSocket.h : header file
//

class CMsg;
//class CChatCSocket;
class CChatRServerDlg;
/////////////////////////////////////////////////////////////////////////////
// CChatCSocket command target

class CChatCSocket : public CSocket
{
	//��̬������
	DECLARE_DYNAMIC(CChatCSocket);
// Attributes
public:

// Operations
public:
	//���캯�������Ҽ�������ڲ���
	CChatCSocket(CChatRServerDlg *pDlg);
	//��������
	virtual ~CChatCSocket();

// Overrides
public:
	void ReceiveMsg(CMsg * pMsg);
	void SendMsg(CMsg * pMsg);
	void Initialize();

	CArchive * m_pArchiveOut;		//���������CArchive����ָ�����
	CArchive * m_pArchiveIn;		//����������CArchive����ָ�����
	CSocketFile * m_pFile;			//����CSocketFile����ָ�����
	
	CChatRServerDlg * m_pDlg;		//����Ի�����ָ�����
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatCSocket)
	public:

	//����������ӵ��¼���Ӧ����
	virtual void OnReceive(int nErrorCode);   //��ӦFD_READ�¼�
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatCSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATCSOCKET_H__C626E150_451F_4452_B29F_B6B93B8F44BB__INCLUDED_)
