public class Solution {
    public static boolean check(Object[] a, Object x) {
      for (Object obj : a) {
        if (obj == x) return true;
      }
      return false;
    }
}

// this solution only does a reference check not a content check
// so if we two strings for example with the same content we could get false
// some other choices here is to use Arrays.asList(a).contains(x) [need to import Java.util.Arrays]
    // .contains automatically calls .equals()
        // .equals checks content
            // the default behaviour is actually == but most classes override that
            // the reason null.equals(x) fails is because the dot operator tries to look at the method's code in the metaspace (or method area. SEPARATE from heap which is where objects live)
    // there is small overhead to wrap in a list but neglibile in most cases
// continuing with for loop approach we can use Objects.equals(o, x)
    // returns true if theyre equal false otherwise
    // this is better than doing obj.equals(x) cos if null we get error
