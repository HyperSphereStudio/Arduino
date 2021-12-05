#ifndef __DEPTHFIRSTSEARCH__
#define __DEPTHFIRSTSEARCH__

#include "Path.h"

template<typename Data_Type>
class DepthFirstSearch : public Path<DataType> {
    using TVertex = Vertex<Data_Type>;
    using TPath = Path<Data_Type>;
public:
	// default constructor
	DepthFirstSearch() {}

	// destructor
	~DepthFirstSearch() {}

	void findPath(TVertex * start, TVertex * end) {
		if (intialCheck(start, end))	_findPath(start, end);
	}

private:
	bool _findPath(TVertex * start, TVertex * end) {
		if (!start || start->isVisted()) return false;

		start->setVisted(true); 
		++TPath::count;

		if (start == end) {
			path.push_front(start);
			return true;
		}
		
		for (auto & x : *start) {
			if (_findPath(x.getVertex(), end)) {
                TPath::path.push_front(start);
				return true;
			}
		}


		return false;
	}

};
#endif // !__DEPTHFIRSTSEARCH__
