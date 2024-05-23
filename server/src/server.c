#include "server.h"
#include "buffer.h"

int main(void) {
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);
	/*
	size_t bytes;

	int32_t handshake;
	int32_t resultOk = 0;
	int32_t resultError = -1;

	bytes = recv(cliente_fd, &handshake, sizeof(int32_t), MSG_WAITALL);
	if (handshake == 1) {
		bytes = send(cliente_fd, &resultOk, sizeof(int32_t), 0);
	} else {
		bytes = send(cliente_fd, &resultError, sizeof(int32_t), 0);
	}*/
	PCB_data  * pcb;
	t_paquete_ejemplo * paquete = malloc(sizeof(t_paquete_ejemplo));
	
	paquete->buffer = malloc(sizeof(t_buffer_ejemplo));
	//recv(cliente_fd,&pcb->regitros.AX,sizeof(), MSG_WAITALL);
	
	recv(cliente_fd, &(paquete->codigo_operacion),sizeof(op_code),0);
	recv(cliente_fd, &(paquete->buffer->size), sizeof(uint32_t),0);
	paquete->buffer->stream=malloc(paquete->buffer->size);
	recv(cliente_fd, paquete->buffer->stream, paquete->buffer->size,0);
	
	
	if(paquete->codigo_operacion == PAQUETE){
		pcb = PCB_ejemplo(paquete->buffer);
	}
	printf("PCB Data:\n");
    printf("PID: %d\n", pcb->pid);
    printf("Program Counter: %u\n", pcb->program_counter);
    printf("vQuantum: %u\n", pcb->vQuantum);

    printf("Registros Generales:\n");
    printf("AX: %u\n", pcb->regitros.AX);
    printf("BX: %u\n", pcb->regitros.BX);
    printf("CX: %u\n", pcb->regitros.CX);
    printf("DX: %u\n", pcb->regitros.DX);
    printf("EAX: %u\n", pcb->regitros.EAX);
    printf("EBX: %u\n", pcb->regitros.EBX);
    printf("ECX: %u\n", pcb->regitros.ECX);
    printf("EDX: %u\n", pcb->regitros.EDX);
	
	//eliminar_paquete_ejemplo(paquete);

	free(paquete->buffer->stream);
	free(paquete->buffer);
	/*
	t_list* lista;
	while (1) {
		int cod_op = recibir_operacion(cliente_fd);
		switch (cod_op) {
		case MENSAJE:
			recibir_mensaje(cliente_fd);
			break;
		case PAQUETE:
			lista = recibir_paquete(cliente_fd);
			log_info(logger, "Me llegaron los siguientes valores:\n");
			list_iterate(lista, (void*) iterator);
			break;
		case -1:
			log_error(logger, "el cliente se desconecto. Terminando servidor");
			return EXIT_FAILURE;
		default:
			log_warning(logger,"Operacion desconocida. No quieras meter la pata");
			break;
		}
	}*/

	return EXIT_FAILURE;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}