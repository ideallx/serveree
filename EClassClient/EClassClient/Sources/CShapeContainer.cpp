#include "CShapeContainer.h"

CShapeStage::CShapeStage(void) {
	iop_lock_init(&m_Lock);
};

CShapeStage::~CShapeStage(void)
{
	iop_lock_destroy(&m_Lock);
}

/*
������ٽ�������Stage
���ߣ� ����
���ڣ� 2012��5��10��
���£� 2012��8��27��
*/
CShape* CShapeStage::FindShape(DWORD uid)
{
	CShape* ps = NULL;
	iop_lock(&m_Lock);

	map<DWORD, CShape*>::iterator iter;
	iter = m_ShapeStage.find(uid);
	if (iter != m_ShapeStage.end()){
		ps = iter->second;
	}
	
	iop_unlock(&m_Lock);
	return ps;
};

/*
������ٽ�������Stage
���ߣ� ����
���ڣ� 2012��5��10��
���£� 2012��8��27��
maps a shape to a certain user
*/
void CShapeStage::MapShape(DWORD uid, CShape* ps)
{
	iop_lock(&m_Lock);

	if (ps) {
		m_ShapeStage[uid] = ps;
	} else {
		m_ShapeStage.erase(uid);									// ��ɾ��
	}
	
	iop_unlock(&m_Lock);
};

/*
������ٽ�������Stage
���ߣ� ����
���ڣ� 2012��5��10��
���£� 2012��8��27��
*/
void CShapeStage::Clear(void)
{
	iop_lock(&m_Lock);
	CShape* pShape = NULL;		
	map<DWORD, CShape*>::iterator iter;
		
	for (iter = m_ShapeStage.begin(); iter != m_ShapeStage.end(); iter++){
		pShape = iter->second;
		if (pShape) {
			delete pShape;
		}
	}

	m_ShapeStage.clear();
	iop_unlock(&m_Lock);
}

/*
������ٽ�������Stage
���ߣ� ����
���ڣ� 2012��5��10��
���£� 2012��8��27��
Draw stage into a canvas
*/
void CShapeStage::Draw(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y)
{
	iop_lock(&m_Lock);
	CShape* pShape = NULL;		
	map<DWORD, CShape*>::iterator iter;
	Pen* pen = NULL;
	Brush* brush = NULL;

	for (iter = m_ShapeStage.begin(); iter != m_ShapeStage.end(); iter++ ){
		pShape = iter->second;
		if (pShape) {
			pen = pt->getPen(pShape->getPenID());
			//brush = pt->GetBrush(pShape->GetBrushID());
			pShape->Draw(pgc, pen, offset_X, offset_Y);
		}
	}
	iop_unlock(&m_Lock);
};

//************************************CTSShapePage***********************************//
CShapePage::CShapePage()
{
};

CShapePage::~CShapePage()
{
	Clear();												// ��������б��е�Ԫ��
};

int CShapePage::Size()
{ 
	return m_ShapePage.size(); 
};

void CShapePage::AddShape(CShape* pShape)
{
	if (!pShape)
		return;
	
	iop_lock(&m_Lock);
	//CShape* shape = new CShape(*pShape);
	m_ShapePage.push_back(pShape);
	iop_unlock(&m_Lock);
};

void CShapePage::UpdateShape(CShape* pShape)				// ������ͼ�εı༭
{
	iop_lock(&m_Lock);
	
	iop_unlock(&m_Lock);
};

CShape* CShapePage::GetShape(unsigned int i)
{
	if (m_ShapePage.size()<=i)
		return NULL;

	return m_ShapePage.at(i);
};

void CShapePage::Clear(void)
{
	iop_lock(&m_Lock);
	
	m_ShapeStage.Clear();									// ��յ�̨����ͼ��
	// ���ҳ�ڵ�ͼ��
	vector<CShape*>::iterator iter;		
	for ( iter = m_ShapePage.begin(); iter != m_ShapePage.end(); iter++ ){
		delete *iter;
	}
	m_ShapePage.clear();	
	
	iop_unlock(&m_Lock);
};

CShape* CShapePage::FindShape(DWORD uid)
{
	if (m_ShapePage.empty())
		return NULL;

	CShape* pShape = NULL;	
	
	iop_lock(&m_Lock);
	vector<CShape*>::iterator    m_Itr;
	for (m_Itr = m_ShapePage.begin(); m_Itr != m_ShapePage.end(); m_Itr++){
		pShape = *m_Itr;
			
		if (pShape->getID() == uid)
			break;
		else
			pShape = NULL;
	}
	iop_unlock(&m_Lock);

	return pShape;
};	

void CShapePage::Draw(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y)
{
	iop_lock(&m_Lock);
	
	m_ShapeStage.Draw(pgc, pt, 0, 0);							// ���Ƶ�̨��
	if (!m_ShapePage.empty()){
		CShape* pShape = NULL;		
		
		for (unsigned int i =0 ; i<m_ShapePage.size(); i++){
			pShape = m_ShapePage.at(i);
			if(pShape){
				Pen* pen = pt->getPen(pShape->getPenID());
				pShape->Draw(pgc, pen, 0, 0);
			}
		}
	}// end if
	
	iop_unlock(&m_Lock);
};

void CShapePage::DrawCurrent(Graphics* pgc, CPaintTools* pt, int offset_X, int offset_Y)
{
	iop_lock(&m_Lock);
	m_ShapeStage.Draw(pgc, pt, offset_X, offset_Y);
	iop_unlock(&m_Lock);
};

// make shapes by the coming in graphic packet
// and returns the shape when the shape is done
// and it will pushed out of stage area
CShape* CShapePage::MakeShape(const TS_GRAPHIC_PACKET& gPacket, CPaintTools* pt)
{
	CShape* rs = NULL;													// Return Shape;
	
	iop_lock(&m_Lock);
	LPTS_GRAPHIC_PACKET pPacket = (LPTS_GRAPHIC_PACKET)&gPacket;
	CShape* ps = m_ShapeStage.FindShape(gPacket.head.UID);				// �ڵ�̨���鿴���û�������ͼ���Ƿ����
		
	Point p;															// ׼��д��ͼ�εĵ�
	p.X = pPacket->data.PointX;
	p.Y = pPacket->data.PointY;
	
	if (ps){															// ͼ���Ѵ����ڵ�̨����
		if (ps->getID() == pPacket->data.ShapeID){						// �������ڵ�ǰͼ��		
			ps->addPoint(gPacket.data.ShapeSeq, &m_beginPoint, &p);		// ������ӵ�ͼ����
			
			if (pPacket->data.DoneFlag == 1){							// �ð��ǵ�ǰͼ�ε����һ����
				AddShape(ps);											// ��Ӹ�ͼ������ǰҳ��
				rs = ps;												// ���ص�ǰ��ͼ��
				m_ShapeStage.MapShape(pPacket->head.UID, NULL);	// Stage�����û�������ͼ���ÿգ�Ϊ�´�ʹ��
			}
		} else {														// ���ݲ����ڵ�ǰͼ�Σ�����һ���ڸ�UID�µ���ͼ��
			if (pPacket->data.ShapeID > ps->getID()){					// �µ�ͼ�ε�ͼ�ΰ�����
				AddShape(ps);											// ���(����)����ͼ����ҳ��

				ps = CreateShape(pPacket->data.ShapeID, pPacket->data.ShapeType, 
					pt->m_penid, pt->m_brushid);	// �����µ�ͼ��
				if (ps) {
					m_ShapeStage.MapShape(pPacket->head.UID, ps);// �ڵ�̨������ͼ�����û�����
					ps->addPoint(gPacket.data.ShapeSeq, &m_beginPoint, &p);			// ������ӵ�ͼ����
				}
				// rs = ps;												// δ��ɵ�ͼ�Σ����÷���
			} else{
				// �����ð���do nothing									// �ٵ���ͼ�ΰ�������
			}
		} // ͼ���Ƿ����
	} // ��̨���в��Ҷ�Ӧ�û���ͼ��
	else{																// ��UID��Ӧ��ͼ�λ�û��
		ps = CreateShape(pPacket->data.ShapeID, pPacket->data.ShapeType, 
			pt->m_penid, pt->m_brushid);								// �����µ�ͼ��
		m_beginPoint = Point(pPacket->data.BeginPx, pPacket->data.BeginPy);
		if (ps){			
			m_ShapeStage.MapShape(pPacket->head.UID, ps);			// �ڵ�̨��������UID���ͼ��
			ps->addPoint(gPacket.data.ShapeSeq, &m_beginPoint, &p);	// ������ӵ�ͼ����
		}	
		//rs = ps;
	}
	
	iop_unlock(&m_Lock);
	return rs;															// �����������ɵ�ͼ��
};
