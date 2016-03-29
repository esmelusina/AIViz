#include "sfwl.h"

#include <iostream>

#include "Graph.h"
#include "visualize.h"

using Node = Graph::Node;



void main()
{
    sfwl::initContext();

    Graph *pGraph = new Graph();
    Node *a = pGraph->AddNode(Vector2(100, 100));
    Node *b = pGraph->AddNode(Vector2(150, 100));
    Node *c = pGraph->AddNode(Vector2(200, 100));
    Node *d = pGraph->AddNode(Vector2(150, 150));
    Node *e = pGraph->AddNode(Vector2(100, 200));
    Node *f = pGraph->AddNode(Vector2(150, 200));
    Node *g = pGraph->AddNode(Vector2(200, 200));
    Node *h = pGraph->AddNode(Vector2(300, 150));
    Node *i = pGraph->AddNode(Vector2(250, 100));
    Node *j = pGraph->AddNode(Vector2(300, 100));
    Node *k = pGraph->AddNode(Vector2(350, 100));

    pGraph->ConnectNodes(a, d, 1);
    pGraph->ConnectNodes(b, d, 1);
    pGraph->ConnectNodes(c, d, 1);
    pGraph->ConnectNodes(d, h, 1);
    pGraph->ConnectNodes(d, e, 1);
    pGraph->ConnectNodes(d, f, 1);
    pGraph->ConnectNodes(d, g, 1);
    pGraph->ConnectNodes(i, h, 1);
    pGraph->ConnectNodes(j, h, 1);
    pGraph->ConnectNodes(k, h, 1);
    pGraph->bakeData();

    while (sfwl::stepContext())
    {
        //drawGraph(pGraph->size(), pGraph->getPositions(), pGraph->getAdjacencyMatrix());

        pGraph->draw();
    }

    delete pGraph;

    sfwl::termContext();
}