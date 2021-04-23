#include <iostream>
#include <vector>
using namespace std;

void welcome();
void firstRow(vector<string> valueLeft, vector<string> valueRight, vector<string> valueZerothRow);
void secondRow(vector<string> valueLeft, vector<string> valueRight, vector<string> value);
void thirdRow(vector<string> firstRow, vector<string> secondRow, vector<string> rulesLeft, vector<string> rulesRight);
void fourthRow(vector<string> firstRow, vector<string> secondRow, vector<string> thirdRow, vector<string> valueLeft, vector<string> valueRight);
void fifthRow(vector<string> firstRow, vector<string> secondRow, vector<string> thirdRow, vector<string> fourthRow, vector<string> valueLeft, vector<string> valueRight);
void sixthRow(vector<string> firstRow, vector<string> secondRow, vector<string> thirdRow, vector<string> fourthRow, vector<string> fifthRow, vector<string> valueLeft, vector<string> valueRight);

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
    fourthRow(firstRow,secondRow,thirdRowVector,valueLeft,valueRight);
}

void fourthRow(vector<string> firstRow, vector<string> secondRow, vector<string> thirdRow, vector<string> valueLeft, vector<string> valueRight) {
    string combined;
    string mixed;
    vector<string> fourthRowVector;
    vector<string> fourthRowVectorVersionA;
    vector<string> fourthRowVectorVersionB;
    vector<string> fourthRowVectorVersionC;

    for (int i = 0; i < firstRow.size(); i++) {
        if (i + 1 < thirdRow.size()) {
            for (int k = 0; k < firstRow[i].size(); k++) {
                for (int l = 0; l < thirdRow[i+1].size(); l++) {
                    combined = combined + firstRow[i][k] + thirdRow[i+1][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fourthRowVectorVersionA.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < thirdRow.size(); i++) {
        if (i + 1 < thirdRow.size()) {
            for (int k = 0; k < thirdRow[i].size(); k++) {
                for (int l = 0; l < firstRow[i+3].size(); l++) {
                    combined = combined + thirdRow[i][k] + firstRow[i+3][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fourthRowVectorVersionB.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < secondRow.size(); i++) {
        if (i + 2 < secondRow.size()) {
            for(int k = 0; k < secondRow[i].size(); k++) {
                for (int l = 0; l < secondRow[i+2].size(); l++) {
                    combined = combined + secondRow[i][k] + secondRow[i+2][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fourthRowVectorVersionC.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < fourthRowVectorVersionA.size(); i++) {
        mixed = mixed + fourthRowVectorVersionA[i] + fourthRowVectorVersionB[i] + fourthRowVectorVersionC[i];
        fourthRowVector.push_back(mixed);
        mixed = "";
    }

    cout << "Ez a negyedik sor: ";
    for (vector<string>::iterator p = fourthRowVector.begin(); p < fourthRowVector.end();++p) {
        cout << *p << " ";
    }
    cout << "\n";

    fifthRow(firstRow,secondRow,thirdRow,fourthRowVector,valueLeft,valueRight);
}

void fifthRow(vector<string> firstRow, vector<string> secondRow, vector<string> thirdRow, vector<string> fourthRow, vector<string> valueLeft, vector<string> valueRight) {
    string combined;
    string mixed;
    vector<string> fifthRowVector;
    vector<string> fifthRowVectorVersionA;
    vector<string> fifthRowVectorVersionB;
    vector<string> fifthRowVectorVersionC;
    vector<string> fifthRowVectorVersionD;

    for (int i = 0; i < firstRow.size(); i++) {
        if (i + 1 < fourthRow.size()) {
            for (int k = 0; k < firstRow[i].size(); k++) {
                for (int l = 0; l < fourthRow[i+1].size(); l++) {
                    combined = combined + firstRow[i][k] + fourthRow[i+1][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fifthRowVectorVersionA.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < fourthRow.size(); i++) {
        if (i + 1 < fourthRow.size()) {
            for (int k = 0; k < fourthRow[i].size(); k++) {
                for (int l = 0; l < firstRow[i+4].size(); l++) {
                    combined = combined + fourthRow[i][k] + firstRow[i+4][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fifthRowVectorVersionB.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < secondRow.size(); i++) {
        if (i + 3 < secondRow.size()) {
            for(int k = 0; k < secondRow[i].size(); k++) {
                for (int l = 0; l < secondRow[i+3].size(); l++) {
                    combined = combined + secondRow[i][k] + secondRow[i+3][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fifthRowVectorVersionC.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < thirdRow.size(); i++) {
        if (i + 2 < thirdRow.size()) {
            for(int k = 0; k < thirdRow[i].size(); k++) {
                for (int l = 0; l < thirdRow[i+2].size(); l++) {
                    combined = combined + thirdRow[i][k] + thirdRow[i+2][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            fifthRowVectorVersionD.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < fifthRowVectorVersionA.size(); i++) {
        mixed = mixed + fifthRowVectorVersionA[i] + fifthRowVectorVersionB[i] + fifthRowVectorVersionC[i] + fifthRowVectorVersionD[i];
        fifthRowVector.push_back(mixed);
        mixed = "";
    }

    cout << "Ez az ötödik sor: ";
    for (vector<string>::iterator p = fifthRowVector.begin(); p < fifthRowVector.end();++p) {
        cout << *p << " ";
    }
    cout << "\n";
    sixthRow(firstRow,secondRow,thirdRow,fourthRow,fifthRowVector,valueLeft,valueRight);
}

void sixthRow(vector<string> firstRow, vector<string> secondRow, vector<string> thirdRow, vector<string> fourthRow, vector<string> fifthRow, vector<string> valueLeft, vector<string> valueRight) {
    string combined;
    string mixed;
    vector<string> sixthRowVector;
    vector<string> sixthRowVectorVersionA;
    vector<string> sixthRowVectorVersionB;
    vector<string> sixthRowVectorVersionC;
    vector<string> sixthRowVectorVersionD;
    vector<string> sixthRowVectorVersionE;

    for (int i = 0; i < firstRow.size(); i++) {
        if (i + 1 < fifthRow.size()) {
            for (int k = 0; k < firstRow[i].size(); k++) {
                for (int l = 0; l < fifthRow[i+1].size(); l++) {
                    combined = combined + firstRow[i][k] + fifthRow[i+1][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            sixthRowVectorVersionA.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < fifthRow.size(); i++) {
        if (i + 1 < fifthRow.size()) {
            for (int k = 0; k < fifthRow[i].size(); k++) {
                for (int l = 0; l < firstRow[i+5].size(); l++) {
                    combined = combined + fifthRow[i][k] + firstRow[i+5][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            sixthRowVectorVersionB.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < secondRow.size(); i++) {
        if (i + 4 < secondRow.size()) {
            for(int k = 0; k < secondRow[i].size(); k++) {
                for (int l = 0; l < secondRow[i+4].size(); l++) {
                    combined = combined + secondRow[i][k] + secondRow[i+4][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            sixthRowVectorVersionC.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < thirdRow.size(); i++) {
        if (i + 3 < thirdRow.size()) {
            for(int k = 0; k < thirdRow[i].size(); k++) {
                for (int l = 0; l < thirdRow[i+3].size(); l++) {
                    combined = combined + thirdRow[i][k] + thirdRow[i+3][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            sixthRowVectorVersionD.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < fourthRow.size(); i++) {
        if (i + 2 < fourthRow.size()) {
            for(int k = 0; k < fourthRow[i].size(); k++) {
                for (int l = 0; l < fourthRow[i+2].size(); l++) {
                    combined = combined + fourthRow[i][k] + fourthRow[i+2][l];
                    for (int m = 0; m < valueRight.size(); m++) {
                        if (combined == valueRight[m]) {
                            mixed = mixed + valueLeft[m];
                        }
                    }
                    combined = "";
                }
            }
            sixthRowVectorVersionE.push_back(mixed);
            mixed = "";
        }
    }

    for (int i = 0; i < sixthRowVectorVersionA.size(); i++) {
        mixed = mixed + sixthRowVectorVersionA[i] + sixthRowVectorVersionB[i] + sixthRowVectorVersionC[i] + sixthRowVectorVersionD[i] + sixthRowVectorVersionE[i];
        sixthRowVector.push_back(mixed);
        mixed = "";
    }

    cout << "Ez az hatodik sor: ";
    for (vector<string>::iterator p = sixthRowVector.begin(); p < sixthRowVector.end();++p) {
        cout << *p << " ";
    }
    cout << "\n";
}