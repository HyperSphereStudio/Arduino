//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H


class Point{
    float x, y;
    bool bound_point;
public:
    Point() = default;
};

class Obstacle{
    Point upperLeft, upperRight, lowerLeft, lowerRight;
public:
    bool contains(Point p);
};

class Graph{
    //std::vector<Point> obstacles;
public:
    void plotPoint(Point p);
};

#endif //FINAL_PROJECT_GRAPH_H
