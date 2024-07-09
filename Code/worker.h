#pragma once
#include <iostream>
using namespace std;
#include <string>

//职工抽象类

class worker
{
public:

    virtual void showInfo()=0;
    virtual string getDeptName()=0;

    int m_id;
    string m_name;
    int m_deptId;;

};
