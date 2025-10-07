#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;
map<string, string> husband;
map<string, string> wife;
map<string, vector<string>> siblings;
void addMarriage(string h, string w) {
    husband[h] = w;
    wife[w] = h;
}

void addSibling(string a, string b) {
    siblings[a].push_back(b);
    siblings[b].push_back(a);
}
bool isHusband(string h, string w) {
    return husband[h] == w;
}

bool isWife(string w, string h) {
    return wife[w] == h;
}

bool isSibling(string a, string b) {
    if (a == b) return false;
    for (string sib : siblings[a]) {
        if (sib == b) return true;
    }
    return false;
}

bool isUncle(string u, string n) {
    // If u is brother of n's parent (husband case)
    for (auto &entry : husband) {
        string father = entry.first;
        string mother = entry.second;
        if (isSibling(u, father)) return true;
    }
    return false;
}

bool isAunt(string a, string n) {
    // If a is sister of n's parent (wife case)
    for (auto &entry : wife) {
        string mother = entry.first;
        string father = entry.second;
        if (isSibling(a, mother)) return true;
    }
    return false;
}

bool isCousin(string a, string b) {
    // Cousins if their parents are siblings
    for (auto &entry1 : husband) {
        string parent1 = entry1.first;
        for (auto &entry2 : husband) {
            string parent2 = entry2.first;
            if (isSibling(parent1, parent2)) return true;
        }
    }
    return false;
}

int main() {
    addMarriage("Ramesh", "Sunita");
    addMarriage("Mahesh", "Kavita");

    addSibling("Ramesh", "Mahesh");  

    addSibling("Anita", "Sunita");   
  cout << "Is Ramesh husband of Sunita? " << (isHusband("Ramesh", "Sunita") ? "Yes" : "No") << endl;
cout << "Is Sunita wife of Ramesh? " << (isWife("Sunita", "Ramesh") ? "Yes" : "No") << endl;
cout << "Are Ramesh and Mahesh siblings? " << (isSibling("Ramesh", "Mahesh") ? "Yes" : "No") << endl;
cout << "Is Ramesh uncle of Kavita? " << (isUncle("Ramesh", "Kavita") ? "Yes" : "No") << endl;
cout << "Is Sunita aunt of Kavita? " << (isAunt("Sunita", "Kavita") ? "Yes" : "No") << endl;
cout << "Are Ramesh's child and Mahesh's child cousins? " 
     << (isCousin("Child1", "Child2") ? "Yes" : "No") << endl;


    return 0;
}