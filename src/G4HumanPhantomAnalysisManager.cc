//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
/*
Author: Susanna Guatelli
*/
// The class G4HumanPhantomAnalysisManager creates and manages ntuples

// The analysis was included in this application following the extended Geant4
// example analysis/AnaEx01

#include <stdlib.h>
#include "G4HumanPhantomAnalysisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

G4HumanPhantomAnalysisManager::G4HumanPhantomAnalysisManager()
{

factoryOn = false;

// Initialization ntuple
  for (G4int k=0; k<MaxNtCol; k++) {
    fNtColId[k] = 0;
  }  
}

G4HumanPhantomAnalysisManager::~G4HumanPhantomAnalysisManager() 
{ 
}

void G4HumanPhantomAnalysisManager::book() 
{  
  G4AnalysisManager* AnalysisManager = G4AnalysisManager::Instance();
  
  AnalysisManager->SetVerboseLevel(2);
 
  // Create a root file
  G4String fileName = "human_phantom.root";

  // Create directories  
  AnalysisManager->SetNtupleDirectoryName("human_phantom_ntuple");
  

  G4bool fileOpen = AnalysisManager->OpenFile(fileName);
  if (!fileOpen) {
    G4cout << "\n---> HistoManager::book(): cannot open " 
           << fileName
           << G4endl;
    return;
  }

  //creating a ntuple, containg 3D energy deposition in the phantom
  AnalysisManager->SetFirstNtupleId(1);
  AnalysisManager -> CreateNtuple("data", "3Dedep");
  fNtColId[0] = AnalysisManager->CreateNtupleDColumn("organID");
  fNtColId[1] = AnalysisManager->CreateNtupleDColumn("edep");
  fNtColId[2] = AnalysisManager->CreateNtupleDColumn("eventID");
  fNtColId[3] = AnalysisManager->CreateNtupleDColumn("primary_energy");

  AnalysisManager->FinishNtuple();
  
  factoryOn = true;    
}

 
void G4HumanPhantomAnalysisManager::FillNtupleWithEnergyDeposition(G4int organ,G4double energyDep, G4int eventID)
{
  if (energyDep !=0)
 {
  G4AnalysisManager* AnalysisManager = G4AnalysisManager::Instance();
  AnalysisManager->FillNtupleDColumn(1, fNtColId[0], organ);
  AnalysisManager->FillNtupleDColumn(1, fNtColId[1], energyDep);
  AnalysisManager->FillNtupleDColumn(1, fNtColId[2], eventID);
  AnalysisManager->FillNtupleDColumn(1, fNtColId[3], fPrimaryEnergy);
  AnalysisManager->AddNtupleRow(1);  
}
 }

void G4HumanPhantomAnalysisManager::save() 
{  
 if (factoryOn) 
   {
    G4AnalysisManager* AnalysisManager = G4AnalysisManager::Instance();    
    AnalysisManager->Write();
    AnalysisManager->CloseFile();  
      
    delete G4AnalysisManager::Instance();
    factoryOn = false;
   }
}

void G4HumanPhantomAnalysisManager::SetPrimaryEnergy(G4double energy)
{
  fPrimaryEnergy = energy;
}










