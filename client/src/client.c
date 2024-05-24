#include "client.h"
#include "buffer.h"

int main(void)
{
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;
	t_paquete_ejemplo*paquete;
	PCB_data pcb;

	pcb.pid = 123;
	pcb.program_counter = 12345;
	pcb.vQuantum = 10;
    pcb.regitros.AX = 1;
    pcb.regitros.BX = 2;
    pcb.regitros.CX = 3;
    pcb.regitros.DX = 4;
    pcb.regitros.EAX = 5;
    pcb.regitros.EBX = 6;
    pcb.regitros.ECX = 7;
    pcb.regitros.EDX = 8;
	
	logger = iniciar_logger();
	log_info(logger, "Soy un log");

	config = iniciar_config();

	valor=config_get_string_value(config,"CLAVE");
	ip=config_get_string_value(config, "IP");
	puerto=config_get_string_value(config,"PUERTO");

	log_info(logger,valor);

	paquete=crear_paquete_ejemplo(pcb);

	conexion = crear_conexion(ip, puerto);

	serializar_y_enviar_paquete_ejemplo(paquete,conexion);
	
	eliminar_paquete_ejemplo(paquete);

	terminar_programa(conexion, logger, config);
	
	free(ip);
	free(puerto);
	return 0;
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
	nuevo_logger = log_create("tp0.log","Cliente",true,LOG_LEVEL_INFO);
	if(nuevo_logger == NULL){
		printf("No se pudo crear un log");
	}
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config = config_create("cliente.config");
		if (nuevo_config == NULL){
			printf("No se pudo crear");
		}
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	// La primera te la dejo de yapa
	leido = readline("> ");

	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
	while(1){
		leido = readline("> ");
		if(!leido){
			free(leido);
			break;
		}else if(strcmp(leido,"")==0){
			free(leido);
			break;
		}
		log_info(logger,leido);
		free(leido);
	}

	// ¡No te olvides de liberar las lineas antes de regresar!

}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;

	// Leemos y esta vez agregamos las lineas al paquete
	paquete=crear_paquete();
	if(paquete==NULL){
		printf("No se pudo crear paquete");
	}
	while(1){
		leido = readline("> ");
		if(!leido){
			break;
		}else if(strcmp(leido,"")==0){
			free(leido);
			break;
		}
		agregar_a_paquete(paquete,leido,strlen(leido)+1);
		free(leido);
	}
	enviar_paquete(paquete,conexion);
	eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}
