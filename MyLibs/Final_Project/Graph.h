//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H

#include "core.h"

typedef unsigned short ustype;

template<typename T>
class Point{
public:
    T x, y;
    Point(T x, T y) : x(x), y(y){}
    bool contains(Point p, float point_width, float point_height) const{
        return (p.x >= x && p.x + point_width <= x) && (p.y >= y && p.y + point_height <= y);
    }

    float distance(Point<T> p){
        return sqrt(pow((float) (p.x - x), 2) + pow((float) (p.y - y), 2));
    }

    Point<T>& operator=(const Point<T>& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
};

template<typename T>
class Graph{
    vector<Point<T>> obstacles;
public:
    float point_width, point_height;

    Graph(float point_width, float point_height) : point_width(point_width), point_height(point_height), obstacles(){}

    void gotoPoint(Point<T> current_location, Point<T>* next_location){

    }

    void plotPoint(Point<T> p){
        if(!checkPoint(p)){
            obstacles.push_back(p);
        }
    }
    bool checkPoint(Point<T> p){
        for(auto& obs : obstacles){
            if(obs.contains(p, point_width, point_height)){
                return false;
            }
        }
        return true;
    }
    void clear(){
        obstacles.clear();
    }
};

#endif //FINAL_PROJECT_GRAPH_H
