TARGET=Tiny
SOURCE=parser.cpp lexer.cpp main.cpp
OBJECT_FILES=${SOURCE:.cpp=.o}

$(TARGET): $(OBJECT_FILES)
	g++ -o $@ $^

lexer.cpp: lexer.l
	flex -o $@ $<

parser.cpp: parser.y
	bison -v -rall --defines=tokens.h -o $@ $<

%.o: %.cpp tokens.h
	g++ -c $<

run: $(TARGET)
	./$(TARGET) < ./samples/quicksort.c

test: $(TARGET)
	./$(TARGET) < ./samples/if_test.cpp
	./$(TARGET) < ./samples/quicksort.c
	./$(TARGET) < ./samples/interpolation_search.c
	./$(TARGET) < ./samples/sample.cpp

clean:
	rm -f lexer.cpp parser.cpp *.o
	rm -f $(TARGET)