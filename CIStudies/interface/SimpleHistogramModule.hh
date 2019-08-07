#ifndef SIMPLEHISTOGRAMMODULE_HH
#define SIMPLEHISTOGRAMMODULE_HH

#include "HistogramOutputModule.hh"

class GenSimIdentificationModule;
class RecoIdentificationModule;

class SimpleHistogramModule : public HistogramOutputModule
{
public:
  SimpleHistogramModule(const GenSimIdentificationModule& genSimModule, const RecoIdentificationModule& recoModule);

  virtual void initialize() override;
  virtual bool process(const edm::EventBase& event) override;
  virtual void finalize() {AnalysisModule::finalize();}

private:
  const GenSimIdentificationModule& genSim;
  const RecoIdentificationModule& reco;

  const int histBins = 100;
};

#endif
