#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> goal = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 0}
};

vector<pair<int,int>> moves = {{-1,0},{1,0},{0,-1},{0,1}};
string boardToString(vector<vector<int>> &board) {
    string s="";
    for(auto &row : board)
        for(int x : row) s += to_string(x);
    return s;
}
pair<int,int> findBlank(vector<vector<int>> &state) {
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(state[i][j]==0) return {i,j};
    return {-1,-1};
}
bool DFSUtil(vector<vector<int>> state, unordered_set<string> &visited, int depth, int limit) {
    if(state == goal) {
        cout << "Goal Found at depth " << depth << "!\n";
        return true;
    }
    if(depth >= limit) return false;

    pair<int,int> blank = findBlank(state);
    int x = blank.first, y = blank.second;

    for(auto &mv : moves) {
        int nx=x+mv.first, ny=y+mv.second;
        if(nx>=0 && ny>=0 && nx<3 && ny<3) {
            auto newState = state;
            swap(newState[x][y], newState[nx][ny]);
            string key = boardToString(newState);
            if(!visited.count(key)) {
                visited.insert(key);
                if(DFSUtil(newState, visited, depth+1, limit))
                    return true;
            }
        }
    }
    return false;
}
void DFS(vector<vector<int>> start, int depthLimit=20) {
    unordered_set<string> visited;
    visited.insert(boardToString(start));

    if(!DFSUtil(start, visited, 0, depthLimit)) {
        cout << "No solution found within depth limit " << depthLimit << ".\n";
    }
}

int main() {
    vector<vector<int>> start = {
        {1, 2, 3},
        {4, 5, 6},
        {0, 7, 8}
    };

    cout << "Running DFS...\n";
    DFS(start, 15); // depth limit 15
}
