#include "servidor.h"

t_log *logger;

int main(void) {
	char *ip, *puerto;
	int server_fd, cliente_fd;

	logger = log_create("sv.log", "SERVIDOR", true, LOG_LEVEL_TRACE);
	leer_config(&ip, &puerto);

	server_fd = iniciar_sv(ip, puerto);
	cliente_fd = esperar_cliente(server_fd);

	recibir_paquete(cliente_fd);

	close(server_fd);
	close(cliente_fd);
	return EXIT_SUCCESS;
}

int iniciar_sv(char *ip, char *puerto) {
	int socket_escucha;
	struct addrinfo entrada, *sv;

	memset(&entrada, 0, sizeof(entrada));
	entrada.ai_family = AF_INET;
	entrada.ai_socktype = SOCK_STREAM;
	entrada.ai_flags = AI_PASSIVE;

	getaddrinfo(ip, puerto, &entrada, &sv);

	socket_escucha = socket(sv->ai_family, sv->ai_socktype, sv->ai_protocol);

	// si se interrumpe la ejecucion no tengo que esperar 2min para reutilizar ese socket
	// en ese ip y puerto
	int activado = 1;
	setsockopt(socket_escucha, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));

	if(socket_escucha < 0) {
		log_info(logger, "No se ha podido iniciar el socket");
		exit(EXIT_FAILURE);
	}

	log_trace(logger, "Se ha creado el socket pasivo");

	if(bind(socket_escucha, sv->ai_addr, sv->ai_addrlen) != 0) {
		log_info(logger, "No se ha podido iniciar el socket");
		exit(EXIT_FAILURE);
	}

	freeaddrinfo(sv);

	log_trace(logger, "Se ha asignado el puerto: %s", puerto);

	if(listen(socket_escucha, MAX_CON) != 0) {
		log_info(logger, "No se ha podido habilitar el socket para recibir conexiones");
		exit(EXIT_FAILURE);
	}

	log_info(logger, "Servidor escuchando en el IP: %s PUERTO: %s", ip, puerto);

	return socket_escucha;
}

int esperar_cliente(int server_fd) {
	int cliente_fd = accept(server_fd, NULL, NULL);
	log_info(logger, "Se ha conectado un cliiente");

	return cliente_fd;
}

void recibir_paquete(int cliente_fd) {
	tsDatos *dato = malloc(sizeof(tsDatos));

	recv(cliente_fd, &dato->num, sizeof(int), 0);

	dato->mensaje = malloc(dato->num);

	recv(cliente_fd, dato->mensaje, dato->num, 0);

	log_info(logger, "%d, %s", dato->num, dato->mensaje);
}
