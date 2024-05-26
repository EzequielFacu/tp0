#include "server.h"
#include "buffer.h"
#include <unistd.h>

int main(void) {
	PCB_data * pcb;

	t_paquete_ejemplo * paquete;

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	
	log_info(logger, "Servidor listo para recibir al cliente");
	
	int cliente_fd = esperar_cliente(server_fd);

	//inicializo el paquete
	
	pcb = inicializar_PCB();

	paquete = inicializar_paquete();

	paquete = recibir_paquete_ejemplo(paquete, cliente_fd);

	//Recivo en orden c/u de los datos en sus correspondientes lugares

	if(paquete->codigo_operacion == PAQUETE){
		recibir_paquete_PCB(pcb,paquete);
	}
	eliminar_paquete_ejemplo(paquete);
    free(pcb->regitros);
    free(pcb);
	return  EXIT_SUCCESS;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}