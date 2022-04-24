/*  Name: Dang Truong, Andrew Pham
    Implement selection sort, insertion sort, merge sort and quick sort.
    Compute the running time of each sorting algorithm and output the result
    into a csv file for graphing. */

#include <iostream>
#include <vector.h>
#include <climits>
#include <fstream>
#include <sys/time.h>

#define MAXLENGTH 100000
#define STEP 1000

/* Utility function for swapping the value of two variables
    Parameters: the references to two numbers 
    Return values: None */
void swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

/*------------------------SELECTION SORT-------------------------------*/


/* Sort a list of numbers by going through each position and
    find the correct number to insert into that position.
    
    Starting at index 0, we find the smallest element from index 0 
    to the end of the list, then swap that element with the element 
    at index 0. We continue the same process for index 1, 2,...
    
    Parameters: a list of integers
    
    Return values: None */
void selectionSort(Vector<int> &list) {
    int n = list.size();
    for (int i = 0; i < n; i++) {
        // pos will be the position of the number that will be inserted
        // into the index i
        int pos = i;
        // Scan to find the smallest element from index (i + 1) to the end of list
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[pos]) pos = j;
        }
        swap(list[i], list[pos]);
    }
}


/*------------------------INSERTION SORT-------------------------------*/

/* Sort a list of numbers by going through each element, use the element  
    as a key and compare the key with elements before it to find the 
    correct position to insert the key
    Parameters: a list of numbers
    Return values: None */
void insertionSort(Vector<int> &list) {
    int n = list.size();
    for (int i = 1; i < n; i++) {
        int key = list[i];
        int j = i - 1;
        while (j > -1 && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}


/*--------------------------MERGE SORT-------------------------------*/

/* Merge two sorted sublists (called left sublist and right sublist) 
    into a sorted list (our main list)
    Parameters: 
    - list: a list of numbers
    - left: the left boundary of the main list (also the left boundary of the left sublist)
    - mid: the mid index of the main list (also the right boundary of the left sublist
    and the left boundary of the right sublist)
    - right: the right boundary of the main list (also the right boundary of the right sublist) 
    Return values: None */
void merge(Vector<int> &list, int left, int mid, int right) {
    // Create a sorted left-sublist
    Vector<int> leftList;
    for (int i = left; i < mid + 1; i++) {
        leftList.add(list[i]);
    }

    /* Add an infinity to handle the case when one list is out of elements,
    all elements in the other list will be smaller than the infinity, 
    so we need only one pass to merge two lists into one sorted list */
    leftList.add(INT_MAX);


    Vector<int> rightList;
    for (int i = mid + 1; i < right + 1; i++) {
        rightList.add(list[i]);
    }
    rightList.add(INT_MAX);

    int i = 0, j = 0;
    for (int k = left; k < right + 1; k++) {
        if (leftList[i] < rightList[j]) {
            list[k] = leftList[i++];
        } else {
            list[k] = rightList[j++];
        }
    }

}

/* Sort a list of numbers by recursively sorting the left half and 
    the right half of the list. After sorting two halves of the list, we
    merge them into a final sorted list
    Parameters:
    - list: a list of numbers
    - left: the left boundary of the sublist
    - right: the right boundary of the sublist 
    Return values: None */
void merge_sort(Vector<int> &list, int left, int right) {
    if (left < right) {
        // Avoid integer overflow
        int mid = left + (right - left) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid + 1, right);
        merge(list, left, mid, right);
    }
}

/* Wrapper function for merge sort
    Parameters: a list of number
    Return values: None */
void mergeSort(Vector<int> &list) {
    merge_sort(list, 0, list.size() - 1);
}


/*--------------------------QUICK SORT-------------------------------*/

/* Find the position of a pivot that splits the list into two 
    sublists, one with elements smaller than or equal to the pivot and one
    with elements larger than the pivot. 
    Parameters: 
    - list: a list of numbers we want to sort
    - left: the left boundary of the list
    - right: the right boundary of the list 
    Return values: the index of the pivot */
int partition(Vector<int> &list, int left, int right) {
    int pivot = list[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (list[j] <= pivot) {
            i++;
            swap(list[i], list[j]);
        }
    }
    swap(list[i + 1], list[right]);
    return i + 1;

}

/* Sort a list of numbers by selecting a pivot that divides the list into 
    two sublists, one with elements less than or equal to the pivot and one
    with elements larger than the pivot. Then, recursively sorting the two parts
    of the list excluding the pivot element since it is already in the correct position. 
    The function returns when the list size is one (meaning that the list is sorted itself) 
    Parameters: 
    - list: a list of numbers we want to sort
    - left: the left boundary of the list
    - right: the right boundary of the list 
    Return values: None */
void quick_sort(Vector<int> &list, int left, int right) {
    if (left < right) {
        // Find the position of a pivot
        int pivotPos = partition(list, left, right);
        quick_sort(list, left, pivotPos - 1);
        quick_sort(list, pivotPos + 1, right);
    }
}

/* Wrapper function for quick sort 
    Parameters: a list of number 
    Return value: None */
void quickSort(Vector<int> &list) {
    quick_sort(list, 0, list.size() - 1);
}


int main() {
    srand(time(0));
    timeval timeBefore, timeAfter;
    long diffSeconds, diffUSeconds;
    double time;
    Vector<int> list, oldList;

    std::ofstream outputFile("test-result.csv");

    if (outputFile.fail()) {
        std::cerr << "Error creating the output file.\n";
        return 1;
    }
    // Column names of the .csv file
    outputFile << "sorting_algorithms, input_size, running_time\n";

    std::cout << "The test is running..." << '\n';

    for (int size = STEP; size <= MAXLENGTH; size += STEP) {
        // Generate a list of random numbers
        int n = oldList.size();
        for (int i = 0; i < size - n; i++) {
            oldList.add(rand());
        }

        // Compute running time of selection sort
        list = oldList;
        gettimeofday(&timeBefore, NULL);
        selectionSort(list);
        gettimeofday(&timeAfter, NULL);

        diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec;
        diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
        time = diffSeconds + diffUSeconds / 1000000.0;
        outputFile << "Selection sort, " << list.size() << ", " << time << '\n';

        // Compute running time of insertion sort
        list = oldList;
        gettimeofday(&timeBefore, NULL);
        insertionSort(list);
        gettimeofday(&timeAfter, NULL);

        diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec;
        diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
        time = diffSeconds + diffUSeconds / 1000000.0;
        outputFile << "Insertion sort, " << list.size() << ", " << time << '\n';
        
        // Compute running time of merge sort
        list = oldList;
        gettimeofday(&timeBefore, NULL);
        mergeSort(list);
        gettimeofday(&timeAfter, NULL);

        diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec;
        diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
        time = diffSeconds + diffUSeconds / 1000000.0;
        outputFile << "Merge sort, " << list.size() << ", " << time << '\n';
        
        // Compute running time of quick sort
        list = oldList;
        gettimeofday(&timeBefore, NULL);
        quickSort(list);
        gettimeofday(&timeAfter, NULL);

        diffSeconds = timeAfter.tv_sec - timeBefore.tv_sec;
        diffUSeconds = timeAfter.tv_usec - timeBefore.tv_usec;
        time = diffSeconds + diffUSeconds / 1000000.0;
        outputFile << "Quick sort, " << list.size() << ", " << time << '\n';
    }
    cout << "The test is complete." << '\n';
    outputFile.close();
    return 0;
}
