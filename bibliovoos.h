#ifndef BIBLIOVOOS_H
#define BIBLIOVOOS_H
#include "structures.h"

/**
 * Imprime os voos almacenados no vector de estruturas
 * 
 * @param totalVector Punteiro ao vector de voos que queremos imprimir
*/
void print_flights(STVECTOR *totalVector);


/**
 * Imprime as reservas almacenadas no vector de estruturas
 * 
 * @param totalVectorB Punteiro ao vector de reservas que queremos imprimir
*/
void print_bookings(STVECTOR_B *totalVectorB);


/**
 * Le o arquivo de voos e almacena os datos nun vector de estruturas
 * 
 * @param fileName Nome do arquivo que queremos ler
 * @param totalVector Punteiro ao vector de estructuras onde imos gardar os datos
*/
void read_flights(char *fileName, STVECTOR *totalVector);


/**
 * Le o arquivo de reservas e almacena os datos nun vector de estruturas
 * 
 * @param fileName Nome do arquivo que queremos ler
 * @param totalVector Punteiro ao vector de estructuras onde imos gardar os datos
*/
void read_bookings(char fileName[], STVECTOR_B *totalVectorB);


/**
 * Comproba se o voo se atopa no vector de estruturas
 * 
 * @param totalVectorF Punteiro ao vector de estructuras onde queremos buscar o voo
 * @param totalVectorB Punteiro ao vector de estructuras onde queremos buscar o voo
 * @param ref_num Numero de referencia do voo que queremos buscar
 * @param mode Modo de traballo: 0 para buscar nun vector de voos, 1 para buscar nun vector de reservas
 * @return Devolve o indice onde se atopa o voo solicitado, ou -1 se non o atopa
*/
int check_flight(STVECTOR *totalVectorF, STVECTOR_B *totalVectorB, char *ref_num, int mode);

/**
 * Comproba se o voo se atopa no vector de estruturas
 * 
 * @param totalVectorB Punteiro ao vector de estructuras onde queremos buscar o usuario
 * @param passenger_ID Numero de identificacion do usuario que queremos buscar
*/
int check_userID(STVECTOR_B *totalVectorB, int passenger_ID);

/**
 * Asigna un numero de asento aleatorio (do 1 ao 118)
*/
void assign_random_seat_num(STVECTOR_B *totalVectorB, int posB, char *ref_num);

/**
 * Modifica os vectores para engadir unha nova reserva de voo
 * 
 * @param totalVectorF Punteiro ao vector de voos
 * @param totalVectorB Punteriro ao vector de reservas 
 * @param ref_num Numero de referencia para buscar o voo que se vai reservar
*/
void book_flight(STVECTOR *totalVectorF, STVECTOR_B *totalVectorB, char *ref_num);

/**
 * Modifica os vectores para engadir unha nova reserva de voo
 * 
 * @param totalVectorF Punteiro ao vector de voos
 * @param totalVectorB Punteriro ao vector de reservas 
 * @param ref_num Numero de referencia do voo que se quere cancelar
 * @param passenger_ID Documento de identidade do pasaxeiro que quere cancelar o voo
*/
void cancel_flight(STVECTOR *totalVectorF, STVECTOR_B *totalVectorB, int passenger_ID, char *ref_num);

/**
 * Imprime por pantalla todos os voos que teñan asentos dispoñibles
 * 
 * @param totalVector Punteiro ao vector de voos
*/
void show_aviable_flights(STVECTOR *totalVector);

/**
 * Imprime por pantalla todos os voos que teñan asentos dispoñibles
 * 
 * @param totalVectorB Punteiro ao vector de reservas
 * @param passenger_ID Documento de identidade do pasaxeiro do que queremos coñecer as reservas (se e 0, amosanse todas as reservas)
*/
void show_user_bookings(STVECTOR_B *totalVectorB, int passenger_ID);


#endif // BIBLIOVOOS_H