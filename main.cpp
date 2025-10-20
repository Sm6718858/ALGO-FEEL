#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <chrono>
#include <thread>
#include <windows.h>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <string>
#include <map>
#include <limits>

using namespace std;
using namespace std::chrono;

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define BOLD "\033[1m"

class AlgorithmVisualizer
{
private:
    vector<int> originalArray;
    vector<vector<int>> adjacencyList;
    map<string, pair<long long, int>> performanceMetrics;

    void pauseExecution(int milliseconds)
    {
        Sleep(milliseconds);
    }

    void clearConsole()
    {
        system("cls");
    }

    void showHeader()
    {
        clearConsole();
        cout << BOLD << CYAN;
        cout << "================================================================\n";
        cout << "          ALGORITHM VISUALIZER & PERFORMANCE ANALYZER          \n";
        cout << "                  Data Structures Demonstration                \n";
        cout << "================================================================\n";
        cout << RESET;
    }

    void displayArray(vector<int> &arr, int pos1 = -1, int pos2 = -1,
                      int compareCount = 0, int swapCount = 0, string algoName = "")
    {
        cout << BOLD << BLUE << "\n=== " << algoName << " Progress ===\n"
             << RESET;
        cout << "Current Array: ";

        for (size_t i = 0; i < arr.size(); i++)
        {
            if ((int)i == pos1)
                cout << RED << BOLD << "[" << arr[i] << "]" << RESET << " ";
            else if ((int)i == pos2)
                cout << GREEN << BOLD << "{" << arr[i] << "}" << RESET << " ";
            else
                cout << CYAN << arr[i] << " " << RESET;
        }

        cout << "\n"
             << YELLOW << "Comparisons: " << compareCount
             << " | Swaps: " << swapCount << RESET << "\n";
        cout << string(60, '=') << "\n";
    }

    vector<int> createRandomArray(int size, int minValue = 1, int maxValue = 100)
    {
        vector<int> arr(size);
        for (int i = 0; i < size; i++)
        {
            arr[i] = rand() % (maxValue - minValue + 1) + minValue;
        }
        return arr;
    }

    void bubbleSort(vector<int> arr)
    {
        showHeader();
        cout << BOLD << YELLOW << "\n>>> BUBBLE SORT - Adjacent Element Comparison\n"
             << RESET;

        int n = arr.size();
        int comparisons = 0, swaps = 0;
        string complexityAchieved = "O(n^2)"; 

        auto startTime = high_resolution_clock::now();

for (int pass = 0; pass < n - 1; pass++) {
    bool swappedInPass = false;
    
    for (int j = 0; j < n - pass - 1; j++) {
        comparisons++;
        displayArray(arr, j, j + 1, comparisons, swaps, "Bubble Sort");
        
        if (arr[j] > arr[j + 1]) {
            swap(arr[j], arr[j + 1]);
            swaps++;
            swappedInPass = true;
        }
        pauseExecution(200);
    }
    
    if (!swappedInPass) {
        if (pass == 0) {
            complexityAchieved = "O(n)"; 
        } else {
            complexityAchieved = "O(n^2)";
        }
        cout << GREEN << BOLD << ">>> Array sorted !\n" << RESET;
        break;
    }

    cout << MAGENTA << "Pass " << pass + 1 << " complete | Total Swaps: " 
         << swaps << RESET << "\n";
    pauseExecution(300);
}


        auto endTime = high_resolution_clock::now();
        auto timeTaken = duration_cast<milliseconds>(endTime - startTime);

        displaySortResults("Bubble Sort", timeTaken.count(), comparisons, swaps, complexityAchieved);
        performanceMetrics["Bubble Sort"] = make_pair(timeTaken.count(), comparisons);
    }

    void merge(vector<int> &arr, int left, int mid, int right, int &compCount, int &swapCount)
    {
        vector<int> leftPart(arr.begin() + left, arr.begin() + mid + 1);
        vector<int> rightPart(arr.begin() + mid + 1, arr.begin() + right + 1);

        int i = 0, j = 0, k = left;

        while (i < (int)leftPart.size() && j < (int)rightPart.size())
        {
            compCount++;
            displayArray(arr, k, -1, compCount, swapCount, "Merge Sort");

            if (leftPart[i] <= rightPart[j])
            {
                arr[k++] = leftPart[i++];
            }
            else
            {
                arr[k++] = rightPart[j++];
                swapCount++;
            }
            pauseExecution(250);
        }

        while (i < (int)leftPart.size())
            arr[k++] = leftPart[i++];
        while (j < (int)rightPart.size())
            arr[k++] = rightPart[j++];
    }

    void performMergeSort(vector<int> &arr, int left, int right, int &compCount, int &swapCount)
    {
        if (left >= right)
            return;

        int mid = left + (right - left) / 2;
        performMergeSort(arr, left, mid, compCount, swapCount);
        performMergeSort(arr, mid + 1, right, compCount, swapCount);
        merge(arr, left, mid, right, compCount, swapCount);
    }

    int partition(vector<int> &arr, int low, int high, int &compCount, int &swapCount)
    {
        int pivotValue = arr[high];
        int i = low - 1;

        cout << YELLOW << "Pivot Element: " << pivotValue
             << " | Range: [" << low << "-" << high << "]\n"
             << RESET;

        for (int j = low; j < high; j++)
        {
            compCount++;
            displayArray(arr, j, high, compCount, swapCount, "Quick Sort");

            if (arr[j] < pivotValue)
            {
                i++;
                swap(arr[i], arr[j]);
                swapCount++;
            }
            pauseExecution(200);
        }

        swap(arr[i + 1], arr[high]);
        swapCount++;
        return i + 1;
    }

    void performQuickSort(vector<int> &arr, int low, int high, int &compCount, int &swapCount)
    {
        if (low < high)
        {
            int pivotIndex = partition(arr, low, high, compCount, swapCount);
            performQuickSort(arr, low, pivotIndex - 1, compCount, swapCount);
            performQuickSort(arr, pivotIndex + 1, high, compCount, swapCount);
        }
    }

    void heapify(vector<int> &arr, int n, int rootIdx, int &compCount, int &swapCount)
    {
        int largest = rootIdx;
        int leftChild = 2 * rootIdx + 1;
        int rightChild = 2 * rootIdx + 2;

        if (leftChild < n)
        {
            compCount++;
            if (arr[leftChild] > arr[largest])
                largest = leftChild;
        }

        if (rightChild < n)
        {
            compCount++;
            if (arr[rightChild] > arr[largest])
                largest = rightChild;
        }

        if (largest != rootIdx)
        {
            swap(arr[rootIdx], arr[largest]);
            swapCount++;
            heapify(arr, n, largest, compCount, swapCount);
        }
    }

    void heapSort(vector<int> arr)
    {
        showHeader();
        cout << BOLD << YELLOW << "\n>>> HEAP SORT - Binary Heap Visualization\n"
             << RESET;

        int n = arr.size();
        int comparisons = 0, swaps = 0;

        auto startTime = high_resolution_clock::now();

        for (int i = n / 2 - 1; i >= 0; i--)
        {
            heapify(arr, n, i, comparisons, swaps);
        }

        for (int i = n - 1; i > 0; i--)
        {
            swap(arr[0], arr[i]);
            swaps++;
            displayArray(arr, 0, i, comparisons, swaps, "Heap Sort");
            pauseExecution(300);
            heapify(arr, i, 0, comparisons, swaps);
        }

        auto endTime = high_resolution_clock::now();
        auto timeTaken = duration_cast<milliseconds>(endTime - startTime);

        displaySortResults("Heap Sort", timeTaken.count(), comparisons, swaps, "O(n log n)");
        performanceMetrics["Heap Sort"] = make_pair(timeTaken.count(), comparisons);
    }

    void displaySortResults(string algorithmName, long long timeMs,
                            int comparisons, int swaps, string achievedComplexity)
    {
        cout << BOLD << GREEN;
        cout << "\n**************************************************************\n";
        cout << "                    SORTING COMPLETED                         \n";
        cout << "**************************************************************\n";
        cout << " Algorithm:      " << YELLOW << setw(40) << left << algorithmName << GREEN << "\n";
        cout << " Execution Time: " << YELLOW << setw(38) << left << (to_string(timeMs) + " ms") << GREEN << "\n";
        cout << " Comparisons:    " << YELLOW << setw(40) << left << to_string(comparisons) << GREEN << "\n";
        cout << " Swaps:          " << YELLOW << setw(40) << left << to_string(swaps) << GREEN << "\n";

        cout << "\n " << CYAN << "Time Complexity:\n"
             << RESET;
        if (algorithmName == "Bubble Sort")
        {
            cout << CYAN << "   Best Case:    " << YELLOW << "O(n)";
            if (achievedComplexity == "O(n)")
                cout << GREEN << " [ACHIEVED]";
            cout << "\n";
            cout << CYAN << "   Average Case: " << YELLOW << "O(n^2)";
            if (achievedComplexity == "O(n^2)")
                cout << GREEN << " [ACHIEVED]";
            cout << "\n";
            cout << CYAN << "   Worst Case:   " << YELLOW << "O(n^2)\n";
        }
        else if (algorithmName == "Merge Sort")
        {
            cout << CYAN << "   Best Case:    " << YELLOW << "O(n log n)" << GREEN << " [ACHIEVED]\n";
            cout << CYAN << "   Average Case: " << YELLOW << "O(n log n)\n";
            cout << CYAN << "   Worst Case:   " << YELLOW << "O(n log n)\n";
        }
        else if (algorithmName == "Quick Sort")
        {
            int n = comparisons; // Rough estimation
            cout << CYAN << "   Best Case:    " << YELLOW << "O(n log n)" << GREEN << " [LIKELY ACHIEVED]\n";
            cout << CYAN << "   Average Case: " << YELLOW << "O(n log n)\n";
            cout << CYAN << "   Worst Case:   " << YELLOW << "O(n^2)\n";
        }
        else if (algorithmName == "Heap Sort")
        {
            cout << CYAN << "   Best Case:    " << YELLOW << "O(n log n)" << GREEN << " [ACHIEVED]\n";
            cout << CYAN << "   Average Case: " << YELLOW << "O(n log n)\n";
            cout << CYAN << "   Worst Case:   " << YELLOW << "O(n log n)\n";
        }

        cout << GREEN << "**************************************************************\n"
             << RESET;
    }

    void buildPath(vector<int> &parent, int start, int destination)
    {
        vector<int> path;
        for (int node = destination; node != -1; node = parent[node])
        {
            path.push_back(node);
        }
        reverse(path.begin(), path.end());

        cout << GREEN << "Shortest Path Found: ";
        for (size_t i = 0; i < path.size(); i++)
        {
            cout << path[i];
            if (i != path.size() - 1)
                cout << " -> ";
        }
        cout << RESET << "\n";
        cout << YELLOW << "Total Edges in Path: " << path.size() - 1 << RESET << "\n";
    }

void breadthFirstSearch(vector<vector<int>> &graph, int startNode, int targetNode = -1)
{
    showHeader();
    cout << BOLD << YELLOW << "\n>>> BREADTH FIRST SEARCH - Level Order Traversal\n" << RESET;

    int graphSize = graph.size();
    vector<bool> visited(graphSize, false);
    vector<int> parent(graphSize, -1);
    vector<int> level(graphSize, 0);
    queue<int> q;
    vector<int> traversalOrder; 

    q.push(startNode);
    visited[startNode] = true;

    cout << CYAN << "Starting from node: " << startNode << RESET << "\n";
    if (targetNode != -1)
        cout << CYAN << "Searching for node: " << targetNode << RESET << "\n\n";

    while (!q.empty())
    {
        int currentNode = q.front();
        q.pop();

        traversalOrder.push_back(currentNode); // Save order
        cout << GREEN << "Visiting Node: " << currentNode;
        if (parent[currentNode] != -1)
            cout << " | Parent: " << parent[currentNode];
        cout << YELLOW << " | Depth Level: " << level[currentNode] << RESET << "\n";
        pauseExecution(200);

        if (currentNode == targetNode && targetNode != -1)
        {
            cout << MAGENTA << BOLD << "\n>>> Target node found! Building path...\n" << RESET;
            buildPath(parent, startNode, targetNode);
            break;
        }

        for (int neighbor : graph[currentNode])
        {
            if (!visited[neighbor])
            {
                visited[neighbor] = true;
                parent[neighbor] = currentNode;
                level[neighbor] = level[currentNode] + 1;
                q.push(neighbor);
                cout << BLUE << "  -> Enqueued: " << neighbor
                     << " (Parent: " << currentNode << ")\n" << RESET;
            }
        }
    }

    cout << BOLD << GREEN << "\n=== Final BFS Traversal Order ===\n" << RESET;
    for (size_t i = 0; i < traversalOrder.size(); i++)
    {
        cout << traversalOrder[i];
        if (i != traversalOrder.size() - 1)
            cout << " -> ";
    }
    cout << "\n";
}


void dfsRecursive(vector<vector<int>> &graph, int node,
                  vector<bool> &visited, vector<int> &traversalOrder)
{
    visited[node] = true;
    traversalOrder.push_back(node);

    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            dfsRecursive(graph, neighbor, visited, traversalOrder);
        }
    }
}

void depthFirstSearch(vector<vector<int>> &graph, int startNode = 0)
{
    showHeader();
    cout << BOLD << YELLOW << "\n>>> DEPTH FIRST SEARCH - Component Detection\n" << RESET;

    int graphSize = graph.size();
    vector<bool> visited(graphSize, false);
    int componentCounter = 0;
    vector<vector<int>> allComponents;

    for (int i = 0; i < graphSize; i++)
    {
        if (!visited[i])
        {
            componentCounter++;
            vector<int> componentTraversal;
            dfsRecursive(graph, i, visited, componentTraversal);
            allComponents.push_back(componentTraversal);
        }
    }

    cout << BOLD << GREEN << "\n=== DFS Traversal Summary ===\n" << RESET;
    for (size_t c = 0; c < allComponents.size(); c++)
    {
        cout << MAGENTA << "Connected Component #" << c + 1 << ": " << RESET;
        for (size_t j = 0; j < allComponents[c].size(); j++)
        {
            cout << allComponents[c][j];
            if (j != allComponents[c].size() - 1)
                cout << " -> ";
        }
        cout << "\n";
    }

    cout << YELLOW << "\nTotal Connected Components Found: " << allComponents.size() << RESET << "\n";
}


    void showPerformanceDashboard()
    {
        showHeader();
        cout << BOLD << YELLOW << "\n>>> ALGORITHM PERFORMANCE COMPARISON\n"
             << RESET;

        if (performanceMetrics.empty())
        {
            cout << RED << "No performance data available yet.\n"
                 << "Please run sorting algorithms first.\n"
                 << RESET;
            return;
        }

        cout << BOLD << BLUE;
        cout << "+---------------------------+--------------+----------------+\n";
        cout << "| " << CYAN << "Algorithm Name" << BLUE << "          | "
             << CYAN << "Time (ms)" << BLUE << "   | " << CYAN << "Comparisons" << BLUE << "    |\n";
        cout << "+---------------------------+--------------+----------------+\n"
             << RESET;

        for (auto &entry : performanceMetrics)
        {
            string algoName = entry.first;
            long long execTime = entry.second.first;
            int compCount = entry.second.second;

            cout << "| " << setw(25) << left << algoName << " | "
                 << setw(12) << execTime << " | "
                 << setw(14) << compCount << " |\n";
        }

        cout << BOLD << BLUE << "+---------------------------+--------------+----------------+\n"
             << RESET;

        auto fastestAlgo = performanceMetrics.begin();
        for (auto it = performanceMetrics.begin(); it != performanceMetrics.end(); ++it)
        {
            if (it->second.first < fastestAlgo->second.first)
            {
                fastestAlgo = it;
            }
        }

        cout << GREEN << BOLD << "\n>>> Optimal Algorithm: " << fastestAlgo->first
             << " (Execution Time: " << fastestAlgo->second.first << " ms)\n"
             << RESET;
    }

public:
    void startApplication()
    {
        srand(time(0));

        while (true)
        {
            showHeader();
            cout << BOLD << CYAN << "\n>>> ALGORITHM VISUALIZER - Main Menu\n"
                 << RESET;
            cout << YELLOW;
            cout << "1. " << BOLD << "Bubble Sort" << RESET << YELLOW
                 << " - Comparison & Swap Analysis\n";
            cout << "2. " << BOLD << "Merge Sort" << RESET << YELLOW
                 << " - Divide and Conquer Approach\n";
            cout << "3. " << BOLD << "Quick Sort" << RESET << YELLOW
                 << " - Partition Based Sorting\n";
            cout << "4. " << BOLD << "Heap Sort" << RESET << YELLOW
                 << " - Binary Heap Structure\n";
            cout << "5. " << BOLD << "BFS Traversal" << RESET << YELLOW
                 << " - Shortest Path Finding\n";
            cout << "6. " << BOLD << "DFS Traversal" << RESET << YELLOW
                 << " - Connected Components\n";
            cout << "7. " << BOLD << "Performance Report" << RESET << YELLOW
                 << " - Algorithm Comparison\n";
            cout << "8. " << BOLD << "Exit Program\n"
                 << RESET;
            cout << BOLD << "\nSelect an option: " << RESET;

            int userChoice;
            cin >> userChoice;

            if (userChoice == 8)
            {
                cout << BOLD << GREEN << "\nExiting program. Thank you!\n"
                     << RESET;
                break;
            }

            switch (userChoice)
            {
            case 1:
            case 2:
            case 3:
            case 4:
            {
                int arraySize;
                cout << "Enter array size (enter 0 for random 8-element array): ";
                cin >> arraySize;

                vector<int> inputArray;
                if (arraySize == 0)
                {
                    inputArray = createRandomArray(8);
                    cout << "Generated array: ";
                    for (int val : inputArray)
                        cout << val << " ";
                    cout << "\n";
                    pauseExecution(1000);
                }
                else
                {
                    inputArray.resize(arraySize);
                    cout << "Enter " << arraySize << " elements: ";
                    for (int i = 0; i < arraySize; i++)
                    {
                        cin >> inputArray[i];
                    }
                }

                originalArray = inputArray;

                if (userChoice == 1)
                {
                    bubbleSort(inputArray);
                }
                else if (userChoice == 2)
                {
                    int comps = 0, swps = 0;
                    auto start = high_resolution_clock::now();
                    performMergeSort(inputArray, 0, inputArray.size() - 1, comps, swps);
                    auto end = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(end - start);
                    displaySortResults("Merge Sort", duration.count(), comps, swps, "O(n log n)");
                    performanceMetrics["Merge Sort"] = make_pair(duration.count(), comps);
                }
                else if (userChoice == 3)
                {
                    int comps = 0, swps = 0;
                    auto start = high_resolution_clock::now();
                    performQuickSort(inputArray, 0, inputArray.size() - 1, comps, swps);
                    auto end = high_resolution_clock::now();
                    auto duration = duration_cast<milliseconds>(end - start);
                    displaySortResults("Quick Sort", duration.count(), comps, swps, "O(n log n)");
                    performanceMetrics["Quick Sort"] = make_pair(duration.count(), comps);
                }
                else
                {
                    heapSort(inputArray);
                }
                break;
            }
            case 5:
            case 6:
            {
                int vertices, edges;
                cout << "Enter number of vertices: ";
                cin >> vertices;

                adjacencyList.clear();
                adjacencyList.resize(vertices);

                cout << "Enter number of edges: ";
                cin >> edges;

                cout << "Enter " << edges << " edges (format: u v):\n";
                for (int i = 0; i < edges; i++)
                {
                    int u, v;
                    cin >> u >> v;
                    adjacencyList[u].push_back(v);
                    adjacencyList[v].push_back(u);
                }

                if (userChoice == 5)
                {
                    int startNode, targetNode;
                    cout << "Enter starting node: ";
                    cin >> startNode;
                    cout << "Enter target node (-1 for full traversal): ";
                    cin >> targetNode;
                    breadthFirstSearch(adjacencyList, startNode, targetNode);
                }
                else
                {
                    depthFirstSearch(adjacencyList, 0);
                }
                break;
            }
            case 7:
            {
                showPerformanceDashboard();
                break;
            }
            default:
                cout << RED << "Invalid option! Please try again.\n"
                     << RESET;
                pauseExecution(1000);
                continue;
            }

            cout << BOLD << "\n>> Press Enter to return to main menu..." << RESET;
            cin.ignore();
            cin.get();
        }
    }
};

int main()
{
    AlgorithmVisualizer visualizer;
    visualizer.startApplication();
    return 0;
}