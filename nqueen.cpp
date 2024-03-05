#include <iostream>
#include <stack>
using namespace std;

const int N = 4;
void print(int print[][N] , int size)
{    
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << print[i][j]<< " ";
        }          
        cout<< endl; 
    }
}
bool checkSpot (int board [][N], int row, int col ){
    if (row>=N || col >= N){
        return false;
    }
   /* for (int i = row, j=col, k=col; i>=0, j < N, k>= 0; i--, j++, k--){
        if (board[i][col]== 1){
            return false;
        }
    }
    */
    for (int i=row, j=col; i>=0 , j<N; j++, i--){
        if (board[i][j]==1){
            return false;
        }
    }
    for(int i=row, j=col; i>=0 , j>=0; j--, i--){
        if (board[i][j]==1){
            return false;
        }
    }
    for (int i = row; i >= 0; i--){
        if (board[i][col]){
            return false;
        }
    }
    return true;
}
void placeQueen(int board [][N],int x, int y){
    board[x][y]=1;
}
void fillBoard(int board [][N], int row, int col){
    for (int y = row; y<N ; y++){
        for (int x = col; x<N ; x++){
            if(checkSpot(board, y, x)){
                placeQueen(board,y,x);
                break;
            }
            else if (x== N -1){

            }
        }
}
}
int main(){
         
    int board [N][N] = {0};
   /* 
    board [0][0] = 1;
    print(board, N);
    cout << checkSpot(board, 1, 1);
    */
    fillBoard(board, 0, 0);
    print(board, N);
    return 0;
}


