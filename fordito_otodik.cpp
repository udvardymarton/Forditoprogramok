#include <iostream>
#include <vector>
using namespace std;

void welcome();
void tableWithHValues(vector<string> rulesLeft, vector<string> rulesRight);
void tableWithHValuesOtherRows(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[5][5], int value);
int checkNonTerminalValueInColumns(vector<string> rulesLeft, string value);
void tableWithHValuesFollow(vector<string> rulesLeft, vector<string> rulesRight, vector<string> firstOne);
void tableWithHValuesOtherRowsFollow(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[5][5], int value);
vector<string> tableElementsLeft(vector<string> valueLeft);
vector<char> tableElementsRight(vector<string> valueRight);
int returnWithASCIIValue(char letter);
string filterTerminal(string value);

int main() {
    cout << "Az ÁLL(1) algoritmus megvalósítása\n";
    cout << "Kérem add meg a szabályokat!\nA szabályok alakja a következő: A->aS\nHa több szabály is van, akkor enterrel válaszd el őket!\n";
    welcome();
}

void welcome() {
    string rules;
    vector<string> rulesLeft;
    vector<string> rulesRight;

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
    cout << "\nKöszönöm!\n";
    cout << "Ez van a bal oldalt: ";
    for (vector<string>::iterator i = rulesLeft.begin(); i < rulesLeft.end();++i) {
        cout << *i << " ";
    }
    cout << "\nEz van a jobb oldalt: ";
    for (vector<string>::iterator j = rulesRight.begin(); j < rulesRight.end();++j) {
        cout << *j << " ";
    }
    cout << endl;
    tableWithHValues(rulesLeft, rulesRight);
}

void tableWithHValues(vector<string> rulesLeft, vector<string> rulesRight) {
    vector<string> elementsLeft; //bal oldali elemek szűrve.
    vector<string> storage;
    vector<string> firstRowStorage;
    string myContainer[5][5];
    int value = 1;
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);
    string mixed;
    int counter = 0;
    elementsLeft = tableElementsLeft(rulesLeft);

    cout << "Ez a táblázat: " << "\n\n";
    cout << "\t";
    for (int i = 0; i < elementsLeft.size(); i++) {
        cout << elementsLeft[i] << "\t";
    }
    cout << "\n\n";
    cout << "H0";
    cout << "\t";
    for (int i = 0; i < elementsLeft.size(); i++) {
        for (int j = 0; j < rulesLeft.size(); j++) {
            if (elementsLeft[i] == rulesLeft[j]) {
                storage.push_back(rulesRight[j]);
            }
        }
        for (int k = 0; k < storage.size(); k++) {
            if (returnWithASCIIValue(storage[k][0]) < 65 || returnWithASCIIValue(storage[k][0]) >= 97 && returnWithASCIIValue(storage[k][0]) <= 122) {
                mixed = mixed + storage[k][0];
            }
            else {
                mixed = mixed + "-";
            }
        }
        myContainer[0][i] = mixed;
        mixed = "";
        storage.clear();
    }

    for (int i = 0; i < size; i++) {
        cout << myContainer[0][i] << "\t";
    }
    cout << "\n\n";
    tableWithHValuesOtherRows(rulesLeft, rulesRight, myContainer, value);
}

void tableWithHValuesOtherRows(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[5][5], int value) {
    int counter = 0; //folyamatosan lépked a szabály jobb oldalán.
    int position = 0;
    string mixed = "";
    vector<string> isItEqual;
    vector<string> firstOne;
    vector<string> elementsLeft;
    elementsLeft = tableElementsLeft(rulesLeft);
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);

    for (int i = 0; i < elementsLeft.size(); i++) {
        for (int j = 0; j < rulesLeft.size(); j++) {
            if (elementsLeft[i] == rulesLeft[j]) {
                if (returnWithASCIIValue(rulesRight[j][0]) >= 65 && returnWithASCIIValue(rulesRight[j][0]) <= 90) {
                    position = checkNonTerminalValueInColumns(rulesLeft,string(1,rulesRight[j][0]));
                    myContainer[value][i] = myContainer[value - 1][position];
                }
                else {
                    myContainer[value][i] = myContainer[value - 1][i];
                }
            }
        }
    }

        for (int p = 0; p < size; p++) {
            if (myContainer[value][p] == myContainer[value - 1][p]) {
                isItEqual.push_back("x");
            }
        }

        cout << "H" << value;
        cout << "\t";
        for (int k = 0; k < size; k++) {
            cout << myContainer[value][k] << "\t";
        }
        cout << "\n\n";
        if (isItEqual.size() == 5) {
            cout << "FIRST1" << "\t";
            for (int k = 0; k < size; k++) {
                cout << myContainer[value][k] << "\t";
                firstOne.push_back(myContainer[value][k]);
            }
            cout << "\n\n";
            tableWithHValuesFollow(rulesLeft,rulesRight,firstOne);
        }
        value++;
        if (isItEqual.size() != 5) {
            tableWithHValuesOtherRows(rulesLeft,rulesRight,myContainer, value);
        }
}

void tableWithHValuesFollow(vector<string> rulesLeft, vector<string> rulesRight, vector<string> firstOne) {
    vector<string> elementsLeft; //bal oldali elemek szűrve.
    vector<string> storage;
    vector<string> firstRowStorage;
    string myContainer[5][5];
    int value = 1;
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);
    string mixed;
    int counter = 0;
    elementsLeft = tableElementsLeft(rulesLeft);

    for (int i = 0; i < elementsLeft.size(); i++) {
        if (i == 0) {
            myContainer[0][i] = "#";
        }
        // else {
        //     myContainer[0][i] = "-";
        // }
    }
    tableWithHValuesOtherRowsFollow(rulesLeft,rulesRight, myContainer, value);
}

void tableWithHValuesOtherRowsFollow(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[5][5], int value){
    int counter = 0;
    int position = 0;
    string mixed = "";
    string combined = "";
    vector<string> isItEqual;
    vector<string> firstOne;
    vector<string> elementsLeft;
    elementsLeft = tableElementsLeft(rulesLeft);
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);

    for (int i = 0; i < elementsLeft.size(); i++) {
        for (int j = 0; j < rulesRight.size(); j++) {
            for (int k = 0; k < rulesRight[j].size(); k++) {
                    combined = string(1,rulesRight[j][k]) + string(1,rulesRight[j][k+1]);
                    if (elementsLeft[i] == combined) {
                        mixed = mixed + "#" + myContainer[value - 1][i - 1];
                    }
                    else if (elementsLeft[i] == string(1,rulesRight[j][k])) {
                        if (returnWithASCIIValue(rulesRight[j][k+1]) < 65 && returnWithASCIIValue(rulesRight[j][k+1]) != 39) {
                            mixed = mixed + rulesRight[j][k+1];
                        }
                        else {
                            mixed = mixed + myContainer[value][i-1];
                            if (returnWithASCIIValue(rulesRight[j][0]) < 65) {
                                if (i == 4 || returnWithASCIIValue(rulesRight[j][0]) != 42) {
                                    mixed = mixed + rulesRight[j][0];
                                }
                            }
                        }
                    }
            }
        }
        if (i == 0) {
            mixed = mixed + myContainer[0][0];
        }
        myContainer[value][i] = filterTerminal(mixed);
        mixed = "";
    }

    value++;
    if (value < 4) {
        tableWithHValuesOtherRowsFollow(rulesLeft,rulesRight,myContainer,value);
    }
    if (value == 4) {
        cout << "Második táblázat: " << "\n\n";
        cout << " \t";
        for (int i = 0; i < elementsLeft.size(); i++) {
        cout << elementsLeft[i] << "\t";
        }
        cout << "\n\n";
        for (int i = 0; i < value; i++) {
            cout << "H'" << i << "\t";
            for (int j = 0; j < 5; j++) {
                cout << myContainer[i][j] << "\t";
            }
            cout << "\n\n";
        }
        cout << "FOLLOW1" << "\t";
        for (int k = 0; k < 5; k++) {
            cout << myContainer[value - 1][k] << "\t";
        }
        cout << "\n\n";

    }
}

// ismétlések nélkül adja vissza a tábla bal oldali elemeit
vector<string> tableElementsLeft(vector<string> valueLeft) {
    vector<string> datas;
    string combined;
    for (int i = 0; i < valueLeft.size(); i++) {
        if (datas.size() > 0) {
            for (int k = 0; k < datas.size(); k++) {
                if (datas[k] == valueLeft[i]) {
                    break;
                }
                else if (k + 1 == datas.size()) {
                    datas.push_back(valueLeft[i]);
                }
            }
        }
        else {
            datas.push_back(valueLeft[i]);
        }
    }
    return datas;
}

// megkeresi, hogy hol fordul elő a szabály bal oldalában a beadott betű (value)
int checkNonTerminalValueInColumns(vector<string> rulesLeft, string value) {
    vector<string> elementsLeft;
    int columnNumber = 0;
    elementsLeft = tableElementsLeft(rulesLeft);

    for (int i = 0; i < elementsLeft.size(); i++) {
        if (value == elementsLeft[i]) {
            columnNumber = i;
        }
    }

    return columnNumber;
}

// kiszűri az ismétlődéseket
string filterTerminal(string value) {
    string newWord = "";
    vector<int> counter;
    for (int i = 0; i < value.size(); i++) {
        if (newWord.size() == 0) {
            newWord = newWord + value[i];
        }
        else {
            for (int j = 0; j < newWord.size(); j++) {
                if (newWord[j] == value[i]) {
                    counter.push_back(j);
                }
            }
            if (counter.size() == 0) {
                newWord = newWord + value[i];
            }
            counter.clear();
        }
    }
    return newWord;
}

int returnWithASCIIValue(char letter){
	int value = letter;
	return value;
}