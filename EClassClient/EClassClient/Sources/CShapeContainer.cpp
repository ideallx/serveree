#include "CShapeContainer.h"

CShapeStage::CShapeStage(void) {
	iop_lock_init(&m_Lock);
};

CShapeStage::~CShapeStage(void)
{
	iop_lock_destroy(&m_Lock);
}

/*
添加了临界区保护Stage
作者： 王庚
日期： 2012年5月10日
更新： 2012年8月27日
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
添加了临界区保护Stage
作者： 王庚
日期： 2012年5月10日
更新： 2012年8月27日
maps a shape to a certain user
*/
void CShapeStage::MapShape(DWORD uid, CShape* ps)
{
	iop_lock(&m_Lock);

	if (ps) {
		m_ShapeStage[uid] = ps;
	} else {
		m_ShapeStage.erase(uid);									// 先删除
	}
	
	iop_unlock(&m_Lock);
};

/*
添加了临界区保护Stage
作者： 王庚
日期： 2012年5月10日
更新： 2012年8月27日
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
添加了临界区保护Stage
作者： 王庚
日期： 2012年5月10日
更新： 2012年8月27日
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
	Clear();												// 清空向量列表中的元素
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

void CShapePage::UpdateShape(CShape* pShape)				// 对已有图形的编辑
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
	
	m_ShapeStage.Clear();									// 清空登台区的图形
	// 清空页内的图形
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
	
	m_ShapeStage.Draw(pgc, pt, 0, 0);							// 绘制登台区
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
	CShape* ps = m_ShapeStage.FindShape(gPacket.head.UID);				// 在登台区查看该用户关联的图形是否存在
		
	Point p;															// 准备写入图形的点
	p.X = pPacket->data.PointX;
	p.Y = pPacket->data.PointY;
	
	if (ps){															// 图形已存在于登台区中
		if (ps->getID() == pPacket->data.ShapeID){						// 数据属于当前图形		
			ps->addPoint(gPacket.data.ShapeSeq, &m_beginPoint, &p);		// 将点添加到图形中
			
			if (pPacket->data.DoneFlag == 1){							// 该包是当前图形的最后一个包
				AddShape(ps);											// 添加该图形至当前页中
				rs = ps;												// 返回当前的图形
				m_ShapeStage.MapShape(pPacket->head.UID, NULL);	// Stage中与用户关联的图形置空，为下次使用
			}
		} else {														// 数据不属于当前图形，这是一个在该UID下的新图形
			if (pPacket->data.ShapeID > ps->getID()){					// 新的图形的图形包到来
				AddShape(ps);											// 添加(推送)已有图形至页中

				ps = CreateShape(pPacket->data.ShapeID, pPacket->data.ShapeType, 
					pt->m_penid, pt->m_brushid);	// 创建新的图形
				if (ps) {
					m_ShapeStage.MapShape(pPacket->head.UID, ps);// 在登台区将该图形与用户关联
					ps->addPoint(gPacket.data.ShapeSeq, &m_beginPoint, &p);			// 将点添加到图形中
				}
				// rs = ps;												// 未完成的图形，不用返回
			} else{
				// 丢弃该包，do nothing									// 迟到的图形包，丢弃
			}
		} // 图形是否存在
	} // 登台区中查找对应用户的图形
	else{																// 该UID对应的图形还没有
		ps = CreateShape(pPacket->data.ShapeID, pPacket->data.ShapeType, 
			pt->m_penid, pt->m_brushid);								// 创建新的图形
		m_beginPoint = Point(pPacket->data.BeginPx, pPacket->data.BeginPy);
		if (ps){			
			m_ShapeStage.MapShape(pPacket->head.UID, ps);			// 在登台区关联该UID与该图形
			ps->addPoint(gPacket.data.ShapeSeq, &m_beginPoint, &p);	// 将点添加到图形中
		}	
		//rs = ps;
	}
	
	iop_unlock(&m_Lock);
	return rs;															// 返回完整生成的图形
};
