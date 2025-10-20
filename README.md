# 🧠 Algorithm Visualizer (C++ CLI)

A comprehensive C++ command-line application that visualizes and analyzes the working of various algorithms with colorful terminal output, step-by-step animations, and performance metrics.

## 📋 Description

This project demonstrates:
- **Sorting Algorithms**: Bubble Sort, Merge Sort, Quick Sort, Heap Sort
- **Graph Traversal Algorithms**: Breadth-First Search (BFS), Depth-First Search (DFS)

All visualizations happen directly in the terminal using ANSI color codes, with configurable delays between steps for better understanding.

## 🚀 Features

- **Colorful Terminal Visualization**: Uses ANSI escape codes for highlighting current operations
- **Step-by-Step Animation**: Configurable pause between steps to observe algorithm progress
- **Performance Analysis**: Tracks execution time, comparisons, and swaps for sorting algorithms
- **Interactive Menu**: Easy-to-use CLI interface for selecting algorithms
- **Random Data Generation**: Option to generate random arrays for testing
- **Graph Visualization**: Supports undirected graphs with adjacency list representation
- **Performance Dashboard**: Compare algorithms based on execution metrics
- **Cross-Platform**: Works on Windows (uses Windows.h for sleep)

## 🏗️ Prerequisites

- C++ compiler (g++ recommended)
- Windows OS (for Sleep function, can be adapted for other platforms)

## 🏃 How to Run

1. **Compile the program:**
   ```bash
   g++ main.cpp -o visualizer
   ```

2. **Execute:**
   ```bash
   ./visualizer
   ```

3. **Follow the interactive menu** to choose algorithms and input data.

## 📚 Usage Examples

### Sorting Algorithms
Choose options 1-4 from the main menu.

**Manual Input:**
```
Select an option: 1
Enter array size (enter 0 for random 8-element array): 5
Enter 5 elements: 5 3 8 1 2
```

**Random Array:**
```
Select an option: 1
Enter array size (enter 0 for random 8-element array): 0
Generated array: 42 17 89 23 56 91 34 78
```

### Graph Traversal Algorithms
Choose options 5-6 from the main menu.

**BFS Example:**
```
Select an option: 5
Enter number of vertices: 5
Enter number of edges: 4
Enter 4 edges (format: u v):
0 1
1 2
2 3
3 4
Enter starting node: 0
Enter target node (-1 for full traversal): 4
```

**DFS Example:**
```
Select an option: 6
Enter number of vertices: 4
Enter number of edges: 3
Enter 3 edges (format: u v):
0 1
1 2
2 3
```

### Performance Comparison
Choose option 7 to view the performance dashboard after running sorting algorithms.

## 🧩 Algorithm Details

### Sorting Algorithms
- **Bubble Sort**: Adjacent element comparison with early termination optimization
- **Merge Sort**: Divide and conquer with recursive merging
- **Quick Sort**: Partition-based sorting with pivot selection
- **Heap Sort**: Binary heap-based sorting

Each sorting algorithm displays:
- Current array state with highlighted elements
- Comparison and swap counts
- Execution time
- Achieved time complexity

### Graph Algorithms
- **BFS**: Level-order traversal with shortest path finding
- **DFS**: Recursive traversal for connected component detection

## 📊 Performance Metrics

The application tracks:
- Execution time (milliseconds)
- Number of comparisons
- Number of swaps (for sorting)
- Time complexity analysis

## 🛠️ Code Structure

- `AlgorithmVisualizer` class: Main application logic
- Modular functions for each algorithm
- Color-coded output using ANSI escape sequences
- Performance tracking with `std::chrono`

## 🔮 Future Enhancements

- Add more algorithms (Dijkstra, A*, Binary Search, etc.)
- GUI version using SFML/Qt
- Bar chart animations for sorting
- Export performance data to CSV
- Support for directed graphs
- Customizable animation speeds

## 🤝 Contributing

Feel free to fork and contribute! Areas for improvement:
- Add more algorithms
- Improve visualization (ASCII art, better colors)
- Cross-platform compatibility
- Unit tests

## 📄 License

This project is open-source. Use it for educational purposes.

---

**Note**: The visualization relies on terminal support for ANSI colors. Ensure your terminal supports ANSI escape sequences for the best experience.
