// Pislari Vadim 323CB 

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10001
#define MAXCADRE 1000

typedef struct{
  char *aux;
  int len;
  int ind;
}Info;

 // functie de comparare
int cmpfunc(const void *a, const void *b){
 return ((*(Info *)a).ind - (*(Info *)b).ind);
}

int main(int argc,char** argv){
  msg r,t;
  init(HOST,PORT);
  int i,cadre = 0;
  
  // alocarea vectorului de structuri
  Info *arr = malloc(sizeof(Info) * MAXCADRE);
  int *primit = calloc(MAXCADRE, sizeof(int));  
  for(i = 0; i != MAXCADRE; i++){
	arr[i].aux = malloc(sizeof(char) * MSGSIZE);
  }
	
  sprintf(t.payload,"ACK");
  int nr_de_cadre_send = -1;
  char corrupt;
  int deschis =0;
  // primirea tuturor pachetelor
  do{
  	recv_message(&r);
	int value = *(int *)(r.payload + 1);
	if(primit[value] == 1) continue;
	else primit[value] = 1;
	arr[cadre].ind = value;
	arr[cadre].len = r.len;
	
	// verificarea daca nu s-a corupt nici un pachet 
	corrupt = (char) r.payload[1];
	
	for(i = 1; i < r.len+4; i++){
		corrupt = corrupt ^ (char)r.payload[1 + i];
	}

	char check = (char) r.payload[0];

	if(corrupt == check && arr[cadre].ind == 0) deschis = 1;
	if(corrupt !=check){
		primit[value] = 0;
		continue;
	}
		
	// daca s-a primit primul pachet se seteaza nr_de_cadre
	if(arr[cadre].ind == 0){
		nr_de_cadre_send = *(int *)(r.payload+5);
		strcpy(arr[cadre].aux, r.payload + 9);
	}
	else{
		// daca s-a primit alte pachete
		memcpy(arr[cadre].aux, r.payload + 5, r.len);
	}
	t.len = arr[cadre].ind;		
	send_message(&t);
	cadre++;		
  }while(cadre != nr_de_cadre_send + 1);// +1 pentru ca se primeste si numele fisierului 
 
  // sortarea pachetelor in functie de indice
  qsort(arr, cadre, sizeof(Info), cmpfunc);
  if(deschis == 1){
	// deschiderea fisierului
	int file_code = open(arr[0].aux, O_WRONLY|O_TRUNC|O_CREAT, 0644);	
	if(file_code < 0){
		printf("file open error");
		return 1;
	}
	  
	// scrierea continutului in pachet
	for(i = 1; i!= cadre; i++){
		write(file_code, arr[i].aux, arr[i].len);
	}
	  
	send_message(&t);
	close(file_code);
  }
  return 0;
}
