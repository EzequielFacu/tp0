#include "server.h"
#include "buffer.h"



void * atender_cliente(void *cliente){
	
	int cliente_fd = *(int*)cliente;

	PCB_data * pcb;

	free(cliente);

	t_paquete_ejemplo * paquete;
	
	pcb = inicializar_PCB();

	paquete = inicializar_paquete();

	//Recivo en orden c/u de los datos en sus correspondientes lugares
	
	paquete = recibir_paquete_ejemplo(paquete, cliente_fd);
	switch (paquete->codigo_operacion){
		case PAQUETE_A:
			log_info(logger, "PAQUETE A recibido");
			recibir_paquete_PCB(pcb,paquete);
			break;
		case PAQUETE_B:
			log_info(logger, "PAQUETE B recibido");
			break;
		default:
			log_info(logger, "error en el tipo de paquete");
			break;
	}
	eliminar_paquete_ejemplo(paquete);
	free(pcb->regitros);
	free(pcb);
	pthread_exit(NULL);
}

int main(void) {
	/*PCB_data * pcb;

	t_paquete_ejemplo * paquete;*/

	pthread_t thread;

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	
	log_info(logger, "Servidor listo para recibir al cliente");
	int contador = 0;
	//Recivo en orden c/u de los datos en sus correspondientes lugares
	while(1){
		int* socketCliente = malloc(sizeof(int));
		*socketCliente = accept(server_fd, NULL, NULL);
		log_info(logger, "Ingresó un cliente");
		pthread_create(&thread, NULL, atender_cliente, socketCliente);
		pthread_detach(thread);
		contador ++;
		printf("Procesos ingresados: %d \n", contador);
	}

	return  EXIT_SUCCESS;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}