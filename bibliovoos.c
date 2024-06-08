#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"

void print_flights(STVECTOR *totalVector){
    printf("\033[1;34m");
    printf("\n~*~*~*~*~*~*~*~*~*~*~*~*~*~*~ Lista de voos: ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    for(int i = 0; i < totalVector->vector_size; i++){
        printf("%s, %s, %d-%d-%d, %s, %s, %s, %.2f, %d, %d\n", totalVector->vector_flight[i].ref_num, totalVector->vector_flight[i].company, totalVector->vector_flight[i].date.year, totalVector->vector_flight[i].date.month, totalVector->vector_flight[i].date.day, 
        totalVector->vector_flight[i].departure_time, totalVector->vector_flight[i].departure_airport, totalVector->vector_flight[i].destination, totalVector->vector_flight[i].price, totalVector->vector_flight[i].total_seats, totalVector->vector_flight[i].remaining_seats);
    }
    printf("\033[1;0m");
}

void print_bookings(STVECTOR_B *totalVectorB){
    printf("\033[1;34m");
    printf("\n~*~*~*~*~*~*~*~*~*~*~*~ Lista de reservas: ~*~*~*~*~*~*~*~*~*~*~*~\n");
    for(int i = 0; i < totalVectorB->vector_size; i++){
        printf("%s %d-%d-%d %d %s %s %d\n", totalVectorB->vector_booking[i].client.name, totalVectorB->vector_booking[i].client.birth.year, totalVectorB->vector_booking[i].client.birth.month, totalVectorB->vector_booking[i].client.birth.day, 
        totalVectorB->vector_booking[i].client.ID, totalVectorB->vector_booking[i].client.email, totalVectorB->vector_booking[i].ref_num, totalVectorB->vector_booking[i].seat_num);

    }
    printf("\033[1;0m");
}

void read_flights(char fileName[], STVECTOR *totalVector){
    // Abrimos o arquivo
    FILE* flights_file = fopen(fileName, "r");
    if (flights_file == NULL){
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }

    // Contamos as lineas do arquivo
    fseek(flights_file, 0, SEEK_SET); 
    int lineas = 0;
    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), flights_file) != NULL){
        lineas++;
    }

    // Creamos o vector para almacenar os datos (reserva de memoria)
    totalVector->vector_flight = malloc((lineas - 1) * sizeof(Flights));
    if(totalVector->vector_flight == NULL){
        perror("Erro ao asignar a memoria dinamica\n");
        exit(EXIT_FAILURE);
    }

    // Volvemos ao inicio do arquivo
    fseek(flights_file, 0, SEEK_SET); 
    
    // Ignoramos a cabeceira
    fgets(buffer, sizeof(buffer), flights_file);

    
    // Lemos cada linea do arquivo
    for (int i = 0; i < lineas-1; i++){
        fgets(buffer, sizeof(buffer), flights_file);
        sscanf(buffer, "%s %s %d-%d-%d %s %s %s %f %d %d", totalVector->vector_flight[i].ref_num, totalVector->vector_flight[i].company, &totalVector->vector_flight[i].date.year, &totalVector->vector_flight[i].date.month, &totalVector->vector_flight[i].date.day, 
        totalVector->vector_flight[i].departure_time, totalVector->vector_flight[i].departure_airport, totalVector->vector_flight[i].destination, &totalVector->vector_flight[i].price, &totalVector->vector_flight[i].total_seats, &totalVector->vector_flight[i].remaining_seats);
    }
    totalVector->vector_size = lineas - 1;   
    
    // Pechamos o arquivo  
    fclose(flights_file);

    print_flights(totalVector);
}

void read_bookings(char fileName[], STVECTOR_B *totalVectorB){
    // Abrimos o arquivo
    FILE* bookings_file = fopen(fileName, "r");
    if (bookings_file == NULL){
        perror("Erro ao abrir o arquivo\n");
        exit(EXIT_FAILURE);
    }
    // Contamos as lineas do arquivo
    fseek(bookings_file, 0, SEEK_SET); 
    int lineas = 0;
    char buffer[1024];
    while(fgets(buffer, sizeof(buffer), bookings_file) != NULL){
        lineas++;
    }

    // Creamos o vector para almacenar os datos (reserva de memoria)
    totalVectorB->vector_booking = malloc((lineas - 1) * sizeof(Booking));
    if(totalVectorB->vector_booking == NULL){
        perror("Erro ao asignar a memoria dinamica\n");
        exit(EXIT_FAILURE);
    }

    // Volvemos ao inicio do arquivo
    fseek(bookings_file, 0, SEEK_SET); 
    
    // Ignoramos a cabeceira
    fgets(buffer, sizeof(buffer), bookings_file);

    // Lemos o arquivo gardando os datos no vector de estruturas
    for(int i = 0; i < lineas-1; i++){
        fgets(buffer, sizeof(buffer), bookings_file);
        sscanf(buffer, "%s %d-%d-%d %d %s %s %d", totalVectorB->vector_booking[i].client.name, &totalVectorB->vector_booking[i].client.birth.year, &totalVectorB->vector_booking[i].client.birth.month, &totalVectorB->vector_booking[i].client.birth.day, 
        &totalVectorB->vector_booking[i].client.ID, totalVectorB->vector_booking[i].client.email, totalVectorB->vector_booking[i].ref_num, &totalVectorB->vector_booking[i].seat_num);
    }
    totalVectorB->vector_size = lineas - 1;

    // Pechamos o arquivo
    fclose(bookings_file);

    print_bookings(totalVectorB);
}

int check_flight(STVECTOR *totalVectorF, STVECTOR_B *totalVectorB, char *ref_num, int mode){
    if(mode == 0){
        for(int i = 0; i  < totalVectorF->vector_size; i++){
            if(strcmp(ref_num, totalVectorF->vector_flight[i].ref_num) == 0)
                return i;
        }
    }
    else if(mode == 1){
        for(int i = 0; i < totalVectorB->vector_size; i++){
            if(strcmp(ref_num, totalVectorB->vector_booking[i].ref_num) == 0)
                return i;
        }
    }
    return -1;
}

int check_userID(STVECTOR_B *totalVectorB, int passenger_ID){
    for(int i = 0; i < totalVectorB->vector_size; i++){
        if(totalVectorB->vector_booking[i].client.ID == passenger_ID)
            return i;
    }
    return -1;
}

void assign_random_seat_num(STVECTOR_B *totalVectorB, int posB, char *refNum){
    // Xeramos un numero aleatorio para determinar o numero de asento
    srand(time(0));
    int num = (rand() % (117 - 0 + 1)) + 0;
    for(int i = 0; i < totalVectorB->vector_size; i++){
        while(strcmp(refNum, totalVectorB->vector_booking[i].ref_num) == 1 && totalVectorB->vector_booking[i].seat_num == num){
            srand(time(0));
            num = (rand() % (117 - 0 + 1)) + 0;
        }
    }
    totalVectorB->vector_booking[posB].seat_num = num;
}

void book_flight(STVECTOR *totalVectorF, STVECTOR_B *totalVectorB, char *ref_num){
    // Comprobamos que o voo solicitado polo usuario exista teña asentos dispoñibles
    int posV = check_flight(totalVectorF, totalVectorB, ref_num, 0);
    if(posV == -1){ 
        printf("\033[1;33m");
        printf("\nO voo solicitado non existe :(");
        printf("\033[1;0m");
        return;
    }
    if(totalVectorF->vector_flight[posV].remaining_seats == 0){
        printf("\033[1;33m");
        printf("\nNon quedan prazas dispoñibles para o voo solicitado :(\n");
        printf("\033[1;0m");
        return;
    }

    // Cambiamos o numero de prazas dispoñibles no vector de voos
    totalVectorF->vector_flight[posV].remaining_seats -= 1;
    
    // Facemos un realloc (reservamos memoria para a nova reserva)
    totalVectorB->vector_size += 1;
    totalVectorB->vector_booking = realloc(totalVectorB->vector_booking, sizeof(*totalVectorB->vector_booking) * totalVectorB->vector_size);

    // Pedimos os datos ao cliente para formalizar a reserva
    int posB = totalVectorB->vector_size - 1;

    // Escaneamos os datos proporcionados polo usuario
    printf("\033[0;34m");
    printf("\nIntroduza o seu nome e apelido (Nome_Apelido): ");
    printf("\033[1;0m");
    scanf("%s", totalVectorB->vector_booking[posB].client.name);
    printf("\033[0;34m");
    printf("\nIntroduza a sua data de nacemento (dd/mm/aaaa): ");   
    printf("\033[1;0m"); 
    scanf("%d/%d/%d", &totalVectorB->vector_booking[posB].client.birth.day, &totalVectorB->vector_booking[posB].client.birth.month, &totalVectorB->vector_booking[posB].client.birth.year);
    printf("\033[0;34m");
    printf("\nIntroduza o seu documento de identidade (9 dixitos): ");
    printf("\033[1;0m");
    scanf("%d", &totalVectorB->vector_booking[posB].client.ID);
    printf("\033[0;34m");
    printf("\nIntroduza o seu email: ");
    printf("\033[1;0m");
    scanf("%s", totalVectorB->vector_booking[posB].client.email);
    
    // Asignamos o numero de voo e de asento
    strcpy(totalVectorB->vector_booking[posB].ref_num, ref_num);

    assign_random_seat_num(totalVectorB, posB, ref_num);
    
    print_bookings(totalVectorB);
    print_flights(totalVectorF);
    printf("\n --------------------------------------------x-----------------------------------------------\n");
    printf("\033[1;34m");
    printf("\nO seu numero de voo e: %s", totalVectorB->vector_booking[posB].ref_num);
    printf("\nO seu numero de asento e: %d", totalVectorB->vector_booking[posB].seat_num);
    printf("\033[1;0m");

}

void cancel_flight(STVECTOR *totalVectorF, STVECTOR_B *totalVectorB, int passenger_ID, char *ref_num){
    // Comprobamos que o ID do ususario exista na nosa "base de datos"
    if(check_userID(totalVectorB, passenger_ID) == -1){
        printf("\033[1;33m");
        printf("\n O numero de identificacion proporcionado non se atopa na nosa base de datos :(\n");
        printf("\033[1;0m");
        return;
    }
    // Comprobamos que o voo exista
    int posV = check_flight(totalVectorF, totalVectorB, ref_num, 1);
    if(posV == -1){ 
        printf("\033[1;33m");
        printf("\nO voo solicitado non existe :(");
        printf("\033[1;0m");
        return;
    }
    // Comprobamos que o cliente teña unha reserva para o voo especificado
    for(int i = 0; i < totalVectorB->vector_size; i++){
        if((totalVectorB->vector_booking[i].client.ID == passenger_ID) && strcmp(totalVectorB->vector_booking[i].ref_num, ref_num) != 0){
            printf("\033[1;33m");
            printf("\nVostede non ten ningunha reserva feita para o voo %s :(\n", ref_num);
            printf("\033[1;0m");
            return;
        } else if((totalVectorB->vector_booking[i].client.ID == passenger_ID) && strcmp(totalVectorB->vector_booking[i].ref_num, ref_num) == 0){

        }
    }
}

void show_aviable_flights(STVECTOR *totalVector){
    printf("\033[1;34m");
    printf("\n~*~*~*~*~*~*~*~*~*~*~*~*~*~*~ Lista de voos disponibles: ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~\n");
    for(int i = 0; i < totalVector->vector_size; i++){
        if(totalVector->vector_flight[i].remaining_seats != 0){
            printf("%s, %s, %d-%d-%d, %s, %s, %s, %.2f, %d, %d\n", totalVector->vector_flight[i].ref_num, totalVector->vector_flight[i].company, totalVector->vector_flight[i].date.year, totalVector->vector_flight[i].date.month, totalVector->vector_flight[i].date.day, 
            totalVector->vector_flight[i].departure_time, totalVector->vector_flight[i].departure_airport, totalVector->vector_flight[i].destination, totalVector->vector_flight[i].price, totalVector->vector_flight[i].total_seats, totalVector->vector_flight[i].remaining_seats);
        }
    }
    printf("\033[1;0m");
}

void show_user_bookings(STVECTOR_B *totalVectorB, int passenger_ID){
    // Si se pasa un 0, amosanse todas as reservas
    if(passenger_ID == 0){
        print_bookings(totalVectorB);
        return;
    }
    // Comprobamos que o ID do ususario exista na nosa "base de datos"
    if(check_userID(totalVectorB, passenger_ID) == -1){
        printf("\033[1;33m");
        printf("\n O numero de identificacion proporcionado non se atopa na nosa base de datos :(\n");
        printf("\033[1;0m");
        return;
    }
    // Recorremos o vector imprimindo solo as reservas do usuario
    for(int i = 0; i < totalVectorB->vector_size; i++){
        if(totalVectorB->vector_booking[i].client.ID == passenger_ID){
            printf("\033[1;34m");
            printf("\n~*~*~*~*~*~*~*~*~*~*~*~ Lista de reservas: ~*~*~*~*~*~*~*~*~*~*~*~\n");
            printf("%s %d-%d-%d %d %s %s %d\n", totalVectorB->vector_booking[i].client.name, totalVectorB->vector_booking[i].client.birth.year, totalVectorB->vector_booking[i].client.birth.month, totalVectorB->vector_booking[i].client.birth.day, 
            totalVectorB->vector_booking[i].client.ID, totalVectorB->vector_booking[i].client.email, totalVectorB->vector_booking[i].ref_num, totalVectorB->vector_booking[i].seat_num);
            printf("\033[1;0m");
        }
    }
}

