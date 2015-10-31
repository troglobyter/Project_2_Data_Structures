#include <string>
#include <stack>

class Evaluator{

	public:
	int eval(string literal_infix_expression);

	private:
	void eval_oper(char oper);

	void convert_to_postfix(const string& infix_expression);
	bool is_operator(char ch) const;
	void process_operator(char operator);	
	int precedence(char hi_op) const;
	static const string OPERATORS;
	static const int PRECEDENCE[];
	string postfix_expression;
	
	stack<char> operator_stack;
	stack<int> operand_stack;
};