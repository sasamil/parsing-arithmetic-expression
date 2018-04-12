# Parsing arithmetic expressions - reverse recursive algorithm
New approach to the arithmetic expressions parsing. Applicable, scalable and fast. No stack, no state machine, no Shunting-Yard, no anything in this algorithm! It can be used in many ways depending of what we want to do with the input expression. This code-example is for transforming simple arithmetic expressions into the corresponding <i>post-order</i> rpn form.

I find this approach promissing because it is scallable. It should be very simple to add new operators and rules. All the same, we can apply this algorithm for different tasks. In a pretty much the same way, we can efficiently make AST trees, evaluate expressions, present them in  <i>post-order</i> or <i>pre-order</i> form, handle unary operators and functions, etc. The applied code is expected to be small, readable and fast (please, see<a href="https://github.com/sasamil/evaluating-arithmetic-expression">evaluating-arithmetic-expression</a>), as a consequence of a simple and straightforward idea.

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

<i>It's not very likely that there can be anything remarkably new in the field of algorithms for parsing arithmetic expressions. However, I was googling and so far, I have found nothing similar to this!? I haven't found this method in the books about discrete math and algorithms!? <img src="http://forum.srpskinacionalisti.com/images/smilies/eusa_think.gif" alt="crazy" height="15" width="15"> Bewildering is that it looks simpler and turns out to be much faster?! <img src="http://forum.srpskinacionalisti.com/images/smilies/eusa_think.gif" alt="crazy" height="15" width="15"> 

If anybody knows that this (or similar) algorithm has already been published, please let me know. I would be very thankful. Until then, I'll consider this new...</i>
