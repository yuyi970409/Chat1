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

//定义侦听套接字
class CChatLSocket : public CSocket
{
	//动态类声明
	DECLARE_DYNAMIC(CChatLSocket);

// Attributes
public:

// Operations
public:
	//构造函数,并且加入了入口参数
	CChatLSocket(CChatRServerDlg *pDlg);
	//析构函数
	virtual ~CChatLSocket();

// Overrides
public:
	CChatRServerDlg * m_pDlg;		//定义对话框类指针变量
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatLSocket)
	public:

	//从类向导中添加的时间响应函数
	virtual void OnAccept(int nErrorCode);   //响应FD_ACCEPT事件
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
