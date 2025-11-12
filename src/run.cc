#include "run.hh" // RunAction class header.
#include "photon_counter.hh" // PhotonCounter class header.
#include "G4AnalysisManager.hh" // Geant4 analysis manager.

// (Removed duplicate definition of PhotonCounter::photonCount)

RunAction::RunAction()
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateNtuple("Hits", "Photon Hits"); // Creates ntuple for hits.
    analysisManager->CreateNtupleIColumn("fEvent"); // Event ID column.
    analysisManager->CreateNtupleIColumn("fX"); // X position column.
    analysisManager->CreateNtupleIColumn("fY"); // Y position column.
    analysisManager->CreateNtupleIColumn("fZ"); // Z position column.
    analysisManager->FinishNtuple(0); // Finalizes ntuple 0.

    analysisManager->CreateNtuple("Photons", "Photon production per event"); // Creates ntuple for photons.
    analysisManager->CreateNtupleIColumn("EventID"); // Event ID column.
    analysisManager->CreateNtupleIColumn("NPhotons"); // Photon count column.
    analysisManager->FinishNtuple(1); // Finalizes ntuple 1.
} // Sets up analysis ntuples.

RunAction::~RunAction()
{} // Destructor.

void RunAction::BeginOfRunAction(const G4Run *)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->OpenFile("output.root"); // Opens output file.
    PhotonCounter::Reset(); // Resets photon counter.
}

void RunAction::EndOfRunAction(const G4Run *)
{
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write(); // Writes data to file.
    analysisManager->CloseFile(); // Closes output file.
    G4cout << "Total optical photons created this run: " << PhotonCounter::GetTotal() << G4endl; // Prints total photon count.
}