#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <sstream>
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

std::vector<double> ChooseD() {
    int opcion;
    int valorSeleccionado = 0;
    std::cout << "Comparing Sorting Methods\n";
    std::cout << "Available data values: 5, 10, 50, 100, 250, 500, 1000, 1500, 2500, 5000, 7500, 10000" << std::endl;
    while (true) {
        std::cout << "Select the number of data points to use:" << std::endl;
        std::cout << "1. 2 data points" << std::endl;
        std::cout << "2. 3 data points" << std::endl;
        std::cout << "3. 4 data points" << std::endl;
        std::cout << "4. 5 data points" << std::endl;
        std::cout << "5. 6 data points" << std::endl;
        std::cout << "6. 7 data points" << std::endl;
        std::cout << "7. 8 data points" << std::endl;
        std::cout << "8. 9 data points" << std::endl;
        std::cout << "9. 10 data points" << std::endl;
        std::cout << "10. 11 data points" << std::endl;
        std::cout << "11. 12 data points" << std::endl;
        std::cout << "12. Exit" << std::endl;
        std::string input;
        std::cout << "Input: ";
        std::cin >> input;
        if (input == "12") {
            std::cout << "Exiting the program." << std::endl;
            break;
        }
        try {
            opcion = std::stoi(input);
            switch (opcion) {
                case 1: valorSeleccionado = 2; break;
                case 2: valorSeleccionado = 3; break;
                case 3: valorSeleccionado = 4; break;
                case 4: valorSeleccionado = 5; break;
                case 5: valorSeleccionado = 6; break;
                case 6: valorSeleccionado = 7; break;
                case 7: valorSeleccionado = 8; break;
                case 8: valorSeleccionado = 9; break;
                case 9: valorSeleccionado = 10; break;
                case 10: valorSeleccionado = 11; break;
                case 11: valorSeleccionado = 12; break;
                default:
                    std::cout << "Invalid option. Enter a number from 1 to 12 or 12 to exit." << std::endl;
                    continue;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Enter a number from 1 to 12 or 12 to exit." << std::endl;
            continue;
        }
        
        std::vector<double> VALUES = {0, 5, 10, 50, 100, 250, 500, 1000, 1500, 2500, 5000, 7500, 10000};
        std::vector<double> selectedData(valorSeleccionado + 1);
        for (int i = 0; i <= valorSeleccionado; ++i) {
            selectedData[i] = VALUES[i];
        }
        return selectedData;
    }
    return std::vector<double>();
}

int ChooseGraphingLanguage() {
    int opcion;
    std::cout << "Choose a Graphing Language\n";
    std::cout << "1. Go" << std::endl;
    std::cout << "2. Python" << std::endl;
    std::cout << "3. Exit" << std::endl;
    
    while (true) {
        std::string input;
        std::cout << "Input: ";
        std::cin >> input;
        if (input == "3") {
            std::cout << "Exiting the program." << std::endl;
            return -1;  // Indicates an exit
        }
        try {
            opcion = std::stoi(input);
            switch (opcion) {
                case 1:
                    return 0;  // Return 0 for Go
                case 2:
                    return 1;  // Return 1 for Python
                default:
                    std::cout << "Invalid option. Enter 1 for Go, 2 for Python, or 3 to exit." << std::endl;
                    continue;
            }
        } catch (const std::invalid_argument& e) {
            std::cout << "Invalid input. Enter 1 for Go, 2 for Python, or 3 to exit." << std::endl;
        }
    }
}

int main(){
    std::vector<double> VALUES = ChooseD();
    int res = ChooseGraphingLanguage();
    if(VALUES.size()!=0 && res !=-1){
        std::vector<std::string> algorithms = {"Bubble", "Heap", "Insertion", "Selection", "Shell", "Merge", "Quick"};
        for (auto n : VALUES) {
            generateAndSortData(algorithms, n);
        }
        if (res == 0){
            int result = std::system(".\\Lineal\\Graphic.exe");
            if (result != 0) {
                std::cerr << "Error executing the plotting in GO." << std::endl;
            }
            for (const std::string& algorithm : algorithms) {
                std::string filename = ".\\Lineal\\" + algorithm;
                if (std::remove(filename.c_str()) != 0) {
                    perror("Error deleting the file");
                }
            }
            int results = std::system(".\\Lineal.png");
            if (results != 0) {
                std::cerr << "Error opening the image." << std::endl;
            }
        }
        if(res==1){
            int result = std::system(".\\dist\\Lineal.exe");
            if (result != 0) {
                std::cerr << "Error executing the plotting in Python." << std::endl;
            }
            
            for (const std::string& algorithm : algorithms) {
                std::string filename = ".\\Lineal\\" + algorithm;
                if (std::remove(filename.c_str()) != 0) {
                    perror("Error deleting the file");
                }
            }
        }
    }
    return 0;
}

//Credits ShinjiMC