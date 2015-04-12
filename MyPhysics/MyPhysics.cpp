// MyPhysics.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MyPhysics.h"
#include "MainFrm.h"

#include "MyPhysicsDoc.h"
#include "MyPhysicsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPhysicsApp

BEGIN_MESSAGE_MAP(CMyPhysicsApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMyPhysicsApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)

	//ON_BN_CLICKED(IDC_BUTTON1, &CMyPhysicsApp::OnBnClickedButton1)
	//ON_UPDATE_COMMAND_UI(IDC_EDIT1, &CMyPhysicsApp::OnUpdateEdit1)

END_MESSAGE_MAP()


// CMyPhysicsApp ����

CMyPhysicsApp::CMyPhysicsApp()
{
	 //TODO: �ڴ˴���ӹ�����룬
	 //��������Ҫ�ĳ�ʼ�������� InitInstance ��
	if(!skinppLoadSkin(_T("skin\\dogmax.ssk")))	// ����Ƥ��
		MessageBox(0,_T("�޷�����Ƥ��!"),_T("Error"),0);
}

CMyPhysicsApp::~CMyPhysicsApp()
{
	// TODO: �ڴ˴�����������룬
	skinppExitSkin(); //�˳�����⣬����������
}


// Ψһ��һ�� CMyPhysicsApp ����

CMyPhysicsApp theApp;


// CMyPhysicsApp ��ʼ��

BOOL CMyPhysicsApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMyPhysicsDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMyPhysicsView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ���á�DDE ִ�С�
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// ������׼������DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// ��������������ָ����������
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// �������к�׺ʱ�ŵ��� DragAcceptFiles
	//  �� SDI Ӧ�ó����У���Ӧ�� ProcessShellCommand  ֮����
	// ������/��
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// �������жԻ����Ӧ�ó�������

void CMyPhysicsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//// CMyPhysicsApp ��Ϣ�������
//
//void CMyPhysicsApp::OnBnClickedButton1()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CString path = _T("skin\\");
//	path += edit1str;
//	if(path.Right(4)!=_T(".ssk")) path += _T(".ssk");
//	if(!skinppLoadSkin((TCHAR*)(LPCTSTR)path))	// ����Ƥ��
//	{
//		MessageBox(0,_T("�޷�����Ƥ��!"),_T("Error"),0);
//		skinppLoadSkin(_T("skin\\Steel.ssk"));
//	}
//}
//
//void CMyPhysicsApp::OnUpdateEdit1(CCmdUI *pCmdUI)
//{
//	pCmdUI->m_pOther->GetWindowText(edit1str);
//}
