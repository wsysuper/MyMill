// MyPhysicsView.cpp : CMyPhysicsView 类的实现
//

#include "stdafx.h"

//#include "MyPhysics.h"

#include "MyPhysicsDoc.h"
#include "MyPhysicsView.h"
#include "setDlg.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPhysicsView

IMPLEMENT_DYNCREATE(CMyPhysicsView, CView)

BEGIN_MESSAGE_MAP(CMyPhysicsView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	// View Messages
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	// Mouse Operations
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_CHECK1,&CMyPhysicsView::OnCheck1)
	ON_UPDATE_COMMAND_UI(IDC_CHECK1, &CMyPhysicsView::OnUpdateCheck1)
	ON_COMMAND(IDC_CHECK2,&CMyPhysicsView::OnCheck2)
	ON_UPDATE_COMMAND_UI(IDC_CHECK2, &CMyPhysicsView::OnUpdateCheck2)
	//ON_COMMAND(IDC_CHECK3,&CMyPhysicsView::OnForce)

	//ON_COMMAND(ID_SIMULATION, &CMyPhysicsView::OnSimulation)
	//ON_COMMAND(ID_CUBE, &CMyPhysicsView::OnCube)
	//ON_COMMAND(ID_SPHERE, &CMyPhysicsView::OnSphere)
	//ON_COMMAND(ID_SLOPE, &CMyPhysicsView::OnSlope)

	ON_COMMAND(IDC_RADIO1, &CMyPhysicsView::OnRunning)
	ON_UPDATE_COMMAND_UI(IDC_RADIO1, &CMyPhysicsView::OnUpdateRunning)
	ON_COMMAND(IDC_RADIO2, &CMyPhysicsView::OnPause)
	ON_UPDATE_COMMAND_UI(IDC_RADIO2, &CMyPhysicsView::OnUpdatePause)

	ON_BN_CLICKED(IDC_UP, &CMyPhysicsView::OnBnClickedUp)
	ON_BN_CLICKED(IDC_DOWN, &CMyPhysicsView::OnBnClickedDown)
	ON_BN_CLICKED(IDC_STOP, &CMyPhysicsView::OnBnClickedStop)
	ON_BN_CLICKED(IDC_APPLY, &CMyPhysicsView::OnBnClickedApply)
	ON_BN_CLICKED(IDC_START, &CMyPhysicsView::OnBnClickedStart)
END_MESSAGE_MAP()

// CMyPhysicsView 构造/析构

int CMyPhysicsView::current_state = 0;
int CMyPhysicsView::tnum = 0;
float CMyPhysicsView::view_xyz[3];
float CMyPhysicsView::view_hpr[3];
float CMyPhysicsView::color[4];
int CMyPhysicsView::use_textures = 1;		// 1 if textures to be drawn
int CMyPhysicsView::use_shadows = 1;		// 1 if shadows to be drawn	
Texture* CMyPhysicsView::sky_texture;
Texture* CMyPhysicsView::ground_texture;
Texture* CMyPhysicsView::wood_texture;
Texture* CMyPhysicsView::checkered_texture;
Texture* CMyPhysicsView::texture[4+1];

float CMyPhysicsView::speed = 0.005f;
float CMyPhysicsView::leavecolor[6][3]=
{
	{1.0f,1.0f,1.0f},
	{1.0f,1.0f,0.0f},
	{0.0f,0.0f,1.0f},
	{0.0f,1.0f,0.0f}
};
float CMyPhysicsView::axiscolor[3]={1.0f,0.0f,0.0f};
float CMyPhysicsView::polecolor[3]={0.0f,1.0f,1.0f};
bool CMyPhysicsView::random=false;

CMyPhysicsView::CMyPhysicsView()
: button(0), lastx(0), lasty(0)
{
	// TODO: 在此处添加构造代码
	fn.version = DS_VERSION;
	fn.start = &CMyPhysicsView::start;
	fn.step = &CMyPhysicsView::simLoop;
	fn.command = 0;
	fn.stop = 0;
	fn.path_to_textures = 0;	// uses default

	// textures and shadows
	sky_texture = 0;
	ground_texture = 0;
	wood_texture = 0;
	checkered_texture = 0;

	// globals used to communicate with rendering thread

	renderer_run = 1;
	renderer_pause = 0;	  // 0=run, 1=pause
	renderer_ss = 0;	  // single step command
	renderer_width = 1;
	renderer_height = 1;
	renderer_fn = 0;
	renderer_dc = 0;
	keybuffer_head = 0;	  // index of next key to put in (modified by GUI)
	keybuffer_tail = 0;	  // index of next key to take out (modified by renderer)
}

CMyPhysicsView::~CMyPhysicsView()
{
}

BOOL CMyPhysicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	return CView::PreCreateWindow(cs);
}

// CMyPhysicsView 绘制

void CMyPhysicsView::OnDraw(CDC* /*pDC*/)
{
	CMyPhysicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
	// Draw();
}


// CMyPhysicsView 打印

BOOL CMyPhysicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyPhysicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMyPhysicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清除过程
}

// CMyPhysicsView 诊断

#ifdef _DEBUG
void CMyPhysicsView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPhysicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPhysicsDoc* CMyPhysicsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPhysicsDoc)));
	return (CMyPhysicsDoc*)m_pDocument;
}
#endif //_DEBUG

// CMyPhysicsView 消息处理程序

int CMyPhysicsView::OnCreate(LPCREATESTRUCT lpcs)
{
	if(CView::OnCreate(lpcs) == -1) return -1;
	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
		1,				     // version number
		PFD_DRAW_TO_WINDOW |	     // support window
		PFD_SUPPORT_OPENGL |	     // support OpenGL
		PFD_DOUBLEBUFFER,		     // double buffered
		PFD_TYPE_RGBA,		     // RGBA type
		24, 			     // 24-bit color depth
		0, 0, 0, 0, 0, 0,		     // color bits ignored
		0,				     // no alpha buffer
		0,				     // shift bit ignored
		0,				     // no accumulation buffer
		0, 0, 0, 0, 		     // accum bits ignored
		32, 			     // 32-bit z-buffer
		0,				     // no stencil buffer
		0,				     // no auxiliary buffer
		PFD_MAIN_PLANE,		     // main layer
		0,				     // reserved
		0, 0, 0			     // layer masks ignored
	};
	m_hDC = GetDC()->GetSafeHdc();
	// get the best available match of pixel format for the device context
	int iPixelFormat = ChoosePixelFormat (m_hDC,&pfd);
	if (iPixelFormat==0) ASSERT("could not find a good OpenGL pixel format");
	// set the pixel format of the device context
	if (SetPixelFormat (m_hDC,iPixelFormat,&pfd)==FALSE)
		ASSERT("could not set DC pixel format for OpenGL");
	m_hRC = wglCreateContext(m_hDC);
	if (m_hRC==NULL)
		ASSERT("could not create OpenGL context");
	if (wglMakeCurrent (m_hDC,m_hRC) != TRUE)
		ASSERT("could not make OpenGL context current");

	::GetWindowRect(GetParent()->GetSafeHwnd(),&wnd_rect);
//////////////////////////dsSimulationLoop/////////////////////////////////

	if (current_state != 0) ASSERT ("dsSimulationLoop() called more than once");
	current_state = 1;
	if (fn.version > DS_VERSION)
		ASSERT ("bad version number in dsFunctions structure");
	
	initMotionModel();
	renderer_pause = FALSE;
	renderer_dc = m_hDC;

	renderer_width = 500;
	renderer_height = 395;
	renderer_fn = &fn;

	// test openGL capabilities
	//int maxtsize=0;
	//glGetIntegerv (GL_MAX_TEXTURE_SIZE,&maxtsize);
	//if (maxtsize < 128) dsWarning ("max texture size too small (%dx%d)",
	//	maxtsize,maxtsize);

	dsStartGraphics (renderer_width,renderer_height,renderer_fn);
	if (renderer_fn->start) renderer_fn->start();

	SetTimer(1,8,NULL);
	return 0;
}

void CMyPhysicsView::OnDestroy()
{
	KillTimer(1);
	CView::OnDestroy();

	wglMakeCurrent(NULL,NULL);
	wglDeleteContext(m_hRC);
}

BOOL CMyPhysicsView::OnEraseBkgnd(CDC* pDC)
{
	//return CView::OnEraseBkgnd(pDC);
	return true;
}


void CMyPhysicsView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType,cx,cy);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30,1,-3,3);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0,0,cx,cy);
	glShadeModel(GL_FLAT);
	RECT now_rect;
	::GetWindowRect(GetParent()->GetSafeHwnd(),&now_rect);
	renderer_width = 500 + (now_rect.right-now_rect.left)-(wnd_rect.right-wnd_rect.left);
	renderer_height = 395 + (now_rect.bottom-now_rect.top)-(wnd_rect.bottom-wnd_rect.top);

}

void CMyPhysicsView::OnTimer(UINT_PTR nIDEvent)
{
	static int counter=10;
	static int stopcounter=10;

	switch(nIDEvent)
	{
	case 1:
		dsDrawFrame (renderer_width,renderer_height,renderer_fn,
			renderer_pause && !renderer_run);
		SwapBuffers (renderer_dc);
		break;
	case 2:
		if(counter==0)
		{
			KillTimer(2);
			speed = 0.05f;
			counter = 10;
		}
		else
		{
			speed = speed + (0.05f - speed) / counter;
			counter--;
		}
		break;
	case 3:
		if(stopcounter==0)
		{
			KillTimer(3);
			speed = 0.0f;
			stopcounter = 10;
		}
		else
		{
			speed = speed - speed / stopcounter;
			stopcounter--;
		}
		break;
	case 4:
		for(int i=0;i<6;i++)
			for(int j=0;j<3;j++)
			{
				leavecolor[i][j]=float(rand())/rand();
				if(leavecolor[i][j]>1)
					leavecolor[i][j]=1/leavecolor[i][j];
			}
		break;
	}
}
/*
void CMyPhysicsView::Draw()
{
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(5,5,view_h,view_s,0,0,0,1,0);
	glColor3f(rand()%256/512.0+0.5,rand()%256/512.0+0.5,rand()%256/512.0+0.5);
	GLfloat RAD = (GLfloat)3.1415926/180;
	GLfloat x,y,z,r;
	int i,j;
	for(i=0;i<180;i+=5)
	{
		glBegin(GL_LINE_LOOP);
			r=2*sin(i*RAD);
			z=2*cos(i*RAD);
			for(j=0;j<360;j+=10)
			{
				x=r*cos(j*RAD);
				y=r*sin(j*RAD);
				glVertex3f(x,y,z);
			}
		glEnd();
	}
	for(j=0;j<360;j+=10)
	{
		glBegin(GL_LINE_LOOP);
			for(i=0;i<180;i+=5)
			{
				r=2*sin(i*RAD);
				z=2*cos(i*RAD);
				x=r*cos(j*RAD);
				y=r*sin(j*RAD);
				glVertex3f(x,y,z);
			}
		glEnd();
	}
	SwapBuffers(m_hDC);
}
*/
void CMyPhysicsView::OnLButtonDown(UINT nFlags, CPoint point)
{
	button |= 1;
	lastx = point.x;
	lasty = point.y;
	SetCapture();
}

void CMyPhysicsView::OnMButtonDown(UINT nFlags, CPoint point)
{
	button |= 2;
	lastx = point.x;
	lasty = point.y;
	SetCapture();
}

void CMyPhysicsView::OnRButtonDown(UINT nFlags, CPoint point)
{
	button |= 4;
	lastx = point.x;
	lasty = point.y;
	SetCapture();
}


void CMyPhysicsView::OnLButtonUp(UINT nFlags, CPoint point)
{
	button &= ~1;
	if (button==0) ReleaseCapture();
}

void CMyPhysicsView::OnMButtonUp(UINT nFlags, CPoint point)
{
	button &= ~2;
	if (button==0) ReleaseCapture();
}

void CMyPhysicsView::OnRButtonUp(UINT nFlags, CPoint point)
{
	button &= ~4;
	if (button==0) ReleaseCapture();
}

void CMyPhysicsView::OnMouseMove(UINT nFlags, CPoint point)
{
	int x = point.x;
	int y = point.y;
	if (button) dsMotion (button,x-lastx,y-lasty);
	lastx = x;
	lasty = y;
}

void CMyPhysicsView::OnCheck1()
{
	use_shadows = !use_shadows;
}

void CMyPhysicsView::OnUpdateCheck1(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(use_shadows);
}

void CMyPhysicsView::OnCheck2()
{
	use_textures = !use_textures;
}

void CMyPhysicsView::OnUpdateCheck2(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(use_textures);
}
//
//void CMyPhysicsView::OnForce()
//{
//	bshow_force = !bshow_force;
//}

//void CMyPhysicsView::OnSimulation()
//{
	//if(!skinppLoadSkin(_T("skin\\dogmax.ssk")))	// 加载皮肤
	//	::MessageBox(0,_T("无法加载皮肤!"),_T("Error"),0);
//}

//void CMyPhysicsView::OnCube()
//{
//	bshowCube = !bshowCube;
//}
//
//void CMyPhysicsView::OnSphere()
//{
//	bshowSphere = !bshowSphere;
//}
//
//void CMyPhysicsView::OnSlope()
//{
//	bshowothers = !bshowothers;
//}

void CMyPhysicsView::OnRunning()
{
	renderer_pause=false;
	renderer_run = true;
}

void CMyPhysicsView::OnUpdateRunning(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(renderer_run);
}

void CMyPhysicsView::OnPause()
{
	renderer_pause = true;
	renderer_run = false;
}

void CMyPhysicsView::OnUpdatePause(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(renderer_pause);
}


void CMyPhysicsView::OnBnClickedUp()
{
	speed *= 1.08f;
	if(random == false && speed>0.07)
	{
		random = true;
		SetTimer(4,1500,NULL);
	}
}


void CMyPhysicsView::OnBnClickedDown()
{
	speed /= 1.08f;
	if(random == true && speed<0.07)
	{
		random = false;
		KillTimer(4);
	}
}

void CMyPhysicsView::OnBnClickedStart()
{
	SetTimer(2,300,NULL);
	// TODO: Add your control notification handler code here
}

void CMyPhysicsView::OnBnClickedStop()
{
	SetTimer(3,300,NULL);
	// TODO: Add your control notification handler code here
}


void CMyPhysicsView::OnBnClickedApply()
{
	setDlg dlg;
	dlg.DoModal();
	float r = GetRValue(dlg.colorCtrl.GetColor()) / 255.0f;
	float g = GetGValue(dlg.colorCtrl.GetColor()) / 255.0f;
	float b = GetBValue(dlg.colorCtrl.GetColor()) / 255.0f;
	switch(dlg.selection)
	{
	case 0:
		polecolor[0]=r;
		polecolor[1]=g;
		polecolor[2]=b;
		break;
	case 1:
		axiscolor[0]=r;
		axiscolor[1]=g;
		axiscolor[2]=b;
		break;
	case 2:
		leavecolor[0][0]=r;
		leavecolor[0][1]=g;
		leavecolor[0][2]=b;
		break;
	case 3:
		leavecolor[2][0]=r;
		leavecolor[2][1]=g;
		leavecolor[2][2]=b;
		break;
	case 4:
		leavecolor[1][0]=r;
		leavecolor[1][1]=g;
		leavecolor[1][2]=b;
		break;
	case 5:
		leavecolor[3][0]=r;
		leavecolor[3][1]=g;
		leavecolor[3][2]=b;
		break;
	default:
		leavecolor[0][0]=1.0f;
		leavecolor[0][1]=1.0f;
		leavecolor[0][2]=1.0f;

		leavecolor[1][0]=1.0f;
		leavecolor[1][1]=1.0f;
		leavecolor[1][2]=0.0f;

		leavecolor[2][0]=0.0f;
		leavecolor[2][1]=0.0f;
		leavecolor[2][2]=1.0f;

		leavecolor[3][0]=0.0f;
		leavecolor[3][1]=1.0f;
		leavecolor[3][2]=0.0f;

		axiscolor[0]=1.0f;
		axiscolor[1]=0.0f;
		axiscolor[2]=0.0f;

		polecolor[0]=0.0f;
		polecolor[1]=1.0f;
		polecolor[2]=1.0f;

		MessageBox("已恢复默认颜色");
	}
	// TODO: Add your control notification handler code here
}
