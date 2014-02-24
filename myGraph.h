#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;

class adData{
    public:
        int to;
        float storeDist;
        adData();
        adData(int t,float sd){to=t,storeDist=sd;}
    };

class myGraph{
private:
    class Vertex{
    public:
        float x,y;
        int name;
        Vertex(){};
        Vertex(int st,float coo1, float coo2){name =st,x = coo1,y=coo2;}
        vector<adData> adjacencyList;
        };


public:
    float sizeGraph;
    vector<Vertex> Vertices;
    vector<adData> getNeighbors(int);
    void addVertex(int,float,float);
    void addEdge(int,int,float);
    void display(ostream & out);
    void gravDisplay(ofstream & graph,string)const;
    void deleteVertex(int);
    void deleteEdge(int,int);
    int aveDegree();
    int getNumberVertices();
    int degree(int);
    int maxDegree();
    int getNumberEdges();

};



#endif // MYGRAPH_H
