#include<iostream>
#include "Graph.h"
#include "Tourism.h"
using namespace std;
CGraph graph;
int main(){
    while(true){
        cout<<"====景区信息管理系统===="<<endl;
        cout<<"1.添加景区景点信息"<<endl;
        cout<<"2.查询景区景点信息"<<endl;
        cout<<"3.旅游景点导航"<<endl;
        cout<<"4.搜索最短路径"<<endl;
        cout<<"5.铺设电路规划"<<endl;
        cout<<"0.退出"<<endl;
        int choice;
        cout<<"请输入选择：";
        cin>>choice;
        switch(choice){
            case 1:
                while(true){   
                    CreateCGraph();
                    cout<<"景区信息添加完成！"<<endl;
                    cout<<"是否继续添加景区信息？"<<endl;
                    cout<<"1.继续添加"<<endl;
                    cout<<"0.返回主菜单"<<endl;
                    cout<<"请输入选择：";
                    cin >> choice;
                    if(choice == 1){
                        continue;
                    }
                    else {
                        break;
                    }
                }
                break;
            case 2:
                while(true){
                    graph.Display();
                    cout<<"请输入想查询景点编号：";
                    cin >> choice;
                    GetSpotInfo(choice);
                    cout<< "是否继续查询" <<endl;
                    cout<<"1.继续查询"<<endl;
                    cout<<"0.返回主菜单"<<endl;
                    cout<<"请输入选择：";
                    cin >> choice;
                    if(choice == 1){
                        continue;
                    }
                    else {
                        break;
                    }
                }
                break;
            case 0:
                cout<<"退出系统！"<<endl;
                return 0;
            default:
                cout<<"无效选择，请重新输入！"<<endl;
                break;
        }
    }

    return 0;
}