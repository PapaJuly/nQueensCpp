#include <iostream>
#include <stack>
using namespace std;

const int N = 4;
struct chessBoard
{
    int board[N][N] = {0};
    chessBoard(int arr[][N], int size)
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                board[i][j] = arr[i][j];
            }
        }
    }
};
void print(int print[][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << print[i][j] << " ";
        }
        cout << endl;
    }
}
bool checkSpot(int board[][N], int row, int col)
{
    if (row >= N || col >= N)
    {
        return false;
    }
    for (int i = row, j = col; i >= 0, j < N; j++, i--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0, j >= 0; j--, i--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    for (int i = row; i >= 0; i--)
    {
        if (board[i][col] == 1)
        {
            return false;
        }
    }
    return true;
}
void placeQueen(int board[][N], int x, int y)
{
    board[x][y] = 1;
}
void removeQueen(int board[][N], int row, int col)
{
    board[row][col] = 0;
}
int fillRow(int board[][N], const int row, const int col)
{
    if (row >= N || col >= N)
        return 108;
    for (int i = col; i < N; i++)
    {
        if (checkSpot(board, row, i))
        {
            placeQueen(board, row, i);
            return i;
        }
    }
    return 108;
}
void fillAllRows(int board[][N])
{
    int i = 0;
    int aux = 108;
    int temper = 0;
    stack<int> result;

    while (i < N && i >= 0)
    {
        aux = fillRow(board, i, temper);
        temper = 0;

        if (aux != 108)
        {
            result.push(aux);
            i += 1;
        }
        else
        {
            i -= 1;
            temper = result.top();
            board[i][temper] = 0;
            temper = temper + 1;
            result.pop();
        }
    }
    print(board, N);
    cout << endl;
}
bool fillBoardRecursively(int board[][N], int row)
{
    chessBoard aux = chessBoard(board, N);
    if (row >= N)
    {
        return true;
    }
    for (int i = 0; i < N; i++)
    {
        if (checkSpot(aux.board, row, i))
        {
            aux.board[row][i] = 1;
            if (fillBoardRecursively(aux.board, row + 1))
            {
                print(aux.board, N);
                cout << endl;
            }
            aux.board[row][i] = 0;
        }
    }
    return false;
}

int main()
{

    int board[N][N] = {0};
    /*
     board [0][0] = 1;
     print(board, N);
     cout << checkSpot(board, 1, 1);
     */
    // fillAllRows(board);
    fillBoardRecursively(board, 0);
    // fillBoard(board);
    // fillBoard(board, 0);

    return 0;
}
