# Data Structures - Beginner Level

This section covers fundamental data structure concepts and basic algorithms for beginners.

## 📚 Topics Covered

### ✅ Implemented

1. **[Array Operations](array_operations.c)** - Fundamental array manipulation
   - Insert and delete elements
   - Linear search
   - Find min/max values
   - Reverse array
   - Rotate left/right
   - Merge arrays

2. **[Sorting Algorithms](sorting.c)** - Basic sorting techniques
   - Bubble Sort
   - Selection Sort
   - Insertion Sort

3. **[Searching Algorithms](searching.c)** - Find elements efficiently
   - Linear Search (unsorted data)
   - Binary Search (sorted data, iterative)
   - Binary Search (sorted data, recursive)

## 🎯 Learning Objectives

By completing this section, you will:

- ✓ Understand array data structure and operations
- ✓ Implement basic sorting algorithms
- ✓ Compare algorithm time and space complexity
- ✓ Learn searching strategies for different scenarios
- ✓ Recognize when to use each algorithm

## 📊 Complexity Cheat Sheet

### Array Operations

| Operation | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| Access    | O(1)           | O(1)             |
| Insert    | O(n)           | O(1)             |
| Delete    | O(n)           | O(1)             |
| Search    | O(n)           | O(1)             |
| Reverse   | O(n)           | O(1)             |
| Rotate    | O(n)           | O(k)             |

### Sorting Algorithms

| Algorithm      | Best    | Average | Worst   | Space | Stable |
|----------------|---------|---------|---------|-------|--------|
| Bubble Sort    | O(n)    | O(n²)   | O(n²)   | O(1)  | Yes    |
| Selection Sort | O(n²)   | O(n²)   | O(n²)   | O(1)  | No     |
| Insertion Sort | O(n)    | O(n²)   | O(n²)   | O(1)  | Yes    |

### Searching Algorithms

| Algorithm     | Best | Average  | Worst    | Space | Requirement |
|---------------|------|----------|----------|-------|-------------|
| Linear Search | O(1) | O(n)     | O(n)     | O(1)  | None        |
| Binary Search | O(1) | O(log n) | O(log n) | O(1)  | Sorted data |

## 🔨 Building and Running

### Build All Examples

```bash
# From project root
mkdir -p build
cd build
cmake ..
cmake --build .
```

### Run Individual Examples

```bash
# Array operations
./bin/data-structures/beginner/array_operations

# Sorting algorithms
./bin/data-structures/beginner/sorting

# Searching algorithms
./bin/data-structures/beginner/searching
```

### Build Single Example

```bash
# From build directory
cmake --build . --target array_operations
cmake --build . --target sorting
cmake --build . --target searching
```

## 📖 Learning Path

### 1. Start with Array Operations
Understanding arrays is fundamental. Work through:
- How elements are stored in memory
- Index-based access (O(1) time)
- Why insertion/deletion is O(n)
- In-place operations vs. creating new arrays

### 2. Practice Sorting
Sorting is one of the most studied problems:
- Visualize how each algorithm works
- Understand trade-offs (time vs. space, stable vs. unstable)
- Recognize when simpler algorithms are better (small datasets)
- Learn optimization techniques (early exit, skip passes)

### 3. Master Searching
Learn when to use each approach:
- Linear search: unsorted data, small arrays, linked lists
- Binary search: sorted data, large arrays, repeated searches
- Understand why sorted data enables O(log n) search

## 💡 Practice Exercises

### Array Operations
1. Implement array rotation using reversal algorithm (O(1) space)
2. Find the kth largest/smallest element
3. Merge two sorted arrays into one sorted array
4. Remove duplicate elements from sorted array
5. Find missing number in array of 1 to n

### Sorting
1. Modify bubble sort to work in descending order
2. Count number of comparisons and swaps in each algorithm
3. Implement a hybrid sort (insertion sort for small arrays)
4. Sort array of strings using these algorithms
5. Find the kth smallest element without fully sorting

### Searching
1. Find first and last occurrence of element in sorted array
2. Count occurrences of element in sorted array
3. Search in rotated sorted array
4. Find peak element in array
5. Search in 2D sorted matrix

## 🎓 Interview Questions

Common beginner-level interview questions:

1. **Two Sum Problem**: Find two numbers that add up to target
2. **Missing Number**: Find missing number in array of 1 to n
3. **Rotate Array**: Rotate array by k positions
4. **Remove Duplicates**: Remove duplicates from sorted array in-place
5. **Merge Sorted Arrays**: Merge two sorted arrays efficiently

## 🔍 Debugging Tips

1. **Array Index Errors**
   - Always check: `0 <= index < size`
   - Off-by-one errors are common in loops
   
2. **Sorting Issues**
   - Print array after each pass to visualize
   - Check boundary conditions (empty, single element)
   - Verify swap logic is correct

3. **Binary Search Problems**
   - Ensure array is sorted first
   - Check middle calculation: `mid = left + (right - left) / 2`
   - Watch out for infinite loops (left/right not updating)

## 📚 Additional Resources

### Visualization Tools
- [VisuAlgo](https://visualgo.net/) - Interactive algorithm visualizations
- [Sorting Algorithms Animations](https://www.toptal.com/developers/sorting-algorithms)

### Reading
- *Introduction to Algorithms* (CLRS) - Chapters 2, 6
- *The Algorithm Design Manual* - Chapter 2

### Practice Platforms
- [LeetCode](https://leetcode.com/) - Easy level array problems
- [HackerRank](https://www.hackerrank.com/) - Data Structures track
- [Codeforces](https://codeforces.com/) - Division 2 problems

## 📝 Next Steps

After mastering this section:

1. **[Intermediate Data Structures](../intermediate/README.md)**
   - Linked lists
   - Stacks and queues
   - Trees and graphs

2. **[Beginner Exercises](../../exercises/beginner/README.md)**
   - Hands-on practice problems
   - Solutions with explanations

3. **[Beginner Projects](../../projects/beginner/README.md)**
   - Apply concepts in real programs
   - Build portfolio pieces

## ❓ Common Questions

**Q: Why learn these "slow" O(n²) algorithms?**  
A: They're educational, simple to implement, and actually efficient for small datasets (<50 elements). They're also used in production as part of hybrid algorithms.

**Q: When would I use insertion sort over quicksort?**  
A: For small arrays (<10-20 elements), nearly sorted data, or when you need a stable sort with O(1) space. Many optimized sorting libraries use insertion sort for small partitions.

**Q: Do I need to memorize these implementations?**  
A: Focus on understanding the logic and complexity. You can look up implementation details, but should be able to explain the algorithm's approach and analyze its performance.

**Q: How do I know if my array is sorted before binary search?**  
A: You either maintain the sorted invariant (always insert in order) or explicitly sort before searching. If you're unsure, use linear search or verify with an O(n) check.

---

**Need Help?** See [CONTRIBUTING.md](../../CONTRIBUTING.md) or open an issue!

**Progress**: Beginner Level ✓ → [Intermediate Level](../intermediate/README.md) → [Advanced Level](../advanced/README.md)
