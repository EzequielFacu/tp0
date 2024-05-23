#include "buffer.h"
/*
t_paquete_ejemplo* crear_paquete_ejemplo (PCB_data PCB){
    t_paquete_ejemplo* paquete = malloc(sizeof(t_paquete_ejemplo));
    paquete->codigo_operacion = PAQUETE;
    paquete->buffer = crear_buffer_de_PCB(PCB);
    return paquete;
}*/
/*
t_buffer_ejemplo * crear_buffer_de_PCB(PCB_data PCB)
{
    t_buffer_ejemplo * buffer = malloc(sizeof(t_buffer_ejemplo));
    buffer->size = sizeof(pid_t)+sizeof(uint32_t) + sizeof(uint16_t) + sizeof(registros_generales);

    buffer->offset = 0;
    buffer->stream = malloc(buffer->size);
    memcpy(buffer->stream + buffer->offset, &PCB.pid,sizeof(pid_t));
    buffer->offset+=sizeof(pid_t);
    memcpy(buffer->stream + buffer->offset, &PCB.program_counter, sizeof(uint32_t));
    buffer->offset+=sizeof(uint32_t);
    memcpy(buffer->stream + buffer->offset, &PCB.vQuantum, sizeof(uint16_t));
    buffer->offset+=sizeof(uint16_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.AX, sizeof(uint8_t));
    buffer->offset+=sizeof(uint8_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.BX, sizeof(uint8_t));
    buffer->offset+=sizeof(uint8_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.CX, sizeof(uint8_t));
    buffer->offset+=sizeof(uint8_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.DX, sizeof(uint8_t));
    buffer->offset+=sizeof(uint8_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.EAX, sizeof(uint32_t));
    buffer->offset+=sizeof(uint32_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.EBX, sizeof(uint32_t));
    buffer->offset+=sizeof(uint32_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.ECX, sizeof(uint32_t));
    buffer->offset+=sizeof(uint32_t);
    memcpy(buffer->stream + buffer->offset, &PCB.regitros.EDX, sizeof(uint32_t));

    
    return buffer;
}
*/
/*
void cargar_Buffer(t_buffer_ejemplo*buffer, void*data,size_t size, int numero){
    memcpy((char*)buffer->stream + buffer->size, data, size);
    if(numero == 0){
        buffer->offset+=size;
    }   
}*/


void serializar_y_enviar_paquete_ejemplo(t_paquete_ejemplo* paquete, int socketCliente){
    void* a_enviar = malloc(paquete->buffer->size + sizeof(op_code) + sizeof(uint32_t)); 
    //uint8 por el Codigo de operacion y uint 32 por el buffer
    
    int offset = 0;

    memcpy(a_enviar + offset, &(paquete->codigo_operacion), sizeof(op_code));
    offset += sizeof(op_code);
    memcpy(a_enviar + offset, &(paquete->buffer->size), sizeof(uint32_t));
    offset += sizeof(uint32_t);

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

PCB_data*PCB_ejemplo(t_buffer_ejemplo*buffer){
	PCB_data*PCB;
	void*stream = buffer->stream;
	memcpy(&(PCB->pid),stream, sizeof(pid_t));
	stream += sizeof(pid_t);
	memcpy(&(PCB->program_counter),stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	memcpy(&(PCB->vQuantum),stream, sizeof(uint16_t));
	stream += sizeof(uint16_t);
	//_X
	memcpy(&(PCB->regitros.AX),stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	memcpy(&(PCB->regitros.BX),stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	memcpy(&(PCB->regitros.CX),stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	memcpy(&(PCB->regitros.DX),stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	//E_X
	memcpy(&(PCB->regitros.EAX),stream, sizeof(uint32_t));
    stream += sizeof(uint32_t);
	memcpy(&(PCB->regitros.EBX),stream, sizeof(uint32_t));
    stream += sizeof(uint32_t);
	memcpy(&(PCB->regitros.ECX),stream, sizeof(uint32_t));
    stream += sizeof(uint32_t);
	memcpy(&(PCB->regitros.EDX),stream, sizeof(uint32_t));
    
	return PCB;
}