#ifndef TOURISM_H
#define TOURISM_H
#include "Graph.h"

class Tourism{
public:
    Tourism(void);
    ~Tourism(void);
    CGraph graph;
    void CreateCGraph(void);
    void GetSpotInfo();
    void TravelPath();
};
#endif
