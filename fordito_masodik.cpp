#include <iostream>
#include <vector>
using namespace std;

void welcome();
void firstRow(vector<string> rulesLeft, vector<string> rulesRight, vector<string> valueZerothRow);
void otherRows(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[7][7], int value, int size);

int main() {
    cout << "A CYK algoritmus megvalósítása\n";
    cout << "Kérem add meg a szabályokat!\nA szabályok alakja a következő: A->B\nHa több szabály is van, akkor enterrel válaszd el őket!\n";
    welcome();
}

void welcome() {
    string rules;
    string zerothRow;
    vector<string> zerothRowVector;
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
    cout << "\nKérem a nulladik sort! (Vizsgálandó szó!)\n";
    cin >> zerothRow;
    for (int l = 0; l < zerothRow.size();l++) {
        char asd = zerothRow[l];
        string value;
        value.push_back(asd);
        zerothRowVector.push_back(value);
    }
    cout << "Ez van a bal oldalt: ";
    for (vector<string>::iterator i = rulesLeft.begin(); i < rulesLeft.end();++i) {
        cout << *i << " ";
    }
    cout << "\nEz van a jobb oldalt: ";
    for (vector<string>::iterator j = rulesRight.begin(); j < rulesRight.end();++j) {
        cout << *j << " ";
    }
    cout << "\nEz a vizsgálandó szó: ";
    for (vector<string>::iterator k = zerothRowVector.begin(); k < zerothRowVector.end();++k) {
        cout << *k << " ";
    }
    cout << "\n";
    firstRow(rulesLeft,rulesRight,zerothRowVector);
}

void firstRow(vector<string> rulesLeft, vector<string> rulesRight, vector<string> valueZerothRow) {
    string mixed = "";
    string myContainer[7][7];
    int value = 1;
    int size = sizeof(myContainer[0]) / sizeof(myContainer[0][0]);
    vector<string> theLeftValue;
    vector<string> firstRowVector;

    for (int i = 0; i < valueZerothRow.size();i++) {
        for (int j = 0; j < rulesRight.size();j++) {
            if (valueZerothRow[i] == rulesRight[j]) {
                theLeftValue.push_back(rulesLeft[j]);
            }
        }
        for (int k = 0; k < theLeftValue.size();k++) {
            mixed = mixed + theLeftValue[k];
        }
        firstRowVector.push_back(mixed);
        mixed = "";
        theLeftValue.clear();
    }
    for (int i = 0; i < 1; i++) {
        for (int j = 0;j < firstRowVector.size(); j++) {
            myContainer[i][j] = firstRowVector[j];
        }
    }
    cout << "Ez az első sor: ";
    for (int l = 0; l < firstRowVector.size();l++) {
        cout << myContainer[0][l] << " ";
    }
    cout << "\n";
    otherRows(rulesLeft,rulesRight,myContainer,value,size);
}

void otherRows(vector<string> rulesLeft, vector<string> rulesRight, string myContainer[7][7], int value, int size) {
    string combined;
    string mixed;

    for (int i = 0; i < value; i++) {
        for (int j = 0; j < size; j++) {
            if (j + 1 < size) {
            for (int k = 0; k < myContainer[i][j].size(); k++) {
                for (int l = 0; l < myContainer[value - (i+1)][i + j + 1].size(); l++) {
                    combined = combined + myContainer[i][j][k] + myContainer[value - (i+1)][i + j + 1][l];
                    for (int n = 0; n < rulesRight.size();n++) {
                        if (combined == rulesRight[n]) {
                            mixed = mixed + rulesLeft[n];
                        }
                    }
                    combined = "";
                }
            }
            myContainer[value][j] = myContainer[value][j] + mixed;
            mixed = "";
        }
    }
    }

    if (size > 1) {
        cout << "Ez a " << value + 1 << ".sor: ";
        for (int i = 0; i < size - 1; i++) {
            if (myContainer[value][i] == "") {
            cout << "- ";
        }
        else {
            cout << myContainer[value][i] << " ";
        }
        }
    cout << endl;
        value++;
        size--;
        otherRows(rulesLeft,rulesRight,myContainer,value,size);
    }

}