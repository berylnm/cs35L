randlibhw.so: randlibhw.c
	gcc $(CFLAGS) randlibhw.c -shared -fPIC -o randlibhw.so
randlibsw.so: randlibsw.c
	gcc $(CFLAGS) randlibsw.c -shared -fPIC -o randlibsw.so
randmain: randcpuid.o randmain.o
	gcc $(CFLAGS) -ldl -Wl,-rpath=$(PWD) -o randmain randcpuid.o randmain.o
