#include<iostream>
#include"worker.h"
#pragma once
using namespace std;

class Boss:public worker
{
public:
    Boss(int id,string name,int dId);
    virtual void showInfo();
    virtual string getDeptName();
};
