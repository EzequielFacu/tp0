#include "server.h"
#include "buffer.h"

op_code operacion_paquete(int cliente){
	op_code code;
	if (recv(cliente, &code, sizeof(op_code),0)>0){
		return code;
	}else{
		return FIN_DEL_PROGRAMA;
	}
}	

void * atender_cliente(void *cliente){
	
	int cliente_fd = *(int*)cliente;

	free(cliente);

	//t_paquete_ejemplo * paquete;
	//paquete = inicializar_paquete();
	
	bool verdad = true;
	//Recivo en orden c/u de los datos en sus correspondientes lugares
	while (verdad){
		//paquete = recibir_paquete_ejemplo(paquete, cliente_fd);
		op_code code = operacion_paquete(cliente_fd);
		
		switch (code){
			case PAQUETE_A:
				PCB_data * pcb;

				t_buffer_ejemplo * buffer = malloc(sizeof(uint32_t));
				
				pcb = inicializar_PCB();

				recv(cliente_fd, &(buffer->size), sizeof(uint32_t),0);
				buffer->stream = malloc(buffer->size);
				recv(cliente_fd, buffer->stream, buffer->size,0); 

				log_info(logger, "PAQUETE A recibido");
				
				recibir_paquete_PCB(pcb,buffer);
				
				eliminar_buffer_y_PCB(buffer,pcb);

				log_info(logger, "PAQUETE A DESTRUIDO");
				break;
			case PAQUETE_B:
				log_info(logger, "PAQUETE B recibido");
				break;
			case PAQUETE_C:
				log_info(logger, "PAQUETE C recibido");
				break;
			case FIN_DEL_PROGRAMA:
				log_info(logger, "FINALIZACION DE EJECUCION");
				//eliminar_paquete_ejemplo(paquete);
				verdad = !verdad;
				break;
			default:
				log_info(logger, "error en el tipo de paquete");
				verdad = !verdad;
				break;
		}
	}

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