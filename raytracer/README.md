# RayTracer (CSE 167, Computer Graphics)

## Overview
This project is a simple raytracer developed as part of **CSE 167: Assignment 4** under Professor Ravi Ramamoorthi at UCSD. The goal of this assignment is to implement a basic raytracer capable of rendering scenes with shadows, reflections, and other effects.

## Features
- Ray-surface intersections (spheres, triangles, and planes)
- Recursive raytracing for reflections
- Basic lighting and shading
- Camera transformations
- Acceleration structures (e.g., uniform grid) for improved performance

## Project Structure
```
raytracer/
├── src/                     # Source code
│   ├── *.cpp, *.h           # Implementation and header files
│   ├── Makefile.mac         # Build script for macOS
│   └── Makefile.win         # Build script for Windows
├── assets/                  # Assets directory
│   ├── glm-0.9.7.1/         # External library
│   └── sample_test_files/   # Input files for raytracer (e.g., .test)
├── testscenes/              # Rendered test scenes (highlight of the project)
│   ├── scene1-camera1.png
│   ├── scene1-camera2.png
│   ├── scene1-camera3.png
│   ├── scene1-camera4.png
│   ├── scene2-camera1.png
│   ├── scene2-camera2.png
│   ├── scene2-camera3.png
│   ├── scene4-ambient.png
│   ├── scene4-diffuse.png
│   ├── scene4-emission.png
│   ├── scene4-specular.png
│   ├── scene5.png
│   ├── scene6.png
│   └── scene7.png
├── output/                  # Output directory for generated images
└── README.md                # Project documentation

```

## Highlights: Test Scenes
Below are some of the rendered images produced by the raytracer:

### Scene 1
| Camera 1                      | Camera 2                      |
|-------------------------------|-------------------------------|
| ![scene1-camera1](testscenes/scene1-camera1.png) | ![scene1-camera2](testscenes/scene1-camera2.png) |

| Camera 3                      | Camera 4                      |
|-------------------------------|-------------------------------|
| ![scene1-camera3](testscenes/scene1-camera3.png) | ![scene1-camera4](testscenes/scene1-camera4.png) |

### Scene 2
| Camera 1                      | Camera 2                      | Camera 3                      |
|-------------------------------|-------------------------------|-------------------------------|
| ![scene2-camera1](testscenes/scene2-camera1.png) | ![scene2-camera2](testscenes/scene2-camera2.png) | ![scene2-camera3](testscenes/scene2-camera3.png) |

### Scene 4
| Ambient                      | Diffuse                      | Emission                      | Specular                      |
|-------------------------------|-------------------------------|-------------------------------|-------------------------------|
| ![scene4-ambient](testscenes/scene4-ambient.png) | ![scene4-diffuse](testscenes/scene4-diffuse.png) | ![scene4-emission](testscenes/scene4-emission.png) | ![scene4-specular](testscenes/scene4-specular.png) |

### Other Scenes
- Scene 5: ![scene5](testscenes/scene5.png)
- Scene 6: ![scene6](testscenes/scene6.png)
- Scene 7: ![scene7](testscenes/scene7.png)

## Getting Started

### Prerequisites
- C++17 compatible compiler (e.g., `g++`)
- `glm` library (included in the `assets/` directory)
- `FreeImage` library (installation instructions for macOS and Windows provided below)
- Make utility

### Building the Project

For macOS:
```bash
make -f Makefile.mac
```
For Windows:
```
make -f Makefile.win
```

## Running the Raytracer

Once built, execute the following command:

```bash
./raytracer [path_to_scene_file]
```
### Example

```bash
./raytracer assets/sample_test_files/scene1.test
```

### Output

The raytracer generates output images in the `output/` directory or directly overwrites existing files in `testscenes/`. Compare these outputs with the provided rendered images in the `testscenes/` directory for validation.

---

### Features and Extensions

#### Basic Features
- **Scene Rendering:** Supports triangles, spheres, and planes with recursive ray tracing.
- **Lighting Models:** Implements basic diffuse, specular, and emission shading.
- **Shadows:** Adds shadows using shadow rays.
- **Camera Transformations:** Supports different views for each test scene.

#### Acceleration Structures
- Implements a uniform grid for optimized ray-object intersection tests.

#### Extra Credit
- Additional features such as area lights (soft shadows) and complex materials can be explored for extra credit.

---

### Acknowledgements

- **CSE 167: Introduction to Computer Graphics**, UCSD
- Professor Ravi Ramamoorthi for providing the assignment and resources.
- **FreeImage Library** for image processing.
