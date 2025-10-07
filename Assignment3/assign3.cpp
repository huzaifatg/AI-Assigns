#include <bits/stdc++.h>
using namespace std;

struct Edge {
    string to;
    int cost;
};
unordered_map<string, int> heuristic = {
    {"Delhi", 300},
    {"Noida", 280},
    {"Chandigarh", 150},
    {"Ludhiana", 100},
    {"Amritsar", 50},
    {"Punjab", 0}
};
unordered_map<string, vector<Edge>> graph = {
    {"Delhi", {{"Noida", 30}, {"Chandigarh", 250}}},
    {"Noida", {{"Chandigarh", 220}}},
    {"Chandigarh", {{"Ludhiana", 100}, {"Amritsar", 200}}},
    {"Ludhiana", {{"Punjab", 80}}},
    {"Amritsar", {{"Punjab", 50}}},
    {"Punjab", {}}
};

struct Node {
    string name;
    int g, f;
    bool operator>(const Node& other) const {
        return f > other.f;
    }
};

vector<string> aStar(string start, string goal) {
    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_map<string, int> gScore;
    unordered_map<string, string> parent;
    unordered_set<string> closed;

    gScore[start] = 0;
    openList.push({start, 0, heuristic[start]});

    while (!openList.empty()) {
        Node current = openList.top();
        openList.pop();

        if (current.name == goal) {
            vector<string> path;
            string node = goal;
            while (!node.empty()) {
                path.push_back(node);
                node = parent[node];
            }
            reverse(path.begin(), path.end());
            cout << "Total cost = " << gScore[goal] << " km\n";
            return path;
        }

        if (closed.count(current.name)) continue;
        closed.insert(current.name);

        for (auto& edge : graph[current.name]) {
            int tentative_g = gScore[current.name] + edge.cost;
            if (!gScore.count(edge.to) || tentative_g < gScore[edge.to]) {
                gScore[edge.to] = tentative_g;
                parent[edge.to] = current.name;
                int f = tentative_g + heuristic[edge.to];
                openList.push({edge.to, tentative_g, f});
            }
        }
    }
    return {};
}

int main() {
    string start = "Delhi";
    string goal = "Punjab";
    vector<string> path = aStar(start, goal);

    if (!path.empty()) {
        cout << "Optimal Path: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "No path found.\n";
    }
    return 0;
}
