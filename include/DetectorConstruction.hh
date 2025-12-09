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
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

    // Material and geometry construction helpers
    void SetSource(G4bool value);
    void UpdateGeometry();

    G4double Gettargetthic() const;

private:

    void DefineMaterials();
    G4VPhysicalVolume* ConstructWorld();

    void ConstructSource(G4LogicalVolume* motherLogicalVolume);

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

