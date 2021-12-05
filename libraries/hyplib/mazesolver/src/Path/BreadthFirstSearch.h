#ifndef __BREADTHFIRSTSEARCH__
#define __BREADTHFIRSTSEARCH__

#include "Path.h"
#include <queue>

template<typename Data_Type>
class BreadthFirstSearch : public Path<Data_Type> {
    using TVertex = Vertex<Data_Type>;
    using TPath = Path<Data_Type>;
public:

	void findPath(TVertex * start, TVertex * end) {
		if (!TPath::intialCheck(start, end)) return;

		TPath::count = 0;
		std::queue<TVertex*> q;
		q.push(start);
		start->setLength(0);
		TVertex* next = nullptr;

		while (!q.empty()) {
			next = q.front();
			q.pop();

			if (next->isVisted()) continue;
			++TPath::count;

			next->setVisted(true);

			if (next == end) break;

			for (auto & x :  *next) {
				if (x.isReachable() && !x.getVertex()->isVisted()) {
					q.push(x.getVertex());
					x.getVertex()->setLength(next->getLength() + 1);
				}
			}

		}

		if (!end->isVisted()) return; // end cannot be reached

		trace(end, start, next->getLength() - 1);

	}

private:

	bool trace(TVertex * start, TVertex * end, int count) {
        TPath::path.push_front(start);

		for (auto & x : *start) {
			if (x.isReachable() && x.getVertex()->getLength() == count) {
				trace(x.getVertex(), start, count - 1);
				return true;
			}
		}

		return false;
	}

};

#endif // !__BREADTHFIRSTSEARCH__
