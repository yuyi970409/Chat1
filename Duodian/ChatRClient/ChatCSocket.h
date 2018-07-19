#if !defined(AFX_CHATCSOCKET_H__E3B9C289_08A5_48EE_9AA1_F7787736CFF2__INCLUDED_)
#define AFX_CHATCSOCKET_H__E3B9C289_08A5_48EE_9AA1_F7787736CFF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatCSocket.h : header file
//

class CChatRClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CChatCSocket command target

class CChatCSocket : public CSocket
{
	DECLARE_DYNAMIC(CChatCSocket);

// Attributes
public:

// Operations
public:
	CChatCSocket(CChatRClientDlg * pDlg);
	virtual ~CChatCSocket();

// Overrides
public:
	CChatRClientDlg * m_pDlg;
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatCSocket)
	public:
	virtual void OnReceive(int nErrorCode);
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

#endif // !defined(AFX_CHATCSOCKET_H__E3B9C289_08A5_48EE_9AA1_F7787736CFF2__INCLUDED_)
