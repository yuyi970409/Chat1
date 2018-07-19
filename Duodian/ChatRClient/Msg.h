// Msg.h: interface for the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSG_H__7950F436_64B2_4C2E_8376_29FC72CED582__INCLUDED_)
#define AFX_MSG_H__7950F436_64B2_4C2E_8376_29FC72CED582__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsg : public CObject  
{
	DECLARE_DYNCREATE(CMsg)

public:
	virtual void Serialize(CArchive& ar);

	BOOL m_bClose;
	CString m_strText;

	CMsg();
	virtual ~CMsg();

};

#endif // !defined(AFX_MSG_H__7950F436_64B2_4C2E_8376_29FC72CED582__INCLUDED_)
