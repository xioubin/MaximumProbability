//
//  main.cpp
//  MaximumProbability
//
//  Created by 謝育斌 on 2021/1/10.
//

#include <iostream>
#include <sstream>
#include <set>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

class Edge {
private:
public:
    int nodeA;
    int nodeB;
    float weight;
    Edge() {
        this->nodeA = 0;
        this->nodeB = 0;
        this->weight = 0;
    }
    Edge(int a, int b, float w) {
        this->nodeA = a;
        this->nodeB = b;
        this->weight = w;
    }
    ~Edge() {}

};

bool compareEdge(Edge& a, Edge& b) {
    return (a.weight > b.weight);
}

bool istree(int indexA, int indexB, vector<vector<int>*>& forest) {
    int locA = 0, locB = 0;
    for (int i = 0; i < forest.size(); i++) {
        for (auto three : *forest[i]) {
            if (three == indexA) {
                locA = i;
            }
            else if (three == indexB) {
                locB = i;
            }
        }
    }

    if (locA == locB) {
        return false;
    }
    else {
        for (auto it : *forest[locB]) {
            forest[locA]->push_back(it);
        }
        forest.erase(forest.begin() + locB);
        return true;
    }
}

int main() {
    int inputnum;
    cin >> inputnum;
    vector<vector<int>*> forest;
    vector<Edge> edges;
    vector<Edge*> route;
    set<int> temp;

    for (int i = 0; i < inputnum; i++) {
        int nodeA, nodeB;
        float weight;
        cin >> nodeA >> nodeB >> weight;
        edges.push_back(Edge(nodeA, nodeB, weight));
        temp.insert(nodeA);
        temp.insert(nodeB);
    }
    for (auto it : temp) {
        vector<int>* newVec = new vector<int>;
        newVec->push_back(it);
        forest.push_back(newVec);
    }

    sort(edges.begin(), edges.end(), compareEdge);

    float result = 1;

    for (auto edge : edges) {
        if (istree(edge.nodeA, edge.nodeB, forest)) {
            route.push_back(&edge);
            result *= edge.weight;
        }
    }

    if (result <= 0.05)
        cout << 0;
    else
        cout << round(result * 10000) / 10000.0;
}
