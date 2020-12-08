__start__: obj __lines_for_space__ interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp ../opis_dzialan/opis_dzialan.cmd

obj:
	mkdir obj


__lines_for_space__:
	@echo
	@echo
	@echo
	@echo
	@echo


__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -pedantic -std=c++17 -Iinc
LDFLAGS=-Wall




interp: obj/xmlinterp.o obj/main.o 
	g++ ${LDFLAGS} -o interp obj/xmlinterp.o obj/main.o -ldl -lxerces-c -lpthread

obj/xmlinterp.o: src/xmlinterp.cpp inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/xmlinterp.o src/xmlinterp.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh
	g++ ${LDFLAGS} -o obj/Scene.o src/Scene.cpp

obj/Set4LibInterfaces.o: src/Set4LibInterfaces.cpp inc/Set4LibInterfaces.hh
	g++ ${LDFLAGS} -o obj/Set4LibInterfaces.o src/Set4LibInterfaces.cpp

obj/LibInterface.o: src/LibInterface.cpp inc/LibInterface.hh
	g++ ${LDFLAGS} -o obj/LibInterface.o src/LibInterface.cpp

obj/main.o: src/main.cpp inc/Interp4Command.hh  inc/xmlinterp.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
