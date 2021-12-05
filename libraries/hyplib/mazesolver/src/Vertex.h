#ifndef __VERTEX__
#define __VERTEX__

#include <climits> 
#include <list>
#include <array>

using std::list;
using std::array;

template<typename Data_Type>
struct Coordinates {
	Data_Type row = -1;
	Data_Type col = -1;
};

template<typename Data_Type>
class Vertex {
    using TCoord = Coordinates<Data_Type>;
public:
	class Edge {
	public:

		Edge() {}

		using iterator = typename list<TCoord>::iterator;
		using const_iterator = typename list<TCoord>::const_iterator;

		iterator begin() {
			return intermidate.begin();
		}

		const_iterator begin() const {
			return intermidate.cbegin();
		}

		iterator end() {
			return intermidate.end();
		}

		const_iterator end() const {
			return intermidate.cend();
		}

		void push_front_intermidate(Data_Type row, Data_Type col) {
            TCoord toPush;
			toPush.row = row;
			toPush.col = col;
			intermidate.push_front(toPush);
		}

		void push_back_intermidate(Data_Type row, Data_Type col) {
            TCoord toPush;
			toPush.row = row;
			toPush.col = col;
			intermidate.push_back(toPush);
		}

		bool isReachable() const {
			return to;
		}

        Data_Type getEdgeLength() const {
			return len;
		}

		Vertex* getVertex() {
			return to;
		}

		void set(Vertex* v, Data_Type length) {
			to = v;
			len = length;
		}

		~Edge() {
			to = nullptr;
		}
			   
	private:
        Data_Type len = INT_MAX; // length set to infinity
		Vertex * to = nullptr; // to which vertex
		list<TCoord> intermidate; // important intermidate points

		friend class Vertex;

	};

private:
	bool visted = false; // to check if cell is visted 
    Data_Type len = INT_MAX; // length set to infinity

	static const int EDGE_SIZE = 4;

	// Edge directions[EDGE_SIZE]; // Edges to top down left right cells
	array<Edge, EDGE_SIZE> directions; // Edges to top down left right cells


	// position of cell of in maze
    Data_Type row = -1;
    Data_Type col = -1;

public:
	using iterator = typename array<Edge, EDGE_SIZE>::iterator;
	using const_iterator = typename array<Edge, EDGE_SIZE>::const_iterator;

	~Vertex() {}

	iterator begin() {
		return directions.begin();
	}

	const_iterator begin() const {
		return directions.begin();
	}

	iterator end() {
		return directions.end();
	}

	const_iterator end() const {
		return directions.end();
	}


	array<Edge, EDGE_SIZE>& getEdges() {
		return directions;
	}

	int edgesSize() {
		return EDGE_SIZE;
	}

	// return row position
    Data_Type getRow() {
		return row;
	}

	// return column position
    Data_Type getColumn() {
		return col;
	}

	// set row and column position 
	void setPosition(Data_Type _row, Data_Type _col) {
		row = _row;
		col = _col;
	}

	/*
		Set Vertex to direction and length to vertex
	*/

	void setTop(Vertex * v, Data_Type len = 1) {
		directions[0].to = v;
		directions[0].len = len;
	}

	void setDown(Vertex * v, Data_Type len = 1) {
		directions[1].to = v;
		directions[1].len = len;
	}

	void setLeft(Vertex * v, Data_Type len = 1) {
		directions[2].to = v;
		directions[2].len = len;
	}

	void setRight(Vertex * v, Data_Type len = 1) {
		directions[3].to = v;
		directions[3].len = len;
	}

	// set length of Vertex
	void setLength(Data_Type _len) {
		len = _len;
	}

	// get length of Vertex
    Data_Type getLength() {
		return len;
	}

	// set visted to b
	void setVisted(bool b) {
		visted = b;
	}

	// return visted
	bool isVisted() {
		return visted;
	}

	/*
		len set to infinity
		visited set to false
	*/
	void reset() {
		visted = false;
		len = INT_MAX;
	}

	Edge& connectingEdge(Vertex * to) {
		for (int i = 0; i < edgesSize(); ++i) {
			if (getEdges()[i].getVertex() == to) {
				return getEdges()[i];
			}
		}
		throw;
	}


};

#endif // !__VERTEX__