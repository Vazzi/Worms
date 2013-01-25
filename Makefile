#Author: Jakub Vlasak
#macros
CPP	=	g++
CPPFLAGS = -Wall -pedantic -lncurses -Wno-long-long -O0 -ggdb
RM = rm -f -r
OFILES = bin/objects/main.o bin/objects/CMenu.o bin/objects/CSMenu.o bin/objects/CTMenu.o bin/objects/CHead.o bin/objects/CScene.o bin/objects/CWorm.o bin/objects/CAIWorm.o bin/objects/CTimer.o bin/objects/CPlayableWorm.o bin/objects/CSPScene.o bin/objects/CMPScene.o bin/objects/CServerScene.o bin/objects/CClientScene.o bin/objects/CInputIPMenu.o bin/objects/CConnection.o
BIN = ./Worms
#------------------------------------------------------------------
#compile
all: $(OFILES)
	make compile
#make object files
compile: $(BIN)
#run
run: $(BIN)
	 $(BIN) test
#remove binary files
clean:
	$(RM) bin $(BIN)
#make single binary files
$(BIN): $(OFILES)
	$(CPP) $(CPPFLAGS) $(OFILES) -o $(BIN)
bin/objects/main.o: src/main.cpp
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/main.cpp -o bin/objects/main.o
bin/objects/CMenu.o: src/CMenu.cpp src/CMenu.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CMenu.cpp -o bin/objects/CMenu.o
bin/objects/CSMenu.o: src/CSMenu.cpp src/CSMenu.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CSMenu.cpp -o bin/objects/CSMenu.o
bin/objects/CTMenu.o: src/CTMenu.cpp src/CTMenu.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CTMenu.cpp -o bin/objects/CTMenu.o
bin/objects/CHead.o: src/CHead.cpp src/CHead.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CHead.cpp -o bin/objects/CHead.o
bin/objects/CScene.o: src/CScene.cpp src/CScene.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CScene.cpp -o bin/objects/CScene.o
bin/objects/CWorm.o: src/CWorm.cpp src/CWorm.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CWorm.cpp -o bin/objects/CWorm.o
bin/objects/CAIWorm.o: src/CAIWorm.cpp src/CAIWorm.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CAIWorm.cpp -o bin/objects/CAIWorm.o
bin/objects/CTimer.o: src/CTimer.cpp src/CTimer.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CTimer.cpp -o bin/objects/CTimer.o
bin/objects/CPlayableWorm.o: src/CPlayableWorm.cpp src/CPlayableWorm.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CPlayableWorm.cpp -o bin/objects/CPlayableWorm.o
bin/objects/CSPScene.o: src/CSPScene.cpp src/CSPScene.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CSPScene.cpp -o bin/objects/CSPScene.o
bin/objects/CMPScene.o: src/CMPScene.cpp src/CMPScene.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CMPScene.cpp -o bin/objects/CMPScene.o
bin/objects/CServerScene.o: src/CServerScene.cpp src/CServerScene.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CServerScene.cpp -o bin/objects/CServerScene.o
bin/objects/CClientScene.o: src/CClientScene.cpp src/CClientScene.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CClientScene.cpp -o bin/objects/CClientScene.o
bin/objects/CInputIPMenu.o: src/CInputIPMenu.cpp src/CInputIPMenu.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CInputIPMenu.cpp -o bin/objects/CInputIPMenu.o
bin/objects/CConnection.o: src/CConnection.cpp src/CConnection.h
	mkdir -p bin/objects
	$(CPP) $(CPPFLAGS) -c src/CConnection.cpp -o bin/objects/CConnection.o
