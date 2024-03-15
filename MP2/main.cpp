#include "World.h"
#include "FileProcessor.h"

int main(int argc, char **argv) {

    FileProcessor *fp = new FileProcessor();

    fp->processFile();
    //fp->processFile();

    delete fp;
    //World *testWorld = new World(3, 5, 3, 20, 20, 20, 20, 20);
    //delete testWorld;
    return 0;
}