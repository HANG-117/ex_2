#include "Graph.h"
#include<iostream>
using namespace std;
CGraph::CGraph(){
    Init();
}
CGraph::~CGraph(){
    
}
void CGraph::Init(void){
    for(int i=0;i<MAX_VEX;i++){
        m_aVex[i].num = 0;
        m_aVex[i].name[0] = '\0';
        m_aVex[i].desc[0] = '\0';
        for(int j=0;j<MAX_VEX;j++){
            m_aADj[i][j] = 0;
        }
    }
    m_nVexNum = 0;
}
bool CGraph::AddVex(Vex vex){
    if(m_nVexNum >= MAX_VEX){
        return false;
    }
    m_aVex[m_nVexNum] = vex;
    m_nVexNum++;
    return true;
}
bool CGraph::AddEdge(Edge edge){
    if(edge.vex1 < 0 || edge.vex1 >= m_nVexNum || edge.vex2 < 0 || edge.vex2 >= m_nVexNum){
        return false;
    }
    m_aADj[edge.vex1][edge.vex2] = edge.weight;
    m_aADj[edge.vex2][edge.vex1] = edge.weight;
    return true;
}
void CGraph::Display(){
    cout<<"景点信息："<<endl;
    for(int i=0;i<m_nVexNum;i++){
        cout<<m_aVex[i].num<<"-"<<m_aVex[i].name<<endl;
    }
}
Vex CGraph::GetVex(int v){
    if(v < 0 || v >= m_nVexNum){
        Vex empty;
        empty.num = -1;
        empty.name[0] = '\0';
        empty.desc[0] = '\0';
        return empty;
    }
    return m_aVex[v];
}
int CGraph::FindEdge(int v,Edge aEdge[]){
    int count = 0;
    for(int i=0;i<m_nVexNum;i++){
        if(m_aADj[v][i] > 0){
            aEdge[count].vex1 = v;
            aEdge[count].vex2 = i;
            aEdge[count].weight = m_aADj[v][i];
            count++;
        }
    }
    return count;
}
