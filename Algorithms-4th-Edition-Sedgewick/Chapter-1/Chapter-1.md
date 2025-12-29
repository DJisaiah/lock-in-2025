# Chapter 1
---
### Chapter 1.3
---
###### some foreknowledge

##### Generics (parameterised types)
- basically allows us to reuse the same code for many types
- Stack example
    - ```C
        // The header says: "Let's use 'Item' as our temporary name for the type"
        // diamond operator in the class header is SPECIFIC to generics
        public class FixedStack<Item> { 
            private Item[] a;

            public FixedStack(int cap) {
            // Casting is required for generic arrays in Java
                    a = (Item[]) new Object[cap]; 
                }

            // Now we can use 'Item' to declare variables
            private Item[] a; 

            // We can use it in method signatures
            public void push(Item item) { ... } 

            // And as a return type
            public Item pop() { ... } 
        }
        ```
        - **Note**:
            - In Java, you cannot create an array of a generic type directly (e.g., new Item[cap] is illegal). You must create an array of Object and cast it
            - Java generics do not support primitives directly
                - to get around this you must use Wrapper classes
                    - do: `FixedStack<Integer>` and NOT `FixedStack<int>`
                        - the automatic promotion is called *AutoBoxing*

##### Iterable collections
- We often want our clients to be able to iterate through the collections (through something like a for-each loop)

---
