DIR_SYSTEM=/home/i02tomag/Escritorio/REDES/MUÑOZ_LOPEZ_y_MARQUEZ_DE_TORRES

all: servidor cliente Clean

servidor: p1-servidor.cpp 
	g++ $^ -Wno-multichar -Wno-type-limits -o servidor

cliente: p1-cliente.cpp 
	g++ $^ -Wno-multichar -Wno-type-limits -o cliente

.Phony: Clean
Clean:
	rm -f *.o 