#include "event.hh"

EventAction::EventAction(RunAction* runAction)
    : fRunAction(runAction), fPhotonCount(0)
{}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* )
{
    fPhotonCount = 0;
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    auto analysisManager = G4AnalysisManager::Instance();
    G4int eventID = event->GetEventID();

    // Fill into PHOTON ntuple (#1)
    analysisManager->FillNtupleIColumn(1, 0, eventID);     // column 0 in ntuple 1
    analysisManager->FillNtupleIColumn(1, 1, fPhotonCount); // column 1 in ntuple 1
    analysisManager->AddNtupleRow(1);

    // Optional printout
    G4cout << "Event " << eventID 
           << ": " << fPhotonCount 
           << " optical photons produced." << G4endl;
}