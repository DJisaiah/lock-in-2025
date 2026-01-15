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

- Multi-way gates
    - based on the idea of multi-bit gates except we perform the operation on all of them simultaneously

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
    - 
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
    - 
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
