#ifndef FLIGHT_H_INCLUDED
#define FLIGHT_H_INCLUDED
// Olcaytu Gürkan 21903031

#include <string>
#include "Reservation.h"
class Flight {
public:
    Flight();
    Flight(int flightNo, int rowNo, int seatNo);
    ~Flight();
    int getFlightNumber();
    int getAvailableSeats();
    int getRowNo();
    int getSeatsInRow();
    void addPassengers(const int noOfPassengers);
    bool resCodeExist(int code);
    void addReservation(int flightNo, const int numOfPassengers, const int*& seatRow, const char*& seatCol, int code);
    bool existingSeat(string s);
    Reservation* getReservations();
    int getNoOfReservations();;
    void cancelledPassengers(int noOfPassengers);
    string* createRowArr();
    string* createColArr();
    string* getAllocatedSeats();
    void setAllocatedSeats(string* inp);
    int getNoOfAllocatedSeats();
private:
    int flightNumber;
    int noOfRowsInAircraft;
    int noOfSeatsInRow;
    int totalSeats;
    string* allocatedSeats;
    int noOfAllocatedSeats;
    int availableSeats;
    Reservation* reservations;
    int noOfReservations;
};

#endif // FLIGHT_H_INCLUDED
