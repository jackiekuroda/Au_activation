#include <iostream>
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "G4ParticleHPManager.hh"
#include "G4RunManager.hh"
#include "G4RunManagerFactory.hh"
#include "G4SteppingVerbose.hh"
#include "G4Types.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "Randomize.hh"

#include "G4IonTable.hh"
#include "G4NuclideTable.hh"


int main(int argc, char** argv)
{
    G4double targetthic = 0;

    G4UIExecutive* ui = 0;

    if (argc == 1)
    {
	ui = new G4UIExecutive(argc, argv, "csh");
	targetthic = 1 *um;
    }

    else if (argc >= 4)
    {
	targetthic = std::stod(argv[3])* um;

    G4cout << "Target Thickness = " << targetthic / um << " um" << G4endl;

    }

    else
    {
        G4cerr << "Usage: " << argv[0] << "<Target thickness in um>" << G4endl;
        return 1;
    }

  // detect interactive mode (if no arguments) and define UI session
  CLHEP::HepRandom::setTheSeed(time(NULL));

  // use G4SteppingVerboseWithUnits
  G4int precision = 4;
  G4SteppingVerbose::UseBestUnit(precision);

  // construct the run manager

  auto* runManager = new G4RunManager();

  // set mandatory initialization classes
  DetectorConstruction* det = new DetectorConstruction(targetthic);
  runManager->SetUserInitialization(det);
  PhysicsList* phys = new PhysicsList;
  runManager->SetUserInitialization(phys);
  runManager->SetUserInitialization(new ActionInitialization(det, targetthic));

   runManager->Initialize();

  // initialize visualization

  G4VisManager* visManager = nullptr;

  // get the pointer to the User Interface manager


 G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui) {
    // interactive mode
    visManager = new G4VisExecutive;
    visManager->Initialize();
    ui->SessionStart();
    delete ui;
  }
  else {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[4];
    UImanager->ApplyCommand(command + fileName);
  }

  // job termination
  delete visManager;


  delete runManager;


}


