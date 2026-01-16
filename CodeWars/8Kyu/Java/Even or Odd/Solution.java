public class Solution {
    public static String evenOrOdd(int number) {
      return number % 2 == 0 ? "Even" : "Odd";
      // we could also do number % 1 == 0
      // Bitwise AND compares the bits of both numbers and if it finds a matching 1 on both it returns 1
      // Recall that
        // even numbers always end in 0 in binary
        // whereas odd numbers always end in 1 in binary
        // so if number was 2 we'd be bitwise AND comparing 0010 and 0001 (looking at last 4 bits)
       // this is technically faster than what we did but on modern devices the compiler is smart enough to optimise our % check
            // recall that division is one of the more expensive operations
        // so this could be useful in a case where things need to be very highly optimised
    }
}
