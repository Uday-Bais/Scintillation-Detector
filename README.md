# Scintillation-Detector

A compact, professional **Geant4-based** example for building and visualizing a scintillation detector simulation.  
This project provides a single executable (`sim`) that assembles detector geometry, physics, and user actions, and configures an interactive visualization environment.

> **Status:** Experimental — intended as an educational / example project and a starting point for detector development.

---

## 📘 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Requirements](#requirements)
- [Repository Layout](#repository-layout)
- [Build (Recommended)](#build-recommended)
- [Running the Simulation](#running-the-simulation)
- [Configuration and Common Options](#configuration-and-common-options)
- [Visualization and UI Commands](#visualization-and-ui-commands)
- [Development Notes](#development-notes)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [Contact](#contact)

---

## 🧩 Overview
This repository demonstrates how to wire a **Geant4 simulation application**: creating a run manager, detector construction, physics list, and action initialization.  
The main program (`sim.cc`) sets up Geant4 visualization and an interactive session, allowing geometry and particle trajectories to be inspected immediately.

---

## ✨ Features
- Minimal, focused Geant4 application for **scintillation crystal visualization** and **trajectory display**  
- Example configuration for **materials** and **detector dimensions** via `DetectorConstruction`  
- Preloaded **visualization commands** for OpenGL viewer setup and colored particle trajectories

---

## ⚙️ Requirements
- **Geant4** (built with UI and visualization modules)  
- **CMake ≥ 3.2**  
- A **C++ compiler** compatible with your Geant4 installation (e.g., GCC or Clang)  
- **OpenGL** for visualization (use Xvfb or a software renderer for headless servers)

---

## 📁 Repository Layout

Scintillation-Detector/
├── CMakeLists.txt # Build configuration; finds Geant4, builds sim
├── sim.cc # Main entry point; sets up detector, physics, actions, UI, visualization
├── include/ # Header files (construction.hh, physics.hh, action.hh)
├── src/ # Source implementations (.cc files)
└── macros/ # Example macro scripts (.mac) copied to build dir


---

## 🛠️ Build (Recommended)

1. **Create and enter a build directory:**
   ```bash
   mkdir -p build && cd build
   cmake ..
   make -j(nproc)
   ./sim
Add macro file as needed for batch execution
   
