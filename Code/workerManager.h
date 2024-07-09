#pragma once
#include<iostream>
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;
#include "worker.h"
class workerManager
{
public:
    workerManager();

    void show_Menu();

    void exitsystem();

    void Add_Emp();

    void save();

    int get_EmpNum();

    void init_Emp();

    void Show_Emp();

    void Del_Emp();

    int IsExist(int id);

    void Mod_Emp();

    void Find_Emp();

    void sort_Emp();

    void Clear_File();

    int m_Empnum;//员工人数

    bool m_FileIsEmpty;//文件是否为空

    worker** m_EmpArray;//指向一个指针数组

    ~workerManager();

};
