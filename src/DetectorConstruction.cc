#include "DetectorConstruction.hh"
#include "SensitiveDetector.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Orb.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GeometryManager.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4RunManager.hh"
#include "G4UserLimits.hh"

#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4Region.hh"
#include "G4RegionStore.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4Torus.hh"
#include "G4Cons.hh"

DetectorConstruction::DetectorConstruction(G4double detectorAngle, G4double targetthic)
    : G4VUserDetectorConstruction(),
      ftargetthic(targetthic),
      physiWorld(nullptr),
      stepLimit(nullptr),
      fCheckOverlaps(true)
{
        DefineMaterials();
}


DetectorConstruction::~DetectorConstruction()
{
        delete stepLimit;
}

G4double DetectorConstruction::Gettargetthic() const
{
        return ftargetthic;
}

void DetectorConstruction::DefineMaterials()
{
        G4NistManager* nist = G4NistManager::Instance();
        Vacuum = nist->FindOrBuildMaterial("G4_Galactic");  // used for world material
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
        G4GeometryManager::GetInstance()->OpenGeometry();
        G4PhysicalVolumeStore::GetInstance()->Clean();
        G4LogicalVolumeStore::GetInstance()->Clean();
        G4SolidStore::GetInstance()->Clean();

        // Construct world
        G4double worldSize = 10.0 * m;
        G4Box* solidWorld = new G4Box("World", worldSize, worldSize, worldSize);
        G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, Vacuum, "LogicWorld");
        logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());

        physiWorld = new G4PVPlacement(nullptr, G4ThreeVector(), logicWorld, "PhysiWorld", nullptr, false, 0, fCheckOverlaps);

        // Add detector components
        ConstructNeutronDetector(logicWorld);

        //add the source
        ConstructSource(logicWorld);


        return physiWorld;
}

//creating the source
void  DetectorConstruction::ConstructSource(G4LogicalVolume* motherLogicalVolume)
{
	G4NistManager* nist = G4NistManager::Instance();
        G4Isotope* Li7 = new G4Isotope("Li7", 3, 7, 7.016*g/mole);
        G4Element * elLi7 = new G4Element("Lith7", "Li7", 1);
        elLi7->AddIsotope(Li7, 100.*perCent);

        G4Material* Lithium  = new G4Material("Li7Material", 0.534*g/cm3, 1);
        Lithium ->AddElement(elLi7, 1);

        G4double  sphi =   0.*deg;
        G4double  dphi = 360.*deg;

        G4VSolid * sourceShape = new G4Tubs("sourceShape", 0.*cm, 1*mm , ftargetthic , sphi, dphi);
        G4LogicalVolume * logSource= new G4LogicalVolume(sourceShape,Lithium,"logsource",0,0,0);

        new G4PVPlacement(0,G4ThreeVector(0.,0., 0. ),logSource,"physsource",motherLogicalVolume,false,0,fCheckOverlaps);

        G4VisAttributes* visAttSource = new G4VisAttributes(G4Colour(0,0.2,1.0));
        visAttSource->G4VisAttributes::SetForceSolid(true);
        logSource->SetVisAttributes(visAttSource);
	flogSource = logSource;
}


//creating the detector
void   DetectorConstruction::ConstructNeutronDetector(G4LogicalVolume* motherLogicalVolume)
{
}










