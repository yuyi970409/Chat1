// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__D7394F9B_E5DC_4F2F_9B2F_1B16ABF67D5F__INCLUDED_)
#define AFX_MSG_H__D7394F9B_E5DC_4F2F_9B2F_1B16ABF67D5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsg : public CObject  
{
	//动态类声明
	DECLARE_DYNCREATE(CMsg);

public:
	//自定义成员函数
	virtual void Serialize(CArchive& ar);
	//自定义成员变量
	BOOL m_bClose;				//是否为关闭状态
	CString m_strText;			//字符串成员
	
	//构造函数
	CMsg();
	//析构函数
	virtual ~CMsg();

};

#endif // !defined(AFX_MSG_H__D7394F9B_E5DC_4F2F_9B2F_1B16ABF67D5F__INCLUDED_)
