// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "helpers.h"
#include "Maze.h"
#include "Queue.h"

bool valid(Maze m, Cell **c, bool **visited, int row, int col);
void path(Maze m, Cell **c, Cell **pred, bool **visited, int row, int col); 

// Direction vectors 
int dRow[] = {-1, 0, 1, 0};
int dCol[] = {0, 1, 0, -1};

bool solve(Maze m) {
    int width = MazeWidth(m);
    int height = MazeHeight(m);
    // Find the entrance in row one
    Cell enter = MazeGetStart(m);
    // Bool of matrix for maze with all initialised to false 
    bool **visited = createBoolMatrix(height, width);
    // Cell matrixes all intialised to (0,0)
    Cell **c = createCellMatrix(height, width);
    Cell **pred = createCellMatrix(height, width);
    // Create new queue
    Queue q = QueueNew();
    // Mark first node as visited
    MazeVisit(m, enter);
    visited[enter.row][enter.col] = true;
    // Queue entrance cell 
    QueueEnqueue(q, enter);
    Cell x;
    while (!QueueIsEmpty(q)) {
        // Get the cell at front of the queue
        x = QueueDequeue(q);
        // Check the adjacent cells 
        for (int i = 0; i < 4; i++) {
            int newRow = x.row + dRow[i];
            int newCol = x.col + dCol[i];
            // Check if the adjacent cell is valid 
            if (valid(m, c, visited, newRow, newCol)) {
                // Mark as visited 
                MazeVisit(m, c[newRow][newCol]);
                visited[newRow][newCol] = true;
                //Keep track of pred
                pred[newRow][newCol].row = x.row;
                pred[newRow][newCol].col = x.col;
                // If the cell is the exit cell 
                if (MazeVisit(m, c[newRow][newCol]) == true) {
                    // Find path
                    path(m, c, pred, visited, newRow, newCol);
                    //Free 
                    QueueFree(q);
                    freeBoolMatrix(visited);
                    freeCellMatrix(c);
                    freeCellMatrix(pred);
                    // Exit found
                    return true;
                } else {
                    // Add this new cell to the end of the queue
                    QueueEnqueue(q, c[newRow][newCol]);
                }
            }
        }
    }
    QueueFree(q);
    freeBoolMatrix(visited);
    freeCellMatrix(c);
    freeCellMatrix(pred);
    // No path exists
    return false;
}

bool valid(Maze m, Cell **c, bool **visited, int row, int col) {
    // Within bounds
    if (row < 0 || col < 0 || row >= MazeHeight(m)|| col >= MazeWidth(m)) {
        return false;
    }
    // Assign values for row and col
    c[row][col].row = row;
    c[row][col].col = col;
    // Check if visited
    if (visited[row][col]) {
        return false;
    }
    // Check if current cell is wall 
    if (MazeIsWall(m, c[row][col])) {
        return false;
    } 
    return true;
}

void path(Maze m, Cell **c, Cell **pred, bool **visited, int row, int col) {
    Cell enter = MazeGetStart(m);
    // Mark exit cell as part of path
    MazeMarkPath(m, c[row][col]);
    // Loop while it's a visited cell 
    while (visited[row][col]) {
        // Get the values stored in pred 
        int newRow = pred[row][col].row;
        int newCol = pred[row][col].col;
        // Mark the pred cell as part of path 
        MazeMarkPath(m, c[newRow][newCol]);
        // Assign as new row and col
        row = newRow;
        col = newCol;
        if (row == enter.row && col == enter.col) {
            break;
        }
    }
    return;
}
 

