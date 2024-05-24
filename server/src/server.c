#include "server.h"
#include "buffer.h"
#include <unistd.h>

int main(void) {
	logger = log_create("log.log", "Servidor", 1, LOG_LEVEL_DEBUG);

	int server_fd = iniciar_servidor();
	log_info(logger, "Servidor listo para recibir al cliente");
	int cliente_fd = esperar_cliente(server_fd);
	
	t_paquete_ejemplo * paquete = malloc(sizeof(t_paquete_ejemplo));
	paquete->buffer = NULL;
	paquete->buffer = malloc(sizeof(t_buffer_ejemplo));
	PCB_data*pcb = malloc(sizeof(PCB_data));

	recv(cliente_fd, &(paquete->codigo_operacion),sizeof(op_code),MSG_WAITALL);
	recv(cliente_fd, &(paquete->buffer->size), sizeof(uint32_t),0);
	paquete->buffer->stream =  malloc(paquete->buffer->size);
	recv(cliente_fd, paquete->buffer->stream, paquete->buffer->size,0);
	
	if(paquete->codigo_operacion == PAQUETE){
		pcb = PCB_ejemplo(paquete->buffer);
		printf("PCB Data:\n");
		printf("PID: %d\n", pcb->pid);	
		printf("Program Counter: %d\n", pcb->program_counter);
		printf("vQuantum: %d\n", pcb->vQuantum);
		printf("Registros Generales:\n");
		printf("AX: %d\n", pcb->regitros->AX);
		printf("BX: %d\n", pcb->regitros->BX);
		printf("CX: %d\n", pcb->regitros->CX);
		printf("DX: %d\n", pcb->regitros->DX);
		printf("EAX: %d\n", pcb->regitros->EAX);
		printf("EBX: %d\n", pcb->regitros->EBX);
		printf("ECX: %d\n", pcb->regitros->ECX);
		printf("EDX: %d\n", pcb->regitros->EDX);
		eliminar_paquete_ejemplo(paquete);
	}
	free(pcb->regitros);
	free(pcb);
	return 0;
}

void iterator(char* value) {
	log_info(logger,"%s", value);
}