#pragma once
#include <vector>
#include <cmath>

struct Vector2 { float x, y; };

float distance(const Vector2 &a, const Vector2 &b)
{
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

struct Grid2D
{
    std::vector<Vector2> node_data;
    std::vector<float>   edge_data;
    size_t rows, cols, size;
   

    Grid2D(size_t rows, size_t cols, const Vector2 &min, const Vector2 &max)
        : rows(rows),cols(cols), size(rows*cols), edge_data(rows*cols*rows*cols, 0)
    {        
        node_data.reserve(rows*cols);

        float xOffset = (max.x - min.x) / float(rows - 1);
        float yOffset = (max.y - min.y) / float(rows - 1);

        for (unsigned i = 0; i < rows; ++i)
            for (unsigned j = 0; j < cols; ++j)
                node_data.push_back(Vector2{ xOffset*i + min.x, yOffset*j + min.y });
        
        for (int i = 0; i < size; ++i)
        {
            if(i%cols > 0)
                edge_data[i*size + i - 1]= distance(node_data[i], node_data[i - 1]);
            
            if (i%(cols+rows) > 0)
                edge_data[i*size + i - rows] = distance(node_data[i], node_data[i - rows]);

            //if(i%cols > 0)  edge_data[i*size - 1] = distance(node_data[i], node_data[i - 1]);

            //if(i > 0)      edge_data[i*size - 1] = distance(node_data[i], node_data[i-1]);
            //if(i < size-1) edge_data[i*size + 1] = distance(node_data[i], node_data[i+1]);

            //if(i > cols)        edge_data[i*size - cols] = distance(node_data[i], node_data[i - cols]);
            //if(i + cols < size) edge_data[i + cols] = distance(node_data[i], node_data[i + cols]);
        }
    }
};