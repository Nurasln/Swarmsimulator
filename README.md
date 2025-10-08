# C++ Boids Flocking Simulation

This project is a high-performance swarm/flocking simulation created from scratch in modern C++ using the SFML library. The project demonstrates how complex, self-organizing emergent behavior can arise from a set of simple rules.


## 📜 About The Project

This simulation is based on Craig Reynolds' classic "Boids" algorithm. Hundreds, or even thousands, of independent "agents" exhibit fluid and realistic swarm behavior by following just three simple rules. The project covers a wide range of topics, from basic C++ principles to advanced subjects like optimization and multithreading.

## ✨ Key Features

* **Boids Algorithm:** A complete implementation of the classic three rules:
    * **Separation:** Prevents agents from crowding each other.
    * **Alignment:** Causes agents to steer towards the average direction of their local flockmates.
    * **Cohesion:** Encourages agents to move towards the average position (center of mass) of their local flockmates.
* **Object-Oriented Design:** All agent behaviors and properties are encapsulated within a modular and manageable `Agent` class.
* **Performance Optimization with a Quadtree:** Instead of a naive O(n²) neighbor search algorithm, a Quadtree data structure was implemented from scratch to efficiently partition the 2D space. This reduces the time complexity of neighbor searching to **O(n log n)**, allowing for thousands of agents to be simulated in real-time.
* **Modern C++ Multithreading:** The agent update loop is parallelized using `std::thread`. This allows the simulation to take full advantage of modern multi-core CPUs, significantly boosting performance at high agent counts.

## 🛠️ Built With

* **Language:** Modern C++ (C++17)
* **Library:** [SFML](https://www.sf-ml.org/) (for graphics, windowing, timing, and basic vector math)
* **Compiler:** MinGW-w64 (GCC)
* **Environment:** Visual Studio Code

## 🚀 Getting Started

To get a local copy up and running, follow these simple steps.

### Prerequisites

* **MSYS2** with the MinGW-w64 toolchain installed.
    ```sh
    pacman -S mingw-w64-ucrt-x86_64-toolchain
    ```
* The **SFML** library installed via `pacman` in the MSYS2 environment.
    ```sh
    pacman -S mingw-w64-ucrt-x86_64-sfml
    ```
* The `C:\msys64\ucrt64\bin` directory added to your system's PATH environment variable.

### Installation & Running

1.  **Clone the repo:**
    ```sh
    git clone [https://github.com/your_username/your_project_name.git](https://github.com/your_username/your_project_name.git)
    ```
2.  **Open the folder in VS Code.**
3.  **Build the Project:**
    Press `Ctrl+Shift+B` to run the default build task. This will compile the project using the configuration in `.vscode/tasks.json` and create `main.exe`.
4.  **Run the Simulation:**
    Open the integrated terminal in VS Code (`Ctrl+` \` ``) and run the executable:
    ```sh
    main.exe
    ```

## 📂 Project Structure

```
/
├── include/
│   ├── Agent.hpp         # Header for the Agent class
│   └── Quadtree.hpp      # Header for the Quadtree data structure
├── src/
│   └── Agent.cpp         # Implementation of the Agent class methods
├── main.cpp              # Main application loop, thread management
└── .vscode/
    └── tasks.json        # Build configuration for VS Code
```

## 📄 License

Distributed under the MIT License. See `LICENSE` for more information.