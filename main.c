#include <stdio.h>
#include <stdlib.h>
#include "bibliovoos.h"
#include "structures.h"

int main(int argc, char *argv[]){
    char option, option2, user_ref_num[15], dep_airport[20], dest_airport[20];
    int user_ID, dia, mes, ano;
    float max_price;
    // Creamos os vectores de estructuras
    STVECTOR *totalVectorFlights = malloc(sizeof(STVECTOR));
    STVECTOR_B *totalVectorBookings = malloc(sizeof(STVECTOR));
    
    // Comprobamos que os nomes dos arquivos se pasen por liña de comandos
    if(argc != 3){
        printf("\033[1;33m");
        printf("\nNumero de argumentos incorrecto. TRY AGAIN :(\n");
        printf("\033[1;0m");
        return EXIT_FAILURE;
    }

    // Lemos os arquivos e gadamos os datos en dous vectores de estruturas
    read_flights(argv[1], totalVectorFlights);
    read_bookings(argv[2], totalVectorBookings);

    do{
        printf("\033[1;35m");
        printf("\n--------------------------------------------------------");
        printf("\n~*~*~*~*~*~*~*~ Seleccione unha opción ~*~*~*~*~*~*~*~\n");
        printf("\na) Reservar voo\n");
        printf("\nb) Cancelar voo\n");
        printf("\nc) Amosar voos dispoñibles\n");
        printf("\nd) Amosar as miñas reservas\n");
        printf("\ne) Consultar dispoñibilidade de voos\n");
        printf("\nf) Funcionalidades ocultas ;)\n");
        printf("\ns) Saír\n");
        printf("--------------------------------------------------------\n");
        printf("\033[1;0m");
        printf("\nOpcion:");
        scanf(" %c", &option);
        switch (option){
            case 'a':
                printf("\033[0;34m");
                printf("\nIntroduza o numero de referencia do voo que quere reservar: ");
                printf("\033[1;0m");
                scanf("%s", user_ref_num);
                book_flight(totalVectorFlights, totalVectorBookings, user_ref_num);
                break;
            
            case 'b':
                printf("\033[0;34m");
                printf("\nIntroduza o seu DNI ou NIE (9 dixitos): ");
                printf("\033[1;0m");
                scanf("%d", &user_ID);
                printf("\033[0;34m");
                printf("\nIntroduza o numero de referencia do voo que quere cancelar: ");
                printf("\033[1;0m");
                scanf("%s", user_ref_num);
            
                cancel_flight(totalVectorFlights, totalVectorBookings, user_ID, user_ref_num);
                break;
            
            case 'c':
                show_aviable_flights(totalVectorFlights);
                break;
            
            case 'd':
                printf("\033[0;34m");
                printf("\nIntroduza o seu DNI ou NIE (9 dixitos): ");
                printf("\033[1;0m");
                scanf("%d", &user_ID);
                show_user_bookings(totalVectorBookings, user_ID);
                break;
            
            case 'e':
            do{
                printf("\033[1;35m");
                printf("\n--------------------------------------------------------");
                printf("\n~*~*~*~*~*~*~*~ Seleccione unha opción ~*~*~*~*~*~*~*~\n");
                printf("\na) Consulta por prezo\n");
                printf("\nb) Consulta por traxecto\n");
                printf("\nc) Consulta por dia de saida\n");
                printf("\nv) Volver\n");
                printf("--------------------------------------------------------\n");
                printf("\033[1;0m");
                printf("\nOpcion:");
                scanf(" %c", &option2);
                switch (option2)
                {
                case 'a':
                    printf("\033[0;34m");
                    printf("\nIntroduza o aeroporto de orixe: ");
                    printf("\033[1;0m");
                    scanf("%s", dep_airport);
                    printf("\033[0;34m");
                    printf("\nIntroduza o prezo maximo: ");
                    printf("\033[1;0m");
                    scanf("%f", &max_price);
                    // FUNCION QUE IMPRIMA OS VOOS DESE AEROPORTO CUN PRECIO INFERIOR
                    break;

                case 'b':
                    printf("\033[0;34m");
                    printf("\nIntroduza o aeroporto de orixe: ");
                    printf("\033[1;0m");
                    scanf("%s", dep_airport);
                    printf("\033[0;34m");
                    printf("\nIntroduza o aeroporto de destino: ");
                    printf("\033[1;0m");
                    scanf("%s", dest_airport);
                    // FUNCION QUE IMPRIMA OS VOOS DESE TRAXECTO
                    break;

                case 'c':
                    printf("\033[0;34m");
                    printf("\nIntroduza o aeroporto de orixe: ");
                    printf("\033[1;0m");
                    scanf("%s", dep_airport);
                    printf("\033[0;34m");
                    printf("\nIntroduza a data de saida (dd/mm/aaaa): ");   
                    printf("\033[1;0m"); 
                    scanf("%d/%d/%d", &dia, &mes, &ano);
                    // FUNCION QUE IMPRIMA OS VOOS PARA ESA DATA E ESE AEROPORTO
                    break;

                case 'v':
                    break;
                }
            } while(option2 != 'v');
                break;
            
            case 'f':
            do{
                printf("\033[1;35m");
                printf("\n--------------------------------------------------------");
                printf("\n~*~*~ Modo ADMIN: seleccione unha opción ~*~*~\n");
                printf("\na) Engadir novos voos\n");
                printf("\nb) Eliminar voos de datas pasadas\n");
                printf("\nv) Volver\n");
                printf("--------------------------------------------------------\n");
                printf("\033[1;0m");
                printf("\nOpcion:");
                scanf(" %c", &option2);
            } while(option2 != 'v');
                break;

            case 's':
                /* code */
                break;
            
            default:
                break;
        }
    } while(option != 's');

    return EXIT_SUCCESS;
}
