#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>


int returnWithASCIIValue(char letter);
void start(char *s, int value);
void identifer(char *s, int value);
void constans(char *s, int value);
void secondBrackets(char *s, int value);
void firstBrackets(char *s, int value);
void firstBracketsWithStars(char *s, int value);
void firstBracketsWithStarsInsideStars(char *s, int value);
void colonWithEqualMark(char *s, int value);
void colon(char *s, int value);
void lessThan(char *s, int value);
void lessThanWithEqual(char *s, int value);
void greaterThan(char *s, int value);
void greaterThanToken(char *s, int value);
void greaterThanWithEqual(char *s, int value);
int isDigit(char s);
int isLetter(char s);
int isSecondBrackets(char s);
int isFirstBrackets(char s);


int main() {
	char s[100];
	printf("kérem adj be valamit!\n");
	printf("Ezt adtad be ---> ");
	scanf("%[^\n]",s);
	start(s,0);
	return 0;
}





void start(char *s, int value) {
	if (isLetter(s[value]) == 1) {
		printf("<azonosítóban> ");
		identifer(s,value);
	}
	else if (isDigit(s[value]) == 1) {
		printf("<számban> ");
		constans(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 123) {
		printf("<{} kommentárban> ");
		secondBrackets(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 40) {
		printf("(-t talált ");
		value++;
		firstBrackets(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 58) {
		printf(":-t talált ");
		value++;
		colon(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 60) {
		printf("<-t talált");
		value++;
		lessThan(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 62) {
		printf(">-t talált");
		value++;
		greaterThan(s,value);
	}
	else if (value == strlen(s)) {
		printf("\nA program sikeresen lefutott\n");
		exit(0);
	}
	else {
		printf("\nHiba! Kezdőállapotban ilyen értéket nem adhatsz meg vagy a nyelv ilyen karaktereket nem fogad el vagy rossz a sorrend! Másképp kérem.\n");
		exit(0);
	}
}

void identifer(char *s,int value) {
	if (isLetter(s[value]) || isDigit(s[value])) {
		printf("%c",s[value]);
		value++;
		identifer(s,value);
	}
	else if(!isLetter(s[value])) {
		printf(" <azonosító vége>");
	}
	start(s,value);
}

void constans(char *s,int value) {
	if (isDigit(s[value])) {
		printf("%c",s[value]);
		value++;
		constans(s,value);
	}
	else if(!isDigit(s[value])) {
		printf(" <szám vége>");
	}
	printf("%d",value);
	start(s,value);
}

void secondBrackets(char *s,int value) {
	if (returnWithASCIIValue(s[value]) == 36) {
		printf("Hiba!");
		exit(0);
	}
	else if (returnWithASCIIValue(s[value]) == 125) {
		printf("%c",s[value]);
		printf(" <{} kommentár vége>");
		printf("\nA program sikeresen lefutott\n");
		exit(0);
	}
	else if (value < strlen(s)){
		printf("%c",s[value]);
		value++;
		secondBrackets(s,value);
	}
	start(s,value);
}


void firstBrackets(char *s, int value) {
	if (returnWithASCIIValue(s[value]) == 36) {
		printf("Hiba!");
		exit(0);
	}
	else if (returnWithASCIIValue(s[value]) == 42) {
		printf("%c",s[value]);
		value++;
		printf(" <(**) kommentárban> ");
		firstBracketsWithStars(s,value);
	}
	else if (value < strlen(s)){
		printf("\nHiba!\n");
		exit(0);
	}
	start(s,value);
}

void firstBracketsWithStars(char *s, int value) {
	if (returnWithASCIIValue(s[value]) == 36) {
		printf("\nHiba!\n");
		exit(0);
	}
	else if (returnWithASCIIValue(s[value]) == 42) {
		printf("%c",s[value]);
		value++;
		printf(" <* (**) kommentárban> ");
		firstBracketsWithStarsInsideStars(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 41) {
		printf(" <(**) kommentár vége>\n");
		printf("\nA program sikeresen lefutott\n");
		exit(0);
	}
	else if (value < strlen(s)) {
		printf("%c",s[value]);
		value++;
		firstBracketsWithStars(s,value);
	}
	printf("%c",s[value]);
	start(s,value);
}

void firstBracketsWithStarsInsideStars(char *s, int value) {
	if (returnWithASCIIValue(s[value]) == 41) {
		printf(" <(**) kommentár vége>\n");
		exit(0);
	}
	else if (returnWithASCIIValue(s[value]) == 36) {
		printf("\nHiba!\n");
		exit(0);
	}
	else if (returnWithASCIIValue(s[value]) == 42) {
		printf("%c",s[value]);
		value++;
		firstBracketsWithStarsInsideStars(s,value);
	}
	else {
		firstBracketsWithStars(s,value);
	}
	start(s,value);
}

void colon(char *s, int value) {
	if (returnWithASCIIValue(s[value]) == 61) {
		printf("%c",value);
		value++;
		printf(" := token ");
		colonWithEqualMark(s,value);
	}
	else if (value == strlen(s)) {
		printf("\nTúl rövid!\n");
		exit(0);
	}
	else {
		printf("\nHiba!\n");
		exit(0);
	}
	start(s,value);
}

void colonWithEqualMark(char *s, int value) {
	start(s,value);
}

void lessThan(char *s, int value) {
	if (returnWithASCIIValue(s[value]) == 61) {
		printf("%c",value);
		value++;
		printf(" <= token ");
		lessThanWithEqual(s,value);
	}
	else if (returnWithASCIIValue(s[value]) == 62) {
		printf("%c",value);
		value++;
		printf(" <> token ");
		greaterThanToken(s,value);
	}
	else if (value == strlen(s)) {
		printf("\nTúl rövid!\n");
		exit(0);
	}
	else {
		printf("\nHiba!\n");
		exit(0);
	}
	start(s,value);
}

void lessThanWithEqual(char *s, int value) {
	start(s,value);
}

void greaterThanToken(char *s, int value) {
	start(s,value);
}

void greaterThan(char *s, int value) {
	if (returnWithASCIIValue(s[value]) == 61) {
		printf("%c",value);
		value++;
		printf(" >= token ");
		greaterThanWithEqual(s,value);
	}
	else if (value == strlen(s)) {
		printf("\nTúl rövid!\n");
		exit(0);
	}
	else {
		printf("\nHiba!\n");
		exit(0);
	}
	start(s,value);
}

void greaterThanWithEqual(char *s, int value) {
	start(s,value);
}




































int returnWithASCIIValue(char letter){
	int value = letter;
	return value;
}

int isDigit(char s) {
	if (returnWithASCIIValue(s) >= 48 && returnWithASCIIValue(s) <= 57) {
		return 1;
	}
	else {
		//printf("\nEz nem egy szám!\n");
		return 0;
	}
}

int isLetter(char s) {
	if ((returnWithASCIIValue(s) >= 65 && returnWithASCIIValue(s) <= 90) || (returnWithASCIIValue(s) >= 97 && returnWithASCIIValue(s) <= 122)) {
		return 1;
	}
	else {
		//printf("\nEz nem egy betű!\n");
		return 0;
	}
}

int isSecondBrackets(char s) {
	if (returnWithASCIIValue(s) == 123) {
		return 1;
	}
	else {
		return 0;
	}
}

int isFirstBrackets(char s) {
	if (returnWithASCIIValue(s) == 40) {
		return 1;
	}
	else {
		return 0;
	}
}