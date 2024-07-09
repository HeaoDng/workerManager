#include"workerManager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
workerManager::workerManager()
{
	this->m_Empnum=0;
	this->m_EmpArray=NULL;
	ifstream ifs;

	//�ļ������ڵ����
	ifs.open(FILENAME,ios::in);
	if(!ifs.is_open())
	{
		cout<<"�ļ�������"<<endl;
		this->m_Empnum=0;
		this->m_FileIsEmpty=true;
		this->m_EmpArray=NULL;
		ifs.close();
		return ;
	}

	//�ļ����ڵ�Ϊ��
	char ch;
	ifs>>ch;
	if(ifs.eof())
	{
		cout<<"�ļ�Ϊ�գ�"<<endl;
		this->m_Empnum=0;
		this->m_EmpArray=NULL;
		this->m_FileIsEmpty=true;
		ifs.close();
		return ;
	}

	int num=this->get_EmpNum();
	cout<<"ְ������Ϊ��"<<num<<endl;
	this->m_Empnum=num;

	this->m_EmpArray=new worker*[this->m_Empnum];
	this->init_Emp();
	for(int i=0;i<this->m_Empnum;i++)
	{
		cout<<"ְ���ţ�"<<this->m_EmpArray[i]->m_id
			<<"ְ��������"<<this->m_EmpArray[i]->m_name
			<<"���ű�ţ�"<<this->m_EmpArray[i]->m_deptId<<endl;
	}
}
void workerManager::show_Menu()
{
    cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ�� **********" << endl;
	cout << "*************  0.�˳��������  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void workerManager::Add_Emp()
{
	cout<<"����������Ա����������"<<endl;
	int addNum=0;
	cin>>addNum;
	if(addNum>0)
	{
		int newSize=m_Empnum+addNum;
		worker** newArray=new worker*[newSize];
		if(this->m_EmpArray!=NULL)
		{
			for(int i=0;i<this->m_Empnum;i++)
			{
				newArray[i]=m_EmpArray[i];
			}
		}

		for(int i=0;i<addNum;i++)
		{
			int id;
			string name;
			int dId;
			cout<<"�������"<<i+1<<"����Ա��id��"<<endl;
			cin>>id;

			cout<<"�������"<<i+1<<"����Ա��������"<<endl;
			cin>>name;

			cout<<"��ѡ���ְ���ĸ�λ��"<<endl;
			cout<<"1.��ְͨ��"<<endl;
			cout<<"2.����"<<endl;
			cout<<"3.�ϰ�"<<endl;
			cin>>dId;

			worker* worker=NULL;
			switch(dId)
			{
			case 1:
				worker = new Employee(id,name,1);
				break;
			case 2:
				worker = new Manager(id,name,2);
				break;
			case 3:
				worker = new Boss(id,name,3);
				break;
			default:
				break;
			}
			newArray[this->m_Empnum+i]=worker;

		}
		delete[]this->m_EmpArray;

		this->m_EmpArray=newArray;

		this->m_Empnum=newSize;

		this->m_FileIsEmpty=false;

		cout<<"��ӳɹ�"<<addNum<<"����ְ����"<<endl;

		this->save();
	}
	else
	{
		cout<<"��������"<<endl;
	}

	system("pause");
	system("cls");
}

void workerManager::exitsystem()
{
	cout<<"��ӭ�´�ʹ��"<<endl;
	system("pause");
	exit(0);
}

void workerManager::save()
{

	ofstream ofs;
	ofs.open(FILENAME,ios::out);

	for(int i=0;i<this->m_Empnum;i++)
	{
		ofs<<this->m_EmpArray[i]->m_id<<"\t"
		<<this->m_EmpArray[i]->m_name<<"\t"
		<<this->m_EmpArray[i]->m_deptId<<endl;
	}

	ofs.close();

}

int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int id;
	string name;
	int dId;

	int num=0;

	while(ifs>>id&&ifs>>name&&ifs>>dId)
	{
		num++;
	}
	ifs.close();

	return num;
}

void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME,ios::in);

	int index=0;

	int id;
	string name;
	int dId;

	while(ifs>>id&&ifs>>name&&ifs>>dId)
	{
		worker* worker=NULL;

		if(dId==1)
		{
			worker=new Employee(id,name,dId);
		}
		else if(dId==2)
		{
			worker = new Employee(id,name,dId);
		}
		else
		{
			worker = new Boss(id,name,dId);
		}
		this->m_EmpArray[index]=worker;
		index++;
	}
}

void workerManager::Show_Emp()
{
	if(m_FileIsEmpty)
	{
		cout<<"�ļ������ڻ��¼Ϊ��"<<endl;
	}
	else
	{
		for(int i=0;i<m_Empnum;i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}

	system("pause");
	system("cls");
}

void workerManager::Del_Emp()
{
	if(this->m_FileIsEmpty)
	{
		cout<<"�ļ������ڻ���Ϊ�գ�"<<endl;
	}
	else
	{
		cout<<"��������Ҫɾ����ְ���ţ�";
		int id=0;
		cin>>id;

		int index=this->IsExist(id);

		if(index!=-1)
		{
			for(int i=index;i<this->m_Empnum-1;i++)
			{
				this->m_EmpArray[i]=this->m_EmpArray[i+1];
			}
			this->m_Empnum--;

			this->save();
			cout<<"ɾ���ɹ�!"<<endl;
		}
		else
		{
			cout<<"ɾ��ʧ�ܣ�û�ҵ���ְ����"<<endl;
		}
	}

	system("pause");
	system("cls");
}

int workerManager::IsExist(int id)
{
	int index=-1;
	for(int i=0;i<this->m_Empnum;i++)
	{
		if(this->m_EmpArray[i]->m_id==id)
		{
			index=i;
		}
	}
	return index;
}

void workerManager::Mod_Emp()
{
	if(m_FileIsEmpty)
	{
		cout<<"�ļ������ڻ�����Ϊ�գ�"<<endl;
	}
	else
	{
		cout<<"������Ҫ�޸ĵ�ְ����ţ�";
		int id;
		cin>>id;

		int ret=this->IsExist(id);
		if(ret)
		{
			delete this->m_EmpArray[ret];

			int newid;
			string newname;
			int dSelect;

			cout<<"�鵽��"<<id<<"��ְ�����������µ�ְ���ţ�";
			cin>>newid;

			cout<<"��������������";
			cin>>newname;

			cout<<"�������λ��"<<endl;
			cout<<"1����ͨԱ��"<<endl;
			cout<<"2������"<<endl;
			cout<<"3���ϰ�"<<endl;
			cin>>dSelect;

			worker* worker=NULL;

			switch(dSelect)
			{
				case 1:
					worker=new Employee(newid,newname,dSelect);
					break;
				case 2:
					worker=new Manager(newid,newname,dSelect);
					break;
				case 3:
					worker = new Boss(newid,newname,dSelect);
					break;
				default:
					break;
			}
			this->m_EmpArray[ret]=worker;

			cout<<"�޸ĳɹ�������"<<endl;

			this->save();
		}
		else
		{
			cout<<"�޸�ʧ�ܣ����޴��ˣ�"<<endl;
		}
	}

	system("pause");
	system("cls");
}

void workerManager::Find_Emp()
{
	if(this->m_FileIsEmpty)
	{
		cout<<"�ļ������ڻ�����Ϊ��"<<endl;
	}
	else
	{
		cout<<"������Ҫ���ҵķ�ʽ��"<<endl
		<<"1������ְ���Ų���"<<endl
		<<"2��������������"<<endl;

		int select;
		cin>>select;

		if(select==1)
		{
			int id;
			cout<<"������Ҫ���ҵ�ְ�����:";
			cin>>id;

			int ret=IsExist(id);
			if(ret!=-1)
			{
				cout<<"���ҳɹ�!��ְ����Ϣ���£�"<<endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout<<"��ְ��������"<<endl;
			}
		}
		else if(select==2)
		{
			cout<<"������Ҫ���ҵ�ְ������:";
			string name;
			cin>>name;

			bool flag=false;
			for(int i=0;i<this->m_Empnum;i++)
			{
				if(this->m_EmpArray[i]->m_name==name)
				{
					cout<<"���ҳɹ�!��ְ����Ϣ���£�"<<endl;
					this->m_EmpArray[i]->showInfo();
					flag=true;
				}
			}
			if(!flag)
			{
				cout<<"��ְ��������"<<endl;
			}
		}
		else
		{
			cout<<"�����������������"<<endl;
		}
	}
	
	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if(this->m_FileIsEmpty)
	{
		cout<<"�ļ�Ϊ�գ��޷�����"<<endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout<<"��ѡ������ʽ"<<endl;
		cout<<"1.��ְ���������"<<endl;
		cout<<"2.��ְ����Ž���"<<endl;

		int select=0;
		cin>>select;

		for(int i=0;i<this->m_Empnum;i++)
		{
			int minOrmax=i;
			for(int j=i+1;j<this->m_Empnum;j++)
			{
				//����
				if(select==1&&this->m_EmpArray[minOrmax]->m_id>this->m_EmpArray[j]->m_id)
				{
					minOrmax=j;
				}
				else//����
				{
					if(select==2&&this->m_EmpArray[minOrmax]->m_id<this->m_EmpArray[j]->m_id)
					{
						minOrmax=j;
					}
				}
			}
			if(minOrmax!=i)
			{
				worker* temp=this->m_EmpArray[i];
				this->m_EmpArray[i]=this->m_EmpArray[minOrmax];
				this->m_EmpArray[minOrmax]=temp;
			}
			
		}
		cout<<"����ɹ�"<<endl;
		this->save();
		this->Show_Emp();
	}
}

void workerManager::Clear_File()
{
	cout<<"ȷ����գ�"<<endl;
	cout<<"1.ȷ��"<<endl;
	cout<<"2.ȡ��"<<endl;

	int select;
	cin>>select;

	if(select==1)
	{
		ofstream ofs(FILENAME,ios::trunc);
		ofs.close();

		if(this->m_EmpArray)
		{
			for(int i=0;i<this->m_Empnum;i++)
			{
				if(this->m_EmpArray[i]!=NULL)
				{
					delete this->m_EmpArray[i];
				}
			}
			this->m_Empnum=0;
			delete []this->m_EmpArray;
			this->m_EmpArray=NULL;
			this->m_FileIsEmpty=true;
		}
		cout<<"����ļ��ɹ�"<<endl;
	}
	system("pause");
	system("cls");
}

workerManager::~workerManager()
{
	if(this->m_EmpArray!=NULL)
	{
		delete[]this->m_EmpArray;
		this->m_EmpArray=NULL;
	}
}