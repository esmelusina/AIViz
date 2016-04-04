#pragma once
#include "sfwl.h"
#include "Graph.h"

//
//inline void Graph::draw()
//{
//    for each(Edge e in edges)
//        sfwl::drawLine(e.a->data.x, e.a->data.y, e.b->data.x, e.b->data.y);
//
//    for each(Node n in nodes)
//        sfwl::drawBox(n.data.x, n.data.y, 8);
//}
//
//
//inline void drawGraph(unsigned count, const float *x, const float *y, const unsigned *colors, const float *adj)
//{
//    for (unsigned i = 0; i < count; ++i)
//        for (unsigned j = 0; j < count; ++j)
//            if (adj[i*count + j] != 0)
//                sfwl::drawLineGradient(x[i], y[i], x[j], y[j], colors[i], colors[j]);
//            
//    for (unsigned i = 0; i < count; ++i)
//        sfwl::drawBox(x[i], y[i], 8, colors[i]);
//}
//
//inline void drawGraph(unsigned count, const Vector2 *p, const float *adj)
//{
//    for (unsigned i = 0; i < count; ++i)
//        for (unsigned j = 0; j < count; ++j)
//            if (adj[i*count + j] != 0)
//                sfwl::drawLineGradient(p[i].x, p[i].y, p[j].x, p[j].y, WHITE, WHITE);
//
//    for (unsigned i = 0; i < count; ++i)
//        sfwl::drawBox(p[i].x, p[i].y, 8, WHITE);
//}