#include "buffer.h"

void eliminar_paquete_ejemplo(t_paquete_ejemplo*paquete){
    free(paquete->buffer->stream);
    free(paquete->buffer);
    free(paquete);
}

PCB_data*PCB_ejemplo(t_buffer_ejemplo*buffer){
	PCB_data*PCB=malloc(sizeof(PCB_data));
    PCB->regitros= malloc(sizeof(registros_generales));
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