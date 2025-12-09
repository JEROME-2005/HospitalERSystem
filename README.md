🚑 Hospital Emergency Response System (H.E.R.S)

A Modular C++ Simulation for Emergency Workflow, Patient Triage & Hospital Routing

🚀 Overview

The Hospital Emergency Response System (H.E.R.S) is a highly modular C++ system designed to simulate operations inside a hospital during emergency scenarios.

It models:

Patient arrival

Emergency triage

Route optimization inside the hospital

Staff allocation

Treatment simulation

Performance monitoring

This project serves as an excellent example of data structures, graph algorithms, and system design in modern C++.

🩺 System Features
✔️ Patient Triage System

Priority queue based on patient severity

Real-time priority updates

Custom MinHeap implementation

✔️ Graph-Based Hospital Navigation

Hospital represented as weighted graph

Shortest path routing using Dijkstra

Minimum Spanning Tree (MST) generation (Kruskal) for infrastructure optimization

✔️ Hospital Staff Management

Doctor, nurse, and specialist assignment

Load balancing of staff during critical events

✔️ Complete Emergency Simulation Engine

Multi-step workflow engine

Patient movement simulation

Treatment time modelling

Performance metrics logging

✔️ Data Validation Mechanism

Ensures safe and consistent simulation input

Reports invalid patient data

✔️ Unit Testing Framework

TestRunner for automated flows

Graph structure tests

MinHeap & TriageQueue tests

🧰 Tech Stack
Component	Technology
Language	C++17
Build System	Makefile / MinGW / g++
Architecture	Modular C++ with separated headers & source
Testing	Custom TestRunner
OS Support	Windows & Linux
🏗️ Architecture
High-Level Structure
┌─────────────────────────────┐
│   Emergency Response System  │
└──────────────┬──────────────┘
               │
  ┌────────────┴──────────────┐
  │                            │
Patient Management       Routing System
(TriageQueue, Stack)     (Graphs, MST, Dijkstra)
  │                            │
  └────────────┬──────────────┘
               │
        Simulation Engine
               │
         Performance Monitor

📐 Algorithms Used
🔹 Dijkstra’s Shortest Path Algorithm

Used to route patients to correct hospital rooms.

🔹 Kruskal’s MST Algorithm

Used to generate an optimal network of hospital units.

🔹 Custom MinHeap

Implements the triage queue — faster than std::priority_queue for this use-case.

🔹 State Stack System

Each patient has their own stack describing:

Checked-in

Examined

Diagnosed

Treated

Released

📁 Project Structure

(Generated automatically by analyzing your ZIP)

New folder/
│── main.cpp
│── Makefile
│── build.bat
│── hospital.exe
│── .vscode/
│── build/
│── include/
│── src/
│── tests/


A detailed breakdown is already included in your previous README section.

🛠️️ Setup & Installation
Option 1 — Using Makefile (Linux & Windows MinGW)
make

Option 2 — Windows build.bat

Double-click:

build.bat

Run the program
./hospital.exe

🧭 Usage Guide

After running:

The system loads hospital layout

Patients enter the triage queue

System assigns priority

Dijkstra routes patient

Staff are assigned

Simulation begins

Logs & performance metrics generated

🧪 Testing

Run tests:

g++ tests/*.cpp -I include -o TestRunner
./TestRunner


Includes tests for:

Graph

MinHeap

Routing

Data validation

📊 Performance & Monitoring

The PerformanceMonitor module tracks:

Simulation run time

Queue wait times

Routing computation time

Staff allocation stats

System bottlenecks

Error logs appear under:

build/error.log

🖼️ Screenshots (Placeholder)
[ Add your images here ]
/screenshots/
   triage_flow.png
   graph_visual.png
   simulation_output.png

🔮 Future Enhancements

Add GUI using Qt or ImGui

Real-time graph visualization

Database integration (PostgreSQL/MySQL)

REST API layer (CPP REST SDK)

Web dashboard for monitoring

Export reports in PDF

🤝 Contributing

Contributions are welcome!

Fork the repo

Create a feature branch

Submit a pull request

📜 License

This project is currently under Educational & Portfolio License — free to use, modify, and display for academic or personal portfolio purposes.