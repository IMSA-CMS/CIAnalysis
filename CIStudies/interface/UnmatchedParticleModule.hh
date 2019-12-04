#ifndef UNMATCHEDPARTICLEMODULE_HH
#define UNMATCHEDPARTICLEMODULE_HH

#include "HistogramOutputModule.hh"

class GenSimIdentificationModule;
class MatchingModule;

class UnmatchedParticleModule : public HistogramOutputModule
{
public:
  UnmatchedParticleModule(const GenSimIdentificationModule& genSimModule, const MatchingModule& matchingModule);

  virtual void initialize() override;
  virtual bool process(const edm::EventBase& event) override;
  virtual void finalize() {AnalysisModule::finalize();}

private:
  const GenSimIdentificationModule& genSim;
  const MatchingModule& matching;

  const int histBins = 100;
};

#endif