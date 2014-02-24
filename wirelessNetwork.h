#ifndef WIRELESSNETWORK_H
#define WIRELESSNETWORK_H
#include "myGraph.h"

using namespace std;

class wirelessNetwork: public myGraph{
public:
    myGraph G;
    vector<int> ID;
    vector<float> posX;
    vector<float> posY;
    vector<int> visitado;
    vector<int> compassRouting(int,int);
    vector<int> addToList(int, vector<int>);
    float peso(int,int);
    float coseno(int,int,int);
    void topologyControl();
    bool isVisited(int,vector<int>);
    wirelessNetwork();
    wirelessNetwork(float,int);



};
#endif // WIRELESSNETWORK_H
