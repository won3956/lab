libarithmatic.so.1.0.1: add.o subtract.o multiple.o divide.o
	 gcc -shared -Wl,-soname,libarithmatic.so.1 -o libarithmatic.so.1.0.1 add.o subtract.o multiple.o divide.o
	 ln -sf libarithmatic.so.1.0.1 libarithmatic.so.1
	 ln -sf libarithmatic.so.1.0.1 libarithmatic.so

add.o: add.c
	 gcc -c -fPIC add.c

subtract.o: subtract.c
	 gcc -c -fPIC subtract.c

multiple.o: multiple.c
	 gcc -c -fPIC multiple.c

divide.o: divide.c
	 gcc -c -fPIC divide.c

clean:
	 rm -f libarithmatic.so.1.0.1 libarithmatic.so.1 libarithmatic.so add.o subtract.o multiple.o divide.o
