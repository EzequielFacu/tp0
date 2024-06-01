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
    registros_generales * regitros; 
}PCB_data;

//en este caso uso punteros a registros, habra que ver si se puede sin ellos y si el error era unicamente el no haber inicializado paquete y buffer

PCB_data * inicializar_PCB();

t_paquete_ejemplo * inicializar_paquete();

t_paquete_ejemplo * recibir_paquete_ejemplo(t_paquete_ejemplo * paquete, int cliente_fd);

void eliminar_paquete_ejemplo(t_paquete_ejemplo * paquete);

void descargar_datos (void**stream, void*data, size_t size, int numero);

PCB_data*deserializar_PCB(t_buffer_ejemplo*buffer, PCB_data * PCB);

void recibir_paquete_PCB(PCB_data * pcb, t_buffer_ejemplo * paquete);

void eliminar_buffer_y_PCB(t_buffer_ejemplo* buffer, PCB_data * pcb); 