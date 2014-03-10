#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "wirelessNetwork.h"
#include "myGraph.h"

using namespace std;

wirelessNetwork::wirelessNetwork(){

    wirelessNetwork(10.0, 500);//Default constructor: creates a 10x10 wirelessNetwork with 500 nodes

}

wirelessNetwork::wirelessNetwork(float size, int n){
    srand(time(NULL));
    G.sizeGraph = size;
    for(int i=0;i<n;i++){
        ID.push_back(i);
        //creates a random coordinate
        posX.push_back(((double)rand()/(RAND_MAX))*size);  
        posY.push_back(((double)rand()/(RAND_MAX))*size);
        G.addVertex(ID[i],posX[i],posY[i]); //Inserts coordinates to node
    }
	
    //Here we calculate distance between nodes
    //if the distance is 1 or less those nodes will be connected by an edge
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            float dist = peso(i,j);
            if(dist <= 1){
                G.addEdge(i,j,dist);
            }
        }
    }
}

//function:calculate distance between nodes
float wirelessNetwork::peso(int i, int j){
    //Distance formula for two points	
    float dist = sqrt(pow(G.Vertices[i].x - G.Vertices[j].x,2) + pow(G.Vertices[i].y-G.Vertices[j].y,2));

    return dist;
}

//function: Lowers the number of edges
void wirelessNetwork::topologyControl(){
    vector<int>bye; //Vector of edges to delete

    for(int i=0;i<G.Vertices.size();i++){
           vector<adData>nei;   //vector that has the neighbors of the "current node"
            if(!G.Vertices[i].adjacencyList.empty()){ //checks if there are any neighbors
                nei = G.getNeighbors(i);
            }
        for(int j=0;j<G.Vertices[i].adjacencyList.size();j++){
            vector<adData>neinei;   //Vector that has the neighbors of the neighbors of the "current node"
            if(!G.Vertices[nei[j].to].adjacencyList.empty()){
                neinei=G.getNeighbors(nei[j].to);
            }
            for(int x=0;x<G.Vertices[nei[j].to].adjacencyList.size();x++){
               if(peso(i,neinei[x].to) != 0 && peso(nei[j].to,neinei[x].to) !=0){//if checks that the node and the neighbor is not the same
               if(peso(i,neinei[x].to) < peso(i,nei[j].to) && peso(nei[j].to,neinei[x].to) < peso(i,nei[j].to)){//compare distance between node and neighbor, node and neighbor's neighbors.
                    bye.push_back(nei[j].to); //if the distance between "current node" and neighbor's neighbor is less than "current node" and neighbor we push the "current node" neighbor to the vector to delete.
                    }
                }
            }
        }
        for(int y=0;y<bye.size();y++){//delete neighbors
            G.deleteEdge(bye[y],i);
        }
        bye.clear();//clean vector so we dont try to delete things that we already erased
    }
}

//function: verifies if the node was visited or not
bool wirelessNetwork::isVisited(int vertex, vector<int> arr){
		for (int i = 0; i<arr.size(); i++)
		{
			if (vertex == arr[i])
				return true;
		}
		return false;
}

//function: inserts element to the compass routing list
vector<int> wirelessNetwork::addToList(int head, vector<int> body){
 	int size = body.size();
		vector<int> merged;
		merged.push_back(head);
		for (int i=1; i<=size; i++)
		{
			merged.push_back(body[i-1]);
		}
		return merged;
}

float wirelessNetwork::coseno(int s,int t, int nei){

    float a = peso(t, nei);
    float b = peso(t, s);
    float c = peso(s, nei);

    return (b*b + c*c -a*a)/(2*b*c);
}

vector<int> wirelessNetwork::compassRouting(int s, int t)
{
		vector<int>ruta;
		if ((G.Vertices[s].x == -1) || (G.Vertices[t].y == -1))
		{
			return ruta;
		}


		else if (s == t) //Verifies if its the same node
		{
			ruta.push_back(t);
			visitado.clear();
			return ruta;
		}
		else if(isVisited(s,visitado)){
			vector<int> emptyRoute;
			return emptyRoute;
		}

		else
		{
			vector<adData> neigh = G.getNeighbors(s);
			int num = neigh.size();


			if (num==0) // verifies if it doesnt have neighbors
			{
				vector<int>emptyRoute;
				visitado.clear();
				return emptyRoute;
			}

			else if ((num==1)&&(isVisited(neigh[0].to, visitado)))//verifies if it only has one neighbor
			{
				vector<int>emptyRoute;
				visitado.clear();
				return emptyRoute;
			}

			else
			{
				double maxCosine = -2;
				int next = s;

				//Finds neighbor with minimum angle
				for (int i = 0; i<num; i++)
				{
					int neighbor = neigh[i].to;
					if ((coseno(s, t, neighbor) > maxCosine)&&(!(isVisited(neighbor, visitado))))
					{
						maxCosine = coseno(s, t, neighbor);
						next = neighbor;
					}
				}
				
				//Selects the next neighbor to continue the compass routing
				visitado.push_back(s);
				return addToList(s, compassRouting(next, t));
			}
		}

}

