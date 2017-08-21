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
	./$(TARGET) < ./tests/quicksort.c

test: $(TARGET)
	./$(TARGET) < ./tests/if_test.cpp
	./$(TARGET) < ./tests/quicksort.c
	./$(TARGET) < ./tests/interpolation_search.c
	./$(TARGET) < ./tests/sample.cpp

clean:
	rm -f lexer.cpp parser.cpp *.o
	rm -f $(TARGET)