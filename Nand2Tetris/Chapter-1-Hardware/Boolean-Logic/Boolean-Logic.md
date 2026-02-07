# Boolean Algebra
- Manipulates two-state binary values
- Boolean function {binary_values} -> {binary_values}
- {And, Or, Not} are not the only subset of logical operators* that can express any other boolean function
    - Any boolean function can be realised using Nand*
---
### Boolean functions

- Every boolean function can be represented in two different ways
    1. via Truth Table
        - We consider this a convenient case for describing specific states
        - To note:
            - Truth tables are unique
    2. Boolean Expressions
        - We consider this useful for our transition to Silicon
        - To note:
            - Boolean expressions for a truth table are not unique as you can imagine
            - Simplifying these expressions is the first step to hardware optimisation
        - We can validate a boolean expression from a truth table by straight comparison
            - Naturally you can make this laborious process quicker by analysing the expression for shortcuts
    - We can convert from both to both
        - Truth table to expression = Synthesis
        - Expression to truth table = Analysis/Verification
---
### Logic Gates

- A gate is any physical device that implements a simple boolean function
    - This can be magnetic, biological, optical, etc.
        - Though these days generally transistors in silicon (chips)
    - Gates can be combined to form *composite gates*
        - The expressions can be written infix or prefix
            - Infix: $a \cdot b \cdot c = (a \cdot b) \cdot c$
            - Prefix: $\text{And}(a, b, c) = \text{And}(\text{And}(a, b), c)$
    - Gates diagramatically:
        1. Gate interface (External view)
            - This is the external layer that the user sees (see simple input and output)
        2. Gate implementation (Internal view)
            - This is what the gate builder what look at. It shows the inner workings
- The abstraction we have on logic gates is thanks to a masters thesis by Claude Shannon
    - Allows us to develop without the worry of nature
- The interface of any gate is unique
    - | Term | Status | Why? |
        | :--- | :--- | :--- |
        | **The Gate Interface** | **Unique** | It is the fixed contract of inputs $\rightarrow$ outputs (The Truth Table). |
        | **Boolean Expressions** | **Not Unique** | There are many ways to write the rule that results in that Truth Table. |
        | **Gate Implementations** | **Not Unique** | There are many ways to physically wire the gates to satisfy the expression. |
---
### Hardware Construction

- We use HDL (hardware description language) to design our chips rather than doing it by hand
    - Doing it by hand for complex cases can be quite hard to test
        - Using hdl (with a hardware simulator) we can simulate efficiency and cost
        - and then once we/a client are/is satsified with the chip they can be sent for physical production

---
### Specification

- Multiplexor
    - Basically a selector
        - given various inputs, decide which one becomes the ouput based on a condition (the selector)
    - it is a **three-input** gate
        - 2 data bits
        - 1 selector bit

- Demultiplexor
    - Basically the opposite of a multiplexor
        - given one input, decide which output gets that input based on a condition (the selector)
    - it is a **two-input** gate
        - 1 input bit
        - 1 selector bit

- Inputs are interpreted as data bits. Selection as a selection bit*

- HDL programs index bits from right to left (rightmost is 0th bit)

- Multi-bit gates are basically just expanding the array of an input 
    - it would still be one input say `a` but the number of bits has increased (8, 16...)

##### Multi-way gates
> based on the idea of multi-bit gates except we perform the operation on all of them simultaneously

- Multi-way Or
    - Basically Or with m inputs

- Multi-way Mux (multiplexor)
    - structure
        - $m$ $n$-bit input bits
        - $k$ selection bits
            - $k = \log_2 m$
                - this makes more sense when you look at the truth table (4-way mux example)
                    - | sel[1] | sel[0] | out |
                        | :---: | :---: | :---: |
                        | 0 | 0 | a |
                        | 0 | 1 | b |
                        | 1 | 0 | c |
                        | 1 | 1 | d |

- We can realise our gates:
    1. with a boolean function in a truth table (for our simpler cases)
    2. In API style
        - Chip name
        - Input
        - Output
        - Function

---
### Project 1

* Important to realise that you are building a real object with electrical capabilities. 

- Not
    - Simply just bind both inputs to the one
    - ```HDL
        CHIP Not {
            IN in;
            OUT out;

            PARTS:
            Nand(a=in , b=in , out=out);
        }

        ```

- And
    - `Simply Not(Nand(a,b))`
    - 
        ```HDL
        CHIP And {
            IN a, b;
            OUT out;
            
            PARTS:
            Nand(a=a, b=b, out=res1);
            Not(in= res1, out=out);
        }

        ```

- Or
    - `Not(And(Not(a), Not(b)))`
        - Naturally can also use `Nand(Not(a), Not(b))`
    - 
    ```HDL
        CHIP Or {
            IN a, b;
            OUT out;

            PARTS:
            Not(in=a, out=nota );
            Not(in=b, out=notb );
            And(a=nota , b=notb , out=andnotanotb );
            Not(in=andnotanotb, out=out );
        }
    ```

- Xor
    - `And(Not( And(a , b)), Or(a , b))`
    - 
        ```HDL
            CHIP Xor {
                IN a, b;
                OUT out;

                PARTS:
                Or(a=a, b=b, out=aorb);
                And(a=a, b=b, out=aandb);
                Not(in=aandb, out=notaandb);
                And(a=notaandb, b=aorb, out=out);
            }

        ```

- Multiplexor
    - It was remarkably easier to think of a programming language solution to this than focus entirely on truth table and splits
        - although we first had to split up this into cases to actually see that solution
            1. sel = 0 -> a = 1 -> out = 1
            2. sel = 1 -> b = 1 -> out = 1
            3. sel = 0 -> a = 0 -> out = 0
            4. sel = 1 -> b = 0 -> out = 0
        - `out = (a && !sel) || (b && sel)`
    - 
        ```HDL
            CHIP Mux {
                IN a, b, sel;
                OUT out;

                PARTS:
                Not(in=sel, out=Notsel);
                And(a=a, b=Notsel, out= aAndNotsel);
                And(a=b, b=sel, out=bAndsel);
                Or(a=aAndNotsel, b=bAndsel, out=out);
                
            }
        ```

- DeMultiplexor (Dmux)
    - Same process as above
        - Analysed truth table of possible results
        - Checked where a=1 then where b=1
        - | sel | in | a | b |
            | :---: | :---: | :---: | :---: |
            | 0 | 0 | 0 | 0 |
            | 0 | 1 | 1 | 0 |
            | 1 | 0 | 0 | 0 |
            | 1 | 1 | 0 | 1 |
    - 
        ```HDL
            CHIP DMux {
                IN in, sel;
                OUT a, b;

                PARTS:
                Not(in=sel, out=NotSel);
                Xor(a=sel, b=in, out=XorSelIn);
                // we can get rid of the above Xor to simplify
                // just do And(in, NotSel)
                // allows us to satisfy in=1 and sel=0
                And(a=XorSelIn, b=NotSel, out=a);
                And(a=sel, b=in, out=b);
            }
        ```

- Not16
    - same process for 16 bits as if there were 16 gates
        - couldve also used `Not` here though
        - 
        ```HDL
            CHIP Not16 {
                IN in[16];
                OUT out[16];

                PARTS:
                Nand(a=in[0], b=in[0], out=out[0]);
                Nand(a=in[1], b=in[1], out=out[1]);
                Nand(a=in[2], b=in[2], out=out[2]);
                Nand(a=in[3], b=in[3], out=out[3]);
                Nand(a=in[4], b=in[4], out=out[4]);
                Nand(a=in[5], b=in[5], out=out[5]);
                Nand(a=in[6], b=in[6], out=out[6]);
                Nand(a=in[7], b=in[7], out=out[7]);
                Nand(a=in[8], b=in[8], out=out[8]);
                Nand(a=in[9], b=in[9], out=out[9]);
                Nand(a=in[10], b=in[10], out=out[10]);
                Nand(a=in[11], b=in[11], out=out[11]);
                Nand(a=in[12], b=in[12], out=out[12]);
                Nand(a=in[13], b=in[13], out=out[13]);
                Nand(a=in[14], b=in[14], out=out[14]);
                Nand(a=in[15], b=in[15], out=out[15]);
            }
        ```

- And16
    - implementation
    ```HDL
            CHIP And16 {
                IN a[16], b[16];
                OUT out[16];

                PARTS:
                And(a=a[0], b=b[0], out=out[0]);
                And(a=a[1], b=b[1], out=out[1]);
                And(a=a[2], b=b[2], out=out[2]);
                And(a=a[3], b=b[3], out=out[3]);
                And(a=a[4], b=b[4], out=out[4]);
                And(a=a[5], b=b[5], out=out[5]);
                And(a=a[6], b=b[6], out=out[6]);
                And(a=a[7], b=b[7], out=out[7]);
                And(a=a[8], b=b[8], out=out[8]);
                And(a=a[9], b=b[9], out=out[9]);
                And(a=a[10], b=b[10], out=out[10]);
                And(a=a[11], b=b[11], out=out[11]);
                And(a=a[12], b=b[12], out=out[12]);
                And(a=a[13], b=b[13], out=out[13]);
                And(a=a[14], b=b[14], out=out[14]);
                And(a=a[15], b=b[15], out=out[15]);
            }
    ```

- Or16
    - implementation
    ```HDL
            CHIP Or16 {
                IN a[16], b[16];
                OUT out[16];

                PARTS:
                Or(a=a[0], b=b[0], out=out[0]);
                Or(a=a[1], b=b[1], out=out[1]);
                Or(a=a[2], b=b[2], out=out[2]);
                Or(a=a[3], b=b[3], out=out[3]);
                Or(a=a[4], b=b[4], out=out[4]);
                Or(a=a[5], b=b[5], out=out[5]);
                Or(a=a[6], b=b[6], out=out[6]);
                Or(a=a[7], b=b[7], out=out[7]);
                Or(a=a[8], b=b[8], out=out[8]);
                Or(a=a[9], b=b[9], out=out[9]);
                Or(a=a[10], b=b[10], out=out[10]);
                Or(a=a[11], b=b[11], out=out[11]);
                Or(a=a[12], b=b[12], out=out[12]);
                Or(a=a[13], b=b[13], out=out[13]);
                Or(a=a[14], b=b[14], out=out[14]);
                Or(a=a[15], b=b[15], out=out[15]);
            }
    ```
- Multi-bit multiplexer
    - implementation
    ```HDL
            CHIP Mux16 {
                IN a[16], b[16], sel;
                OUT out[16];

                PARTS:
                Mux(a= a[0], b= b[0], sel=sel, out=out[0]);
                Mux(a= a[1], b= b[1], sel=sel, out=out[1]);
                Mux(a= a[2], b= b[2], sel=sel, out=out[2]);
                Mux(a= a[3], b= b[3], sel=sel, out=out[3]);
                Mux(a= a[4], b= b[4], sel=sel, out=out[4]);
                Mux(a= a[5], b= b[5], sel=sel, out=out[5]);
                Mux(a= a[6], b= b[6], sel=sel, out=out[6]);
                Mux(a= a[7], b= b[7], sel=sel, out=out[7]);
                Mux(a= a[8], b= b[8], sel=sel, out=out[8]);
                Mux(a= a[9], b= b[9], sel=sel, out=out[9]);
                Mux(a= a[10], b= b[10], sel=sel, out=out[10]);
                Mux(a= a[11], b= b[11], sel=sel, out=out[11]);
                Mux(a= a[12], b= b[12], sel=sel, out=out[12]);
                Mux(a= a[13], b= b[13], sel=sel, out=out[13]);
                Mux(a= a[14], b= b[14], sel=sel, out=out[14]);
                Mux(a= a[15], b= b[15], sel=sel, out=out[15]);
            }
    ```

- Multi-way Or
    - implementation
    ```HDL
            CHIP Or8Way {
                IN in[8];
                OUT out;

                PARTS:
                Or(a=in[0], b=in[1], out=out1);
                Or(a=out1, b=in[2], out=out2);
                Or(a=out2, b=in[3], out=out3);
                Or(a=out3, b=in[4], out=out4);
                Or(a=out4, b=in[5], out=out5);
                Or(a=out5, b=in[6], out=out6);
                Or(a=out6, b=in[7], out=out);
            }
    ```

- 4-Way Mux16
    - analysing the truth table to form cases for each helped
        - realising sel[0] formed the selector for the a&b then c&d
        - sel[1] formed the selector between the winner of those two groups
    - implementation
    ```HDL
            CHIP Mux4Way16 {
                IN a[16], b[16], c[16], d[16], sel[2];
                OUT out[16];
                
                PARTS:
                Mux16(a=a, b=b, sel=sel[0], out=outAB);
                Mux16(a=c, b=d, sel=sel[0], out=outCD);
                Mux16(a=outAB, b=outCD, sel=sel[1], out=out);
            }
    ```

- 8-Way Mux16
    - implementation
    ```HDL
            /**
             * 8-way 16-bit multiplexor:
             * out = a if sel = 000
             *       b if sel = 001
             *       c if sel = 010
             *       d if sel = 011
             *       e if sel = 100
             *       f if sel = 101
             *       g if sel = 110
             *       h if sel = 111
             */
            CHIP Mux8Way16 {
                IN a[16], b[16], c[16], d[16],
                   e[16], f[16], g[16], h[16],
                   sel[3];
                OUT out[16];

                PARTS:
                Mux4Way16(a=a, b=b, c=c, d=d, sel=sel[0..1], out=ABCD);
                Mux4Way16(a=e, b=f, c=g, d=h, sel=sel[0..1], out=EFGH);
                Mux16(a=ABCD, b=EFGH, sel=sel[2], out=out);
                
            }
    ```

- 4WayDmux
    - implementation 1
    ```HDL
             * 4-way demultiplexor:
             * [a, b, c, d] = [in, 0, 0, 0] if sel = 00
             *                [0, in, 0, 0] if sel = 01
             *                [0, 0, in, 0] if sel = 10
             *                [0, 0, 0, in] if sel = 11
             */
            CHIP DMux4Way {
                IN in, sel[2];
                OUT a, b, c, d;

                PARTS:
                Not(in=sel[0], out=NotSel0);
                Not(in=sel[1], out=NotSel1);
                And(a=sel[1], b=sel[0], out=outd);
                And(a=sel[1], b=NotSel0, out=outc);
                And(a=NotSel1, b=sel[0], out=outb);
                And(a=NotSel0, b=NotSel1, out=outa);
                And(a=in, b=outd, out=d);
                And(a=in, b=outc, out=c);
                And(a=in, b=outb, out=b);
                And(a=in, b=outa, out=a);
            }
    ```
    - implementation 2
    ```HDL
        CHIP DMux4Way {
            IN in, sel[2];
            OUT a, b, c, d;

            PARTS:
            DMux(in=in, sel=sel[1], a=caseAB, b=caseCD);
            DMux(in=caseAB, sel=sel[0], a=a, b=b);
            DMux(in=caseCD, sel=sel[0], a=c, b=d);
        }
    ```
    - realised this solution through analysing the results of input 1 case
        - when is d,c,b,a 1?
        - we then realise we can split those into cases where ab or cd is 1, then the other pair must be zero
        - and voila!

- DMux8Way
    - implementation
    ```HDL
            CHIP DMux8Way {
                IN in, sel[3];
                OUT a, b, c, d, e, f, g, h;

                PARTS:
                DMux(in=in, sel=sel[2], a=caseABCD, b=caseEFGH);
                DMux4Way(in=caseABCD, sel=sel[0..1], a=a, b=b, c=c, d=d);
                DMux4Way(in=caseEFGH, sel=sel[0..1], a=e, b=f, c=g, d=h);
            }
    ```
    - realise here that sel[2] is the one that decides which group ABCD gets to be 1 and then from there it's just a DMux4Way
        - again just analysed the table
            - very useful to put selector logic in growing numbers in terms of binary (2..4..6...)
