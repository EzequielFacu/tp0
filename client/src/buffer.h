#include "utils.h"

typedef struct {
    uint32_t size; // Tamaño del payload
    void* stream; // Payload
} t_buffer_ejemplo;

typedef struct {
    op_code codigo_operacion;
    t_buffer_ejemplo*buffer;
}t_paquete_ejemplo;

typedef struct{
    uint8_t AX;             //Registro Numérico de propósito general
    uint8_t BX;             //Registro Numérico de propósito general
    uint8_t CX;             //Registro Numérico de propósito general
    uint8_t DX;             //Registro Numérico de propósito general
    uint32_t EAX;           //Registro Numérico de propósito general
    uint32_t EBX;           //Registro Numérico de propósito general
    uint32_t ECX;           //Registro Numérico de propósito general
    uint32_t EDX;           //Registro Numérico de propósito general
}registros_generales;

typedef struct{
    pid_t pid;
    uint32_t program_counter;
    uint16_t vQuantum;
    registros_generales regitros; 
}PCB_data;

t_buffer_ejemplo * crear_buffer_de_PCB(PCB_data PCB);

t_paquete_ejemplo * crear_paquete_ejemplo(PCB_data PCB);

//void cargar_Buffer(t_buffer_ejemplo*buffer, void*data,size_t size, int numero);

void serializar_y_enviar_paquete_ejemplo(t_paquete_ejemplo* paquete, int socketCliente);

void eliminar_paquete_ejemplo(t_paquete_ejemplo*paquete);