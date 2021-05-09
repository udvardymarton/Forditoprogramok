#include <iostream>
#include <vector>
#include <string>
using namespace std;

void welcome();
vector<char> tableElementsLeft(vector<string> valueLeft);
int returnWithASCIIValue(char letter);
void firstMove(vector<string> rulesLeft, vector<string> rulesRight, vector<string> taskVector);
void start(vector<string> rulesLeft, vector<string> rulesRight, char condition, int position, vector<string> solution, vector<string> alternatives);

int main() {
    cout << "Az Alulról felfelé haladó elemzések algoritmus megvalósítása\n";
    cout << "Kérem add meg a szabályokat!\nA szabályok alakja a következő: A->aS\nHa több szabály is van, akkor enterrel válaszd el őket!\n";
    cout << "Az összes szabály megadása után az end kulcsszót várom!\n";
    welcome();
}

void welcome() {
    string rules;
    string task;
    int counter = 0;
    vector<string> taskVector;
    vector<string> rulesLeft;
    vector<string> rulesRight;
    vector<char> elementsLeft;
    vector<int> elementsLeftIndex;
    vector<string> newRulesLeft;

    while(rules != "end") {
        string s = rules;
        string delimiter = "->";

        size_t pos = 0;
        string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            s.erase(0, pos + delimiter.length());
            rulesLeft.push_back(token);
            rulesRight.push_back(s);
        }
        cin >> rules;
    }
    // előfordulások száma
    elementsLeft = tableElementsLeft(rulesLeft);
    for (int k = 0; k < elementsLeft.size(); k++) { 
        for (int b = 0; b < rulesLeft.size(); b++) {
            if (elementsLeft[k] == rulesLeft[b][0]) {
                counter++;
            }
        }
        elementsLeftIndex.push_back(counter);
        counter = 0;
    }
    cout << "\nKöszönöm!\n";
    cout << "\nKérem a megoldandó feladatot!\n";
    cin >> task;
    for (int l = 0; l < task.size();l++) {
        char asd = task[l];
        string value;
        value.push_back(asd);
        taskVector.push_back(value);
    }
    cout << "Ez van a bal oldalt: ";
    for (vector<string>::iterator i = rulesLeft.begin(); i < rulesLeft.end();++i) {
        cout << *i << " ";
    }
    cout << "\nEz van a jobb oldalt: ";
    for (vector<string>::iterator j = rulesRight.begin(); j < rulesRight.end();++j) {
        cout << *j << " ";
    }
    cout << "\nEz a megoldandó feladat: ";
    for (vector<string>::iterator k = taskVector.begin(); k < taskVector.end();++k) {
        cout << *k;
    }
    cout << "\n";

    for (int i = 0; i < elementsLeftIndex.size();i++) {
        string combined;
        cout << elementsLeft[i] << " alternatívái: ";
        for (int j = 0; j < elementsLeftIndex[i]; j++) {
            cout << elementsLeft[i] << j+1 << " = " << rulesRight[counter];
            counter++;
            cout << ". ";
            combined = elementsLeft[i] + to_string(j+1);
            newRulesLeft.push_back(combined);
        }
        cout << "\n"; 
    }
    firstMove(rulesLeft, rulesRight, taskVector);
}

void firstMove(vector<string> rulesLeft, vector<string> rulesRight, vector<string> taskVector) {
    cout << "\n\n";
    char condition = 'q';
    int position = 1;
    int counter = 0;
    vector<string> solution;
    vector<string> alternatives;
    solution.push_back("#");
    alternatives.push_back("#");

    cout << "Levezetés: \n\n";
    cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
    cout << "(kezdő)";
    cout << "\n";

    start(rulesLeft, rulesRight, condition, position, solution, alternatives);
}

void start(vector<string> rulesLeft, vector<string> rulesRight, char condition, int position, vector<string> solution, vector<string> alternatives) {
    int counter = 0;
    //1
    if (solution[0] == "#") {
        position = position + 1;
        solution.clear();
        solution.push_back(rulesRight[rulesRight.size() - 1]);
        alternatives.clear();
        alternatives.push_back("s");
        cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
        cout << "(léptetés)";
        cout << "\n";
    }

    //2
    if (solution[0].size() == 1) {
        for (int i = 0; i < rulesRight.size(); i++) {
            if (solution[0] == rulesRight[i]) {
                solution[0] = rulesLeft[i];
                alternatives[0].insert(alternatives[0].begin(), to_string(i+1)[0]);
                cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
                cout << "(redukálás)";
                cout << "\n";
                counter++;
            }
        }
        if (counter == 0) {
            position = position + 1;
            solution[0].push_back('+');
            alternatives[0].insert(alternatives[0].begin(), 's');
            cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
            cout << "(léptetés)";
            cout << "\n";
        }
    }

    //3
    else if (solution[0].size() > 1) {
        for (int i = 0; i < rulesRight.size(); i++) {
            if (solution[0] == rulesRight[i]) {
                solution[0] = rulesLeft[i];
                alternatives[0].insert(alternatives[0].begin(), to_string(i+1)[0]);
                cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
                cout << "(redukálás)";
                cout << "\n";
                break;
            }
            else if (solution[0][solution[0].size() - 1] == rulesRight[i][0]) {
                solution[0][solution[0].size() - 1] = rulesLeft[i][0];
                alternatives[0].insert(alternatives[0].begin(), to_string(i+1)[0]);
                cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
                cout << "(redukálás)";
                cout << "\n";
                break;
            }
            else if (i + 1 == rulesRight.size()) {
                position = position + 1;
                solution[0].push_back('a');
                alternatives[0].insert(alternatives[0].begin(), 's');
                cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
                cout << "(léptetés)";
                cout << "\n";
            }
        }
    }

    //4
    if (position == 4 && solution[0] == "S") {
        condition = 't';
        cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
        cout << "(elfogadás)";
        cout << "\n";
        cout << "vége";
        cout << "\n";
        exit(0);
    }

    start(rulesLeft, rulesRight, condition, position, solution, alternatives);

    
}

// ismétlések nélkül adja vissza a tábla bal oldali elemeit
vector<char> tableElementsLeft(vector<string> valueLeft) {
    vector<char> datas;
    for (int i = 0; i < valueLeft.size(); i++) {
        for (int j = 0; j < valueLeft[i].size(); j++) {
            if (returnWithASCIIValue(valueLeft[i][j]) >= 65 && returnWithASCIIValue(valueLeft[i][j]) <= 90) {
                if (datas.size() > 0) {
                    for (int k = 0; k < datas.size(); k++) {
                        if (datas[k] == valueLeft[i][j]) {
                            break;
                        }
                        else if (k + 1 == datas.size()) {
                            datas.push_back(valueLeft[i][j]);
                        }
                    }
                }
                else {
                    datas.push_back(valueLeft[i][j]);
                }
            }
        }
    }
    return datas;
}

int returnWithASCIIValue(char letter){
	int value = letter;
	return value;
}