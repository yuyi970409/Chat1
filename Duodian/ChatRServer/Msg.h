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
	//��̬������
	DECLARE_DYNCREATE(CMsg);

public:
	//�Զ����Ա����
	virtual void Serialize(CArchive& ar);
	//�Զ����Ա����
	BOOL m_bClose;				//�Ƿ�Ϊ�ر�״̬
	CString m_strText;			//�ַ�����Ա
	
	//���캯��
	CMsg();
	//��������
	virtual ~CMsg();

};

#endif // !defined(AFX_MSG_H__D7394F9B_E5DC_4F2F_9B2F_1B16ABF67D5F__INCLUDED_)
