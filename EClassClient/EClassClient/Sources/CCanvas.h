#pragma once

#include "../stdafx.h"
#pragma comment( lib, "gdiplus.lib" )									    //�������ͷ�ļ��Ϳ�
#include <gdiplus.h>
using namespace Gdiplus;

/*************************CCanvas ����˸*************************************/
/*
Canvas��ϵͳ�ڴ��е�һ���������л��Ƶ����ݶ����Ȼ�����Canvas��
֮������CanvasͶ���ڴ�����
Canvas�Ĵ�С���ǵ�ǰ���ڵĴ�С
*/
class CCanvas{										// ���˭�����ƣ���ʲô���ƻ����л��Ƶ�����
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
	virtual void Clear(void){return;};					// ���Canvas MemDC�е�����
	virtual HDC GetCanvasDC(void){return NULL;};		// ���Canvas��MemDC���
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

class CWinCanvas : 							// ���˭�����ƣ���ʲô���ƻ����л��Ƶ�����
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
	virtual void Clear(void);									// ���Canvas MemDC�е�����
	virtual HDC GetCanvasDC(void);								// ���Canvas��MemDC���
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
	: public CCanvas								// ���˭�����ƣ���ʲô���ƻ����л��Ƶ�����
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
	virtual void Clear(void);									// ���Canvas MemDC�е�����
	virtual HDC GetCanvasDC(void);								// ���Canvas��MemDC���
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

