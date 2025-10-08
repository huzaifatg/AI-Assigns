#include <bits/stdc++.h>
using namespace std;

// Tic-Tac-Toe game using Minimax Algorithm
const int SIZE = 3;
char board[SIZE][SIZE];
const char COMPUTER = 'X';
const char HUMAN = 'O';
const char EMPTY = '_';

// Initialize the board
void initializeBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

// Print the current board state
void printBoard() {
    cout << "\nCurrent Board:\n";
    cout << "   0   1   2\n";
    for (int i = 0; i < SIZE; i++) {
        cout << i << "  ";
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "  -----------\n";
    }
    cout << "\n";
}

// Check if someone has won
char checkWinner() {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != EMPTY) {
            return board[i][0];
        }
    }
    
    // Check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != EMPTY) {
            return board[0][j];
        }
    }
    
    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != EMPTY) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != EMPTY) {
        return board[0][2];
    }
    
    return EMPTY; // No winner yet
}

// Check if the board is full
bool isBoardFull() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

// Check if the game is over
bool isGameOver() {
    return checkWinner() != EMPTY || isBoardFull();
}

// Evaluate the current board state
int evaluate() {
    char winner = checkWinner();
    if (winner == COMPUTER) return 10;
    if (winner == HUMAN) return -10;
    return 0; // Draw or game not over
}

// Minimax algorithm implementation
int minimax(int depth, bool isMaximizing) {
    int score = evaluate();
    
    // If game is over, return the score
    if (score != 0) return score;
    if (isBoardFull()) return 0; // Draw
    
    if (isMaximizing) {
        int maxScore = INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    int currentScore = minimax(depth + 1, false);
                    board[i][j] = EMPTY; // Undo move
                    maxScore = max(maxScore, currentScore);
                }
            }
        }
        return maxScore;
    } else {
        int minScore = INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = HUMAN;
                    int currentScore = minimax(depth + 1, true);
                    board[i][j] = EMPTY; // Undo move
                    minScore = min(minScore, currentScore);
                }
            }
        }
        return minScore;
    }
}

// Find the best move for the computer using Minimax
pair<int, int> findBestMove() {
    int bestScore = INT_MIN;
    pair<int, int> bestMove = {-1, -1};
    
    cout << "Computer is thinking...\n";
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int score = minimax(0, false);
                board[i][j] = EMPTY; // Undo move
                
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = {i, j};
                }
            }
        }
    }
    
    cout << "Computer's best move score: " << bestScore << "\n";
    return bestMove;
}

// Make a move
bool makeMove(int row, int col, char player) {
    if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == EMPTY) {
        board[row][col] = player;
        return true;
    }
    return false;
}

// Get human move
pair<int, int> getHumanMove() {
    int row, col;
    cout << "Enter your move (row col): ";
    cin >> row >> col;
    return {row, col};
}

// Main game loop
void playGame() {
    initializeBoard();
    cout << "=== TIC-TAC-TOE with MINIMAX AI ===\n";
    cout << "You are 'O' and Computer is 'X'\n";
    cout << "Enter moves as: row column (0-2)\n";
    
    printBoard();
    
    while (!isGameOver()) {
        // Human's turn
        cout << "Your turn:\n";
        pair<int, int> humanMove = getHumanMove();
        
        if (!makeMove(humanMove.first, humanMove.second, HUMAN)) {
            cout << "Invalid move! Try again.\n";
            continue;
        }
        
        printBoard();
        
        if (isGameOver()) break;
        
        // Computer's turn
        cout << "Computer's turn:\n";
        pair<int, int> computerMove = findBestMove();
        makeMove(computerMove.first, computerMove.second, COMPUTER);
        cout << "Computer chose: " << computerMove.first << " " << computerMove.second << "\n";
        
        printBoard();
    }
    
    // Game over - announce result
    char winner = checkWinner();
    if (winner == COMPUTER) {
        cout << "Computer wins! Better luck next time.\n";
    } else if (winner == HUMAN) {
        cout << "Congratulations! You won!\n";
    } else {
        cout << "It's a draw! Good game.\n";
    }
}

// Menu system
void displayMenu() {
    cout << "\n========================================\n";
    cout << "    MINIMAX ALGORITHM DEMONSTRATION\n";
    cout << "========================================\n";
    cout << "1. Play Tic-Tac-Toe vs AI\n";
    cout << "2. Show Minimax Algorithm Info\n";
    cout << "3. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice (1-3): ";
}

void showAlgorithmInfo() {
    cout << "\n=== MINIMAX ALGORITHM INFORMATION ===\n";
    cout << "Minimax is a decision-making algorithm used in game theory.\n";
    cout << "It's designed for two-player, zero-sum games like Tic-Tac-Toe.\n\n";
    cout << "How it works:\n";
    cout << "1. Explores all possible game states\n";
    cout << "2. Maximizing player tries to maximize the score\n";
    cout << "3. Minimizing player tries to minimize the score\n";
    cout << "4. Assumes both players play optimally\n";
    cout << "5. Returns the best possible move\n\n";
    cout << "In this implementation:\n";
    cout << "- Computer (X) is the maximizing player\n";
    cout << "- Human (O) is the minimizing player\n";
    cout << "- Win = +10, Loss = -10, Draw = 0\n";
}

int main() {
    int choice;
    
    cout << "Welcome to Minimax Algorithm Demonstration!\n";
    
    while (true) {
        displayMenu();
        cin >> choice;
        
        switch (choice) {
            case 1:
                playGame();
                break;
                
            case 2:
                showAlgorithmInfo();
                break;
                
            case 3:
                cout << "Thank you for playing!\n";
                return 0;
                
            default:
                cout << "Invalid choice! Please enter 1-3.\n";
                break;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
    return 0;
}
