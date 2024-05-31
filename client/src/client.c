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
	PCB_data * pcb;

	logger = iniciar_logger();

	config = iniciar_config();

	log_info(logger, "Soy un log");

	pcb = crear_PCB_A(pcb);

	valor = config_get_string_value(config,"CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config,"PUERTO");

	log_info(logger,valor);

	paquete = crear_paquete_ejemplo(pcb);

	conexion = crear_conexion(ip, puerto);

	serializar_y_enviar_paquete_ejemplo(paquete,conexion);
	
	log_info(logger,"Se envio el paquete A");

	eliminar_paquete_ejemplo(paquete);

	terminar_programa(conexion, logger, config);
	
	free(pcb->regitros);
	free(pcb);

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
