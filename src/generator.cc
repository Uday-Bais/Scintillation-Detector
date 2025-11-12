#include "generator.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

PrimaryGenerator::PrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1); // Single particle per event

    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma"); // Photon

    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(1.022*MeV); // 1.022 MeV photon
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., -1.)); // Along -z axis (toward detector)
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., 20*mm));
}

PrimaryGenerator::~PrimaryGenerator()
{
    delete fParticleGun;
}

void PrimaryGenerator::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}
