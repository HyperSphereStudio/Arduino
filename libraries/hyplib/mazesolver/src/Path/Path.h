#ifndef __PATH__
#define __PATH__

#include <list>
#include "../Vertex.h"

using std::list;

template<typename T>
class Path {
    using TVertex = Vertex<T>;
protected:
	list<TVertex*> path; // path from start to end
	int count = 0; // used for iteration count
	
	/*
		Inital check done before path finding 

		Parameters
		Start end : postion to start to end

		return true if specified path finding should continue
	*/
	bool intialCheck(TVertex * start, TVertex * end) {
		if (!start || !end)	// if start or end are nullptr path doesnot exist
			return false;

		if (start == end) { // if start equals end path found return false
			path.push_back(start);
			return false;
		}

		return true; // find path 
	}

public:
	// default constructor
	Path() {}

	//default 
	~Path() {
		path.clear();
	}

	// added function for printing

	// findPath function to implement path specific algorithm
	virtual void findPath(TVertex * start, TVertex * end) = 0;

	// return count
	int getCount() {
		return count;
	}

	// get path
	const list<TVertex*> & getPath() {
		return path;
	}

};
#endif // !__PATH__
