#include "Tourism.h"
#include "Graph.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
using namespace std;
extern CGraph graph;
void CreateCGraph(void){
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
void GetSpotInfo(int v){
    Vex vex = graph.GetVex(v);
    cout << vex.name << " " << vex.desc << endl;
    Edge aEdge[MAX_VEX];
    int edgeCount = graph.FindEdge(v, aEdge);
    cout<<"与景点"<<vex.num<<"相邻的景点有："<<endl;
    for(int i=0;i<edgeCount;i++){
        cout<< vex.name << "->" << graph.GetVex(aEdge[i].vex2).name << " " << aEdge[i].weight <<"m" <<endl;
    }
}