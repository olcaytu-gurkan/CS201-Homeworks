#include <iostream>
#include <stdlib.h>
using namespace std;
#include "ReservationSystem.h"
// Olcaytu Gürkan 21903031

ReservationSystem::ReservationSystem() {
    allFlights = NULL;
    noOfFlights = 0;
}

ReservationSystem::~ReservationSystem() {
    delete [] allFlights;
}

void ReservationSystem::addFlight(const int flightNo, const int rowNo, const int seatNo) {
    if (rowNo <= 0 || seatNo <= 0) {
        cout << "Invalid row/seat numbers given." << endl;
        return;
    }
    if (noOfFlights == 0) {
        delete [] allFlights;
        noOfFlights++;
        allFlights = new Flight[noOfFlights];
        Flight firstFlight(flightNo, rowNo, seatNo);
        allFlights[0] = firstFlight;
        cout << "Flight " << flightNo << " has been added." << endl;
    }
    else {
        for (int i = 0; i < noOfFlights; i++) {
            if (allFlights[i].getFlightNumber() == flightNo) {
                cout << "Flight "<< flightNo << " already exists." << endl;
                return;
            }
        }
        noOfFlights++;
        Flight* temp = new Flight[noOfFlights];
        Flight newFlight(flightNo, rowNo, seatNo);
        for (int i = 0; i < noOfFlights - 1; i++) {
            temp[i] = allFlights[i]; //copying contents of original flight
        }
        delete [] allFlights;
        temp[noOfFlights - 1] = newFlight;
        allFlights = temp;
        cout << "Flight " << flightNo << " has been added." << endl;
    }
}

void ReservationSystem::cancelFlight(const int flightNo) {
    bool found = false;
    int positionOfFlight = 0;
    for (int i = 0; i < noOfFlights && !found; i++) {
        if (allFlights[i].getFlightNumber() == flightNo){
            found = true;
            positionOfFlight = i;
        }
    }
    if (found) {
        Flight* temp = new Flight[noOfFlights - 1];
        int j = 0;
        for (int i = 0; i < noOfFlights; i++) {
            if (i != positionOfFlight) {
                temp[j] = allFlights[i]; //copying flights if is not equal to going-to-deleted flight
                j++;
            }
        }
        delete[] allFlights[positionOfFlight].getAllocatedSeats();
        delete[] allFlights[positionOfFlight].getReservations();
        delete[] allFlights;
        noOfFlights--;
        allFlights = temp;
        cout << "Flight " << flightNo << " and all of its reservations are canceled." << endl;
    }
    else {
        cout << "Error, flight " << flightNo << " doesn't exist." << endl;
    }
}

void ReservationSystem::showAllFlights() {
    if (noOfFlights == 0)
        cout << "There are no flights operated currently." << endl;
    else
        cout << "Currently operated flights:" << endl;
    for (int i = 0; i < noOfFlights; i++) {
        cout << "Flight " << allFlights[i].getFlightNumber() << " (" << allFlights[i].getAvailableSeats() << " available seats)" << endl;
    }
}

void ReservationSystem::showFlight(const int flightNo) {
    bool found = false;
    int positionOfFlight = 0;
    for (int i = 0; i < noOfFlights && !found; i++) {
        if (allFlights[i].getFlightNumber() == flightNo){
            found = true;
            positionOfFlight = i;
        }
    }
    if (found == false) {
        cout << "Flight "<< flightNo << " does not exist." << endl;
    }
    else {
        string* pos = allFlights[positionOfFlight].createRowArr(); // created those arrays to convert user given reservations to string in heap.
        string* col = allFlights[positionOfFlight].createColArr();
        cout << "Flight " << flightNo << " has " << allFlights[positionOfFlight].getAvailableSeats() << " available seats." << endl;
        int seatNo = allFlights[positionOfFlight].getSeatsInRow();
        int rowNo = allFlights[positionOfFlight].getRowNo();
        cout << "   ";
        for (int i = 0; i < seatNo; i++) {
            cout << col[i] << "  ";
        }
        cout << endl;
        delete[] col;

        for (int i = 0; i < rowNo; i++) {
            int y = i + 1;
            cout << y << "  ";
            for (int j = 0; j < seatNo; j++) {
                if (allFlights[positionOfFlight].existingSeat(pos[i] + ((char)('A' + j )))) //converting reservations to string and concetaneting
                    cout << "x  ";
                else
                    cout << "o  ";
            }
            cout << endl;
        }
        delete[] pos;
    }
}

int ReservationSystem::makeReservation(const int flightNo, const int numPassengers, const int *seatRow, const char *seatCol) {
    bool found = false;
    int code = 0;
    int positionOfFlight = 0;
    for (int i = 0; i < noOfFlights && !found; i++) {
        if (allFlights[i].getFlightNumber() == flightNo){
            found = true;
            positionOfFlight = i;
        }
    }
    if (found == false) {
        cout << "This flight does not exist." << endl;
        code = -1;
        return code;
    }
    else {
        string* pos = allFlights[positionOfFlight].createRowArr();
        bool aChecker = false;
        for (int i = 0; i < numPassengers; i++) {
            if (allFlights[positionOfFlight].existingSeat(pos[seatRow[i] - 1] + seatCol[i])) { // checking if seat exists
                cout << seatRow[i] << "" << seatCol[i] << " is not available." << endl;
                aChecker = true;
            }
        }
        delete[] pos;
        if (aChecker)
            return -1;
        bool similarityCheck = true;
        int simCount;
        while (similarityCheck) { //randomly generating a code and checking if that code exists on flight.
            simCount = 0;
            code = rand() % 2000;
            for (int i = 0; i < noOfFlights; i++) {
                if (!(allFlights[i].resCodeExist(code))) {
                    simCount++;
                }
            }
            if (simCount == noOfFlights) {
                similarityCheck = false;
            }
        }
        allFlights[positionOfFlight].addPassengers(numPassengers);
        allFlights[positionOfFlight].addReservation(flightNo, numPassengers, seatRow, seatCol, code);
        return code;
    }
}

void ReservationSystem::cancelReservation(const int resCode) {
    int positionOfFlight;
    bool found = false;
    int positionOfRes;
    for (int i = 0; i < noOfFlights; i++) {
        for (int j = 0; j < allFlights[i].getNoOfReservations() && !found; j++) {
            if ((allFlights[i].getReservations())[j].getReservationCode() == resCode) {
                positionOfFlight = i;
                found = true;
                positionOfRes = j;
            }
        }
    }
    if (!found) {
        cout << "No reservations under Code " << resCode << endl;
    }
    else {
        string* pos = allFlights[positionOfFlight].createRowArr();
        int flightSize = allFlights[positionOfFlight].getNoOfAllocatedSeats();
        int noOfPassengers = (allFlights[positionOfFlight].getReservations())[positionOfRes].getNoOfPassengers();
        int tempSize = flightSize - noOfPassengers;
        string* temp = new string[tempSize];
        string* resArr = new string[noOfPassengers];
        for (int j = 0; j < noOfPassengers; j++) {
            resArr[j] = (pos[allFlights[positionOfFlight].getReservations()[positionOfRes].getSeatRow()[j] - 1]+ allFlights[positionOfFlight].getReservations()[positionOfRes].getSeatCol()[j]);

        }
        int tempIndice = 0;
        delete[] pos;
        for (int i = 0; i < allFlights[positionOfFlight].getNoOfAllocatedSeats(); i++) {
            bool finder = false;
            for (int j = 0; j < noOfPassengers; j++) {
                if (allFlights[positionOfFlight].getAllocatedSeats()[i] == resArr[j]) {
                    finder = true;
                }
            }
            if (finder == false) {
                temp[tempIndice] = allFlights[positionOfFlight].getAllocatedSeats()[i];
                tempIndice++;
            }
        }
        cout << "Reservations for the seats ";
        for (int i = 0; i < noOfPassengers; i++) {
            cout << resArr[i] + " ";
        }
        cout << "are cancelled in Flight " << allFlights[positionOfFlight].getFlightNumber() << endl;
        allFlights[positionOfFlight].cancelledPassengers(noOfPassengers);
        delete[] (allFlights[positionOfFlight].getAllocatedSeats());
        allFlights[positionOfFlight].setAllocatedSeats(temp);
        delete [] resArr;
    }
 }

 void ReservationSystem::showReservation(const int resCode) {
    int positionOfFlight;
    bool found = false;
    int positionOfRes;
    for (int i = 0; i < noOfFlights; i++) {
        for (int j = 0; j < allFlights[i].getNoOfReservations(); j++) {
            if ((allFlights[i].getReservations())[j].getReservationCode() == resCode) {
                positionOfFlight = i;
                found = true;
                positionOfRes = j;
            }
        }
    }
    if (!found) {
        cout << "No reservations under Code " << resCode << endl;
    }
    else {
        string s = "";
        string* pos = allFlights[positionOfFlight].createRowArr();
        for (int j = 0; j <(allFlights[positionOfFlight].getReservations())[positionOfRes].getNoOfPassengers(); j++) {
            s = s + (pos[allFlights[positionOfFlight].getReservations()[positionOfRes].getSeatRow()[j] - 1] + allFlights[positionOfFlight].getReservations()[positionOfRes].getSeatCol()[j]) + " ";
        }
        cout << "Reservations under Code " << resCode << " in Flight " << allFlights[positionOfFlight].getFlightNumber() << ": " << s << endl;
        delete[] pos;
    }

 }

