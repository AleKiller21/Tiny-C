TARGET=Tiny
AST_EXPRESSION=./ast/expressions
PURE_HEADER=ast.h ${AST_EXPRESSION}/expression.h ${AST_EXPRESSION}/unary/unary_expression.h
HEADER=${AST_EXPRESSION}/primary/id/id_expression.h ${AST_EXPRESSION}/primary/char/char_expression.h ${AST_EXPRESSION}/primary/string/string_expression.h ${AST_EXPRESSION}/primary/int/int_expression.h ${AST_EXPRESSION}/expression_list/expression_list.h ${AST_EXPRESSION}/postfix/array/array_expression.h ${AST_EXPRESSION}/postfix/function/function_expression.h ${AST_EXPRESSION}/postfix/post_increment/post_increment_expression.h ${AST_EXPRESSION}/postfix/post_decrement/post_decrement_expression.h ${AST_EXPRESSION}/unary/pre_increment/pre_increment_expression.h ${AST_EXPRESSION}/unary/pre_decrement/pre_decrement_expression.h ${AST_EXPRESSION}/unary/pointer/pointer_expression.h ${AST_EXPRESSION}/unary/address/address_expression.h ${AST_EXPRESSION}/unary/negative/negative_expression.h ${AST_EXPRESSION}/unary/positive/positive_expression.h ${AST_EXPRESSION}/unary/two_complement/two_complement_expression.h ${AST_EXPRESSION}/unary/negation/negation_expression.h
SOURCE=${HEADER:.h=.cpp} parser.cpp lexer.cpp main.cpp
OBJECT_FILES=${SOURCE:.cpp=.o}

$(TARGET): $(OBJECT_FILES)
	g++ -o $@ $^

lexer.cpp: lexer.l
	flex -o $@ $<

parser.cpp: parser.y
	bison -v -rall --defines=tokens.h -o $@ $<

%.o: %.cpp tokens.h $(PURE_HEADER) $(HEADER)
	g++ -std=c++11 -c -o $@ $<

run: $(TARGET)
	./$(TARGET) < ./samples/quicksort.c

test: $(TARGET)
	./$(TARGET) < ./samples/if_test.cpp
	./$(TARGET) < ./samples/quicksort.c
	./$(TARGET) < ./samples/interpolation_search.c
	./$(TARGET) < ./samples/sample.cpp
	./$(TARGET) < ./samples/routines.c

clean:
	rm -f lexer.cpp parser.cpp *.o $(AST_EXPRESSION)/**/**/*.o
	rm -f $(TARGET)