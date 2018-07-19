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
	//动态类声明
	DECLARE_DYNAMIC(CChatCSocket);
// Attributes
public:

// Operations
public:
	//构造函数，并且加入了入口参数
	CChatCSocket(CChatRServerDlg *pDlg);
	//析构函数
	virtual ~CChatCSocket();

// Overrides
public:
	void ReceiveMsg(CMsg * pMsg);
	void SendMsg(CMsg * pMsg);
	void Initialize();

	CArchive * m_pArchiveOut;		//定义输出型CArchive对象指针变量
	CArchive * m_pArchiveIn;		//定义输入型CArchive对象指针变量
	CSocketFile * m_pFile;			//定义CSocketFile对象指针变量
	
	CChatRServerDlg * m_pDlg;		//定义对话框类指针变量
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatCSocket)
	public:

	//从类向导中添加的事件响应函数
	virtual void OnReceive(int nErrorCode);   //响应FD_READ事件
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
