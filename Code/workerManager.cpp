#include"workerManager.h"
#include"boss.h"
#include"employee.h"
#include"manager.h"
workerManager::workerManager()
{
	this->m_Empnum=0;
	this->m_EmpArray=NULL;
	ifstream ifs;

	//文件不存在的情况
	ifs.open(FILENAME,ios::in);
	if(!ifs.is_open())
	{
		cout<<"文件不存在"<<endl;
		this->m_Empnum=0;
		this->m_FileIsEmpty=true;
		this->m_EmpArray=NULL;
		ifs.close();
		return ;
	}

	//文件存在但为空
	char ch;
	ifs>>ch;
	if(ifs.eof())
	{
		cout<<"文件为空！"<<endl;
		this->m_Empnum=0;
		this->m_EmpArray=NULL;
		this->m_FileIsEmpty=true;
		ifs.close();
		return ;
	}

	int num=this->get_EmpNum();
	cout<<"职工个数为："<<num<<endl;
	this->m_Empnum=num;

	this->m_EmpArray=new worker*[this->m_Empnum];
	this->init_Emp();
	for(int i=0;i<this->m_Empnum;i++)
	{
		cout<<"职工号："<<this->m_EmpArray[i]->m_id
			<<"职工姓名："<<this->m_EmpArray[i]->m_name
			<<"部门编号："<<this->m_EmpArray[i]->m_deptId<<endl;
	}
}
void workerManager::show_Menu()
{
    cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！ **********" << endl;
	cout << "*************  0.退出管理程序  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}
void workerManager::Add_Emp()
{
	cout<<"请输入增加员工的数量："<<endl;
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
			cout<<"请输入第"<<i+1<<"个新员工id："<<endl;
			cin>>id;

			cout<<"请输入第"<<i+1<<"个新员工姓名："<<endl;
			cin>>name;

			cout<<"请选择该职工的岗位："<<endl;
			cout<<"1.普通职工"<<endl;
			cout<<"2.经理"<<endl;
			cout<<"3.老板"<<endl;
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

		cout<<"添加成功"<<addNum<<"名新职工！"<<endl;

		this->save();
	}
	else
	{
		cout<<"输入有误"<<endl;
	}

	system("pause");
	system("cls");
}

void workerManager::exitsystem()
{
	cout<<"欢迎下次使用"<<endl;
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
		cout<<"文件不存在或记录为空"<<endl;
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
		cout<<"文件不存在或者为空！"<<endl;
	}
	else
	{
		cout<<"请输入想要删除的职工号：";
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
			cout<<"删除成功!"<<endl;
		}
		else
		{
			cout<<"删除失败，没找到次职工！"<<endl;
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
		cout<<"文件不存在或者是为空！"<<endl;
	}
	else
	{
		cout<<"请输入要修改的职工编号：";
		int id;
		cin>>id;

		int ret=this->IsExist(id);
		if(ret)
		{
			delete this->m_EmpArray[ret];

			int newid;
			string newname;
			int dSelect;

			cout<<"查到："<<id<<"号职工，请输入新的职工号：";
			cin>>newid;

			cout<<"请输入新姓名：";
			cin>>newname;

			cout<<"请输入岗位："<<endl;
			cout<<"1、普通员工"<<endl;
			cout<<"2、经理"<<endl;
			cout<<"3、老板"<<endl;
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

			cout<<"修改成功！！！"<<endl;

			this->save();
		}
		else
		{
			cout<<"修改失败，查无此人！"<<endl;
		}
	}

	system("pause");
	system("cls");
}

void workerManager::Find_Emp()
{
	if(this->m_FileIsEmpty)
	{
		cout<<"文件不存在或者是为空"<<endl;
	}
	else
	{
		cout<<"请输入要查找的方式："<<endl
		<<"1、按照职工号查找"<<endl
		<<"2、按照姓名查找"<<endl;

		int select;
		cin>>select;

		if(select==1)
		{
			int id;
			cout<<"请输入要查找的职工编号:";
			cin>>id;

			int ret=IsExist(id);
			if(ret!=-1)
			{
				cout<<"查找成功!该职工信息如下："<<endl;
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout<<"该职工不存在"<<endl;
			}
		}
		else if(select==2)
		{
			cout<<"请输入要查找的职工姓名:";
			string name;
			cin>>name;

			bool flag=false;
			for(int i=0;i<this->m_Empnum;i++)
			{
				if(this->m_EmpArray[i]->m_name==name)
				{
					cout<<"查找成功!该职工信息如下："<<endl;
					this->m_EmpArray[i]->showInfo();
					flag=true;
				}
			}
			if(!flag)
			{
				cout<<"该职工不存在"<<endl;
			}
		}
		else
		{
			cout<<"输入错误，请重新输入"<<endl;
		}
	}
	
	system("pause");
	system("cls");
}

void workerManager::sort_Emp()
{
	if(this->m_FileIsEmpty)
	{
		cout<<"文件为空，无法排序"<<endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout<<"请选择排序方式"<<endl;
		cout<<"1.按职工编号升序"<<endl;
		cout<<"2.按职工编号降序"<<endl;

		int select=0;
		cin>>select;

		for(int i=0;i<this->m_Empnum;i++)
		{
			int minOrmax=i;
			for(int j=i+1;j<this->m_Empnum;j++)
			{
				//升序
				if(select==1&&this->m_EmpArray[minOrmax]->m_id>this->m_EmpArray[j]->m_id)
				{
					minOrmax=j;
				}
				else//降序
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
		cout<<"排序成功"<<endl;
		this->save();
		this->Show_Emp();
	}
}

void workerManager::Clear_File()
{
	cout<<"确认清空？"<<endl;
	cout<<"1.确认"<<endl;
	cout<<"2.取消"<<endl;

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
		cout<<"清空文件成功"<<endl;
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