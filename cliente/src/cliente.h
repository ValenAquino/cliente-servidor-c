#ifndef CLIENTE_H_
#define CLIENTE_H_

// Bibliotecas
#include <shared/shared.h>

// Prototipos
void  crear_conexion(char *, char *, int *);
void cargar_struct(tsDatos *dato);
void enviar(int cliente_fd, tsDatos dato);
void* serializar(tsDatos dato);

#endif /* CLIENTE_H_ */
