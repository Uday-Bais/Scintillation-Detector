```markdown
# Scintillation-Detector

A compact, professional Geant4-based example for building and visualizing a scintillation detector simulation. This project provides a single executable (`sim`) that assembles detector geometry, a physics list, and user actions, and configures an interactive visualization environment.

Status: Experimental — intended as an educational / example project and a starting point for detector development.

Table of Contents
- Overview
- Features
- Requirements
- Repository layout
- Build (recommended)
- Running the simulation
- Configuration and common options
- Visualization and UI commands used at startup
- Development notes
- Troubleshooting
- Contributing
- License & Contact

Overview
--------
This repository demonstrates how to wire a Geant4 simulation application: creation of a run manager, a detector construction, a physics list, and action initialization. The main program (`sim.cc`) sets up Geant4 visualization and a default interactive session so the geometry and particle trajectories can be inspected immediately.

Features
--------
- Minimal, focused Geant4 application to visualize a scintillation crystal and trajectories.
- Example configuration for materials selection and detector dimension (via `DetectorConstruction` interface).
- Startup visualization commands to open an OpenGL viewer and apply sensible default rendering and trajectory coloring.

Requirements
------------
- Geant4 (with UI and visualization modules enabled). The CMake expects Geant4 CMake configuration to be discoverable by CMake.
- CMake ≥ 3.2 (CMakeLists sets this minimum).
- A C++ compiler supported by your Geant4 installation (e.g., GCC or Clang).
- OpenGL/display (for interactive visualization). On headless servers, use Xvfb or a non-OpenGL driver.

Repository layout
-----------------
- CMakeLists.txt
  - Top-level CMake configuration. Finds Geant4, includes the `include/` directory, collects sources from `src/*.cc`, copies macros from `macros/*.mac`, and builds the `sim` executable.
- sim.cc
  - The program entrypoint: constructs run manager, detector construction, physics list, action initialization, and configures visualization/UI.
- include/
  - Header files for detector construction, physics list and user actions (expected names referenced by `sim.cc`: `construction.hh`, `physics.hh`, `action.hh`).
- src/
  - Implementation files (any `.cc` here are picked up by CMake automatically).
- macros/
  - Place macro files (e.g., visualization or run macros) here; CMake copies `macros/*.mac` to the build directory for convenience.

Build (recommended)
-------------------
1. Create and enter a build directory:
   mkdir -p build
   cd build

2. Configure with CMake:
   cmake ..

   Notes:
   - If CMake cannot find Geant4 automatically, point it explicitly:
     cmake -DGeant4_DIR=/path/to/Geant4/lib/Geant4-<version>/cmake ..
   - Some Geant4 installations provide an environment script (e.g., `geant4.sh`) that sets environment variables used by CMake. If provided, source it before running CMake:
     source /path/to/geant4/install/bin/geant4.sh

3. Compile:
   make -j$(nproc)

4. Result:
   The executable `sim` will be available in the build directory after a successful build.

Running the simulation
----------------------
Interactive (visualization)
- Execute the binary:
  ./sim

- `sim.cc` creates a `G4UIExecutive` and a `G4VisExecutive`, and then starts an interactive session so you can issue commands at the Geant4 prompt and interact with the viewer.

Batch (macros)
- Place macro files in the repository `macros/` directory. CMake copies them to the build directory so you can run them after building.
- To execute a macro from the Geant4 prompt:
  /control/execute myrun.mac

- If you prefer automated, non-interactive invocation, expand `sim.cc` to accept a macro filename from `argv` and execute it before `SessionStart()`.

Configuration and common options
--------------------------------
The main program configures `DetectorConstruction` with two example calls. Change them in `sim.cc` or expose them via your own UI commands:

- Material selection (index mapping shown as comments in `sim.cc`):
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

  Example in code:
  detectorConstruction->SetMaterial(9);

- Crystal thickness (example):
  detectorConstruction->SetCrystalZ(20.0*mm);

Multithreading
-------------
- `sim.cc` contains commented code showing how to instantiate `G4MTRunManager` (Geant4 multithreaded run manager). To enable multithreading:
  - Use `G4MTRunManager` instead of `G4RunManager`.
  - Ensure your Geant4 build supports multithreading and that you link against the right Geant4 libraries.

Visualization and UI commands applied at startup
-----------------------------------------------
`sim.cc` applies a sequence of visualization commands to prepare the viewer. These are executed automatically when the program launches:

- /vis/open OGL
- /vis/viewer/set/autoRefresh false
- /vis/drawVolume
- /vis/viewer/set/viewpointVector 1 1 1
- /vis/viewer/set/lightsVector 1 1 1
- /vis/scene/add/trajectories smooth
- /vis/scene/add/axes 0 0 0 50 mm
- /vis/modeling/trajectories/create/drawByParticleID
- /vis/modeling/trajectories/drawByParticleID-0/set gamma green
- /vis/modeling/trajectories/drawByParticleID-0/set e- red
- /vis/modeling/trajectories/drawByParticleID-0/set e+ blue
- /vis/modeling/trajectories/drawByParticleID-0/set opticalphoton yellow
- /vis/scene/endOfEventAction accumulate
- /tracking/storeTrajectory 1
- /vis/viewer/set/autoRefresh true
- /tracking/verbose 1

These commands provide a sensible default for geometry rendering, trajectory visualization, coloring by particle type, and interactivity.

Development notes
-----------------
- Headers should be placed in `include/` and implementations in `src/`. CMake already adds `include/` to the include path and globs `src/*.cc` automatically.
- To add additional executables or change build settings, update CMakeLists.txt.
- Consider adding unit or integration tests for physics or geometry behavior where feasible.

Troubleshooting
---------------
- CMake cannot locate Geant4:
  - Ensure Geant4 is installed and that the `Geant4_DIR` variable points to the Geant4 CMake config directory (e.g., `<geant4-install>/lib/Geant4-<version>/cmake`).
  - Source Geant4-provided environment script if available.

- OpenGL viewer fails:
  - Confirm display/X server is available. On headless machines, use Xvfb or a software OpenGL driver.
  - Alternatively, configure Geant4 to use a different visualization backend if required.

- Missing headers or linker errors:
  - Verify `include/` contains the header files referenced by `sim.cc` (e.g., `construction.hh`, `physics.hh`, `action.hh`).
  - Ensure all `.cc` implementations are present in `src/`.

Contributing
------------
Contributions are welcome. Suggested workflow:
1. Fork the repository.
2. Create a descriptive branch for your changes (feature/fix/docs).
3. Add tests and documentation for non-trivial changes.
4. Submit a pull request describing the change and rationale.

When submitting changes that modify build behavior, please include explicit build instructions and any new external dependencies.

License
-------
No license file is present in the repository. If you intend to share or publish this project, add a LICENSE file (e.g., MIT, Apache 2.0, or BSD) so users know how the software may be used.

Contact
-------
Repository owner: Uday-Bais (GitHub: @Uday-Bais)

Acknowledgements
----------------
- This project is structured as a Geant4 tutorial-style example. It adapts standard Geant4 application patterns (run manager, detector construction, physics list, user actions, visualization) as a compact demonstrator.

```
