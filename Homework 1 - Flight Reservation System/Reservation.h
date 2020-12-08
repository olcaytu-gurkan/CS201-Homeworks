#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED
// Olcaytu Gürkan 21903031

class Reservation {
public:
    Reservation();
    Reservation(int numPassengers, int code, const int* rowArr, const char* colArr);
    ~Reservation();
    int getReservationCode();
    int getNoOfPassengers();
    const int* getSeatRow();
    const char* getSeatCol();
private:
    int reservationCode;
    const int* seatRow;
    const char* seatCol;
    int numPassengers;
};


#endif // RESERVATION_H_INCLUDED
