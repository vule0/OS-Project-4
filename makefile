all: myls mysearch mystat mytail

myls: myls-Vu.c
	gcc myls-Vu.c -o myls

mysearch: mysearch-Vu.c
	gcc mysearch-Vu.c -o mysearch -std=c99

mystat: mystat-Vu.c
	gcc mystat-Vu.c -o mystat

mytail: mytail-Vu.c
	gcc mytail-Vu.c -o mytail