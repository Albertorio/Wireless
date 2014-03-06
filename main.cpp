#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "myGraph.h"
#include "wirelessNetwork.h"

using namespace std;

void Experiment1(){
    int conta=1;
    cout << "Experiment 1" << endl;
    for(int i=500;i<=950;i=i+50){
    wirelessNetwork W(10,i);
    ofstream graph;
    W.G.gravDisplay(graph,"before");
    cout << "--------------------------------------------" << endl;
    cout << "Before " << conta << ": " << endl;
    cout << "Average Degree: " << W.G.aveDegree() << endl;
    cout << "Max Degree:" << W.G.maxDegree();
    W.topologyControl();
    cout << endl << endl;
    ofstream graph2;
    W.G.gravDisplay(graph2,"after");
    cout << "After " << conta << ": " << endl;
    cout << "Average Degree: " << W.G.aveDegree() << endl;
    cout << "Max Degree: " << W.G.maxDegree() << endl;
    cout << "--------------------------------------------" << endl;

    cout << endl << endl;
    conta++;
    }
}

void Experiment2(wirelessNetwork N){
    cout << "Experiment 2" << endl;
    srand(time(NULL));
    int plen;
    int s, t;
    vector<int> com;
    s = (rand() % 1000);
    t = (rand() % 1000);

    cout << "Message from " << s << ", " << t << endl;

    com = N.compassRouting(s,t);
    plen = com.size();
    cout << "List: ";
    for(int i=0; i<com.size();i++){
            cout << com[i] << " ";
    }
        cout << endl;
        cout << "Length: " << plen;
        cout << endl << endl;
}

void Experiment3(wirelessNetwork N){
cout << "Experiment 3" << endl;
    srand(time(NULL));
    int plen;
    int s, t;
    vector<int> com;
    s = (rand() % 1000);
    t = (rand() % 1000);

    cout << "Message from " << s << ", " << t << endl;

    com = N.compassRouting(s,t);
    plen = com.size();
    cout << "List: ";
    if(!com.empty()){
    for(int i=0; i<com.size();i++){
            cout << com[i] << " ";
    }
}else{
    cout << "no hay ruta" << endl;

}
        cout << endl;
        cout << "Length: " << plen;
        cout << endl << endl;
}



int main()
{
    wirelessNetwork N = wirelessNetwork(10,1000);
    wirelessNetwork W(10,500);
    ofstream graph;
    W.G.gravDisplay(graph,"before");

    W.topologyControl();

    ofstream graph2;
    W.G.gravDisplay(graph,"after");

    Experiment1();

    Experiment2(N);

    N.topologyControl();

    Experiment3(N);

    return 0;
}
