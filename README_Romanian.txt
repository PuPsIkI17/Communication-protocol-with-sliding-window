     	     Pislari Vadim 323CB Protocoale de Comunicatii
		     Protocol cu Fereastra glisanta
	Transmiterea eficienta a fisierului cu ajutorul ferestrei glisante
   se realizeaza in urmatorul fel: In primul rand se determina parametrii 
   necesare, speed, delay si denumirea fisierului se primesc din linia de
   comanda. Apoi se calculeaza dimensiunea ferestrei glisante, se deschide 
   fisierul, se calculeaza numarul de caractere din fisier, se determina 
   numarul de cadre(pachete) care vor fi transmise, se aloca un vector de 
   dimensiunea numarului de cadre, se citeste informatia din fisier si se 
   repartizeaza in pachete, in acelasi timp se indica si in len de la msg
   numarul de caractere citite. Primul pachet cu indicele 0 este rezervat, 
   si reprezinta denumirea fisierului. Pentru realizarea a tuturor subpun-
   ctelor este necesar de transmis in payload si indicele pachetului si un
   checksum (folosit pentru determinarea pachetului coruprt). Acestea sunt 
   insluse byte cu byte la inceputul payloadului. Checksumul e primul si 
   ocupa un byte. Indicele e un int si ocup 4 byti. In pachetul 0 dupa 
   indice este inclus si numarul de cadre care este folosit pentru a sti 
   cand sa termine receiveru-l sa primeasca mesaje cu pachete.
	Transmiterea simpla a unui fisier decurge in urmatorul fel. La 
   inceput se umple fereastra cu mesaje (send_message).Odata ce receiver-ul
   a receptionat un mesaj trimite un acknowledge. Iar cand sender-ul pri-
   meste un ack mai transmite un mesaj. Prin acest procedeu fereastra ra-
   mane mereu plina si nu se pierde timp. La sfarsit se mai primesc un numar
   de dimensiuna ferestrei-1 ack-uri. 
	In cazul in care se pierd mesaje, depistarea si retransmiterea 
   mesajelor pierdute se face in urmatorul fel: a fost creata o coada, si 
   de fiecare data cand se transmite un pachet se introduce indicele pache-
   tului in coada, si odata ce se primeste pachetul se elimina din coada.
   Daca nu a fost primit ack pentru primul pachet din coada se retransmite 
   pachetul si toate mesajele pana cu indicele diferit de cel a ack-ului se
   copie la sfarsitul cozii. Astfel mesajele pierdute vor fi retransmise 
   din nou si din nou, iar daca sunt receptionate in diferita ordine la 
   sfarsit dupa ce se primesc toate mesajele se face o sortare in ordine
   crescatoare a tuturor mesajelor dupa indice.
	Depistare pachetelor corupte se realizeaza in urmatorul fel. Se 
   face xor byte cu byte a tuturor bytilor intr-un pachet si se pastreaza
   rezultatul in checsum care se transmite in payload. Receiverul realizeaza
   acelasi lucru (byte cu byte fara checksum). Si daca in pachetul receptionat
   checksum-ul este diferit de rezultatul cautat pachetul se marcheaza ca 
   pierdut. In caz contrar este marcat ca unul bun.
	Reordonare se face in urmatorul fel. In momentul in care este primit
   un pachet el este adaugat in vector de pachete. Dupa ce sau primit toate
   pachetele se realizeaza o sortare a pachetelor in functie de indice.
	Astfel s-a realizat tema complet. Checkerul local arata 85 puncte.

