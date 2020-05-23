#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include<Windows.h>
#include<stack>

using namespace std;

struct Rib {
public:
    int start;
    int end;
    int weight;
};

void initializeGraph(int &picks, int &ribs, vector<Rib> &structRibs);

void sortRibs(int &picks, int &ribs, vector<Rib> &structRibs);

bool hasUnmarkedPicks(vector<bool> &markedPicks);

int selectRib(vector<bool> &markedRibs, vector<bool> &markedPicks, vector<Rib> &structRibs);

vector<bool> primAlgorithm(int &picks, int &ribs, vector<Rib> &structRibs);

void printSpanningTree(vector<bool>markedRibs, vector<Rib>structRibs);

int main() {
    vector<Rib> ribsList;
    int n = 0, m = 0;
    initializeGraph(n, m, ribsList);
    sortRibs(n, m, ribsList);
    SetConsoleOutputCP(CP_UTF8);
    printSpanningTree(primAlgorithm(n,m,ribsList),ribsList);
    return 0;
}

void initializeGraph(int &picks, int &ribs, vector<Rib> &structRibs) {
    Rib myRib{};
    ifstream inFile;
    inFile.open("GraphWithScales.txt");

    if (!inFile.is_open()) cout << "It is not open" << endl;
    inFile >> picks >> ribs;

    for (int i = 0; i < ribs; i++) {
        inFile >> myRib.start >> myRib.end >> myRib.weight;

        structRibs.push_back(myRib);
    }
    inFile.close();
}

void sortRibs(int &picks, int &ribs, vector<Rib> &structRibs) {

    Rib tmp{};
    for (int i = 0; i < ribs - 1; i++) {
        for (int j = 0; j < ribs - 1; j++) {
            if ((structRibs[j].start + structRibs[j].end) > (structRibs[j + 1].start + structRibs[j + 1].end)) {

                tmp = structRibs[j];
                structRibs[j] = structRibs[j + 1];
                structRibs[j + 1] = tmp;

            }
        }
    }
}

vector<bool> primAlgorithm(int &picks, int &ribs, vector<Rib> &structRibs) {

    vector<bool> markedPicks(picks, false);
    vector<bool> markedRibs(ribs, false);
    vector<int> usingPicks;
    usingPicks.push_back(1);
    markedPicks[0]=true;

    while (hasUnmarkedPicks(markedPicks)) {
        int minWeightIndex =selectRib(markedRibs,markedPicks,structRibs);
        int pick=0;
        for (int i = 0; i < usingPicks.size(); i++) {

            for (int j = 0; j < structRibs.size(); j++) {

                if (structRibs[j].start == usingPicks[i] && markedPicks[structRibs[j].end - 1]==false) {
                    if (structRibs[j].weight <= structRibs[minWeightIndex].weight) {
                        minWeightIndex = j;
                        pick = structRibs[j].end;
                    }
                }

                if (structRibs[j].end == usingPicks[i] && markedPicks[structRibs[j].start - 1]==false) {
                    if (structRibs[j].weight <= structRibs[minWeightIndex].weight) {
                        minWeightIndex = j;
                        pick = structRibs[j].start;
                    }
                }

            }
        }
        usingPicks.push_back(pick);
        markedRibs[minWeightIndex] = true;
        markedPicks[pick - 1] = true;

    }
return markedRibs;
}

bool hasUnmarkedPicks(vector<bool> &markedPicks) {
    for (auto &&markedPick : markedPicks) {
        if (!markedPick)return true;
    }
    return false;
}

int selectRib(vector<bool> &markedRibs, vector<bool> &markedPicks, vector<Rib> &structRibs) {

    for (int i = 0; i < structRibs.size(); i++) {
        if (markedRibs[i]==false && markedPicks[structRibs[i].start - 1]==true && markedPicks[structRibs[i].end - 1]==false) return i;
        if (markedRibs[i]==false && markedPicks[structRibs[i].start - 1]==false && markedPicks[structRibs[i].end - 1]==true) return i;
    }

    return -1;
}

void printSpanningTree(vector<bool>markedRibs, vector<Rib>structRibs){
    cout<< "В мінімальне кістякове дерево входять такі ребра: \n";
    for(int i=0; i<structRibs.size(); i++){
        if(markedRibs[i]==true) cout<<"Ребро "<<structRibs[i].start<<" "<<structRibs[i].end<<" з вагою "<<structRibs[i].weight<<endl;
    }
}