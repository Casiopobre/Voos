#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Date{
    int day;
    int month;
    int year;
} Date;

typedef struct Passenger{
    char name[50];
    Date birth;
    int ID;
    char email[50];
} Passenger;

typedef struct Booking{
    Passenger client;
    char ref_num[10];
    int seat_num;
} Booking;

typedef struct Flights{
    char ref_num[15];
    char company[20];
    Date date;
    char departure_time[10];
    char departure_airport[20];
    char destination[20];
    float price;
    int total_seats;
    int remaining_seats;
} Flights;

typedef struct STVECTOR{
    Flights *vector_flight;
    int vector_size;
} STVECTOR;

typedef struct STVECTOR_B{
    Booking *vector_booking;
    int vector_size;
} STVECTOR_B;

#endif // STRUCTURES_H
