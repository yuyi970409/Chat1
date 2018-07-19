// ChatRServer.h : main header file for the CHATRSERVER application
//

#if !defined(AFX_CHATRSERVER_H__B683F993_E279_4429_9015_AA720F95C898__INCLUDED_)
#define AFX_CHATRSERVER_H__B683F993_E279_4429_9015_AA720F95C898__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatRServerApp:
// See ChatRServer.cpp for the implementation of this class
//

class CChatRServerApp : public CWinApp
{
public:
	CChatRServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatRServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatRServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATRSERVER_H__B683F993_E279_4429_9015_AA720F95C898__INCLUDED_)
