#include "server.h"
#include "buffer.h"
#include <unistd.h>
/*
void * atender_cliente(void*arg){
	int * cliente_fd = (int*) arg;
	
	PCB_data * pcb;

	t_paquete_ejemplo * paquete;
	
	pcb = inicializar_PCB();

	paquete = inicializar_paquete();

	//Recivo en orden c/u de los datos en sus correspondientes lugares
	while(1){	
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
			eliminar_paquete_ejemplo(paquete);
			free(pcb->regitros);
			free(pcb);
			pthread_exit(NULL);
			break;
		}
		eliminar_paquete_ejemplo(paquete);
		free(pcb->regitros);
		free(pcb);
		pthread_exit (NULL);
	}
}*/

int main(void) {
	/*logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	
	log_info(logger, "Servidor listo para recibir al cliente");
	
	pthread_t thread;
	int*cliente_fd = malloc(sizeof(int));
	*cliente_fd = esperar_cliente(server_fd);
	pthread_create(&thread, NULL, atender_cliente, (void*)cliente_fd);
	pthread_join(thread,NULL);
	//inicializo el paquete
	free(cliente_fd);*/
	PCB_data * pcb;

	t_paquete_ejemplo * paquete;

	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	
	log_info(logger, "Servidor listo para recibir al cliente");
	
	int cliente_fd = esperar_cliente(server_fd);

	//Recivo en orden c/u de los datos en sus correspondientes lugares
	
	pcb = inicializar_PCB();

	paquete = inicializar_paquete();


	//Recivo en orden c/u de los datos en sus correspondientes lugares
	while(1){	
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
			eliminar_paquete_ejemplo(paquete);
			free(pcb->regitros);
			free(pcb);
			return EXIT_FAILURE;
			break;
		}
		eliminar_paquete_ejemplo(paquete);
		free(pcb->regitros);
		free(pcb);
		return  EXIT_FAILURE;
	}
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}