#ifndef MASSRESOLUTIONHIST_HH
#define MASSRESOLUTIONHIST_HH

#include "CIAnalysis/CIStudies/interface/ResolutionPrototype.hh"

class MassResolutionHist : public ResolutionPrototype
{
  public:
    using ResolutionPrototype::ResolutionPrototype; //copies constructor over from ResolutionPrototype
  protected:
    double getValue(const ParticleCollection& partColl) const override;
};

#endif
