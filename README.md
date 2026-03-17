# Data Structures Performance Benchmarking

This project implements and evaluates the performance of multiple fundamental data structures in C++.
The goal is to analyze their behavior in terms of construction time and search efficiency using large textual datasets.

## Project Overview

The application reads data from a text file, inserts it into different data structures, and performs search operations to compare their performance.

All data structures are implemented from scratch without relying on external libraries for their core functionality.

## Data Structures Implemented

* **Unsorted Array**
  Dynamic array with manual memory management and sequential search.

* **Sorted Array**
  Maintains ordered elements and supports Binary Search for lookups.

* **Binary Search Tree (BST)**
  Standard tree structure with recursive insertion and search operations.

* **AVL Tree**
  Self-balancing binary search tree using rotations (LL, RR, LR, RL) to maintain height balance.

* **Hash Table**
  Uses open addressing with double hashing for collision resolution and dynamic resizing based on load factor.

## Performance Evaluation

The program benchmarks each data structure by:

* Measuring the time required to construct each structure from input data
* Performing multiple search queries on the stored elements
* Recording execution times using high-resolution timing tools

The experiments are designed to highlight differences in performance and scalability between data structures.

## Technologies Used

* **C++** – Core implementation
* **std::chrono** – High-resolution timing for benchmarking
* **OOP Concepts** – Encapsulation and modular design
* **Algorithms & Data Structures** – Trees, hashing, searching

## How to Run

1. Clone the repository:

```bash
git clone https://github.com/eleniarvan/data-structures-search-performance-comparison.git
```

2. Navigate to the project directory and compile:

```bash
g++ main.cpp NonSortedArray.cpp SortedArray.cpp BinarySearchTree.cpp AVLTree.cpp HashTable.cpp -o datastructures
```

3. Make sure an `input.txt` file exists in the same directory.

4. Run the program:

```bash
./datastructures
```

The program will generate an `output.txt` file containing the benchmarking results.

## Notes

This project was developed as part of a university assignment for the Data Structures course at the Aristotle University of Thessaloniki (AUTH).

It focuses on understanding:

* Trade-offs between different data structures
* Practical performance compared to theoretical complexity
* Efficient handling of large datasets

## Contributors (2)

Developed collaboratively as part of coursework.
