#include <bits/stdc++.h>
using namespace std;
const int N = 8;
bool isSafe(vector<int> &board, int row, int col) {  
    for (int i = 0; i < row; i++) {
        if (board[i] == col || abs(board[i]-col) == abs(i-row))
            return false;
    }
    return true;
}
void printBoard(vector<int> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i] == j) cout << "Q ";
            else cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

void solveNQueens(int row, vector<int> &board, int &count) {
    if (row == N) {
        count++;
        printBoard(board);
        return;
    }
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col)) {
            board[row] = col;
            solveNQueens(row+1, board, count);
            
        }
    }
}

int main() {
    vector<int> board(N, -1);
    int totalSolutions = 0;
    solveNQueens(0, board, totalSolutions);
    cout << "Total solutions: " << totalSolutions << endl;
    return 0;
}