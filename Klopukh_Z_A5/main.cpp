#include "lazyBST.h"
#include "Student.h"
#include "Faculty.h"
#include "database.h"

int main() {
    database *db = new database(); //create the database
    db->runProgram(); //run program
    delete db; // don't forget to delete
}