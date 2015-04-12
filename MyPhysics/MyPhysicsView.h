// MyPhysicsView.h : CMyPhysicsView 类的接口
//


#pragma once

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <drawstuff/drawstuff.h>
#include "physics.h"

class CMyPhysicsView : public CView
{
protected: // 仅从序列化创建
	CMyPhysicsView();
	DECLARE_DYNCREATE(CMyPhysicsView)

// 属性
public:
	static float speed;
	static float leavecolor[6][3];
	static float axiscolor[3];
	static float polecolor[3];
	static bool random;
	//static bool bshowCube;
	//static bool bshowSphere;
	//static bool bshowothers;
	HDC m_hDC;
	HGLRC m_hRC;
	RECT wnd_rect;
	int button,lastx,lasty;	// used for mouse events
	dsFunctions fn;

	// the current state:
	//    0 = uninitialized
	//    1 = dsSimulationLoop() called
	//    2 = dsDrawFrame() called
	static int current_state;

	// textures and shadows
	static int use_textures;		// 1 if textures to be drawn
	static int use_shadows;		// 1 if shadows to be drawn
	static Texture *sky_texture;
	static Texture *ground_texture;
	static Texture *wood_texture;
	static Texture *checkered_texture;

	static Texture *texture[4+1]; // +1 since index 0 is not used

	// motion model

	// current camera position and orientation
	static float view_xyz[3];	// position x,y,z
	static float view_hpr[3];	// heading, pitch, roll (degrees)

	// globals used to communicate with rendering thread

	int renderer_run;
	int renderer_pause;	  // 0=run, 1=pause
	int renderer_ss;	  // single step command
	int renderer_width;
	int renderer_height;
	dsFunctions *renderer_fn;
	HDC renderer_dc;
	int keybuffer[16];	  // fifo ring buffer for keypresses
	int keybuffer_head;	  // index of next key to put in (modified by GUI)
	int keybuffer_tail;	  // index of next key to take out (modified by renderer)
	//***************************************************************************
	// the current drawing state (for when the user's step function is drawing)

	static float color[4];	// current r,g,b,alpha color
	static int tnum;			// current texture number

////////////////////////// END OF MY OWN VARIABLES /////////////////////////////////

	CMyPhysicsDoc* GetDocument() const;

// 操作
public:
	void Draw();
	void initMotionModel();
	static void wrapCameraAngles();
	void dsMotion (int mode, int deltax, int deltay);
	// drawing loop stuff
	void dsStartGraphics (int width, int height, dsFunctions *fn);
	void dsStopGraphics();
	void drawSky (float view_xyz[3]);
	void drawGround();
	void drawPyramidGrid();
	void dsDrawFrame (int width, int height, dsFunctions *fn, int pause);

	static void dsSetViewpoint (float xyz[3], float hpr[3]);
	static void dsGetViewpoint (float xyz[3], float hpr[3]);
	static void dsSetTexture (int texture_number);
	static void dsSetColor (float red, float green, float blue);

	///////////////////////////////////////////////////////////////////////

	static void dsDrawBox (const float pos[3], const float R[12],
						   const float sides[3]);

	void dsDrawConvex (const float pos[3], const float R[12],
							  float *_planes,unsigned int _planecount,
							  float *_points,
							  unsigned int _pointcount,
							  unsigned int *_polygons);

	static void dsDrawSphere (const float pos[3], const float R[12],
							  float radius);

	static void dsDrawTriangle (const float pos[3], const float R[12],
								const float *v0, const float *v1,
								const float *v2, int solid);

	static void dsDrawCylinder (const float pos[3], const float R[12],
								float length, float radius);

	static void dsDrawCapsule (const float pos[3], const float R[12],
							   float length, float radius);

	static void dsDrawLine (const float pos1[3], const float pos2[3]);

	static void setupDrawingMode();
	
	static void setShadowDrawingMode();

	///////////////////////////////////////////////////////////////////////

	static void start();
	static void simLoop (int pause);

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyPhysicsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	//{{AFX_MSG(CMyPhysicsView)
	afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

	afx_msg void OnCheck1();
	afx_msg void OnUpdateCheck1(CCmdUI *pCmdUI);
	afx_msg void OnCheck2();
	afx_msg void OnUpdateCheck2(CCmdUI *pCmdUI);
	//afx_msg void CMyPhysicsView::OnForce();

	//afx_msg void OnSimulation();
	//afx_msg void OnCube();
	//afx_msg void OnSphere();
	//afx_msg void OnSlope();

	afx_msg void OnRunning();
	afx_msg void OnUpdateRunning(CCmdUI *pCmdUI);
	afx_msg void OnPause();
	afx_msg void OnUpdatePause(CCmdUI *pCmdUI);


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedStart();
};

#ifndef _DEBUG  // MyPhysicsView.cpp 中的调试版本
inline CMyPhysicsDoc* CMyPhysicsView::GetDocument() const
   { return reinterpret_cast<CMyPhysicsDoc*>(m_pDocument); }
#endif

