#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4UserLimits.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

class DetectorMessenger;
class G4GlobalMagFieldMessenger;

class G4Box;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4VPVParameterisation;
class G4UserLimits;

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction(G4double targetthic);
    virtual ~DetectorConstruction();

//    G4LogicalVolume* GetLogicDetector() const { return fLogActiveDetector; }

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();


    // Material and geometry construction helpers
    void SetSource(G4bool value);
    void UpdateGeometry();
    void SetDetectorLength(G4double length);
    void SetDetectorRadius(G4double thickness);
    void SetDetectorMaterial(const G4String& name);

    G4double GetDetectorLength() const;
    G4double GetDetectorRadius() const;
    G4Material* GetDetectorMaterial() const;
    G4double Gettargetthic() const;

private:

    void DefineMaterials();
    G4VPhysicalVolume* ConstructWorld();

    void ConstructNeutronDetector(G4LogicalVolume* );
    void ConstructSource(G4LogicalVolume* motherLogicalVolume);
    G4double detectorLength = 5.08 * cm;
    G4double detectorRadius = 5.08/2 * cm;
    G4Material* detectorMaterial = nullptr;
    G4Material* sourceMaterial = nullptr;
    G4LogicalVolume* flogSource = nullptr;

    G4double fdetectorAngle;
    G4double ftargetthic;
    // Core geometry
    G4VPhysicalVolume* physiWorld;

    //flags
    G4bool fCheckOverlaps;


    // Materials
    G4Material* Vacuum;

    // Optional
    G4UserLimits* stepLimit;

};




#endif

