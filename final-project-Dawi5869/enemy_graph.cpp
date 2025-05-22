#include "enemy_graph.hpp"
#include <iostream>

EnemyGraph::EnemyGraph() {
	return;
}

EnemyGraph::~EnemyGraph() {
    for (auto entry : vertices) {
        delete entry.second;
    }
    vertices.clear();
}

Vertex* EnemyGraph::addVertex(string id) {
    // Check for unique ID
    if (vertices.count(id) > 0) {
        cout << "ID already exists: " << id << endl;
        return nullptr;
    }
    Vertex* v = new Vertex();
    v->id = id;
	v->distance = 0;
	v->solved = false;
    vertices.insert({id, v});
    return v;
}

Vertex* EnemyGraph::searchVertex(string id) {
	Vertex* toReturn = nullptr;
	for (auto entry : vertices) {
		if (entry.first == id)
			return entry.second;
	}
	return toReturn;
}

/**
 * Adds an undirected edge between two vertices with specified IDs.
 */
void EnemyGraph::addEdge(string v1_id, string v2_id, string enemy_id) {
    // Verify that the IDs exist and are unique
    if (v1_id == v2_id) {
        cout << "v1_id and v2_id must be different!" << endl;
        return;
    }
    if (vertices.count(v1_id) == 0) {
        cout << "No Vertex with ID: " << v1_id << endl;
        return;
    }
    if (vertices.count(v2_id) == 0) {
        cout << "No Vertex with ID: " << v2_id << endl;
        return;
    }

    Vertex* v1 = vertices.at(v1_id);
    Vertex* v2 = vertices.at(v2_id);

    // Verify that edge doesn't already exist
    for (const auto &v : v1->adjacent) {
        if (v.v->id == v2_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }
    for (const auto &v : v2->adjacent) {
        if (v.v->id == v1_id) {
            cout << "There is already an edge between " << v1_id << " and " << v2_id << endl;
            return;
        }
    }

    AdjacentVertex adj_v2;
    adj_v2.v = v2;
    adj_v2.enemy_id = enemy_id;
    v1->adjacent.push_back(adj_v2);

    AdjacentVertex adj_v1;
    adj_v1.v = v1;
    adj_v1.enemy_id = enemy_id;
    v2->adjacent.push_back(adj_v1);
}

/**
 *
 */
void EnemyGraph::buildGraphFromFile(string fname) 
{
    
    ifstream ifile;
    ifile.open(fname.c_str());
    if( !ifile.is_open())
    {
        cout<<"wrong file name or path"<<endl;
        return;
    }
    string line;
    while(getline(ifile,line))
    {
        stringstream s(line);
        string type; // vertex or edge
		string vertex_ID; // data for vertex
		string vertex1, vertex2, charName; // data for edges
        getline(s,type,';'); //cout<<movieName<<endl;
		if (type == "vertex") {
        	getline(s,vertex_ID,';'); 
			addVertex(vertex_ID);
		} else if (type == "edge") {
        	getline(s,vertex1,';');
        	getline(s,vertex2,';'); 
        	getline(s,charName,';'); 
			addEdge(vertex1, vertex2, charName);
		} else {
			cout << "line read error..." << endl;
		}
    }
    
}

/**
 *  Your implmentation should run a Dijkstra's search from the start vertext to the end
 *   - Edges are labeled with character names, 
 *   - Edge weights will be the character's highest damage item
 */
int EnemyGraph::findEasiestPath(HashTable ht) 
{

    Vertex* start = searchVertex("start");

    if (start == nullptr)
    {
        cout << "No start vertex" << endl;
        return -1;
    }

    start->distance = 0;
    start->solved = true;



    Vertex* curr = start;

    while (true)
    {
        int minDist = INT_MAX;
        Vertex* nextVertex = nullptr;

        for (int i = 0; i < curr->adjacent.size(); i++)
        {
            AdjacentVertex adj = curr->adjacent[i];

            if (!adj.v->solved)
            {
                node* enemyNode = ht.searchCharacter(adj.enemy_id);
                int weight;
                if (enemyNode == nullptr || enemyNode->pq.peek() == nullptr)
                {
                    weight = INT_MAX;
                }
                else
                {
                    weight = enemyNode->pq.peek()->damage;
                }

                int newDist = curr->distance + weight;
                if (adj.v->distance == 0 || newDist < adj.v->distance)
                {
                    adj.v->distance = newDist;
                }
            }
        }

        for (auto it = vertices.begin(); it != vertices.end(); it++)
        {
            Vertex* v = it->second;
            if (!v->solved && v->distance < minDist && v->distance != 0)
            {
                minDist = v->distance;
                nextVertex = v;
            }
        }

        if (nextVertex == nullptr)
        {
            break;
        }

        nextVertex->solved = true;
        curr = nextVertex;

        if (curr->id == "end")
        {
            break;
        }
    }


    Vertex* end = searchVertex("end");
    if (end != nullptr)
    {
        return end->distance;
    }
    else
    {
        return -1;
    }



}
