EXECUTABLE = Step1
CC = g++
RM = rm -f
CFLAGS = -g -std=c++11 -Wall -Werror -DTIXML_USE_STL
OBJECTS = main.o Attack.o Condition.o Container.o Creature.o Element.o Item.o Room.o Trigger.o XMLParser.o \
	tinystr.o tinyxml.o tinyxmlerror.o tinyxmlparser.o

run: $(EXECUTABLE)
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $(EXECUTABLE) $(OBJECTS)

.cpp.o: $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o
	$(RM) $(EXECUTABLE)

.PHONY: run clean