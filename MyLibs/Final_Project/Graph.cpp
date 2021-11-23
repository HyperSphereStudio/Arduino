//
// Created by JohnB on 11/18/2021.
//

#include "Graph.h"

void Graph::plotPoint(Point p) {
    if(!checkPoint(p)){
        obstacles.push_back(p);
    }
}

Graph::Graph(float point_width, float point_height) : point_width(point_width), point_height(point_height), obstacles(){}

bool Graph::checkPoint(Point p) {
    for(auto& obs : obstacles){
        if(obs.contains(p, point_width, point_height)){
            return false;
        }
    }
    return true;
}

void Graph::clear() {
    obstacles.clear();
}

void Graph::gotoPoint(Point current_location, Point *next_location) {

}

bool Point::contains(Point p, float point_width, float point_height) const {
    return (p.x >= x && p.x + point_width <= x) && (p.y >= y && p.y + point_height <= y);
}
