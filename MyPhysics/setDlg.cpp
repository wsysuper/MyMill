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
	selectCtrl.AddString("�糵��");
	selectCtrl.AddString("�糵��");
	selectCtrl.AddString("��1Ƭ��Ҷ");
	selectCtrl.AddString("��2Ƭ��Ҷ");
	selectCtrl.AddString("��3Ƭ��Ҷ");
	selectCtrl.AddString("��4Ƭ��Ҷ");

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
