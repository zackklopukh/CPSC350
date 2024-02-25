#include "Translator.h"
#include "Model.h"

Translator::Translator() {
    myModel = new Model();
    //default constructor
}

Translator::~Translator() {
    delete myModel;
    //default destructor
}

string Translator::translateEnglishWord(string input) {

    string defaultWord = input;
    string translatedWord = "";

    for (int i = 0; i < defaultWord.size(); ++i) {
        if (isalpha(defaultWord[i])) { //double check these are letters
            if (tolower(defaultWord[i]) == 'a' || tolower(defaultWord[i]) == 'e' || tolower(defaultWord[i]) == 'i' || tolower(defaultWord[i]) == 'o' || tolower(defaultWord[i]) == 'u') {
                translatedWord += myModel->translateSingleVowel(defaultWord[i]);
                //translate vowels using model class
            } else {
                translatedWord += myModel->translateSingleConsonant(defaultWord[i]);
                // translate consonants using model class
            }
        } else { //this else is used with non-letter chars e.i (%$@|*%{})
            translatedWord += defaultWord[i];
        }
    }

    return translatedWord;

}

string Translator::translateEnglishSentence(string input) {

    string sentence = input;
    string word = "";
    string translatedSentence = "";

    for (int i = 0; i < sentence.size(); ++i) {
        if (sentence[i] != ' ' || !ispunct(sentence[i])) {
            //if there is no break in a word, continue to add to the string
            word += sentence[i];
        } else {
        // once there is a break, translate using translateEnglishWord() and add the punct char
           translatedSentence += this->translateEnglishWord(word) + sentence[i];
           word = "";
        }
    }

    translatedSentence += this->translateEnglishWord(word);
    //runs if a word is the last part of the text with no punct or space

    return translatedSentence;
}