#include <time.h>
#include "StdAfx.h"

#pragma once
//������Ϣ�ṹ�� 24 bytes
struct disk
{
	char *disk_start;//���̿�ʼλ��ָ��	4 bytes
	unsigned long total_space;//���̴�С ����λ��Bytes�� 4 bytes
	unsigned long used_space;//������ʹ�ô�С����λ��Bytes�� 4 bytes
	char disk_name[12];//������ 12 bytes
};
//�ļ����ƿ�ṹ�� 56 bytes
struct FCB
{
	char file_name[32];//�ļ��� 32 bytes

	unsigned long file_start;//�ļ���ʼλ��ƫ�ƣ�����ڴ�����ʼλ�ã� 4 bytes
	unsigned long file_size;//�ļ���С 4 bytes

	time_t create_time;//����ʱ��	4 bytes
	time_t update_time;//�޸�ʱ��	4 bytes

	byte file_properties;//�ļ����� 1 byte [isindex][r][w][e] (0110) [0][0][0][0]
	char other_use[7];//���� 7bytes
};

//Ŀ¼�ļ��ṹ�� 4*1024 bytes
struct index
{
	unsigned int file_number;//�ļ���Ŀ 4 bytes
	unsigned long fcb_index[1023];//fcb �����±� 4*1023 bytes
};
//�ļ����ƿ��б���Ϣ�ṹ�� 4 bytes
struct FCB_list
{
	unsigned long FCB_number;//�ļ���Ŀ 4 bytes
};

//���̳�ʼ��
void init_disk(disk& v_disk,char* t_disk_start,char* t_disk_name,unsigned long t_disk_size);

//FCB��ʼ��
void init_FCB_FILE(FCB& c_fcb);
void init_FCB_FOLDER(FCB& c_fcb);
//Ŀ¼�ļ���ʼ��
void init_index(index& c_index);

//�����ļ�
bool create_file(char* file_name,char* current_index);//���統ǰĿ¼���ļ���ĿΪ1024����ʧ��
//ɾ���ļ�
bool delete_file(char* file_name,char* current_index);//�����ļ�Ϊֻ��ɾ��ʧ��
//�ƶ��ļ�
bool move_file(char* file_name,char* s_index,char* d_index);//����Ŀ��Ŀ¼��ĿΪ1024�ƶ�ʧ��
//�ļ�����
bool update_file_name(char* file_name,char* new_file_name);//�������ļ�������32bytes����ʧ��

void update_disk_used_size(unsigned int sz);//���´���ʹ�ô�С
void update_head_use(unsigned int sz);//���¹���ռ�ʹ�ô�С
void update_file_offset(unsigned long f_offset);
void copy_fcb(FCB& f_fcb);
void copy_folder(index& t_index);
void copy_file(char* file,DWORD file_len);//�ļ����Ƶ�������
char* get_folder_start(CString folder_path);//�����ļ���·�����ҵ�Ŀ¼�ļ��洢�������ַ

void add_file_to_folder(CString folder_path,unsigned int f_fcb_number);//�����ļ���·��������ļ�(FCB�����±�)
char* get_fcb_by_path(CString file_path);//ͨ���ļ�·���ҵ�fcb
CString get_fn_by_pth(CString file_path);//ͨ��·����ȡ�ļ���
void del_file_by_path(CString file_path);//ͨ��·��ɾ���ļ�
//ɾ���ļ�ʱ���޸�Ŀ¼�ļ�
void del_update_folder(CString file_pth);