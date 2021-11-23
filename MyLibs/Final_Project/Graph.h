//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H

#include "core.h"

class Point{
public:
    float x, y;
    Point(float x, float y) : x(x), y(y){}
    bool contains(Point p, float point_width, float point_height) const;
};

class Graph{
    vector<Point> obstacles;
public:
    float point_width, point_height;

    Graph(float point_width, float point_height);
    void gotoPoint(Point current_location, Point* next_location);
    void plotPoint(Point p);
    bool checkPoint(Point p);
    void clear();
};

#endif //FINAL_PROJECT_GRAPH_H
