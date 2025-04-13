Converts infix mathematical expressions into reverse Polish notation.

---

## `soup`: Stack OUtput Precedence

So sure, a terribly silly name, but I like it. This uses a variation of
Dijkstra's yard shunting algorithm (I *think*...). Essentially it uses two
stacks, an output and an operator, and then puts a big emphasis on operator
precedence to **get stuff done**.

The evaluation of this is done by the classic stack method. That is the *entire*
point of using RPN.


## `stew`: String to Tree of Expressions Wow!

I felt obligated to continue with the naming system. So this essentially works
by creating an expression tree from the input and then doing a post-order
traversal on it in order to produce the output. I imagine this would be an
easier system to scale in order to create features such as multi digit numbers
and unary operators, but maybe not, who knows.

---

## Comparison

Based on my simple benchmarking functions, which gets each algorithm to
translate four simple (around 10 tokens each) infix expressions into RPN many
times, soup is more efficient. At 1 million repitions - for a total of 4 million
conversions - soup came in at 0.603 seconds, whereas stew took a filfthy 2.448
seconds. To clarify, this does not include evaluating the expressions. I could
also probably optimise both far more.

Algorithm | Trials | Duration (average of 3 trials in seconds to 3 d.p)
----------|--------|----------------------------------
C-soup    | 400    | 0.000
C-stew    | 400    | 0.001
C#        | 400    | 0.005
C-soup    | 4mil.  | 0.601
C-stew    | 4mil.  | 2.440
C#        | 4mil.  | 6.005
C-soup    | 20mil. | 2.842
C-stew    | 20mil. | 13.065
C#        | 20mil. | 27.164

---

**TODO**:
- add decriptors to all prototypes
- globalise evaluation
- separate utilities for stew
