#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
class Employee:public worker
{
    public:

    Employee(int id,string name,int dId);

    virtual void showInfo();
    virtual string getDeptName();

};

