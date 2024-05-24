#include "buffer.h"

t_buffer_ejemplo * crear_buffer_de_PCB(PCB_data PCB)
{
    t_buffer_ejemplo * buffer = malloc(sizeof(t_buffer_ejemplo));
    buffer->size = sizeof(pid_t)+ sizeof(uint16_t) + sizeof(uint8_t)*4 + sizeof(uint32_t)*5;

    uint32_t offset = 0;
    buffer->stream = malloc(buffer->size);
    memcpy(buffer->stream + offset, &PCB.pid,sizeof(pid_t));
    offset+=sizeof(pid_t);
    memcpy(buffer->stream + offset, &PCB.program_counter, sizeof(uint32_t));
    offset+=sizeof(uint32_t);
    memcpy(buffer->stream + offset, &PCB.vQuantum, sizeof(uint16_t));
    offset+=sizeof(uint16_t);
    memcpy(buffer->stream + offset, &PCB.regitros.AX, sizeof(uint8_t));
    offset+=sizeof(uint8_t);
    memcpy(buffer->stream + offset, &PCB.regitros.BX, sizeof(uint8_t));
    offset+=sizeof(uint8_t);
    memcpy(buffer->stream + offset, &PCB.regitros.CX, sizeof(uint8_t));
    offset+=sizeof(uint8_t);
    memcpy(buffer->stream + offset, &PCB.regitros.DX, sizeof(uint8_t));
    offset+=sizeof(uint8_t);
    memcpy(buffer->stream + offset, &PCB.regitros.EAX, sizeof(uint32_t));
    offset+=sizeof(uint32_t);
    memcpy(buffer->stream + offset, &PCB.regitros.EBX, sizeof(uint32_t));
    offset+=sizeof(uint32_t);
    memcpy(buffer->stream + offset, &PCB.regitros.ECX, sizeof(uint32_t));
    offset+=sizeof(uint32_t);
    memcpy(buffer->stream + offset, &PCB.regitros.EDX, sizeof(uint32_t));

    /*cargar_Buffer(buffer, &PCB.pid, sizeof(pid_t), 0);
    cargar_Buffer(buffer, &PCB.program_counter,sizeof(uint32_t),0);
    cargar_Buffer(buffer, &PCB.vQuantum, sizeof(uint16_t),0);
    cargar_Buffer(buffer, &PCB.regitros, sizeof(registros_generales),1);
    */
    return buffer;
}
/*
void cargar_Buffer(t_buffer_ejemplo*buffer, void*data,size_t size, int numero){
    memcpy((char*)buffer->stream + buffer->size, data, size);
    if(numero == 0){
        buffer->offset+=size;
    }   
}*/

t_paquete_ejemplo* crear_paquete_ejemplo (PCB_data PCB){
    t_paquete_ejemplo* paquete = malloc(sizeof(t_paquete_ejemplo));
    paquete->codigo_operacion = PAQUETE;
    paquete->buffer = crear_buffer_de_PCB(PCB);
    return paquete;
}

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