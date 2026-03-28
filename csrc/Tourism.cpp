#include "Tourism.h"
#include "Graph.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
using namespace std;
Tourism::Tourism(void){
}
Tourism::~Tourism(void){
}
void Tourism::CreateCGraph(void){
    Vex vexs[MAX_VEX];
    Edge edges[MAX_VEX * MAX_VEX/2];
    int vexnum, edgenum;
    ifstream vex_file("data/Vex.txt");
    ifstream edge_file("data/Edge.txt");
    if(!vex_file.is_open() || !edge_file.is_open()){
        cout<<"无法打开数据文件！"<<endl;
        return; 
    }
    string line;
    getline(vex_file, line);
    vexnum = stoi(line);
    for(int i=0;i<vexnum;i++){
        getline(vex_file, line);
        int num = stoi(line);
        getline(vex_file, line);
        string name = line;
        getline(vex_file, line);
        string desc = line;
        vexs[i].num = num;
        strncpy(vexs[i].name, name.c_str(), sizeof(vexs[i].name)-1);
        strncpy(vexs[i].desc, desc.c_str(), sizeof(vexs[i].desc)-1);
    }
    while(getline(edge_file, line)){
        int vex1, vex2, weight;
        stringstream ss(line);
        ss >> vex1 >> vex2 >> weight;
        edges[edgenum].vex1 = vex1;
        edges[edgenum].vex2 = vex2;
        edges[edgenum].weight = weight;
        edgenum++;
    }
    for(int i = 0; i < vexnum; i++){
       cout<<"景点编号: "<<vexs[i].num<<"name:" << vexs[i].name << "description:" << vexs[i].desc << endl;
    }
    for(int i = 0; i < edgenum; i++){
        cout<<"景点"<<edges[i].vex1<<"与景点"<<edges[i].vex2<<"的距离为"<<edges[i].weight<<endl;
    }
    for(int i=0;i<vexnum;i++){
        graph.AddVex(vexs[i]);
    }
    for(int i=0;i<edgenum;i++){
        graph.AddEdge(edges[i]);
    }
    vex_file.close();
    edge_file.close();
}
void Tourism::GetSpotInfo(){
    int v;
    cout<<"请输入查询的景点编号：";
    cin >> v;
    Vex vex = graph.GetVex(v);
    cout << vex.name << " " << vex.desc << endl;
    Edge aEdge[MAX_VEX];
    int edgeCount = graph.FindEdge(v, aEdge);
    cout<<"与景点"<<vex.num<<"相邻的景点有："<<endl;
    for(int i=0;i<edgeCount;i++){
        cout<< vex.name << "->" << graph.GetVex(aEdge[i].vex2).name << " " << aEdge[i].weight <<"m" <<endl;
    }
}

void Tourism::TravelPath(){
    int start;
    cout<<"请输入起点景点编号：";
    cin >> start;
    PathList head = new path;
    head->next = nullptr;
    PathList tail = head;

    graph.DFSTraverse(start, tail);
    cout<<"从景点"<<graph.GetVex(start).name<<"出发的所有路径："<<endl;
    PathList current = head->next;
    while(current != nullptr){
        for(int i=0;i<graph.GetVexNum();i++){
            cout<< graph.GetVex(current->vexs[i]).name << "->";
        }
        cout<<"END"<<endl;
        current = current->next;
    }
}

void Tourism::FindShortPath(void){
    int start, end;
    cout<<"请输入起点景点编号：";
    cin >> start;
    cout<<"请输入终点景点编号：";
    cin >> end;
    int aPath[MAX_VEX];
    int totalDist = graph.FindShortestPath(start, end, aPath);
    if(totalDist == -1){
        cout<<"从景点"<<graph.GetVex(start).name<<"到景点"<<graph.GetVex(end).name<<"不可达！"<<endl;
        return;
    }
    cout<<"从景点"<<graph.GetVex(start).name<<"到景点"<<graph.GetVex(end).name<<"的最短路径为：";
    for(int i=0;aPath[i] != -1 && i < MAX_VEX; i++){
        cout<< graph.GetVex(aPath[i]).name << "->";
    }
    cout<<"END"<<endl;
    cout<<"最短距离为"<<totalDist<<"m"<<endl;
}

void Tourism::DesignPath(void){
    Edge aEdge[MAX_VEX];
    int edgeCount = graph.FindMinTree(aEdge);
    int sum = 0;
    if(edgeCount != graph.GetVexNum() - 1){
        cout<<"无法覆盖所有景区！"<<endl;
        return;
     }
    cout<<"铺设线路如下："<<endl;
    for(int i=0;i<edgeCount;i++){
        cout<< graph.GetVex(aEdge[i].vex1).name <<"-" << graph.GetVex(aEdge[i].vex2).name << " 距离为：" << aEdge[i].weight << endl;
        sum += aEdge[i].weight;
    }
    cout<<"电线总距离为："<<sum<<endl;
}