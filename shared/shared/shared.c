#include "../shared/shared.h"

void leer_config(char **ip, char **puerto) {
	t_config *confile;
	confile = config_create("conexion.config");

	log_trace(logger, "logger inizializado");
	log_trace(logger, "config inizializado");

	*ip = config_get_string_value(confile, "IP");
	*puerto = config_get_string_value(confile, "PUERTO");

	log_debug(logger, "ip: %s", *ip);
	log_debug(logger, "puerto: %s", *puerto);
}
