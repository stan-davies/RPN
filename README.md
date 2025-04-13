Converts infix mathematical expressions into reverse Polish notation.

soup: Stack OUtput Precedence
So sure, a terribly silly name, but I like it. This uses a variation of
Dijkstra's yard shunting algorithm (I *think*...). Essentially it uses two
stacks, an output and an operator, and then puts a big emphasis on operator
precedence to **get stuff done**.

The evaluation of this is done by the classic stack method. That is the *entire*
point of using RPN.


stew: String to Tree of Expressions Wow!
I felt obligated to continue with the naming system. So this essentially works
by creating an expression tree from the input and then doing a post-order
traversal on it in order to produce the output. I imagine this would be an
easier system to scale in order to create features such as multi digit numbers
and unary operators, but maybe not, who knows.
