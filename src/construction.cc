// filepath: /home/uday/Desktop/Softwares/my_file_geant4/try_1/src/construction.cc
#include "construction.hh"
DetectorConstruction::DetectorConstruction() : material(2), crystalZ(10.0*mm) {} // Default to NaI(Tl) and 10mm z
DetectorConstruction::~DetectorConstruction() {}

G4VPhysicalVolume* DetectorConstruction::Construct()
{//-----------------------------------------------------------------------
    //
    //G4double energy[2] = {7*eV, 7.07*eV};
    G4double energy[3] = {7*eV, 7.04*eV, 7.14*eV};
    
    //-----------------------------------------------------------------------
    // Materials
    G4NistManager* nist = G4NistManager::Instance();

    // all elements for the materials
    G4Element *Na = nist->FindOrBuildElement("Na");
    G4Element *I = nist->FindOrBuildElement("I");
    G4Element *Tl = nist->FindOrBuildElement("Tl");
    G4Element *Cs = nist->FindOrBuildElement("Cs");
    G4Element *Pb = nist->FindOrBuildElement("Pb");
    G4Element *W = nist->FindOrBuildElement("W");
    G4Element *O = nist->FindOrBuildElement("O");
    G4Element *Ce = nist->FindOrBuildElement("Ce");
    G4Element *Br = nist->FindOrBuildElement("Br");
    G4Element *Lu = nist->FindOrBuildElement("Lu");
    G4Element *Y = nist->FindOrBuildElement("Y");
    G4Element *Si = nist->FindOrBuildElement("Si");

    // ========== Liquid Xenon (LXe) ==========
    G4Material* LXe = nist->FindOrBuildMaterial("G4_lXe");
    G4double rindexLXe[3] = {1.57, 1.57, 1.57};
    G4double absLengthLXe[3] = {100.*cm, 100.*cm, 100.*cm};
    G4double scintLXe[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptLXe = new G4MaterialPropertiesTable();
    mptLXe->AddProperty("RINDEX", energy, rindexLXe, 3);
    mptLXe->AddProperty("ABSLENGTH", energy, absLengthLXe, 3);
    mptLXe->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintLXe, 3);
    mptLXe->AddConstProperty("SCINTILLATIONYIELD", 42000./MeV); // DEFAULT: 42,000 photons/MeV
    mptLXe->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptLXe->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 2.2*ns);
    mptLXe->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    LXe->SetMaterialPropertiesTable(mptLXe);

    // ========== Pure Sodium Iodide (NaI - undoped) ==========
    G4Material* NaI_pure = new G4Material("NaI_pure", 3.67*g/cm3, 2);
    NaI_pure->AddElement(Na, 1);
    NaI_pure->AddElement(I, 1);
    
    G4double rindexNaI_pure[3] = {1.85, 1.85, 1.85};
    G4double absLengthNaI_pure[3] = {50.*cm, 50.*cm, 50.*cm};
    G4double scintNaI_pure[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptNaI_pure = new G4MaterialPropertiesTable();
    mptNaI_pure->AddProperty("RINDEX", energy, rindexNaI_pure, 3);
    mptNaI_pure->AddProperty("ABSLENGTH", energy, absLengthNaI_pure, 3);
    mptNaI_pure->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintNaI_pure, 3);
    mptNaI_pure->AddConstProperty("SCINTILLATIONYIELD", 38000./MeV); // DEFAULT
    mptNaI_pure->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptNaI_pure->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250.*ns);
    mptNaI_pure->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    NaI_pure->SetMaterialPropertiesTable(mptNaI_pure);

    // ========== Sodium Iodide with Thallium Doping NaI(Tl) ==========
    G4Material* NaITl = new G4Material("NaI(Tl)", 3.67*g/cm3, 3);
    NaITl->AddElement(Na, 999);      // 999 parts Na
    NaITl->AddElement(I, 999);       // 999 parts I
    NaITl->AddElement(Tl, 2);        // 2 parts Tl (~0.1% doping)
    
    G4double rindexNaITl[3] = {1.85, 1.85, 1.85};
    G4double absLengthNaITl[3] = {50.*cm, 50.*cm, 50.*cm};
    G4double scintNaITl[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptNaITl = new G4MaterialPropertiesTable();
    mptNaITl->AddProperty("RINDEX", energy, rindexNaITl, 3);
    mptNaITl->AddProperty("ABSLENGTH", energy, absLengthNaITl, 3);
    mptNaITl->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintNaITl, 3);
    mptNaITl->AddConstProperty("SCINTILLATIONYIELD", 38000./MeV); // DEFAULT
    mptNaITl->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptNaITl->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 250.*ns);
    mptNaITl->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    NaITl->SetMaterialPropertiesTable(mptNaITl);

    // ========== Pure Cesium Iodide (CsI - undoped) ==========
    G4Material* CsI_pure = new G4Material("CsI_pure", 4.51*g/cm3, 2);
    CsI_pure->AddElement(Cs, 1);
    CsI_pure->AddElement(I, 1);
    
    G4double rindexCsI_pure[3] = {1.79, 1.79, 1.79};
    G4double absLengthCsI_pure[3] = {50.*cm, 50.*cm, 50.*cm};
    G4double scintCsI_pure[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptCsI_pure = new G4MaterialPropertiesTable();
    mptCsI_pure->AddProperty("RINDEX", energy, rindexCsI_pure, 3);
    mptCsI_pure->AddProperty("ABSLENGTH", energy, absLengthCsI_pure, 3);
    mptCsI_pure->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintCsI_pure, 3);
    mptCsI_pure->AddConstProperty("SCINTILLATIONYIELD", 2000./MeV); // DEFAULT (pure CsI has low yield)
    mptCsI_pure->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptCsI_pure->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 16.*ns);
    mptCsI_pure->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    CsI_pure->SetMaterialPropertiesTable(mptCsI_pure);

    // ========== Cesium Iodide with Thallium Doping CsI(Tl) ==========
    G4Material* CsITl = new G4Material("CsI(Tl)", 4.51*g/cm3, 3);
    CsITl->AddElement(Cs, 999);      // 999 parts Cs
    CsITl->AddElement(I, 999);       // 999 parts I
    CsITl->AddElement(Tl, 2);        // 2 parts Tl (~0.1% doping)
    
    G4double rindexCsITl[3] = {1.79, 1.79, 1.79};
    G4double absLengthCsITl[3] = {50.*cm, 50.*cm, 50.*cm};
    G4double scintCsITl[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptCsITl = new G4MaterialPropertiesTable();
    mptCsITl->AddProperty("RINDEX", energy, rindexCsITl, 3);
    mptCsITl->AddProperty("ABSLENGTH", energy, absLengthCsITl, 3);
    mptCsITl->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintCsITl, 3);
    mptCsITl->AddConstProperty("SCINTILLATIONYIELD", 54000./MeV); // DEFAULT (Tl-doped has high yield)
    mptCsITl->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptCsITl->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 1000.*ns);
    mptCsITl->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    CsITl->SetMaterialPropertiesTable(mptCsITl);

    // ========== Lead Tungstate (PbWO4) ==========
    G4Material* PbWO4 = new G4Material("PbWO4", 8.28*g/cm3, 3);
    PbWO4->AddElement(Pb, 1);
    PbWO4->AddElement(W, 1);
    PbWO4->AddElement(O, 4);
    
    G4double rindexPbWO4[3] = {2.20, 2.20, 2.20};
    G4double absLengthPbWO4[3] = {20.*cm, 20.*cm, 20.*cm};
    G4double scintPbWO4[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptPbWO4 = new G4MaterialPropertiesTable();
    mptPbWO4->AddProperty("RINDEX", energy, rindexPbWO4, 3);
    mptPbWO4->AddProperty("ABSLENGTH", energy, absLengthPbWO4, 3);
    mptPbWO4->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintPbWO4, 3);
    mptPbWO4->AddConstProperty("SCINTILLATIONYIELD", 200./MeV); // DEFAULT: 200 photons/MeV (low but fast)
    mptPbWO4->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptPbWO4->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 10.*ns); // Very fast decay
    mptPbWO4->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    PbWO4->SetMaterialPropertiesTable(mptPbWO4);

    // ========== Bismuth Germanate (BGO) - no doping ==========
    G4Material* BGO = nist->FindOrBuildMaterial("G4_BGO");
    G4double rindexBGO[3] = {2.15, 2.15, 2.15};
    G4double absLengthBGO[3] = {40.*cm, 40.*cm, 40.*cm};
    G4double scintBGO[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptBGO = new G4MaterialPropertiesTable();
    mptBGO->AddProperty("RINDEX", energy, rindexBGO, 3);
    mptBGO->AddProperty("ABSLENGTH", energy, absLengthBGO, 3);
    mptBGO->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintBGO, 3);
    mptBGO->AddConstProperty("SCINTILLATIONYIELD", 8500./MeV); // DEFAULT: 8,500 photons/MeV
    mptBGO->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptBGO->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 300.*ns);
    mptBGO->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    BGO->SetMaterialPropertiesTable(mptBGO);

    // ========== Cerium Bromide (CeBr3) - Ce is the activator ==========
    G4Material* CeBr3 = new G4Material("CeBr3", 5.1*g/cm3, 2);
    CeBr3->AddElement(Ce, 1);
    CeBr3->AddElement(Br, 3);
    G4double rindexCeBr3[3] = {1.9, 1.9, 1.9};
    G4double absLengthCeBr3[3] = {50.*cm, 50.*cm, 50.*cm};
    G4double scintCeBr3[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptCeBr3 = new G4MaterialPropertiesTable();
    mptCeBr3->AddProperty("RINDEX", energy, rindexCeBr3, 3);
    mptCeBr3->AddProperty("ABSLENGTH", energy, absLengthCeBr3, 3);
    mptCeBr3->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintCeBr3, 3);
    mptCeBr3->AddConstProperty("SCINTILLATIONYIELD", 60000./MeV); // DEFAULT: 60,000 photons/MeV
    mptCeBr3->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptCeBr3->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 17.*ns);
    mptCeBr3->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    CeBr3->SetMaterialPropertiesTable(mptCeBr3);

    // ========== LYSO (Lu1.8Y0.2SiO5:Ce) ==========
    G4Material* LYSO = new G4Material("LYSO", 7.1*g/cm3, 4);
    LYSO->AddElement(Lu, 9);
    LYSO->AddElement(Y, 1);
    LYSO->AddElement(Si, 5);
    LYSO->AddElement(O, 25);
    G4double rindexLYSO[3] = {1.82, 1.82, 1.82};
    G4double absLengthLYSO[3] = {40.*cm, 40.*cm, 40.*cm};
    G4double scintLYSO[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptLYSO = new G4MaterialPropertiesTable();
    mptLYSO->AddProperty("RINDEX", energy, rindexLYSO, 3);
    mptLYSO->AddProperty("ABSLENGTH", energy, absLengthLYSO, 3);
    mptLYSO->AddProperty("SCINTILLATIONCOMPONENT1", energy, scintLYSO, 3);
    mptLYSO->AddConstProperty("SCINTILLATIONYIELD", 32000./MeV); // DEFAULT: 32,000 photons/MeV
    mptLYSO->AddConstProperty("RESOLUTIONSCALE", 1.0);
    mptLYSO->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 41.*ns);
    mptLYSO->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
    LYSO->SetMaterialPropertiesTable(mptLYSO);

    // ========== MyMade ==========
G4double z, a, density;
//G4double rindexWorld_test[2]={1. ,1. };
// std::vector<G4double> rindexWorld_test = {1. ,1. };
// std::vector<G4double> energy_test = {1*eV, 7.07*eV};

// Define MyMade (NaI) material
density = 3.67*g/cm3;
G4Material* MyMade = new G4Material("MyMade", density, 2);
MyMade->AddElement(Na, 1);
MyMade->AddElement(I, 1);

// optical properties for MyMade
std::vector<G4double> mymade_Energy = {7.0*eV, 7.04*eV, 7.14*eV};
//std::vector<G4double> mymade_Energy = {1.0*eV, 3.07*eV, 7.14*eV};
std::vector<G4double> mymade_SCINT  = {0.1, 1.0, 0.1};      // Custom emission spectrum
std::vector<G4double> mymade_RIND   = {1.60, 1.60, 1.60};   // Custom refractive index
std::vector<G4double> mymade_ABSL   = {100.*cm, 100.*cm, 100.*cm}; // Custom absorption length

G4MaterialPropertiesTable* mymade_mt = new G4MaterialPropertiesTable();
mymade_mt->AddProperty("SCINTILLATIONCOMPONENT1", mymade_Energy, mymade_SCINT);
mymade_mt->AddProperty("SCINTILLATIONCOMPONENT2", mymade_Energy, mymade_SCINT);
mymade_mt->AddProperty("RINDEX",mymade_Energy, mymade_RIND);
// mymade_mt->AddProperty("RINDEX",        energy_test, rindexWorld_test);
mymade_mt->AddProperty("ABSLENGTH",     mymade_Energy, mymade_ABSL);
mymade_mt->AddConstProperty("SCINTILLATIONYIELD", 100./MeV);
mymade_mt->AddConstProperty("RESOLUTIONSCALE", 1.0);
mymade_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT1", 20.*ns);
mymade_mt->AddConstProperty("SCINTILLATIONTIMECONSTANT2", 45.*ns);
mymade_mt->AddConstProperty("SCINTILLATIONYIELD1", 1.0);
mymade_mt->AddConstProperty("SCINTILLATIONYIELD2", 0.0);
MyMade->SetMaterialPropertiesTable(mymade_mt);

    //------------------------------------------------------------------------------

    //selecting material 
    G4Material* detectorMaterial = NaITl; // Default
    switch(material) {
        case 0: detectorMaterial = LXe; break;
        case 1: detectorMaterial = NaI_pure; break;
        case 2: detectorMaterial = NaITl; break;
        case 3: detectorMaterial = CsI_pure; break;
        case 4: detectorMaterial = CsITl; break;
        case 5: detectorMaterial = PbWO4; break;
        case 6: detectorMaterial = BGO; break;
        case 7: detectorMaterial = CeBr3; break;
        case 8: detectorMaterial = LYSO; break;
        case 9: detectorMaterial = MyMade; break;
        default: detectorMaterial = NaITl; break;
    }


    //=====================================================================================================================================================
    // World
    // Define world material and its optical properties BEFORE use
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4double rindexWorld[3] = {1.0, 1.0, 1.0};
    G4MaterialPropertiesTable *mptWorld = new G4MaterialPropertiesTable();
    mptWorld->AddProperty("RINDEX", energy, rindexWorld, 3);
    worldMat->SetMaterialPropertiesTable(mptWorld);
    //------------------------------------------------------------------------------
    
    G4Box* solidWorld = new G4Box("solidWorld", 0.1*m, 0.1*m, 0.1*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "physWorld", 0, false, 0, true);
    //=====================================================================================================================================================
    // scintillation crystal
    // Crystal dimensions: 10mm x 10mm x crystalZ
    G4Box *solidScint = new G4Box("solidScint", 5.0*mm, 5.0*mm, crystalZ/2.0);
    G4LogicalVolume *logicScint = new G4LogicalVolume(solidScint, detectorMaterial, "logicScint");
    
    // Set crystal color to light blue
    G4VisAttributes* crystalVisAtt = new G4VisAttributes(G4Colour(0.5, 0.7, 1.0)); // Light blue (RGB)
    logicScint->SetVisAttributes(crystalVisAtt);
    
    // Position crystal at z = 0 (center of world)
    G4double crystalPosZ = 0.0*m;
    G4VPhysicalVolume *physScint = new G4PVPlacement(0, G4ThreeVector(0., 0., crystalPosZ), logicScint, "physScint", logicWorld, false, 0, true);

    //=====================================================================================================================================================
    // Detector
    // Detector positioned 0.1mm behind the crystal's back face
    G4Material* detMat = nist->FindOrBuildMaterial("G4_Si");
    G4Box *solidDetector = new G4Box("solidDetector", 5.0*mm, 5.0*mm, 0.5*mm); // 10mm x 10mm x 1mm

    // Set detector material optical properties to match the chosen crystal material
    detMat->SetMaterialPropertiesTable(detectorMaterial->GetMaterialPropertiesTable());

    logicDetector = new G4LogicalVolume(solidDetector, detMat, "logicDetector");
    
    
    // Set detector color to grey
    G4VisAttributes* detectorVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5)); // Grey (RGB)
    logicDetector->SetVisAttributes(detectorVisAtt);
    
    // Position: crystal back face is at (crystalPosZ - crystalZ/2), detector starts directly behind that (no gap)
    G4double detectorPosZ = crystalPosZ - crystalZ/2.0 - 0.5*mm;
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0., 0., detectorPosZ), logicDetector, "physDetector", logicWorld, false, 0, true);

    
    //===========================================================================================================================================================

// Reflective coating around the crystal (except the detector face)
// -----------------------------------------------------------------------------

// G4double skinThick = 0.1 * mm;  // small gap to avoid overlaps

// // --- Reflectivity arrays ---
// G4double reflVals[3] = {0.98, 0.98, 0.98};   // reflective faces (98%)
// G4double zeroRefl[3] = {0.0, 0.0, 0.0};      // non-reflective (0%)

// // --- Reflective optical surface (simulate metalized reflector) ---
// G4OpticalSurface* opReflect = new G4OpticalSurface("CrystalReflectiveSurface");
// opReflect->SetType(dielectric_metal);
// opReflect->SetModel(unified);
// opReflect->SetFinish(polished);

// G4MaterialPropertiesTable* mptReflect = new G4MaterialPropertiesTable();
// mptReflect->AddProperty("REFLECTIVITY", energy, reflVals, 3);
// opReflect->SetMaterialPropertiesTable(mptReflect);

// // --- Absorbing (black) surface ---
// G4OpticalSurface* opAbsorb = new G4OpticalSurface("CrystalAbsorbingSurface");
// opAbsorb->SetType(dielectric_metal);
// opAbsorb->SetModel(unified);
// opAbsorb->SetFinish(polished);

// G4MaterialPropertiesTable* mptAbs = new G4MaterialPropertiesTable();
// mptAbs->AddProperty("REFLECTIVITY", energy, zeroRefl, 3);
// opAbsorb->SetMaterialPropertiesTable(mptAbs);

// // --- Create thin “skin” volumes for each face of the crystal ---
// G4double crystalX = 10.0 * mm;
// G4double crystalY = 10.0 * mm;
// G4double crystalZ = 20.0 * mm;


// // // FRONT (detector side, non-reflective)
// // G4Box* solidFrontSkin = new G4Box("solidFrontSkin", crystalX/2, crystalY/2, skinThick/2);
// // auto logicFrontSkin = new G4LogicalVolume(solidFrontSkin, worldMat, "logicFrontSkin");
// // G4ThreeVector posFront(0., 0., crystalPosZ + crystalZ/2 + skinThick/2);
// // auto physFrontSkin = new G4PVPlacement(0, posFront, logicFrontSkin, "physFrontSkin", logicWorld, false, 0, true);

// // LEFT (-X)
// G4Box* solidLeftSkin = new G4Box("solidLeftSkin", skinThick/2, crystalY/2, crystalZ/2);
// auto logicLeftSkin = new G4LogicalVolume(solidLeftSkin, worldMat, "logicLeftSkin");
// G4ThreeVector posLeft(-(crystalX/2 + skinThick/2), 0., crystalPosZ);
// auto physLeftSkin = new G4PVPlacement(0, posLeft, logicLeftSkin, "physLeftSkin", logicWorld, false, 0, true);

// // RIGHT (+X)
// G4Box* solidRightSkin = new G4Box("solidRightSkin", skinThick/2, crystalY/2, crystalZ/2);
// auto logicRightSkin = new G4LogicalVolume(solidRightSkin, worldMat, "logicRightSkin");
// G4ThreeVector posRight((crystalX/2 + skinThick/2), 0., crystalPosZ);
// auto physRightSkin = new G4PVPlacement(0, posRight, logicRightSkin, "physRightSkin", logicWorld, false, 0, true);

// // TOP (+Y)
// G4Box* solidTopSkin = new G4Box("solidTopSkin", crystalX/2, skinThick/2, crystalZ/2);
// auto logicTopSkin = new G4LogicalVolume(solidTopSkin, worldMat, "logicTopSkin");
// G4ThreeVector posTop(0., (crystalY/2 + skinThick/2), crystalPosZ);
// auto physTopSkin = new G4PVPlacement(0, posTop, logicTopSkin, "physTopSkin", logicWorld, false, 0, true);

// // BOTTOM (-Y)
// G4Box* solidBottomSkin = new G4Box("solidBottomSkin", crystalX/2, skinThick/2, crystalZ/2);
// auto logicBottomSkin = new G4LogicalVolume(solidBottomSkin, worldMat, "logicBottomSkin");
// G4ThreeVector posBottom(0., -(crystalY/2 + skinThick/2), crystalPosZ);
// auto physBottomSkin = new G4PVPlacement(0, posBottom, logicBottomSkin, "physBottomSkin", logicWorld, false, 0, true);

// // --- Visualization attributes ---
// auto skinVisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // red
// logicFrontSkin->SetVisAttributes(skinVisAtt);
// logicLeftSkin->SetVisAttributes(skinVisAtt);
// logicRightSkin->SetVisAttributes(skinVisAtt);
// logicTopSkin->SetVisAttributes(skinVisAtt);
// logicBottomSkin->SetVisAttributes(skinVisAtt);

// // Optionally hide them for clean visualization
// // logicFrontSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// // logicLeftSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// // logicRightSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// // logicTopSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// // logicBottomSkin->SetVisAttributes(G4VisAttributes::GetInvisible());

// // --- Assign border surfaces between crystal and skins ---
// // new G4LogicalBorderSurface("Surface_Front",  physScint, physFrontSkin,  opAbsorb);
// new G4LogicalBorderSurface("Surface_Left1",  physScint, physLeftSkin,   opReflect);
// new G4LogicalBorderSurface("Surface_Left2",  physLeftSkin, physScint,   opReflect);
// new G4LogicalBorderSurface("Surface_Right1", physScint, physRightSkin,  opReflect);
// new G4LogicalBorderSurface("Surface_Right2", physRightSkin, physScint,  opReflect);
// new G4LogicalBorderSurface("Surface_Top1",   physScint, physTopSkin,    opReflect);
// new G4LogicalBorderSurface("Surface_Top2",   physTopSkin, physScint,    opReflect);
// new G4LogicalBorderSurface("Surface_Bot1",   physScint, physBottomSkin, opReflect);
// new G4LogicalBorderSurface("Surface_Bot2",   physBottomSkin, physScint, opReflect);

//==========================================================================================================
// -----------------------------------------------------------------------------
// Reflective coating around the crystal (front + sides, NOT on detector side)
// -----------------------------------------------------------------------------

G4double skinThick = 0.5 * mm;  // small thickness to avoid overlaps

// --- Reflectivity arrays ---
G4double reflVals[3] = {0.98, 0.98, 0.98};  // reflective faces (98%)
G4double zeroRefl[3] = {0.0, 0.0, 0.0};     // non-reflective

// --- Reflective (metal-like) optical surface ---
auto opReflect = new G4OpticalSurface("CrystalReflectiveSurface");
opReflect->SetType(dielectric_metal);
opReflect->SetModel(unified);
opReflect->SetFinish(polished);

auto mptReflect = new G4MaterialPropertiesTable();
mptReflect->AddProperty("REFLECTIVITY", energy, reflVals, 3);
opReflect->SetMaterialPropertiesTable(mptReflect);

// --- Basic geometry parameters ---
G4double crystalX = 10.0 * mm;
G4double crystalY = 10.0 * mm;
G4double crystalZ = 20.0 * mm;

// --- FRONT FACE (+Z): reflective (gamma enters here) ---
auto solidFrontSkin = new G4Box("solidFrontSkin", crystalX/2, crystalY/2, skinThick/2);
auto logicFrontSkin = new G4LogicalVolume(solidFrontSkin, worldMat, "logicFrontSkin");
G4ThreeVector posFront(0., 0., crystalPosZ + crystalZ/2 + skinThick/2);
auto physFrontSkin = new G4PVPlacement(0, posFront, logicFrontSkin, "physFrontSkin", logicWorld, false, 0, true);

// --- LEFT (-X) ---
auto solidLeftSkin = new G4Box("solidLeftSkin", skinThick/2, crystalY/2, crystalZ/2);
auto logicLeftSkin = new G4LogicalVolume(solidLeftSkin, worldMat, "logicLeftSkin");
G4ThreeVector posLeft(-(crystalX/2 + skinThick/2), 0., crystalPosZ);
auto physLeftSkin = new G4PVPlacement(0, posLeft, logicLeftSkin, "physLeftSkin", logicWorld, false, 0, true);

// --- RIGHT (+X) ---
auto solidRightSkin = new G4Box("solidRightSkin", skinThick/2, crystalY/2, crystalZ/2);
auto logicRightSkin = new G4LogicalVolume(solidRightSkin, worldMat, "logicRightSkin");
G4ThreeVector posRight((crystalX/2 + skinThick/2), 0., crystalPosZ);
auto physRightSkin = new G4PVPlacement(0, posRight, logicRightSkin, "physRightSkin", logicWorld, false, 0, true);

// --- TOP (+Y) ---
auto solidTopSkin = new G4Box("solidTopSkin", crystalX/2, skinThick/2, crystalZ/2);
auto logicTopSkin = new G4LogicalVolume(solidTopSkin, worldMat, "logicTopSkin");
G4ThreeVector posTop(0., (crystalY/2 + skinThick/2), crystalPosZ);
auto physTopSkin = new G4PVPlacement(0, posTop, logicTopSkin, "physTopSkin", logicWorld, false, 0, true);

// --- BOTTOM (-Y) ---
auto solidBottomSkin = new G4Box("solidBottomSkin", crystalX/2, skinThick/2, crystalZ/2);
auto logicBottomSkin = new G4LogicalVolume(solidBottomSkin, worldMat, "logicBottomSkin");
G4ThreeVector posBottom(0., -(crystalY/2 + skinThick/2), crystalPosZ);
auto physBottomSkin = new G4PVPlacement(0, posBottom, logicBottomSkin, "physBottomSkin", logicWorld, false, 0, true);

// --- Visualization (optional) ---
auto skinVis = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // red
logicFrontSkin->SetVisAttributes(skinVis);
logicLeftSkin->SetVisAttributes(skinVis);
logicRightSkin->SetVisAttributes(skinVis);
logicTopSkin->SetVisAttributes(skinVis);
logicBottomSkin->SetVisAttributes(skinVis);

// Optionally hide skins in the viewer
// logicFrontSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// logicLeftSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// logicRightSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// logicTopSkin->SetVisAttributes(G4VisAttributes::GetInvisible());
// logicBottomSkin->SetVisAttributes(G4VisAttributes::GetInvisible());

// --- Assign border surfaces ---
// FRONT (+Z): reflective (gamma entry side)
new G4LogicalBorderSurface("Surface_Front", physScint, physFrontSkin, opReflect);

// SIDES (±X, ±Y): reflective
new G4LogicalBorderSurface("Surface_Left1",  physScint, physLeftSkin,   opReflect);
new G4LogicalBorderSurface("Surface_Left2",  physLeftSkin, physScint,   opReflect);
new G4LogicalBorderSurface("Surface_Right1", physScint, physRightSkin,  opReflect);
new G4LogicalBorderSurface("Surface_Right2", physRightSkin, physScint,  opReflect);
new G4LogicalBorderSurface("Surface_Top1",   physScint, physTopSkin,    opReflect);
new G4LogicalBorderSurface("Surface_Top2",   physTopSkin, physScint,    opReflect);
new G4LogicalBorderSurface("Surface_Bot1",   physScint, physBottomSkin, opReflect);
new G4LogicalBorderSurface("Surface_Bot2",   physBottomSkin, physScint, opReflect);

// --- BACK FACE (-Z): no coating, crystal touches detector directly ---





//----------------------------------------------------------------------------
    return physWorld;
}

void DetectorConstruction::ConstructSDandField(){
    SensitiveDetector* sensitiveDetector = new SensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensitiveDetector);
    
    // Print setup information
    //PrintSetup();
}