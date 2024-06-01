#include "buffer.h"

void eliminar_paquete_ejemplo(t_paquete_ejemplo*paquete){
    free(paquete->buffer->stream);
    free(paquete->buffer);
    free(paquete);
}

PCB_data * deserializar_PCB(t_buffer_ejemplo*buffer, PCB_data * PCB){

	void*stream = buffer->stream;

	descargar_datos(&stream, &PCB->pid, sizeof(pid_t), 0);
  
    descargar_datos(&stream, &PCB->program_counter, sizeof(uint32_t), 0);
	
    descargar_datos(&stream, &PCB->vQuantum, sizeof(uint16_t),0);
	
    descargar_datos(&stream,&PCB->regitros->AX,sizeof(uint8_t),0);
	
    descargar_datos(&stream,&PCB->regitros->BX,sizeof(uint8_t),0);
	
    descargar_datos(&stream,&PCB->regitros->CX,sizeof(uint8_t),0);
	
    descargar_datos(&stream,&PCB->regitros->DX,sizeof(uint8_t),0);
	
    descargar_datos(&stream,&PCB->regitros->EAX,sizeof(uint32_t),0);

    descargar_datos(&stream,&PCB->regitros->EBX,sizeof(uint32_t),0);

    descargar_datos(&stream,&PCB->regitros->ECX,sizeof(uint32_t),0);
	
    descargar_datos(&stream,&PCB->regitros->EDX,sizeof(uint32_t),1);
    //se recibe uno por uno segun el "tamaño" o "peso" de cada dato segun el orden en el que fueron enviados

    return PCB;
}

void descargar_datos (void**stream, void*data, size_t size, int numero){
    memcpy(data, *stream, size);
    if(numero == 0){
        *stream += size;
    }
}

void recibir_paquete_PCB(PCB_data * pcb, t_paquete_ejemplo * paquete){
    pcb = deserializar_PCB(paquete->buffer, pcb);
		//me aseguro de que recive el codigo de operacion de forma correcta

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
	
	//me aseguro de que cada dato fue recivido correctamente
}

PCB_data * inicializar_PCB(){
    PCB_data * pcb = malloc(sizeof(PCB_data));
    pcb->regitros = malloc(sizeof(registros_generales));
    return pcb;
}

t_paquete_ejemplo * inicializar_paquete(){
    t_paquete_ejemplo * paquete = malloc(sizeof(t_paquete_ejemplo));
    paquete->buffer = malloc(sizeof(t_buffer_ejemplo));
    return paquete;
}

t_paquete_ejemplo * recibir_paquete_ejemplo (t_paquete_ejemplo * paquete, int cliente_fd){
    recv(cliente_fd, &(paquete->codigo_operacion),sizeof(op_code),0);
    recv(cliente_fd, &(paquete->buffer->size), sizeof(uint32_t),0);
	paquete->buffer->stream =  malloc(paquete->buffer->size);
	recv(cliente_fd, paquete->buffer->stream, paquete->buffer->size,0);
    return paquete;
}