# Project 7 — Putting It All Together

**Course:** CST-310 — Computer Graphics Lecture & Lab
**Institution:** Grand Canyon University
**Authors:** Jared Walker (Part 1), James Hohn (Part 2)
**Instructor:** Ricardo Citro
**Date:** March 15, 2026

---

## Overview

This project extends two provided OpenGL starter programs with animation, keyboard interactivity, material-based lighting, and scene geometry. Both parts use the fixed-function OpenGL pipeline with GLUT for windowing and input handling. No external shaders, mesh files, or image files are required.

---

## Part 1 — CheckeredTriangles

Extends `CheckeredTriangles.cpp` with continuous 360-degree spin animation, stop/start controls, directional movement on both axes, and perspective zoom via field-of-view adjustment.

### Compile & Run

```bash
g++ CheckeredTriangles.cpp -o CheckeredTriangles -lGL -lGLU -lglut -std=c++17
./CheckeredTriangles
```

### Controls

| Key | Action |
|-----|--------|
| `C` | Start / continue spinning |
| `P` | Pause spinning |
| `U` | Move image up |
| `D` | Move image down |
| `L` | Move image left |
| `R` | Move image right |
| `+` | Zoom in |
| `-` | Zoom out |
| `ESC` | Quit |

---

## Part 2 — ColorCubeFlyby

Extends `ColorCube.cpp` with scene rotation, stop/continue animation, vertical movement, zoom, three additional cubes with distinct material properties and illumination, two vertical boundary planes, and cube bouncing behavior.

### Compile & Run

```bash
g++ ColorCube.cpp -o ColorCube -lGL -lGLU -lglut -std=c++17
./ColorCube
```

### Controls

| Key | Action |
|-----|--------|
| `R` | Toggle scene rotation |
| `S` | Stop animation |
| `C` | Continue animation |
| `U` | Move scene up |
| `D` | Move scene down |
| `+` | Zoom in |
| `-` | Zoom out |
| `ESC` | Quit |

---

## Software Requirements

- **OS:** Ubuntu 22.04 LTS or later (any Debian-based Linux)
- **Compiler:** g++ with C++17 support
- **Libraries:** FreeGLUT, Mesa OpenGL, GLU

Install dependencies:

```bash
sudo apt install build-essential freeglut3-dev libglu1-mesa-dev -y
```

---

## File Structure

```
project7/
├── CheckeredTriangles.cpp   # Part 1 — textured triangles
├── ColorCube.cpp            # Part 2 — animated cube flyby
├── instructions.txt         # Run instructions and software requirements
├── README.md                # This file
└── screenshots/
    ├── part1_spin.png
    ├── part1_zoom.png
    ├── part2_cubes.png
    └── part2_rotation.png
```

---

## References

- de Vries, J. (2021). *Basic lighting*. LearnOpenGL. https://learnopengl.com/Lighting/Basic-Lighting
- de Vries, J. (2021). *Textures*. LearnOpenGL. https://learnopengl.com/Getting-started/Textures
- Khronos Group. (2024). *OpenGL wiki*. https://www.khronos.org/opengl/wiki
- Shreiner, D., Sellers, G., Kessenich, J., & Licea-Kane, B. (2013). *OpenGL programming guide* (8th ed.). Addison-Wesley.
- Angel, E., & Shreiner, D. (2015). *Interactive computer graphics* (7th ed.). Pearson.
