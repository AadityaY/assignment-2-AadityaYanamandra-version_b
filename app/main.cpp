#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    ifstream myFile;

    int capacity=10;
    AirlinePassenger *arr = new AirlinePassenger[10];
    AirlinePassenger tempPass;
    int arrDoubled=0;
    int i;
    string tempArr[6];
    tempArr[0]=string(argv[0]);
    tempArr[1]=string(argv[1]);
    tempArr[2]=string(argv[2]);
    tempArr[3]=string(argv[3]);
    tempArr[4]=string(argv[4]);
    tempArr[5]=string(argv[5]);
    parseFile(myFile, tempArr, arr, capacity, i, arrDoubled);
    
    cout << "Array doubled: " << arrDoubled << endl;
    cout << "Total number of passengers returned after the query: " << i << endl;
    printQueriedPassengers(arr, i);
    return 0;
}
