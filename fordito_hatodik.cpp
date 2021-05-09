#include <iostream>
#include <vector>
using namespace std;

void welcome();
vector<char> tableElementsLeft(vector<string> valueLeft);
void firstMove(vector<string> newRulesLeft, vector<string> rulesLeft, vector<string> rulesRight, vector<string> taskVector);
void start(vector<string> newRulesLeft, vector<string> rulesRight, vector<string> taskVector, char condition, int position, vector<string> solution, vector<string> alternatives,int counter);
int returnWithASCIIValue(char letter);

int main() {
    cout << "A Felülről-lefelé haladó elemzések algoritmus megvalósítása\n";
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
    firstMove(newRulesLeft, rulesLeft, rulesRight, taskVector);
}


void firstMove(vector<string> newRulesLeft, vector<string> rulesLeft, vector<string> rulesRight, vector<string> taskVector) {
    cout << "\n\n";
    char condition = 'q';
    int position = 1;
    int counter = 0;
    vector<string> solution;
    vector<string> alternatives;
    solution.push_back("#");
    alternatives.push_back(rulesLeft[0]);

    cout << "Levezetés: \n\n";
    cout << "(" << condition << "," << position << "," << solution[0] << "," << alternatives[0] << ")" << "\t";
    cout << "(kezdő)";
    cout << "\n";

    start(newRulesLeft,rulesRight,taskVector,condition,position,solution,alternatives,counter);
}

void start(vector<string> newRulesLeft, vector<string> rulesRight, vector<string> taskVector, char condition, int position, vector<string> solution, vector<string> alternatives, int counter) {
    vector<string> vectorOfSLeft;
    vector<string> vectorOfSRight;
    vector<string> vectorOfTLeft;
    vector<string> vectorOfTRight;
    string solutionPrint;
    string alternativesPrint;
    string valami;
    int storeSolutionPos = 0;

    // felosztom két külön vectorra, a könnyebb számolás érdekében.
    for (int i = 0; i < rulesRight.size() / 2; i++) {
       vectorOfSLeft.push_back(newRulesLeft[i]);
       vectorOfSRight.push_back(rulesRight[i]);
    }
    for (int j = rulesRight.size() / 2; j < rulesRight.size(); j++) {
        vectorOfTLeft.push_back(newRulesLeft[j]);
        vectorOfTRight.push_back(rulesRight[j]);
    }
    //1
    if (alternatives[0] == "S") {
        if (solution[0] == "#") {
            solution.clear();
        }
        solution.push_back(vectorOfSLeft[0]);
        alternatives.clear();
        alternatives.push_back(vectorOfSRight[0]);
        solutionPrint = "";
        for (int i = 0; i < solution.size(); i++) {
            solutionPrint = solutionPrint + solution[i]; 
        }
        alternativesPrint = "";
        for (int j = 0; j < alternatives.size(); j++) {
            alternativesPrint = alternativesPrint + alternatives[j];
        }
        cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
        cout << "(S kiterjesztése)";
        cout << "\n";
    }

    //2
    else if (alternatives[0] == "a") {
        position = position + 1;
        solution.push_back(alternatives[0]);
        alternatives[0] = "#";
        solutionPrint = "";
        for (int i = 0; i < solution.size(); i++) {
            solutionPrint = solutionPrint + solution[i]; 
        }
        alternativesPrint = "";
        for (int j = 0; j < alternatives.size(); j++) {
            alternativesPrint = alternativesPrint + alternatives[j];
        }
        cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
        cout << "(sikeres input illesztés)";
        cout << "\n";
        
        condition = 't';
        cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
        cout << "(sikeres elemzés!)";
        cout << "\n";
        exit(0);
    }

    //3
    else if(alternatives[0][0] == 'T') {
        if (counter == 4 && alternatives[0] != "T") {
            condition = 'q';
            solution.pop_back();
            solution.push_back(vectorOfSLeft[1]);
            alternatives[0] = vectorOfSRight[1];
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(backtrack a kiterjesztésben)";
            cout << "\n";
        }
        else if (counter == 4 && alternatives[0] == "T") {
            solution.push_back(vectorOfTLeft[0]);
            alternatives[0] = vectorOfTRight[0];
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(T kiterjesztése)";
            cout << "\n";

        }
        else {
            solution.push_back(vectorOfTLeft[0]);
            alternatives[0][0] = vectorOfTRight[0][0];
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(T kiterjesztése)";
            cout << "\n";
        }
    }

    //4
    else if (counter == 4) {
        if (alternatives[0][0] == vectorOfTRight[0][0]) {
            condition = 'q';
            solution.pop_back();
            solution.push_back(vectorOfTLeft[1]);
            alternatives[0][0] = vectorOfTRight[1][0];
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(backtrack a kiterjesztésben)";
            cout << "\n";
            }
        else if (alternatives[0][0] == vectorOfTRight[1][0]) {
            condition = 'b';
            solution.pop_back();
            alternatives[0] = vectorOfSRight[0];
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(backtrack a kiterjesztésben)";
            cout << "\n";
        }
    }

    //5
    else if (position > 3) {
        if (condition == 'q') {
            condition = 'b';
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(sikertelen input illesztés)";
            cout << "\n";
        }
        else {
            condition = 'b';
            position = position - 1;
            valami = solution[solution.size() - 1];
            solution.pop_back();
            alternatives[0] = valami + alternatives[0];
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(backtrack az inputban)";
            cout << "\n";
            // itt lesz a counter 4.
            // erre azért van szükség, mert az első 3 értékét akkor kapja meg, ha megtalálta mind a 3 taskVectorban lévő elemet egyszer.
            // ezzel kerülöm ki azt, hogy végtelen ciklusba fusson a program.
            counter++;
        }
    }

    //6
    else if (alternatives[0][0] == taskVector[position - 1][0]) {
        position = position + 1;
        solution.push_back(string(1,alternatives[0][0]));
        alternatives[0] = alternatives[0].substr(1, alternatives[0].size() - 1);
        solutionPrint = "";
        for (int i = 0; i < solution.size(); i++) {
            solutionPrint = solutionPrint + solution[i]; 
        }
        alternativesPrint = "";
        for (int j = 0; j < alternatives.size(); j++) {
            alternativesPrint = alternativesPrint + alternatives[j];
        }
        cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
        counter++;
        cout << "(sikeres input illeszkedés)";
        cout << "\n";
    }

    //7
    else if (alternatives[0][0] != taskVector[position - 1][0] && alternatives[0][0] == vectorOfTRight[0][0] || alternatives[0][0] == vectorOfTRight[1][0]) {
        if (alternatives[0][0] == vectorOfTRight[0][0] && condition == 'q') {
            condition = 'b';
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(sikertelen input illesztés)";
            cout << "\n";
        }
        else {
            condition = 'q';
            alternatives[0][0] = vectorOfTRight[1][0];
            solution.pop_back();
            solution.push_back(vectorOfTLeft[1]);
            solutionPrint = "";
            for (int i = 0; i < solution.size(); i++) {
                solutionPrint = solutionPrint + solution[i]; 
            }
            alternativesPrint = "";
            for (int j = 0; j < alternatives.size(); j++) {
                alternativesPrint = alternativesPrint + alternatives[j];
            }
            cout << "(" << condition << "," << position << "," << solutionPrint << "," << alternativesPrint << ")" << "\t";
            cout << "(backtrack a kiterjesztésben)";
            cout << "\n";
        }
    }

    //8
    else {
        cout << "Program vége!";
        cout << "\n";
        exit(0);
    }

    start(newRulesLeft,rulesRight,taskVector,condition,position,solution,alternatives,counter);
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