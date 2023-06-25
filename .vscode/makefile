CC=g++
CFLAGS=-std=c++11 -Wall

TARGET=aplicacao

SRC_DIR = ./src
BUILD_DIR = ./build
INCLUDE_DIR = ./include


${BUILD_DIR}/Maquina_De_Busca.o: ${INCLUDE_DIR}/busca/Maquina_De_Busca.h ${SRC_DIR}/busca/Maquina_De_Busca.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/busca/ -c ${SRC_DIR}/busca/Maquina_De_Busca.cpp -o ${BUILD_DIR}/Maquina_De_Busca.o

${BUILD_DIR}/main.o: ${INCLUDE_DIR}/busca/Maquina_De_Busca.h ${SRC_DIR}/main.cpp
	${CC} ${CFLAGS} -I ${INCLUDE_DIR}/busca/ -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o

${TARGET}: ${BUILD_DIR}/Maquina_De_Busca.o ${BUILD_DIR}/main.o
	${CC} ${CFLAGS} -o ${TARGET} ${BUILD_DIR}/*.o

clean:
	rm -f main.o
