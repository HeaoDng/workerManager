#include<iostream>
using namespace std;
#include "workerManager.h"

#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
// void test01()
// {
//     worker* worker0=new Employee(1,"张三",1); 
//     worker0->showInfo();
//     delete worker0;

//     worker* worker1=new Manager(2,"李四",2); 
//     worker1->showInfo();
//     delete worker1;

//     worker* worker2=new Boss(3,"王五",3); 
//     worker1->showInfo();
//     delete worker2;
// }
int main()
{
    
    workerManager wm;
    int choice=0;
    while(true)
    {
        wm.show_Menu();
        cout<<"请输入您的选择"<<endl;
        cin>>choice;
        switch(choice)
        {
            case 0:
            wm.exitsystem();
                break;
            case 1:
            wm.Add_Emp();
                break;
            case 2:
            wm.Show_Emp();
                break;
            case 3:
            wm.Del_Emp();
                break;
            case 4:
                wm.Mod_Emp();
                break;
            case 5:
            wm.Find_Emp();
                break;
            case 6:
            wm.sort_Emp();
                break;
            case 7:
            wm.Clear_File();
                break;
            default:
                system("cls");
                break;
        };
    }

    system("pause");
    return 0;
}