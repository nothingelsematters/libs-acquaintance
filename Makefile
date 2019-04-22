GCC = g++
SRC = library_sources
LIBDYNAMIC = libdynamic.so
MAIN = main
USING_LIBRARY = export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${PWD};

static: $(SRC).o $(MAIN).o
	ar rcs libstatic.a $(SRC).o
	$(GCC) $(MAIN).o -L. -lstatic -o statically-linked
	./statically-linked

dynamic: $(LIBDYNAMIC) $(MAIN).o
	$(GCC) $(MAIN).o -L. -ldynamic -o dynamically-linked
	$(USING_LIBRARY) ./dynamically-linked

loading: $(LIBDYNAMIC)
	$(GCC) -rdynamic loading_main.cpp -ldl -o loading
	$(USING_LIBRARY) ./loading

$(SRC).o:
	$(GCC) -c $(SRC).cpp

$(MAIN).o:
	$(GCC) -c $(MAIN).cpp

$(LIBDYNAMIC):
	$(GCC) -fPIC -shared $(SRC).cpp -o $(LIBDYNAMIC)

clean:
	rm -vf *.o *.a *.out *.so statically-linked dynamically-linked loading
