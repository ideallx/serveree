#include "myzip.h"
/*
*   flag:APPEND_STATUS_CREATE   �����������δ򿪲�����
*        APPEND_STATUS_ADDINZIP �����������Ѵ��ڵ�zip�����������
*/
bool CZip::saveToZip(const char* DestPathName,const char* FileName,const void* pBuf,unsigned int nLen, bool isCreate)
{   
	if (NULL == pBuf)
		return false;

	zipFile zf = NULL;
	zip_fileinfo FileInfo;

	int flag = isCreate ? APPEND_STATUS_CREATE : APPEND_STATUS_ADDINZIP;

	zf = zipOpen64(DestPathName,flag);
	if (NULL == zf)
		return false;

	memset(&FileInfo, 0, sizeof(FileInfo));               
	zipOpenNewFileInZip4(zf, FileName, &FileInfo, 
		NULL, 0, NULL, 0, NULL, 
		Z_DEFLATED,9,0, -MAX_WBITS, DEF_MEM_LEVEL, 
		Z_DEFAULT_STRATEGY,NULL, 0, 0, 0);

	zipWriteInFileInZip(zf,pBuf,nLen);               
	zipCloseFileInZip(zf);  
	zipClose(zf,0);                                   
	return true;
};

/*
*  ��ȡ���ļ�ѹ��֮ǰ�����ݳ���
*/

unsigned int CZip::getOriginalSize(const char* SrcPathName,const char* FileName)
{	
	unzFile uf=NULL;
	unz_global_info64 gi;
	unz_file_info64 uFileInfo;      
	char szName[260] = {'\0'};
	int  nRet;
	unsigned int nSize = 0;
	memset(&gi, 0,sizeof(unz_global_info64));
	memset(&uFileInfo, 0, sizeof(unz_file_info64));

	uf = unzOpen64(SrcPathName);                     
	if (NULL == uf)
		return 0; 

	if(UNZ_END_OF_LIST_OF_FILE == unzLocateFile(uf,FileName,0))
		return 0;  

	nRet = unzGetCurrentFileInfo64(uf,&uFileInfo,szName,sizeof(szName),NULL,0,NULL,0);
	if (UNZ_OK != nRet)
		return 0;

	nSize = uFileInfo.uncompressed_size;    
	unzClose(uf);
	return nSize;
};


/*
*   ��ѹ�����и���֮ǰָ�����ļ�����ȡ���ݣ�����ȷ����ʹ�øú���ǰ����getOriginalSizeȷ�����ݳ���
*/
bool CZip::loadFromZip(const char* SrcPathName, const char* FileName, void* pBuf, unsigned int nLen)
{
	unzFile uf=NULL;
	unz_global_info64 gi;
	unz_file_info64 uFileInfo;      
	char szName[260] = {'\0'};
	int  nRet;
	unsigned int nSize = 0;

	memset(&gi, 0,sizeof(unz_global_info64));
	memset(&uFileInfo, 0,sizeof(unz_file_info64));

	uf = unzOpen64(SrcPathName);                     
	if (NULL == uf)
		return false; 

	if(UNZ_END_OF_LIST_OF_FILE == unzLocateFile(uf,FileName,0))
		return false;  

	if (unzGetCurrentFileInfo64(uf,&uFileInfo,szName,sizeof(szName),NULL,0,NULL,0)!= UNZ_OK)
		return false;

	nSize = uFileInfo.uncompressed_size;

	//if (nLen < nSize)
	//	return false;

	nRet=unzOpenCurrentFile(uf);
	if (UNZ_OK != nRet)
		return false;

	nRet= unzReadCurrentFile(uf,pBuf,nLen);     
	if (nRet < 0)
		return false;    

	unzCloseCurrentFile(uf);                          
	unzClose(uf);
	return true;
};
