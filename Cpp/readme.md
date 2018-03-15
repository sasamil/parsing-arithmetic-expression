Small C++ code example to demonstrate the new approach for expression parsing. It is assumed that input-expression is valid and already tokenized (no blank spaces, no multi-character tokens) - the focus is at parsing algorithm, here. The new algorithm itself can be seen in the "rpn" function.

Two c++ files are provided.

<i>rpn_basic.cpp</i> - It has been made to be readable. The intention was to make the basic idea clear.

<i>rpn_opt</i> - A bit optimized version. It gives the same results but it should be faster. C-like handling of strings (character arrays). An attempt to prevent searching for an operator more than once.
