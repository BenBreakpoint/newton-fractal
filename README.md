# Newton Fractal Generator
Generates Newton fractals for the function z^n - 1 using ISPC and C++

---

## Requirements
- C++ compiler (e.g. g++ or MSVC)
- [ISPC compiler](https://ispc.github.io/) installed and available in PATH

---

## Build and Run

1. **Compile the ISPC file**
```bash
ispc newton.iscp -o newton.obj
```

2. **Compile C++ and link with ISPC object**
```bash
g++ main.cpp newton.obj -o newton_fractal.exe
```

3. **Run the program**
```bash
./newton_fractal.exe [n]
```
- `n` is optional, the degree of z^n (default: 5)

---

## Output
- Generates a PNG image `newton.png` showing the Newton fractal

