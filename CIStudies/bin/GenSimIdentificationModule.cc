#include "GenSimIdentificationModule.hh"

#include <cmath>

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/FWLite/interface/Event.h"

void GenSimIdentificationModule::process(const edm::EventBase& event)
{
  //Get Events Tree and create handle for GEN

  edm::Handle<std::vector<reco::GenParticle>> genParticlesHandle;
  event.getByLabel(std::string("prunedGenParticles"), genParticlesHandle);
 
` const reco::GenParticle* particle = nullptr
  //Begin GEN looping
  //Loop through Particle list&
  for (const auto& p : *genParticlesHandle)
    {	
      //Check for (anti)muon or (anti)electron
      if ((abs(p.pdgId()) == 13 || abs(p.pdgId()) == 11))
	{
	  if (p.status() == 1 && !particle && (p.mother()->status() != 1))
	    { 
	      if (isParticle(p))
		{
		  particle = &p;
		}

	      if (particle)
		{
		  if (particle->pt()>ptCut)
		    { 
		      genParticles.push_back(particle); 
		    }
		}
	    }
	}
    }
}

bool GenSimIdentificationModule::isParticle(const reco::GenParticle& p) const
{
  const reco::Candidate* nu = p.mother();
  int motherId = nu->pdgId();
  bool isParticle = true; 
  while (abs(motherId) > 6) //not a quark
    {
      if(nu->mother() && nu)
	{
	  nu = nu->mother(); 
	  motherId = nu->pdgId();
	  if (abs(motherId) > 13)
	    { //not a particle
	      isParticle = false; 
	    }
	  if (abs(motherId) < 7)
	    {//#is a quark 
	      isParticle = true;
	    }
	}		  
      else
	{
	  std::cout<<"error"<<std::endl; 
	  return false; 
	}
    }
  return isParticle;
}


