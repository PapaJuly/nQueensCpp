#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

const int N = 3;
int counter = 0;
ofstream opFile;
void placeQueen(int board[][N], int x, int y)
{
    board[x][y] = 1;
}
void print(int print[][N], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < N; j++)
        {
            opFile << print[i][j] << " ";
        }
        opFile << endl;
    }
    opFile<<endl;
}
bool checkSpot(int board[][N], int row, int col)
{
    if (row >= N || col >= N)
    {
        return false;
    }
    for (int i = row, j = col; i >= 0 && j < N; j++, i--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    for (int i = row, j = col; i >= 0 && j >= 0; j--, i--)
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
int main(){
     int board[N][N] = {0};
    opFile.open("oneSol.txt");
    fillAllRows(board);
    return 0;
}