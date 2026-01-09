
# Minesweeper (C++ / SFML)

A faithful recreation of the classic Minesweeper game, built using **C++** and the **SFML (Simple and Fast Multimedia Library)** graphics engine.

This project was originally developed in **2023** as a university coursework project. In **2026**, I revisited and refactored the codebase to modernize it for **Apple Silicon (M-series)** architecture and migrate it from SFML 2.5 to the latest **SFML 3.0**, demonstrating my ability to maintain and update legacy software.

---

## 🎮 Features
* **Core Gameplay**: Recursive tile revealing, flagging mechanism, and win/loss states.
* **Leaderboard System**: Persists top 5 scores using file I/O (`std::fstream`).
* **Custom UI**: Custom-built sprite rendering for digits, buttons, and board tiles.
* **Debug Mode**: Developer toggle to reveal all mines for testing purposes.
* **Event Handling**: Responsive mouse and keyboard input for player names.

## 🛠️ Technical Highlights
* **Language**: C++17 (Updated from C++11).
* **Library**: SFML 3.0 (Graphics, Windowing, System).
* **Concepts Applied**:
    * **Object-Oriented Programming**: distinct classes for `Board`, `Cell`, and `GUI` management.
    * **Recursion**: Implemented the "flood fill" algorithm to reveal empty adjacent tiles.
    * **File I/O**: Reading board configurations and writing leaderboard data.
    * **Legacy Refactoring**: Resolved breaking changes in SFML 3.0 (Type-safe Event system, `std::optional` polling, and resource management).

## 🚀 How to Build & Run
**Prerequisites**:
* C++ Compiler (Clang/GCC)
* SFML 3.0 Library (via Homebrew on macOS)

**Build Command (macOS / Apple Silicon)**:
```bash
# Compile
/usr/bin/clang++ -std=c++17 src/*.cpp -o minesweeper -I/opt/homebrew/include -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# Run
./minesweeper

```

---

## 📝 Retrospective & Future Improvements

*A note on the codebase: The core logic of this project was written in 2023. While fully functional, my coding standards and understanding of architectural patterns have evolved since then.*

### If I were to rebuild this today, I would improve:

1. **Namespace Management**:
* *Current*: Uses `using namespace std;` globally.
* *Improvement*: Remove global namespace pollution to prevent naming collisions in larger projects.


2. **Separation of Concerns (MVC Pattern)**:
* *Current*: The Rendering logic (`GUI.h`) and Game Loop (`main.cpp`) are tightly coupled.
* *Improvement*: Implement a strict **Model-View-Controller** pattern. The `Board` (Model) should have zero knowledge of SFML textures. A separate `Renderer` (View) class should handle all drawing.


3. **Resource Management**:
* *Current*: Textures are loaded directly in struct constructors.
* *Improvement*: Implement a **Resource Manager** (Singleton or passed service) to load textures once and hand out references. This prevents reloading assets and improves memory efficiency.


4. **Modern C++ Practices**:
* *Current*: Uses raw pointers and older C-style casting in some areas.
* *Improvement*: Utilize smart pointers (`std::unique_ptr`) and `static_cast` for type safety.


5. **Build System**:
* *Improvement*: Replace raw terminal commands with **CMake**. This would make the project cross-platform (Windows/Linux/macOS) without changing build scripts.



---

## 📂 Project Structure

```text
.
├── files/              # Assets (Images, Fonts, Configs)
├── src/
│   ├── main.cpp        # Entry point & Game Loop
│   ├── Board.h         # Game logic & Grid management
│   ├── Cell.h          # Individual tile states
│   └── GUI.h           # Texture management & Rendering helpers
└── README.md

```

## 👤 Author

**Mya Ramsey**

* *Original Project*: July 2023
* *Refactored*: January 2026
