// setDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyPhysics.h"
#include "setDlg.h"
#include "afxdialogex.h"


// setDlg dialog

IMPLEMENT_DYNAMIC(setDlg, CDialogEx)

setDlg::setDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(setDlg::IDD, pParent)
	, selection(0)
{
}

setDlg::~setDlg()
{
}

void setDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, selectCtrl);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, colorCtrl);
	DDX_CBIndex(pDX, IDC_COMBO1, selection);
}


BEGIN_MESSAGE_MAP(setDlg, CDialogEx)
END_MESSAGE_MAP()


// setDlg message handlers


BOOL setDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	selectCtrl.AddString("风车杆");
	selectCtrl.AddString("风车轴");
	selectCtrl.AddString("第1片扇叶");
	selectCtrl.AddString("第2片扇叶");
	selectCtrl.AddString("第3片扇叶");
	selectCtrl.AddString("第4片扇叶");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
