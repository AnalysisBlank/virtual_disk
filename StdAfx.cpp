// stdafx.cpp : source file that includes just the standard includes
//	virtual_disk.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"



//ȫ�ִ�����ʼָ��
char* disk_start;
char disk_name[12];
disk v_disk;
unsigned long disk_size;

unsigned long fcb_number=0;

FCB file_fcb;
FCB folder_fcb;

unsigned long file_start=4*1024*1024;

index t_index;//Ŀ¼�ļ�
unsigned long file_offset=0;//�ļ������4M��ƫ����


CString g_folder_name;//Ŀ¼��

bool g_is_copy=true;// copy:true,cut:false

bool g_is_test_stop=true;