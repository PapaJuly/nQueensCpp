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
void removeQueen(int board [][N], int row, int col){
    board[row][col]=0;
}
int fillRow(int board [][N], const int row, const int col){
        if (row >= N || col >= N )
        return 108;
        for (int i = col; i<N; i++){
            if (checkSpot(board, row, i)){
                placeQueen(board, row, i);
                return i;
            }
        }
        return 108;
}
void fillAllRows (int board[][N]){

    stack <int> queens;
    
    while (queens.size() < N){
        if (queens.empty()){
            queens.push(fillRow(board, 0, 0));
        }
        else if(queens.top()==108){
            queens.pop();
            if ( queens.top() < N -1){
            int aux = queens.top();
            int sizeAux = queens.size() - 1;
            board[queens.size()][aux] = 0;
            queens.pop();
            queens.push(fillRow(board, aux +1, sizeAux));
            }
        }
        else {
            queens.push(fillRow(board, queens.size(), 0));
        }
    }

    print(board, N);
}
/*void fillBoard(int board [][N], int row, int col){
    int i = 0;
    int aux = 108;
    int temper = 0;
    stack <int> result;
    while (i<N){
        result.push(fillRow(board,i,temper));
        print(board,N);
        cout<< "\n";
        if(result.top() > N){
            result.pop();
            i = i - 1;
            board[i][result.top()] = 0;
            temper = result.top()+1;
            result.pop(); 
        }
        else{
        cout<< "\n" << result.top() << " \n" ;
        i++;
        }
    }
    }
    */

int main(){
         
    int board [N][N] = {0};
   /* 
    board [0][0] = 1;
    print(board, N);
    cout << checkSpot(board, 1, 1);
    */
    fillAllRows(board);
    print(board, N);

    return 0;
}


