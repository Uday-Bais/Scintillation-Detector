#include "physics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4LossTableManager.hh"
#include "G4SystemOfUnits.hh"

Physics::Physics() : fOpticalPhysics(nullptr) {
    // ==============================
    // 1. Core EM physics (for gammas)
    // ==============================
    RegisterPhysics(new G4EmStandardPhysics_option4());

    // ==============================
    // 2. Optical physics (for scintillation + transport)
    // ==============================
    fOpticalPhysics = new G4OpticalPhysics();
    RegisterPhysics(fOpticalPhysics);

    // ==============================
    // 3. Decay physics (optional, for positron annihilation or isotope sources)
    // ==============================
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());

    // ==============================
    // 4. Optional fine-tuning
    // ==============================
    // SetDefaultCutValue(0.1 * mm);
    // SetVerboseLevel(1);
}

Physics::~Physics() = default;
