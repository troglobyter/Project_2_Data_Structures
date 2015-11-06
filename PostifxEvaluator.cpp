#include "Evaluator.h"
#include <sstream>
#include <cctype>
#include <string>

using namespace std; 

bool is_operator(char ch);

bool is_number(char c);

int EvaluateOperation(char operation, int operand1, int operand2);


int PostfixEvaluator(string postfix_expression)
{
  
    stack<int> S;

    for (int i = 0; i< postfix_expression.length(); i++) {

        if (postfix_expression[i] == ' ' || postfix_expression[i] == ',') continue;

        
        else if (is_operator(postfix_expression[i])) {
            int operand2 = S.top(); 
            S.pop();
            int operand1 = S.top(); 
            S.pop();
            int result = EvaluateOperation(postfix_expression[i], operand1, operand2); 
            S.push(result);
        }
        else if(is_number(postfix_expression[i])){
            int operand = 0;
            while (i<postfix_expression.length() && is_number(postfix_expression[i])) {
                operand = (operand * 10) + (postfix_expression[i] - '0');
                i++;
            }
            i--;

            S.push(operand);
        }
    }

    return S.top();
}
