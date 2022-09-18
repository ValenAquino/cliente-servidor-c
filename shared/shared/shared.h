#ifndef SHARED_H_
#define SHARED_H_

#define MAX_CON 10 // maxima cantidad de conexiones entrantes

//Uso general
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<signal.h>

//Sockets
#include<sys/socket.h>
#include<unistd.h>
#include<netdb.h>

//Hilos
#include<pthread.h>

//Commons
#include<commons/log.h>
#include<commons/config.h>
#include<commons/collections/list.h>
#include<commons/string.h>

t_log* logger;

// Estructuras
typedef enum {
	MENSAJE,
	PAQUETE,
	DESCONEXION
} op_code;

typedef struct {
	int size;
	void* stream;
} t_buffer;

typedef struct {
	op_code codigo_operacion;
	t_buffer* buffer;
} t_paquete;

typedef struct {
	int num;
	char *mensaje;
} tsDatos;

// Prototipos
void leer_config(char **ip, char **puerto);

#endif /* SHARED_H_ */
