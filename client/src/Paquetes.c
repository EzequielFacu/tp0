#include "Paquetes.h"

void crear_proceso_A(t_log * logger, int conexion){

    t_paquete_ejemplo * paquete;
	
    PCB_data * pcb;
    
    pcb = crear_PCB_A(pcb);

    paquete = crear_paquete_ejemplo(pcb);

    serializar_y_enviar_paquete_ejemplo(paquete, conexion);
    
    log_info(logger, "Se envio el Paquete A");

    eliminar_paquete_ejemplo(paquete);
    free(pcb->regitros);
    free(pcb);
}