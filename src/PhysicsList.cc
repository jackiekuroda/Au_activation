#include "PhysicsList.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4NuclideTable.hh"

#include "G4GenericBiasingPhysics.hh"

// particles
#include "G4BaryonConstructor.hh"
#include "G4BosonConstructor.hh"
#include "G4IonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

#include "G4IonPhysicsPHP.hh"
#include "G4HadronPhysicsQGSP_BIC_AllHP.hh"

#include "G4HadronElasticPhysics.hh"
#include "G4HadronInelasticQBBC.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4HadronPhysicsINCLXX.hh"
#include "G4IonElasticPhysics.hh"
#include "G4IonPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
//decay physics
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
//em physics
#include "G4EmExtraPhysics.hh"
#include "G4EmParameters.hh"
#include "G4EmStandardPhysics.hh"



PhysicsList::PhysicsList()
{
  G4int verb = 0;
  SetVerboseLevel(verb);

  // Mandatory for G4NuclideTable
//  G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(0.1 * picosecond);
//  G4NuclideTable::GetInstance()->SetLevelTolerance(1.0 * eV);

  // add new units for cross sections
  new G4UnitDefinition("mm2/g", "mm2/g", "Surface/Mass", mm2 / g);
  new G4UnitDefinition("um2/mg", "um2/mg", "Surface/Mass", um * um / mg);

  // EM physics
  RegisterPhysics(new G4EmStandardPhysics());

  // Radioactive decay
//  RegisterPhysics(new G4DecayPhysics());
//  auto* radDec = new G4RadioactiveDecayPhysics();
//  radDec->SetVerboseLevel(1);
//  RegisterPhysics(radDec);

  RegisterPhysics(new G4HadronPhysicsQGSP_BIC_AllHP(verb));
  RegisterPhysics( new G4IonPhysics(verb));

  // Hadron Elastic scattering
  RegisterPhysics(new G4HadronElasticPhysicsHP(verb));


  // Ion Elastic scattering
  RegisterPhysics(new G4IonElasticPhysics(verb));


  // Gamma-Nuclear Physics
//  G4EmExtraPhysics* gnuc = new G4EmExtraPhysics();
//  gnuc->ElectroNuclear(false);
//  gnuc->MuonNuclear(false);
//  RegisterPhysics(gnuc);

}



void PhysicsList::ConstructProcess()
{
G4VModularPhysicsList::ConstructProcess();


}


void PhysicsList::ConstructParticle()
{
  G4BosonConstructor BosonConstructor;
  BosonConstructor.ConstructParticle();

  G4LeptonConstructor LeptonConstructor;
  LeptonConstructor.ConstructParticle();

  G4MesonConstructor MesonConstructor;
  MesonConstructor.ConstructParticle();

  G4BaryonConstructor BaryonConstructor;
  BaryonConstructor.ConstructParticle();

  G4IonConstructor IonConstructor;
  IonConstructor.ConstructParticle();

  G4ShortLivedConstructor ShortLivedConstructor;
  ShortLivedConstructor.ConstructParticle();
}

void PhysicsList::SetCuts()
{
  SetCutsWithDefault();
  G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(0.001*eV, 100*GeV);
}









