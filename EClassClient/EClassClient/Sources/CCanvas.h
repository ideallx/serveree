#pragma once

#include "../stdafx.h"
#pragma comment( lib, "gdiplus.lib" )									    //包含相关头文件和库
#include <gdiplus.h>
using namespace Gdiplus;

/*************************CCanvas 防闪烁*************************************/
/*
Canvas是系统内存中的一个区域，所有绘制的内容都首先绘制在Canvas上
之后再由Canvas投射在窗口上
Canvas的大小就是当前窗口的大小
*/
class CCanvas{										// 解决谁来绘制，在什么绘制环境中绘制的问题
protected:
	HDC			m_hdc;	
	int			m_nWidth;							// context Width
	int			m_nHeight;							// context Height
	COLORREF	m_BkColor;
	
public:
	CCanvas(void);
	virtual ~CCanvas(void);

public:
	virtual BOOL Create(HDC hdc, DWORD cx, DWORD cy){return FALSE;};
	virtual BOOL Delete(void){return FALSE;};
	virtual BOOL ReSize(DWORD cx, DWORD cy){return FALSE;};
	virtual void Clear(void){return;};					// 清空Canvas MemDC中的内容
	virtual HDC GetCanvasDC(void){return NULL;};		// 获得Canvas的MemDC句柄
	virtual Graphics* GetCanvasGraphic(void){return NULL;}
	virtual void FillBackground(COLORREF c){return;};

public:
	// Win32 Draw
	virtual void Draw(HDC hdc, int left, int top){};
	virtual void Draw(HDC hdc, int left, int top, int width, int height){};
	virtual void TransparentDraw(HDC hdc, int left, int top){};
	virtual void TransparentDraw(HDC hdc, int left, int top, int width, int height){};

	// GDI+ Draw
	virtual void Draw(Graphics* pgc, int left, int top){};
	virtual void Draw(Graphics* pgc, int left, int top, int width, int height){};
};

class CWinCanvas : 							// 解决谁来绘制，在什么绘制环境中绘制的问题
	public CCanvas
{		
protected:				
	HDC			m_hMemDC;
	HBITMAP		m_hBmp;
	BITMAP		m_Bmp;

public:
	CWinCanvas(void);
	virtual ~CWinCanvas(void);

public:
	virtual BOOL Create(HDC hdc, DWORD cx, DWORD cy);
	virtual BOOL Delete(void);
	virtual BOOL ReSize(DWORD cx, DWORD cy);
	virtual void Clear(void);									// 清空Canvas MemDC中的内容
	virtual HDC GetCanvasDC(void);								// 获得Canvas的MemDC句柄
	virtual Graphics* GetCanvasGraphic(void);
	virtual void FillBackground(COLORREF c);

public:
	// Win32 Draw
	virtual void Draw(HDC hdc, int left, int top);
	virtual void Draw(HDC hdc, int left, int top, int width, int height);
	virtual void TransparentDraw(HDC hdc, int left, int top);
	virtual void TransparentDraw(HDC hdc, int left, int top, int width, int height);

	// GDI+ Draw
	virtual void Draw(Graphics* pgc, int left, int top);
	virtual void Draw(Graphics* pgc, int left, int top, int width, int height);
};

class CGDICanvas
	: public CCanvas								// 解决谁来绘制，在什么绘制环境中绘制的问题
{
protected:
	Graphics*	p_GC;
	Bitmap*		p_Bmp;

public:
	CGDICanvas(void);
	virtual ~CGDICanvas(void);

public:
	virtual BOOL Create(HDC hdc, DWORD cx, DWORD cy);
	virtual BOOL Delete(void);
	virtual BOOL ReSize(DWORD cx, DWORD cy);
	virtual void Clear(void);									// 清空Canvas MemDC中的内容
	virtual HDC GetCanvasDC(void);								// 获得Canvas的MemDC句柄
	virtual Graphics* GetCanvasGraphic(void);
	virtual void FillBackground(COLORREF c);

public:
	// Win32 Draw
	virtual void Draw(HDC hdc, int left, int top);
	virtual void Draw(HDC hdc, int left, int top, int width, int height);
	virtual void TransparentDraw(HDC hdc, int left, int top);
	virtual void TransparentDraw(HDC hdc, int left, int top, int width, int height);

	// GDI+ Draw
	virtual void Draw(Graphics* pgc, int left, int top);
	virtual void Draw(Graphics* pgc, int left, int top, int width, int height);
};

