Small Python code example to demonstarte the new approach for expression parsing. It is assumed that input-expression is valid and already tokenized (no blank spaces, no multi-character tokens). The focus is at new parsing algorithm here. So, please see the "rpn" function, in code.

Two c++ files are provided.

<i>rpn_basic.cpp</i> - It has been made to be readable. The intention was to make the basic idea clear.

<i>rpn_opt</i> - A bit optimized version. It gives the same results but it should be faster. C-like handling of strings (character arrays). An attempt to prevent searching for an operator more than once.
