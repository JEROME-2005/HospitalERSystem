@echo off
cls
echo ========================================
echo  H.E.R.O.S Final Build
echo ========================================

REM Clean
if exist build rmdir /s /q build
if exist hospital.exe del hospital.exe
mkdir build

echo.
echo Compiling Core...
g++ -std=c++11 -Iinclude -c src/core/Patient.cpp -o build/Patient.o 2>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/core/HospitalRoom.cpp -o build/HospitalRoom.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/core/MedicalStaff.cpp -o build/MedicalStaff.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/core/EmergencyResponseSystem.cpp -o build/EmergencyResponseSystem.o 2>>build/error.log
if errorlevel 1 goto :error

echo Compiling Data Structures...
g++ -std=c++11 -Iinclude -c src/data_structures/TriageQueue.cpp -o build/TriageQueue.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/data_structures/PatientState.cpp -o build/PatientState.o 2>>build/error.log
if errorlevel 1 goto :error

echo Compiling Algorithms...
g++ -std=c++11 -Iinclude -c src/algorithms/Graph.cpp -o build/Graph.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/algorithms/DijkstraRouter.cpp -o build/DijkstraRouter.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/algorithms/MSTGenerator.cpp -o build/MSTGenerator.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/algorithms/RadixSorter.cpp -o build/RadixSorter.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/algorithms/QuickSorter.cpp -o build/QuickSorter.o 2>>build/error.log
if errorlevel 1 goto :error

echo Compiling Utilities...
g++ -std=c++11 -Iinclude -c src/utils/PerformanceMonitor.cpp -o build/PerformanceMonitor.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/utils/DataValidator.cpp -o build/DataValidator.o 2>>build/error.log
if errorlevel 1 goto :error

g++ -std=c++11 -Iinclude -c src/utils/Simulation.cpp -o build/Simulation.o 2>>build/error.log
if errorlevel 1 goto :error

echo Linking...
g++ -std=c++11 -Iinclude main.cpp build/*.o -o hospital.exe 2>>build/error.log
if errorlevel 1 goto :error

echo.
echo ========================================
echo  SUCCESS! Run: hospital.exe
echo ========================================
goto :end

:error
echo.
echo ========================================
echo  BUILD FAILED!
echo ========================================
type build\error.log
echo.

:end
pause