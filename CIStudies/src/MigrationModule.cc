#include "CIAnalysis/CIStudies/interface/MigrationModule.hh"
#include "CIAnalysis/CIStudies/interface/MatchingModule.hh"

MigrationModule::MigrationModule(const MatchingModule& matchingModule, int minMass, int maxMass, int massInterval) :
  matching(matchingModule),
  minMassCut(minMass),
  maxMassCut(maxMass),
  interval(massInterval)
{
}


bool MigrationModule::process(const edm::EventBase& event)
{
  auto bestPairs = matching.getMatchingBestPairs();

  if (bestPairs.getSize() >= 2)
    {
      double genSimMass = bestPairs.getGenParticles().getInvariantMass();
      double recoMass = bestPairs.getRecoParticles().getInvariantMass();

      std::string massBin = pickMassBin(genSimMass);
      fillHistogram("genSimHistBin" + massBin, genSimMass);
      fillHistogram("recoHistBin" + massBin, recoMass);
    }
  
  return true;
}

void MigrationModule::createHistograms()
{
  const int numberOfBins = (maxMassCut - minMassCut) / interval;


  for(int i = 0; i < numberOfBins; ++i)
    {
      const std::string migrationStr = "Migration";
      makeHistogram(("genSimHistBin" + std::to_string(i * interval + minMassCut)), migrationStr, interval, (i * 100 + minMassCut - 200), (i * 100 + minMassCut + 300));
      makeHistogram(("recoHistBin" + std::to_string(i * interval + minMassCut)), migrationStr, interval, (i * 100 + minMassCut - 200), (i * 100 + minMassCut + 300));
    }
}

std::string MigrationModule::pickMassBin(double invariantMass)
{
  int mass = static_cast<int>(invariantMass) / interval * interval; //mass is invariantMass floored to the highest multiple of interval
  if (mass < minMassCut)
    {
      mass = minMassCut;
    }
  else if (mass > maxMassCut)
    {
      mass = maxMassCut;
    }

  return std::to_string(mass);
}
