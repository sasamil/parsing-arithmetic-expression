# parsing-arithmetic-expression
New approach to parsing simple arithmetic expressions. Widely applicable, scalable and fast, hopefully.

This code-example enables transforming simple arithmetic expressions into the corresponding <i>post-order</i> rpn form.
It's not very likely that there can be anything new in the field of algorithms for parsing arithmetic expressions. 
However, I was googling a bit and so far, I have found nothing similar to this approach!? No stack, no state machine, no Shunting-Yard, no anything in this algorithm! So, I'll consider it new, for a while...

I find this approach promissing because it is scallable. It should be very simple to add new operators and rules. All the same, we can apply this algorithm for different tasks. In a pretty much the same way, we can efficiently make AST trees, evaluate expressions, present them in <i>pre-order</i> form, handle unary operators and functions, etc. In addition, the applied code is expected to be small and readable, as a consiquence of a simple and straightforward idea.

The main idea of this approach is: 

a) We are searching for an operator of the lowest precedence level which is not embraced by any parentheses. We are always searching backwards i.e. if the operators associativity is left-to-right, we are searching from right-to-left in the expression. If the operators associativity is right-to-left, we are searching from left-to-right. 

b) When an operator is found, we are using the simple recursive formula, depending of the task we are doing:<br/>
in the case of reverse Polish notation, it would be: rpn = rpn(left subexpression) + rpn(right subexpression) + (operator)<br/>
in the case of evaluation, it would be: eval = apply_operator(eval(left_subexpression), eval(right_subexpression))<br/> 
in the case of building AST tree: ast = operator_node(ast(left_subexpression), ast(right_subexpression))<br/> 
etc.

c) If no operator has been found, we are going to make next try with the operators of the next (higher) precedence level.

d) If we have made searches for all the operators from all the precedence levels and found nothing - it means that entire expression if is enclosed within the redundant parentheses (e.g. (x+y-z) ). In that case, parentheses should be just trimmed on both ends.
