// Pislari Vadim 323CB 
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "link_emulator/lib.h"

#define HOST "127.0.0.1"
#define PORT 10000

int main(int argc,char** argv){
  init(HOST,PORT);
  msg t;

  // deschiderea fisierului
  int file_code = open(argv[1], O_RDONLY);
  if(file_code < 0){
	printf("file open error");
        return 1;
  }

  // determinarea parametrilor necesari
  int tt = atoi(argv[2]), tp = atoi(argv[3]);
  int len = (tt*tp*1000) / (8 * sizeof(msg));
  int file_dim = lseek(file_code ,0L, SEEK_END);
  int cadre = file_dim / (MSGSIZE - 6);
  if(file_dim % (MSGSIZE - 6) != 0) cadre++;
  msg *arr = malloc(sizeof(msg) * cadre);
  lseek(file_code, 0L, SEEK_SET);
  int ind = 0, i, j, k;
  char corrupt;
  // setarea byti-lor care indica numarul de fisiere
  arr[ind].payload[8]=(cadre >>24) & 0xFF;
  arr[ind].payload[7]=(cadre >> 16) & 0xFF;
  arr[ind].payload[6]=(cadre >> 8) & 0xFF;
  arr[ind].payload[5]=cadre & 0xFF;
  
  // setarea byti-lor care indica indicele(adica 0)
  arr[ind].payload[4]=0;
  arr[ind].payload[3]=0;
  arr[ind].payload[2]=0;
  arr[ind].payload[1]=0;
  
  // setarea denumirii fisierului
  strcpy(arr[0].payload + 9,"recv_");
  strcat(arr[0].payload + 9,argv[1]);

  // setarea checksum-ului
  corrupt = arr[0].payload[1];
  int lung = 19;
  for(i = 1; i < lung; i++){
    	corrupt = corrupt ^ (char)arr[ind].payload[1 + i];
  }
  arr[0].payload[0] = corrupt;
  arr[0].len = lung-4;
  ind++;
  
  do{
	// transmiterea indiciului format din 4 bytes puse la inceputul payload-ului
	arr[ind].payload[4] = (ind >> 24) & 0xFF;
	arr[ind].payload[3] = (ind >> 16) & 0xFF;
	arr[ind].payload[2] = (ind >> 8) & 0xFF;
	arr[ind].payload[1] = ind & 0xFF;

	// pastrarea pachetelor intr-un vector 
  	arr[ind].len = read(file_code, arr[ind].payload + 5, MSGSIZE - 6);
	
	// calcularea coruperii dintre toti byti-i pentru verificarea coruperii
	corrupt = (char) arr[ind].payload[1];
	for(i = 1; i < arr[ind].len + 4; i++){
		corrupt = corrupt ^ (char)arr[ind].payload[1 + i];
	}	
	arr[ind].payload[0] = corrupt;
	ind++;
  }while(arr[ind - 1].len == MSGSIZE - 6);
  
  // folosirea cozii pentru stocarea mesajelor trimise si 
  // determinarea celor care au fost pierdute
  int *coada = malloc(1000 * cadre * sizeof(int));
  int elem = 0,full = 0, ok = 0;
 
  for(i = 0; i < ind; ){
	// transmiterea primelor mesaje pentru a umple fereastra
	for(j = full; j < len;j++){
		if(i >= ind){
			ok = 1;
			break;
		}
		coada[elem++] = i; 
		send_message(arr + i);		
		full++;
		i++;	
	}    
   
	// daca s-au transmis toate pachetele 
	if(ok == 1)break;
  	full--;
	recv_message(&t);
	j=0;

	// se recopie toate pachetele pierdute la sfarsitul cozii
	while(t.len != coada[j]){  
	   coada[elem++] = coada[j];
	   j++;	
	}

	// daca a fost pierdut primul mesaj
	if(j!=0) {
		send_message(arr+coada[0]);
	}

	// reinitializarea datelor cozii, inceputul si dimensiunea
	elem =elem - j - 1;	
	coada = coada + j+1;					
  }

  // vector care pastreaza daca pachetele au fost primite
  int *primit = calloc(cadre + 1, sizeof(int)), mesaj = elem;
  
  // primirea ultimelor ack-uri 
  while(mesaj > 0){
	full--;

	// se verifica daca se primeste ack, daca
	// nu se retrimit pachetele pierdute
	if(recv_message_timeout(&t, 2 * tp) < 0) {
		
                // pana se umple fereastra se retransmit pachetele
		// la care nu a venit ack-ul
		while(full<len){
			for(k = 0; k < elem; k++)
				if(primit[coada[k]] == 0){
					if(full >= len)break;
					send_message(arr + coada[k]);
					full++;								
				}	
		}
	}else{

		// s-a primit ack, inseamna ca nu s-a pierdut pachetul
		primit[t.len] = 1;
  		mesaj--;
	}
  }

  recv_message(&t);
  close(file_code);
  return 0;
}
