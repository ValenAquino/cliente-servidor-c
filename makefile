H_SRCS=$(shell find shared/shared -iname "*.h" | tr '\n' ' ')

ifneq ($(shell id -un),root)
SUDO=sudo
endif

all:
	@echo "Compilando SHARED"
	@make all -C ./shared/Debug
	@echo "----------------- \n"
	@echo "Compilando CLIENTE"
	@make all -C ./cliente/Debug
	@echo "----------------- \n"
	@echo "Compilando SERVIDOR"
	@make all -C ./servidor/Debug
	@echo "----------------- \n"

install: all
	$(SUDO) cp -u ./shared/Debug/libshared.so /usr/lib
	$(SUDO) cp --parents -u $(H_SRCS) /usr/include

uninstall:
	$(SUDO) rm -f /usr/lib/libshared.so
	$(SUDO) rm -rf /usr/include/sharelibshared
	
clean: uninstall
	@make clean -C ./shared/Debug