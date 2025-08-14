To understand theoratically:
https://www.geeksforgeeks.org/cpp/copy-swap-idiom-c/

Understanding my way:

### Scenario: a = b

1. Temporary deep copy

   * Inside `operator=()` we take `b` by value -> so the copy constructor makes a deep copy of `b` into a temporary object, say `temp`.
   * Now:

     ```
     a → old data
     b → original data
     temp(copy_of_b) -> deep copy of b
     ```

2. Swap resources

   * We swap pointers/data members between `a` and `temp`.
   * After swap:

     ```
     a -> data of b
     temp -> old data of a
     b -> untouched
     ```

3. Temporary destruction

   * `temp` goes out of scope → destructor frees old data of a.
   * Result:

     ```
     a -> b's data (copied)
     b -> untouched
     ```

---

Why it’s good:

* Copy is made first, so if copying fails, `a` is untouched.
* Swap is cheap (just exchanging pointers).
* No duplicate cleanup logic.

---
