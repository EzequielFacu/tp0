#include "buffer.h"

t_buffer_ejemplo * crear_buffer_de_PCB(PCB_data*PCB)
{
    t_buffer_ejemplo * buffer = malloc(sizeof(t_buffer_ejemplo));
    buffer->size = sizeof(pid_t)+ sizeof(uint16_t) + sizeof(uint8_t)*4 + sizeof(uint32_t)*5;

    uint32_t offset = 0;
    buffer->stream = malloc(buffer->size);
    
    cargar_datos(buffer->stream, &PCB->pid, &offset, sizeof(pid_t),0);
    cargar_uint32(buffer->stream, &PCB->program_counter, &offset,0);
    cargar_datos(buffer->stream, &PCB->vQuantum, &offset, sizeof(uint16_t),0);
    cargar_uint8(buffer->stream, &PCB->regitros->AX, &offset, 0);
    cargar_uint8(buffer->stream, &PCB->regitros->BX, &offset, 0);
    cargar_uint8(buffer->stream, &PCB->regitros->CX, &offset, 0);
    cargar_uint8(buffer->stream, &PCB->regitros->DX, &offset, 0);
    cargar_uint32(buffer->stream, &PCB->regitros->EAX, &offset, 0);
    cargar_uint32(buffer->stream, &PCB->regitros->EBX, &offset, 0);
    cargar_uint32(buffer->stream, &PCB->regitros->ECX, &offset, 0);
    cargar_uint32(buffer->stream, &PCB->regitros->EDX, &offset, 1);
    
    return buffer;
}

void serializar_y_enviar_paquete_ejemplo(t_paquete_ejemplo* paquete, int socketCliente){
    void* a_enviar = malloc(paquete->buffer->size + sizeof(op_code) + sizeof(uint32_t)); 
    //sizeof(op_code) por el Codigo de operacion y uint 32 por el buffer
    
    uint32_t offset = 0;

    cargar_datos(a_enviar,&(paquete->codigo_operacion), &offset,sizeof(op_code),0);

    cargar_datos(a_enviar, &(paquete->buffer->size), &offset, sizeof(uint32_t), 0);
    
    memcpy(a_enviar + offset, paquete->buffer->stream, paquete->buffer->size);

    send(socketCliente, a_enviar, paquete->buffer->size + sizeof(op_code) + sizeof(uint32_t), 0);
    
    free(a_enviar);
    //despues tenemos que liberar los punteros de buffer y paquete en otro codigo
}

void eliminar_paquete_ejemplo(t_paquete_ejemplo*paquete){
    free(paquete->buffer->stream);
    free(paquete->buffer);
    free(paquete);
}

void cargar_uint32(void* buffer, uint32_t*data, uint32_t* offset,int numero){
    memcpy(buffer + *offset, data, sizeof(uint32_t));
    if(numero == 0){
        *offset += sizeof(uint32_t);
    }
}

void cargar_uint8 (void* buffer, uint8_t*data, uint32_t* offset, int numero){
    memcpy(buffer + *offset, data, sizeof(uint8_t));
    if(numero == 0){
        *offset += sizeof(uint8_t);
    }
}

void cargar_datos (void*buffer, void*data, uint32_t*offset, size_t size, int numero){
    memcpy(buffer + *offset, data, size);
    if(numero == 0){
        *offset += size;
    }
}

t_paquete_ejemplo* crear_paquete_ejemplo (PCB_data* PCB){
    t_paquete_ejemplo* paquete = malloc(sizeof(t_paquete_ejemplo));
    paquete->codigo_operacion = PAQUETE_A;
    paquete->buffer = crear_buffer_de_PCB(PCB);
    return paquete;
}

PCB_data * crear_PCB_A(PCB_data*pcb){
	pcb = malloc(sizeof(PCB_data));
	pcb->regitros = malloc(sizeof(registros_generales));

	pcb->pid = 123;
	pcb->program_counter = 12345;
	pcb->vQuantum = 10;
    pcb->regitros->AX = 1;
    pcb->regitros->BX = 2;
    pcb->regitros->CX = 3;
    pcb->regitros->DX = 4;
    pcb->regitros->EAX = 5;
    pcb->regitros->EBX = 6;
    pcb->regitros->ECX = 7;
    pcb->regitros->EDX = 8;
	return pcb;
}