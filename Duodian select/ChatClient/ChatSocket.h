#if !defined(AFX_CHATSOCKET_H__F785B00B_ACD5_4D19_BCA4_33A050DF4973__INCLUDED_)
#define AFX_CHATSOCKET_H__F785B00B_ACD5_4D19_BCA4_33A050DF4973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChatSocket.h : header file
//

class CChatClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CChatSocket command target

class CChatSocket : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CChatSocket();
	virtual ~CChatSocket();

// Overrides
public:
	void SetParent(CChatClientDlg * pDlg);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatSocket)
	public:
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CChatSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	CChatClientDlg * m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATSOCKET_H__F785B00B_ACD5_4D19_BCA4_33A050DF4973__INCLUDED_)
