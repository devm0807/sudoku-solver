#include <iostream>
#include <vector>
using namespace std;

class Sudoku
{
public:
    void printboard(vector<vector<int>> board)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                cout << board[i][j] << " ";
                if (j == 2 || j == 5)
                {
                    cout << "| ";
                }
            }
            cout << endl;
            if (i == 2 || i == 5)
            {
                cout << "---------------------" << endl;
            }
        }
    }
    void initialise(vector<vector<int>> &board)
    {
        board = {
            {0, 0, 0, 0, 0, 0, 0, 0, 3},
            {3, 5, 1, 6, 0, 0, 9, 0, 0},
            {4, 0, 9, 0, 0, 0, 0, 0, 7},
            {0, 7, 0, 0, 0, 0, 1, 9, 0},
            {9, 4, 6, 0, 5, 0, 8, 0, 0},
            {1, 0, 0, 3, 0, 0, 0, 0, 5},
            {0, 0, 0, 4, 1, 5, 0, 0, 0},
            {0, 0, 5, 0, 0, 3, 0, 0, 0},
            {0, 0, 0, 0, 0, 8, 0, 6, 1},
        };
    }
    bool check(vector<vector<int>> board, int row, int col, int num)
    {
        for (int i = 0; i < 9; i++)
        {
            if (board[row][i] == num)
                return false;
        }
        for (int i = 0; i < 9; i++)
        {
            if (board[i][col] == num)
                return false;
        }
        int block_row = row - row % 3;
        int block_col = col - col % 3;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[block_row + i][block_col + j] == num)
                    return false;
            }
        }
        return true;
    }
    bool solver(vector<vector<int>> &board, int row, int col)
    {
        // cout << "#####################" << endl;
        // printboard(board);
        if (row == 8 && col == 9) // finished & out of bounds
        {
            return true; // solved
        }
        if (col == 9) // not finished & out of bounds
        {
            row++;
            col = 0;
        }
        if (board[row][col] > 0)
        {
            return solver(board, row, col + 1);
        }
        for (int num = 1; num <= 9; num++)
        {
            if (check(board, row, col, num)) // if num is allowed in row,col
            {
                board[row][col] = num;           // set current cell = num
                if (solver(board, row, col + 1)) // if the further board is solved
                {
                    return true;
                }
            }
            board[row][col] = 0; // if num is not allowed or if board is not solved with num in row,col then erase num
        }
        return false;
    }
};

int main()
{
    vector<vector<int>> board(9, vector<int>(9, 0));
    Sudoku sudoku;
    sudoku.initialise(board);
    cout<<"Please input the board to be solved:"<<endl;
    for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                cin >> board[i][j];
    cout<<"The board to be solved is:"<<endl;
    sudoku.printboard(board);

    if (sudoku.solver(board, 0, 0))
    {
        cout << "The solved sudoku is:" << endl;
        sudoku.printboard(board);
    }
    else
    {
        cout << "board is invalid" << endl;
    }
}