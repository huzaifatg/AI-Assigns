#include <bits/stdc++.h>
using namespace std;
struct Rule {
    string conclusion;
    vector<string> premises;
};

bool backwardChaining(const string &goal, const set<string> &facts, vector<Rule> &rules, set<string> &visited) {
    if (visited.find(goal) != visited.end()) return false;
    visited.insert(goal);
    if (facts.find(goal) != facts.end()) {
        cout << "Fact '" << goal << "' is known." << endl;
        return true;
    }
    for (auto &rule : rules) {
        if (rule.conclusion == goal) {
            bool allPremisesTrue = true;
            for (auto &p : rule.premises) {
                if (!backwardChaining(p, facts, rules, visited)) {
                    allPremisesTrue = false;
                    break;
                }
            }
            if (allPremisesTrue) {
                cout << "Goal '" << goal << "' inferred using rule." << endl;
                return true;
            }
        }
    }

    return false;
}

int main() {
    // --- Known Facts ---
    set<string> facts = {"fever", "cough"};
    vector<Rule> rules = {
        {"flu", {"fever", "cough"}},
        {"infection", {"flu", "sore_throat"}},
        {"infection", {"fever"}}
    };

    string goal = "infection";
    set<string> visited;

    if (backwardChaining(goal, facts, rules, visited))
        cout << "Goal '" << goal << "' is achievable from facts." << endl;
    else
        cout << "Goal '" << goal << "' cannot be achieved from facts." << endl;

    return 0;
}