# Chapter 2 Sorting

#### some foreknowledge

![high school sum formulas](https://mathswithdavid.com/wp-content/uploads/2021/08/image-43.png)
*(source: mathswithdavid)*

##### `Comparable` interface
- **why**
    - java does not support operator overloading and so we cannot compare non-primitives with `>` and `<`
- Built-in java interface
    - comes from `java.lang`
- allows us to sort any type as long as it implements the interface
    - most types in java do
    - methods to implement:
        - `compareTo`
            - 
            ```java
                public class Student implements Comparable<Student> {
                    private int id;
                    private String name;

                    public Student(int id, String name) {
                        this.id = id;
                        this.name = name;
                    }

                    @Override
                    public int compareTo(Student other) {
                        // Simple logic: subtract IDs
                        // If this.id is smaller, result is negative (comes first)
                        // If this.id is larger, result is positive (comes last)
                        return Integer.compare(this.id, other.id);
                        // we could've returned pos/neg based on direct value comparisons 
                        // with + and - but this can lead to bugs with large numbers. 
                        // This is the standard in modern java
                    }

                    @Override
                    public String toString() {
                        return id + ": " + name;
                    }
                }
            ```
            - this method needs to be implemented as a total order
                - reflexive
                - antisymmetric
                - transitive
            - in our case we find it useful to also have methods like `less` and `exch`
    
---
#### Selection sort

##### the idea is: 
1. at each iteration find the minimum (on first assume first)
2. if something lesser is found (j), make that the min
3. place it at i
4. repeat until sorted

##### notable points:
- selection sort is not sensitive to input
    - it takes the same amount of time to sort a sorted array vs unsorted array
- date movement is minimal
    - it's pretty slow at it's job but it saves in physical exchanges compared to other algorithms which can be pretty beneficial depending on your situation
        - situations:
            - flash cell/ssd lifespan
                - you might be using a storage device that wears down on writes. 
            - super large memory objects
                - moving these is a higher cost
            - low-power systems
                - writing to non-volatile memory often costs more in energy and time on low-power systems

##### implementation:
```Java
public static void selectionSort(Comparable[] arr) {
    int N = arr.length;
    for (int i = 0; i < N; i++) {
        int minIndex= i;
        for (int j = i+1; j < N; j++) {
            if (less(arr[j], arr[minIndex])) minIndex = j;
        }
        exchange(arr, i, minIndex);
    }
}
```

##### proof

*selection sort has $N^2/2$ compares and $N$ exchanges*

N exchanges because on each loop there's just one exchange

The inner loop of Selection Sort starts at `j = i + 1` and runs to the end of the array ($N$). As the outer loop index $i$ increases, the inner loop has fewer elements to check:

* **Iteration 1 ($i=0$):** Inner loop runs $N-1$ times.
* **Iteration 2 ($i=1$):** Inner loop runs $N-2$ times.
* **Iteration 3 ($i=2$):** Inner loop runs $N-3$ times.
* ...
* **Final Iteration:** Inner loop runs $0$ times.

###### The Visual Proof (The Staircase)
Imagine you have $N = 5$. The formula says you need to add $(N-1) + (N-2) + ... + 1 + 0$, which is $4 + 3 + 2 + 1 + 0$.

If you visualize these as blocks, they form a **"staircase"** or a triangle:

```text
Iteration 1: **** (4)
Iteration 2: *** (3)
Iteration 3: ** (2)
Iteration 4: * (1)
Iteration 5:      (0)
```

To find the area of this "triangle," you can imagine taking a second identical staircase, flipping it upside down, and pressing it against the first one. This creates a **rectangle**:

* The **width** of the rectangle is $N$ (5).
* The **height** of the rectangle is $N - 1$ (4).
* The **total area** of that combined rectangle is $N \times (N - 1)$.
* Since we only want **one** of the staircases, we divide by 2: $\frac{N(N-1)}{2}$.

*naturally we can also remember our summation formulas from high school (see top) from high school*
