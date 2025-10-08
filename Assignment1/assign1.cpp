#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<vector<int>> state;
    string path;
};

vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

vector<pair<int, int>> moves = {{-1,0}, {1,0}, {0,-1}, {0,1}};
vector<char> moveChar = {'U','D','L','R'};

string boardToString(vector<vector<int>> &board) {
    string s="";
    for (auto &row : board)
        for (int x : row) s += to_string(x);
    return s;
}

pair<int,int> findBlank(vector<vector<int>> &state) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(state[i][j]==0) return {i,j};
    return {-1,-1};
}

void printBoard(vector<vector<int>> &board) {
    cout << "\nCurrent Board State:\n";
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            if(board[i][j] == 0) cout << "_ ";
            else cout << board[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void BFS(vector<vector<int>> start) {
    cout << "\n=== Running BFS Algorithm ===\n";
    printBoard(start);
    
    queue<Node> q;
    unordered_set<string> visited;

    q.push({start, ""});
    visited.insert(boardToString(start));

    while(!q.empty()) {
        Node cur = q.front(); q.pop();

        if(cur.state == goal) {
            cout << "BFS Found Solution!\nPath: " << cur.path << "\n";
            cout << "Moves: " << cur.path.size() << "\n";
            cout << "Solution Path: ";
            for(char c : cur.path) {
                switch(c) {
                    case 'U': cout << "Up "; break;
                    case 'D': cout << "Down "; break;
                    case 'L': cout << "Left "; break;
                    case 'R': cout << "Right "; break;
                }
            }
            cout << "\n";
            return;
        }

        pair<int,int> blank = findBlank(cur.state);
        int x = blank.first, y = blank.second;
        for(int k=0;k<4;k++) {
            int nx=x+moves[k].first, ny=y+moves[k].second;
            if(nx>=0 && ny>=0 && nx<3 && ny<3) {
                auto newState = cur.state;
                swap(newState[x][y], newState[nx][ny]);
                string key = boardToString(newState);
                if(!visited.count(key)) {
                    visited.insert(key);
                    q.push({newState, cur.path+moveChar[k]});
                }
            }
        }
    }
    cout << "No solution found.\n";
}

bool DFSUtil(vector<vector<int>> state, unordered_set<string> &visited, int depth, int limit, string path) {
    if(state == goal) {
        cout << "DFS Found Solution at depth " << depth << "!\n";
        cout << "Path: " << path << "\n";
        cout << "Moves: " << path.size() << "\n";
        cout << "Solution Path: ";
        for(char c : path) {
            switch(c) {
                case 'U': cout << "Up "; break;
                case 'D': cout << "Down "; break;
                case 'L': cout << "Left "; break;
                case 'R': cout << "Right "; break;
            }
        }
        cout << "\n";
        return true;
    }
    if(depth >= limit) return false;

    pair<int,int> blank = findBlank(state);
    int x = blank.first, y = blank.second;

    for(int k=0; k<4; k++) {
        int nx=x+moves[k].first, ny=y+moves[k].second;
        if(nx>=0 && ny>=0 && nx<3 && ny<3) {
            auto newState = state;
            swap(newState[x][y], newState[nx][ny]);
            string key = boardToString(newState);
            if(!visited.count(key)) {
                visited.insert(key);
                if(DFSUtil(newState, visited, depth+1, limit, path+moveChar[k]))
                    return true;
                visited.erase(key); // Backtrack for DFS
            }
        }
    }
    return false;
}

void DFS(vector<vector<int>> start, int depthLimit) {
    cout << "\n=== Running DFS Algorithm ===\n";
    printBoard(start);
    
    unordered_set<string> visited;
    visited.insert(boardToString(start));

    if(!DFSUtil(start, visited, 0, depthLimit, "")) {
        cout << "No solution found within depth limit " << depthLimit << ".\n";
    }
}

vector<vector<int>> getCustomInput() {
    vector<vector<int>> board(3, vector<int>(3));
    cout << "\nEnter the 3x3 board (use 0 for blank space):\n";
    cout << "Enter row by row (9 numbers total, 0-8):\n";
    
    for(int i=0; i<3; i++) {
        cout << "Row " << (i+1) << ": ";
        for(int j=0; j<3; j++) {
            cin >> board[i][j];
        }
    }
    return board;
}

void displayMenu() {
    cout << "\n========================================\n";
    cout << "         8-PUZZLE SOLVER MENU\n";
    cout << "========================================\n";
    cout << "1. Solve using BFS (Breadth-First Search)\n";
    cout << "2. Solve using DFS (Depth-First Search)\n";
    cout << "3. Use custom puzzle input\n";
    cout << "4. Show current puzzle\n";
    cout << "5. Reset to default puzzle\n";
    cout << "6. Exit\n";
    cout << "========================================\n";
    cout << "Enter your choice (1-6): ";
}

int main() {
    vector<vector<int>> currentPuzzle = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 7, 8}
    };
    
    int choice;
    int dfsDepthLimit = 20;
    
    cout << "Welcome to 8-Puzzle Solver!\n";
    cout << "Goal State:\n";
    printBoard(goal);
    
    while(true) {
        displayMenu();
        cin >> choice;
        
        switch(choice) {
            case 1:
                BFS(currentPuzzle);
                break;
                
            case 2:
                cout << "Enter depth limit for DFS (default 20): ";
                cin >> dfsDepthLimit;
                DFS(currentPuzzle, dfsDepthLimit);
                break;
                
            case 3:
                currentPuzzle = getCustomInput();
                cout << "Custom puzzle set successfully!\n";
                printBoard(currentPuzzle);
                break;
                
            case 4:
                cout << "Current Puzzle:\n";
                printBoard(currentPuzzle);
                break;
                
            case 5:
                currentPuzzle = {
                    {1, 2, 3},
                    {4, 5, 6},
                    {0, 7, 8}
                };
                cout << "Puzzle reset to default!\n";
                printBoard(currentPuzzle);
                break;
                
            case 6:
                cout << "Thank you for using 8-Puzzle Solver!\n";
                return 0;
                
            default:
                cout << "Invalid choice! Please enter 1-6.\n";
                break;
        }
        
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
    
    return 0;
}