// MyPhysics.cpp : 定义应用程序的类行为。
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
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)

	//ON_BN_CLICKED(IDC_BUTTON1, &CMyPhysicsApp::OnBnClickedButton1)
	//ON_UPDATE_COMMAND_UI(IDC_EDIT1, &CMyPhysicsApp::OnUpdateEdit1)

END_MESSAGE_MAP()


// CMyPhysicsApp 构造

CMyPhysicsApp::CMyPhysicsApp()
{
	 //TODO: 在此处添加构造代码，
	 //将所有重要的初始化放置在 InitInstance 中
	if(!skinppLoadSkin(_T("skin\\dogmax.ssk")))	// 加载皮肤
		MessageBox(0,_T("无法加载皮肤!"),_T("Error"),0);
}

CMyPhysicsApp::~CMyPhysicsApp()
{
	// TODO: 在此处添加析构代码，
	skinppExitSkin(); //退出界面库，做清理工作。
}


// 唯一的一个 CMyPhysicsApp 对象

CMyPhysicsApp theApp;


// CMyPhysicsApp 初始化

BOOL CMyPhysicsApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMyPhysicsDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CMyPhysicsView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 启用“DDE 执行”
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);


	// 调度在命令行中指定的命令。如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// 唯一的一个窗口已初始化，因此显示它并对其进行更新
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	// 仅当具有后缀时才调用 DragAcceptFiles
	//  在 SDI 应用程序中，这应在 ProcessShellCommand  之后发生
	// 启用拖/放
	m_pMainWnd->DragAcceptFiles();
	return TRUE;
}



// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// 用于运行对话框的应用程序命令

void CMyPhysicsApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

//// CMyPhysicsApp 消息处理程序
//
//void CMyPhysicsApp::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString path = _T("skin\\");
//	path += edit1str;
//	if(path.Right(4)!=_T(".ssk")) path += _T(".ssk");
//	if(!skinppLoadSkin((TCHAR*)(LPCTSTR)path))	// 加载皮肤
//	{
//		MessageBox(0,_T("无法加载皮肤!"),_T("Error"),0);
//		skinppLoadSkin(_T("skin\\Steel.ssk"));
//	}
//}
//
//void CMyPhysicsApp::OnUpdateEdit1(CCmdUI *pCmdUI)
//{
//	pCmdUI->m_pOther->GetWindowText(edit1str);
//}
