#pragma once

#include <vector>
#include <stack>    // DFS Open List
#include <queue>    // BFS Open List
#include <list>     // Closed List
#include <set>      // Alternative Closed List
#include <iostream>

class Graph
{
public:
    // predefine classes
    struct Node;
    struct Edge
    {
        Node *connection;
        // default constructor
        Edge() : connection(NULL) { }
        // overloaded construct
        Edge(Node *node) : connection(node) { }
    };
    struct Node
    {
        int value;
        int dos; // Degrees of Separation
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
    void AddConnection(Node *n1, Node *n2/*, float weight */)
    {
        n1->connections.push_back(Edge(n2/*, weight*/));
        n2->connections.push_back(Edge(n1/*, weight*/));
    }
private:
    std::vector< Node * > m_nodes;
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

inline bool CompareDFS(const Graph::Node  *a, const Graph::Node *b)
{
    return a->dos > b->dos;
}

inline bool CompareBFS(const Graph::Node *a, const Graph::Node *b)
{
    return a->dos < b->dos;
}


inline void PrintByComparison(Graph::Node *startNode, CompFunc comp)
{
    std::list <Graph::Node *> frontier;  // Open List
    std::set  <Graph::Node *> explored;  // Closed List

   
    // Push our starting node into the frontier
    frontier.push_back(startNode);
    explored.insert(startNode);
    // set it's book-keeping data to help us sort the frontier
    startNode->dos = 0;

    while (!frontier.empty()) // Nodes left to process
    {
        frontier.sort(comp);  // order the frontier according to our priorities
                              // This is a 'priority queue'

        // Process the current node
        auto current = frontier.front();
        std::cout << (char)current->value << " ";
        frontier.pop_front();

        // Add all neighbors to the frontier!
        for each(Graph::Edge e in current->connections)
        {
            if (!explored.count(e.connection)) // add a new node if it isn't explored
            {
                e.connection->dos = current->dos + 1;
                frontier.push_back(e.connection);
                explored.insert(e.connection);
            }
            // If it's already in the frontier, but our new book-keeping data is better
            // just update the book-keeping data
            else if (explored.count(e.connection) &&
                            e.connection->dos > current->dos + 1)
                e.connection->dos = current->dos + 1;
        }
    }
}