# parsing-arithmetic-expression
New approach to parsing simple arithmetic expressions. Widely applicable, scalable and fast.

This example enables transforming simple arithmetic expressions into the corresponding <i>post-order</i> rpn form.
It's not very likely that there can be anything new in the field of algorithms for parsing arithmetic expressions. 
However, I was googling a bit and so far, I have found nothing similar to this approach!? No stack, no state machine, no Shunting-Yard, no anything in this new algorithm!

So, I'll consider it new, for a while...

I find this approach good because it is scallable. It should be very simple to add new operators and rules. All the same, we can apply this algorithm for different tasks. In the same way, we can efficiently make AST trees, evaluate expressions, present them in <i>pre-order</i> form, etc.
