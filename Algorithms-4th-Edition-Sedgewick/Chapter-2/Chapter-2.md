# Chapter 2 Sorting
---
#### Selection sort

the idea is: 
1. at each iteration find the minimum (on first assume first)
2. if something lesser is found (j), make that the min
3. place it at i
4. repeat until sorted

notable points:
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

implementation:
**to fix**
```Java
public static void selectionSort(Comparable[] arr) {
    int N = arr.length;
    for (int i = 0; i < N; i++) {
        int minIndex= i;
        for (int j = i+1; j < N; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
        }
        exchange(arr, i, minIndex);
    }
}
```
