#include"employee.h"
 Employee::Employee(int id,string name,int dId)
{
    this->m_id=id;
    this->m_name=name;
    this->m_deptId=dId;
}
void Employee::showInfo()
{
    cout<<"职工编号："<<this->m_id
    <<"\t职工姓名："<<this->m_name
    <<"\t岗位："<<this->getDeptName()
    <<"\t岗位职责：完成经理交给的任务"<<endl;
}
string Employee::getDeptName()
{
    return "员工";
}

