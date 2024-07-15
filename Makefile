# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 12:27:42 by ciglesia          #+#    #+#              #
#    Updated: 2024/07/16 01:40:16 by ciglesia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BIN         =   kernel.bin
ISO         =   kernel.iso

#****************** INC *******************#

INC			=   ./include/
INCLUDE		=   -I $(INC)

#****************** SRC *******************#

DIRSRC      =   ./kernel/
SRC         =   kernel.c terminal.c gdt.c printk.c
GDT			=	load_gdt.s

DIRASM	  	=   ./boot/
ASM			=	boot.s

DIRLNK		=   ./linker/
LNK			=	$(DIRLNK)linker.ld

DIRISO		=	./iso/
GRUB_CFG	=	./grub/grub.cfg

#****************** OBJ *******************#

DIROBJ      =   ./obj/

#============================== END OF CONFIG ===============================#

OAUX        =   $(SRC:%=$(DIROBJ)%)
DEPS        =   $(OBJS:.o=.d)
OBJS        =   $(OAUX:.c=.o)
OASM		=	$(DIROBJ)$(ASM:.s=.o)
OGDT		=	$(DIROBJ)$(GDT:.s=.o)

.ONESHELL:
$(shell mkdir -p $(DIROBJ))

ifndef VERBOSE
.SILENT:
endif

#****************** RULES *******************#

CFLAGS      =   -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS      =   -ffreestanding -O2 -nostdlib -lgcc

ENV         =   /usr/bin/env
AC          =   $(ENV) i386-elf-as
CC          =   $(ENV) i386-elf-gcc
LC          =   $(CC)
CP          =   $(ENV) cp
RM          =   $(ENV) rm -rf
MKDIR       =   $(ENV) mkdir -p
PRINTF      =   $(ENV) printf

GREEN       =   "\e[92m"
E0M         =   "\e[0m"

#****************** COMPILER CHECKS *******************#

define n


endef

CC_CHECK := $(shell which $(CC) 2>&1)
ifeq (,$(findstring i386-elf,$(CC_CHECK)))
    $(error $nThis kernel needs to be compiled with an ix86-elf compiler!\
	$nPlease use "./build.sh" to make the project in a Docker container.$n)
endif

#****************** TARGETS *******************#

%.o         :   ../$(DIRSRC)/%.c
				@$(PRINTF) $(GREEN)"Generating kernel objects... %-33.33s\r"$(E0M) $@
				$(CC) $(CFLAGS) $(INCLUDE) -MMD -c $< -o $@

#******************* ISO ********************#

define create_iso
    $(MKDIR) $(DIRISO)boot/grub
    $(CP) $(BIN) $(DIRISO)boot/kernel.bin
    $(CP) $(GRUB_CFG) $(DIRISO)boot/grub/grub.cfg
    grub-mkrescue -o $(ISO) $(DIRISO)
	@$(PRINTF) $(GREEN)"ISO created... %-33.33s\n"$(E0M) $(ISO)
endef

#****************** RULES *******************#

$(BIN)     :   $(OBJS)
				@$(PRINTF) $(GREEN)"\nCompiling kernel... %-33.33s\n"$(E0M) $@
				$(AC) $(DIRASM)$(ASM) -o $(OASM)
				$(AC) $(DIRSRC)$(GDT) -o $(OGDT)
				$(LC) -T $(LNK) -o $(BIN) $(OASM) $(OGDT) $(OBJS) $(LFLAGS)
				$(call create_iso)

all         :   $(BIN)

clean       :
				@$(PRINTF) $(GREEN)"Cleaning kernel objects... %-33.33s\n"$(E0M) $(DIROBJ)
				$(RM) $(DIROBJ)

fclean      :   clean
				@$(PRINTF) $(GREEN)"Cleaning kernel binary... %-33.33s\n"$(E0M) $(BIN)
				$(RM) $(BIN)
				$(RM) $(ISO)
				$(RM) $(DIRISO)

re          :   fclean mkdepo all

mkdepo		:
				@$(MKDIR) $(DIROBJ)

.PHONY      :   all clean fclean re
