#include "Model.h"
#include "FileProcessor.h"
#include "Translator.h"

int main(int argc, char **argv) {
    FileProcessor fileProcessor;
    fileProcessor.processFile("test.txt", "translatedNice.html");
    return 0;
}
