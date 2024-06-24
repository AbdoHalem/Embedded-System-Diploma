#@Copyright : Abdo Halem

CC=arm-none-eabi
CFLAGS= -gdwarf-2 -mcpu=cortex-m4 -g
INCS=-I .
LIBS=
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
#As = $(wildcard *.s)
#AsOBJ = $(As:.s=.o)
Project_name=Unit3_Lesson4_Lab3_cortex_m4

all: $(Project_name).bin
	@echo "=========Build is Done========="

#startup.o: startup.s
#	$(CC)-as $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)-gcc -c $(CFLAGS) -mthumb $(INCS) $< -o $@
	
$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)-ld -T linker_script.ld  $(LIBS) $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)-objcopy -O binary $< $@

clean_all:
	rm *.o *.elf *.bin
	
clean:
	rm *.elf *.bin
