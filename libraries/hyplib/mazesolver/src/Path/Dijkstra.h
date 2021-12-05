#ifndef __DIJKSTRA__
#define __DIJKSTRA__

#include "Path.h"
#include <queue>

template<typename Data_Type>
class Dijkstra : public Path<Data_Type> {
	using _myBase = Path<Data_Type>;
    using TVertex = Vertex<Data_Type>;
    using TPath = Path<Data_Type>;
private:

	struct orderByDijkstra {
		bool operator()(TVertex *lhs, TVertex* rhs) {
			return rhs->getLength() < lhs->getLength();
		}
	};

public:

	void findPath(TVertex * start, TVertex * end) {
		if (!intialCheck(start, end)) return;
		start->setLength(0);
		_findPath<orderByDijkstra>(start, end);
	}

protected:

	int setDistance(TVertex* from, TVertex* to, int toLen = 1) {
		to->setLength(to->getLength() > from->getLength() + toLen ? from->getLength() + toLen : to->getLength());
		return to->getLength();
	}

	template <class comparator>
	void _findPath(TVertex * start, TVertex * end) {
		std::priority_queue<TVertex*, std::vector<TVertex*>, comparator> q;
		q.push(start);
		TVertex* next = nullptr;

		while (!q.empty()) {

			next = q.top();
			q.pop();

			if (next->isVisted()) continue;

			next->setVisted(true);
			++TPath::count;

			if (next == end) break;

			for (auto & x : *next) {
				if (x.isReachable() && !x.getVertex()->isVisted()) {
					setDistance(next, x.getVertex(), x.getEdgeLength());
					q.push(x.getVertex());
				}
			}

		}

		trace(start, end);

	}

	void trace(TVertex * start, TVertex * end) {

		if (!end->isVisted()) return; // cannot reach end

		int min = 0;
		TVertex * next = end, *buffer = nullptr;
        TPath::path.push_front(next);
		while (next != start) {
			min = next->getLength();

			for (auto & x : *next) {
				if (x.isReachable() && min > x.getVertex()->getLength()) {
					buffer = x.getVertex();
					min = x.getVertex()->getLength();
				}
			}

            TPath::path.push_front(buffer);
			next = buffer;
		}

	}

};

#endif // !__DIJKSTRA__
