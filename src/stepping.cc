#include "stepping.hh" // SteppingAction class header.
#include "event.hh" // EventAction class header.
#include "G4Step.hh" // Geant4 step class.
#include "G4Track.hh" // Geant4 track class.
#include "G4OpticalPhoton.hh" // Geant4 optical photon class.
#include "photon_counter.hh"   // PhotonCounter class header.

SteppingAction::SteppingAction(EventAction* eventAction)
    : fEventAction(eventAction)
{
    // ...any initialization...
} // Constructor initializes event action pointer.

SteppingAction::~SteppingAction()
{
    // ...any cleanup...
} // Destructor.

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    const G4Track* track = step->GetTrack();

    // Check for newly created optical photons
    if (track->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()
        && track->GetCurrentStepNumber() == 1)
    {
        // increment global run counter
        PhotonCounter::Inc();

        // update per-event counter (optional, kept for event-level bookkeeping)
        fEventAction->AddPhoton();
    }
} // Increments counters for new optical photons.