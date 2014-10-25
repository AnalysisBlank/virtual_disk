
#include "StdAfx.h"
#include "file_system.h"
#include "time.h"
//���̳�ʼ��
void init_disk(disk& v_disk,char* t_disk_start,char* t_disk_name,unsigned long t_disk_size)
{
	v_disk.disk_start=t_disk_start;
	memcpy(v_disk.disk_name,t_disk_name,strlen(t_disk_name));
	v_disk.total_space=t_disk_size;
	v_disk.used_space=0;
	int x=0;
}
//�ļ�FCB��ʼ��
void init_FCB_FILE(FCB& c_fcb)

{
	memset(&c_fcb,0,56);
	//	struct tm *ptr;
	time_t lt;
	lt =time(NULL);
	c_fcb.create_time=lt;
	c_fcb.update_time=lt;
	c_fcb.file_properties=0x60;//��ͨ�ļ����ɶ�����д������ִ��
	memset(c_fcb.other_use,0,7);
}

//Ŀ¼FCB��ʼ��
void init_FCB_FOLDER(FCB& c_fcb)
{
	//	struct tm *ptr;
	time_t lt;
	lt =time(NULL);
	c_fcb.create_time=lt;
	c_fcb.update_time=lt;
	c_fcb.file_properties=0xE0;//Ŀ¼�ļ����ɶ�����д������ִ�У�1110��
	memset(c_fcb.other_use,0,7);
	c_fcb.file_size=1024*4;
}


//Ŀ¼�ļ���ʼ��
void init_index(index& c_index)
{
	c_index.file_number=0;
}
/*
//�����ļ�
bool create_file(char* file_name,char* current_index);//���統ǰĿ¼���ļ���ĿΪ1024����ʧ��

  //ɾ���ļ�
  bool delete_file(char* file_name,char* current_index);//�����ļ�Ϊֻ��ɾ��ʧ��
  //�ƶ��ļ�
  bool move_file(char* file_name,char* s_index,char* d_index);//����Ŀ��Ŀ¼��ĿΪ1024�ƶ�ʧ��
  //�ļ�����
  bool update_file_name(char* file_name,char* new_file_name);//�������ļ�������32bytes����ʧ��
*/
void update_disk_used_size(unsigned int sz)//���´���ʹ�ô�С
{
	file_offset+=sz;
	memcpy(disk_start+28,&file_offset,4);
}
void update_head_use(unsigned int sz)//���¹���ռ�ʹ�ô�С
{
	v_disk.used_space+=sz;
	memcpy(disk_start,&v_disk,24);
}
void update_file_number()//�����ļ���Ŀ������
{
	fcb_number+=1;
	memcpy(disk_start+24,&fcb_number,4);
}
void update_file_offset(unsigned long f_offset)
{
	file_offset+=f_offset;
	memcpy(disk_start+28,&file_offset,4);
}
void copy_fcb(FCB& f_fcb)//fcb���Ƶ�������
{
	memcpy(disk_start+v_disk.used_space,&f_fcb,sizeof(f_fcb));
	v_disk.used_space+=sizeof(f_fcb);
	memcpy(disk_start,&v_disk,sizeof(v_disk));
	
	fcb_number++;
	memcpy(disk_start+24,&fcb_number,4);
}
void copy_folder(index& t_index)//��Ŀ¼����
{
	memcpy(disk_start+file_offset,&t_index,4096);
	file_offset+=4096;
	memcpy(disk_start+28,&file_offset,4);
}
void copy_file(char* file,DWORD file_len)//�ļ����Ƶ�������
{
	memcpy(disk_start+file_offset,file,file_len);
	file_offset+=file_len;
	memcpy(disk_start+28,&file_offset,4);
}
bool char_Z_compare(char* ch1,char* ch2)//����Ƚ�
{
	if (strlen(ch1)==strlen(ch2))
	{
		CString str1=ch1;
		CString str2=ch2;
		if (!str1.Compare(ch2))
		{
			return true;
		}
	}
	return FALSE;
}
char* get_folder_start(CString folder_path)//�����ļ���·�����ҵ�Ŀ¼�ļ��洢�������ַ
{
	if (!folder_path.Compare("/"))//��Ŀ¼
	{
		return disk_start+4*1024*1024;
	}
	unsigned int index_level=0;//�ļ��в���
	int i;
	for (i=0;i<folder_path.GetLength();i++)
	{
		if (folder_path.GetAt(i)=='/')
		{
			index_level++;
		}
	}
	char** folder=new char*[index_level];
	for (i=0;i<index_level;i++)
	{
		folder[i]=new char[32];
	}
	//�������ļ��������õ���ά������
	folder[0]="/";//��Ŀ¼
	int j=0;
	int cstr_index=1;
	for (i=1;i<index_level;i++)
	{
		j=0;
		while (folder_path.GetAt(cstr_index)!='/')
		{
			folder[i][j]=folder_path.GetAt(cstr_index);
			cstr_index++;
			j++;
		}
		folder[i][j]=0;
		j++;cstr_index++;
	}
	//�����ҵ���ά�����е��ļ���
	char* folder_store;
	FCB f_fcb;
	index f_index;//�ļ����ļ�
	folder_store=disk_start+4*1024*1024;
	for (i=1;i<index_level;i++)
	{
		memcpy(&f_index,folder_store,4*1024);
		for (j=0;j<f_index.file_number;j++)
		{
			memcpy(&f_fcb,disk_start+32+56*f_index.fcb_index[j],56);
			if (char_Z_compare(folder[i],f_fcb.file_name))
			{
				folder_store=disk_start+f_fcb.file_start;//���̿�ʼλ��+Ŀ¼�ļ�ƫ��
				break;
			}
		}
	}
	return folder_store;
}
void add_file_to_folder(CString folder_path,unsigned int f_fcb_number)
{
	char* folder_store;
	FCB f_fcb;
	index f_index;//Ŀ¼�ļ�
	folder_store=get_folder_start(folder_path);
	memcpy(&f_index,folder_store,4*1024);
	f_index.file_number++;
	f_index.fcb_index[f_index.file_number-1]=f_fcb_number;
	//��дĿ¼�ļ�
	memcpy(folder_store,&f_index,4*1024);
}
char* get_fcb_by_path(CString file_path)//ͨ���ļ�·���ҵ�fcb
{
	if (!file_path.Compare("/"))//��Ŀ¼
	{
		return disk_start+32;
	}
	unsigned int index_level=0;//�ļ��в���
	int i;
	for (i=0;i<file_path.GetLength();i++)
	{
		if (file_path.GetAt(i)=='/')
		{
			index_level++;
		}
	}
	char** folder=new char*[index_level];
	for (i=0;i<index_level;i++)
	{
		folder[i]=new char[32];
	}
	//�������ļ��������õ���ά������
	folder[0]="/";//��Ŀ¼
	int j=0;
	int cstr_index=1;
	for (i=1;i<index_level;i++)
	{
		j=0;
		while (file_path.GetAt(cstr_index)!='/')
		{
			folder[i][j]=file_path.GetAt(cstr_index);
			cstr_index++;
			j++;
		}
		folder[i][j]=0;
		j++;cstr_index++;
	}
	//�����ҵ���ά�����е��ļ���
	char* folder_store;
	FCB f_fcb;
	index f_index;//�ļ����ļ�
	folder_store=disk_start+4*1024*1024;
	int fcb_offset=0;
	for (i=1;i<index_level;i++)
	{
		memcpy(&f_index,folder_store,4*1024);
		for (j=0;j<f_index.file_number;j++)
		{
			fcb_offset=32+56*f_index.fcb_index[j];
			memcpy(&f_fcb,fcb_offset+disk_start,56);
			if (char_Z_compare(folder[i],f_fcb.file_name))
			{
				folder_store=disk_start+f_fcb.file_start;//���̿�ʼλ��+Ŀ¼�ļ�ƫ��
				break;
			}
		}
	}
	char* folder_fcb=disk_start+fcb_offset;
	
	if (file_path.Right(1).Compare(_T("/")))
	{
		//������ļ�
		char file_name[32];
		memset(file_name,0,32);
		CString cstr_file_name=file_path.Right(file_path.GetLength()-file_path.ReverseFind('/')-1);
		memcpy(file_name,cstr_file_name.GetBuffer(cstr_file_name.GetLength()),cstr_file_name.GetLength());
		memset(&f_index,0,4096);
		memcpy(&f_index,folder_store,4*1024);
		for (j=0;j<f_index.file_number;j++)
		{
			fcb_offset=32+56*f_index.fcb_index[j];
			memset(&f_fcb,0,56);
			memcpy(&f_fcb,fcb_offset+disk_start,56);
			if (char_Z_compare(file_name,f_fcb.file_name))
			{
				folder_store=disk_start+f_fcb.file_start;//���̿�ʼλ��+Ŀ¼�ļ�ƫ��
				break;
			}
		}
		char* file_fcb=disk_start+fcb_offset;
		return file_fcb;
	}
	return folder_fcb;
	
}
//ͨ���ļ�·����ȡ�ļ���
CString get_fn_by_pth(CString file_path)
{
	CString cstr_file_name=file_path.Right(file_path.GetLength()-file_path.ReverseFind('/')-1);
	return cstr_file_name;
}
//ͨ��Ŀ¼ɾ���ļ�
void del_file_by_path(CString file_path)
{
	char* pFcb=get_fcb_by_path(file_path);
	//��FCB��������
	memset(&folder_fcb,0,56);
	memcpy(&folder_fcb,pFcb,56);
	//�����ƶ�FCB
	FCB tp_fcb;
	
	//��ɾ���ļ���С
	unsigned long tfile_size=folder_fcb.file_size;
	
	int fcb_offset=(pFcb-disk_start-32)/56;//��ɾ�ļ���FCB�����±�
	int i=0;
	for (i=0;i<fcb_number-fcb_offset;i++)
	{
		memset(&tp_fcb,0,56);
		
		memcpy(&tp_fcb,pFcb+56,56);
		tp_fcb.file_start=tp_fcb.file_start-tfile_size;
		memcpy(pFcb,&tp_fcb,56);
		pFcb+=56;
	}

	fcb_number--;
	memcpy(disk_start+24,&fcb_number,4);

	//memmove�����������ص�����,ʵ���ļ������ƽ�
	unsigned long tfile_start=folder_fcb.file_start;
	memmove(disk_start+tfile_start,disk_start+tfile_start+tfile_size,file_offset-tfile_start-tfile_size);

	//�޸����а������ƶ�FCB��Ŀ¼�ļ�
	FCB folder_fcb_tp;
	index folder_index_tp;
	char* folder_stt_tp;
	int fnum=0;
	int j;
	for (i=0;i<fcb_number;i++)
	{
		memset(&folder_fcb_tp,0,56);
		memcpy(&folder_fcb_tp,disk_start+32+56*i,56);
		if ((folder_fcb_tp.file_properties&0x80)==0)//�ж����ļ�
		{
			continue;
		}else//��Ŀ¼
		{
			folder_stt_tp=disk_start+folder_fcb_tp.file_start;
			memset(&folder_index_tp,0,4096);
			memcpy(&folder_index_tp,folder_stt_tp,4096);//������Ŀ¼�ļ�
			fnum=folder_index_tp.file_number;
			for (j=0;j<fnum;j++)
			{
				if (folder_index_tp.fcb_index[j]==fcb_offset)//���Ǳ�ɾ�����ļ�
				{
					folder_index_tp.file_number--;
					for (int k=j;k<fnum-1;k++)
					{
						folder_index_tp.fcb_index[k]=folder_index_tp.fcb_index[k+1];
						if (folder_index_tp.fcb_index[k]>fcb_offset)
						{
							folder_index_tp.fcb_index[k]--;
						}	
					}
					break;
				}
				if (folder_index_tp.fcb_index[j]>fcb_offset)//���ƶ��Ķ�-1
				{
					folder_index_tp.fcb_index[j]--;
				}
			}
			memcpy(folder_stt_tp,&folder_index_tp,4096);//Ŀ¼����������
		}

	}
	//���´�����Ϣ
	file_offset-=tfile_size;
	memcpy(disk_start+28,&file_offset,4);

	v_disk.used_space=v_disk.used_space-56;
	memcpy(disk_start,&v_disk,24);
}
//ɾ���ļ�ʱ���޸�Ŀ¼�ļ�
void del_update_folder(CString file_pth)
{
	char* fcb_st=get_fcb_by_path(file_pth);
	int tfcb_number=(fcb_st-disk_start-32)/56;
	char* folder_st=get_folder_start(file_pth);
	index folder;
	memset(&folder,0,4096);
	memcpy(&folder,folder_st,4096);
	int i;
	for ( i=0;i<folder.file_number;i++)
	{
		if (folder.fcb_index[i]==tfcb_number)
		{
			break;
		}
	}
	for (i=i;i<folder.file_number;i++)
	{
		folder.fcb_index[i]=folder.fcb_index[i+1];
	}
	folder.file_number--;
	memcpy(folder_st,&folder,4096);
}