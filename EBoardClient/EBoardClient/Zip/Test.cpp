#include <stdio.h>
#include "zip.h"
#include "zlib.h"
#include "unzip.h"
#include <fstream>
using namespace std;
#pragma comment(lib,"zlib.lib")


int main()
{
	/****压缩文件到zip包***/
	zipFile zf = NULL;
	zf = zipOpen64("myZip.zip",APPEND_STATUS_CREATE);  //创建压缩流
	if (NULL == zf)                                    //打开失败
		return 0;

	zip_fileinfo FileInfo;
	fstream infile;
	size_t nLen = 0;
	char* pBuff = NULL;

	//压缩第一个文件文件
	memset(&FileInfo, 0,sizeof(FileInfo));               
	zipOpenNewFileInZip4(zf,"CalculateActivity.java", &FileInfo, //@@@@
		NULL, 0, NULL, 0, NULL, 
		Z_DEFLATED,9,0, -MAX_WBITS, DEF_MEM_LEVEL, 
		Z_DEFAULT_STRATEGY,NULL, 0, 0, 0);
	//注意buf为文件名，password为空时需要给NULL,level为压缩比，9为最高，0最低。

	infile.open("D:\\Program Files (x86)\\Vs2010\\Project\\ZipTest\\CalculateActivity.java",ios::in|ios::binary);
	if (!infile.is_open())                                     //打开失败
		return 0;
	infile.seekg(0,ios::end);
	nLen = infile.tellg();
	pBuff= new char[nLen];
	memset(pBuff,0,nLen);
	infile.seekg(0,ios::beg);
	infile.read(pBuff,nLen);
	infile.close();

	zipWriteInFileInZip(zf,pBuff,nLen);                //@@@@写入压缩文件
	delete pBuff;
	pBuff = NULL;
	zipCloseFileInZip(zf);                             //@@@@关闭当前文件,而非zip包


	//压缩第二个文件（一次性）
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

	zipClose(zf,0);                                    //关闭整个zip包

	//压缩第二个文件文件（分次）
	/*
	zf = NULL;
	zf = zipOpen64("myZip.zip",APPEND_STATUS_ADDINZIP);//打开已存在的压缩流
	if (NULL == zf)                                    //打开失败
	return 0;

	nLen = 0;
	pBuff = NULL;

	memset(&FileInfo, 0,sizeof(FileInfo));               
	zipOpenNewFileInZip4(zf,"QQ.jpg", &FileInfo, //@@@@
	NULL, 0, NULL, 0, NULL, 
	Z_DEFLATED,9,0, -MAX_WBITS, DEF_MEM_LEVEL, 
	Z_DEFAULT_STRATEGY,NULL, 0, 0, 0);

	infile.open("D:\\Program Files (x86)\\Vs2010\\Project\\ZipTest\\QQ.jpg",ios::in|ios::binary);
	if (!infile.is_open())                                     //打开失败
	return 0;
	infile.seekg(0,ios::end);
	nLen = infile.tellg();
	pBuff= new char[nLen];
	memset(pBuff,0,nLen);
	infile.seekg(0,ios::beg);
	infile.read(pBuff,nLen);
	infile.close();

	zipWriteInFileInZip(zf,pBuff,nLen);                //@@@@写入压缩文件
	delete pBuff;
	pBuff = NULL;
	zipCloseFileInZip(zf);                             //@@@@关闭当前文件,而非zip包
	zipClose(zf,0); 
	*/

	/****解压缩zip包****/

	unzFile uf=NULL;
	unz_global_info64 gi;
	unz_file_info64 uFileInfo;  
	char filename[260] = {'\0'};                       //存储文件名
	int  nRet;
	fstream outfile;
	nLen = 0;
	memset(&gi, 0,sizeof(unz_global_info64));
	memset(&uFileInfo, 0,sizeof(unz_file_info64));
	uf = unzOpen64("myZip.zip");                       //打开已存在的zip包
	if (NULL == uf)
		return 0; 


	/****解压缩指定的文件****/
	
	if(UNZ_END_OF_LIST_OF_FILE == unzLocateFile(uf,"QQ.jpg",0))//此函数极其重要
		return 0;                                      //压缩包中无指定文件名的文件
	if (unzGetCurrentFileInfo64(uf,&uFileInfo,filename,sizeof(filename),NULL,0,NULL,0)!= UNZ_OK)
		return 0;
	nLen = uFileInfo.uncompressed_size;
	nRet=unzOpenCurrentFile(uf);                      //打开无密码文件
	pBuff = new char[nLen];
	memset(pBuff,0,nLen);
	nRet= unzReadCurrentFile(uf,pBuff,nLen);          //读取内容到指定缓冲区 
	if(nRet < 0)
		return 0;                                   
	unzCloseCurrentFile(uf);                          //关闭当前文件
	outfile.open(filename,ios::out|ios::binary);
	outfile.write(pBuff,nLen);
	outfile.close();
	delete pBuff;
	pBuff = NULL;
	unzClose(uf);
	


    /****循环解压缩文件（一次性）****/
	/*
	nRet = unzGetGlobalInfo64(uf, &gi);                //为得到zip包中包含所有文件数目
	if (nRet != UNZ_OK)          
	return 0;

	for(int i=0;i<gi.number_entry;++i)
	{
	if (unzGetCurrentFileInfo64(uf,&uFileInfo,filename,sizeof(filename),NULL,0,NULL,0)!= UNZ_OK)
	return 0;
	nLen = uFileInfo.uncompressed_size;
	nRet=unzOpenCurrentFile(uf);                       //打开无密码文件
	//nRet=unzOpenCurrentFilePassword(uf,szPassword);  //有密码文件	
	pBuff = new char[nLen];
	memset(pBuff,0,nLen);
	nRet= unzReadCurrentFile(uf,pBuff,nLen);           //读取内容到指定缓冲区 
	if(nRet < 0)
	return 0;                                   
	unzCloseCurrentFile(uf);                           //关闭当前文件
	outfile.open(filename,ios::out|ios::binary);
	outfile.write(pBuff,nLen);
	outfile.close();
	delete pBuff;
	pBuff = NULL;
	if(i < gi.number_entry - 1 && unzGoToNextFile(uf) != UNZ_OK)//出错
	return 0;
	}

	unzClose(uf);                                      //关闭流
	*/

	return 0; 
}





//int main()                       
///***可行，就是不知道多个文件压缩入一个zip包和最后按需求解压缩如何解决***/
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

