#include "array_double.hpp"
#include <sstream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    string line;
    AirlinePassenger tempPass;
    input.open(queryParams[1]);
    if (input.is_open()) {
        recordIdx = 0;
        while (getline(input, line)) {
            stringstream ss;
            ss << line;
            tempPass.name=line.substr(0, line.find(','));
            line.erase(0, line.find(',')+1);
            tempPass.airline=line.substr(0, line.find(','));
            line.erase(0, line.find(',')+1);
            tempPass.location=line.substr(0, line.find(','));
            line.erase(0, line.find(',')+1);
            tempPass.age=stoi(line);
            if (isPassengerQueried(tempPass, queryParams[2], queryParams[3], stoi(queryParams[4]), stoi(queryParams[5]))) {
                addPassenger(passengers, tempPass, arrCapacity, recordIdx, doublingCounter);
            }
        }
    }

}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {
    if ((passenger.age>=startAge)&&(passenger.age<=endAge)&&(passenger.location==queryLocation)&&(passenger.airline==queryAirline)) {
        return true;
    }
    return false;
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {
    AirlinePassenger* temp = new AirlinePassenger[*arraySize * 2];
    for (int i=0; i<*arraySize; i++) {
        temp[i]=*&passengers[i];
    }
    *arraySize=*arraySize*2;
    delete[] *&passengers;
    passengers=temp;
    return;
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) {
   //TODO
   int *capacityPtr = &arrCapacity;
    if (recordIdx==arrCapacity) {
        doublingCounter++;
        resizeArr(passengers, capacityPtr);
    }
    passengers[recordIdx].name=airlinePassenger.name;
    passengers[recordIdx].airline=airlinePassenger.airline;
    passengers[recordIdx].location=airlinePassenger.location;
    passengers[recordIdx].age=airlinePassenger.age;
    recordIdx++;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) {
    bool swapped;
    AirlinePassenger temp;
    string tempName;
    for (int i=0; i<length-1; i++) {
        swapped=false;
        for (int j=0; j<length-1; j++) {
            if (passengers[j+1].age>passengers[j].age) {
                temp=passengers[j];
                passengers[j]=passengers[j+1];
                passengers[j+1]=temp;
                swapped=true;
            }
        }
        if (swapped==false) {
            break;
        }
    }
    for (int i=0; i<length-1; i++) {
        swapped=false;
        for (int j=0; j<length-1; j++) {
            if (passengers[j+1].age==passengers[j].age) {
                if (passengers[j+1].name<passengers[j].name) {
                    temp=passengers[j];
                    passengers[j]=passengers[j+1];
                    passengers[j+1]=temp;
                    swapped=true;
                }
            }
        }
        if (swapped==false) {
            break;
        }
    }
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {
    sortPassengers(passengers, numOfRecords);
    cout << "Queried Passengers" << endl;
    cout << "---------------------------------------" << endl;
    for (int i=0; i<numOfRecords; i++) {
        cout << passengers[i].name << " " << passengers[i].age << endl;
    }
}
