#include "auxFunctions.h"


void incrementScope() {
	scope = scope + 1;
}
void decrementScope() {
	scope = scope - 1;
}

void setVariableFor(char * new_variable) {
	variable_for = mallocNewString(new_variable);
	strcpy(new_variable, variable_for);
}

char * getVariableFor() {
	return variable_for;
}

void printTabs() {
	int i;
	for (i = 0; i < scope; i++) {
		fprintf(fileOut, "\t");
	}
}

void printBlankSpace() {
	fprintf(fileOut, " ");
}

void printNewLine() {
	fprintf(fileOut, "\n");
}

void printIncludesOfProgram() {
	fprintf(fileOut, "#include <bits/stdc++.h>");
    printNewLine();
    printNewLine();
    fprintf(fileOut, "using namespace std;");
    printNewLine();
    printNewLine();
}

void printBeginOfProgram() {
    printNewLine();
	fprintf(fileOut, "int main() {");
    printNewLine();
}

void printEndOfProgram() {
	printNewLine();
	printTabs();
	fprintf(fileOut, "return 0;");
	printNewLine();
	fprintf(fileOut, "}");
	printNewLine();
}

void printDeclaration(char * type, type_values * name) {
	printTabs();
	fprintf(fileOut, "%s", type);
	printBlankSpace();
    fprintf(fileOut, "%s", (char*)name->value);
    fprintf(fileOut, ";");
    printNewLine();
}

void printAtribuition(char * variable, type_values * value) {
	printTabs();
	fprintf(fileOut, "%s", variable);
	printBlankSpace();
	fprintf(fileOut, "=");
	printBlankSpace();

	if (value->type == TYPE_STRING) {
    	fprintf(fileOut, "\"");
		printTypeValues(value);
		fprintf(fileOut, "\"");
	} else {
		printTypeValues(value);
	}

    fprintf(fileOut, ";");
    printNewLine();
}

void printIfDeclaration(char * type) {
	if (strcmp(type, "begin") == 0) {
		printTabs();
		fprintf(fileOut, "if (");
	} else if (strcmp(type, "begin_else") == 0) {
		fprintf(fileOut, "if (");
	} else {
        fprintf(fileOut, ") {");
        printNewLine();
    }
}

void printElseDeclaration(char * type) {
	if (strcmp(type, "begin") == 0) {
		printTabs();
		fprintf(fileOut, "else { \n");
	} else if (strcmp(type, "begin_if") == 0) {
		printTabs();
		fprintf(fileOut, "else ");
	}
}

void printWhileDeclaration(char * type) {
	if (strcmp(type, "begin") == 0) {
		printTabs();
		fprintf(fileOut, "while (");
	} else {
        fprintf(fileOut, ") {");
        printNewLine();
    }
}

void printForDeclaration(char * type) {
	if (strcmp(type, "begin") == 0) {
		printTabs();
		fprintf(fileOut, "for (");
	} else {
		fprintf(fileOut, ") {");
        printNewLine();
	}
}

void printForAtribuition(type_values * value) {

	fprintf(fileOut, "%s", getVariableFor());
	printBlankSpace();
	fprintf(fileOut, "=");
	printBlankSpace();

	printTypeValues(value);

	fprintf(fileOut, ";");
}

void printForScope(char * type, type_values * expression) {
	if (strcmp(type, ">") == 0) {
		printForScopeAux1();
		fprintf(fileOut, ">");
		printForScopeAux2(expression);

		fprintf(fileOut, "%s--", getVariableFor());
	} else {
		printForScopeAux1();
		fprintf(fileOut, "<");
		printForScopeAux2(expression);
		fprintf(fileOut, "%s++", getVariableFor());
	}
}

void printForScopeAux1() {
	printBlankSpace();
	fprintf(fileOut, "%s", getVariableFor());
	printBlankSpace();
}

void printForScopeAux2(type_values * expression) {
	printBlankSpace();
	printTypeValues(expression);
	fprintf(fileOut, ";");
	printBlankSpace();
}

void printRepeatDeclaration(char * type) {
	if (strcmp(type, "begin") == 0) {
		printTabs();
		fprintf(fileOut, "do {");
		printNewLine();
	} else if (strcmp(type, "before_end") == 0) {
		printTabs();
        fprintf(fileOut, "} while (");
    } else {
        fprintf(fileOut, ");");
        printNewLine();
    }
}

void printConditionValue(type_values * expression) {
	printTypeValues(expression);
}

void printCondition(type_values * expression1, type_values * expression2, char * condition) {
	printConditionValue(expression1);

	fprintf(fileOut, " %s ", condition);

	printConditionValue(expression2);
}


void printAndOrCondition(char * type) {
	if (strcmp(type, "and") == 0) {
		fprintf(fileOut, " && ");
	} else {
		fprintf(fileOut, " || ");
	}
}

void printWriteDeclarationValues(type_values * expression) {
	if (expression->type == TYPE_STRING) {
		fprintf(fileOut, "\"");
		printTypeValues(expression);
		fprintf(fileOut, "\"");
	} else {
		printTypeValues(expression);
	}
}

void printWriteDeclaration(char * type) {
	if (strcmp(type, "begin") == 0) {
		printTabs();
		fprintf(fileOut, "cout << ");
	} else if (strcmp(type, "endln") == 0) {
		fprintf(fileOut, " << endl;");
		printNewLine();
	} else {
		fprintf(fileOut, ";");
		printNewLine();
	}
}

void printReadDeclaration(char * type) {
	printTabs();
	fprintf(fileOut, "cin >> %s;", type);
	printNewLine();
}

void printComment(char * type, char * comment) {
	if (strcmp(type, "slash") == 0) {
		printTabs();
		fprintf(fileOut, "%s", comment);
	} else if (strcmp(type, "brace_asterisk") == 0) {
		printTabs();
		if (comment[0] == '*') {
			fprintf(fileOut, "/%s/", comment);
		} else {
			fprintf(fileOut, "/* %s */", comment);
		}
	}

	printNewLine();
}

void printEndStatements() {
	printTabs();
	fprintf(fileOut, "}");
	printNewLine();
}

void printClrscrStatements() {
	printTabs();
	fprintf(fileOut, "cout << string(50, \"\\n\");\n");
}

void printTypeValues(type_values * type_value) {
	if (type_value->type == TYPE_STRING) {
		fprintf(fileOut, "%s", returnTypeValuesString(type_value));

	} else if (type_value->type == TYPE_INT) {
		fprintf(fileOut, "%d", returnTypeValuesInt(type_value));

	} else {
		fprintf(fileOut, "%lf", returnTypeValuesDouble(type_value));
	}
}

void printTypeValues1(type_values * type_value) {
	if (type_value->type == TYPE_STRING) {
		printf("%s", returnTypeValuesString(type_value));

	} else if (type_value->type == TYPE_INT) {
		printf("%d", returnTypeValuesInt(type_value));

	} else {
		printf("%lf", returnTypeValuesDouble(type_value));
	}
}

void printTypeValues2(int type, void * type_value) {
	if (type == TYPE_STRING) {
		printf("%s", returnTypeValuesString(type_value));

	} else if (type == TYPE_INT) {
		printf("%d", returnTypeValuesInt(type_value));

	} else {
		printf("%lf", returnTypeValuesDouble(type_value));
	}
}

char * returnTypeValuesString(type_values * type_value) {
	return (char*)type_value->value;
}

int returnTypeValuesInt(type_values * type_value) {
	return ((int*)type_value->value)[0];
}

double returnTypeValuesDouble(type_values * type_value) {
	return ((double*)type_value->value)[0];
}

char * mallocNewString(char * new_text) {
	char * destination = malloc(sizeof(strlen(new_text)));
    strcpy(destination, new_text);
    return destination;
}

int convertTypeStringToTypeInt(char * type) {
	int returnConvert = -1;

	if (!strcmp(type, "string") || !strcmp(type, "char")) {
		returnConvert = TYPE_STRING;

	} else if (!strcmp(type, "int") 		 || !strcmp(type, "signed char") 		|| !strcmp(type, "short int") 		   ||
			   !strcmp(type, "long long") 	 || !strcmp(type, "unsigned char") 	  	|| !strcmp(type, "unsigned short int") ||
			   !strcmp(type, "unsigned int") || !strcmp(type, "unsigned long long") || !strcmp(type, "int")) {
		returnConvert = TYPE_INT;

	} else if (!strcmp(type, "double") || !strcmp(type, "long double") || !strcmp(type, "float")) {
		returnConvert = TYPE_DOUBLE;

	} else if (!strcmp(type, "bool")) {
		returnConvert = TYPE_BOOL;

	} else {
		returnConvert = -1;
	}

	return returnConvert;
}

char * convertTypeIntToTypeString(int type) {
	char * returnConvert = "";

	switch(type) {
		case TYPE_STRING:
			strcpy(returnConvert, "string");
		break;

		case TYPE_INT:
			strcpy(returnConvert, "int");
		break;

		case TYPE_DOUBLE:
			strcpy(returnConvert, "double");
		break;

		case TYPE_BOOL:
			strcpy(returnConvert, "bool");
		break;

		default:
			strcpy(returnConvert, "falha");
		break;
	}

	return returnConvert;
}

void printCalcStatements(type_values * expression1) {
	printTabs();
	printTypeValues(expression1);
	printBlankSpace();
	fprintf(fileOut, "=");
	printBlankSpace();
}
