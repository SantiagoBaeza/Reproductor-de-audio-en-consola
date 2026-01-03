#include <stdio.h>
#include <stdint.h>
#include "audio_player.h"
#include <stdlib.h>

typedef struct
{
    uint32_t sample_rate;
    uint32_t sample_count;
    char sound_name[64];
    float *sound_data;
}cancion;

int main()
{
//inciso 1
    uint32_t count_of_sounds;
    FILE *archivo = fopen("audio_list.raw", "rb"); //mas o menos me acorde la mayoria menos que esto se usaba con fopen lolxd
    fread(&count_of_sounds, sizeof(uint32_t),1,archivo);
    printf("\nATENCNION: La cantidad de canciones disponibles es: %u\n", count_of_sounds); //importante para detectar algun error 
    cancion *canciones= malloc(count_of_sounds * sizeof(cancion));
    if(canciones==NULL)
    {
        printf("\nError: No se pudo apartar memoria.\n");
        free(canciones);
        fclose(archivo);
        return 1;
    }

    for(int i=0; i<count_of_sounds; i++)//for para los headers
    {
        fread(&canciones[i].sample_rate, sizeof(uint32_t), 1, archivo);
        fread(&canciones[i].sample_count, sizeof(uint32_t),1,archivo);
        fread(canciones[i].sound_name, sizeof(char), 64, archivo); //casi le pongo & a este jaksjak
    }

    for(int i=0; i<count_of_sounds;i++)
    {
        canciones[i].sound_data = malloc(canciones[i].sample_count *sizeof(float));
        if(canciones[i].sound_data == NULL)
        {
            printf("\nError: No se pudo apartar memoria.\n");
            //si hubo algun fallo, eso significa que desde 0 hasta i hay que liberar memoria antes de salir
            for(int j=0; j<i; j++)
            {
                free(canciones[j].sound_data); //libero cada memoria guardada antes del del fallo 
            }
            free(canciones);
            fclose(archivo);
            return 1;  
        }
        fread(canciones[i].sound_data, sizeof(float), canciones[i].sample_count,archivo); 
        //fread(destino, tipo de dato, cantidad de muestras, origen)
        //para liberar esta memoria al final voy a tener que usar otro for igual a este 
    }

    //a este punto mi struct tiene todos los datos que queria, ahora hago el menu:
    int seleccion;
    do{
        do
        {
            printf("\n***************MENU***************\n");
            
            printf("0) salir.\n");
            for(int i=0; i<count_of_sounds; i++)
            {
                printf("%d) %s.\n", i+1, canciones[i].sound_name);
            }
            printf("Elija entre alguna de las opciones:\n");
            scanf("%d",&seleccion);
            if(seleccion < 0 || seleccion > count_of_sounds)
            {
                printf("\nError: el valor seleccionado no es valido.");
            }
        }while(seleccion < 0 || seleccion > count_of_sounds);

        //si llegamos a este punto significa que en selecion esta lo proximo a hacer
        if(seleccion != 0)
        {
            play_audio(canciones[seleccion-1].sample_rate, canciones[seleccion-1].sample_count, canciones[seleccion-1].sound_data); //reproduzco la cancion 
            //int play_audio(uint32_t sample_rate,uint32_t sample_count,float *audio);

            int seleccion_2;
            do
            {
                printf("\nQuiere guardar la cancion actual en un archivo.raw?");
                printf("\nNo(ingrese 0) / Si(ingrese 1)");
                scanf("%d",&seleccion_2);
                if(seleccion_2<0 || seleccion_2>1)
                {
                    printf("\nError: el valor seleccionado no es valido.");
                }
            }while(seleccion_2<0 || seleccion_2>1);

            if(seleccion_2 == 1)
            {
                //guardo el archivo de la cancion 
                FILE *guardar = fopen("cancion.raw", "wb");
                if(guardar == NULL)
                {
                    printf("\nError: no se pudo guardar la cancion.");
                    //aca no hacemos lo de cerrar el programa para que el usuario pueda seguir usandolo
                }else
                {
                    fwrite(canciones[seleccion-1].sound_data, sizeof(float),canciones[seleccion-1].sample_count, guardar);
                    //fwrite(origen, tipo de dato, cantidad, destino(array))
                    fclose(guardar);
                }
                
            }
        }
    }while(seleccion !=0);

    //si estamos aca significa que el usuario preciono cero
    printf("\nGracias por usar este programa.");
    for(int i=0; i< count_of_sounds; i++)//para liberar toda la memoria de sound_data
    {
        free(canciones[i].sound_data);
    }
    free(canciones);
    fclose(archivo);
    return 0; //este lo arregle, antes habia puesto return 1;

}