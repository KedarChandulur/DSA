# DSA – Data Structures & Algorithms in C++

This project is a growing collection of algorithmic and cryptographic implementations written in modern C++ (C++23). Each concept is isolated in its own file or module and can be tested individually through a central `main.cpp` file.

---

## ⚙️ How It Works

- All implementations are organized under the `Source` directory by topic (e.g., `Algorithms`, `Cryptology`, etc.).
- Each algorithm or technique (like QuickSort, Catalan, AES, SDES, etc.) is defined in its own `.cpp` and `.h` files.
- Testing is handled through `main.cpp` using toggle macros (e.g., `#define AES_TEST true`)—only one should be active at a time.
- Inputs can be modified manually within the `main.cpp` or constant header files like `SDESConstants.h`.

---

## 🔨 Building and Running

To compile:

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

To run:
```bash
./dsa_exec
```
Make sure the appropriate test macro is enabled in main.cpp before building.

## Why This Repo?
This isn’t just a collection of throwaway code for interview prep. It’s structured with reusability and clarity in mind—minimal main functions in logic files, encapsulated class designs, and clean integration with CMake to keep it platform-friendly.
