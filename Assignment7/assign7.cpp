#include <bits/stdc++.h>
using namespace std;

// Rule structure
struct Rule {
    vector<string> premises;  
    string conclusion;       
};

// Check if all premises are in the set of known facts
bool canFire(const Rule &rule, const set<string> &facts) {
    for (string p : rule.premises)
        if (facts.find(p) == facts.end())
            return false;
    return true;
}

// Forward Chaining Algorithm
void forwardChaining(vector<Rule> &rules, set<string> &facts, string goal) {
    bool addedNewFact;
    do {
        addedNewFact = false;
        for (auto &rule : rules) {
            if (canFire(rule, facts) && facts.find(rule.conclusion) == facts.end()) {
                facts.insert(rule.conclusion);
                cout << "Inferred: " << rule.conclusion << endl;
                addedNewFact = true;
                if (rule.conclusion == goal) {
                    cout << "Goal '" << goal << "' reached!" << endl;
                    return;
                }
            }
        }
    } while (addedNewFact);
    cout << "Goal '" << goal << "' not reached." << endl;
}

int main() {
    // --- Facts ---
    set<string> facts = {"fever", "cough"};

    // --- Rules ---
    vector<Rule> rules = {
        {{"fever", "cough"}, "flu"},
        {{"flu", "sore_throat"}, "infection"},
        {{"fever"}, "infection"}
    };

    string goal = "infection";

    forwardChaining(rules, facts, goal);

    cout << "\nFinal Facts: ";
    for (auto f : facts) cout << f << " ";
    cout << endl;

    return 0;
}
