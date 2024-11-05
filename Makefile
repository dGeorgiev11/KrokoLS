

krokols: main.o utils.o
	g++ ./obj/main.o ./obj/utils.o -o krokols

main.o: 
	g++ -c ./src/main.cpp -o ./obj/main.o

utils.o: 
	g++ -c ./src/utils.cpp -o ./obj/utils.o

clean:
	rm krokols obj/*.o /usr/local/bin/kls

install: krokols
	cp krokols /usr/local/bin/kls	
