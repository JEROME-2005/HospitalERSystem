@echo off
cls
echo ========================================
echo  H.E.R.O.S Clean Build (MinGW-32)
echo ========================================

REM Clean old files
echo Cleaning old build files...
if exist build rmdir /s /q build
if exist hospital.exe del hospital.exe

REM Create build directory
mkdir build

echo.
echo [1/5] Compiling Core modules...
g++ -std=c++11 -Wall -Iinclude -c src/core/Patient.cpp -o build/Patient.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/core/HospitalRoom.cpp -o build/HospitalRoom.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/core/MedicalStaff.cpp -o build/MedicalStaff.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/core/EmergencyResponseSystem.cpp -o build/EmergencyResponseSystem.o || goto :error

echo [2/5] Compiling Data Structures...
g++ -std=c++11 -Wall -Iinclude -c src/data_structures/TriageQueue.cpp -o build/TriageQueue.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/data_structures/PatientState.cpp -o build/PatientState.o || goto :error

echo [3/5] Compiling Algorithms...
g++ -std=c++11 -Wall -Iinclude -c src/algorithms/Graph.cpp -o build/Graph.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/algorithms/DijkstraRouter.cpp -o build/DijkstraRouter.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/algorithms/MSTGenerator.cpp -o build/MSTGenerator.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/algorithms/RadixSorter.cpp -o build/RadixSorter.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/algorithms/QuickSorter.cpp -o build/QuickSorter.o || goto :error

echo [4/5] Compiling Utilities...
g++ -std=c++11 -Wall -Iinclude -c src/utils/PerformanceMonitor.cpp -o build/PerformanceMonitor.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/utils/DataValidator.cpp -o build/DataValidator.o || goto :error
g++ -std=c++11 -Wall -Iinclude -c src/utils/Simulation.cpp -o build/Simulation.o || goto :error

echo [5/5] Linking executable...
g++ -std=c++11 -Wall -Iinclude main.cpp build/*.o -o hospital.exe || goto :error

echo.
echo ========================================
echo  BUILD SUCCESSFUL!
echo ========================================
echo  Run: hospital.exe
echo ========================================
goto :end

:error
echo.
echo ========================================
echo  BUILD FAILED!
echo ========================================
echo Check errors above

:end
pause