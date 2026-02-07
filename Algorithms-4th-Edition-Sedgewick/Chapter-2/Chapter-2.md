# Chapter 2 Sorting

#### some foreknowledge

![high school sum formulas](https://mathswithdavid.com/wp-content/uploads/2021/08/image-43.png)
*(source: mathswithdavid)*

- Inversions
    - this refers to pairs that are out of order (E-A, A should be before A)

- Partially sorted array
    - This is when the number of inversions is *less* than a *constant* multiple of the array size
        - what this means in practice is
            - the growth rate of the number of inversions in relation to the size of N, does not change
                - the growth rate is **linear**
    - table
        | Array Size ($N$) | Definition of "Partially Sorted" ($10N$) | Definition of "Random" ($N^2 / 4$) |
        | :--- | :--- | :--- |
        | **100** | 1,000 inversions (10 per item) | 2,500 inversions (25 per item) |
        | **1,000** | 10,000 inversions (Still 10 per item) | 250,000 inversions (250 per item!) |
        | **1,000,000** | 10,000,000 inversions (Still 10 per item) | 250,000,000,000 inversions (250,000 per item!!) |
    - visually we see:
        - an array where each entry is not far from its rightful place
        - a small array appended to a large sorted array
        - an array with only a small number of entries that arent in place

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
#### Selection sort "Look ahead and select, then swap."

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
- this is true for average, best, and worst case (in the standard implementation as we see in sedgewick)
    - if we consider an optimised version then in the best case we can enjoy 0 exchanges
        - checking if the min index we're swapping with is the one we started with

| Operation | Best Case | Average Case | Worst Case |
| :--- | :--- | :--- | :--- |
| **Comparisons** | $\sim \frac{1}{2} N^2$ | $\sim \frac{1}{2} N^2$ | $\sim \frac{1}{2} N^2$ |
| **Exchanges** | $N$ | $N$ | $N$ |


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

#### Insertion sort "Let me insert myself into this line, 1 ahead to stay humble, then judge those behind me back to the beginning to see where i stand, ctsly move up."

##### the idea is:
1. Start at index 1 (i)
2. Then look at values to the left of i to see if theyre bigger than the value at i (j)
    - essentially comparing pairs
        - if one of them is smaller swap with the bigger one in the pair
3. Go all the way to the left til the beginning of the array (j > 0)
4. Repeat this process until we reach the end of the array

##### implementation:
```Java
import java.util.Arrays;

public class InsertionSort {
    public static void main() {
        Integer[] arr = {90, 22, 300, 1, 12, 55};
        String[] arr2 = {"Banana", "Apple", "Xylophone", "Diner", "Cranberry"};
        System.out.println(Arrays.toString(sort(arr)));
        System.out.println(Arrays.toString(sort(arr2)));
    }

    // we use bounded type parameters here
    // this is to ensure that we ONLY accept classes that extend Comparable
    // we put T in Comparable<T> so that we only want T to be compared to T
    // this is bcos two classes can of course implement Comparable but that's obv not desired
    // this possible mismatch can lead to errors
    // w/o this btp, compiler gives us warnings
    public static <T extends Comparable<T>> T[] sort(T[] arr) {
        int N = arr.length;
        for (int i = 1; i < N; i++) {
            // this is cleaner than making a separate variable to compare the other vals with
            for (int j = i; j > 0 && arr[j].compareTo(arr[j-1]) < 0; j--) {
                // exchange the two if current index is not the largest upon lookin back
                T temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
        return arr;
    }
}
```

```bash
java InsertionSort
[1, 12, 22, 55, 90, 300]
[Apple, Banana, Cranberry, Diner, Xylophone]
```
##### Performance

###### Best case $N$
- When the array is sorted insertion sort's running time is linear (or when all keys are the same)
    - Imagine an array `[1, 2, 3, 4, 5]`. Let's trace the work:
        * $i = 1$: Compare `2` and `1`. Is $2 < 1$? **No.** Inner loop terminates immediately.
        * $i = 2$: Compare `3` and `2`. Is $3 < 2$? **No.** Inner loop terminates immediately.
        * $i = 3$: Compare `4` and `3`. Is $4 < 3$? **No.** Inner loop terminates immediately.
        * $i = 4$: Compare `5` and `4`. Is $5 < 4$? **No.** Inner loop terminates immediately.

###### Worst Case ~$N^2/2$
- When the array is in reverse order
    - Algorithm has to do a full $\frac{(N - 1)(N - 1)}{2}$

###### Average Case ~$N^2/4$
- Rectangle model
    - So the width would be (N - 1)
    - the length would be (N - 1)
    - but of course i need to divide that whole expression by 2 since this is not a full rectangle. 
    - Then i remembered that we would only be doing abt half the necessary work in the inner loop in the average case so divide (N-i) by 2 in the original expression 
- Accurate Expression (*called Exact Complexity*):
    - $$\frac{(N - 1) \times \frac{(N - 1)}{2}}{2} = \frac{(N - 1)(N - 1)}{4}$$
- Tilde Notation:
    - ~$N^2/4$
- Big O:
    - $N^2$
- note
    - it didnt matter whether we chose the exchanges or comparisons as they had the same growth rate
    - unique for insertion sort

- *insertion sort is efficient for partially sorted arrays and fine for small arrays*


##### Optimisation (faster memory operations -> faster cpu)
- Insertion sort can be optimised in it's assignments/exchanges
    - instead of doing 3 assignments every time we exchange for each larger neighbour we can:
        -  instead of exchanging for each lesser, put our candidate in a temp box, if we find a larger neighbour shift it up until there aren't any larger ones, then put the temp in the leftover space
        - this way we shift from moving two items every larger neighbour, we only move one (this cuts the work/array accesses in half)

```java
T temp = a[i]; // Pick up the candidate
int j = i;
while (j > 0 && less(temp, a[j-1])) {
    a[j] = a[j-1]; // Just shift the neighbor right
    j--;
}
a[j] = temp; // Drop the candidate in the hole
```
#### Shell sort

- A great optimisation of insertion sort
    - where insertion lacks in that it only does adjacent swaps, shellsort looks ahead and does n/(implementation dependent) gap sorts
    - it does this until there is only a gap of 1
        - which is insertion sort's most efficient state
    - much faster than regular insertion sort for large arrays
