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
void CGraph::DFS(int nVex, bool visited[], int aPath[], int &index,PathList &pList){
    visited[nVex] = true;
    aPath[index++] = nVex;
    if(index == m_nVexNum){
        PathList newNode = new path;
        for(int i=0;i<index;i++){
            newNode->vexs[i] = aPath[i];
        }
        pList ->next = newNode;
        newNode->next = nullptr;
        pList = newNode;
        return;
    }
    Edge aEdge[MAX_VEX];
    int edgeCount = FindEdge(nVex, aEdge);
    for(int i=0;i<edgeCount;i++){
        if(!visited[aEdge[i].vex2]){
            DFS(aEdge[i].vex2, visited, aPath, index, pList);
            visited[aEdge[i].vex2] = false;
            index--;
        }
    }
}

void CGraph::DFSTraverse(int nVex, PathList &pList){
    bool visited[MAX_VEX] = {false};
    int aPath[MAX_VEX];
    int index = 0;
    pList -> next = nullptr;
    DFS(nVex, visited, aPath, index, pList);
}


int CGraph::FindShortestPath(int nVexStart, int nVexEnd, int aPath[]) {
    if (nVexStart < 0 || nVexStart >= m_nVexNum || nVexEnd < 0 || nVexEnd >= m_nVexNum) {
        return -1;
    }

    int dist[MAX_VEX];      
    bool visited[MAX_VEX];  
    int prev[MAX_VEX];     

    for (int i = 0; i < m_nVexNum; i++) {
        dist[i] = (m_aADj[nVexStart][i] > 0) ? m_aADj[nVexStart][i] : INF;
        visited[i] = false;
        if (dist[i] < INF) {
            prev[i] = nVexStart;
        } else {
            prev[i] = -1;
        }
    }

    dist[nVexStart] = 0;
    visited[nVexStart] = true;
    prev[nVexStart] = -1;

    for (int i = 1; i < m_nVexNum; i++) {
        int minDist = INF;
        int u = -1;

        for (int j = 0; j < m_nVexNum; j++) {
            if (!visited[j] && dist[j] < minDist) {
                u = j;
                minDist = dist[j];
            }
        }

        if (u == -1 || u == nVexEnd) break;

        visited[u] = true;

        for (int v = 0; v < m_nVexNum; v++) {
            if (!visited[v] && m_aADj[u][v] > 0) {
                if (dist[u] + m_aADj[u][v] < dist[v]) {
                    dist[v] = dist[u] + m_aADj[u][v];
                    prev[v] = u; 
                }
            }
        }
    }

    if (dist[nVexEnd] == INF) {
        return -1; 
    }

    int tempPath[MAX_VEX];
    int count = 0;
    int curr = nVexEnd;
    
    while (curr != -1) {
        tempPath[count++] = curr;
        curr = prev[curr];
    }

    for (int i = 0; i < count; i++) {
        aPath[i] = tempPath[count - 1 - i];
    }
    
    if(count < MAX_VEX) aPath[count] = -1;

    return dist[nVexEnd];
}

int CGraph::FindMinTree(Edge aEdge[]){
    //prim算法实现最小生成树
    bool selected[MAX_VEX] = {false};
    int edgeCount = 0;
    selected[0] = true;
    for(int i=0;i<m_nVexNum-1;i++){
        int minWeight = INF;
        int minVex1 = -1, minVex2 = -1;
        for(int j=0;j<m_nVexNum;j++){
            if(selected[j]){
                for(int k=0;k<m_nVexNum;k++){
                    if(!selected[k] && m_aADj[j][k] > 0){
                        if(m_aADj[j][k] < minWeight){
                            minWeight = m_aADj[j][k];
                            minVex1 = j;
                            minVex2 = k;
                            aEdge[edgeCount].vex1 = minVex1;
                            aEdge[edgeCount].vex2 = minVex2;
                            aEdge[edgeCount].weight = minWeight;
                        }
                    }
                }
            }
        }
        edgeCount++;
        selected[minVex2] = true;
    }
    return edgeCount;
}