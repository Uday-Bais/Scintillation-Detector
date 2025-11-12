#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "construction.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4Element.hh"
#include "G4MaterialPropertiesTable.hh"
#include "detector.hh"
#include <G4OpticalSurface.hh>
#include <G4LogicalBorderSurface.hh>
#include <G4LogicalSkinSurface.hh>  

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    void SetMaterial(G4int mat) { material = mat; }
    void SetCrystalZ(G4double z) { crystalZ = z; }
    void PrintSetup();
protected:
    virtual void ConstructSDandField() override;

private:
    G4LogicalVolume *logicDetector;
    G4int material;
    G4double crystalZ;
};


#endif