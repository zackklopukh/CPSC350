// File processor reads the input text, creates the windows, customers and runs the simulation
#include "FileProcessor.h"
using namespace std;


FileProcessor::FileProcessor() {
}

FileProcessor::~FileProcessor() {
    delete myCenter;
}

void FileProcessor::processFile(string inFile) {

    ifstream textFile(inFile);

    //error checking one file will suffice
    if (!textFile.is_open()) {
        cerr << "Error in opening File." << endl;
    }

    //The first line will be the number of windows open at the registrar. 
    //The second line will be the number of windows open at the cashier. 
    //The third line will be the number of windows open at the financial aid office. 
    //add them to array, send them to create the ServiceCenter
    int windowNumArray[3];
    for (int i = 0; i < 3; ++i) {
        if (!(textFile >> windowNumArray[i])) {
            cerr << "Error reading integer from file.\n";
        }
    }
    myCenter = new ServiceCenter(windowNumArray[0], windowNumArray[1], windowNumArray[2]);


    //The next line will be the time (or clock tick) at which the next students arrive. 
        // we want to read this, run the simulation for this time, then reset it if there is another hour
    string currTime;
    string customerInfo;
    int numCustomers;
    int customers10Wait = 0;

    while (textFile >> currTime) { //first line gets the time
        textFile >> numCustomers; //this line gets the number of students

        Customer* *customerArray = new Customer*[numCustomers];

        for (int i = 0; i < numCustomers; ++i) {

            int timeArray[3];
            int timeOrder;
            for (int j = 0; j < 3; ++j) {
                textFile >> timeOrder;
                timeArray[j] = timeOrder;
            }

            char charArray[3];
            char charOrder;
            for (int j = 0; j < 3; ++j) {
                textFile >> charOrder;
                charArray[j] = charOrder;
            }
            
            Customer *tempCustomer = new Customer(charArray[0], charArray[1], charArray[2], timeArray[0], timeArray[1], timeArray[2]);
            customerArray[i] = tempCustomer;
        }
        //runSimulation();

        // RUN SIMULATION

        while (true) {

            for (int i = 0; i < numCustomers; ++i) {
                //for each customer, run what would have to happen. 
                //If finished skip
                //If inOffice, run tickinOffice
                //If not inOffice not finished, add to next Office

                if(customerArray[i]->isFinished) {
                    continue;
                }

                //Check if someone has 0 time for an office, or doesn't need to attend it
                while(customerArray[i]->timeQ[customerArray[i]->currOffice] == 0 && customerArray[i]->currOffice < 3) {
                    customerArray[i]->currOffice++;
                }
                if (customerArray[i]->currOffice > 2) {
                    customerArray[i]->isFinished = true;
                    continue;
                }

                
                if (!customerArray[i]->inOffice) {
                    switch(customerArray[i]->orderQ[customerArray[i]->currOffice]) {
                    case 'R':
                        customerArray[i]->inOffice = true;
                        myCenter->registrarOffice->addCustomerToQueue(customerArray[i]);
                        break;
                    case 'F':
                        customerArray[i]->inOffice = true;
                        myCenter->financialOffice->addCustomerToQueue(customerArray[i]);
                        break;
                    case 'C':
                        customerArray[i]->inOffice = true;
                        myCenter->cashierOffice->addCustomerToQueue(customerArray[i]);
                        break;
                    default:
                        cout << "Invalid choice." << endl;
                        break;
                    }
                }
            }

            myCenter->addQueueCustomersForAllOffices(); 
            //This makes it so everybody in queue for an Office will go
            //To a window if avaiable


            //Now everybody is in their correct location
            // run the tick in time

            // this will give idleTicks for people in queues
            for (int i = 0; i < numCustomers; ++i) {
                if(!customerArray[i]->isFinished && !customerArray[i]->atWindow && customerArray[i]->inOffice) {
                    customerArray[i]->idleTime++;
                }
            }

            //this will simulate a tick for all windows
            myCenter->simTick();

            //check if all poeple are finished
            int finishedCustomers = 0;
            for (int i = 0; i < numCustomers; ++i) {
                if (customerArray[i]->isFinished)
                    finishedCustomers++;
            }
            if (finishedCustomers >= numCustomers)
                break;
        }

        //check how many people waited 10+ ticks
        for (int i = 0; i < numCustomers; ++i) {
            if (customerArray[i]->totIdleTime > 9) {
                customers10Wait++;
            }
        }

        delete[] customerArray;
    }
    
    stringstream outFileText;
    outFileText << "\nCashier's Office:\n";
    outFileText << myCenter->cashierOffice->printStats();
    outFileText << "\nFinancial Aid's Office:\n";
    outFileText << myCenter->financialOffice->printStats();
    outFileText << "\nRegistrar's Office:\n";
    outFileText << myCenter->registrarOffice->printStats();

    outFileText << "\nNumber of students waiting over 10 minutes across all offices: " << customers10Wait << " tick(s)\n";
    outFileText << "Number of windows idle for over 5 minutes across all offices: " << myCenter-> totWindow5Plus() << " tick(s)\n\n";

    cout << outFileText.str();
}
