Code gets input file and produces a maze based off of the specifications as a series of nodes pointing to each other, then traverses the maze.

The input file describes the starting point, finishing point and the (y,x) coordinates of the walls, represented as '#'.


## Map.h File
Contains the classes and maze building code.

### Map class
Each section of the maze is built as a node with four pointers to other map nodes. The node also contains the position, type (e.g. wall, empty, start, finish...), and status (e.g. visited).
The rest of the class is mostly getters and setters.

### mapList
Contains a pointer to a head and tail map type. Generates a net of map types all pointing to each other. First a row of map types are created and pointed to each other. Then the next row is created, and if there is a previous row, the map types are set to point to each other with the top and bottom pointers.

## Source.cpp
1. Get maze dimmensions from from input file
2. Use class mapList to generate maze
3. Get starting point and finishing point from input file, and set points on maze
4. Get wall coordinates from input file, and set walls in maze
5. Use stack/heap algorithm to traverse maze
6. Get state of each section of the maze as a string, and print string to a text file.


To Run The Code:
g++ -g Source.cpp -o Source -lm
Maze
