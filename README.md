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


## `stew2`: String to Tree of Expressions Wow! 2

This version makes several optimisations. The first, and most important, was
scrapping the post-order traversal being a separate function. Instead, the whole
process now happens all within a single recursive function. As well as being
speedier, this means that there is no longer any need to actually make a tree,
so the `st_node` structure can be binned. Furthermore, I realised that splitting
the input string for each of the children was unecessary, and so instead just
passed on the indices of the start and end of a string slice to child
recursions. This has also proven to be much more efficient.

## `stew2.1` : String to Tree of Expressions Wow! 2.1

This version changes `st_LSOP()` by making it start it's search from the right.
I am uncertain if this has had much of, if any, impact on performance.

## `stew3` : String to Tree of Expressions Wow! 3

This version is not here. It is in the asm-code directory under 'stew3' locally
and the repository 'stew3' on github. This uses the same algorithm as the latest
version of C-stew but is written in assembly (AArch64). I had to learn assembly
in order to do this, so it is quite rough around the edges.

---

## Comparison

Based on my simple benchmarking functions, which gets each algorithm to
translate four simple (around 10 tokens each) infix expressions into RPN many
times, soup is more efficient. To clarify, this does not include evaluating the
expressions.

Overall, soup reigns supreme. Original stew was fairly slow, with revised stew
being a huge improvement on it (~3.4 times faster). In making the changes for
stew2, soup also seemed to speed up slightly, but by only a very small amount -
around 50 milliseconds faster on average at 20 million conversions. I am not
sure why this is...

My assembly implementation of stew is fairly poor, and runs quite slowly.

Also the C# implemention stinks and is far slower than everything else.

Algorithm | Trials | Duration (average of 3 trials in seconds to 3 d.p)
----------|--------|----------------------------------
C-soup    | 400    | 0.000
C-stew    | 400    | 0.001
C#        | 400    | 0.005
C-stew2   | 400    | 0.000
S-stew3   | 400    | 0.000
..........|........|.........
C-soup    | 4mil.  | 0.601
C-stew    | 4mil.  | 2.440
C#        | 4mil.  | 6.005
C-stew2   | 4mil.  | 0.753
S-stew3   | 4mil.  | 0.412
..........|........|.........
C-soup    | 20mil. | 2.842
C-stew    | 20mil. | 13.065
C#        | 20mil. | 27.164
C-stew2   | 20mil. | 3.767
S-stew3   | 20mil. | 2.045

---

**TODO**:
- add decriptors to all prototypes
- globalise evaluation
- separate utilities for stew
