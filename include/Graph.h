#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VEX 20
struct Vex
{
    int num;
    char name[20];
    char desc[1024];
};
struct Edge
{
    int vex1;
    int vex2;
    int weight;
};
class CGraph
{
    private:
        int m_aADj[MAX_VEX][MAX_VEX];
        Vex m_aVex[MAX_VEX];
        int m_nVexNum;
    public:
        CGraph();
        ~CGraph();
        void Init(void);
        bool AddVex(Vex vex);
        bool AddEdge(Edge edge);
        void Display();
        Vex GetVex(int v);
        int GetVexNum(){ return m_nVexNum; }
        int FindEdge(int v,Edge aEdge[]);
};
#endif