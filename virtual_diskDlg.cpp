// virtual_diskDlg.cpp : implementation file
//

#include "stdafx.h"
#include "virtual_disk.h"
#include "virtual_diskDlg.h"
#include "dlg_create_disk.h"
#include "file_system.h"
#include "dlg_create_folder.h"
#include "time.h"
#include <stdlib.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//�Զ��嶨����Ϣ������ˢ�½���
#define WM_MYUPDATEDATA WM_USER+100

CVirtual_diskDlg* pdlg;
//���Զ��̷߳���Ϣ����
DWORD WINAPI test(LPVOID lparm)
{
	pdlg->m_current_folder_path="1111111";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(5000);
return 0;
}
DWORD WINAPI test_virtualdisk(LPVOID lparm)
{
		// TODO: ���Ժ���
/*	while(1)
	{

	}
*/
	//1.����Ŀ¼
	time_t lt;//Ϊ��־���ʱ��

	while(!g_is_test_stop)
	{

	Sleep(1000);
	HTREEITEM root=pdlg->m_tree.GetRootItem();
	pdlg->m_tree.SelectItem(root);//ѡ��root

	pdlg->test_add_folder();//root�����һ��Ŀ¼
	pdlg->m_current_option="���Ŀ¼";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);


	HTREEITEM root_child=pdlg->m_tree.GetChildItem(root);
	pdlg->m_tree.SelectItem(root_child);//ѡ��ո���ӵ�Ŀ¼
	
	pdlg->test_add_file();
	pdlg->m_current_option="����ļ�";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	pdlg->test_add_file();
	pdlg->m_current_option="����ļ�";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 

	Sleep(1000);
	pdlg->m_tree.SelectItem(root_child);
	pdlg->test_add_folder();//root�����һ��Ŀ¼
	pdlg->m_current_option="���Ŀ¼";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 

	Sleep(1000);
 
	HTREEITEM node_2=pdlg->m_tree.GetChildItem(root_child);
	HTREEITEM t_node=pdlg->m_tree.GetNextItem(node_2,TVGN_NEXT );
	t_node=pdlg->m_tree.GetNextItem(t_node,TVGN_NEXT );//��λ��Ŀ¼
	
	pdlg->m_tree.SelectItem(t_node);//ѡ�иո���ӵ�Ŀ¼
	pdlg->test_add_file();
	pdlg->m_current_option="����ļ�";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);

	pdlg->m_tree.SelectItem(t_node);//ѡ�иո���ӵ�Ŀ¼
	pdlg->test_add_file();
	pdlg->m_current_option="����ļ�";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);

	//ɾ���ļ�
	node_2=t_node;//�游�ڵ�
	t_node=pdlg->m_tree.GetChildItem(t_node);//���ӽڵ�
	t_node=pdlg->m_tree.GetNextItem(t_node,TVGN_NEXT);//ѡ��
	pdlg->m_tree.SelectItem(t_node);
	pdlg->test_del_file();//ɾ��
	pdlg->m_current_option="ɾ���ļ�";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);

	//ɾ���ļ�
	t_node=node_2;
	t_node=pdlg->m_tree.GetChildItem(t_node);//���ӽڵ�
	pdlg->m_tree.SelectItem(t_node);
	pdlg->test_del_file();//ɾ��
	pdlg->m_current_option="ɾ���ļ�";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);

	//ɾ��Ŀ¼
	t_node=node_2;
	pdlg->m_tree.SelectItem(t_node);
	pdlg->test_del_file();//ɾ��
	pdlg->m_current_option="ɾ��Ŀ¼";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	Sleep(1000);
	
	//��ʽ��
	pdlg->formatVDISK();
	pdlg->m_current_option="��ʽ���������";
	time(&lt);
	pdlg->m_test_log+=pdlg->m_current_option+ctime(&lt)+"\r\n";
	Sleep(2000);
	pdlg->SendMessage(WM_MYUPDATEDATA,FALSE); 
	
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtual_diskDlg dialog

CVirtual_diskDlg::CVirtual_diskDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVirtual_diskDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVirtual_diskDlg)
	m_current_file_path = _T("");
	m_current_folder_path = _T("");
	m_disk_name = _T("");
	m_disk_remain_space = 0;
	m_disk_dotal_space = 0;
	m_new_name = _T("");
	m_paste_pad = _T("");
	m_fcb_index = 0;
	m_current_file_offset = 0;
	m_current_file_size = 0;
	m_current_option = _T("");
	m_test_log = _T("");
	m_file_update_time = _T("");
	m_file_create_time = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtual_diskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVirtual_diskDlg)
	DDX_Control(pDX, IDC_TREE_FILES, m_tree);
	DDX_Text(pDX, IDC_EDIT_CURRENT_FILE, m_current_file_path);
	DDX_Text(pDX, IDC_EDIT_CURRENT_FOLDER, m_current_folder_path);
	DDX_Text(pDX, IDC_EDIT_DISK_NAME, m_disk_name);
	DDX_Text(pDX, IDC_EDIT_DISK_REMAIN, m_disk_remain_space);
	DDX_Text(pDX, IDC_EDIT_DISK_TOTAL, m_disk_dotal_space);
	DDX_Text(pDX, IDC_EDIT_NEW_NAME, m_new_name);
	DDX_Text(pDX, IDC_EDIT_PASTE_PAD, m_paste_pad);
	DDX_Text(pDX, IDC_EDIT_FCB_INDEX, m_fcb_index);
	DDX_Text(pDX, IDC_EDIT_FILE_OFFSET, m_current_file_offset);
	DDX_Text(pDX, IDC_EDIT_FILE_SIZE, m_current_file_size);
	DDX_Text(pDX, IDC_EDIT_TEST_CURRENT_OP, m_current_option);
	DDX_Text(pDX, IDC_EDIT_TEST_LOG, m_test_log);
	DDX_Text(pDX, IDC_EDIT_FILE_UPDATE_TIME, m_file_update_time);
	DDX_Text(pDX, IDC_EDIT_FILE_CREATE_TIME, m_file_create_time);
	//}}AFX_DATA_MAP
}
//�޸Ĳ������Ϣ
BEGIN_MESSAGE_MAP(CVirtual_diskDlg, CDialog)
	//{{AFX_MSG_MAP(CVirtual_diskDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE_FILE, OnButtonCreateFile)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_FILES, OnSelchangedTreeFiles)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_DISK, OnButtonCreateDisk)
	ON_BN_CLICKED(IDC_BUTTON_FORMAT, OnButtonFormat)
	ON_BN_CLICKED(IDC_BUTTON_CREATE_INDEX, OnButtonCreateIndex)
	ON_BN_CLICKED(IDC_BUTTON_DISK_SAVE, OnButtonDiskSave)
	ON_BN_CLICKED(IDC_BUTTON_DISK_IMPORT, OnButtonDiskImport)
	ON_BN_CLICKED(IDC_BUTTON_RENAME, OnButtonRename)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_CUT, OnButtonCut)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnButtonPaste)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, OnButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_TEST_START, OnButtonTestStart)
	ON_MESSAGE(WM_MYUPDATEDATA,OnUpdateMyData)
	ON_BN_CLICKED(IDC_BUTTON_STOP_TEST, OnButtonStopTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVirtual_diskDlg message handlers

BOOL CVirtual_diskDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	HICON hicon[2];
    m_image_list.Create(32,32,ILC_COLOR32,2,2);
    hicon[0]=AfxGetApp()->LoadIcon(IDI_ICON_FOLDER);
    hicon[1]=AfxGetApp()->LoadIcon(IDI_ICON_FILE);
   
    for(int n=0;n<2;n++)
        m_image_list.Add(hicon[n]);
	
    m_tree.SetImageList(&m_image_list,TVSIL_NORMAL); 
	
	//���ø�ʽ��������ļ������Ŀ¼Ϊ��
	GetDlgItem(IDC_BUTTON_FORMAT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CREATE_FILE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CREATE_INDEX)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CUT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
				GetDlgItem(IDC_BUTTON_DISK_SAVE)->EnableWindow(FALSE);
					GetDlgItem(IDC_BUTTON_RENAME)->EnableWindow(FALSE);
						GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(FALSE);
							GetDlgItem(IDC_BUTTON_STOP_TEST)->EnableWindow(FALSE);
								GetDlgItem(IDC_BUTTON_TEST_START)->EnableWindow(FALSE);
									GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(FALSE);
//	m_hAccel=::LoadAccelerators(::AfxGetResourceHandle(),MAKEINTRESOURCE(IDR_ACCELERATOR1));
	pdlg=this;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVirtual_diskDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVirtual_diskDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVirtual_diskDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVirtual_diskDlg::OnButtonCreateFile() 
{
	// TODO: �����ļ�

	CFileDialog dlg(TRUE);
	if (IDOK==dlg.DoModal())
	{
		//��ȡ�ļ�
		char *buffer;
		CFile file(dlg.GetPathName(),CFile::modeRead);

		//�ж��ļ��Ƿ�����
		if (judege_repeat_name(file.GetFileName()))
		{
			//����
			file.Close();
			MessageBox("�ļ�������");
			return;
		}
		

		DWORD f_len=file.GetLength();


		//�ж��ļ��Ƿ����
		if (f_len>v_disk.total_space-v_disk.used_space)
		{
			file.Close();
			MessageBox("�ļ�����");
			return;
		}

		buffer=new char[f_len];
		memset(buffer,0,f_len);
		file.Read(buffer,f_len);
		//����FCB   
		FCB file_fcb;
		init_FCB_FILE(file_fcb);
		file_fcb.file_size=f_len;
		file_fcb.file_start=file_offset;
		
		//����FCB�ļ���
		int str_len=dlg.GetFileName().GetLength();
		memcpy(file_fcb.file_name,dlg.GetFileName().GetBuffer(str_len),str_len);
		//��FCB���Ƶ�������
		copy_fcb(file_fcb);
		//����file_offset
		copy_file(buffer,f_len);
		//����ļ���Ŀ¼
		add_file_to_folder(m_current_folder_path,fcb_number);
		//���ļ�������ӽڵ�
		CString file_path=m_current_folder_path+file.GetFileName();
		tree_add_file(file.GetFileName(),file_path);
		file.Close();
		//���´�����Ϣ
	//	update_disk_used_size(f_len);
		this->update_disk_info();
		UpdateData(FALSE);
	}
}

void CVirtual_diskDlg::OnSelchangedTreeFiles(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: �ļ���ѡ����Ӧ��ť
	//��ȡ��ѡ�еĽڵ�
	this->get_item_path();
	
	FCB t_fcb;
	char* p=get_fcb_by_path(m_current_file_path);
	memcpy(&t_fcb,p,56);
	m_current_file_size=t_fcb.file_size;
	m_current_file_offset=t_fcb.file_start;
	int fcb_index=0;
	fcb_index=(p-disk_start-32)/56;
	m_fcb_index=fcb_index;


	//�ļ��޸�ʱ��
	time_t lt;
	memcpy(&lt,&t_fcb.update_time,4);
	m_file_update_time=ctime(&lt);
	memcpy(&lt,&t_fcb.create_time,4);
	m_file_create_time=ctime(&lt);
	UpdateData(FALSE);
	*pResult = 0;
}

void CVirtual_diskDlg::OnButtonCreateDisk() 
{
	// TODO: ��������
	dlg_create_disk dlg;
	dlg.DoModal();

	//���ø�ʽ��������ļ������Ŀ¼Ϊ��
	GetDlgItem(IDC_BUTTON_FORMAT)->EnableWindow(TRUE);

//	int x=0;
}

void CVirtual_diskDlg::OnButtonFormat() 
{
	// TODO: ��ʽ������
	//ɾ��ԭ����
	m_tree.DeleteAllItems();

	//������Ϣ�ṹ�� 24bytes
	init_disk(v_disk,disk_start,disk_name,disk_size);
	v_disk.used_space=sizeof(v_disk);
	memcpy(disk_start,&v_disk,24);

	//�ļ����ƿ����
	fcb_number=0;
	v_disk.used_space+=4;
	memcpy(disk_start+24,&fcb_number,4);

	//�ļ�ƫ�������disk_start
	file_offset=4*1024*1024;
	memcpy(disk_start+28,&file_offset,4);
	update_head_use(4);
	//��Ŀ¼
		//FCB����
	init_FCB_FOLDER(folder_fcb);
	char *tp="ROOT";
	memcpy(folder_fcb.file_name,tp,strlen(tp));
	folder_fcb.file_start=file_start;
		//FCB ����
	memcpy(disk_start+v_disk.used_space,&folder_fcb,sizeof(folder_fcb));
	v_disk.used_space+=sizeof(folder_fcb);
	memcpy(disk_start,&v_disk,sizeof(v_disk));
		//Ŀ¼����
	init_index(t_index);
	memcpy(disk_start+file_start,&t_index,4096);//�ƶ�����ʼ4K 4M+4K
	update_file_offset(4*1024);
		//��ʾ���ļ�����
	HTREEITEM hroot=m_tree.InsertItem("ROOT",0,0);

	set_itempath("/",hroot);

		//���´�����Ϣ
	this->update_disk_info();

	GetDlgItem(IDC_BUTTON_CREATE_FILE)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CREATE_INDEX)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_CUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_DISK_SAVE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_RENAME)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_PASTE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_STOP_TEST)->EnableWindow(TRUE);
				GetDlgItem(IDC_BUTTON_TEST_START)->EnableWindow(TRUE);
									GetDlgItem(IDC_BUTTON_COPY)->EnableWindow(TRUE);

}
//���´�����Ϣ������
void CVirtual_diskDlg::update_disk_info()
{
	m_disk_dotal_space=v_disk.total_space;
	m_disk_name=v_disk.disk_name;
	m_disk_remain_space=v_disk.total_space-file_offset;
	SendMessage(WM_MYUPDATEDATA,FALSE); 
}
//��һ��CString ��ָ����ڽڵ��У�CString Ϊ�ļ���·��
void CVirtual_diskDlg::set_itempath(CString f_path,HTREEITEM& node)
{
	CString* str=new CString;
	str->Format(f_path);
	unsigned long dwtp=0;
	memcpy(&dwtp,&str,4);
	m_tree.SetItemData(node,dwtp);
}
//��ȡ�ڵ��е��ı�·��
void CVirtual_diskDlg::get_item_path()
{
	CString* str_t;
	HTREEITEM d1=m_tree.GetSelectedItem();
	unsigned d2=m_tree.GetItemData(d1);
	memcpy(&str_t,&d2,4);
	m_current_file_path=*str_t;

	if (!((*str_t).Compare("/")))//��Ŀ¼û�и��ڵ�
	{
		m_current_folder_path=*str_t;
		UpdateData(FALSE);
		return;
	}
	if ((*str_t).Right(1)==_T("/"))//��ǰ�ڵ�Ϊ·��
	{
		m_current_folder_path=*str_t;
	}
	else
	{
		HTREEITEM parent_node=m_tree.GetParentItem(d1);
		d2=m_tree.GetItemData(parent_node);
		memcpy(&str_t,&d2,4);
		m_current_folder_path=*str_t;
	}

	UpdateData(FALSE);
}

void CVirtual_diskDlg::tree_add_file(CString filename,CString filepath)
{
	HTREEITEM sl_it=m_tree.GetSelectedItem();

	HTREEITEM file_node=m_tree.InsertItem(filename,1,1,sl_it);
	set_itempath(filepath,file_node);
	m_tree.Expand(sl_it,TVE_EXPAND);
}

void CVirtual_diskDlg::OnButtonCreateIndex() 
{
	// TODO: ����Ŀ¼
	dlg_create_folder dlg;
	dlg.DoModal();
	//�ж�Ŀ¼����
	if (judege_repeat_name(g_folder_name))
	{
		MessageBox("Ŀ¼������");
		return;
	}
	
		//FCB
	memset(&folder_fcb,0,56);
	init_FCB_FOLDER(folder_fcb);
	memcpy(folder_fcb.file_name,g_folder_name.GetBuffer(g_folder_name.GetLength()),g_folder_name.GetLength());
	folder_fcb.file_start=file_offset;
	
	
	copy_fcb(folder_fcb);
		//Ŀ¼�ļ�
	init_index(t_index);
	copy_folder(t_index);

		//���´���ʹ��
	update_show_disk_info();

		//��������Ŀ¼��Ŀ¼�ļ�
	char* folder_parent=get_folder_start(m_current_folder_path);
	memset(&t_index,0,4096);
	memcpy(&t_index,folder_parent,4096);
	
	t_index.fcb_index[t_index.file_number]=fcb_number;
	t_index.file_number++;
	memcpy(folder_parent,&t_index,4096);
		//�����ļ���
	HTREEITEM node_parent=m_tree.GetSelectedItem();
	HTREEITEM curnt_folder_node=m_tree.InsertItem(g_folder_name,0,0,node_parent);
	CString folder_pth=m_current_folder_path+g_folder_name+"/";
	set_itempath(folder_pth,curnt_folder_node);
	
	
	m_tree.Expand(node_parent,TVE_EXPAND);
	MessageBox("Ŀ¼�����ɹ���");
	UpdateData(FALSE);
}

void CVirtual_diskDlg::OnButtonDiskSave() 
{
	// TODO: ��������
	CFileDialog dlg(FALSE);
	dlg.m_ofn.lpstrTitle="�������";
	if (IDOK==dlg.DoModal())
	{
		CFile file(dlg.GetPathName(),CFile::modeWrite|CFile::modeCreate);
		DWORD file_len=v_disk.total_space;
		file.Write(disk_start,file_len);
		file.Close();
	}

}

void CVirtual_diskDlg::OnButtonDiskImport() 
{
	// TODO: �������
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle="�������";
	if (IDOK==dlg.DoModal())
	{
		CFile file(dlg.GetPathName(),CFile::modeRead);
		DWORD file_len=file.GetLength();
		disk_start=new char[file_len];
		file.Read(disk_start,file_len);//����disk_start
		//���´�����Ϣ
		update_show_disk_info();
		//�����ļ���
		update_disk_tree();
	}
}
//�����ڴ����ݸ����ļ���
void CVirtual_diskDlg::update_file_tree()
{

}
//����ǰ32byte��Ϣ�ֶΣ�������ʾ������Ϣ
void CVirtual_diskDlg::update_show_disk_info()
{
	memcpy(&v_disk,disk_start,24);
	memcpy(&fcb_number,disk_start+24,4);
	memcpy(&file_offset,disk_start+28,4);
	m_disk_name=v_disk.disk_name;
	m_disk_dotal_space=v_disk.total_space;
	m_disk_remain_space=v_disk.total_space-file_offset;
	SendMessage(WM_MYUPDATEDATA,FALSE); 
}

void CVirtual_diskDlg::OnButtonRename() 
{
	UpdateData(TRUE);
	// TODO: �ļ����ļ��У�������
	//fcb �޸�
	char *fio_fcb=get_fcb_by_path(m_current_file_path);
	memcpy(&folder_fcb,fio_fcb,56);
	char new_name[32];
	memset(new_name,0,32);
	memcpy(new_name,m_new_name.GetBuffer(m_new_name.GetLength()),m_new_name.GetLength());
	memcpy(folder_fcb.file_name,new_name,32);
	memcpy(fio_fcb,&folder_fcb,56);
	//�ļ����޸�
	HTREEITEM tn0=m_tree.GetSelectedItem();
	m_tree.SetItemText(tn0,m_new_name);
	DWORD dwfpth=m_tree.GetItemData(tn0);
	CString* cstrfpth;
	memcpy(&cstrfpth,&dwfpth,4);
	*cstrfpth=m_current_folder_path+m_new_name;
	memcpy(&dwfpth,&cstrfpth,4);
	m_tree.SetItemData(tn0,dwfpth);
	m_current_file_path=*cstrfpth;
	UpdateData(false);
}

void CVirtual_diskDlg::OnButtonCopy() 
{
	// TODO: ����
	m_paste_pad=m_current_file_path;
	g_is_copy=true;
	UpdateData(FALSE);
}

void CVirtual_diskDlg::OnButtonCut() 
{
	// TODO: ����
	m_paste_pad=m_current_file_path;
	g_is_copy=false;
	UpdateData(FALSE);
}

void CVirtual_diskDlg::OnButtonPaste() 
{

	//�ж�ճ�����Ƿ�����
	CString fn=get_fn_by_pth(m_paste_pad);
	if (judege_repeat_name(fn))
	{
		MessageBox("�ļ�������");
		return;
	}
	


	// TODO: ճ��
	//�ó�fcb
	char* file_s=get_fcb_by_path(m_paste_pad);
	memset(&folder_fcb,0,56);
	memcpy(&folder_fcb,file_s,56);
//	folder_fcb.file_start=file_offset;


	//�����ļ�
	file_s=disk_start+folder_fcb.file_start;
	copy_file(file_s,folder_fcb.file_size);
	//����fcb
	folder_fcb.file_start=file_offset;
	copy_fcb(folder_fcb);

	//����ļ���Ŀ¼
	file_s=get_fcb_by_path(m_paste_pad);
	unsigned int idn=(file_s-disk_start-32)/56;
	add_file_to_folder(m_current_folder_path,idn);
	//���ļ�������ӽڵ�
	CString file_path=m_current_folder_path+get_fn_by_pth(m_paste_pad);
	tree_add_file(get_fn_by_pth(m_paste_pad),file_path);
	update_disk_used_size(folder_fcb.file_size);
	this->update_disk_info();
	
	if (!g_is_copy)//�Ǽ��оͼ���ɾ������
	{
		//ɾ���ļ�
		del_file_by_path(m_paste_pad);
		//�޸�����·��Ŀ¼�ļ�
		del_update_folder(m_paste_pad);
		//�����ļ���
	//	HTREEITEM sl_n=m_tree.GetSelectedItem();
	//	m_tree.DeleteItem(sl_n);
		m_tree.DeleteAllItems();
		update_disk_tree();
		HTREEITEM root=m_tree.GetRootItem();
		m_tree.Expand(root,TVE_EXPAND);
		m_paste_pad="";
		update_disk_info();
		UpdateData(FALSE);
	}
	
}

void CVirtual_diskDlg::OnButtonDelete() 
{
	// TODO: ɾ���ļ�:ɾ��FCB,�Ѻ����FCB��ǰ�ƶ�,ɾ���ļ�,�Ѻ�����ļ���ǰ�ƶ����޸�FCBnumber,file_offset.�鿴����Ŀ¼�ļ�
	//�޸�Ŀ¼�ļ���FCBnumber(FCB��ǰ�ƶ��˵�)

	//ɾ���ļ�
	del_file_by_path(m_current_file_path);
	//�޸�Ŀ¼�ļ�
//	del_update_folder(m_current_file_path);
	//�����ļ���
	HTREEITEM sl_n=m_tree.GetSelectedItem();
	m_tree.DeleteItem(sl_n);
	
	update_disk_info();
	UpdateData(FALSE);
}
//���ݴ��̸��´�����
void CVirtual_diskDlg::update_disk_tree()
{
	//init
	memcpy(&v_disk,disk_start,24);
	memcpy(&fcb_number,disk_start+24,4);
	memcpy(&file_offset,disk_start+28,4);
	index tfolder;
	//root dir
	memcpy(&tfolder,disk_start+4*1024*1024,4096);
	HTREEITEM root=m_tree.InsertItem("ROOT",0,0);
	set_itempath("/",root);
	
	expand_dir(tfolder,root);
	m_tree.Expand(root,TVE_EXPAND);
}
//����·�����ݹ�չ��Ŀ¼��ӵ���
void CVirtual_diskDlg::expand_dir(index folder,HTREEITEM dir)
{
	int fnumber=folder.file_number;
	FCB tfcb;
	int x=0;
	int fcb_offset=0;
	CString fname;
	CString dir_path=get_node_string(dir);
	
	for (int i=0;i<fnumber;i++)
	{
		x=folder.fcb_index[i];
		fcb_offset=32+56*x;
		memset(&tfcb,0,56);
		memcpy(&tfcb,disk_start+fcb_offset,56);
		if ((tfcb.file_properties&0x80)==0)//�ļ�
		{
			fname.Format(tfcb.file_name);
			HTREEITEM f=m_tree.InsertItem(fname,1,1,dir);
			set_itempath(dir_path+fname,f);
		}else//Ŀ¼
		{
			fname.Format(tfcb.file_name);
			HTREEITEM f=m_tree.InsertItem(fname,0,0,dir);
			set_itempath(dir_path+fname+"/",f);
			
			//FCB -> Folder store
			char* tfolderstt=disk_start+tfcb.file_start;
			index tfolder;
			memset(&tfolder,0,56);
			memcpy(&tfolder,tfolderstt,4096);
			expand_dir(tfolder,f);
		}
	}
	UpdateData(FALSE);
}
//��ȡ���ڵ�Ĵ洢���ַ���
CString CVirtual_diskDlg::get_node_string(HTREEITEM node)
{
	CString* str_t;
	HTREEITEM d1=node;
	unsigned d2=m_tree.GetItemData(d1);
	memcpy(&str_t,&d2,4);
	return *str_t;
	
}
//�ж��ļ��Ƿ�����
bool CVirtual_diskDlg::judege_repeat_name( CString fname)
{
	bool is_rept=false;
	HTREEITEM flder=m_tree.GetSelectedItem();
	HTREEITEM cld;
	cld=m_tree.GetChildItem(flder);

	CString name_tp;
	while (cld!=NULL)
	{
		name_tp = m_tree.GetItemText(cld);
		if (!name_tp.Compare(fname))//�ҵ��ļ�����ͬ���ļ�
		{
			is_rept=true;
		}
		cld=m_tree.GetNextSiblingItem(cld);
	}
	return is_rept;
}
//���ڿ�ʼ����
void CVirtual_diskDlg::OnButtonTestStart() 
{
	g_is_test_stop=false;
	HANDLE testThread=CreateThread(NULL, 0, test_virtualdisk, NULL, 0, NULL);
	CloseHandle(testThread);
}
//���ڲ���ʱ����Զ������ļ�(����ļ����������С)
void CVirtual_diskDlg::test_add_file()
{
	srand((int)time(0));
	unsigned int f_len=rand()%(4*1024*1024);//�������4M���µ�����
	char* buffer=new char[f_len];
	memset(buffer,56,f_len);//��ʼ������

	//�ж��ļ��Ƿ����
	if (f_len>v_disk.total_space-v_disk.used_space)
	{
		m_test_log+="�Զ����ɵ��ļ������޷�������\r\n";
		return;
	}
	//�����ļ���
	char* file_name=new char[12];
	int i,rd;
	for (i=0;i<11;i++)
	{
		rd=rand()%26;
		file_name[i]=65+rd;
	}
	file_name[11]=0;
	//����FCB   
	FCB file_fcb;
	init_FCB_FILE(file_fcb);
	file_fcb.file_size=f_len;
	file_fcb.file_start=file_offset;
	
	//����FCB�ļ���
	memcpy(file_fcb.file_name,file_name,11);
	//��FCB���Ƶ�������
	copy_fcb(file_fcb);
	//����file_offset
	copy_file(buffer,f_len);
	//����ļ���Ŀ¼
	add_file_to_folder(m_current_folder_path,fcb_number);
	//���ļ�������ӽڵ�
	CString file_path=m_current_folder_path+file_name;
	tree_add_file(file_name,file_path);
	//���´�����Ϣ
	//	update_disk_used_size(f_len);
	this->update_disk_info();
	SendMessage(WM_MYUPDATEDATA,FALSE); 

}
//�������ļ���
void CVirtual_diskDlg::test_add_folder()
{
	srand((int)time(0));
	//�������Ŀ¼��
	char* folder_name=new char[12];
	int i,rd;
	for (i=0;i<11;i++)
	{
		rd=rand()%26;
		folder_name[i]=65+rd;
	}
	folder_name[11]=0;
	//���Ŀ¼
	//FCB
	memset(&folder_fcb,0,56);
	init_FCB_FOLDER(folder_fcb);
	memcpy(folder_fcb.file_name,folder_name,11);
	folder_fcb.file_start=file_offset;
	
	
	copy_fcb(folder_fcb);
	//Ŀ¼�ļ�
	init_index(t_index);
	copy_folder(t_index);
	
	//���´���ʹ��
	update_show_disk_info();
	
	//��������Ŀ¼��Ŀ¼�ļ�
	char* folder_parent=get_folder_start(m_current_folder_path);
	memset(&t_index,0,4096);
	memcpy(&t_index,folder_parent,4096);
	
	t_index.fcb_index[t_index.file_number]=fcb_number;
	t_index.file_number++;
	memcpy(folder_parent,&t_index,4096);
	//�����ļ���
	HTREEITEM node_parent=m_tree.GetSelectedItem();
	HTREEITEM curnt_folder_node=m_tree.InsertItem(folder_name,0,0,node_parent);
	CString folder_pth=m_current_folder_path+folder_name+"/";
	set_itempath(folder_pth,curnt_folder_node);
	
	m_tree.Expand(node_parent,TVE_EXPAND);
	SendMessage(WM_MYUPDATEDATA,FALSE); 

}
//ɾ����ѡ��Ŀ¼
void CVirtual_diskDlg::test_del_file()
{
	
	//ɾ���ļ�
	del_file_by_path(m_current_file_path);
	//�޸�Ŀ¼�ļ�
	//	del_update_folder(m_current_file_path);
	//�����ļ���
	HTREEITEM sl_n=m_tree.GetSelectedItem();
	m_tree.DeleteItem(sl_n);
	
	update_disk_info();
	SendMessage(WM_MYUPDATEDATA,FALSE); 

}

void CVirtual_diskDlg::OnUpdateMyData()
{
	//ˢ������
	UpdateData(FALSE);
	//ˢ�¹�����
	CEdit* p=(CEdit*)GetDlgItem(IDC_EDIT_TEST_LOG);
	p->LineScroll(p->GetLineCount()-1);
}

void CVirtual_diskDlg::formatVDISK()
{
	this->OnButtonFormat();
}

void CVirtual_diskDlg::OnButtonStopTest() 
{
	// TODO:ֹͣ����
	g_is_test_stop=true;
}
