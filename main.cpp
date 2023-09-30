#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include "InsertionSort.h"
#include "MergeSort.h"
#include "BubbleSort.h"
#include "HeapSort.h"
#include "SelectionSort.h"
#include "ShellSort.h"
#include "QuickSort.h"

using namespace std;

template <typename T>
void printVector(const std::vector<T>& vec, const std::string& c) {
    std::cout << c;
    for (const T& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

std::vector<double> GetPoints(const int& d){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::vector<double> points (d);
    for (auto& c:points){
        c = dis(gen);
    }
    return points;
}

void getTimeSort(const std::vector<double>& points, const std::vector<std::string>& algorithms, int n) {
    for (int i = 0; i < 7; i++) {
        std::vector<double> data = points;
        auto start = std::chrono::high_resolution_clock::now();
        switch (i) {
            case 0: bubbleSort(data); break;
            case 1: heapsort(data); break;
            case 2: InsertionSort(data); break;
            case 3: selectionSort(data); break;
            case 4: shellSort(data); break;
            case 5: mergeSort(data, 0, data.size() - 1); break;
            case 6: quickSort(data); break;
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;
        std::ofstream outputFile("Lineal/" + algorithms[i], n == 0 ? std::ios::trunc : std::ios::app);
        if (!outputFile.is_open()) {
            std::cerr << "Error opening the file for writing." << std::endl;
            return;
        }
        if (n > 0) {
            outputFile << duration.count() << " ";
        }
        outputFile.close();
    }
}

void generateAndSortData(const std::vector<std::string>& algorithms, int n) {
    if (n > 0) {
        std::vector<double> points = GetPoints(n);
        getTimeSort(points, algorithms, n);
    } else {
        for (int i = 0; i < 7; i++) {
            std::ofstream outputFile("Lineal/" + algorithms[i], std::ios::trunc);
            if (!outputFile.is_open()) {
                std::cerr << "Error opening the file for writing." << std::endl;
                return;
            }
            outputFile << "0 ";
            outputFile.close();
        }
    }
}

int main(){
    std::vector<double> VALUES = {0, 5, 10, 50, 100, 250, 500, 1000, 1500, 2500, 5000, 7500, 10000};
    std::vector<std::string> algorithms = {"Bubble", "Heap", "Insertion", "Selection", "Shell", "Merge", "Quick"};
    for (auto n : VALUES) {
        generateAndSortData(algorithms, n);
    }
    //int result = std::system(".\\Lineal\\Lineal.exe");
    /*if (result != 0) {
        std::cerr << "Error executing the plotting in GO." << std::endl;
    }
    std::remove(".\\Lineal\\Insertion");
    std::remove(".\\Lineal\\Merge");
    int results = std::system(".\\Lineal.png");
    if (results != 0) {
        std::cerr << "Error opening the image." << std::endl;
    }*/
    return 0;
}

//Credits ShinjiMC