#include"manager.h"
#include<string>
using namespace std;

Manager::Manager(int id,string name,int dId)
{
    this->m_id=id;
    this->m_name=name;
    this->m_deptId=dId;
}
    string Manager::getDeptName()
    {
        return "����";
    }
    void Manager::showInfo()
    {
        cout<<"ְ����ţ�"<<this->m_id
        <<"\tְ��������"<<this->m_name
        <<"\t��λ��"<<this->getDeptName()
        <<"\t��λְ������ϰ彻�������񣬲��·���Ա��"<<endl;
    }