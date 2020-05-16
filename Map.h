//#pragma once
#include <string>
#include <vector>

using namespace std;

class Map
{
private:
	//coordinate spot;
	int x;
	int y;
	bool empty;
	bool wall;
	bool start;
	bool finish;
	//Dead end if at least three out of four links are blocked
	bool deadEnd;

	//If this map value is the currentl location
	bool currentLocation;
	//has an open link in this direction; aka map value linked in this direction is not wall, edge, deadend
	bool canGoUp;
	bool canGoDown;
	bool canGoLeft;
	bool canGoRight;
	bool visited;
	//Manhattan Value of map; to be set when maze is constructed
	int manhattanValue = 0;

public:
	Map *left; //prev
	Map *right; //next
	Map *up;
	Map *down;

	//Default as empty
	Map()
	{
		x = 0;
		y = 0;
		empty = true;
		wall = false;
		start = false;
		finish = false;
		deadEnd = false;
		//--------------------
		left = 0;
		right = 0;
		up = 0;
		down = 0;
		visited = false;
		currentLocation = false;
	}
	//Creates map data value with coordinate instatiated
	Map(int one, int two)
	{
		x = one;
		y = two;
		empty = true;
		wall = false;
		start = false;
		finish = false;
		left = 0;
		right = 0;
		up = 0;
		down = 0;
		visited = false;
		currentLocation = false;
	}
	bool getDeadEnd()
	{
		return deadEnd;
	}
	bool getE()
	{
		return empty;
	}
	bool getW()
	{
		return wall;
	}
	bool getS()
	{
		return start;
	}
	bool getF()
	{
		return finish;
	}
	int getX()
	{
		return x;
	}
	int getY()
	{
		return y;
	}
	bool getV()
	{
		return visited;
	}
	bool getME()
	{
		return currentLocation;
	}
	//set value of state as true or false. If true in one state, all others are set as false
	void setE(bool x)
	{
		empty = x;
		if (x == true)
		{
			wall = true;
			start = false;
			finish = false;
		}
	}
	void setW(bool x)
	{
		wall = x;
		if (x == true)
		{
			empty = false;
			start = false;
			finish = false;
		}
	}
	void setS(bool x)
	{
		start = x;
		if (x == true)
		{
			wall = false;
			empty = false;
			finish = false;
		}
	}
	void setF(bool x)
	{
		finish = x;
		if (x == true)
		{
			wall = false;
			start = false;
			empty = false;
		}
	}
	void setCoor(int a, int b)
	{
		x = a;
		y = b;
	}

	void setV(bool vic)
	{
		visited = vic;
	}
	void setDeadEnd(bool v)
	{

		v = deadEnd;
		/*
		//Check how many invalid directions a map value has, if more than two, dead-end
		int counter = 0;
		//if the right Map value is a deadend or a wall or an edge, add one to counter
		if ((right)->getDeadEnd() == true || (right)->getW() == true || (right) == 0)
		{
			counter ++;
		}

		if ((left)->getDeadEnd() == true || (left)->getW() == true || (left) == 0)
		{std::cout << "Check1";
			counter ++;
		}
		
		if (up->getDeadEnd() == true || up->getW() == true || up == 0)
		{
			counter ++;
		}

		if ((down)->getDeadEnd() == true || (down)->getW() == true || (down) == 0)
		{
			counter ++;
			//std::cout << "Check1";
		}

		if (counter >= 3)
		{
			deadEnd = true;
		}*/
	}
	void setME(bool thee)
	{
		currentLocation = thee;
	}

	void setLeft(Map *el)
	{
		left = el;
	}
	void setRight(Map *el)
	{
		right = el;
	}
	void setUp(Map *el)
	{
		up = el;
	}
	void setDown(Map *el)
	{
		down = el;
	}

	void setManhattanValue(int value)
	{
		manhattanValue = value;
	}
	int getManhattanValue()
	{
		return manhattanValue;
	}

};

//linked List of map values, with head and tail map value pointers
class mapList
{
private:
	
public:
	Map *head;
	Map *tail;
	mapList() 
	{
		head = tail = 0;
	}

	//Create a maze net using row and column lengths
		//(x, y)
	//(column, rows) = (10,11)
	void createNet(int row, int column)
	{
		
		//Create maze net using rows and columns for coordinates
		for (int yi = 0; yi <= row; yi++)
		{
			for (int xi = 0; xi <= column-1; xi++)
			{
				if (xi == 0 && yi == 0)
				{
					//Create beginning of maze net
					tail = head = new Map(xi, yi);
				}
				//If x coordinate = 0, start new row
				if (xi == 0 && yi != 0)
				{
					//Go back to start of row
					Map *ptr2 = tail;
					while (ptr2->left != 0)
					{
						ptr2 = ptr2->left;
					}
					//new element added below tail
					ptr2->down = new Map (xi, yi);
					//new element's up linked to tail
					(ptr2->down)->up = ptr2;
					//tail = new element
					tail = ptr2->down;
				}
				if(xi != 0)
				{
					//Create new map to right of tail
					tail->right = new Map(xi, yi);
					//link new map's left to tail
					(tail->right)->left = tail;
					//tail = new element
					tail = (tail->right);
				}
			}
		}
		if (head->down != 0)
		{
			//Complete the maze net by connecting above and below
			Map *pointerAbove = head;
			Map *pointerBelow = head->down;

			//While the lower pointer is not at the end of the map net
			while (pointerBelow->down != 0)
			{
				//Pointers to keep track of beginning of rows
				Map *start2 = pointerBelow;
				//Move right until pB reaches the end
				while (pointerBelow->right != 0)
				{
					pointerBelow = pointerBelow->right;
					pointerAbove = pointerAbove->right;
					//Link map elements
					//point pB and pA to each other
					pointerBelow->up = pointerAbove;
					pointerAbove->down = pointerBelow;
				}
				//Set pointers to lower rows
				pointerBelow = start2->down;
				pointerAbove = start2;
			}
		}
	}

	//Adds a single new Map element to linked list
	void addToTail(Map temp, int column, int row)
	{
		if (head == 0)
		{
			tail = head = new Map (temp);
		}
		else
		{
			Map *counter = head;
			int num = 1;
			while (counter->right != 0)
			{
				num++;
				counter = counter->right;
			}
			//If the element is the not the last element in a row, continue row
			if (num < column)
			{
				tail->right = new Map(temp);
				(tail->right)->left = tail;
				tail = (tail->right);
				
				//Connect above and below elements together, if more than one row
				if (head->down != 0)
				{
					Map *pointerAbove = head;
					Map *pointerBelow = head->down;
					//Move downwards until pB reaches the end
					while (pointerBelow->down != 0)
					{
						pointerBelow = pointerBelow->down;
						pointerAbove = pointerAbove->down;
					}
					//Move right until pB reaches the end
					while (pointerBelow->right != 0)
					{
						pointerBelow = pointerBelow->right;
						pointerAbove = pointerAbove->right;
					}
					//point pB and pA to each other
					pointerBelow->up = pointerAbove;
					pointerAbove->down = pointerBelow;
				}

			}
			//if the element is the last element in a row, start new row
			if (num == column)
			{
				//Map pointer starting at head
				Map *pointer5 = head;
				//Move all the way down the first column
				while (pointer5->down != 0)
				{
					pointer5 = pointer5->down;
				}
				//Start new row with new Map element
				pointer5->down = new Map(temp);
				//Point new Map element's up pointer to pointed element
				(pointer5->down)->up = pointer5;
				//Tail equals new Map element
				tail = pointer5->down;
			}
		}
	}

	//Index starts at 0
	Map outputAt(int index)
	{
		Map *id;
		id = head;
		int counter = 0;

		if (head != 0)
		{
			//while able to go right or down, continue until unable
			while (counter != index)
			{
				if ((id->right) != 0)
				{
					id = (id->right);
					counter++;
				}
				else
				{
					//Go back to the first element on the left of the row and then go down one element
					if ((id->down) != 0)
					{
						while (id->left != 0)
						{
							id =(id->left);
						}
						id = (id->down);
						counter++;
					}
					else
					{
						std::cout << "Out of Bounds. \nLast Value Returned.";
						counter = index;
					}
				}
				

			}
		}
		else
		{
			std::cout << "Maze is Empty. Out of Bounds.";
		}
		//Error will return last value in maze
		return *id;
	}

	//OutputAt function using (x,y): starts a (0,0)
	Map outputAt(int x, int y)
	{
		Map *castle = head;
		for (int i = 0; i < x; i++)
		{
			castle = castle->right;
		}
		for (int j = 0; j < y; j++)
		{
			castle = castle->down;
		}
		return *castle;
	}
	
	/*
	//Returns memeory address at x,y coordinates
	Map* giveAddress(int x, int y)
	{
		Map *castle = head;
		for (int i = 0; i < x; i++)
		{
			castle = castle->right;
		}
		for (int j = 0; j < y; j++)
		{
			castle = castle->down;
		}
		return castle;
	}
	*/

	/*
	void exitMaze() 
	{
		
		//exitMaze()
			//initialize stack, exitCell, entryCell, currentCell = entryCell;
			//while currentCell is not exitCell
				//mark currentCell as visited;
				//push onto the stack the unvisited neighbors of currentCell;
				//if stack is empty
					//failure;
				//else pop off a cell from the stack and make it currentCell;
			//success;
		
		stack <int> commands;
		Map *playerOne = head;
		//Move to starting point
		while (playerOne->getS() == false)
		{
			//Move right, unless unable
			if (playerOne->right != 0)
			{
				playerOne = playerOne->right;
			}
			//if unable, go down, then move all the way back to the left most element
			else
			{
				playerOne = playerOne->down;
				while (playerOne->left != 0)
				{
					playerOne = playerOne->left;
				}
			}
		}

		//Traverse Maze
		while (playerOne->getF() != true)
		{
			playerOne->setV(true);

			if (playerOne->up != 0 && (playerOne->up)->getV() == false)
			{
				cout << "Push Up" << endl;
				commands.push(1);
			}
			if (playerOne->down != 0 && (playerOne->down)->getV() == false)
			{
				cout << "Push Down" << endl;
				commands.push(2);
			}
			if (playerOne->left != 0 && (playerOne->left)->getV() == false)
			{
				cout << "Push Left" << endl;
				commands.push(3);
			}
			if (playerOne->right != 0 && (playerOne->right)->getV() == false)
			{
				cout << "Push Right" << endl;
				commands.push(4);
			}

			cout << commands.top() << endl;

			if (commands.empty() == true)
			{
				cout << "Error: Stack Empty. The Minotaur Got You." << endl;
				exit(1);
			}
			else
			{
				int move = commands.top();
				commands.pop();
				if (move == 1 && (playerOne->up)->getW() == false)
				{
					cout << "Move up" << endl;
					playerOne = playerOne->up;
				}
				if (move == 2 && (playerOne->down)->getW() == false)
				{
					cout << "Move down" << endl;
					playerOne = playerOne->down;
				}
				if (move == 3 && (playerOne->left)->getW() == false)
				{
					cout << "Move left" << endl;
					playerOne = playerOne->left;
				}
				if (move == 4 && (playerOne->right)->getW() == false)
				{
					cout << "Move right" << endl;
					playerOne = playerOne->right;
				}
			}

		}
	}
	*/

	/*
	void exitMaze(int startx, int starty) 
	{
		int row, col;
		//currentCell = entryCell;
		Map *p1 = head;
		for (int i = 0; i < startx; i++)
		{
			p1 = p1->right;
		}
		for(int j = 0; j < starty; j++)
		{
			p1 = p1->down;
		}

		while (!(p1->getF == true)) 
		{
			//row = currentCell.x;
			//col = currentCell.y;
			//cout << *this; // print a snapshot;
			if (!(currentCell == entryCell))
				store[row][col] = visited;
			pushUnvisited(row - 1, col);
			pushUnvisited(row + 1, col);
			pushUnvisited(row, col - 1);
			pushUnvisited(row, col + 1);
			if (mazeStack.empty()) {
				cout << *this;
				cout << “Failure\n”;
				return;
			}
			else currentCell = mazeStack.pop();
		}
		cout << *this;
		cout << "Success\n";
	}
	*/

	//SETS MANHATTAN VALUE FOR ALL ELEMENTS IN MAZE	
	void setManhattanForAll(int rows, int columns, int finishX, int finishY)
	{
		Map *id;
		id = head;
		int counter = 0;

		if (head != 0)
		{
			//while able to go right or down, continue until unable
			while (counter != (rows*columns))
			{
				int mhX = abs((id->getX()) - finishX);
				int mhY = abs((id->getY()) - finishY);
				id->setManhattanValue(mhX + mhY);


				if ((id->right) != 0)
				{
					id = (id->right);
					counter++;
				}
				else
				{
					//Go back to the first element on the left of the row and then go down one element
					if ((id->down) != 0)
					{
						while (id->left != 0)
						{
							id = (id->left);
						}
						id = (id->down);
						counter++;
					}
					else
					{
						//std::cout << "Out of Bounds. \nLast Value Returned.";
						counter = rows*columns;
					}
				}


			}
		}
		else
		{
			std::cout << "Maze is Empty. Out of Bounds.";
		}
		/*
		//Decides which direction to move the scanner
		bool goLeft = true;
		Map *scanner = head;
		for (int i = 0; i < (columns*rows); i++)
		{
			//Manhattan Value: absolute Value of (x - finalX) + absolute Value of (y - finalY)
			int mhX = abs((scanner->getX()) - finishX);
			int mhY = abs((scanner->getY()) - finishY);
			scanner->setManhattanValue(mhX+mhY);
			//Checks if you can move further left to a new value
			if (scanner->getX() == columns && goLeft == true)
			{
				scanner = scanner->down;
				goLeft = false;
			}
			//Checks if you can move further right to a new value
			if (scanner->getX() == columns && goLeft == false)
			{
				scanner = scanner->down;
				goLeft = true;
			}
			
			//Move to next map value
			if(goLeft == true)
			{
				scanner = scanner->left;
			}
			else
			{
				scanner = scanner->right;
			}
			
		}
		*/
	}


	//Index starts at 0
	int outputMH(int index)
	{
		Map *id;
		id = head;
		int counter = 0;

		if (head != 0)
		{
			//while able to go right or down, continue until unable
			while (counter != index)
			{
				if ((id->right) != 0)
				{
					id = (id->right);
					counter++;
				}
				else
				{
					//Go back to the first element on the left of the row and then go down one element
					if ((id->down) != 0)
					{
						while (id->left != 0)
						{
							id = (id->left);
						}
						id = (id->down);
						counter++;
					}
					else
					{
						std::cout << "Out of Bounds. \nLast Value Returned.";
						counter = index;
					}
				}


			}
		}
		else
		{
			std::cout << "Maze is Empty. Out of Bounds.";
		}
		//Error will return last value in maze
		return id->getManhattanValue();
	}

	/*
	//Index starts at 0
	Map* outputAddress(int index)
	{
		Map *id;
		id = head;
		int counter = 0;

		if (head != 0)
		{
			//while able to go right or down, continue until unable
			while (counter != index)
			{
				if ((id->right) != 0)
				{
					id = (id->right);
					counter++;
				}
				else
				{
					//Go back to the first element on the left of the row and then go down one element
					if ((id->down) != 0)
					{
						while (id->left != 0)
						{
							id = (id->left);
						}
						id = (id->down);
						counter++;
					}
					else
					{
						std::cout << "Out of Bounds. \nLast Value Returned.";
						counter = index;
					}
				}


			}
		}
		else
		{
			std::cout << "Maze is Empty. Out of Bounds.";
		}
		//Error will return last value in maze
		return id;
	}
	*/
};

//Creates a heap using a vector
class heapVec
{
private:
	vector <Map*> heapTree;
	int rowSize;
	int columnSize;

public:
	//Adds row and column dimensions to data
	heapVec();
	heapVec(int r, int c)
	{
		rowSize = r;
		columnSize = c;
	}
	//Returns size of vector
	int lengthHeap()
	{
		return heapTree.size();
	}
	//Adds elements and organizes based on their manhattan values
	void heapAdd(Map *ptr)
	{
		heapTree.push_back(ptr);
		int x = (heapTree.size())-1;

		while (x != 0 && (heapTree[x])->getManhattanValue() > (heapTree[x - 1])->getManhattanValue())
		{
			Map *temp = heapTree[x-1];
			heapTree[x - 1] = heapTree[x];
			heapTree[x] = temp;

			x--;
		}
	}
	//return heap data as string
	string outputHeap()
	{
		int multiplyer = 1;
		string allData = "";
		for (int i = 0; i < heapTree.size(); i++)
		{
			//cout << "Address: " << heapTree[i] << endl;
			if ((heapTree[i]) != 0)
			{
				allData += "(";
				allData += to_string((heapTree[i])->getX());
				allData += ", ";
				allData += to_string((heapTree[i])->getY());
				allData += "): ";
				allData += to_string((heapTree[i])->getManhattanValue());

				
				//cout << "allData: " << allData << endl;
				if (multiplyer == (i+1))
				{
					allData += " \n";
					multiplyer *= 2;
					//cout << "allData: " << allData << endl;
				}
				else
				{
					allData += " \t";
				}
				//cout << "allData: " << allData << endl;
				
			}
		}

	return allData;
	}
	//return last address of element in heap
	Map* address()
	{
		return heapTree[heapTree.size() - 1];
	}

	//return element that the last address of heap was pointing to
	Map lastElement()
	{
		Map test = *(heapTree.back());
		return test;
	}

	//remove last heap element
	void heapRemoveLast()
	{
		heapTree.pop_back();
	}

	//return if element is in heap or not
	bool findMap(Map* test)
	{
		bool q = false;
		for (int i = 0; i < heapTree.size(); i++)
		{
			if (heapTree[i] == test)
			{
				q = true;
			}
		}
		return q;
		
	}

	//Creates a higher Manhattan Value for visited places, making them lower priority than normal
	void heapAddX(Map *ptr)
	{
		if (findMap(ptr) == false)
		{
		
			heapTree.push_back(ptr);
			int x = (heapTree.size()) - 1;
			//*************Add lower priority to visited locations
			int mh = (heapTree[x])->getManhattanValue();
			if ((heapTree[x])->getV() == true)
			{
				mh += (rowSize*columnSize);
			}

			while (x != 0 && mh > (heapTree[x - 1])->getManhattanValue())
			{
				Map *temp = heapTree[x - 1];
				heapTree[x - 1] = heapTree[x];
				heapTree[x] = temp;

				x--;
			}
		}
	}

	//Better heap string format
	string simplePrint()
	{
		//Unable to create heap format without empty value as first element
		vector <Map*> heapTree2;
		heapTree2.push_back(0);
		for (int ii = 0; ii < heapTree.size(); ii++)
		{
			heapTree2.push_back(heapTree[ii]);
		}

		string result = "\n:::::HEAP:::::\n1: [";

		int multiplyer = 1;
		for (int i = 1; i < heapTree2.size(); i++)
		{
			if ((heapTree2[i-1]) != 0)
			{
				result += "(";
				result += to_string((heapTree2[i-1])->getX());
				result += ", ";
				result += to_string((heapTree2[i-1])->getY());
				result += "): ";
				result += to_string((heapTree2[i-1])->getManhattanValue());

				
				//cout << "allData: " << allData << endl;
				if ((multiplyer) == i )
				{
					result += "] \n" + to_string(i) + ": [";
					multiplyer *= 2;
					
				}
				else
				{
					result += "\t";
				}
				//cout << "allData: " << allData << endl;
				

			}
			else
			{
				multiplyer *= 2;
			}
		}
		result += "]\n";
		return result;
	}

	//*****************************************************
	void heapRemove(int x, int y)
	{
		int location;
		for (int i = 0; i < heapTree.size(); i++)
		{
			if (heapTree[i]->getX() == x && heapTree[i]->getY() == y)
			{
				location = i;
				i = heapTree.size();
				cout << "Location: " << i << endl;
			}
		}
		//Swap data from location to bottom
		Map *temp = heapTree[heapTree.size()-1];
		heapTree[location] = temp;
		//Remove data from last bottom
		heapTree[heapTree.size() - 1] = NULL;
		int x1 = location;
		//Move data at location to appropriate level
		while (x1 != 0 && x1 != (heapTree.size() - 1) && (heapTree[x1])->getManhattanValue() < (heapTree[x1 - 1])->getManhattanValue())
		{
			//if manhattan value is less than below, swap with down
			Map *temp = heapTree[x1 - 1];
			heapTree[x1 - 1] = heapTree[x];
			heapTree[x1] = temp;
			x1--;
		}
		int x2 = location;
		while (x2 != 0 && x2 != (heapTree.size() - 1) && (heapTree[x2])->getManhattanValue() > (heapTree[x2 + 1])->getManhattanValue())
		{
			//if manhattan value is greater than above, swap with above
			Map *temp = heapTree[x2 + 1];
			heapTree[x2 + 1] = heapTree[x2];
			heapTree[x2] = temp;
			x2++;
			
		}
	}
};




/*
class heapArray
{
private:
	int nextPosition = 0;
	int row;
	int column;
	Map** heapFormat[];
	
public:
	heapArray(int rows, int colu)
	{
		heapFormat[(rows*colu)];
		row = rows;
		column = colu;
	}

	int lengthHeap()
	{
		int x = 0;
		int y = 0;
		for (int i = 0; i < (row*column); i++)
		{
			if ((heapFormat[i]) == (0))
			{
				x++;
			}
			else
			{
				y++;
			}
		}
		return y;
	}

	void enqueue(Map *pointer)
	{
		int x = nextPosition;
		heapFormat[nextPosition] = &pointer;
		nextPosition++;

		while (x != 0 && (((heapFormat[x])->getManhattanValue()) > ((heapFormat[x-1])->getManhattanValue())))
		{
			Map *temp;
			temp = heapFormat[x];
			heapFormat[x] = heapFormat[x - 1];
			heapFormat[x - 1] = temp;

			x--;
		}
		/*
		int x;
		for (int i = 0; i < (row*column); i++)
		{
			if (heapFormat[i] == NULL)
			{
				heapFormat[i] = pointer;
				i = (row*column);
				x = i;
				//cout << "Inserted Element at index " << i << endl;
			}
		}
		
		while (x != 0 && (heapFormat[x])->getManhattanValue() > heapFormat[x-1]->getManhattanValue())
		{
			Map *temp = heapFormat[x];
			heapFormat[x] = heapFormat[x - 1];
			heapFormat[x - 1] = temp;
		}
		*/
/*
	}

	void dequeue(int index)
	{
		
		//extract the element from the root;
		//put the element from the last leaf in its place;
		//remove the last leaf;
		//// both subtrees of the root are heaps;
		//p = the root;
		//while p is not a leaf and p < any of its children
		//	swap p with the larger child;
		
	}

	string outputHeap()
	{
		int multiplyer = 1;
		string allData = "";
		for (int i = 0; i < (row*column); i++)
		{
			if (heapFormat[i] != NULL)
			{
				allData += "(";
				allData += to_string((heapFormat[i])->getX());
				allData += ", ";
				allData += to_string((heapFormat[i])->getY());
				allData += "): ";
				allData += to_string((heapFormat[i])->getManhattanValue());

				if (multiplyer == i)
				{
					allData += " \n";
					multiplyer *= 2;
				}
				else
				{
					allData += " \t";
				}

			}
		}
		return allData;
	}

};
*/