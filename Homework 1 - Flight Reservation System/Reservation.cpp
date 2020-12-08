#include <iostream>
using namespace std;
#include "Reservation.h"
// Olcaytu Gürkan 21903031

Reservation::Reservation(int passNum, int code, const int* rowArr, const char* seatArr) {
    seatRow = rowArr;
    seatCol = seatArr;
    reservationCode = code;
    numPassengers = passNum;
}

Reservation::Reservation() {
    reservationCode = 0;
    numPassengers = 0;
}

Reservation::~Reservation() {
}

int Reservation::getReservationCode() {
    return reservationCode;
}

int Reservation::getNoOfPassengers() {
    return numPassengers;
}

const int* Reservation::getSeatRow() {
    return seatRow;
}

const char* Reservation::getSeatCol() {
    return seatCol;
}
