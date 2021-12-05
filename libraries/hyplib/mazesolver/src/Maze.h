#ifndef __MAZE__
#define __MAZE__

#include "Vertex.h"
#include "IMazeReader.h"
#include <list>

using std::list;

/*
	Maze Data Structure
*/

template<typename Data_Type>
class Maze {

public:

	/*
		To tranverse list of TVertexs
	*/
	using TVertex = Vertex<Data_Type>;
	using const_iterator = typename list<TVertex*>::const_iterator;
	using iterator = typename list<TVertex*>::iterator;

	/*
		Default Constructor
	*/
	Maze() {
		goal[0] = nullptr;
		goal[1] = nullptr;
	}

	/*
		Destructor
	*/
	~Maze() {
		clear();
	}

	/*
		Set size of maze
	*/
	void setSize(size_t row, size_t col) {
		_row = row;
		_col = col;
	}

	/*
		Getter for column
	*/
	size_t getColumn() {
		return _col;
	}

	/*
		Getter for row
	*/
	size_t getRow() {
		return _row;
	}

	/*
		push_back into list of TVertex
	*/
	void push_back(TVertex * v) {
		_maze.push_back(v);
	}

	/*
		Iterators 
	*/
	iterator begin() {
		return _maze.begin();
	}

	const_iterator begin() const {
		return _maze.cbegin();
	}

	iterator end() {
		return _maze.end();
	}

	const_iterator end() const {
		return _maze.cend();
	}

	/*
		Reset of list of TVertex
	*/
	void reset() {
		for (auto & x : _maze)
			x->reset();
	}

	/*
		return size of list
	*/
	int listSize() const {
		return _maze.size();
	}

	/*
		clear list
	*/
	void clear() {
		for (auto & x : *this)
			delete x;
		_maze.clear();
		goal[0] = nullptr;
		goal[1] = nullptr;
	}

	/*
		return true if maze is empty
	*/
	bool empty() const {
		return _maze.empty();
	}

	/*
		IMazeReader implement the following functions

		void setSize(size_t & row, size_t & col);
			Needed to set deminsions of the maze

		void isTVertex(int y, int x, bool & top, bool & down, bool & left, bool & right, bool & isGoal);
			Needed to get configration of a cell at row y and col x
			top down left right -> true if you can move in the direction at that cell
			isGoal -> true if cell represent start or end point

	*/
	void setMaze(IMazeReader<Data_Type> & mb) {
		clear();
		mb.setSize(_row, _col);
		bool isGoal = false;

		// for count 
		Data_Type * top_count = new Data_Type[getColumn()]();
		TVertex ** top_next = new TVertex*[getColumn()];
		list<TVertex*> reduntant; // to store reduntant TVertex to later delete

		// for paths
		bool path_top = false, path_down = false, path_right = false, path_left = false;
		for (int line = 0; line < getRow(); ++line)
		{
            Data_Type right_count = 0;
			TVertex * left_next = nullptr;

			for (int index = 0; index < getColumn(); ++index) {
                Data_Type count = 0;
				path_top = false; path_down = false; path_right = false; path_left = false;

				// get directions
				mb.isVertex(line, index, path_top, path_down, path_left, path_right, isGoal);

				// for number of open directions
				if (path_top) ++count;
				if (path_down) ++count;
				if (path_left) ++count;
				if (path_right) ++count;

				// TVertex requires a decision for...
				bool left_right = bool(path_left != path_right); // ...left or right
				bool up_down = bool(path_top != path_down);		 // ...up or down		
				bool all = bool(path_top && path_down && path_left && path_right); //... all options are open -> could or could not be important 

				// create new TVertex
				if (left_right || up_down || all || isGoal) { 
					TVertex * current = new TVertex;
					current->setPosition(line, index);

					if (path_top) { // top
						current->setTop(top_next[index], top_count[index] + 1);
						top_next[index]->setDown(current, top_count[index] + 1);
					}

					if (path_left) { // left
						current->setLeft(left_next, right_count + 1);
						left_next->setRight(current, right_count + 1);
					}

					// set pointer
					top_next[index] = left_next = current;

					// reset count
					top_count[index] = 0;
					right_count = 0;

					if (isGoal) {
						addToGoal(current);
					}

					if (isGoal || count != 2) { // is not reduntant 
						push_back(current);
						isGoal = false;
					}
					else
						reduntant.push_back(current);
				}
				else { 	// increment counter
					++right_count;
					++top_count[index];
				}

			}
		}
		
		// connect TVertexs and remove redundant TVertex
		for (auto & x : reduntant) {
			TVertex* connect[2]; // TVertex to connect
            Data_Type index[2]; // indexes of edges to connect in x
            Data_Type i = 0;
			for (Data_Type j = 0; j < x->edgesSize(); ++j) {
				if (x->getEdges()[j].isReachable()) {
					connect[i] = x->getEdges()[j].getVertex();
					index[i++] = j;
				}
			}

			// find edge between connect[0] and x
			int i1 = 0;
			for (; i1 < x->edgesSize(); ++i1) {
				if (x == connect[0]->getEdges()[i1].getVertex())
					break;
			}

			// find edge between connect[1] and x
			int i2 = 0;
			for (; i2 < x->edgesSize(); ++i2) {
				if (x == connect[1]->getEdges()[i2].getVertex())
					break;
			}

			// update intermidate nodes if x is directly connected
			connect[1]->getEdges()[i2].push_back_intermidate(x->getRow(), x->getColumn());
			for (auto & c : x->getEdges()[index[0]]) {
				connect[1]->getEdges()[i2].push_back_intermidate(c.row, c.col);
			}

			connect[0]->getEdges()[i1].push_back_intermidate(x->getRow(), x->getColumn());
			for (auto & c : x->getEdges()[index[1]]) {
				connect[0]->getEdges()[i1].push_back_intermidate(c.row, c.col);
			}

			// create edge between connect[0] and connect[1]
			connect[0]->getEdges()[i1].set(connect[1], connect[0]->getEdges()[i1].getEdgeLength() + connect[1]->getEdges()[i2].getEdgeLength());
			connect[1]->getEdges()[i2].set(connect[0], connect[0]->getEdges()[i1].getEdgeLength());
			
			// free mememory
			delete x;
			connect[0] = nullptr;
			connect[1] = nullptr;
	 
		}

		// free memory
		for (int i = 0; i < getColumn(); ++i) {
			top_next[i] = nullptr;
		}
		delete[] top_next;

		if (!maze_begin()) addToGoal(*begin());
		if (!maze_end()) addToGoal(*--end());

	}
		
	/*
		Add TVertex to goal
	*/
	void addToGoal(TVertex * v) {
		if (!goal[0]) goal[0] = v;
		else goal[1] = v;
	}
	/*
		return start position
	*/
	TVertex* maze_begin() {
		return goal[0];
	}

	/*
		return end position
	*/
	TVertex* maze_end() {
		return goal[1];
	}

    void getVertex(Data_Type row, Data_Type col, TVertex*& vertex){
        for (auto* i : _maze) {
            if(i->getRow() == row && i->getColumn() == col){
                vertex = &*i;
            }
        }
    }

private:

	list<TVertex*> _maze; // to hold TVertex 
	
	// size of maze
	size_t _row = 0; 
	size_t _col = 0;
	
	TVertex *goal[2]; // start and end positions

};

#endif // !__MAZE__
