@echo off
echo ========================================
echo  H.E.R.O.S Build Script (MinGW-32)
echo ========================================

REM Create build directory
if not exist build mkdir build

echo.
echo [1/5] Compiling Core modules...
g++ -std=c++11 -Iinclude -c src/core/Patient.cpp -o build/Patient.o
g++ -std=c++11 -Iinclude -c src/core/HospitalRoom.cpp -o build/HospitalRoom.o
g++ -std=c++11 -Iinclude -c src/core/MedicalStaff.cpp -o build/MedicalStaff.o
g++ -std=c++11 -Iinclude -c src/core/EmergencyResponseSystem.cpp -o build/EmergencyResponseSystem.o

echo [2/5] Compiling Data Structures...
g++ -std=c++11 -Iinclude -c src/data_structures/TriageQueue.cpp -o build/TriageQueue.o
g++ -std=c++11 -Iinclude -c src/data_structures/PatientState.cpp -o build/PatientState.o

echo [3/5] Compiling Algorithms...
g++ -std=c++11 -Iinclude -c src/algorithms/Graph.cpp -o build/Graph.o
g++ -std=c++11 -Iinclude -c src/algorithms/DijkstraRouter.cpp -o build/DijkstraRouter.o
g++ -std=c++11 -Iinclude -c src/algorithms/MSTGenerator.cpp -o build/MSTGenerator.o
g++ -std=c++11 -Iinclude -c src/algorithms/RadixSorter.cpp -o build/RadixSorter.o
g++ -std=c++11 -Iinclude -c src/algorithms/QuickSorter.cpp -o build/QuickSorter.o

echo [4/5] Compiling Utilities...
g++ -std=c++11 -Iinclude -c src/utils/PerformanceMonitor.cpp -o build/PerformanceMonitor.o
g++ -std=c++11 -Iinclude -c src/utils/DataValidator.cpp -o build/DataValidator.o
g++ -std=c++11 -Iinclude -c src/utils/Simulation.cpp -o build/Simulation.o

echo [5/5] Linking executable...
g++ -std=c++11 -Iinclude main.cpp build/*.o -o hospital.exe

if exist hospital.exe (
    echo.
    echo ========================================
    echo  BUILD SUCCESSFUL!
    echo ========================================
    echo  Run: hospital.exe
    echo ========================================
) else (
    echo.
    echo ========================================
    echo  BUILD FAILED!
    echo ========================================
)

pause