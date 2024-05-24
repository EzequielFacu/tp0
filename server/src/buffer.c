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
	memcpy(&PCB->pid, stream, sizeof(pid_t));
	stream += sizeof(pid_t);
	memcpy(&PCB->program_counter,stream, sizeof(uint32_t));
	stream += sizeof(uint32_t);
	memcpy(&PCB->vQuantum,stream, sizeof(uint16_t));
	stream += sizeof(uint16_t);
	//_X
	memcpy(&PCB->regitros->AX,stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	memcpy(&PCB->regitros->BX,stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	memcpy(&PCB->regitros->CX,stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	memcpy(&PCB->regitros->DX,stream, sizeof(uint8_t));
    stream += sizeof(uint8_t);
	//E_X
	memcpy(&PCB->regitros->EAX,stream, sizeof(uint32_t));
    stream += sizeof(uint32_t);
	memcpy(&PCB->regitros->EBX,stream, sizeof(uint32_t));
    stream += sizeof(uint32_t);
	memcpy(&PCB->regitros->ECX,stream, sizeof(uint32_t));
    stream += sizeof(uint32_t);
	memcpy(&PCB->regitros->EDX,stream, sizeof(uint32_t));
   
    //se recibe uno por uno segun el "tamaño" o "peso" de cada dato segun el orden en el que fueron enviados

    return PCB;
}