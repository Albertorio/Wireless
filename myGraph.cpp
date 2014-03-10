#include<iostream>
#include<fstream>
#include "myGraph.h"
#include "adListData.h"

using namespace std;

//function: insert a node
void myGraph::addVertex(int name,float x, float y){
    Vertices.push_back(Vertex(name,x,y));
}

//function: insert an edge between nodes
void myGraph::addEdge(int origID,int destID, float weight){
    if(origID < 0 || destID < 0){
        cout << "Invalid node index" << origID << ", " << destID << endl;
        return;
    }
    Vertices[origID].adjacencyList.push_back(adData(destID,weight));
    Vertices[destID].adjacencyList.push_back(adData(origID,weight));

}

//function: displays de adjacency list of each node
void myGraph::display(ostream & out){
  out << "Adjacency-List Representation: \n";

    for (int i = 0; i < Vertices.size(); i++){
		if (Vertices[i].x  != -1 || Vertices[i].y != -1){
			cout << endl << Vertices[i].name << " --";
			for (int j =0; j < Vertices[i].adjacencyList.size();j++){
					cout << " " << Vertices[i].adjacencyList[j].to;
				}
		}
	}
	cout << endl << endl;
}

//function: delete a node
void myGraph::deleteVertex(int n){
    Vertices.erase(Vertices.begin()+n);
}

//function: deletes an edge
void myGraph::deleteEdge(int origID,int destID){
   for(int i=0;i<Vertices[origID].adjacencyList.size();i++){
        if(Vertices[origID].adjacencyList[i].to == destID){
            Vertices[origID].adjacencyList.erase(Vertices[origID].adjacencyList.begin() + i);
        }
   }
   for(int j=0;j<Vertices[destID].adjacencyList.size();j++){
        if(Vertices[destID].adjacencyList[j].to == origID){
            Vertices[destID].adjacencyList.erase(Vertices[destID].adjacencyList.begin() + j);
        }
   }
}
//function: returns neighbors of a node in a vector
vector<adData> myGraph::getNeighbors(int ver){
    vector<adData> neighbors;

    neighbors = Vertices[ver].adjacencyList;

    return neighbors;

}

//function: returns total number of nodes
int myGraph::getNumberVertices(){
    int conta =0;

    for(int i=0;i<Vertices.size();i++){
        conta++;
    }

    return conta;
}

//function: returns total number of edges
int myGraph::getNumberEdges(){
    int conta =0;
    for(int i=0;i<Vertices.size();i++){
        for(int j=0; j<Vertices[i].adjacencyList.size();j++){
            conta++;
        }
    }
    return conta/2;
}

//funciton: display for graphviz
void  myGraph::gravDisplay(ofstream & graph,string name)const{

    graph.open(name.c_str());
    graph << "graph G { \n";
    graph << "overlap=false" << endl;
    graph << "size =  \"" << sizeGraph << "\";" << endl;
    graph << "node [shape=square , fixedsize=true, fontsize=5, width=.10, height=.10];" << endl;
    for(int i=0;i<Vertices.size();i++){
        graph << i << "[ pos = \""<<Vertices[i].x << "," << Vertices[i].y;
        graph <<"!\", label=\"" << i << "\" ]" << endl;
    }

    for(int i=0;i<Vertices.size();i++){
        for(int j=0;j<Vertices[i].adjacencyList.size();j++){
            if(Vertices[i].adjacencyList[j].to > i){
                graph << i << "--" << Vertices[i].adjacencyList[j].to << ";\n";
            }
        }
    }
            graph << "}" << endl;
            graph.close();
}

//function: returns the degree of a node
int myGraph::degree(int ver){
    int conta;
    conta = Vertices[ver].adjacencyList.size();

    return conta;
}

//function: returns average degree of nodes
int myGraph::aveDegree(){
    int ave;

    ave = getNumberEdges()/getNumberVertices();
    return ave;
}

//function: returns maximum degree of nodes
int myGraph::maxDegree(){
    int maxD = degree(0);

    for(int i=1;i<Vertices.size();i++){
        if(degree(i) > maxD){
            maxD = degree(i);
        }
    }

    return maxD;
}
