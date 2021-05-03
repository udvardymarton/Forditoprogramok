#include <iostream>
#include <vector>
using namespace std;

void welcome();
void tableWithHValues(vector<string> rulesLeft, vector<string> rulesRight);
void tableWithHValuesOtherRows(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[5][5], vector<int> elementsLeftIndex, int value);
void secondTableWithOtherValues(vector<string> rulesLeft, vector<string> rulesRight, vector<string> firstOne, vector<int> elementsLeftIndex);
void filterOtherTable(vector<string> rulesLeft,vector<string> rulesRight, vector<string> firstOne, vector<int> elementsLeftIndex);
void filterThirdTable(vector<string> rulesLeft,vector<string> rulesRight,string myContainer[5][5], vector<string> firstOne, vector<int> elementsLeftIndex, int value);
int returnWithASCIIValue(char letter);
int checkNonTerminalValueInColumns(vector<string> rulesLeft, char value);
string filterTerminal(string value);
int checkTerminalValueInColumns(vector<char> elementsRight, char value);
vector<char> tableElementsLeft(vector<string> valueRight);
vector<char> tableElementsRight(vector<string> valueRight);

int main() {
    cout << "A LLL(1) algoritmus megvalósítása\n";
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

// legelső táblázat megvalósítása
void tableWithHValues(vector<string> rulesLeft, vector<string> rulesRight) {
    vector<char> elementsLeft; //bal oldali elemek szűrve.
    vector<int> elementsLeftIndex; //nagybetűk előfordulásainak száma.
    vector<string> firstRowStorage;
    string myContainer[5][5];
    int value = 1;
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);
    string mixed;
    int counter = 0;
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

    cout << "Ez a táblázat: " << "\n\n";
    cout << "\t";
    for (vector<char>::iterator j = elementsLeft.begin(); j < elementsLeft.end();++j) {
        cout << *j << "\t";
    }
    cout << "\n\n";
    cout << "H0";
    cout << "\t";
    for (int i = 0; i < elementsLeft.size(); i++) {
        for (int p = 0; p < elementsLeftIndex[i]; p++) {
            if (returnWithASCIIValue(rulesRight[counter][0]) >= 97 && returnWithASCIIValue(rulesRight[counter][0]) <= 122) {
                if (mixed == "-") {
                    mixed = "";
                }
                mixed = mixed + rulesRight[counter][0];
            }
            else if (returnWithASCIIValue(rulesRight[counter][0]) >= 65 && returnWithASCIIValue(rulesRight[counter][0]) <= 90 && mixed == "") {
                mixed = mixed + "-";
            }
            counter++;
        }
        myContainer[0][i] = mixed;
        mixed = "";
    }

    for (int j = 0; j < size; j++) {
        cout << myContainer[0][j] << "\t";
    }
    cout << "\n\n";
    tableWithHValuesOtherRows(rulesLeft,rulesRight,myContainer, elementsLeftIndex, value);
}

//összes többi sor megvalósítása
void tableWithHValuesOtherRows(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[5][5], vector<int> elementsLeftIndex, int value) {
    int counter = 0; //folyamatosan lépked a szabály jobb oldalán.
    int position = 0;
    string mixed = "";
    vector<string> isItEqual;
    vector<string> firstOne;
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < elementsLeftIndex[i]; j++) {
                if (returnWithASCIIValue(rulesRight[counter][0]) >= 65 && returnWithASCIIValue(rulesRight[counter][0]) <= 90) {
                    position = checkNonTerminalValueInColumns(rulesLeft, rulesRight[counter][0]);
                    if (myContainer[value - 1][i] != "-") { 
                        mixed = mixed + myContainer[value - 1][i] + myContainer[value - 1][position]; // majd ahol előfordult, ahanyadik helyről kiveszi a value - 1 sorból az elemet
                    }
                    else {
                        mixed = mixed + myContainer[value - 1][position];
                    }
                }
                else {
                    mixed = mixed + myContainer[value - 1][i];
                }
                counter++;
            }
            myContainer[value][i] = filterTerminal(mixed);
            mixed = "";
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
            secondTableWithOtherValues(rulesLeft, rulesRight, firstOne, elementsLeftIndex);
        }
        value++;
        if (isItEqual.size() != 5) {
            tableWithHValuesOtherRows(rulesLeft,rulesRight,myContainer, elementsLeftIndex, value);
        }
}

// második táblázat legfelső sorának kiíratása, majd a táblázatot létrehozó függvény meghívása.
void secondTableWithOtherValues(vector<string> rulesLeft, vector<string> rulesRight, vector<string> firstOne, vector<int> elementsLeftIndex) {
    string myContainer[5][5];
    int value = 0;
    // first row
    for (int k = 0; k < 5; k++) {
        if (k == 0) {
            myContainer[0][k] = "#";
        }
        else if (k > 0) {
            myContainer[0][k] = "-";
        }
    }
    cout << "Második táblázat: " << "\n\n";
    vector<char> elementsRight;
    elementsRight = tableElementsRight(rulesRight);
    cout << " \t";
    for (int j = 0; j < elementsRight.size(); j++) {
        cout << elementsRight[j] << "\t";
    }
    cout << "\n\n";
    value++;
    filterOtherTable(rulesLeft,rulesRight,firstOne,elementsLeftIndex);
    filterThirdTable(rulesLeft,rulesRight,myContainer,firstOne,elementsLeftIndex,value);
}

// tábla létrehozás
void filterOtherTable(vector<string> rulesLeft,vector<string> rulesRight, vector<string> firstOne, vector<int> elementsLeftIndex) {
    int counter = 0;
    int anotherCounter = 0;
    int position = 0;
    int position2 = 0;
    int size = 0;
    string myContainer[11][6];
    int myContainerSizeColumn = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);
    int myContainerSizeRow = sizeof(myContainer) / sizeof(myContainer[0]);
    vector<char> elementsRight;
    vector<char> elementsLeft;
    vector<char> elementsLeftOther;
    elementsRight = tableElementsRight(rulesRight);
    elementsLeft = tableElementsLeft(rulesLeft);
    elementsLeftOther = tableElementsLeft(rulesLeft);
    for (int i = 0; i < elementsRight.size(); i++) {
        elementsLeftOther.push_back(elementsRight[i]);
    }

    for (int i = 0; i < elementsLeft.size(); i++) {
        for (int j = 0; j < elementsLeftIndex[i]; j++) {
            if (returnWithASCIIValue(rulesRight[counter][0]) >= 65 && returnWithASCIIValue(rulesRight[counter][0]) <= 90) {
                position = checkNonTerminalValueInColumns(rulesLeft,rulesRight[counter][0]);
                if (firstOne[position].size() == elementsRight.size() - 1) {
                    for (int k = 0; k < elementsLeft.size(); k++) {
                        anotherCounter = counter + 1;
                        myContainer[i][k] = "(" + rulesRight[counter] + "," + std::to_string(anotherCounter) + ")";
                    }
                }
                else {
                    position = checkNonTerminalValueInColumns(rulesLeft,rulesRight[counter][0]);
                    size = firstOne[position].size();
                    for (int n = 0; n < size; n++) {
                       position2 = checkTerminalValueInColumns(elementsRight,firstOne[position][n]);
                       anotherCounter = counter + 1;
                       myContainer[i][position2] = "(" + rulesRight[counter] + "," + std::to_string(anotherCounter) + ")";
                    }
                }
            }
            else {
                position2 = checkTerminalValueInColumns(elementsRight,rulesRight[counter][0]); //megkeresem a kisbetű hanyadik elem a kisbetűk között
                anotherCounter = counter + 1;
                myContainer[i][position2] = "(" + rulesRight[counter] + "," + std::to_string(anotherCounter) + ")";
            }
            counter++;
        }
    }
    position = elementsLeft.size();
    for (int i = 0; i < elementsRight.size(); i++) {
        for (int j = 0; j < elementsRight.size(); j++) {
            if (elementsRight[i] == '#' && elementsRight[j] == '#') {
                myContainer[position][j] = "accept";
            }
            else if (elementsRight[i] == elementsRight[j]) {
                myContainer[position][j] = "pop";
            }
        }
        position++;
    }
    for (int i = 0; i < myContainerSizeRow; i++) {
        cout << elementsLeftOther[i] << "\t";
        for (int j = 0; j < myContainerSizeColumn; j++) {
            cout << myContainer[i][j] << "\t";
        }
        cout << "\n\n";
    }
}

// harmadik táblázat kiszámítása
void filterThirdTable(vector<string> rulesLeft,vector<string> rulesRight, string myContainer[5][5], vector<string> firstOne, vector<int> elementsLeftIndex, int value) {
    vector<char> elementsRight;
    vector<char> elementsLeft;
    vector<string> analyst;
    string mixed;
    int position = 0;
    elementsLeft = tableElementsLeft(rulesLeft);
        // az 5 a column
    for (int j = 1; j < 5; j++) {
        myContainer[value][0] = "#";
        for (int k = 0; k < rulesRight.size(); k++) {
            for (int l = 0; l < rulesRight[k].size(); l++) {
                if (elementsLeft[j] == rulesRight[k][l]) {
                    analyst.push_back(rulesRight[k]);
                }
            }
        }
        for (int n = 0; n < analyst.size(); n++) {
            for (int m = 0; m < analyst[n].size(); m++) {
                if (analyst[n][m] == elementsLeft[j]) {
                    if (m == analyst[n].size() - 1) { // pont a legutolsó eleme az m
                        mixed = mixed + "#";
                    }
                    else if (returnWithASCIIValue(analyst[n][m+1]) >= 65 && returnWithASCIIValue(analyst[n][m+1]) <= 90) { // egyébként meg megkeressük a jelenleg vizsgált nagybetű utáni betű hol van a firstOne-ban, majd hozzáadjuk a firstOne beli értékét a mixedhez.
                        position = checkNonTerminalValueInColumns(rulesLeft, analyst[n][m+1]);
                        mixed = mixed + firstOne[position];
                    }
                    else {
                        mixed = mixed + analyst[n][m+1];
                    }
                }
            }
        }
        if (value > 1 && j == 1) {
            myContainer[value][j] = filterTerminal(mixed) + "deb";
        }
        else {
            myContainer[value][j] = filterTerminal(mixed);
        }
        mixed = "";
        analyst.clear(); 
    }

    value++;
    if (value < 4) {
        filterThirdTable(rulesLeft,rulesRight,myContainer,firstOne,elementsLeftIndex,value);
    }
    if (value == 4) {
        cout << "Harmadik táblázat: " << "\n\n";
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

// megkeresi, hogy hol fordul elő a szabály bal oldalában a beadott betű (value)
int checkNonTerminalValueInColumns(vector<string> rulesLeft, char value) {
    vector<char> elementsLeft;
    int columnNumber = 0;
    elementsLeft = tableElementsLeft(rulesLeft);

    for (int i = 0; i < elementsLeft.size(); i++) {
        if (value == elementsLeft[i]) {
            columnNumber = i;
        }
    }

    return columnNumber;
}

// megkeresi, hogy hol fordul elő a szabály bal oldalában a beadott betű (value)
int checkTerminalValueInColumns(vector<char> elementsRight, char value) {
    int columnNumber = 0;

    for (int i = 0; i < elementsRight.size() - 1; i++) {
        if (value == elementsRight[i]) {
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

// ismétlések nélkül adja vissza a tábla jobb oldali elemeit
vector<char> tableElementsRight(vector<string> valueRight) {
    vector<char> datas;
    for (int i = 0; i < valueRight.size(); i++) {
        for (int j = 0; j < valueRight[i].size(); j++) {
            if (returnWithASCIIValue(valueRight[i][j]) >= 97 && returnWithASCIIValue(valueRight[i][j]) <= 122) {
                if (datas.size() > 0) {
                    for (int k = 0; k < datas.size(); k++) {
                        if (datas[k] == valueRight[i][j]) {
                            break;
                        }
                        else if (k + 1 == datas.size()) {
                            datas.push_back(valueRight[i][j]);
                        }
                    }
                }
                else {
                    datas.push_back(valueRight[i][j]);
                }
            }
        }
    }
    datas.push_back('#');
    return datas;
}


int returnWithASCIIValue(char letter){
	int value = letter;
	return value;
}