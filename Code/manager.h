#pragma once
#include<iostream>
using namespace std;

#include"worker.h"

class Manager:public worker{

public:
    Manager(int id,string name,int dId);
    virtual string getDeptName();
    virtual void showInfo();
};