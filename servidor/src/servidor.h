#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <shared/shared.h>

// Prototipos
void inicializar_modulo(char *, char *);
int iniciar_sv(char *, char *);
int esperar_cliente();
void recibir_paquete(cliente_fd);

#endif /* SERVIDOR_H_ */
