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
