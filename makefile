H_SRCS=$(shell find ./shared -type f -iname "*.h" -exec basename {} \;)

ifneq ($(shell id -un),root)
SUDO=sudo
endif

all: install
	@echo "Compilando CLIENTE"
	@make all -C ./cliente/Debug
	@echo "\n-----------------\n"
	@echo "Compilando SERVIDOR"
	@make all -C ./servidor/Debug
	@echo "\n-----------------\n"

install: makefolder
	@echo "\nCompilando SHARED"
	@make all -C ./shared/Debug
	@echo "\n-----------------\n"
	@echo "Instalando SHARED"
	$(SUDO) cp -u ./shared/Debug/libshared.so /usr/lib
	$(SUDO) cp -u ./shared/shared/$(H_SRCS) /usr/include/shared
	@echo "\n-----------------\n"

makefolder:
	@$(SUDO) mkdir -p /usr/include/shared

uninstall:
	$(SUDO) rm -f /usr/lib/libshared.so
	$(SUDO) rm -rf /usr/include/shared
	
clean: uninstall
	@make clean -C ./shared/Debug
	@echo ">>> shared cleaned \n"
	@make clean -C ./cliente/Debug
	@echo ">>> cliente cleaned \n"
	@make clean -C ./servidor/Debug
	@echo ">>> servidor cleaned \n"
