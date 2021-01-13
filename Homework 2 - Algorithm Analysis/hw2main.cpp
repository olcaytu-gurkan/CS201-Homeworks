#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

void firstAlgorithm(int*& arr1, int*& arr2, int*& arr3, int size) {
    double duration;
    clock_t startTime = clock();
    for (int i = 0; i < size; i++)
        arr3[i] = arr1[i];

    if (arr2[0] <= arr1[size - 1]) {
        for (int i = 0; i < size; i++) {
            for (int j = i; j < size * 2; j++) {
                if (arr2[i] <= arr3[j]) {
                    for (int k = (size * 2) - 1; k > j; k--) {
                        arr3[k] = arr3[k - 1];
                    }
                    arr3[j] = arr2[i];
                    break;
                }
                else if (arr3[j] == -1337 && arr3[j - 1] != -1337) { //-1337 is sentinel value.
                    arr3[j] = arr2[i];
                    break;
                }
            }
        }
    }
    else {
        int j = 0;
        for (int i = size; i < size * 2; i++) {
            arr3[i] = arr2[j];
            j++;
        }
    }
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Algo1 took " << duration << " milliseconds." << endl;
}

void secondAlgorithm (int*& arr1, int*& arr2, int*& arr3, int size) {
    double duration;
    clock_t startTime = clock();
    int firstIndice = 0;
    int secondIndice = 0;
    int thirdIndice = 0;
    while (firstIndice < size && secondIndice < size) {
        if (arr1[firstIndice] < arr2[secondIndice]) {
            arr3[thirdIndice] = arr1[firstIndice];
            firstIndice++;
        }
        else {
            arr3[thirdIndice] = arr2[secondIndice];
            secondIndice++;
        }
        thirdIndice++;
    }

    while (firstIndice < size) {
        arr3[thirdIndice] = arr1[firstIndice];
        firstIndice++;
        thirdIndice++;
    }

    while (secondIndice < size) {
        arr3[thirdIndice] = arr2[secondIndice];
        secondIndice++;
        thirdIndice++;
    }
    duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
    cout << "Algo2 took " << duration << " milliseconds." << endl;
}

int main () {
    int size = 5;
    while (size != -1) {
        int* arr1 = new int[size];
        int* arr2 = new int[size];
        int* arr3 = new int[size * 2];

        /*for (int i = 0; i < size; i++) { // Filling loop for case (i), arr1 < arr2.
            int addedValue = rand() % (size * 10);
            arr1[i] = addedValue;
            arr2[i] = addedValue + (size * 10);

        }*/

        for (int i = 0; i < size; i++) { // Filling loop for case (ii), arr2 < arr1.
            int addedValue = rand() % (size * 10);
            arr2[i] = addedValue;
            arr1[i] = addedValue + (size * 10);

        }

        /*for (int i = 0; i < size; i++) { // Filling loop for case (iii), no precise comparison.
            arr2[i] = rand() % (size * 10);
            arr1[i] = rand() % (size * 10);

        }*/

        for (int i = 0; i < size * 2; i++) {
            arr3[i] = -1337; //-1337 is my sentinel value, with the premise that our arrays are positive.
        }

        sort(arr1, arr1 + size);
        sort(arr2, arr2 + size);
        cout << "First Array:";

        for (int i = 0; i < size; i++) {
            cout << " " << arr1[i] << " ";
        }

        cout << endl;
        cout << endl;
        cout << "Second Array:";

        for (int i = 0; i < size; i++) {
            cout << " " << arr2[i] << " ";
        }

        cout << endl;
        cout << endl;

        firstAlgorithm(arr1, arr2, arr3, size);

        cout << "Third and Sorted Array:";

        for (int i = 0; i < size * 2; i++) {
           cout << " " << arr3[i] << " ";
        }

        cout << endl;

        delete[] arr1;
        delete[] arr2;
        delete[] arr3;

        cout << "Please enter the size, type -1 to exit." << endl;
        cin >> size;
    }
    return 0;
}
