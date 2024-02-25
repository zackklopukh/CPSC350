#include "Model.h"

Model::Model() {
}

Model::~Model() {
}

string Model::translateSingleConsonant(char c) {
    char letter = c;
    string translated = "";
    translated += letter;
    translated += "o";
    translated += tolower(c=letter);

    return translated;
}

string Model::translateSingleVowel(char c) {
    char letter = c;
    string translated = "";
    translated += letter;
    return translated;
}