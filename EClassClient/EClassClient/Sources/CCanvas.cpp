#include "CCanvas.h"

//*****************************����Ϊʵ�֣������з���*********************************/
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

//*************************************CCanvas Win32 ʵ��**************************************//
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

	// ȱʡ��Bitmap�Ǻ�ɫ�ģ�������Ҫ�����±���
	// �����Ҫ����FillBackground���������Ʊ���ɫ

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
	Clear();												// ������
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
	BitBlt(hdc, left, top, m_nWidth, m_nHeight, m_hMemDC, 0, 0, SRCCOPY);	// ������
};

void CWinCanvas::Draw(HDC hdc, int left, int top, int width, int height)
{
	BitBlt(hdc, left, top, width, height, m_hMemDC, 0, 0, SRCCOPY);	// ������
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
	BitBlt(hdc, left, top, m_nWidth, m_nHeight, m_hMemDC, 0, 0, SRCCOPY);	// ������
	pgc->ReleaseHDC(hdc);
}

void CWinCanvas::Draw(Graphics* pgc, int left, int top, int width, int height)
{
	if (!pgc)
		return;

	HDC hdc = pgc->GetHDC();
	BitBlt(hdc, left, top, width, height, m_hMemDC, 0, 0, SRCCOPY);	// ������
	pgc->ReleaseHDC(hdc);
}

//*************************************CCanvas GDI+ ʵ��**************************************//
CGDICanvas::CGDICanvas(void){
	p_GC = NULL;
	p_Bmp = NULL;
};

CGDICanvas::~CGDICanvas(void)
{
	Delete();
};

// ����ڴ�Bitmap�л��Ƶ�����
void CGDICanvas::Clear(void)
{
	if (p_Bmp) 
		delete p_Bmp;								// don't keep any old content
	p_Bmp = new Bitmap(m_nWidth, m_nHeight);		// ����һ���µ�Bitmap, ���ڴ��з���

	if (p_GC)
		delete p_GC;
	p_GC = Graphics::FromImage(p_Bmp);				// �������ڴ�Bitmap, ����Graphics���Ƶ�ͼ�ζ��ڸ�Bitmap��
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
	m_hdc = hdc;									// hdc���������ã����ּ��ݣ���������ΪNULL
	m_nWidth = cx;
	m_nHeight = cy;

	if (p_Bmp) 
		delete p_Bmp;
	p_Bmp = new Bitmap(cx, cy);						// ����һ���µ�Bitmap, ���ڴ��з���

	if (p_GC)
		delete p_GC;
	p_GC = Graphics::FromImage(p_Bmp);				// �������ڴ�Bitmap, ����Graphics���Ƶ�ͼ�ζ��ڸ�Bitmap��

	return TRUE;
};

BOOL CGDICanvas::Delete(void){
	//if (p_Bmp) delete p_Bmp;
	//if (p_GC) delete p_GC;

	return TRUE;
};

BOOL CGDICanvas::ReSize(DWORD cx, DWORD cy)
{
	Bitmap* bmp = new Bitmap(cx, cy);					// ����һ���µ�Bitmap, ���ڴ��з���
	Graphics* pgc = Graphics::FromImage(bmp);			// �������ڴ�Bitmap, ����Graphics���Ƶ�ͼ�ζ��ڸ�Bitmap��

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

// �����õ��ڴ�BITMAP������Ŀ��HDC��
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

// �����õ��ڴ�BITMAP������Ŀ��Graphics��
void CGDICanvas::Draw(Graphics* pgc, int left, int top)
{
	if(!pgc)
		return;

	pgc->DrawImage(p_Bmp, left, top, m_nWidth, m_nHeight);
}

// �����õ��ڴ�BITMAP������Ŀ��Graphics��
void CGDICanvas::Draw(Graphics* pgc, int left, int top, int width, int height)
{
	if(!pgc)
		return;

	pgc->DrawImage(p_Bmp, left, top, width, height);
}
