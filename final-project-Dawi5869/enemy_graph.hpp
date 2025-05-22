#ifndef ENEMY_GRAPH_HPP
#define ENEMY_GRAPH_HPP

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <climits>

#include "hash.hpp"
#include "PriorityQueue.hpp"

using namespace std;

struct Vertex;

struct AdjacentVertex {
    Vertex *v;
    string enemy_id;
};

struct Vertex {
    string id;
	int distance;
	bool solved;
    vector<AdjacentVertex> adjacent;
};

class EnemyGraph {
    public:
        EnemyGraph();
        ~EnemyGraph();
        Vertex* addVertex(string id);
        void addEdge(string source_id, string destination_id, string enemy_id);

		Vertex* searchVertex(string id);

        int findEasiestPath(HashTable ht);

		void buildGraphFromFile(string fname);

    private:
        unordered_map<string, Vertex*> vertices;
};

#endif
