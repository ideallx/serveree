#include "CShape.h"


CPaintTools::CPaintTools() :
	m_pPen(NULL),
	m_pBrush(NULL),
	m_penid(0),
	m_brushid(0) {
	initialize();
}

CPaintTools::~CPaintTools() {
	clear();
}

void CPaintTools::initialize(void) {
	Color c(255, 0, 0);
	m_pPen = new Pen(c);

	c.SetFromCOLORREF(RGB(255, 255, 255));
	m_pBrush = new SolidBrush(c);

	m_PenManager.insert(make_pair(m_penid, m_pPen));
	m_BrushManager.insert(make_pair(m_brushid, m_pBrush));
}

BOOL CPaintTools::addPen(DWORD id, Pen* pen) {
	if (m_PenManager.count(id) != 0)
		return false;

	m_penid = id;
	m_PenManager.insert(make_pair(id, pen));
	return TRUE;
}

BOOL CPaintTools::deletePen(DWORD id) {
	if (m_PenManager.count(id) == 0)
		return false;

	// ??? m_pid����ô�������ǲ�Ҫdelete�ѡ�
	m_PenManager.erase(id);
	return TRUE;
}

Pen* CPaintTools::getPen(DWORD id) {
	if (m_PenManager.count(id) == 0)
		return NULL;

	return m_PenManager[id];
}

BOOL CPaintTools::addBrush(DWORD id, Brush* brush) {
	if (m_BrushManager.count(id) != 0)
		return false;

	m_brushid = id;
	m_BrushManager.insert(make_pair(id, brush));
	return TRUE;
}

BOOL CPaintTools::deleteBrush(DWORD id) {
	if (m_BrushManager.count(id) == 0)
		return false;

	m_BrushManager.erase(id);
	return TRUE;
}

Brush* CPaintTools::getBrush(DWORD id) {
	if (m_BrushManager.count(id) == 0)
		return NULL;

	return m_BrushManager[id];
}

void CPaintTools::clear(void) {
	delete m_pPen;
	delete m_pBrush;

	m_PenManager.clear();
	m_BrushManager.clear();
}

CShape::CShape() :
	m_ShapeType(NONE),			// ȱʡΪ��ͼ��
	m_PenID(0),					// if 0, use default pen
	m_BrushID(0),				// if 0, don't use brush
	m_MaxSeq(0) {
}

void CShape::setProperties(DWORD id, DWORD type, DWORD penid, DWORD brushid) {
	m_ID		= id;
	m_ShapeType = type;									// ȱʡΪ��д����
	m_PenID		= penid;
	m_BrushID	= brushid;
};

BOOL CShape::addPoint(DWORD seq, Point* b, Point* p) {	// �������ͼ�εĵ�λ
	if ((b == NULL) || (p == NULL))
		return FALSE;

	m_StartPoint = *b;

	if (seq > m_MaxSeq) m_MaxSeq = seq;					// ��¼���seq


	if (m_ShapeType == SCRIPTS) {						// ��д�����ǲ��ϵ���ӵ�
		Point* pt = new Point(p->X, p->Y);				// �����µĵ�
		m_PointList.insert(make_pair(seq, pt));
	}

	if (seq != m_MaxSeq)								// �������Сֵ����ʱû������
		return TRUE;

	m_EndPoint.X = p->X;
	m_EndPoint.Y = p->Y;

	m_Rect.X = min(m_StartPoint.X, m_EndPoint.X);		// ����������
	m_Rect.Y = min(m_StartPoint.Y, m_EndPoint.Y);
	m_Rect.Width = abs(m_StartPoint.X - m_EndPoint.X);
	m_Rect.Height = abs(m_StartPoint.Y - m_EndPoint.Y);
	return TRUE;
};

void CShape::clear(void) {
	for (unsigned int i=0;i<m_PointList.size();i++)
		delete m_PointList.at(i);						// ɾ����new�����ĵ�
		
	m_PointList.clear();								// ������ж���
};