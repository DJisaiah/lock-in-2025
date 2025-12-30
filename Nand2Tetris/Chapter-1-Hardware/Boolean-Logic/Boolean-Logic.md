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
