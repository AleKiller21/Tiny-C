TARGET = Tiny
CXXFLAGS = -std=c++11 -g -Wall
CPPFLAGS = -MMD -MP

AST_EXPRESSION =./ast/expressions
AST_STATEMENT =./ast/statements
AST_DECLARATOR =./ast/declarations
AST_FUNCTION =./ast/functions
AST_TYPES =./ast/types.h

BINARY_EXPRESSION = $(AST_EXPRESSION)/binary
PRIMARY_EXPRESSION = $(AST_EXPRESSION)/primary
POSTFIX_EXPRESSION = $(AST_EXPRESSION)/postfix
UNARY_EXPRESSION = $(AST_EXPRESSION)/unary

SOURCE = $(PRIMARY_EXPRESSION)/id/id_expression.cpp $(PRIMARY_EXPRESSION)/char/char_expression.cpp \
$(PRIMARY_EXPRESSION)/string/string_expression.cpp $(PRIMARY_EXPRESSION)/int/int_expression.cpp $(AST_EXPRESSION)/expression_list/expression_list.cpp \
$(POSTFIX_EXPRESSION)/array/array_expression.cpp $(POSTFIX_EXPRESSION)/function/function_expression.cpp \
$(POSTFIX_EXPRESSION)/post_increment/post_increment_expression.cpp $(POSTFIX_EXPRESSION)/post_decrement/post_decrement_expression.cpp \
$(UNARY_EXPRESSION)/pre_increment/pre_increment_expression.cpp $(UNARY_EXPRESSION)/pre_decrement/pre_decrement_expression.cpp \
$(UNARY_EXPRESSION)/pointer/pointer_expression.cpp $(UNARY_EXPRESSION)/address/address_expression.cpp \
$(UNARY_EXPRESSION)/negative/negative_expression.cpp $(UNARY_EXPRESSION)/positive/positive_expression.cpp \
$(UNARY_EXPRESSION)/two_complement/two_complement_expression.cpp $(UNARY_EXPRESSION)/negation/negation_expression.cpp \
$(UNARY_EXPRESSION)/sizeof/sizeof_expression.cpp $(UNARY_EXPRESSION)/time/time_expression.cpp $(UNARY_EXPRESSION)/srand/srand_expression.cpp \
$(UNARY_EXPRESSION)/rand/rand_expression.cpp $(AST_EXPRESSION)/cast/cast_expression.cpp $(BINARY_EXPRESSION)/mult/mult_expression.cpp \
$(BINARY_EXPRESSION)/div/div_expression.cpp $(BINARY_EXPRESSION)/mod/mod_expression.cpp $(BINARY_EXPRESSION)/sum/sum_expression.cpp \
$(BINARY_EXPRESSION)/sub/sub_expression.cpp $(BINARY_EXPRESSION)/lshift/lshift_expression.cpp $(BINARY_EXPRESSION)/rshift/rshift_expression.cpp \
$(BINARY_EXPRESSION)/less/less_expression.cpp $(BINARY_EXPRESSION)/less_equal/less_equal_expression.cpp \
$(BINARY_EXPRESSION)/greater_equal/greater_equal_expression.cpp $(BINARY_EXPRESSION)/greater/greater_expression.cpp \
$(BINARY_EXPRESSION)/equal/equal_expression.cpp $(BINARY_EXPRESSION)/not_equal/not_equal_expression.cpp $(BINARY_EXPRESSION)/and/and_expression.cpp \
$(BINARY_EXPRESSION)/xor/xor_expression.cpp $(BINARY_EXPRESSION)/or/or_expression.cpp $(BINARY_EXPRESSION)/logical_and/logical_and_expression.cpp \
$(BINARY_EXPRESSION)/logical_or/logical_or_expression.cpp $(AST_EXPRESSION)/conditional/conditional_expression.cpp \
$(BINARY_EXPRESSION)/assign/assignment_expression.cpp $(AST_STATEMENT)/return/return_statement.cpp $(AST_STATEMENT)/break/break_statement.cpp \
$(AST_STATEMENT)/continue/continue_statement.cpp $(AST_STATEMENT)/expression/expression_statement.cpp $(AST_STATEMENT)/for/for_statement.cpp \
$(AST_STATEMENT)/while/while_statement.cpp $(AST_STATEMENT)/if/if_statement.cpp $(AST_STATEMENT)/list/statement_list.cpp \
$(AST_DECLARATOR)/simple/simple_declarator.cpp $(AST_DECLARATOR)/array/array_declarator.cpp $(AST_DECLARATOR)/parameter_list/parameter_list.cpp \
$(AST_DECLARATOR)/function/function_declarator.cpp $(AST_DECLARATOR)/initializer/initializer.cpp $(AST_DECLARATOR)/declarator_list/declarator_list.cpp \
$(AST_DECLARATOR)/declaration/declaration.cpp $(AST_DECLARATOR)/declaration_list/declaration_list.cpp $(AST_STATEMENT)/block/block_statement.cpp \
$(AST_FUNCTION)/function_definition.cpp $(UNARY_EXPRESSION)/printf/printf_expression.cpp symbol_table/symbol_table.cpp \
redundancy_manager/redundancy_manager.cpp compiler/compiler.cpp comp_utils/comp_utils.cpp label_manager/label_manager.cpp \
register_manager/register_manager.cpp stack_manager/stack_manager.cpp parser.cpp lexer.cpp main.cpp

.PHONY: clean

$(TARGET): $(SOURCE:.cpp=.o)
	g++ -o $@ $^

lexer.cpp: lexer.l
	flex -o $@ $<

parser.cpp: parser.y
	bison -v -rall --defines=tokens.h -o $@ $<

-include $(SOURCE:%.cpp=%.d)

run: $(TARGET)
	(./$(TARGET) < ../tinyc_samples/quick_sort.c) > ~/Compi2/vmipssoc/src/main.S

test: $(TARGET)
	./$(TARGET) < ./samples/if_test.cpp
	./$(TARGET) < ./samples/quicksort.c
	./$(TARGET) < ./samples/interpolation_search.c
	./$(TARGET) < ./samples/sample.cpp
	./$(TARGET) < ./samples/routines.c

clean:
	rm -f $(TARGET) lexer.cpp parser.cpp
	find . -type f -name "*.d" -exec rm {} +
	find . -type f -name "*.o" -exec rm {} +