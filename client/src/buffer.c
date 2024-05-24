#include "buffer.h"

t_buffer_ejemplo * crear_buffer_de_PCB(PCB_data PCB)
{
    t_buffer_ejemplo * buffer = malloc(sizeof(t_buffer_ejemplo));
    buffer->size = sizeof(pid_t)+ sizeof(uint16_t) + sizeof(uint8_t)*4 + sizeof(uint32_t)*5;

    uint32_t offset = 0;
    buffer->stream = malloc(buffer->size);
    
    offset = cargar_datos_a_Buffer(buffer, &PCB.pid, offset, sizeof(pid_t),0);
    offset= cargar_uint32(buffer, &PCB.program_counter, offset,0);
    offset = cargar_datos_a_Buffer(buffer,&PCB.vQuantum, offset,sizeof(uint16_t),0);
    offset = cargar_uint8(buffer, &PCB.regitros.AX, offset, 0);
    offset = cargar_uint8(buffer, &PCB.regitros.BX, offset, 0);
    offset = cargar_uint8(buffer, &PCB.regitros.CX, offset, 0);
    offset = cargar_uint8(buffer, &PCB.regitros.DX, offset, 0);
    offset = cargar_uint32(buffer, &PCB.regitros.EAX, offset, 0);
    offset = cargar_uint32(buffer, &PCB.regitros.EBX, offset, 0);
    offset = cargar_uint32(buffer, &PCB.regitros.ECX, offset, 0);
    offset = cargar_uint32(buffer, &PCB.regitros.EDX, offset, 1);
    
    return buffer;
}

uint32_t cargar_uint32(t_buffer_ejemplo* buffer, uint32_t*data, uint32_t offset,int numero){
    memcpy(buffer->stream + offset, data, sizeof(uint32_t));
    if(numero == 0){
        offset += sizeof(uint32_t);
    }
    return offset;
}

uint32_t cargar_uint8 (t_buffer_ejemplo* buffer, uint8_t*data, uint32_t offset, int numero){
     memcpy(buffer->stream + offset, data, sizeof(uint8_t));
    if(numero == 0){
        offset += sizeof(uint8_t);
    }
    return offset;
}
uint32_t cargar_datos_a_Buffer(t_buffer_ejemplo*buffer, void*data, uint32_t offset, size_t size, int numero){
    memcpy(buffer->stream + offset, data, size);
    if(numero == 0){
        offset += size;
    }
    return offset;
}

t_paquete_ejemplo* crear_paquete_ejemplo (PCB_data PCB){
    t_paquete_ejemplo* paquete = malloc(sizeof(t_paquete_ejemplo));
    paquete->codigo_operacion = PAQUETE;
    paquete->buffer = crear_buffer_de_PCB(PCB);
    return paquete;
}

void serializar_y_enviar_paquete_ejemplo(t_paquete_ejemplo* paquete, int socketCliente){
    void* a_enviar = malloc(paquete->buffer->size + sizeof(op_code) + sizeof(uint32_t)); 
    //sizeof(op_code) por el Codigo de operacion y uint 32 por el buffer
    
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