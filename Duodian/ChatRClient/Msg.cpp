// Msg.cpp: implementation of the CMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChatRClient.h"
#include "Msg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMsg::CMsg()
{
	m_strText=_T("");
	m_bClose=FALSE;
}

CMsg::~CMsg()
{

}

void CMsg::Serialize(CArchive &ar)
{
	//判断是输入还是输出，若是输入则发送数据，否则接收数据
	if(ar.IsStoring()){
		//若为输出，则发送数据
		ar<<(WORD)m_bClose;
		ar<<m_strText;
	}else{
		//否则接收数据
		WORD wd;
		ar>>wd;
		m_bClose=(BOOL)wd;
		ar>>m_strText;
	}

}

IMPLEMENT_DYNAMIC(CMsg,CObject)