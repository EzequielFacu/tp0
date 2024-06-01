#include "client.h"
#include "buffer.h"

int main(void)
{
	int conexion;
	char* ip;
	char* puerto;
	//char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

	config = iniciar_config();

	log_info(logger, "Soy un log");

	//valor = config_get_string_value(config,"CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config,"PUERTO");

	bool verdadero = true;

	conexion = crear_conexion(ip, puerto);

	while(verdadero){
		int numero;
		printf("Elije un proceso a ejecutar:\n");
		printf("1. Proceso A: Enviar PCB predeterminado\n");
		printf("2. Proceso B: \n");
		printf("3. Proceso C: \n");
		printf("4. Finalizar programa\n");

		scanf("%d", &numero);

		switch (numero){
			case 1:
				log_info(logger, "Se inicia el Proceso A");
				crear_proceso_A(logger, conexion);
				break;
			case 2:
				log_info(logger, "Se inicia el Proceso B");
				break;
			case 3:
				log_info(logger, "Se inicia el Proceso C");
				break;
			case 4: 
				log_info(logger, "Finalizacion de CLIENTE");
				verdadero = !verdadero;
				break;
			default:
				log_info(logger, "Finalizacion Forzada de CLIENTE");
				terminar_programa(conexion, logger, config);
				break;
		}
	}
	/*
	pcb = crear_PCB_A(pcb);

	paquete = crear_paquete_ejemplo(pcb);

	serializar_y_enviar_paquete_ejemplo(paquete,conexion);
	
	log_info(logger,"Se envio el paquete A");

	eliminar_paquete_ejemplo(paquete);

	free(pcb->regitros);
	free(pcb);
	*/

	terminar_programa(conexion, logger, config);
	
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
/*
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
*/
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
