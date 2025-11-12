# Scintillation-Detector

A small Geant4-based example project that builds a simple simulation executable (`sim`) to visualize and run a scintillation detector geometry. This repository includes a top-level CMake file and a main program (`sim.cc`) which wires together detector construction, physics, and action initialization. It expects Geant4 with the UI and visualization components to be available.

---

Table of contents
- Project overview
- Repository layout
- Key source: sim.cc (what it does)
- CMake build details
- Requirements
- Build instructions
- Running the simulation (interactive & batch)
- Useful visualization / UI commands used by sim.cc
- How to modify detector/materials
- Troubleshooting & notes
- License

---

Project overview
This project constructs and runs a Geant4 simulation for a scintillation detector. The main executable is `sim`, which initializes the run manager, the detector construction, the physics list, and user actions. It also sets up the visualization manager and a set of default visualization/UI commands so you can immediately view the geometry and trajectories.

Repository layout (what I inspected)
- CMakeLists.txt — top-level CMake configuration (finds Geant4, declares `sim` target, copies macros).
- sim.cc — the main program; creates run manager, initializes detector/physics/actions, and configures visualization and UI.
- include/ — include directory (expected to contain header files like `construction.hh`, `physics.hh`, `action.hh`; the main program includes them).
- src/ — source directory (CMake is set to glob `src/*.cc` for additional implementation files).
- macros/ — referenced by CMake (any `*.mac` files placed here will be copied into the build directory).

Note: sim.cc references `construction.hh`, `physics.hh`, and `action.hh`. Implementations for these are expected to be in `include/` and `src/`. The CMake file globs `src/*.cc`, so any `.cc` files you add there will be compiled into the `sim` executable automatically.

Key source: sim.cc (high level)
- Creates a G4RunManager (single-thread by default; code contains commented lines suggesting how to use `G4MTRunManager` for multithreading).
- Instantiates and sets `DetectorConstruction`:
  - The main file shows a call to `detectorConstruction->SetMaterial(9);` — a numeric selector for detector material.
  - It also sets a crystal thickness via `SetCrystalZ(20.0*mm);`.
  - A comment lists the material options (interpreted from the in-source comment):
    - 0 = LXe
    - 1 = NaI_pure
    - 2 = NaI(Tl)
    - 3 = CsI_pure
    - 4 = CsI(Tl)
    - 5 = PbWO4
    - 6 = BGO
    - 7 = CeBr3
    - 8 = LYSO
    - 9 = MyMade
- Registers `Physics()` and `ActionInitialization()` with the run manager.
- Initializes visualization (uses `G4VisExecutive`) and applies a sequence of visualization/UI commands to:
  - Open an OpenGL viewer
  - Configure viewpoint/lighting
  - Add trajectory drawing, axes, per-event accumulation, and particle-colour mapping
  - Set tracking verbosity and store trajectories
- Starts an interactive UI session using `G4UIExecutive`.

CMakeLists.txt (what it does)
- Requires CMake >= 3.2 and sets project name `Cherenkov`.
- Finds Geant4 with `find_package(Geant4 REQUIRED ui_all vis_all)`.
- Includes the `include/` directory.
- Glob-matches all `src/*.cc` source files and includes them in the build.
- Copies any macros matching `macros/*.mac` to the build directory (so they are available next to the executable).
- Builds an executable named `sim` from `sim.cc` and `${sources}`, linking to `${Geant4_LIBRARIES}`.
- Adds a custom target `Tutorial` that depends on `sim`.

Requirements
- Geant4 installed and configured with CMake config files (must include UI and visualization modules such as OpenGL).
- A C++ compiler supported by Geant4 (typically gcc/clang on Linux).
- CMake (3.2 or newer, although a modern CMake is recommended).
- For interactive OpenGL visualization, X server/display access (or appropriate OpenGL context on your platform).

Build instructions (recommended)
1. From the repository root:
   - mkdir build
   - cd build
   - cmake ..
     - If CMake cannot find Geant4 automatically, point it using:
       - cmake -DGeant4_DIR=/path/to/Geant4/installation/lib64/Geant4-<version>/cmake ..
     - Or make sure Geant4 environment is set (source Geant4's `geant4.sh` if provided by your installation).
   - make -jN
2. After building, the `sim` executable will be in the build directory.

Running the simulation
Interactive mode (recommended for visualization)
- Run the executable:
  - ./sim
- This will open the Geant4 UI (as `sim.cc` creates a `G4UIExecutive`) and the visualization window (the code applies a set of visualization commands automatically). Use the UI prompt to issue commands or execute macro files.

Batch mode (macros)
- Place macro files in `macros/` in the repository root; CMake will copy them into the build directory.
- In the interactive UI you can run:
  - /control/execute yourmacro.mac
- Some Geant4 programs accept a macro file as a command-line argument; if that's desired, adapt `sim.cc` to detect argc/argv and run `/control/execute` automatically when a macro is provided.

Useful visualization / UI commands applied by sim.cc
(sim.cc invokes the following commands at startup)
- /vis/open OGL — open an OpenGL viewer
- /vis/viewer/set/autoRefresh false — temporarily disable auto-refresh while configuring
- /vis/drawVolume — draw the world/volumes
- /vis/viewer/set/viewpointVector 1 1 1 — set the camera direction
- /vis/viewer/set/lightsVector 1 1 1 — set lights direction
- /vis/scene/add/trajectories smooth — add smoothed trajectories
- /vis/scene/add/axes 0 0 0 50 mm — add XYZ axes at origin (50 mm)
- /vis/modeling/trajectories/create/drawByParticleID — enable per-particle drawing
- /vis/modeling/trajectories/drawByParticleID-0/set gamma green — color gamma green
- /vis/modeling/trajectories/drawByParticleID-0/set e- red — color electron red
- /vis/modeling/trajectories/drawByParticleID-0/set e+ blue — color positron blue
- /vis/modeling/trajectories/drawByParticleID-0/set opticalphoton yellow — color optical photon yellow
- /vis/scene/endOfEventAction accumulate — accumulate scene between events
- /tracking/storeTrajectory 1 — store trajectories for visualization
- /vis/viewer/set/autoRefresh true — re-enable auto-refresh
- /tracking/verbose 1 — set tracking verbosity (console output)

How to modify detector/materials
- sim.cc calls:
  - detectorConstruction->SetMaterial(<index>);
  - detectorConstruction->SetCrystalZ(<value_in_mm>);
- To change the material or dimensions, change the numbers in `sim.cc` or provide UI commands (if `DetectorConstruction` is implemented to accept UI commands).
- The comment in `sim.cc` lists material index mappings (0..9). Consult `construction.hh`/`construction.cc` to see exact material definitions and how `SetMaterial` maps indices to materials.

Multithreading
- The sim.cc includes commented lines showing how to use `G4MTRunManager` (Geant4 multithreaded run manager). To enable multithreading:
  - Replace `G4RunManager` with `G4MTRunManager` and link/build with a Geant4 multithread-capable installation.
  - Ensure your Geant4 build and environment support MT.

Adding sources and headers
- Put header files in `include/` and implementation `.cc` files in `src/`.
- CMakeLists already includes `${PROJECT_SOURCE_DIR}/include` and globs `src/*.cc`, so no CMake changes are required for additional source files placed in those locations.

Troubleshooting
- CMake cannot find Geant4:
  - Make sure Geant4 is installed and its CMake package files are visible (set `Geant4_DIR` or source your Geant4 environment script).
- OpenGL viewer fails to open:
  - Ensure you have an X server/display or compatible OpenGL support. On headless machines, consider using a virtual X server (Xvfb) or use a non-OpenGL visualization driver.
- Missing headers (construction.hh, etc.):
  - Ensure the `include/` and `src/` directories contain the implementations for the detector, physics list, and action initialization. The main program references them and they must be present to compile.

License
- No license file was found in the repository. If you intend to share or publish the project, consider adding an appropriate license (e.g., MIT, Apache 2.0, BSD).

Contact / Contributing
- If you provide additional files (detector/physics/action source files or macros), I can update this README with examples of macro files, sample run commands, and screenshots of the visualization.

---
What I did: I inspected the top-level files (CMakeLists.txt, sim.cc, README.md) and used the information in `sim.cc` and CMake to create a full README that documents how the project is structured, how to build and run it, and how to adjust the detector/materials and visualization.

What I can do next: If you provide the contents of `include/` and `src/` (the detector, physics, and action implementations) or example macros, I will extend the README with concrete examples, typical macros (e.g., `vis.mac`, `run.mac`), and sample expected output/usage.  
