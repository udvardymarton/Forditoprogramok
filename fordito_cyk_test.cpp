#include <iostream>
#include <vector>
using namespace std;

void welcome();
void firstRow(vector<string> valueLeft, vector<string> valueRight, vector<string> valueZerothRow);
void secondRow(vector<string> valueLeft, vector<string> valueRight, vector<string> value);
void thirdRow(vector<string> firstRow, vector<string> secondRow, vector<string> rulesLeft, vector<string> rulesRight);

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
            //cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
            //cout << s << std::endl;
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

void firstRow(vector<string> valueLeft, vector<string> valueRight, vector<string> valueZerothRow) {
    int value = 0;
    string mixed = "";
    vector<string> theLeftValue;
    vector<string> firstRowVector;

    for (int i = 0; i < valueZerothRow.size();i++) {
        for (int j = 0; j < valueRight.size();j++) {
            if (valueZerothRow[i] == valueRight[j]) {
                theLeftValue.push_back(valueLeft[j]);
            }
        }
        for (int k = 0; k < theLeftValue.size();k++) {
            mixed = mixed + theLeftValue[k];
        }
        firstRowVector.push_back(mixed);
        mixed = "";
        theLeftValue.clear();
    }
    cout << "Ez az első sor: ";
    for (int l = 0; l < firstRowVector.size();l++) {
        cout << firstRowVector[l] << " ";
    }
    cout << "\n";

    secondRow(valueLeft,valueRight,firstRowVector);
}

void secondRow(vector<string> valueLeft, vector<string> valueRight, vector<string> value) {
    string combined;
    string mixed;
    string other;
    vector<string> secondRowVector;

    for (int i = 0; i < value.size(); i++) {
        if (i + 1 < value.size()) {
            for (int j = 0; j < value[i].size();j++) {
                for (int n = 0; n < value[i+1].size();n++) {
                    combined = combined + value[i][j] + value[i+1][n];
                    for (int k = 0; k < valueRight.size();k++) {
                        if (combined == valueRight[k]) {
                            mixed = mixed + valueLeft[k];
                        }
                    }
                    combined = "";
                }
            }
            secondRowVector.push_back(mixed);
            mixed = "";
        }
    }
    cout << "Ez a második sor: ";
    for (vector<string>::iterator p = secondRowVector.begin(); p < secondRowVector.end();++p) {
        cout << *p << " ";
    }
    cout << "\n";
    thirdRow(value,secondRowVector,valueLeft,valueRight);
}

void thirdRow(vector<string> firstRow, vector<string> secondRow, vector<string> valueLeft, vector<string> valueRight) {
    string combined;
    string mixed;
    vector<string> thirdRowVector;
    vector<string> thirdRowVectorVersionA;
    vector<string> thirdRowVectorVersionB;

    for (int i = 0; i < firstRow.size(); i++) {
        if (i + 1 < secondRow.size()) {
            for (int k = 0; k < firstRow[i].size(); k++) {
                for (int l = 0; l < secondRow[i+1].size(); l++) {
                    combined = combined + firstRow[i][k] + secondRow[i+1][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            thirdRowVectorVersionA.push_back(mixed);
            mixed = "";
        }
    }
    //cout << "A thirdRowVectorVersionA mérete: " << thirdRowVectorVersionA.size();
    //cout << "\n";
    //cout << "Elemek VersionA: " << " ";
    // for (vector<string>::iterator p = thirdRowVectorVersionA.begin(); p < thirdRowVectorVersionA.end();++p) {
    //     if (*p == "") {
    //         cout << "üres ";
    //     }
    //     else {
    //         cout << *p << " ";
    //     }
    // }
    // cout << "\n";

    for (int i = 0; i < secondRow.size(); i++) {
        if (i + 1 < secondRow.size()) {
            for (int k = 0; k < secondRow[i].size(); k++) {
                for (int l = 0; l < firstRow[i+2].size(); l++) {
                    combined = combined + secondRow[i][k] + firstRow[i+2][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            thirdRowVectorVersionB.push_back(mixed);
            mixed = "";
        }
    }
    //cout << "A thirdRowVectorVersionB mérete: " << thirdRowVectorVersionB.size();
    //cout << "\n";
    //cout << "Elemek VersionB: " << " ";
    // for (vector<string>::iterator p = thirdRowVectorVersionB.begin(); p < thirdRowVectorVersionB.end();++p) {
    //     if (*p == "") {
    //         cout << "üres ";
    //     }
    //     else {
    //         cout << *p << " ";
    //     }
    // }
    // cout << "\n";

    for (int i = 0; i < thirdRowVectorVersionA.size(); i++) {
        mixed = mixed + thirdRowVectorVersionA[i] + thirdRowVectorVersionB[i];
        thirdRowVector.push_back(mixed);
        mixed = "";
    }

    cout << "Ez a harmadik sor: ";
    for (vector<string>::iterator p = thirdRowVector.begin(); p < thirdRowVector.end();++p) {
        cout << *p << " ";
    }
    cout << "\n";
}

void fourthRow() {
    
}