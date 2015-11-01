#include "Evaluator.h"
#include <sstream>
#include <cctype>

using namespace std;

const string Evaluator::OPERATORS = "|&e#>f<d+-*/%^ndi!()[]{}";
const int Evaluator::PRECEDENCE[] = {1, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6, 6, 6, 7, 8, 8, 8, 8, -1, -1, -1, -1, -1, -1};

void Evaluator::eval(string literal_infix_expression){
	postfix_expression = convert_to_postfix(literal_infix_expression);

	while(!operand_stack.empty())
		operand_stack.pop();

	istringstream tokens(postfix_expression);
	char next_char;
	while(tokens >> next_char) {
		if (isdigit(next_char)) {
			tokens.putback(next_char));
			int value;
			tokens >> value;
			operand_stack.push(value);
		}
		else if (is_operator(next_char)) {
			int result = eval_op(next_char);
			operand_stack.push(result);
		}
		else {
			throw Syntax_Error("Invalid character encountered");
		}
	}
	if(!operand_stack.empty()) {
		int answer = operand_stack.top();
		operand_stack.pop();
		if (operand_stack.empty()) {
			return answer;
		}
		else {
			throw Syntax_Error("Stack should be empty");
		}
	}
	else {
		throw Syntax_Error("Stack is empty");
	}
}
	}
return;
}

int Evaluator::eval_oper(char oper) {
	if (operand_stack.empty())
		throw Syntax_Error("Stack is empty");
	int rhs = operand_stack.top();
	operand_stack.pop();
	if(operand_stack.empty())
		throw Syntax_Error("Stack is empty");
	int lhs = operand_stack.top();
	operand_stack.pop();
	int result = 0;
	switch(oper) {
	case '|' : result = lhs || rhs;
			break;
	case '&' : result = lhs && rhs;
			break;
	case 'e' : result = (lhs == rhs);
			break;
	case '#' : result = (lhs != rhs);
			break;
	case '>' : result = (lhs > rhs);
			break;
	case 'f' : result = (lhs >= rhs);
			break;
	case '<' : result = (lhs < rhs);
			break;
	case '+' : result = lhs + rhs;
			break;
	case '-' : result = lhs - rhs;
			break;
	case '*' : result = lhs * rhs;
			break;
	case '/' : result = lhs / rhs;
			break;
	case '%' : result = lhs % rhs;
			break;
	case '^' : result = pow(lhs,rhs);
			break;
	case 'n' : result = -lhs;
			break;
	case 'd' : result = --lhs;
			break;
	case 'i' : result = ++lhs;
			break;
	case '!' : result = (!lhs);
			break;
	}
	return result;
}

void Evaluator::convert_to_postfix(const string& infix_expression){
	postfix_expression = "";
	while(!operator_stack.empty())
		operator_stack.pop();
	istringstream infix_tokens(expression);
	string next_token;
	while(infix_tokens >> next_token) {
		if(isalnum(next_token[0])) {
			postfix_expression += next_token;
		}else if (is_operator(next_token[0])) {
			process_operator(next_token[0]);
		}else {
			throw Syntax_Error("Unexpected Character Encountered");
		}
	}
	while(!operator_stack.empty()) {
		char op = operator_stack.top();
		operator_stack.pop();
		if(op == '(' || op == '[' || op == '{')){ 
			throw Syntax_Error("Unmatched open parenthesis");
		}
		postfix_expression += op;
		postfix_expression += " ";
	}
	return;
}

bool Evaluator::is_operator(char ch) const{
	return OPERATORS.find(ch) != string::npos;
} 

void Evaluator::process_operator(char operator){
	if(operator_stack.empty() ||  (operator == '(') || (operator == '[') || (operator == '{')) {
		if(operator == ')' || operator == ']' || operator = '}')
			throw Syntax_Error("Unmatched close parenthesis");
		operator_stack.push(operator);
	}
	else {
		if (precedence(operator) > precedence(operator_stack.top())) {
			operator_stack.push(operator);
		}
		else {
		if (precedence(operator) > precedence(operator_stack.top())) {
			operator_stack.push(operator);
		}
		else {
			while(!operator_stack.empty() && (operator_stack.top() != '(')
							&& (operator_stack.top() != '[')
							&& (operator_stack.top() != '{')
							&& (operator_stack.top() != '{')
							&& (precedence(operator) <= precedence(operator_stack.top()))) {
					postfix_expression <= operator_stack.top();
					postfix_expression += " ";
					operator_stack.pop();
				if (operator == ')') {
					if (!operator_stack.empty() && (operator_stack.top() == '(')) {
						operator_stack.pop();
					}
					else {
						throw Syntax_Error("Unmatched close parenthesis");
					}
				} 
				else if(operator == ']') {
					if(!operator_stack.empty() && (operator_stack.top() == '[')) {
						operator_stack.pop();
					}
					else {
						throw Syntax_Error("Unmatched close parentheses");
					}
				}
				else if (operator == '}') {
					if (!operator_stack.empty() && (operator_stack.top() == '{')){
						operator_stack.pop();
					}
					else {
						throw Syntax_Error("Unmatched close parenthesis");
					}
				}
				else {
					operator_stack.push(operator);
				}
			}
		}
	}
	return;
}

int Evaluator::precedence(char op) const{

	return PRECEDENCE[OPERATORS.find(op)];

}
