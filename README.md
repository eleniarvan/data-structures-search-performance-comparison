# Data Structures Performance Benchmarking

This project implements and evaluates the performance of multiple data structures from scratch in **C++**. The primary goal is to analyze and benchmark the **construction time** and **search efficiency** of each structure using large textual datasets (up to 500MiB).

##  Data Structures Implemented

The following data structures were custom-built without relying on external libraries for their core mechanics:

- **Unsorted Array:** Dynamic memory allocation with custom array resizing.
- **Sorted Array:** Implements Binary Search for efficient lookups.
- **Binary Search Tree (BST):** Standard implementation with recursive insertion and search.
- **AVL Tree:** Self-balancing BST featuring algorithmic L, R, LR, and RL rotations to maintain an optimal height balance.
- **Hash Table:** Uses Open Addressing with Double Hashing for collision resolution, and dynamic rehashing (doubling the table size to the next prime number) when the load factor exceeds 0.5.

##  Performance Evaluation & Results

The structures were rigorously tested on a Debian Linux environment (compiled with `g++`). We measured the time required to build the structures and perform 1,000 random search queries. 

*Key insights from processing a **10MiB** text file:*
- The **Hash Table** vastly outperformed the others, taking only `~0.93s` to create and `~0.0005s` to complete the search operations.
- The **AVL Tree** and **BST** constructed the datasets in `~6.2s` and `~6.7s` respectively, offering highly efficient `~0.002s` search times.
- The **Unsorted Array** struggled with construction time (`~1.2 hours`) due to the massive number of sequential comparisons required during insertion to check for duplicates.

##  Technologies Used

- **Language:** C++
- **Profiling:** `std::chrono` library for high-resolution performance benchmarking.
- **Core Concepts:** Object-Oriented Programming (OOP), Memory Management, Algorithmic Complexity, Double Hashing, Tree Rotations.

##  How to Run

1. Clone the repository:
   bash
   git clone https://github.com/eleniarvan/data-structures-search-performance-comparison.git
   
2. Navigate to the project directory and compile the source files using `g++`:
   bash
   g++ main.cpp NonSortedArray.cpp SortedArray.cpp BinarySearchTree.cpp AVLTree.cpp HashTable.cpp -o datastructures
   
3. Ensure an `input.txt` file containing the text data is in the same directory.
4. Run the executable:
   bash
   ./datastructures
   
   *(The program will automatically generate `output.txt` with the benchmarking results.)*
