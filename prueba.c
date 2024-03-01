#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rp.h"

#define BUFFER_SIZE 16384

int main(int argc, char **argv) {
    /* Inicialización de la Red Pitaya */
    if(rp_Init() != RP_OK) {
        fprintf(stderr, "Error al inicializar la Red Pitaya.\n");
        return EXIT_FAILURE;
    }

    /* Configuración del canal de entrada (in1) */
    rp_AcqReset();
    rp_AcqSetDecimation(RP_DEC_8); // Sin decimación

    /* Bucle para leer continuamente la señal de entrada y escribirla en la salida */
    while(1) {
        float buffer[BUFFER_SIZE];
        rp_AcqGetDataV(RP_CH_1, 0, &BUFFER_SIZE, buffer); // Leer datos del canal de entrada

        // Escribir los datos leídos en el canal de salida
        rp_GenWaveform(RP_CH_1, RP_WAVEFORM_ARBITRARY, buffer, BUFFER_SIZE);
        rp_GenOutEnable(RP_CH_1); // Habilitar la salida

        usleep(50000); // Esperar un tiempo corto para permitir la actualización (ajustar según sea necesario)
    }

    return EXIT_SUCCESS;
}
