# Scintillation-Detector

A compact, professional **Geant4-based** example for building and visualizing a scintillation detector simulation.  
This project provides a single executable (`sim`) that assembles detector geometry, physics, and user actions, and configures an interactive visualization environment.

---

## 📘 Table of Contents
- [Overview](#overview)
- [How the Simulation Works](#how-the-simulation-works)
- [Features](#features)
- [Calculating Detector Efficiency](#calculating-detector-efficiency)
- [Configurable Parameters in sim.cc](#configurable-parameters-in-simcc)
- [Available Scintillator Materials](#available-scintillator-materials)
- [Physics Processes](#physics-processes)
- [Requirements](#requirements)
- [Build (Recommended)](#build-recommended)
- [Running the Simulation](#running-the-simulation)
- [Configuration and Common Options](#configuration-and-common-options)
- [Visualization and UI Commands](#visualization-and-ui-commands)

---

## 🧩 Overview

This repository demonstrates how to wire a **Geant4 simulation application**: creating a run manager, detector construction, physics list, and action initialization.  
The main program (`sim.cc`) sets up Geant4 visualization and an interactive session, allowing geometry and particle trajectories to be inspected immediately.

The simulation models a complete **scintillation detection system** where:
1. **Gamma rays** (or other particles) enter a scintillation crystal
2. The gamma ray interacts with the crystal material through photoelectric effect, Compton scattering, or pair production
3. Energy deposited in the crystal causes **scintillation** — the emission of optical photons
4. Optical photons propagate through the crystal with realistic optical properties (refraction, absorption, reflection)
5. A **sensitive detector** (modeled as a silicon photodetector) at the back of the crystal records photon hits
6. Reflective coatings on the crystal surfaces guide optical photons toward the detector

---

## 🔬 How the Simulation Works

### Geometry Setup
The detector geometry consists of:
- **World volume**: A 20×20×20 cm³ air-filled box
- **Scintillation crystal**: A 10×10 mm² cross-section crystal with configurable thickness (Z dimension)
- **Silicon photodetector**: A 10×10×1 mm³ detector positioned directly behind the crystal
- **Reflective coating**: 98% reflective surfaces on the front and sides of the crystal to maximize light collection

### Particle Source
The primary particle generator creates:
- **Gamma rays** with 1.022 MeV energy (customizable in `src/generator.cc`)
- Fired along the **-Z axis** toward the crystal front face
- Starting position at Z = +20 mm (above the crystal)

### Detection Process
1. When a gamma ray deposits energy in the scintillator, optical photons are generated
2. The number of photons depends on the material's **scintillation yield** (photons/MeV)
3. Photons propagate according to the material's optical properties
4. Photons reaching the silicon detector are counted and their positions recorded
5. The **stepping action** counts newly created optical photons per event

---

## ✨ Features

- Minimal, focused Geant4 application for **scintillation crystal visualization** and **trajectory display**  
- Example configuration for **materials** and **detector dimensions** via `DetectorConstruction`  
- Preloaded **visualization commands** for OpenGL viewer setup and colored particle trajectories
- **10 different scintillator materials** with realistic optical properties
- **Configurable crystal size** for efficiency studies
- **Photon counting** and hit position recording
- **ROOT file output** for data analysis
- **Reflective coating** simulation for realistic light collection

---

## 📊 Calculating Detector Efficiency

One of the key uses of this simulation is to **study detector efficiency** as a function of crystal dimensions. The efficiency can be calculated by analyzing the relationship between:
- Number of optical photons produced (depends on deposited energy and scintillation yield)
- Number of photons detected at the photodetector

### Changing Crystal Size in `sim.cc`

To study how crystal thickness affects detection efficiency, modify the crystal Z dimension in `sim.cc`:

```cpp
// In sim.cc, around line 26-27:
DetectorConstruction* detectorConstruction = new DetectorConstruction();
detectorConstruction->SetMaterial(9);  // Choose material (0-9)
detectorConstruction->SetCrystalZ(20.0*mm);  // ⬅️ CHANGE THIS VALUE
```

**Recommended efficiency studies:**
| Crystal Z (mm) | Expected Behavior |
|----------------|-------------------|
| 5.0            | Low absorption, many gammas pass through |
| 10.0           | Moderate absorption (default in constructor) |
| 20.0           | Good absorption for most energies |
| 50.0           | Near-complete absorption for 1 MeV gammas |
| 100.0          | Full absorption, longer optical path |

### Efficiency Calculation Method

After running multiple events, calculate efficiency using:

```
Detection Efficiency = (Photons Detected / Photons Produced) × 100%
Gamma Absorption Efficiency = (Events with Scintillation / Total Events) × 100%
```

The simulation outputs photon counts per event, which can be analyzed from the ROOT file.

---

## ⚙️ Configurable Parameters in `sim.cc`

The main file `sim.cc` provides easy access to key simulation parameters:

### 1. Material Selection (Line ~25)
```cpp
detectorConstruction->SetMaterial(9);  // 0-9, see material table below
```

### 2. Crystal Thickness (Line ~26)
```cpp
detectorConstruction->SetCrystalZ(20.0*mm);  // Crystal thickness in Z direction
```

### 3. Visualization Settings (Lines ~46-61)
The visualization commands configure:
- Viewer type (`/vis/open OGL` for OpenGL)
- Viewpoint and lighting
- Trajectory colors by particle type:
  - **Green**: Gamma rays
  - **Red**: Electrons (e-)
  - **Blue**: Positrons (e+)
  - **Yellow**: Optical photons
- Coordinate axes display

### 4. Other Parameters to Modify

| File | Parameter | Location | Description |
|------|-----------|----------|-------------|
| `sim.cc` | Material | Line ~25 | Scintillator type (0-9) |
| `sim.cc` | Crystal Z | Line ~26 | Crystal thickness |
| `src/generator.cc` | Particle Energy | Line ~16 | Gamma energy (default 1.022 MeV) |
| `src/generator.cc` | Particle Type | Line ~13 | Change from "gamma" to other particles |
| `src/generator.cc` | Start Position | Line ~18 | Particle starting point |
| `src/construction.cc` | Crystal X/Y | Line ~257 | Crystal cross-section (default 5mm half-width) |

---

## 🧪 Available Scintillator Materials

The simulation includes **10 pre-configured scintillator materials** with realistic properties:

| ID | Material | Density (g/cm³) | Scint. Yield (ph/MeV) | Decay Time (ns) | Refractive Index |
|----|----------|-----------------|----------------------|-----------------|------------------|
| 0 | LXe (Liquid Xenon) | 3.02 | 42,000 | 2.2 | 1.57 |
| 1 | NaI (pure) | 3.67 | 38,000 | 250 | 1.85 |
| 2 | NaI(Tl) | 3.67 | 38,000 | 250 | 1.85 |
| 3 | CsI (pure) | 4.51 | 2,000 | 16 | 1.79 |
| 4 | CsI(Tl) | 4.51 | 54,000 | 1000 | 1.79 |
| 5 | PbWO₄ | 8.28 | 200 | 10 | 2.20 |
| 6 | BGO | 7.13 | 8,500 | 300 | 2.15 |
| 7 | CeBr₃ | 5.10 | 60,000 | 17 | 1.90 |
| 8 | LYSO | 7.10 | 32,000 | 41 | 1.82 |
| 9 | MyMade (custom) | 3.67 | 100 | 20 | 1.60 |

### Material Selection Considerations

- **High light yield** (CeBr₃, CsI(Tl)): Best energy resolution
- **Fast decay** (PbWO₄, CsI pure, CeBr₃): Best timing resolution
- **High density** (PbWO₄, BGO, LYSO): Best gamma stopping power
- **Low cost** (NaI(Tl)): Common for general spectroscopy

---

## ⚛️ Physics Processes

The simulation includes comprehensive physics modeling:

### Electromagnetic Physics (`G4EmStandardPhysics_option4`)
- Photoelectric effect
- Compton scattering
- Pair production
- Electron/positron interactions
- Multiple scattering
- Bremsstrahlung

### Optical Physics (`G4OpticalPhysics`)
- **Scintillation**: Optical photon emission from energy deposition
- **Optical absorption**: Photon attenuation in materials
- **Refraction/Reflection**: At material boundaries
- **Total internal reflection**: Critical for light collection

### Decay Physics
- `G4DecayPhysics`: Standard particle decays
- `G4RadioactiveDecayPhysics`: For radioactive source simulation

---


### Console Output

During simulation, the console displays:
- Photon hit positions for each detected optical photon
- Detector copy number for hit tracking
- Per-event photon production count
- Total optical photons at end of run

---

## ⚙️ Requirements

- **Geant4** (built with UI and visualization modules)  
- **CMake ≥ 3.2**  
- A **C++ compiler** compatible with your Geant4 installation (e.g., GCC or Clang)  
- **OpenGL** for visualization (use Xvfb or a software renderer for headless servers)
- **ROOT** (optional, for output file analysis)

---


---

## 🛠️ Build (Recommended)

1. **Create and enter a build directory:**
   ```bash
   mkdir -p build && cd build
   cmake ..
   make -j$(nproc)
   ./sim
   ```
   Add macro file as needed for batch execution
   
