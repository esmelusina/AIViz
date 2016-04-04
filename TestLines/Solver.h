#pragma once
#include <list>
#include <vector>
#include <set>


struct Meta
{

    enum STATE { undiscovered, frontier, explored } state;

    // For visualization
    enum PATH { none, route, start, goal } path;

    float g, h, f;      // Scores
    unsigned DOS;       // Degrees of separation
    size_t prev, self;  // indices to other stuff

                        // For closed/open list


    Meta() : state(undiscovered), path(none) {}
};

typedef bool(*CompFunc)(const Meta &a, const Meta &b);


template<typename Node> // T is the data stored in a node.
class Solver
{
public:


    // comparison and heuristic function typedefs
   
    typedef float(*HeurFunc)(const Node &a, const Node &b);

    std::list  <Meta>  frontier;
    std::vector<Meta>  meta_data;
    
    CompFunc comp;
    HeurFunc heur;

    std::vector<Node>  node_data;  
    std::vector<float> edge_data;   // Adjacency Matrix

    size_t start, goal, size;

    // Build the solver based upon the graph information provided
    Solver(size_t size,
        const std::vector<Node> &nodes,
        const std::vector<float> &edges,
        CompFunc comparison, HeurFunc heuristic)
        :   size(size), 
            comp(comparison), heur(heuristic),
            node_data(nodes), edge_data(edges)
    {
        meta_data.reserve(size);
    }

    // initialize searching
    void doSearch(size_t start, size_t goal)
    {
        this->goal  = goal;     //set goal and start
        this->start = start;
        meta_data.clear();      // clear out metadata
        meta_data.resize(size);

        // setup the start's metadata
        Meta temp;
        temp.g = 0;
        temp.h = heur(node_data[start], node_data[goal]);
        temp.f = temp.g + temp.h;
        temp.DOS = 0;
        temp.prev = start;
        temp.self = start;
        temp.state = Meta::frontier;

        // push start to frontier
        meta_data[start] = temp;
        frontier.push_back(meta_data[start]);

        meta_data[start].path = Meta::start;
        meta_data[goal ].path = Meta::goal;
    }

    std::vector<size_t> getPath()
    {
        std::vector<size_t> path;
        size_t i = goal;
        do
        {          
            path.push_back(i);
            meta_data[i].path = Meta::route;
            i = meta_data[i].prev;
            
        } while (i != start);

        meta_data[start].path = Meta::start;
        meta_data[goal ].path = Meta::goal ;

        path.push_back(start);
        std::reverse(path.begin(), path.end());

        for each(unsigned i in path)
                    std::cout << i << " ";
        
        std::cout << std::endl;
        return path;
    }

    int step() 
    {
        if(frontier.empty()) return -1; // I failed!

        frontier.sort(comp);
        
        Meta current = frontier.front();
        frontier.pop_front();
        
        meta_data[current.self].state = Meta::explored;

        if (current.self == goal)
        {
            frontier.clear();
            return 1; // I succeeded!
        }

        for (unsigned i = 0; i < size; ++i)
            if (meta_data[i].state != Meta::explored && edge_data[current.self*size + i] > 0)
            {
                Meta temp;
                temp.g     = current.g + edge_data[current.self*size + i];
                temp.h     = heur(node_data[i], node_data[goal]);
                temp.f     = temp.g + temp.h;
                temp.DOS   = current.DOS + 1;
                temp.prev  = current.self;
                temp.self  = i;
                temp.state = Meta::frontier;
                temp.path  = meta_data[i].path;

                if (!meta_data[i].state || temp.g < meta_data[i].g)
                {
                    meta_data[i] = temp;
                    frontier.push_back(meta_data[i]);
                }
            }
  
        return 0;
    }
};


