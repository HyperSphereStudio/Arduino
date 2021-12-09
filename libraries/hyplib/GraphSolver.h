#include "Graph.h"

template<typename T, int w, int h>
class Graph;

template<typename T, int w, int h>
class Point;

class GraphSolver{

    template<typename T, int w, int h>
    static GraphDirection getNearestDirection(Point<T, w, h> curr_loc, Point<T, w, h> goto_loc, bool checked){
        float diffX = goto_loc.x - curr_loc.x;
        float diffY = goto_loc.y - curr_loc.y;
        if(diffX == 0 && diffY == 0){
            return GEnd;
        }

        if(diffX >= 0 && diffY >= 0){
            return (checked ? (diffX > diffY ? GNorth : GEast) : (diffX > diffY ? GEast : GNorth));
        }else if(diffX >= 0 && diffY <= 0){
            return (checked ? (diffX > diffY ? GSouth : GEast) : (diffX > abs(diffY) ? GEast : GSouth));
        }else if(diffX <= 0 && diffY <= 0){
            return (checked ? (diffX < diffY ? GSouth : GWest) : (diffX < diffY ? GWest : GSouth));
        }else{
            return (checked ? (abs(diffX) > diffY ? GNorth : GWest) : (abs(diffX) > diffY ? GWest : GNorth));
        }
    }
public:

    template<typename T, int w, int h>
    static void findPath(Graph<T,w, h>* g, Point<T, w, h> curr_loc, Point<T, w, h> goto_loc, vector<GraphDirection>* dirs){
        using TPoint = Point<T, w, h>;
        TPoint checkPoint;
        GraphDirection angle;
        if(!g->isSafePoint(goto_loc)){
            goto_loc = TPoint::getChangePoint(curr_loc, getNearestDirection(curr_loc, goto_loc, false), 1);
            if(!g->isSafePoint(goto_loc)){
                goto_loc = TPoint::getChangePoint(curr_loc, getNearestDirection(curr_loc, goto_loc, true), 1);
            }
        }
        while(!curr_loc.compare(goto_loc)){
            print(curr_loc);
            print(goto_loc);
            debug_print("\n");
            angle = getNearestDirection(curr_loc, goto_loc, false);
            checkPoint = TPoint::getChangePoint(curr_loc, angle, 1);
            if(!checkPoint.compare(goto_loc) && !g->isSafePoint(checkPoint)){
                angle = getNearestDirection(curr_loc, goto_loc, true);
                checkPoint = TPoint::getChangePoint(curr_loc, angle, 1);
            }
            curr_loc = checkPoint;
            dirs->push_back(angle);
        }
    }
};