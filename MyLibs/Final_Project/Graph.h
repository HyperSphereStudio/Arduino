//
// Created by JohnB on 11/18/2021.
//

#ifndef FINAL_PROJECT_GRAPH_H
#define FINAL_PROJECT_GRAPH_H

#include "core.h"
#include "mazesolver/src/Maze.h"
#include "mazesolver/src/Path/BreadthFirstSearch.h"

typedef char GraphDirection;

#define GEast 0
#define GNorth 1
#define GWest 2
#define GSouth 3


template<typename T, int width, int height>
class Point{
public:
    T x, y;
    Point(T x, T y) : x(x), y(y){}
    Point() : Point(0, 0){}

    bool operator==(Point p) const{
        return (p.x >= x && p.x + width < x) && (p.y >= y && p.y + height < y);
    }

    float distance(Point p){
        return sqrt(pow((float) (p.x - x), 2) + pow((float) (p.y - y), 2));
    }

    Point& operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
};

template<typename T, int point_width, int point_height>
class Graph;

template<typename Data_Type, int point_width, int point_height>
class MazeReader : public IMazeReader<Data_Type>{
    Graph<Data_Type, point_width, point_height>* g;
    using TPoint = Point<Data_Type, point_width, point_height>;
public:
    MazeReader(Graph<Data_Type, point_width, point_height>* g) : g(g){}

    void isVertex(Data_Type y, Data_Type x, bool & top, bool & down, bool & left, bool & right, bool & isGoal) override{
        x = g->itransX(x);
        y = g->itransY(y);
        top = g->isSafePoint(TPoint(x, y + 1));
        down = g->isSafePoint(TPoint(x, y - 1));
        left = g->isSafePoint(TPoint(x - 1, y));
        right = g->isSafePoint(TPoint(x + 1, y));
    }

    void setSize(size_t & row, size_t & col) override{
        row = (g->getMaxY() - g->getMinY()) / point_height;
        col = (g->getMaxX() - g->getMinX()) / point_width;
    }
};

template<typename T, int point_width, int point_height>
class Graph : public vector<Point<T, point_width, point_height>>{
    using TPoint = Point<T, point_width, point_height>;
    using TVertex = Vertex<T>;
    using TVector = vector<TPoint>;

    T maxX;
    T minX;
    T maxY;
    T minY;
    Maze<T> maze;
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
        dprintstrl("Finding Path:(");
        dprint(curr_loc.x);
        dprintstrl("),(");
        dprint(curr_loc.y);
        dprintstrl(")->(");
        dprint(goto_loc.x);
        dprintstrl("),(");
        dprint(goto_loc.y);
        dprintstrlln(")");
#endif
        maze.reset();
        BreadthFirstSearch<T> bfs;
        TVertex* vex = nullptr;
        TVertex* vex2 = nullptr;
        maze.getVertex(transX(curr_loc.x), transY(curr_loc.y), vex);
        maze.getVertex(transX(goto_loc.x), transY(goto_loc.y), vex2);
        bfs.findPath(vex, vex2);
        dprintstrl("Path Found!!! Number of Moves:");
        dprintln(bfs.getCount());
        T lastX = curr_loc.x;
        T lastY = curr_loc.y;
        for(TVertex* const& v : bfs.getPath()){
            auto newX = itransX(v->getColumn());
            auto newY = itransY(v->getRow());

            //No Idea... Dont ask
            auto diffY = newX - lastX;
            auto diffX = newY - lastY;

            if(diffX == -1 && diffY == 0){
                dirs->push_back(GEast);
            }else if(diffX == 1 && diffY == 0){
                dirs->push_back(GWest);
            }else if(diffX == 0 && diffY == -1){
                dirs->push_back(GNorth);
            }else if(diffX == 0 && diffY == 1){
                dirs->push_back(GSouth);
            }
            lastX = newX;
            lastY = newY;
        }
    }

    void mazeify(){
        dprintstrlln("Building Maze");
        MazeReader<T, point_width, point_height> reader(this);
        maze.setMaze(reader);
        TVector::clear();
    }

    T transY(T y){
        return maxY - y;
    }

    T itransY(T y){
        return maxY - y;
    }

    T itransX(T x){
        return x + minX;
    }

    T transX(T x){
        return x - minX;
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
            default:
                return "South";
        }
    }

};


#endif //FINAL_PROJECT_GRAPH_H
