#include"boss.h"
#include<string>
using namespace std;

Boss::Boss(int id,string name,int dId)
{
    this->m_id=id;
    this->m_name=name;
    this->m_deptId=dId;
}
void Boss::showInfo()
{
    cout<<"职工编号："<<this->m_id
        <<"\t职工姓名；"<<this->m_name
        <<"\t岗位："<<this->getDeptName()
        <<"\t岗位职责：管理公司所有事务"<<endl;
}
string Boss::getDeptName()
{
    return "总裁";
}