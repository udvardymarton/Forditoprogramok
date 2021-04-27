#include <iostream>
#include <vector>
using namespace std;

void welcome();
int returnWithASCIIValue(char letter);
vector<char> tableElementsRight(vector<string> valueRight);
vector<char> tableElementsLeft(vector<string> valueRight);
void table(vector<string> rulesLeft, vector<string> rulesRight);

int main() {
    cout << "A ELL(1) algoritmus megvalósítása\n";
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
    table(rulesLeft,rulesRight);
}

void table(vector<string> rulesLeft, vector<string> rulesRight) {
    vector<char> elementsRight;
    vector<char> elementsLeft;
    vector<char> elementsLeftAndRightMix;
    vector<int> elementIndexLeft;
    vector<string> elementIndexRight;
    elementsLeft = tableElementsLeft(rulesLeft);
    elementsRight = tableElementsRight(rulesRight);
    elementsLeftAndRightMix = tableElementsLeft(rulesLeft);
    for (int n = 0; n < elementsRight.size(); n++) {
        elementsLeftAndRightMix.push_back(elementsRight[n]);
    }
    for (vector<char>::iterator j = elementsLeftAndRightMix.begin(); j < elementsLeftAndRightMix.end();++j) {
        cout << "Az elem: ";
        cout << *j << "\t";
    }

    cout << "Ez a táblázat: \n" << endl;
    cout << " \t";
    for (vector<char>::iterator j = elementsRight.begin(); j < elementsRight.end();++j) {
        cout << *j << "\t";
    }
    cout << "\n\n";
    for (vector<char>::iterator k = elementsLeftAndRightMix.begin(); k < elementsLeftAndRightMix.end();++k) {
        cout << *k << "\t";
        for (int j = 0; j < elementsRight.size(); j++) {
            if (returnWithASCIIValue(*k) >= 65 && returnWithASCIIValue(*k) <= 90) {
                for (int m = 0; m < rulesLeft.size(); m++) {
                    if(*k == rulesLeft[m][0]) {
                        elementIndexLeft.push_back(m);
                    }
                }
                for (int i = 0; i < elementIndexLeft.size();i++) {
                    elementIndexRight.push_back(rulesRight[elementIndexLeft[i]]);
                }

                if (elementsRight[j] == elementIndexRight[0][0]) {
                    cout << "(" << elementIndexRight[0] << "," << elementIndexLeft[0] + 1 << ")" << "\t";
                }
                else if (elementsRight[j] == elementIndexRight[1][0]) {
                    cout << "(" << elementIndexRight[1] << "," << elementIndexLeft[1] + 1 << ")" << "\t";
                }
                else {
                    cout << "error" << "\t";
                }
                elementIndexLeft.clear();
                elementIndexRight.clear();
            }
            else if (*k == '#' && elementsRight[j] == '#') {
                cout << "accept" << "\t";
            }
            else if (*k == elementsRight[j]){
                cout << "pop" << "\t";
            }
            else { 
                cout << "error" << "\t";
            }
        }
        cout << "\n\n";
    }
}

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