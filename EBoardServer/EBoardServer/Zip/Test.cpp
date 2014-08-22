#include <stdio.h>
#include "zip.h"
#include "zlib.h"
#include "unzip.h"
#include <fstream>
using namespace std;
#pragma comment(lib,"zlib.lib")


int main()
{
	/****ѹ���ļ���zip��***/
	zipFile zf = NULL;
	zf = zipOpen64("myZip.zip",APPEND_STATUS_CREATE);  //����ѹ����
	if (NULL == zf)                                    //��ʧ��
		return 0;

	zip_fileinfo FileInfo;
	fstream infile;
	size_t nLen = 0;
	char* pBuff = NULL;

	//ѹ����һ���ļ��ļ�
	memset(&FileInfo, 0,sizeof(FileInfo));               
	zipOpenNewFileInZip4(zf,"CalculateActivity.java", &FileInfo, //@@@@
		NULL, 0, NULL, 0, NULL, 
		Z_DEFLATED,9,0, -MAX_WBITS, DEF_MEM_LEVEL, 
		Z_DEFAULT_STRATEGY,NULL, 0, 0, 0);
	//ע��bufΪ�ļ�����passwordΪ��ʱ��Ҫ��NULL,levelΪѹ���ȣ�9Ϊ��ߣ�0��͡�

	infile.open("D:\\Program Files (x86)\\Vs2010\\Project\\ZipTest\\CalculateActivity.java",ios::in|ios::binary);
	if (!infile.is_open())                                     //��ʧ��
		return 0;
	infile.seekg(0,ios::end);
	nLen = infile.tellg();
	pBuff= new char[nLen];
	memset(pBuff,0,nLen);
	infile.seekg(0,ios::beg);
	infile.read(pBuff,nLen);
	infile.close();

	zipWriteInFileInZip(zf,pBuff,nLen);                //@@@@д��ѹ���ļ�
	delete pBuff;
	pBuff = NULL;
	zipCloseFileInZip(zf);                             //@@@@�رյ�ǰ�ļ�,����zip��


	//ѹ���ڶ����ļ���һ���ԣ�
	memset(&FileInfo, 0,sizeof(FileInfo));               
	zipOpenNewFileInZip4(zf,"QQ.jpg", &FileInfo, NULL, 0, NULL, 0, NULL, Z_DEFLATED,5,0, -MAX_WBITS, DEF_MEM_LEVEL, 
		Z_DEFAULT_STRATEGY,NULL, 0, 0, 0);
	infile.open("D:\\Program Files (x86)\\Vs2010\\Project\\ZipTest\\QQ.jpg",ios::in|ios::binary);
	if (!infile.is_open())                                     
		return 0;
	infile.seekg(0,ios::end);
	nLen = infile.tellg();
	pBuff = new char[nLen];
	memset(pBuff,0,nLen);
	infile.seekg(0,ios::beg);
	infile.read(pBuff,nLen);
	infile.close();

	zipWriteInFileInZip(zf,pBuff,nLen);                
	delete pBuff;
	pBuff = NULL;
	zipCloseFileInZip(zf);                             

	zipClose(zf,0);                                    //�ر�����zip��

	//ѹ���ڶ����ļ��ļ����ִΣ�
	/*
	zf = NULL;
	zf = zipOpen64("myZip.zip",APPEND_STATUS_ADDINZIP);//���Ѵ��ڵ�ѹ����
	if (NULL == zf)                                    //��ʧ��
	return 0;

	nLen = 0;
	pBuff = NULL;

	memset(&FileInfo, 0,sizeof(FileInfo));               
	zipOpenNewFileInZip4(zf,"QQ.jpg", &FileInfo, //@@@@
	NULL, 0, NULL, 0, NULL, 
	Z_DEFLATED,9,0, -MAX_WBITS, DEF_MEM_LEVEL, 
	Z_DEFAULT_STRATEGY,NULL, 0, 0, 0);

	infile.open("D:\\Program Files (x86)\\Vs2010\\Project\\ZipTest\\QQ.jpg",ios::in|ios::binary);
	if (!infile.is_open())                                     //��ʧ��
	return 0;
	infile.seekg(0,ios::end);
	nLen = infile.tellg();
	pBuff= new char[nLen];
	memset(pBuff,0,nLen);
	infile.seekg(0,ios::beg);
	infile.read(pBuff,nLen);
	infile.close();

	zipWriteInFileInZip(zf,pBuff,nLen);                //@@@@д��ѹ���ļ�
	delete pBuff;
	pBuff = NULL;
	zipCloseFileInZip(zf);                             //@@@@�رյ�ǰ�ļ�,����zip��
	zipClose(zf,0); 
	*/

	/****��ѹ��zip��****/

	unzFile uf=NULL;
	unz_global_info64 gi;
	unz_file_info64 uFileInfo;  
	char filename[260] = {'\0'};                       //�洢�ļ���
	int  nRet;
	fstream outfile;
	nLen = 0;
	memset(&gi, 0,sizeof(unz_global_info64));
	memset(&uFileInfo, 0,sizeof(unz_file_info64));
	uf = unzOpen64("myZip.zip");                       //���Ѵ��ڵ�zip��
	if (NULL == uf)
		return 0; 


	/****��ѹ��ָ�����ļ�****/
	
	if(UNZ_END_OF_LIST_OF_FILE == unzLocateFile(uf,"QQ.jpg",0))//�˺���������Ҫ
		return 0;                                      //ѹ��������ָ���ļ������ļ�
	if (unzGetCurrentFileInfo64(uf,&uFileInfo,filename,sizeof(filename),NULL,0,NULL,0)!= UNZ_OK)
		return 0;
	nLen = uFileInfo.uncompressed_size;
	nRet=unzOpenCurrentFile(uf);                      //���������ļ�
	pBuff = new char[nLen];
	memset(pBuff,0,nLen);
	nRet= unzReadCurrentFile(uf,pBuff,nLen);          //��ȡ���ݵ�ָ�������� 
	if(nRet < 0)
		return 0;                                   
	unzCloseCurrentFile(uf);                          //�رյ�ǰ�ļ�
	outfile.open(filename,ios::out|ios::binary);
	outfile.write(pBuff,nLen);
	outfile.close();
	delete pBuff;
	pBuff = NULL;
	unzClose(uf);
	


    /****ѭ����ѹ���ļ���һ���ԣ�****/
	/*
	nRet = unzGetGlobalInfo64(uf, &gi);                //Ϊ�õ�zip���а��������ļ���Ŀ
	if (nRet != UNZ_OK)          
	return 0;

	for(int i=0;i<gi.number_entry;++i)
	{
	if (unzGetCurrentFileInfo64(uf,&uFileInfo,filename,sizeof(filename),NULL,0,NULL,0)!= UNZ_OK)
	return 0;
	nLen = uFileInfo.uncompressed_size;
	nRet=unzOpenCurrentFile(uf);                       //���������ļ�
	//nRet=unzOpenCurrentFilePassword(uf,szPassword);  //�������ļ�	
	pBuff = new char[nLen];
	memset(pBuff,0,nLen);
	nRet= unzReadCurrentFile(uf,pBuff,nLen);           //��ȡ���ݵ�ָ�������� 
	if(nRet < 0)
	return 0;                                   
	unzCloseCurrentFile(uf);                           //�رյ�ǰ�ļ�
	outfile.open(filename,ios::out|ios::binary);
	outfile.write(pBuff,nLen);
	outfile.close();
	delete pBuff;
	pBuff = NULL;
	if(i < gi.number_entry - 1 && unzGoToNextFile(uf) != UNZ_OK)//����
	return 0;
	}

	unzClose(uf);                                      //�ر���
	*/

	return 0; 
}





//int main()                       
///***���У����ǲ�֪������ļ�ѹ����һ��zip������������ѹ����ν��***/
//{
//	gzFile zipFile = gzopen("my.zip", "wb");
//	fstream infile("original.jpg",ios::in|ios::binary);
//	infile.seekg(0,ios::end);
//	size_t nLen = infile.tellg();
//
//	char* pBuff = new char[nLen];
//	memset(pBuff,0,nLen);
//	infile.seekg(0,ios::beg);
//	infile.read(pBuff,nLen);
//	size_t a;
//	a = gzwrite(zipFile, (void*)pBuff, nLen);
//	infile.close();
//	gzclose(zipFile);
//
//	fstream outfile("after.jpg",ios::out|ios::binary);
//	gzFile uzFile = gzopen("my.zip", "rb");
//
//	if( outfile != NULL )
//	{
//		char szBuff[1024];
//		size_t nSize;
//		unsigned int nTimes = 0;
//		while(true)
//		{
//			nSize = gzread(uzFile, (voidp)szBuff, 1024);
//			if(nSize == 0)
//			{
//				break;
//			}
//			outfile.write(szBuff,nSize);
//			nTimes++;
//		}
//
//		gzclose(uzFile);
//		outfile.close();
//
//	}
//
//	return 0; 
//}

