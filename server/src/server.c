#include "server.h"
#include "buffer.h"



void * atender_cliente(void *cliente){
	
	int cliente_fd = *(int*)cliente;

	free(cliente);

	t_paquete_ejemplo * paquete;
	paquete = inicializar_paquete();

	t_buffer_ejemplo* t_buffer_ejemplo = malloc(sizeof());
	bool verdad = true;
	//Recivo en orden c/u de los datos en sus correspondientes lugares
	while (verdad){
		paquete = recibir_paquete_ejemplo(paquete, cliente_fd);
		switch (paquete->codigo_operacion){
			case PAQUETE_A:
				PCB_data * pcb;

				pcb = inicializar_PCB();

				log_info(logger, "PAQUETE A recibido");
				
				recibir_paquete_PCB(pcb,paquete);
				
				free(pcb->regitros);
				free(pcb);
				log_info(logger, "PAQUETE A DESTRUIDO");
				break;
			case PAQUETE_B:
				log_info(logger, "PAQUETE B recibido");
				break;
			case PAQUETE_C:
				log_info(logger, "PAQUETE C recibido");
				break;
			case 0:
				log_info(logger, "FINALIZACION DE EJECUCION");
				eliminar_paquete_ejemplo(paquete);
				verdad = !verdad;
				break;
			default:
				log_info(logger, "error en el tipo de paquete");
				break;
		}
	}
	eliminar_paquete_ejemplo(paquete);

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