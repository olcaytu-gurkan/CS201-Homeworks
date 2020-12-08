#include <iostream>
using namespace std;
#include "Flight.h"
// Olcaytu Gürkan 21903031

Flight::Flight() {
    flightNumber = 0;
    noOfRowsInAircraft = 0;
    noOfSeatsInRow = 0;
    totalSeats =  0;
    noOfAllocatedSeats = 0;
    allocatedSeats = NULL;
    availableSeats = totalSeats;
    reservations = NULL;
    noOfReservations = 0;
}
Flight::Flight(int flightNo, int rowNo, int seatNo) {
    flightNumber = flightNo;
    noOfRowsInAircraft = rowNo;
    noOfSeatsInRow = seatNo;
    totalSeats = rowNo * seatNo;
    noOfAllocatedSeats = 0;
    allocatedSeats = NULL;
    availableSeats = totalSeats;
    reservations = NULL;
    noOfReservations = 0;
}

Flight::~Flight() {
}

int Flight::getFlightNumber() {
    return flightNumber;
}

int Flight::getAvailableSeats() {
    return availableSeats;
}

int Flight::getRowNo() {
    return noOfRowsInAircraft;
}

int Flight::getSeatsInRow() {
    return noOfSeatsInRow;
}
void Flight::cancelledPassengers(int noOfPassengers) {
    availableSeats = availableSeats + noOfPassengers;
    noOfAllocatedSeats = noOfAllocatedSeats - noOfPassengers;
    noOfReservations--;
}

void Flight::addPassengers(int noOfPassengers) {
    availableSeats = availableSeats - noOfPassengers;
    noOfReservations++;
}

bool Flight::resCodeExist(int code) {
    for (int i = 0; i < noOfReservations; i++) {
        if (reservations[i].getReservationCode() == code) {
            return true;
        }
    }
    return false;
}

void Flight::addReservation(int flightNo, const int numOfPassengers, const int*& seatRow, const char*& seatCol, int code) {
    if (reservations == NULL) {
        reservations = new Reservation[1];
        reservations[0] = Reservation(numOfPassengers,code, seatRow, seatCol);
    }
    else {
        Reservation* temp = new Reservation[noOfReservations];
        for (int i = 0; i < noOfReservations-1; i++) {
            temp[i] = reservations[i];
        }
        temp[noOfReservations-1] = Reservation(numOfPassengers, code, seatRow, seatCol);
        delete[] reservations;
        reservations = temp;
    }
    if (noOfAllocatedSeats == 0) {
        string* pos = (*this).createRowArr();
        allocatedSeats = new string[numOfPassengers];
        for (int i = 0; i < numOfPassengers; i++) {
            allocatedSeats[i] = pos[seatRow[i]-1] + seatCol[i];
            noOfAllocatedSeats++;
        }
        delete[] pos;
    }
    else {
        string* temp = new string[noOfAllocatedSeats + numOfPassengers];
        for (int i = 0; i < noOfAllocatedSeats; i++) {
            temp[i] = allocatedSeats[i];
        }
        int k = 0;
        int initialValue = noOfAllocatedSeats;
        string* pos = (*this).createRowArr();
        for (int j = noOfAllocatedSeats; j < numOfPassengers + initialValue; j++) {
            temp[j] = pos[seatRow[k] - 1]+ seatCol[k];
            noOfAllocatedSeats++;
            k++;
        }
        delete[] allocatedSeats;
        delete[] pos;
        allocatedSeats = temp;
    }

}

bool Flight::existingSeat(string s) {
    for (int i = 0; i < noOfAllocatedSeats; i++) {
        if (allocatedSeats[i] == s)
            return true;
    }
    return false;
}

Reservation* Flight::getReservations() {
    return reservations;
}

int Flight::getNoOfReservations() {
    return noOfReservations;
}

string* Flight::createRowArr() {
    string* s = new string[22];
    s[0] = "1"; s[1] = "2"; s[2] = "3"; s[3] = "4"; s[4] = "5"; s[5] = "6"; s[6] = "7"; s[7] = "8"; s[8] = "9"; s[9] = "10"; s[10] = "11";
    s[11] = "12"; s[12] = "13"; s[13] = "14"; s[14] = "15"; s[15] = "16"; s[16] = "17"; s[17] = "18"; s[18] = "19"; s[19] = "20"; s[20] = "21"; s[21] = "22";
    return s;
}

string* Flight::createColArr() {
    string* s = new string[26];
    s[0] = "A"; s[1] = "B"; s[2] = "C"; s[3] = "D"; s[4] = "E"; s[5] = "F"; s[6] = "G"; s[7] = "H"; s[8] = "I"; s[9] = "J"; s[10] = "K";
    s[11] = "L"; s[12] = "M"; s[13] = "N"; s[14] = "O"; s[15] = "P"; s[16] = "Q"; s[17] = "R"; s[18] = "S"; s[19] = "T"; s[20] = "U"; s[21] = "V";
    s[22] = "W"; s[23] = "X"; s[24] = "Y"; s[25] = "Z";
    return s;
}

string* Flight::getAllocatedSeats() {
    return allocatedSeats;
}

void Flight::setAllocatedSeats(string* inp) {
    allocatedSeats = inp;
}

int Flight::getNoOfAllocatedSeats() {
    return noOfAllocatedSeats;
}
