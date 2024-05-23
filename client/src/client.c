#include "client.h"
#include "buffer.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;


	t_paquete_ejemplo*paquete;
	t_buffer_ejemplo*buffer;
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
	
	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info(logger, "Soy un log");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	valor=config_get_string_value(config,"CLAVE");
	ip=config_get_string_value(config, "IP");
	puerto=config_get_string_value(config,"PUERTO");
	// Loggeamos el valor de config
	log_info(logger,valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	paquete=crear_paquete_ejemplo(pcb);
	conexion = crear_conexion(ip, puerto);
	//buffer = crear_buffer_de_PCB(pcb);
	//send(conexion, &buffer, sizeof(t_buffer_ejemplo),0);
	/*
	size_t bytes;

	int32_t handshake = 1;
	int32_t result;

	bytes = send(conexion, &handshake, sizeof(int32_t), 0);
	bytes = recv(conexion, &result, sizeof(int32_t), MSG_WAITALL);

	if (result == 0) {
		printf("BIEN");
	} else {
		printf("ERROR");
	}*/

	serializar_y_enviar_paquete_ejemplo(paquete,conexion);
	//Enviamos al servidor el valor de CLAVE como mensaje
	//enviar_mensaje(valor,conexion);
	// Armamos y enviamos el paquete
	//paquete(conexion);

	eliminar_paquete_ejemplo(paquete);

	terminar_programa(conexion, logger, config);
	
	free(ip);
	free(puerto);
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
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}
