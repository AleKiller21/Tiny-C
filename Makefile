TARGET=Tiny
AST_EXPRESSION=./ast/expressions
BINARY_EXPRESSION=$(AST_EXPRESSION)/binary
PRIMARY_EXPRESSION=$(AST_EXPRESSION)/primary
POSTFIX_EXPRESSION=$(AST_EXPRESSION)/postfix
UNARY_EXPRESSION=$(AST_EXPRESSION)/unary
AST_STATEMENT=./ast/statements

PURE_HEADER=ast.h $(AST_EXPRESSION)/expression.h $(UNARY_EXPRESSION)/unary_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(AST_STATEMENT)/statement.h

HEADER=$(PRIMARY_EXPRESSION)/id/id_expression.h $(PRIMARY_EXPRESSION)/char/char_expression.h $(PRIMARY_EXPRESSION)/string/string_expression.h $(PRIMARY_EXPRESSION)/int/int_expression.h $(AST_EXPRESSION)/expression_list/expression_list.h $(POSTFIX_EXPRESSION)/array/array_expression.h $(POSTFIX_EXPRESSION)/function/function_expression.h $(POSTFIX_EXPRESSION)/post_increment/post_increment_expression.h $(POSTFIX_EXPRESSION)/post_decrement/post_decrement_expression.h $(UNARY_EXPRESSION)/pre_increment/pre_increment_expression.h $(UNARY_EXPRESSION)/pre_decrement/pre_decrement_expression.h $(UNARY_EXPRESSION)/pointer/pointer_expression.h $(UNARY_EXPRESSION)/address/address_expression.h $(UNARY_EXPRESSION)/negative/negative_expression.h $(UNARY_EXPRESSION)/positive/positive_expression.h $(UNARY_EXPRESSION)/two_complement/two_complement_expression.h $(UNARY_EXPRESSION)/negation/negation_expression.h $(BINARY_EXPRESSION)/mult/mult_expression.h $(BINARY_EXPRESSION)/div/div_expression.h $(BINARY_EXPRESSION)/mod/mod_expression.h $(BINARY_EXPRESSION)/sum/sum_expression.h $(BINARY_EXPRESSION)/sub/sub_expression.h $(BINARY_EXPRESSION)/lshift/lshift_expression.h $(BINARY_EXPRESSION)/rshift/rshift_expression.h $(BINARY_EXPRESSION)/less/less_expression.h $(BINARY_EXPRESSION)/less_equal/less_equal_expression.h $(BINARY_EXPRESSION)/greater_equal/greater_equal_expression.h $(BINARY_EXPRESSION)/greater/greater_expression.h $(BINARY_EXPRESSION)/equal/equal_expression.h $(BINARY_EXPRESSION)/not_equal/not_equal_expression.h $(BINARY_EXPRESSION)/and/and_expression.h $(BINARY_EXPRESSION)/xor/xor_expression.h $(BINARY_EXPRESSION)/or/or_expression.h $(BINARY_EXPRESSION)/logical_and/logical_and_expression.h $(BINARY_EXPRESSION)/logical_or/logical_or_expression.h $(AST_EXPRESSION)/conditional/conditional_expression.h $(BINARY_EXPRESSION)/assign/assign_equal/assign_equal_expression.h $(BINARY_EXPRESSION)/assign/mult_equal/mult_equal_expression.h $(BINARY_EXPRESSION)/assign/div_equal/div_equal_expression.h $(BINARY_EXPRESSION)/assign/mod_equal/mod_equal_expression.h $(BINARY_EXPRESSION)/assign/sum_equal/sum_equal_expression.h $(BINARY_EXPRESSION)/assign/sub_equal/sub_equal_expression.h $(BINARY_EXPRESSION)/assign/lshift_equal/lshift_equal_expression.h $(BINARY_EXPRESSION)/assign/rshift_equal/rshift_equal_expression.h $(BINARY_EXPRESSION)/assign/and_equal/and_equal_expression.h $(BINARY_EXPRESSION)/assign/xor_equal/xor_equal_expression.h $(BINARY_EXPRESSION)/assign/or_equal/or_equal_expression.h $(AST_STATEMENT)/return/return_statement.h $(AST_STATEMENT)/break/break_statement.h $(AST_STATEMENT)/continue/continue_statement.h $(AST_STATEMENT)/expression/expression_statement.h $(AST_STATEMENT)/for/for_statement.h $(AST_STATEMENT)/while/while_statement.h $(AST_STATEMENT)/if/if_statement.h $(AST_STATEMENT)/list/statement_list.h

SOURCE=$(HEADER:.h=.cpp) parser.cpp lexer.cpp main.cpp
OBJECT_FILES=$(SOURCE:.cpp=.o)

$(TARGET): $(OBJECT_FILES)
	g++ -o $@ $^

lexer.cpp: lexer.l
	flex -o $@ $<

parser.cpp: parser.y
	bison -v -rall --defines=tokens.h -o $@ $<

$(PRIMARY_EXPRESSION)/id/id_expression.o: $(PRIMARY_EXPRESSION)/id/id_expression.cpp $(PRIMARY_EXPRESSION)/id/id_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(PRIMARY_EXPRESSION)/char/char_expression.o: $(PRIMARY_EXPRESSION)/char/char_expression.cpp $(PRIMARY_EXPRESSION)/char/char_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(PRIMARY_EXPRESSION)/string/string_expression.o: $(PRIMARY_EXPRESSION)/string/string_expression.cpp $(PRIMARY_EXPRESSION)/string/string_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(PRIMARY_EXPRESSION)/int/int_expression.o: $(PRIMARY_EXPRESSION)/int/int_expression.cpp $(PRIMARY_EXPRESSION)/int/int_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_EXPRESSION)/expression_list/expression_list.o: $(AST_EXPRESSION)/expression_list/expression_list.cpp $(AST_EXPRESSION)/expression_list/expression_list.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(POSTFIX_EXPRESSION)/array/array_expression.o: $(POSTFIX_EXPRESSION)/array/array_expression.cpp $(POSTFIX_EXPRESSION)/array/array_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(POSTFIX_EXPRESSION)/function/function_expression.o: $(POSTFIX_EXPRESSION)/function/function_expression.cpp $(POSTFIX_EXPRESSION)/function/function_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(POSTFIX_EXPRESSION)/post_increment/post_increment_expression.o: $(POSTFIX_EXPRESSION)/post_increment/post_increment_expression.cpp $(POSTFIX_EXPRESSION)/post_increment/post_increment_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(POSTFIX_EXPRESSION)/post_decrement/post_decrement_expression.o: $(POSTFIX_EXPRESSION)/post_decrement/post_decrement_expression.cpp $(POSTFIX_EXPRESSION)/post_decrement/post_decrement_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/pre_increment/pre_increment_expression.o: $(UNARY_EXPRESSION)/pre_increment/pre_increment_expression.cpp $(UNARY_EXPRESSION)/pre_increment/pre_increment_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/pre_decrement/pre_decrement_expression.o: $(UNARY_EXPRESSION)/pre_decrement/pre_decrement_expression.cpp $(UNARY_EXPRESSION)/pre_decrement/pre_decrement_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/pointer/pointer_expression.o: $(UNARY_EXPRESSION)/pointer/pointer_expression.cpp $(UNARY_EXPRESSION)/pointer/pointer_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/address/address_expression.o: $(UNARY_EXPRESSION)/address/address_expression.cpp $(UNARY_EXPRESSION)/address/address_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/negative/negative_expression.o: $(UNARY_EXPRESSION)/negative/negative_expression.cpp $(UNARY_EXPRESSION)/negative/negative_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/positive/positive_expression.o: $(UNARY_EXPRESSION)/positive/positive_expression.cpp $(UNARY_EXPRESSION)/positive/positive_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/two_complement/two_complement_expression.o: $(UNARY_EXPRESSION)/two_complement/two_complement_expression.cpp $(UNARY_EXPRESSION)/two_complement/two_complement_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(UNARY_EXPRESSION)/negation/negation_expression.o: $(UNARY_EXPRESSION)/negation/negation_expression.cpp $(UNARY_EXPRESSION)/negation/negation_expression.h $(UNARY_EXPRESSION)/unary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/mult/mult_expression.o: $(BINARY_EXPRESSION)/mult/mult_expression.cpp $(BINARY_EXPRESSION)/mult/mult_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/div/div_expression.o: $(BINARY_EXPRESSION)/div/div_expression.cpp $(BINARY_EXPRESSION)/div/div_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/mod/mod_expression.o: $(BINARY_EXPRESSION)/mod/mod_expression.cpp $(BINARY_EXPRESSION)/mod/mod_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/sum/sum_expression.o: $(BINARY_EXPRESSION)/sum/sum_expression.cpp $(BINARY_EXPRESSION)/sum/sum_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/sub/sub_expression.o: $(BINARY_EXPRESSION)/sub/sub_expression.cpp $(BINARY_EXPRESSION)/sub/sub_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/lshift/lshift_expression.o: $(BINARY_EXPRESSION)/lshift/lshift_expression.cpp $(BINARY_EXPRESSION)/lshift/lshift_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/rshift/rshift_expression.o: $(BINARY_EXPRESSION)/rshift/rshift_expression.cpp $(BINARY_EXPRESSION)/rshift/rshift_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/less/less_expression.o: $(BINARY_EXPRESSION)/less/less_expression.cpp $(BINARY_EXPRESSION)/less/less_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/greater/greater_expression.o: $(BINARY_EXPRESSION)/greater/greater_expression.cpp $(BINARY_EXPRESSION)/greater/greater_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/greater_equal/greater_equal_expression.o: $(BINARY_EXPRESSION)/greater_equal/greater_equal_expression.cpp $(BINARY_EXPRESSION)/greater_equal/greater_equal_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/less_equal/less_equal_expression.o: $(BINARY_EXPRESSION)/less_equal/less_equal_expression.cpp $(BINARY_EXPRESSION)/less_equal/less_equal_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/equal/equal_expression.o: $(BINARY_EXPRESSION)/equal/equal_expression.cpp $(BINARY_EXPRESSION)/equal/equal_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/not_equal/not_equal_expression.o: $(BINARY_EXPRESSION)/not_equal/not_equal_expression.cpp $(BINARY_EXPRESSION)/not_equal/not_equal_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/and/and_expression.o: $(BINARY_EXPRESSION)/and/and_expression.cpp $(BINARY_EXPRESSION)/and/and_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/logical_and/logical_and_expression.o: $(BINARY_EXPRESSION)/logical_and/logical_and_expression.cpp $(BINARY_EXPRESSION)/logical_and/logical_and_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/logical_or/logical_or_expression.o: $(BINARY_EXPRESSION)/logical_or/logical_or_expression.cpp $(BINARY_EXPRESSION)/logical_or/logical_or_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/or/or_expression.o: $(BINARY_EXPRESSION)/or/or_expression.cpp $(BINARY_EXPRESSION)/or/or_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/xor/xor_expression.o: $(BINARY_EXPRESSION)/xor/xor_expression.cpp $(BINARY_EXPRESSION)/xor/xor_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_EXPRESSION)/conditional/conditional_expression.o: $(AST_EXPRESSION)/conditional/conditional_expression.cpp $(AST_EXPRESSION)/conditional/conditional_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/assign_equal/assign_equal_expression.o: $(BINARY_EXPRESSION)/assign/assign_equal/assign_equal_expression.cpp $(BINARY_EXPRESSION)/assign/assign_equal/assign_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/mult_equal/mult_equal_expression.o: $(BINARY_EXPRESSION)/assign/mult_equal/mult_equal_expression.cpp $(BINARY_EXPRESSION)/assign/mult_equal/mult_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/div_equal/div_equal_expression.o: $(BINARY_EXPRESSION)/assign/div_equal/div_equal_expression.cpp $(BINARY_EXPRESSION)/assign/div_equal/div_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/mod_equal/mod_equal_expression.o: $(BINARY_EXPRESSION)/assign/mod_equal/mod_equal_expression.cpp $(BINARY_EXPRESSION)/assign/mod_equal/mod_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/sum_equal/sum_equal_expression.o: $(BINARY_EXPRESSION)/assign/sum_equal/sum_equal_expression.cpp $(BINARY_EXPRESSION)/assign/sum_equal/sum_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/sub_equal/sub_equal_expression.o: $(BINARY_EXPRESSION)/assign/sub_equal/sub_equal_expression.cpp $(BINARY_EXPRESSION)/assign/sub_equal/sub_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/lshift_equal/lshift_equal_expression.o: $(BINARY_EXPRESSION)/assign/lshift_equal/lshift_equal_expression.cpp $(BINARY_EXPRESSION)/assign/lshift_equal/lshift_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/rshift_equal/rshift_equal_expression.o: $(BINARY_EXPRESSION)/assign/rshift_equal/rshift_equal_expression.cpp $(BINARY_EXPRESSION)/assign/rshift_equal/rshift_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/and_equal/and_equal_expression.o: $(BINARY_EXPRESSION)/assign/and_equal/and_equal_expression.cpp $(BINARY_EXPRESSION)/assign/and_equal/and_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/xor_equal/xor_equal_expression.o: $(BINARY_EXPRESSION)/assign/xor_equal/xor_equal_expression.cpp $(BINARY_EXPRESSION)/assign/xor_equal/xor_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(BINARY_EXPRESSION)/assign/or_equal/or_equal_expression.o: $(BINARY_EXPRESSION)/assign/or_equal/or_equal_expression.cpp $(BINARY_EXPRESSION)/assign/or_equal/or_equal_expression.h $(BINARY_EXPRESSION)/assign/assignment_expression.h $(BINARY_EXPRESSION)/binary_expression.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/return/return_statement.o: $(AST_STATEMENT)/return/return_statement.cpp $(AST_STATEMENT)/return/return_statement.h $(AST_STATEMENT)/statement.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/break/break_statement.o: $(AST_STATEMENT)/break/break_statement.cpp $(AST_STATEMENT)/break/break_statement.h $(AST_STATEMENT)/statement.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/continue/continue_statement.o: $(AST_STATEMENT)/continue/continue_statement.cpp $(AST_STATEMENT)/continue/continue_statement.h $(AST_STATEMENT)/statement.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/expression/expression_statement.o: $(AST_STATEMENT)/expression/expression_statement.cpp $(AST_STATEMENT)/expression/expression_statement.h $(AST_STATEMENT)/statement.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/for/for_statement.o: $(AST_STATEMENT)/for/for_statement.cpp $(AST_STATEMENT)/for/for_statement.h $(AST_STATEMENT)/statement.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/while/while_statement.o: $(AST_STATEMENT)/while/while_statement.cpp $(AST_STATEMENT)/while/while_statement.h $(AST_STATEMENT)/statement.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/if/if_statement.o: $(AST_STATEMENT)/if/if_statement.cpp $(AST_STATEMENT)/if/if_statement.h $(AST_STATEMENT)/statement.h $(AST_EXPRESSION)/expression.h
	g++ -std=c++11 -c -o $@ $<

$(AST_STATEMENT)/list/statement_list.o: $(AST_STATEMENT)/list/statement_list.cpp $(AST_STATEMENT)/list/statement_list.h $(AST_STATEMENT)/statement.h
	g++ -std=c++11 -c -o $@ $<

parser.o: parser.cpp $(PURE_HEADER) $(HEADER)
	g++ -std=c++11 -c -o $@ $<

lexer.o: lexer.cpp tokens.h $(PURE_HEADER) $(HEADER)
	g++ -std=c++11 -c -o $@ $<

main.o: main.cpp
	g++ -std=c++11 -c -o $@ $<

##################################################################



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