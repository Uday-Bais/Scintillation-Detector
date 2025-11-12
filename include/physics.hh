#ifndef PHYSICS_HH
#define PHYSICS_HH


#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4EmExtraPhysics.hh"



class Physics : public G4VModularPhysicsList {
public:
    Physics();
    ~Physics() override;
private:
    G4OpticalPhysics* fOpticalPhysics;
};

#endif
