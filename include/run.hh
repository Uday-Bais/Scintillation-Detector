#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4Timer.hh"
#include "globals.hh"

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    ~RunAction();
    
    
    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;
    
    void AddOpticalPhotons(G4int count) { fTotalOpticalPhotons += count; }
    void AddOpticalEnergy(G4double energy) { fTotalOpticalEnergy += energy; }

private:
    G4Timer* fTimer;
    G4int fTotalOpticalPhotons;
    G4double fTotalOpticalEnergy;
};

#endif