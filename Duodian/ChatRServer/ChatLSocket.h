#if !defined(AFX_CHATLSOCKET_H__37875DC9_B112_4623_9690_BED543930461__INCLUDED_)
#define AFX_CHATLSOCKET_H__37875DC9_B112_4623_9690_BED543930461__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatLSocket.h : header file
//

class CChatRServerDlg;

/////////////////////////////////////////////////////////////////////////////
// CChatLSocket command target

//���������׽���
class CChatLSocket : public CSocket
{
	//��̬������
	DECLARE_DYNAMIC(CChatLSocket);

// Attributes
public:

// Operations
public:
	//���캯��,���Ҽ�������ڲ���
	CChatLSocket(CChatRServerDlg *pDlg);
	//��������
	virtual ~CChatLSocket();

// Overrides
public:
	CChatRServerDlg * m_pDlg;		//����Ի�����ָ�����
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatLSocket)
	public:

	//����������ӵ�ʱ����Ӧ����
	virtual void OnAccept(int nErrorCode);   //��ӦFD_ACCEPT�¼�
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatLSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATLSOCKET_H__37875DC9_B112_4623_9690_BED543930461__INCLUDED_)
