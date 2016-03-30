#include "sfwl.h"

#include <iostream>

#include "Graph.h"


//#include "visualize.h"

int main(int argc, char **argv)
{
    Graph *pGraph = new Graph();
    
    Graph::Node *a, *b, *c, *d, *e, *f, *g, *h, *i, *j;
    a = pGraph->AddNode('a'); b = pGraph->AddNode('b');
    c = pGraph->AddNode('c'); d = pGraph->AddNode('d');
    e = pGraph->AddNode('e'); f = pGraph->AddNode('f');
    g = pGraph->AddNode('g'); h = pGraph->AddNode('h');
    i = pGraph->AddNode('i'); j = pGraph->AddNode('j');
    pGraph->AddConnection(a, b); pGraph->AddConnection(a, d);
    pGraph->AddConnection(a, e); pGraph->AddConnection(b, c);
    pGraph->AddConnection(d, h); pGraph->AddConnection(e, h);
    pGraph->AddConnection(e, f); pGraph->AddConnection(f, c);
    pGraph->AddConnection(f, j); pGraph->AddConnection(g, c);
    pGraph->AddConnection(g, j); pGraph->AddConnection(i, j);
    pGraph->AddConnection(i, h);

    PrintDFS(a);
    std::cout << std::endl;
    PrintBFS(a);
    std::cout << std::endl;
    std::cout << std::endl;
    PrintByComparison(a, CompareDFS);
    std::cout << std::endl;
    PrintByComparison(a, CompareBFS);
    std::cout << std::endl;

    delete pGraph;
    system("pause");
    return 0;
};