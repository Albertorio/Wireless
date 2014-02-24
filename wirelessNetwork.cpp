#include <cmath>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "wirelessNetwork.h"
#include "myGraph.h"

using namespace std;

wirelessNetwork::wirelessNetwork(){

    wirelessNetwork(10.0, 500);//contructor default crea un wirelessNetwork 10x10 con 500 nodos

}

wirelessNetwork::wirelessNetwork(float size, int n){
    srand(time(NULL));
    G.sizeGraph = size;
    for(int i=0;i<n;i++){
        ID.push_back(i);
        posX.push_back(((double)rand()/(RAND_MAX))*size);   //crea una coordenada decimal random
        posY.push_back(((double)rand()/(RAND_MAX))*size);
        G.addVertex(ID[i],posX[i],posY[i]); // inserta esas coordenadas en su respectivo vertice
    }

    //Aqui se calcula la distancia entre vertices
    //si es de 1 o menos esos vertices van conectados con una arista
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            float dist = peso(i,j);
            if(dist <= 1){
                G.addEdge(i,j,dist);
            }
        }
    }
}

//funcion: calcula distancia entre vertices
float wirelessNetwork::peso(int i, int j){
    //formula de distancia entre dos puntos
    float dist = sqrt(pow(G.Vertices[i].x - G.Vertices[j].x,2) + pow(G.Vertices[i].y-G.Vertices[j].y,2));

    return dist;
}

//funcion: Disminuye el numero de aristas
void wirelessNetwork::topologyControl(){
    vector<int>bye; //vector de aristas a borrar

    for(int i=0;i<G.Vertices.size();i++){
           vector<adData>nei;   //vector que va a tener los vecinos del "current node"
            if(!G.Vertices[i].adjacencyList.empty()){ //verifica que tenga vecinos
                nei = G.getNeighbors(i);
            }
        for(int j=0;j<G.Vertices[i].adjacencyList.size();j++){
            vector<adData>neinei;   //vector que tendra los vecinos del vecino del vertice
            if(!G.Vertices[nei[j].to].adjacencyList.empty()){
                neinei=G.getNeighbors(nei[j].to);
            }
            for(int x=0;x<G.Vertices[nei[j].to].adjacencyList.size();x++){
               if(peso(i,neinei[x].to) != 0 && peso(nei[j].to,neinei[x].to) !=0){//if verifica que no estemos que el vecino no sea el mismo
               if(peso(i,neinei[x].to) < peso(i,nei[j].to) && peso(nei[j].to,neinei[x].to) < peso(i,nei[j].to)){//comparamos distancia entre nodo y vecino, nodo y vecino del vecino
                    bye.push_back(nei[j].to); //si la distancia entre el nodo y vecino del vecino es menor que la de nodo a vecino, insertamos el vecino del nodo para borrar
                    }
                }
            }
        }
        for(int y=0;y<bye.size();y++){//borramos los vecinos
            G.deleteEdge(bye[y],i);
        }
        bye.clear();//limpiamos vector para no tratar de borrar cosas que ya borramos
    }
}

//funcion: verifica si el nodo ya ha sido visitado o no
bool wirelessNetwork::isVisited(int vertex, vector<int> arr){
		for (int i = 0; i<arr.size(); i++)
		{
			if (vertex == arr[i])
				return true;
		}
		return false;
}

//funcion: inserta elemento a la lista de compass routing
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


		else if (s == t) //Verifica si es el mismo nodo
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


			if (num==0) // verifica si no tiene vecinos
			{
				vector<int>emptyRoute;
				visitado.clear();
				return emptyRoute;
			}

			else if ((num==1)&&(isVisited(neigh[0].to, visitado)))//verifica si solo tiene un vecino
			{
				vector<int>emptyRoute;
				visitado.clear();
				return emptyRoute;
			}

			else
			{
				double maxCosine = -2;
				int next = s;

				//Encuentra vecino con angulo minimo
				for (int i = 0; i<num; i++)
				{
					int neighbor = neigh[i].to;
					if ((coseno(s, t, neighbor) > maxCosine)&&(!(isVisited(neighbor, visitado))))
					{
						maxCosine = coseno(s, t, neighbor);
						next = neighbor;
					}
				}

				//escoge al proximo vecino para seguir el comppass routing
				visitado.push_back(s);
				return addToList(s, compassRouting(next, t));
			}
		}

}

