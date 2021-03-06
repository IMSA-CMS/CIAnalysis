#include <iostream>
#include <memory>

#include "TROOT.h"
#include "TSystem.h"

#include "CIAnalysis/CIStudies/interface/Analyzer.hh"
#include "CIAnalysis/CIStudies/interface/DoubleMuonTrigger.hh"
#include "CIAnalysis/CIStudies/interface/GenSimEventDumpModule.hh"
#include "CIAnalysis/CIStudies/interface/GenSimIdentificationModule.hh"
#include "CIAnalysis/CIStudies/interface/HistogramOutputModule.hh"
#include "CIAnalysis/CIStudies/interface/LeptonEfficiency.hh"
#include "CIAnalysis/CIStudies/interface/LRWeightModule.hh"
#include "CIAnalysis/CIStudies/interface/MassRecoEfficiency.hh"
#include "CIAnalysis/CIStudies/interface/MatchingModule.hh"
#include "CIAnalysis/CIStudies/interface/NLeptonsFilter.hh"
#include "CIAnalysis/CIStudies/interface/NLeptonsHist.hh"
#include "CIAnalysis/CIStudies/interface/RecoIdentificationModule.hh"
#include "CIAnalysis/CIStudies/interface/SameSignInvariantMassHist.hh"
#include "CIAnalysis/CIStudies/interface/SingleMuonTrigger.hh"
#include "CIAnalysis/CIStudies/interface/ThirdMuonPtHist.hh"
#include "CIAnalysis/CIStudies/interface/RecoveredInvariantMassHist.hh"
#include "CIAnalysis/CIStudies/interface/TriggerEfficiencyModule.hh"
#include "CIAnalysis/CIStudies/interface/TriggerModule.hh"
#include "CIAnalysis/CIStudies/interface/TripleMuonTrigger.hh"
#include "CIAnalysis/CIStudies/interface/WeightingModule.hh"
#include "CIAnalysis/CIStudies/interface/PhotonsHist.hh"

using std::make_shared;

Analyzer hPlusPlusMassAnalysis() {
  Analyzer analyzer;

  auto eventDump = make_shared<GenSimEventDumpModule>(7);

  auto genSimMod = make_shared<GenSimIdentificationModule>(9900041, true);
  auto recoMod = make_shared<RecoIdentificationModule>(50);
  auto matchMod = make_shared<MatchingModule>(genSimMod, recoMod);
  auto triggerMod = make_shared<TriggerModule>(recoMod);
  auto weightMod = make_shared<WeightingModule>();
  auto lrWeightMod = make_shared<LRWeightModule>();

  auto nLeptonsFilter = make_shared<NLeptonsFilter>(recoMod); //Needs to be updated with shared pointers
  
  auto histMod = make_shared<HistogramOutputModule>(genSimMod, recoMod, weightMod, lrWeightMod);
  auto nLeptonsHist = make_shared<NLeptonsHist>(matchMod, "Matched Leptons", 10, 0, 10);
  auto nElectronsHist = make_shared<NLeptonsHist>(matchMod, "Matched Electrons", 10, 0, 10, 11);
  auto nMuonsHist = make_shared<NLeptonsHist>(matchMod, "Matched Muons", 10, 0, 10, 13);

  auto leptonEfficiency = make_shared<LeptonEfficiency>(matchMod, genSimMod);
  //auto massRecoEfficiency200 = make_shared<MassRecoEfficiency>(recoMod, 200, 10);
  //auto massRecoEfficiency500 = make_shared<MassRecoEfficiency>(recoMod, 500, 25);
  //auto massRecoEfficiency800 = make_shared<MassRecoEfficiency>(recoMod, 800, 40);
  //auto massRecoEfficiency1000 = make_shared<MassRecoEfficiency>(recoMod, 1000, 50);
  //auto massRecoEfficiency1300 = make_shared<MassRecoEfficiency>(recoMod, 1300, 65);

  auto massRecoEfficiency55 = make_shared<MassRecoEfficiency>(recoMod, 800, 5, 5);
  auto massRecoEfficiency1010 = make_shared<MassRecoEfficiency>(recoMod, 800, 10, 10);
  auto massRecoEfficiency4010 = make_shared<MassRecoEfficiency>(recoMod, 800, 40, 10);
  auto massRecoEfficiency4040 = make_shared<MassRecoEfficiency>(recoMod, 800, 40, 40);
  auto massRecoEfficiency8040 = make_shared<MassRecoEfficiency>(recoMod, 800, 80, 40);
  auto massRecoEfficiency20080 = make_shared<MassRecoEfficiency>(recoMod, 800, 200, 80);

  auto triggerEfficiencyMod4010 = make_shared<TriggerEfficiencyModule>(matchMod, genSimMod, 800, 40, 10);
  auto triggerEfficiencyMod4040 = make_shared<TriggerEfficiencyModule>(matchMod, genSimMod, 800, 40, 40);
  auto triggerEfficiencyMod8040 = make_shared<TriggerEfficiencyModule>(matchMod, genSimMod, 800, 80, 40);
  auto triggerEfficiencyMod20080 = make_shared<TriggerEfficiencyModule>(matchMod, genSimMod, 800, 200, 80);

  auto recoThirdMuonPtHist = make_shared<ThirdMuonPtHist>(genSimMod, recoMod, false, std::string("Reconstructed Third Muon Transverse Momentum"), 50, 0, 3000);
  auto sameSignInvMassHist = make_shared<SameSignInvariantMassHist>(genSimMod, recoMod, true, "GenSim Same Sign Invariant Mass", 100, 0, 1000);

  auto genSimHPlusPlusRecoveredInvMassHist = make_shared<RecoveredInvariantMassHist>(genSimMod, recoMod, true, "GenSim H++ Recovered Invariant Mass with 3 Leptons", 100, 0, 1000, 3, 9900041);
  auto recoHPlusPlusRecoveredInvMassHist = make_shared<RecoveredInvariantMassHist>(genSimMod, recoMod, false, "Reco H++ Recovered Invariant Mass with 3 Leptons", 100, 0, 1000, 3, 9900041);
  auto genSimHMinusMinusRecoveredInvMassHist = make_shared<RecoveredInvariantMassHist>(genSimMod, recoMod, true, "GenSim H-- Recovered Invariant Mass with 3 Leptons", 100, 0, 1000, 3, -9900041);
  auto recoHMinusMinusRecoveredInvMassHist = make_shared<RecoveredInvariantMassHist>(genSimMod, recoMod, false, "Reco H-- Recovered Invariant Mass with 3 Leptons", 100, 0, 1000, 3, 9900041);

  auto photonHist = make_shared<PhotonsHist>(genSimMod, recoMod, true, "Photon Histogram", 100, 0, 1000);

  // Add the histogram(s) created above to histMod
  //histMod->addHistogram(recoThirdMuonPtHist);
  //histMod->addHistogram(sameSignInvMassHist);
  histMod->addHistogram(genSimHPlusPlusRecoveredInvMassHist);
  histMod->addHistogram(recoHPlusPlusRecoveredInvMassHist);
  histMod->addHistogram(genSimHMinusMinusRecoveredInvMassHist);
  histMod->addHistogram(recoHMinusMinusRecoveredInvMassHist);
  histMod->addHistogram(photonHist);
  histMod->addHistogram(nLeptonsHist);
  //histMod->addHistogram(nElectronsHist);
  //histMod->addHistogram(nMuonsHist);

  // Initialize triggers
  auto singleMuonTrigger = make_shared<SingleMuonTrigger>(recoMod, 50);
  auto doubleMuonTrigger = make_shared<DoubleMuonTrigger>(recoMod, 37, 27);
  auto tripleMuonTrigger = make_shared<TripleMuonTrigger>(recoMod, 10, 5, 5);

  // Add triggers to the TriggerModule
  triggerMod->addTrigger(singleMuonTrigger);
  triggerMod->addTrigger(doubleMuonTrigger);
  triggerMod->addTrigger(tripleMuonTrigger);

  analyzer.addProductionModule(genSimMod);
  analyzer.addProductionModule(recoMod);
  analyzer.addProductionModule(matchMod);
  analyzer.addProductionModule(triggerMod);
  analyzer.addProductionModule(weightMod);
  analyzer.addProductionModule(lrWeightMod);

  // Filters
  //analyzer.addFilterModule(nLeptonsFilter);

  analyzer.addAnalysisModule(histMod); // Don't remove unless you don't want histograms
  //analyzer.addAnalysisModule(eventDump);
  //analyzer.addAnalysisModule(leptonEfficiency);

  //analyzer.addAnalysisModule(triggerEfficiencyMod4010);
  //analyzer.addAnalysisModule(triggerEfficiencyMod4040);
  //analyzer.addAnalysisModule(triggerEfficiencyMod8040);
  //analyzer.addAnalysisModule(triggerEfficiencyMod20080);

  //analyzer.addAnalysisModule(massRecoEfficiency200);
  //analyzer.addAnalysisModule(massRecoEfficiency500);
  //analyzer.addAnalysisModule(massRecoEfficiency800);
  //analyzer.addAnalysisModule(massRecoEfficiency1000);
  //analyzer.addAnalysisModule(massRecoEfficiency1300);
  
  analyzer.addAnalysisModule(massRecoEfficiency55);
  analyzer.addAnalysisModule(massRecoEfficiency1010);
  //analyzer.addAnalysisModule(massRecoEfficiency4010);
  //analyzer.addAnalysisModule(massRecoEfficiency4040);
  //analyzer.addAnalysisModule(massRecoEfficiency8040);
  //analyzer.addAnalysisModule(massRecoEfficiency20080);

  return analyzer;
}
