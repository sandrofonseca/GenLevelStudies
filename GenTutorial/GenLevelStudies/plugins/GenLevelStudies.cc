// -*- C++ -*-
//
// Package:    GenTutorial/GenLevelStudies
// Class:      GenLevelStudies
//
/**\class GenLevelStudies GenLevelStudies.cc GenTutorial/GenLevelStudies/plugins/GenLevelStudies.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Sandro Fonseca De Souza
//         Created:  Wed, 05 Feb 2020 09:25:53 GMT
//
//


// system include files
#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"


#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"


//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.


using reco::GenParticleCollection;
using namespace std;
using namespace reco;
using namespace edm;


class GenLevelStudies : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
	public:
		explicit GenLevelStudies(const edm::ParameterSet&);
		~GenLevelStudies();



	private:
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
                virtual void beginJob() override ;
                virtual void endJob() override ;
                void initialize();
		// ----------member data ---------------------------
		edm::EDGetTokenT<GenParticleCollection> genParticlesToken_;

		TTree *mc;
		vector<double> genpt;
                vector<double> geneta;
                int runNumber=0; int eventNumber=0;              
};

////////////////////////////////////////////////////////////////////////////
GenLevelStudies::GenLevelStudies(const edm::ParameterSet& iConfig)
	:genParticlesToken_(consumes<GenParticleCollection>(edm::InputTag{"genParticles"}))
{
	//now do what ever initialization is needed
	edm::Service<TFileService> fs;
	mc = fs->make<TTree>("mc","mc");
}


GenLevelStudies::~GenLevelStudies()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}
//
// member functions
//

// ------------ method called for each event  ------------
	void
GenLevelStudies::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	using namespace std;
        //to clear vectors
        initialize();
       //run, event, lumi section
	runNumber= iEvent.id().run();
	eventNumber= iEvent.id().event();


	Handle<GenParticleCollection> genParticles;
	iEvent.getByToken(genParticlesToken_, genParticles);
	cout << "Running " << endl;

	for(const auto& genParticles : iEvent.get(genParticlesToken_) ){


		cout << " PDG_ID: " << genParticles.pdgId() << " status: "<< genParticles.status() << " pT: "  << genParticles.pt() << "|eta|: " << abs(genParticles.eta()) << " phi: "<< genParticles.phi() << endl;
            

            double pt = genParticles.pt();
            double eta = abs(genParticles.eta()); 

		// fill vector
		genpt.push_back(pt);
		geneta.push_back(eta); 

	}

mc->Fill();
}// end analyze function

       void
GenLevelStudies::initialize( )
{
        runNumber=0; eventNumber=0;
        genpt.clear();
        geneta.clear();

}
///////
//++++++++++++++++++
void GenLevelStudies::endJob(){

    cout <<"######################################################################"<<endl;
    cout << "Number of Events: " << eventNumber << " Run Number: " << runNumber << endl;
    
}


/////////////////////
     void
GenLevelStudies::beginJob()
{
        mc->Branch("runNumber",&runNumber,"runNumber/I");
	mc->Branch("eventNumber",&eventNumber,"eventNumber/I");
        mc->Branch("genpt",&genpt);
        mc->Branch("geneta",&geneta);
}



//////////////////////////////////////////
//define this as a plug-in
DEFINE_FWK_MODULE(GenLevelStudies);
