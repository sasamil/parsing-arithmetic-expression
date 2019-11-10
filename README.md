# Parsing arithmetic expressions - reverse recursive algorithm
New approach to the arithmetic expressions parsing. Applicable, scalable and fast. No stack, no state machine, no Shunting-Yard, no anything in this algorithm! It can be used in many ways depending of what we want to do with the input expression. The code-example which is given here is for transforming simple arithmetic expressions into the corresponding <i>post-order</i> <strong>R</strong>everse<strong>P</strong>olish<strong>N</strong>otation form. (Please note that this intermediary step is not needed anymore for expressions evaluating. Using this algorithm, the evaluation can be done in-place and much faster, which is demonstrated in <a href="https://github.com/sasamil/evaluating-arithmetic-expression">evaluating-arithmetic-expression</a>.)

I find this approach promissing because it is fast and scalable. As for the speed, it beats the industry-standard 'shunting-yard' algorithm. As for the scalability, it should be very simple to add new operators and rules. All the same, we can apply this algorithm/idea for quite different tasks. In a pretty much the same way, we can efficiently make AST trees, evaluate expressions, present them in  <i>post-order</i> or <i>pre-order</i> form, handle unary operators and functions, etc. The applied code is expected to be small, readable and fast, as a consequence of a simple and straightforward idea.

The main idea i.e. the main question of this approach is: <i>"which operator will be executed last?"</i>

It leads us to the following procedure:

<p style="color:RGB(169, 169, 169);">a) We are searching for a <i>free operator</i> of the lowest precedence level (free - not embraced by any parentheses). We are always searching in the oposite direction i.e. if the operators associativity is left-to-right, we are searching from-right-to-left within the expression. If the operators associativity is right-to-left, we are searching left-to-right. 

b) When an operator is found, we are using the simple recursive formula, depending on the task we are doing:<br/>
in the case of reverse Polish notation, it would be: <i>rpn = rpn(left_subexpression) + rpn(right_subexpression) + (operator)</i><br/>
in the case of evaluation, it would be: <i>eval = apply_operator(eval(left_subexpression), eval(right_subexpression))</i><br/> 
in the case of building AST tree: <i>ast = operator_node(ast(left_subexpression), ast(right_subexpression))</i><br/> 
etc.

c) If no <i>free operator</i> has been found, we are going to make next try with the operators of the next (higher) precedence level.

d) If we passed all the precedence levels and no <i>free operator</i> has been found, it just means that the entire expression is enclosed within the redundant parentheses (e.g. (x+y-z) ). In that case, parentheses should be trimmed (or ignored) on both ends and we can go on with a) again.</p>

<i>It's not very likely that there can be anything remarkably new in the field of algorithms for parsing arithmetic expressions. However, I was googling and so far, I have found nothing similar to this!? I haven't found this method in the books about discrete math and algorithms!? The interesting is that its logic is (imo) simple and it turns out to be much faster than the most reputed relevant algorithm - Dijkstra's shunting-yard!? <img src="https://raw.githubusercontent.com/sasamil/WMS-TMS-Maker-Qt-GUI/master/icons/emoticons/eusa_think.gif" alt="crazy" height="15" width="15"> 

If anybody knows that this (or similar) algorithm has already been published, please let me know. I will be very thankful. <strong>Until then, I'll consider it new<strong>...</i>
