TARGET=Tiny
AST_EXPRESSION=./ast/expressions
BINARY_EXPRESSION=${AST_EXPRESSION}/binary
PRIMARY_EXPRESSION=${AST_EXPRESSION}/primary
POSTFIX_EXPRESSION=${AST_EXPRESSION}/postfix
UNARY_EXPRESSION=${AST_EXPRESSION}/unary

PURE_HEADER=ast.h ${AST_EXPRESSION}/expression.h ${UNARY_EXPRESSION}/unary_expression.h ${BINARY_EXPRESSION}/binary_expression.h

HEADER=${PRIMARY_EXPRESSION}/id/id_expression.h ${PRIMARY_EXPRESSION}/char/char_expression.h ${PRIMARY_EXPRESSION}/string/string_expression.h ${PRIMARY_EXPRESSION}/int/int_expression.h ${AST_EXPRESSION}/expression_list/expression_list.h ${POSTFIX_EXPRESSION}/array/array_expression.h ${POSTFIX_EXPRESSION}/function/function_expression.h ${POSTFIX_EXPRESSION}/post_increment/post_increment_expression.h ${POSTFIX_EXPRESSION}/post_decrement/post_decrement_expression.h ${UNARY_EXPRESSION}/pre_increment/pre_increment_expression.h ${UNARY_EXPRESSION}/pre_decrement/pre_decrement_expression.h ${UNARY_EXPRESSION}/pointer/pointer_expression.h ${UNARY_EXPRESSION}/address/address_expression.h ${UNARY_EXPRESSION}/negative/negative_expression.h ${UNARY_EXPRESSION}/positive/positive_expression.h ${UNARY_EXPRESSION}/two_complement/two_complement_expression.h ${UNARY_EXPRESSION}/negation/negation_expression.h ${BINARY_EXPRESSION}/mult/mult_expression.h ${BINARY_EXPRESSION}/div/div_expression.h ${BINARY_EXPRESSION}/mod/mod_expression.h

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
	rm -f lexer.cpp parser.cpp *.o
	rm -f $(BINARY_EXPRESSION)/**/*.o
	rm -f $(PRIMARY_EXPRESSION)/**/*.o
	rm -f $(POSTFIX_EXPRESSION)/**/*.o
	rm -f $(UNARY_EXPRESSION)/**/*.o
	rm -f $(AST_EXPRESSION)/**/*.o
	rm -f $(TARGET)