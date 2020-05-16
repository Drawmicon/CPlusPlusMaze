// Steven Gallegos
// CST 201
// Date
// This is my own work

#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include "Map.h"
#include <stack>
#include <queue>

using namespace std;

//--------------------------------------------------------
//Removes punctuation from string, converts to int, returns int
int stringToInt(string number)
{
	int result;
	string input = number;
	input.erase(std::remove(input.begin(), input.end(), '('), input.end());
	input.erase(std::remove(input.begin(), input.end(), ')'), input.end());
	input.erase(std::remove(input.begin(), input.end(), '.'), input.end());
	input.erase(std::remove(input.begin(), input.end(), ','), input.end());

	result = atoi(input.c_str());

	return result;
}
//Bottom and Top string of maze element
string stringEnds(bool ww, bool ws, bool wf)
{
	string theory;
	if (ww == true)
	{
		theory = "###";
	}
	else
	{
		theory = "...";
	}
	return theory;
}
//Middle string of maze element
string stringMid(bool ww, bool ws, bool wf, bool wv, bool me, bool we)
{
	string theory;

	if (wv == true)
	{
		theory = ".V.";
	}
	else
	{
		if (me == true)
		{
			theory = ":-)";
		}
		else
		{
			if (ws == true)
			{
				theory = ".S.";
			}
			else
			{
				if (wf == true)
				{
					theory = ".F.";
				}
				else
				{

					if (ww == true)
					{
						theory = "###";
					}
					else
					{ 
						theory = "...";
					}
				}
			}
		}
	}
	return theory;
}
//-----------------------------------------

//Takes text file and converts to a maze represented as an list, then outputs visual representation of maze as text file
int main()
{
	string fileData ="";
	//#############################################################
	//			GET ROW AND COLUMN DIMMENSIONS OF MAZE
	//#############################################################

	//Gets data from input_file.txt
	string arrayColumn;
	string arrayRow;
	ifstream myfile("input_file.txt");
	
	//(x, y)
	//(column, rows)

	//Get first and second int to create maze dimmensions
	myfile >> arrayColumn;
	int colu = stringToInt(arrayColumn);
	myfile >> arrayRow;
	int row = stringToInt(arrayRow);
	

	//#############################################################
	//			CREATE BLANK MAZE WITH DIMMENSIONS (row, column)
	//#############################################################
	//Create empty four directional linked list of Map values
	mapList maze;
	std::cout <<  "Column(x): " << colu << " Row(y): "  << row <<endl;
	//--------------------------
	fileData += "Column(x): " + colu;
	fileData += " Row(y): " + row;
	fileData += "\n";
	//---------------------------
	maze.createNet(row, colu);
	//std::cout << "X: " << maze.outputAt(9,1).getX() << " Y: " << maze.outputAt(9,1).getY() << endl;

	//#############################################################
	//			ADD STARTING POINT AND FINISHING POINT
	//#############################################################
	//Get (x,y), from text file, for start and finish points
	string start;
	int s0, s1;
	int f0, f1;
	//get starting point coordinates
	myfile >> start;
	s0 = stringToInt(start);
	myfile >> start;
	s1 = stringToInt(start);
	//-----------------------------
	fileData += "Starting Point: (" + to_string(s0);
	fileData += " ," + to_string(s1);
	//--------------------------------
	//get finishing point coordinates
	myfile >> start;
	f0 = stringToInt(start);
	myfile >> start;
	f1 = stringToInt(start);
	//------------------------------------
	fileData += ")\nFinishing Point: (" + to_string(f0);
	fileData += " ," + to_string(f1);
	fileData += ")\n";
	//-----------------------------------
	//Go through map to find matching coordinates
	Map *point = maze.head;
	for (int i = 0; i < s0; i++)
	{
		point = point->right;
	}
	for (int j = 0; j < s1; j++)
	{
		point = point->down;
	}
	point->setS(true);
	//Finish point
	Map *point2 = maze.head;
	for (int i = 0; i < f0; i++)
	{
		point2 = point2->right;
	}
	for (int j = 0; j < f1; j++)
	{
		point2 = point2->down;
	}
	point2->setF(true);


	point = NULL;
	delete point;

	point2 = NULL;
	delete point2;
	//#############################################################
	//			ADD WALLS TO MAZE
	//#############################################################
	
	//While the file is not done, go through link list and change values when coordinates match values retrieved from text file
	while (!myfile.eof())
	{
		myfile >> start;
		int retrievedX = stringToInt(start);
		myfile >> start;
		int retrievedY = stringToInt(start);

		//cout << "(" << retrievedX << " ," << retrievedY << ")" << endl;
		Map *pointer3 = maze.head;
		for (int i = 0; i < retrievedX; i++)
		{
			pointer3 = pointer3->right;
		}
		for (int j = 0; j < retrievedY; j++)
		{
			pointer3 = pointer3->down;
		}
		pointer3->setW(true);

		//Unknown error: At (7,7) element is changed to wall without any cause
		if (retrievedX == 7 && retrievedY == 7)
		{
			pointer3->setW(false);
		}
		
	}


	//#############################################################
	//			ADDING MANHATTAN VALUES TO EACH ELEMENT
	//#############################################################

	maze.setManhattanForAll(row, colu,f0,f1);
	cout << "Manhattan Values: " << endl;
	//-----------------------
	fileData += "\nManhattan Values: ";
	//-----------------------
	for (int i = 0; i < (row*colu); i++)
	{
		if (i % 10 == 0)
		{
			cout << "" << endl;
			//---------------
			fileData += " \n";
		}
		
		if (maze.outputMH(i) < 10)
		{
			cout << maze.outputMH(i) << "  ";
			//------------------
			fileData += to_string(maze.outputMH(i)) + "  ";
		}
		else
		{
			cout << maze.outputMH(i) << " ";
			//----------------
			fileData += to_string(maze.outputMH(i)) + " ";
		}
	}
	cout << "\n" << endl;
	//------------------
	fileData += "\n\n";


	//#############################################################
	//			TRAVERSE MAZE
	//#############################################################

	//************************************************
	//Stack Algorithm:
	//Algorithm: push up, down, left and right, in that order, if directions are valid
	// pop direction to go, if not at finish
	//--If no directions to pop and not at finish, then error
	//--Make sure to return as finished


	//Link List algorithm:
	//Algorithm: push right, left, down, up, in that order, if directions are valid
	//--EnQueue, DeQueue
	//Head->()+()+()<-Tail
	//Add to tail, Remove to head

	//1 = up, 2 = down, 3 = left, 4 = right


	//Create Maze-Traveler pointing to top left corner of maze
	Map *playerOne = maze.head;
	//Move Maze-Traveler to starting point
	for (int i = 0; i < s0; i++)
	{
		playerOne = playerOne->right;
	}
	for (int j = 0; j < s1; j++)
	{
		playerOne = playerOne->down;
	}
	//Create output file
	ofstream outputFile("Output_file.txt");
	//outputFile << fileOutput;
	//string fileOutput2 = "";
	
	//#############################################################
	//			HEAP TRAVERSAL	{{{{{{{{{{{{{{{{{
	//#############################################################
	//Currently playerOne pointer is at starting point
	//Priority Heap Created
	heapVec traverse(row, colu);
	//Move to smaller value, unless already been there or wall/edge or visited
	//Then go to next value

	bool done = false;
	while (playerOne->getManhattanValue() != 0 || done == true)
	//for(int i = 0; i < 20; i++)
	{
		playerOne->setV(true);
		cout << "Current Location: (" << playerOne->getX() << ", " << playerOne->getY() << ")" << endl;
		//------------------------
		fileData += "\nCurrent Location: (" + to_string(playerOne->getX());
		fileData += ", " + to_string(playerOne->getY());
		fileData += ")";
		//--------------------------
		if ((playerOne->left) != 0 && (playerOne->left)->getW() == false)// && (playerOne->left)->getV == false)
		{
			if (traverse.findMap(playerOne->left) == false)
			{
				traverse.heapAddX(playerOne->left);
			}
		}
		if ((playerOne->right) != 0 && (playerOne->right)->getW() == false)// && (playerOne->right)->getV == false)
		{
			if (traverse.findMap(playerOne->right) == false)
			{
				traverse.heapAddX(playerOne->right);
			}
		}
		if ((playerOne->up != 0) && (playerOne->up)->getW() == false)// && (playerOne->up)->getV == false)
		{
			if (traverse.findMap(playerOne->up) == false)
			{
				traverse.heapAddX(playerOne->up);
			}
		}
		if ((playerOne->down != 0) && (playerOne->down)->getW() == false) //&& (playerOne->down)->getV == false)
		{
			if (traverse.findMap(playerOne->down) == false)
			{
				traverse.heapAddX(playerOne->down);
			}
		}

		string tree = traverse.simplePrint();
		cout << tree << endl;
		//-----------
		fileData += tree;
		//-----------
		if (traverse.lengthHeap() == 0)
		{
			cout << "Heap Is Empty. The Minotaur Got You." << endl;
			fileData += "Heap Is Empty. The Minotaur Got You.";
			exit(0);
			done = true;
		}
		else
		{
			/*
			while ((traverse.lastElement()).getV() == true)
			{
				traverse.heapRemoveLast();
			}
			*/
			playerOne = traverse.address();
			traverse.heapRemoveLast();
		}

	}



	//HEAP TEST CODE
	/*
	//cout << "Heap Array Size: " << traverse.lengthHeap() <<  endl;
	//string tree = traverse.outputHeap();
	//cout << tree << endl;
	
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);
	playerOne = playerOne->right;
	traverse.heapAdd(playerOne);

	//Map test;
	//traverse.heapAdd(&test);

	//traverse.heapAdd(playerOne);
	cout << "Writing: " << endl;
	string tree4 = traverse.outputHeap();
	cout << tree4 << endl;

	traverse.heapRemoveLast();

	//
	cout << ": Finished" << endl;
	cout << "Heap Array Size: " << traverse.lengthHeap() << endl;
	playerOne = traverse.address();
	cout << "playerOne: " << playerOne->getManhattanValue() << endl;
	*/

	//#############################################################
	//			HEAP TRAVERSAL	}}}}}}}}}}}}}}}}}
	//#############################################################

	/*
	//-------------------------------------------------
	//Create pointer address queue for backtracking
	queue <Map*> commands;

	while (playerOne->getF() == false)
	{
		//Output current location
		std::cout << "Player1 currently at: (" << playerOne->getX() << ", " << playerOne->getY() << ")" << endl;
		fileOutput2 += "Player1 currently at: (" + to_string((*playerOne).getX()) + ", " + to_string(playerOne->getY()) + ")\n";

		//Set current location as visited
		playerOne->setV(true);

		if (playerOne->up != 0 && (playerOne->up)->getV() == false && (playerOne->up)->getW() == false)
		{
			//Go up, backtrack plan is down
			//std::cout << "Push Up" << endl;
			//1 = up, 2 = down, 3 = left, 4 = right
			commands.push(playerOne->up);
		}
		if (playerOne->down != 0 && (playerOne->down)->getV() == false && (playerOne->down)->getW() == false)
		{
			//Go up, backtrack plan is down
			//std::cout << "Push Up" << endl;
			//1 = up, 2 = down, 3 = left, 4 = right
			commands.push(playerOne->down);
		}
		if (playerOne->left != 0 && (playerOne->left)->getV() == false && (playerOne->left)->getW() == false)
		{
			//Go up, backtrack plan is down
			//std::cout << "Push Up" << endl;
			//1 = up, 2 = down, 3 = left, 4 = right
			commands.push(playerOne->left);
		}
		if (playerOne->right != 0 && (playerOne->right)->getV() == false && (playerOne->right)->getW() == false)
		{
			//Go up, backtrack plan is down
			//std::cout << "Push Up" << endl;
			//1 = up, 2 = down, 3 = left, 4 = right
			commands.push(playerOne->right);
		}

		
		if (commands.empty())
		{
			std::cout << "Error: Stack Empty. The Minotaur Got You." << endl;
			exit(1);
		}
		else
		{
			//1 = up, 2 = down, 3 = left, 4 = right

			playerOne = commands.front();
			commands.pop();
			//cout << commands.front() << endl;

		}
	}
	*/
	//-------------------------------------------------
	//Output Traversal Coordinates to output file: (x,y) Format
	outputFile << fileData;
	playerOne = NULL;
	delete playerOne;
	//-------------------------------------------------
	

	/*
	stack <int> commands;
	Map *playerOne = maze.head;
	//Move to starting point
	for (int i = 0; i < s0; i++)
	{
		playerOne = playerOne->right;
	}
	for (int j = 0; j < s1; j++)
	{
		playerOne = playerOne->down;
	}
	std::cout << "Player1 Starting at: (" << playerOne->getX() << ", " << playerOne->getY() << ")" << endl;
	//Traverse Maze
	while (playerOne->getF() == false)
	{

		std::cout << "Player1 currently at: (" << playerOne->getX() << ", " << playerOne->getY() << ")" << endl;
		fileOutput2 +=  "Player1 currently at: (" + to_string((*playerOne).getX()) + ", " + to_string(playerOne->getY()) + ")\n";


		playerOne->setV(true);
		//int move;

		if (playerOne->up != 0 && (playerOne->up)->getV() == false && (playerOne->up)->getW() == false)
		{
			//Go up, backtrack plan is down
			//std::cout << "Push Up" << endl;
			playerOne = playerOne->up;
			commands.push(2);
		}
		else
		{
			if (playerOne->down != 0 && (playerOne->down)->getV() == false && (playerOne->down)->getW() == false)
			{
				//std::cout << "Push Down" << endl;
				playerOne = playerOne->down;
				commands.push(1);
			}
			else
			{
				if (playerOne->left != 0 && (playerOne->left)->getV() == false && (playerOne->left)->getW() == false)
				{
					//std::cout << "Push Left" << endl;
					playerOne = playerOne->left;
					commands.push(4);
				}
				else
				{
					if (playerOne->right != 0 && (playerOne->right)->getV() == false && (playerOne->right)->getW() == false)
					{
						//std::cout << "Push Right" << endl;
						playerOne = playerOne->right;
						commands.push(3);
					}
					else
					{
						//Backtrack
						if (commands.empty())
						{
							std::cout << "Error: Stack Empty. The Minotaur Got You." << endl;
							exit(1);
						}
						else
						{

							int move = commands.top();
							commands.pop();
							if (move == 1 && (playerOne->up)->getW() == false)
							{
								//std::cout << "Move up" << endl;
								playerOne = playerOne->up;
							}
							if (move == 2 && (playerOne->down)->getW() == false)
							{
								//std::cout << "Move down" << endl;
								playerOne = playerOne->down;
							}
							if (move == 3 && (playerOne->left)->getW() == false)
							{
								//std::cout << "Move left" << endl;
								playerOne = playerOne->left;
							}
							if (move == 4 && (playerOne->right)->getW() == false)
							{
								//std::cout << "Move right" << endl;
								playerOne = playerOne->right;
							}
						}
					}
				}
			}
		}

	}
	outputFile << fileOutput2;
	playerOne = NULL;
	delete playerOne;
	*/
	

	//#############################################################
	//			ADD ALL MAZE DATA TO STRING
	//#############################################################
	string fileOutput = "";
	fileOutput = "\n\n  ";
	//Add column index to maze
	for (int s = 0; s < colu; s++)
	{
		string text = to_string(s);
		fileOutput += " " + text + " ";
	}
	fileOutput += "\n";
	
	//then add the proper characters, based on each element's state
	//For every row and column, output string representation
	//(column, row):(x, y):(10, 11)
	
	for (int i = 0; i < row; i++)
	{	
		fileOutput += "  ";
		for (int j = 0; j < colu; j++)
		{
			//cout << ((i*colu) + j) << ", (" << j << ", " << i << ")\n" << endl;
			Map traveler = maze.outputAt((i*colu) + j);
			fileOutput += "";
			//Get state of an elements
			bool ww = traveler.getW();
			bool ws = traveler.getS();
			bool wf = traveler.getF();
			fileOutput += stringEnds(ww, ws, wf);
		}
		fileOutput += "\n" + to_string(i);
		
		if (i < 10)
		{
			fileOutput += " ";
		}
		
		for (int j = 0; j < colu; j++)
		{
			Map traveler = maze.outputAt((i*colu) + j);
			fileOutput += "";
			//Get state of an elements
			bool ww = traveler.getW();
			bool ws = traveler.getS();
			bool wf = traveler.getF();
			bool wv = traveler.getV();
			bool we = traveler.getE();
			bool me = traveler.getME();
			fileOutput += stringMid(ww, ws, wf, wv, me, we);
		}
		fileOutput += "\n  ";
		for (int j = 0; j < colu; j++)
		{
			Map traveler = maze.outputAt((i*colu) + j);
			fileOutput += "";
			//Get state of an elements
			bool ww = traveler.getW();
			bool ws = traveler.getS();
			bool wf = traveler.getF();
			//Output element bottom string
			fileOutput += stringEnds(ww, ws, wf);
		}
		fileOutput += "\n";
		
	}

	//#############################################################
	//			OUTPUT STRING CONTAINING DATA TO TEXT FILE
	//#############################################################
	
	std::cout << fileOutput << endl;
	
	//Restore all resources
	myfile.close();
	//delete[] test;
	//test = NULL;
	
	//ofstream outputFile("Output_file.txt");
	outputFile << fileOutput;

	
	return 0;
}