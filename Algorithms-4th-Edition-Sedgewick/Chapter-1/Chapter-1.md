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

##### Iterable collections `import java.util.Iterator;`
* An iterator is an object from a class that implements the methods `hasNext()` and `next()`
    - you can see that definition in the `Iterable` interface
    - *there is also a `remove()` method that needs to be implemented but we leave it blank for safety

```Java
private class ArrayIterator implements Iterator<Item> {
    private int i = 0;

    public boolean hasNext() { return i < N; }
    public Item next() { return a[++i]; }
    public void remove() { }
}
```
*this is mostly for, for-each loop*

#### Comparable

- In Java we're able to make use of interfaces as types (not when instantiating)
    - this allows us polymorphism
    - for example you can have arrays of type Comparable
        - this allows us to sort whatever types in our algorithms for example

- Comparable interface
    - Requires a compareTo method
        - 
        ```Java
                public class Player implements Comparable<Player> {
                    private int score;
                    private String name;

                    // Constructor and getters...

                    @Override // optional; we use it as a safety measure for mispells or others
                    public int compareTo(Player other) {
                        // Natural ordering: ascending order by score
                        return Integer.compare(this.score, other.score);
                    }
                }
        ```

---
*to come back to
