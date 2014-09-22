#include "CCanvas.h"

//*****************************以下为实现，请自行分离*********************************/
//*************************************CCanvas**************************************//
CCanvas::CCanvas()
{
	m_hdc		= NULL;
	m_nWidth	= m_nHeight = 0;
	m_BkColor	= RGB(255, 255, 255);
};

CCanvas::~CCanvas()
{

}

//*************************************CCanvas Win32 实现**************************************//
CWinCanvas::CWinCanvas(void){
	m_hdc		= NULL;
	m_hMemDC	= NULL;
	m_hBmp		= NULL;
};

CWinCanvas::~CWinCanvas(void)
{
	Delete();
};

void CWinCanvas::Clear(void)
{
	if (!m_hMemDC)
		return;

	// 缺省的Bitmap是黑色的，按照需要来更新背景
	// 因此需要调用FillBackground过程来绘制背景色

	::DeleteObject(m_hBmp);
	m_hBmp = ::CreateCompatibleBitmap(m_hdc, m_nWidth, m_nHeight);
	::SelectObject(m_hMemDC, m_hBmp);
};

HDC CWinCanvas::GetCanvasDC(void)
{
	return m_hMemDC;
};

Graphics* CWinCanvas::GetCanvasGraphic(void)
{
	return Graphics::FromHDC(m_hMemDC);
}

BOOL CWinCanvas::Create(HDC hdc, DWORD cx, DWORD cy)
{
	BOOL rc = FALSE;
	if (hdc == NULL)
		return FALSE;

	m_nWidth = cx;
	m_nHeight = cy;

	m_hdc = hdc;
	m_hMemDC = ::CreateCompatibleDC(hdc);	
	if (!m_hMemDC)
		return FALSE;

	m_hBmp = ::CreateCompatibleBitmap(hdc, cx, cy);
	if (!m_hBmp){
		::DeleteDC(m_hMemDC);
		return FALSE;
	}

	::SelectObject(m_hMemDC, m_hBmp);
	Clear();												// 清理背景
	return TRUE;
};

BOOL CWinCanvas::Delete(void){
	::DeleteObject(m_hBmp);
	::DeleteDC(m_hMemDC);									// A compatible DC
	
	m_hBmp = NULL;
	m_hMemDC = NULL;
	return TRUE;
};

BOOL CWinCanvas::ReSize(DWORD cx, DWORD cy)
{
	Delete();
	Create(m_hdc, cx, cy);
	FillBackground(m_BkColor);
	return TRUE;
};

void CWinCanvas::FillBackground(COLORREF c)
{
	m_BkColor = c;
	//::SetBkColor(m_hMemDC, m_BkColor);

	RECT rect;
	::SetRect(&rect, 0, 0, m_nWidth, m_nHeight);
	HBRUSH brush = ::CreateSolidBrush(c);
	::FillRect(m_hMemDC, &rect, brush);
	::DeleteObject(brush);
};

void CWinCanvas::Draw(HDC hdc, int left, int top)
{
	BitBlt(hdc, left, top, m_nWidth, m_nHeight, m_hMemDC, 0, 0, SRCCOPY);	// 贴内容
};

void CWinCanvas::Draw(HDC hdc, int left, int top, int width, int height)
{
	BitBlt(hdc, left, top, width, height, m_hMemDC, 0, 0, SRCCOPY);	// 贴内容
};

void CWinCanvas::TransparentDraw(HDC hdc, int left, int top)
{
	TransparentBlt(hdc, left, top, m_nWidth, m_nHeight, m_hMemDC, 0, 0, m_nWidth, m_nHeight, m_BkColor);
}

void CWinCanvas::TransparentDraw(HDC hdc, int left, int top, int width, int height)
{
	TransparentBlt(hdc, left, top, width, height, m_hMemDC, 0, 0, width, height, m_BkColor);
}

void CWinCanvas::Draw(Graphics* pgc, int left, int top)
{
	if (!pgc)
		return;

	HDC hdc = pgc->GetHDC();
	BitBlt(hdc, left, top, m_nWidth, m_nHeight, m_hMemDC, 0, 0, SRCCOPY);	// 贴内容
	pgc->ReleaseHDC(hdc);
}

void CWinCanvas::Draw(Graphics* pgc, int left, int top, int width, int height)
{
	if (!pgc)
		return;

	HDC hdc = pgc->GetHDC();
	BitBlt(hdc, left, top, width, height, m_hMemDC, 0, 0, SRCCOPY);	// 贴内容
	pgc->ReleaseHDC(hdc);
}

//*************************************CCanvas GDI+ 实现**************************************//
CGDICanvas::CGDICanvas(void){
	p_GC = NULL;
	p_Bmp = NULL;
};

CGDICanvas::~CGDICanvas(void)
{
	Delete();
};

// 清空内存Bitmap中绘制的内容
void CGDICanvas::Clear(void)
{
	if (p_Bmp) 
		delete p_Bmp;								// don't keep any old content
	p_Bmp = new Bitmap(m_nWidth, m_nHeight);		// 定义一个新的Bitmap, 在内存中分配

	if (p_GC)
		delete p_GC;
	p_GC = Graphics::FromImage(p_Bmp);				// 创建了内存Bitmap, 所有Graphics绘制的图形都在该Bitmap中
};

HDC CGDICanvas::GetCanvasDC(void)
{
	if (p_GC)
		return p_GC->GetHDC();						// looks return a NULL hdc
	else
		return NULL;
};

Graphics* CGDICanvas::GetCanvasGraphic(void)
{
	return p_GC;
}

BOOL CGDICanvas::Create(HDC hdc, DWORD cx, DWORD cy)
{
	m_hdc = hdc;									// hdc在这里无用，保持兼容，可以设置为NULL
	m_nWidth = cx;
	m_nHeight = cy;

	if (p_Bmp) 
		delete p_Bmp;
	p_Bmp = new Bitmap(cx, cy);						// 定义一个新的Bitmap, 在内存中分配

	if (p_GC)
		delete p_GC;
	p_GC = Graphics::FromImage(p_Bmp);				// 创建了内存Bitmap, 所有Graphics绘制的图形都在该Bitmap中

	return TRUE;
};

BOOL CGDICanvas::Delete(void){
	//if (p_Bmp) delete p_Bmp;
	//if (p_GC) delete p_GC;

	return TRUE;
};

BOOL CGDICanvas::ReSize(DWORD cx, DWORD cy)
{
	Bitmap* bmp = new Bitmap(cx, cy);					// 定义一个新的Bitmap, 在内存中分配
	Graphics* pgc = Graphics::FromImage(bmp);			// 创建了内存Bitmap, 所有Graphics绘制的图形都在该Bitmap中

	if (p_Bmp){ 
		pgc->DrawImage(p_Bmp, 0, 0);					// Keep the old content;
		delete p_Bmp;	
	}
	p_Bmp = bmp;										// reassign the bitmap				

	if (p_GC)
		delete p_GC;
	p_GC = pgc;											// reassign the graphics			

	return TRUE;
};

void CGDICanvas::FillBackground(COLORREF c)
{
	m_BkColor = c;
	Color color;
	color.SetFromCOLORREF(c);
	SolidBrush* brush = new SolidBrush(color);
	
	if(p_GC)
		p_GC->FillRectangle(brush, 0, 0, m_nWidth, m_nHeight);
	
	delete brush;
};

// 将内置的内存BITMAP绘制在目标HDC上
void CGDICanvas::Draw(HDC hdc, int left, int top)
{
	Graphics* pgc = Graphics::FromHDC(hdc);
	if(!pgc) 
		return;

	//pgc->DrawImage(p_Bmp, left, top, m_nWidth, m_nHeight);
	pgc->DrawImage(p_Bmp, left, top);
	delete pgc;
};

void CGDICanvas::Draw(HDC hdc, int left, int top, int width, int height)
{
	Graphics* pgc = Graphics::FromHDC(hdc);
	if(!pgc) 
		return;

	pgc->DrawImage(p_Bmp, left, top, width, height);
	delete pgc;
};

void CGDICanvas::TransparentDraw(HDC hdc, int left, int top)
{
	Draw(hdc, left, top);
}

void CGDICanvas::TransparentDraw(HDC hdc, int left, int top, int width, int height)
{
	Draw(hdc, left, top, width, height);
}

// 将内置的内存BITMAP绘制在目标Graphics上
void CGDICanvas::Draw(Graphics* pgc, int left, int top)
{
	if(!pgc)
		return;

	pgc->DrawImage(p_Bmp, left, top, m_nWidth, m_nHeight);
}

// 将内置的内存BITMAP绘制在目标Graphics上
void CGDICanvas::Draw(Graphics* pgc, int left, int top, int width, int height)
{
	if(!pgc)
		return;

	pgc->DrawImage(p_Bmp, left, top, width, height);
}
