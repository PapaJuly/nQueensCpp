#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

const int N = 6;
int counter = 0;
ofstream opFile;
  
struct chessBoard
{
    int board[N][N];
    void start(){
        for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                        board[i][j] = 0;
}
}
}
    chessBoard(int arr[][N], int size)
    {
     	start();
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
            opFile << print[i][j] << " ";
        }
        opFile << endl;
    }
    opFile<<endl;
}
void printOnTerminal(int print[][N],int size){
    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << print[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
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
inline void placeQueen(int board[][N], int x, int y)
{
    board[x][y] = 1;
}
inline void removeQueen(int board[][N], int row, int col)
{
    board[row][col] = 0;
}
bool fillBoardRecursively(int board[][N], int row)
{
    chessBoard aux = chessBoard(board, N);
    if (row >= N)
    {
        counter += 1;
        return true;
    }
    for (int i = 0; i < N; i++)
    {
        if (checkSpot(aux.board, row, i))
        {
            aux.board[row][i] = 1;
            if (fillBoardRecursively(aux.board, row + 1))
            {
                print (aux.board, N);
               // cout << endl;
            }
            aux.board[row][i] = 0;
        }
    }
    return false;
}
int main()
{

    int board[N][N] = {0};
    opFile.open("opFile.txt");
    fillBoardRecursively(board, 0);

    opFile <<"The total solutions found: " << counter;
    opFile.close();

    //fillAllRows(board);
    //printOnTerminal(board,N);
   
    return 0;
}
