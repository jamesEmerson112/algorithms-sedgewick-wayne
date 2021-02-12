//
//  selection-sort.cpp
//  Copyright (c) 2017 Dylan Brown. All rights reserved.
//

// NOTES
// Selection sort is straightforward. Loop over all elements to find the minimum
//     [ B C D E F (A) Q R S ]
// Then swap that element with the item in the first index position. Increment
// the starting index, and repeat this process on the remaining elements.
//     [ A | C D E F (B) Q R S ]
//     [ A B | D E F C Q R S ]
// Note that we conduct ~(n^2 / 2 compares + n swaps) to create an ascending
// sort of comparable items in time O(n^2).

#include <chrono>       // time the algorithm
#include <cstdlib>      
#include <fstream>      // reading input files
#include <iostream>     // basic I/O
#include <string>       
#include <utility>      
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;


/*
* class_identifier: this class Selection is doing a Selection sort
*
* constructors: 
*
* public functions: a vertical list of public function prototypes
* void sort: sorting a vector
* bool is_sorted: confirm wheather a vector is sorted
* void show: print the vector
*
* static members: a vertical list of any static members
*                 (variables and function prototypes)
* bool is_less: compare the values of two variables
* void exch: swapping place
*/
template <typename Type> class Selection {
public:
  // requires Sortable<T> (T must implement comparison operators).
  void sort(vector<Type> &);

  bool is_sorted(const vector<Type> &);

  void show(const vector<Type> &a) {
    for (auto item : a) {
      cout << item << " ";
    }
    cout << endl;
  }

private:
  // Returns true if v < w. Again, T must implement comparison operators.
  bool is_less(Type v, Type w) { return (v < w); }
  // Pass by reference to ensure std::swap mutates the caller's data.
  void exch(vector<Type> &a, int i, int j) { std::swap(a[i], a[j]); }
};

// boolean is_sorted checks if the vector is sorted
// input: vector alpha
// output: true or false
template <typename Type>
bool is_sorted(const vector<Type> &alpha) {
    for (int i = 1; i < alpha.size(); i++) {
      if (is_less(alpha[i], alpha[i - 1])) {
        return false;
      }
    }
    return true;
}

// void Selection implements Selection Sort on vector alpha
// input: vector alpha
// output: sorted vector alpha
template <typename Type> 
void Selection<Type>::sort(vector<Type> &alpha) {
  int N = alpha.size();
  for (int i = 0; i < N; i++) {
    // show(a); // Debug
    int min = i;
    for (int j = i + 1; j < N; j++) {
      if (is_less(alpha[j], alpha[min])) {
        min = j;
      }
    }
    exch(a, i, min);
  }
}

int main(int argc, char *argv[]) {
  // Read file given on command line.
  string filename;
  if (argc != 2) {
    cout << "Usage: selection-sort ../algs4-data/words3.txt" << endl;
    return EXIT_FAILURE;
  } else {
    filename = argv[1];
  }

  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    cout << "ERROR: failed to open \"" << filename << "\" for reading." << endl;
    return EXIT_FAILURE;
  }

  // Instantiate a selection sort object.
  auto sel = Selection<string>();

  // For this example, we'll sort strings in alphabetical order.
  // Read the input data into a vector of std::string tokens.
  vector<string> tokens;
  for (string tkn; input_file >> tkn;) {
    tokens.push_back(tkn);
  }
  input_file.close();

  // Apply the weighted quick-union algorithm to the input data.
  auto begin = std::chrono::steady_clock::now();
  sel.sort(tokens);
  auto end = std::chrono::steady_clock::now();

  // Ensure that the data structure is sorted.
  if (!sel.is_sorted(tokens)) {
    cout << "ERROR: upon review, selection sort failed "
            "to completely sort the data."
         << endl;
    return EXIT_FAILURE;
  }

  // Output the performance and results.
  cout << "Selection::sort, elapsed time (ns) = "
       << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin)
              .count()
       << endl;
  sel.show(tokens);
}
