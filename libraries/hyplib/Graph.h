//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H

typedef char GraphDirection;

#define GEast 0
#define GNorth 1
#define GWest 2
#define GSouth 3
#define GEnd 4

#include "core.h"
#include "GraphSolver.h"

template<typename T, int width, int height>
class Point{
public:
    T x, y;
    Point(T x, T y) : x(x), y(y){}
    Point() : Point(0, 0){}

    static Point getChangePoint(Point curr_loc, GraphDirection dir, T distance){
        switch(dir){
            case GEast:
                return {static_cast<T>(distance + curr_loc.x), curr_loc.y};
            case GNorth:
                return {curr_loc.x, static_cast<T>(distance + curr_loc.y)};
            case GSouth:
                return {curr_loc.x, static_cast<T>(curr_loc.y - distance)};
            case GWest:
                return {static_cast<T>(curr_loc.x - distance), curr_loc.y};
            case GEnd:
                return curr_loc;
        }
    }

    bool operator==(Point p) {
        return compare(p);
    }

    float distance(Point p){
        return sqrt(pow((float) (p.x - x), 2) + pow((float) (p.y - y), 2));
    }

    bool comp_compare(Point p){
        return p.x == x || p.y == y;
    }

    float compare(Point p){
        return p.x == x && p.y == y;
    }

    Point& operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
};

template<typename T, int point_width, int point_height>
class Graph : public vector<Point<T, point_width, point_height>>{
    using TPoint = Point<T, point_width, point_height>;

    T maxX;
    T minX;
    T maxY;
    T minY;
public:
    Graph()= default;

    void plotPoint(TPoint p){
        if(!containsPoint(p)){
            vector<TPoint>::push_back(p);
            maxX = max(maxX, p.x);
            maxY = max(maxY, p.y);
            minY = min(minY, p.y);
            minX = min(minX, p.x);
        }
    }

    bool isSafePoint(TPoint p){
        return !containsPoint(p) && !(minX >= p.x || minY >= p.y || maxX <= p.x || maxY <= p.y);
    }

    bool containsPoint(TPoint p){
        auto iter = this->begin();
        this->begin();
        while(iter != this->end()){
            if(p == *iter){
                return true;
            }
            iter++;
        }
        return false;
    }

     void getPath(TPoint curr_loc, TPoint goto_loc, vector<GraphDirection>* dirs){
#if DEBUG
         debug_print(F("Finding Path:("));
         debug_print(curr_loc.x);
         debug_print(F("),("));
         debug_print(curr_loc.y);
         debug_print(F(")->("));
         debug_print(goto_loc.x);
         debug_print(F("),("));
         debug_print(goto_loc.y);
         debug_println(F(")"));
#endif
        GraphSolver::findPath(this, curr_loc, goto_loc, dirs);
    }

    T getMinX(){
        return minX;
    }

    T getMinY(){
        return minY;
    }

    T getMaxX(){
        return maxX;
    }

    T getMaxY(){
        return maxY;
    }

    void setMinX(T t){
        minX = t;
    }

    void setMinY(T t){
        minY = t;
    }

    void setMaxX(T t){
        maxX = t;
    }

    void setMaxY(T t){
        maxY = t;
    }

    static bool isLeft(GraphDirection dir, GraphDirection comp){
        return comp == (dir == 0 ? 3 : dir - 1);
    }

    static bool isRight(GraphDirection dir, GraphDirection comp){
        return comp == (dir == 3 ? 0 : dir + 1);
    }

    static int dircos(GraphDirection dir){
        switch(dir){
            case GSouth:
            case GNorth:
                return 0;
            case GEast:
                return 1;
            default:
                return -1;
        }
    }

    static int dirsin(GraphDirection dir){
        switch(dir){
            case GEast:
            case GWest:
                return 0;
            case GNorth:
                return 1;
            default:
                return -1;
        }
    }

    static String dirstr(GraphDirection dir){
        switch(dir){
            case GEast:
                return "East";
            case GWest:
                return "West";
            case GNorth:
                return "North";
            case GSouth:
                return "South";
            case GEnd:
                return "End";
            default:
                return "Unknown";
        }
    }

};


template<typename T, int pw, int ph>
void print(Point<T, pw, ph> p){
    debug_print(F("("));
    debug_print(p.x);
    debug_print(F(","));
    debug_print(p.y);
    debug_print(F(")"));
}


#endif //FINAL_PROJECT_GRAPH_H
