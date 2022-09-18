H_SRCS=$(shell find ./shared -type f -iname "*.h" -exec basename {} \;)

ifneq ($(shell id -un),root)
SUDO=sudo
endif

all:
	@echo "Compilando SHARED"
	@make all -C ./shared/Debug
	@echo "----------------- \n"

compilar:
	@echo "Compilando CLIENTE"
	@make all -C ./cliente/Debug
	@echo "----------------- \n"
	@echo "Compilando SERVIDOR"
	@make all -C ./servidor/Debug
	@echo "----------------- \n"
mos:
	@echo $(H_SRCS)

install: all makefolder
	$(SUDO) cp -u ./shared/Debug/libshared.so /usr/lib
	$(SUDO) cp -u ./shared/shared/$(H_SRCS) /usr/include/shared

makefolder:
	$(SUDO) mkdir /usr/include/shared

uninstall:
	$(SUDO) rm -f /usr/lib/libshared.so
	$(SUDO) rm -rf /usr/include/shared
	
clean: uninstall
	@make clean -C ./shared/Debug
