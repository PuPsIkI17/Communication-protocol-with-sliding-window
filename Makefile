all: send recv

link_emulator/lib.o:
	$(MAKE) -C link_emulator

send: send.o link_emulator/lib.o
	gcc -g -Werror -Wall send.o link_emulator/lib.o -o send

recv: recv.o link_emulator/lib.o
	gcc -g -Werror -Wall recv.o link_emulator/lib.o -o recv

.c.o:
	gcc -Werror -Wall -g -c $?

clean:
	$(MAKE) -C link_emulator clean
	-rm -f *.o send recv
