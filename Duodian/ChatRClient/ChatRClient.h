// ChatRClient.h : main header file for the CHATRCLIENT application
//

#if !defined(AFX_CHATRCLIENT_H__36179AE3_7108_4E5C_9697_D659DCFF7765__INCLUDED_)
#define AFX_CHATRCLIENT_H__36179AE3_7108_4E5C_9697_D659DCFF7765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatRClientApp:
// See ChatRClient.cpp for the implementation of this class
//

class CChatRClientApp : public CWinApp
{
public:
	CChatRClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatRClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATRCLIENT_H__36179AE3_7108_4E5C_9697_D659DCFF7765__INCLUDED_)
