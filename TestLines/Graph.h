#pragma once

#include <vector>
#include <stack>    // DFS Open List
#include <queue>    // BFS Open List
#include <list>     // Closed List
#include <set>      // Alternative Closed List
#include <iostream>

struct Vector2
{
    float x, y;
    Vector2() {}
    Vector2(float x, float y) :x(x), y(y) {}
};

inline float distance(Vector2 a, Vector2 b)
{
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}


class Graph
{
public:
    // predefine classes
    struct Node;
    struct Edge
    {
        Node *connection;
        float weight;
        // default constructor
        Edge() : connection(NULL) { }
        // overloaded construct
        Edge(Node *node, float weight) : connection(node), weight(weight) { }
    };
    struct Node
    {
        int value;
        
        int   dos; // Degrees of Separation
        Node *prev;

        float g;
                
        std::vector< Graph::Edge > connections;
        // default constructor
        Node() : value(0) {}
        // overloaded constructor
        Node(int val) : value(val) {}
    };
    ~Graph()
    {
        // make sure to delete all nodes added to the graph
        for (auto iter = m_nodes.begin(); iter != m_nodes.end(); iter++)
            delete (*iter);
        m_nodes.clear();
    }
    Node *AddNode(int value)
    {
        m_nodes.push_back(new Node(value));
        return m_nodes.back();
    }
    void AddConnection(Node *n1, Node *n2, float weight = 1)
    {
        n1->connections.push_back(Edge(n2, weight));
        n2->connections.push_back(Edge(n1, weight));
    }
private:
    std::vector< Node *> m_nodes;
};













inline void PrintDFS(Graph::Node *startNode)
{
    //std::stack<Graph::Node *> frontier;  // Open List
    std::list<Graph::Node *> frontier;
    std::set <Graph::Node *> explored;  // Closed List
                                         
    frontier.push_front(startNode);
    explored.insert(startNode);

    while(!frontier.empty())               
    {
        auto current = frontier.front();     
        std::cout << (char)current->value << " "; 
        frontier.pop_front();                     
        explored.insert(current);

        for each(Graph::Edge e in current->connections)
            if (!explored.count(e.connection))
            {
                frontier.push_front(e.connection);
                explored.insert(e.connection);
            }
    }
}

inline void PrintBFS(Graph::Node *startNode)
{
    std::list <Graph::Node *> frontier;  // Open List
    std::set  <Graph::Node *> explored;  // Closed List

    frontier.push_back(startNode);
    explored.insert(startNode);
    while (!frontier.empty())
    {
        auto current = frontier.front();
        std::cout << (char)current->value << " ";
        frontier.pop_front();

        for each(Graph::Edge e in current->connections)
        {
            if (!explored.count(e.connection))
            {
                frontier.push_back(e.connection);
                explored.insert(e.connection);
            }
        }
    }
}





typedef bool (*CompFunc)(const Graph::Node  *, const Graph::Node  *);

typedef float(*HeurFunc)(const Graph::Node  *, const Graph::Node  *);

inline bool CompareDFS(const Graph::Node  *a, const Graph::Node *b)
{
    return a->dos > b->dos;
}

inline bool CompareBFS(const Graph::Node *a, const Graph::Node *b)
{
    return a->dos < b->dos;
}

inline bool compareDijkstra(const Graph::Node *a, const Graph::Node *b)
{
    return a->g < b->g;
}

inline float distance(const Graph::Node *a, const Graph::Node *b)
{
    
}

inline void PrintByComparison(Graph::Node *startNode, Graph::Node *goalNode, CompFunc comp, HeurFunc heur)
{
    std::list <Graph::Node *> frontier;  // Open List
    std::set  <Graph::Node *> explored;  // Closed List

   
    // Push our starting node into the frontier
    frontier.push_back(startNode);
    explored.insert(startNode);
    // set it's book-keeping data to help us sort the frontier
    startNode->dos = 0;
    startNode->g   = 0;
    Graph::Node *current = nullptr;
    while (!frontier.empty()) // Nodes left to process
    {
        frontier.sort(comp);  // order the frontier according to our priorities
                              // This is a 'priority queue'

        // Process the current node
        current = frontier.front();
        std::cout << (char)current->value << " ";
        frontier.pop_front();

        if (current == goalNode) break;

        // Add all neighbors to the frontier!
        for each(Graph::Edge e in current->connections)
        {
            float g = current->g + e.weight;

            if (g < e.connection->g || !explored.count(e.connection))
            {
                e.connection->dos = e.connection->dos + 1;
                e.connection->g = g;
                e.connection->prev = current;
                
                if (!explored.count(e.connection))
                    frontier.push_back(e.connection);

                explored.insert(e.connection);
            }
        }
    }

    std::cout << std::endl;
    // current->prev->prev->prev->prev


    while (current != startNode)
    {
        std::cout << (char)current->value << " ";
        current = current->prev;
    }
    std::cout << (char)startNode->value << " ";
}