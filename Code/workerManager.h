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

    int m_Empnum;//Ա������

    bool m_FileIsEmpty;//�ļ��Ƿ�Ϊ��

    worker** m_EmpArray;//ָ��һ��ָ������

    ~workerManager();

};
