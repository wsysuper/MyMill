#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"
#include "resource.h"

// setDlg dialog

class setDlg : public CDialogEx
{
	DECLARE_DYNAMIC(setDlg)

public:
	setDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~setDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox selectCtrl;
	CMFCColorButton colorCtrl;
	virtual BOOL OnInitDialog();
	int selection;
};
