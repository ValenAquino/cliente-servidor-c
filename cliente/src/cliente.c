#include "cliente.h"

t_log *logger;

int main(void) {
	int cliente_fd;
	char *ip, *puerto;
	tsDatos dato;

	logger = log_create("cl.log", "CLIENTE", true, LOG_LEVEL_TRACE);
	leer_config(&ip, &puerto);
	crear_conexion(ip, puerto, &cliente_fd);
	cargar_struct(&dato);
	enviar(cliente_fd, dato);
	close(cliente_fd);

	return EXIT_SUCCESS;
}

void  crear_conexion(char *ip, char *puerto, int *cliente_fd) {
	struct addrinfo condiciones, *server_info;

	memset(&condiciones, 0, sizeof(condiciones));
	condiciones.ai_family = AF_INET;
	condiciones.ai_socktype = SOCK_STREAM;

	getaddrinfo(ip, puerto, &condiciones, &server_info);

	*cliente_fd = socket(
		server_info->ai_family, server_info->ai_socktype, server_info->ai_protocol
	);

	freeaddrinfo(server_info);

	if(*cliente_fd == -1) {
		log_info(logger, "no se ha podido establecer una conexion con el servidor");
		exit(EXIT_FAILURE);
	}

	if(connect(*cliente_fd, server_info->ai_addr, server_info->ai_addrlen) == -1) {
		log_info(logger, "no se ha podido establecer una conexion con el servidor");
		exit(EXIT_FAILURE);
	}

	log_info(logger, "Se ha realizado la conexion con exito");
}

void cargar_struct(tsDatos *dato) {
	dato->mensaje = readline("Ingrese un mensaje: ");
	dato->num = strlen(dato->mensaje) + 1; // 1 por el '/0'

	log_debug(logger, "%d, %s", dato->num, dato->mensaje);
}

void enviar(int cliente_fd, tsDatos dato) {
	void *stream = serializar(dato);
	int size = sizeof(int) + dato.num;

	send(cliente_fd, stream, size, 0);
	free(stream);
}

void* serializar(tsDatos dato) {
	void *stream = malloc(sizeof(dato));

	int desplazamiento = 0;
	memcpy(stream + desplazamiento, &dato.num, sizeof(int));

	desplazamiento += sizeof(int);
	memcpy(stream + desplazamiento, dato.mensaje, dato.num);

	return stream;
}
