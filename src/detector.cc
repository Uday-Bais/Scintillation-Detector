#include "detector.hh"

SensitiveDetector::SensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{

}

SensitiveDetector::~SensitiveDetector()
{
}

G4bool SensitiveDetector::ProcessHits(G4Step* aStep, G4TouchableHistory* ROhist)
{
    if (!aStep) return false;

    G4Track* aTrack = aStep->GetTrack();
    aTrack->SetTrackStatus(fStopAndKill);
    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint* postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    G4cout << "Photon hit at: " << posPhoton.x()/m << " m, "
           << posPhoton.y()/m << " m, "
           << posPhoton.z()/m << " m" << G4endl;

    auto analysisManager = G4AnalysisManager::Instance();
    G4int eventID = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    analysisManager->FillNtupleIColumn(0, eventID);
    analysisManager->FillNtupleIColumn(1, posPhoton.x()/mm);
    analysisManager->FillNtupleIColumn(2, posPhoton.y()/mm);
    analysisManager->FillNtupleIColumn(3, posPhoton.z()/mm);
    analysisManager->AddNtupleRow();



    const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
    G4int copyNo = touchable->GetCopyNumber();
    G4cout << "Hit in detector copy number: " << copyNo << G4endl;
    G4VPhysicalVolume* physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout << "Detector position: " << posDetector << G4endl;
    return true;
}