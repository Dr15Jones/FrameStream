// -*- C++ -*-
//
// Package:     procname
// Module:      procname
// 
// Description: <one line class summary>
//
// Implementation:
//     <Notes on implementation>
//
// Author:      John Doe
// Created:     day-mon-xx
// RCS(Id)
//
// Revision history
//
// RCS(Log)
//

#include "Experiment/Experiment.h"

// system include files

// user include files
#include "procname/procname.h"
#include "Experiment/report.h"
#include "Experiment/units.h"  // for converting to/from standard CLEO units

#include "DataHandler/Record.h"
#include "DataHandler/Frame.h"
#include "FrameAccess/extract.h"
#include "FrameAccess/FAItem.h"
#include "FrameAccess/FATable.h"

example_track_dedx_rich_eventshape_kshort_dchain #include "Navigation/NavTrack.h"
example_track #include "TrackRoot/TRHelixFit.h"
example_track #include "TrackRoot/TRTrackFitQuality.h"
example_track #include "TrackRoot/TRSeedTrackQuality.h"
example_track_eventshape #include "TrackDelivery/TDKinematicFit.h"

example_shower_eventshape_pi0_dchain #include "Navigation/NavShower.h"
example_shower_eventshape #include "C3cc/CcShowerAttributes.h"
example_pi0_dchain #include "Navigation/NavPi0ToGG.h"
example_pi0_dchain #include "PhotonDecays/PhdPi0.h"
example_kshort_dchain #include "Navigation/NavKs.h"
example_rich //RICH example 
example_rich #include "Navigation/NavRich.h"
example_dedx //Dedx example
example_dedx #include "DedxInfo/DedxInfo.h"
example_eventshape //Event Shape example
example_eventshape #include "EventShape/EventShape.h"
example_eventshape #include "BeamEnergy/BeamEnergy.h"

example_mc #include "MCInfo/MCDecayTree/MCDecayTree.h"
example_mc #include "MCInfo/MCDecayTree/MCParticle.h"
example_mc #include "MCInfo/MCParticleProperty/MCParticleProperty.h"
example_mc #include "MCInfo/MCParticleProperty/MCParticlePropertyStore.h"
example_histogram #include "HistogramInterface/HIHist1D.h"
example_histogram #include "CleoDB/DBEventHeader.h"
example_dchain #include "DChain/Element/DCChildren.h"
example_dchain #include "DChain/List/Template/DCLabeledDecayList.cc"
example_dchain #include "DChain/List/Template/DCDecayList.cc"
example_dchain #include "DChain/Iterator/DCMuteWholeItr.h"
example_dchain #include "DChain/Function/DCAnalysisFunction.h"
example_dchain #include "DChain/Element/Template/DCLabeledDecay.cc"
example_dchain #include "DChain/List/DCCombinatoricList.h"
example_dchain #include "CleoDChain/CDCandidate.h"
example_dchain #include "CleoDChain/CDDecay.h"
example_dchain #include "CleoDChain/CDDecayList.h"
example_dchain #include "CleoDChain/CDChargedPionList.h"
example_dchain #include "CleoDChain/CDChargedKaonList.h"
example_dchain #include "CleoDChain/CDPhotonList.h"
example_dchain #include "CleoDChain/CDPi0.h"
example_dchain #include "CleoDChain/CDPi0List.h"
example_dchain #include "CleoDChain/CDKs.h"
example_dchain #include "CleoDChain/CDKsList.h"
example_dchain #include "CleoDChain/CDTruthEvidence.h"
example_dchain #include "CleoDChain/CDCandidateList.h"
example_dchain #include "CleoDChain/DefaultCombiner.h"
example_dchain #include "HistogramInterface/HINtupleVarNames.h"

// STL classes
// You may have to uncomment some of these or other stl headers 
// depending on what other header files you include (e.g. FrameAccess etc.)!
//#include <string>
//#include <vector>
//#include <set>
//#include <map>
//#include <algorithm>
//#include <utility>
example_dchain #if defined(AUTO_INSTANTIATE_TEMPLATE_BUG)
example_dchain template class DCLabeledDecay<CDDecay>;
example_dchain #endif

//
// constants, enums and typedefs
//
static const char* const kFacilityString = "Processor.procname" ;

// ---- cvs-based strings (Id and Tag with which file was checked out)
static const char* const kIdString  = "$Id: processor.cc,v 1.34 2003/07/23 16:12:06 jed Exp $";
static const char* const kTagString = "$Name:  $";

example_mc // Some handy typedefs for accessing MC information
example_mc typedef MCDecayTree::const_vIterator MCVertexConstIt;
example_mc typedef MCDecayTree::const_pIterator MCPartConstIt;
example_mc typedef MCVertex::const_pIterator    MCChildConstIt;
example_mc
//
// static data member definitions
//

example_dchain // these functions are used to tell DChain whether or not you want to keep
example_dchain // a particular candidate
example_dchain 
example_dchain // keep K*+ candidates within 75 MeV of nominal
example_dchain static
example_dchain DChainBoolean
example_dchain kStarPlusSelection( CDDecay& iKStarPlus )
example_dchain {
example_dchain    return ( fabs( iKStarPlus.mass() - 891.88*k_MeV ) <= 75*k_MeV );
example_dchain }
example_dchain 
example_dchain // keep D0 candidates within 100 MeV of nominal D0 mass
example_dchain static
example_dchain DChainBoolean
example_dchain d0Selection( CDDecay& iD0 ) 
example_dchain {
example_dchain    return ( fabs( iD0.mass() - 1.8645*k_GeV ) <= 100*k_MeV );
example_dchain }
example_dchain
example_dchain 
example_dchain // keep D*0 candidates within 10 MeV of nominal mass difference
example_dchain static
example_dchain DChainBoolean
example_dchain dStarSelection( CDDecay& iDStar )
example_dchain {
example_dchain    float massDiff = iDStar.mass() - iDStar.child( DCChildren::First ).mass();
example_dchain 
example_dchain    return ( fabs( massDiff - 145.5*k_MeV ) <= 10*k_MeV); 
example_dchain }
example_dchain 

example_mc // These are functions you might write to identify certain
example_mc //   signal decays in a general decay tree
example_mc // In your own code, you might consider making these member functions
example_mc
example_mc // Checks whether a particular decay vertex is a B decay
example_mc static
example_mc DABoolean
example_mc isBDecay( const MCVertex& vtx )
example_mc {
example_mc    const MCParticleProperty& parent = vtx.parent().properties();
example_mc  
example_mc    // Is this a B?
example_mc    // (You might instead consider using the bottom() member function
example_mc    //   in MCParticleProprty . . .)
example_mc    if ((parent.name() == "B+") ||
example_mc        (parent.name() == "B-") ||
example_mc        (parent.name() == "B0") ||
example_mc        (parent.name() == "B0B"))
example_mc    {
example_mc       return true;
example_mc    }
example_mc 
example_mc    return false;
example_mc }
example_mc
example_mc // Checks whether a particular decay vertex is B -> X_u l nu
example_mc static
example_mc DABoolean
example_mc isBXulnu( const MCVertex& vtx )
example_mc {
example_mc    // Is this a B decay?
example_mc    if (!isBDecay(vtx)) return false;
example_mc
example_mc    // To be a signal B -> Xu l nu decay, we want all daughters to either
example_mc    //   be a lepton, neutrino, or non-charmed
example_mc    
example_mc    // Loop over daughters of the vertex
example_mc    int numNeutrinos = 0;
example_mc    int numLeptons   = 0;
example_mc    MCChildConstIt   childEnd = vtx.pEnd();
example_mc    for (MCChildConstIt child = vtx.pBegin();
example_mc         child != childEnd; ++child)
example_mc    {
example_mc       const MCParticleProperty& childProp = child->properties();
example_mc       
example_mc       if (childProp.neutrino()) ++numNeutrinos;
example_mc       if (childProp.lepton())   ++numLeptons;
example_mc
example_mc       if (childProp.charmed()) return false;
example_mc    }
example_mc    
example_mc    return ((numNeutrinos == 1) && (numLeptons == 1));
example_mc }

//
// constructors and destructor
//
procname::procname( void )               // anal1
   : Processor( "procname" )
example_tuplevector    ,m_example=Inserter(false) //does not delete what is inserted
{
   report( DEBUG, kFacilityString ) << "here in ctor()" << endl;

   // ---- bind a method to a stream -----
   // These lines ARE VERY IMPORTANT! If you don't bind the 
   // code you've just written (the "action") to a stream, 
   // your code won't get executed!

   bind( &procname::event,    Stream::kEvent );
   //bind( &procname::beginRun, Stream::kBeginRun );
   //bind( &procname::endRun,   Stream::kEndRun );

   // do anything here that needs to be done at creation time
   // (e.g. allocate resources etc.)

example_tuplevector    //initially reserve space for 2 to avoid taking up lots of memory
example_tuplevector    //(it will automatically grow if more are added)
example_tuplevector    m_example=List.reserve(2);

example_tuple_tuplevector    registerProxyFactory(Stream::kEvent, 
example_tuple_tuplevector                         m_example=Inserter.makeFactory(),
example_tuple_tuplevector                         UsageTag() );
}

procname::~procname()                    // anal5
{
   report( DEBUG, kFacilityString ) << "here in dtor()" << endl;
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ methods for beginning/end "Interactive" ------------
// --------------------------- init method -------------------------
void
procname::init( void )          // anal1 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in init()" << endl;

   // do any initialization here based on Parameter Input by User
   // (e.g. run expensive algorithms that are based on parameters
   //  specified by user at run-time)

}

// -------------------- terminate method ----------------------------
void
procname::terminate( void )     // anal5 "Interactive"
{
   report( DEBUG, kFacilityString ) << "here in terminate()" << endl;

   // do anything here BEFORE New Parameter Change
   // (e.g. write out result based on parameters from user-input)
 
}

example_dchain enum {kDMass, kDStarMass, kDMom, kDStarNum};

// ---------------- standard place to book histograms ---------------
void
procname::hist_book( HIHistoManager& iHistoManager )
{
   report( DEBUG, kFacilityString ) << "here in hist_book()" << endl;

   // book your histograms here
example_histogram    m_histo1 = iHistoManager.histogram( "Event Number" ,
example_histogram                                        12000          ,
example_histogram                                        0              ,
example_histogram                                        120000         );

example_dchain    HINtupleVarNames ntupleNames(kDStarNum);
example_dchain    ntupleNames.addVar(kDMass, "DMass");
example_dchain    ntupleNames.addVar(kDStarMass, "DStar");
example_dchain    ntupleNames.addVar(kDMom, "DMom");
example_dchain    m_dStarNtuple = iHistoManager.ntuple(10, "DStar", kDStarNum, 10000,
example_dchain 					ntupleNames.names());
}

// --------------------- methods bound to streams -------------------
ActionBase::ActionResult
procname::event( Frame& iFrame )          // anal3 equiv.
{
   report( DEBUG, kFacilityString ) << "here in event()" << endl;

example_tuplevector    //get rid of old stuff in our list
example_tuplevector    m_example=List.erase(m_example=List.begin(), m_example=List.end());
example_tuplevector
example_track
example_track_dedx_rich_eventshape_dchain    // Create a table of tracks and fill it.
example_track_dedx_rich_eventshape_dchain    FATable< NavTrack > trackTable;
example_track_dedx_rich_eventshape_dchain    extract( iFrame.record( Stream::kEvent ) , trackTable );
example_track_dedx_rich_eventshape_dchain
example_track_dedx_rich_eventshape_dchain    FATable< NavTrack >::const_iterator trackTableBegin = trackTable.begin();
example_track_dedx_rich_eventshape_dchain    FATable< NavTrack >::const_iterator trackTableEnd = trackTable.end();
example_track    // Loop over tracks.
example_track    for ( FATable< NavTrack >::const_iterator trackItr = trackTableBegin;
example_track          trackItr != trackTableEnd ;
example_track          ++trackItr )
example_track    {
example_track       // Print out the track's ID number.
example_track       report( INFO, kFacilityString )
example_track          << "track "
example_track          << (*trackItr).identifier()
example_track          << endl;
example_track
example_track       // Ask for the pion fit and quality information.
example_track       FAItem< TDKinematicFit > pionFit = (*trackItr).pionFit();
example_track       FAItem< TRHelixFit > pionHelix = (*trackItr).pionHelix();
example_track       FAItem< TRTrackFitQuality > pionQuality = (*trackItr).pionQuality();
example_track       FAItem< TRSeedTrackQuality > seedQuality = (*trackItr).seedQuality();
example_track
example_track       // Now apply some of the standard rare-B analysis cuts.
example_track       if ( (*seedQuality).numberHitsExpected() == 0)
example_track       {
example_track          report(WARNING, kFacilityString)
example_track             <<"Number of Hits expected is zero, skipping this track!" 
example_track		  << endl;   
example_track          continue;
example_track       }
example_track
example_track       float hit_fraction 
example_track                = (*pionQuality).ratioNumberHitsToExpected();
example_track       

example_track       double cos_theta =
example_track          sqrt( 1 - 1 / ( 1+sqr((*pionHelix).cotTheta()) ) );
example_track       // You could also have:
example_track       //    double cos_theta = (*pionFit).momentum().cosTheta();
example_track       // but then you'd need to make sure that you take its absolute
example_track       // value when using it, assuming that's what you want.
example_track
example_track       if ( !(*pionQuality).fitAbort()          // not an aborted fit
example_track            &&
example_track            !(*seedQuality).originUsed()        // not a "z-escape"
example_track            &&
example_track            ( (*pionFit).pmag() <= 5.3*k_GeV )
example_track            &&
example_track            ( (*pionFit).pmag() > 100*k_MeV )
example_track            &&
example_track            ( hit_fraction >= 0.3 )
example_track            &&
example_track            ( cos_theta <= 0.9 ) )   // or abs(cos_theta)
example_track       {
example_track          report( INFO, kFacilityString )
example_track             << "  momentum: "
example_track             << (*pionFit).momentum()
example_track             << endl;
example_track       }
example_track    }
example_shower
example_shower_eventshape_dchain    FATable< NavShower > showerTable;
example_shower_eventshape_dchain    extract( iFrame.record( Stream::kEvent ) , showerTable );
example_shower_eventshape_dchain
example_shower_eventshape_dchain    FATable< NavShower >::const_iterator showerBegin = showerTable.begin();
example_shower_eventshape_dchain    FATable< NavShower >::const_iterator showerEnd = showerTable.end();
example_shower    for (FATable< NavShower >::const_iterator showerItr = showerBegin; 
example_shower         showerItr != showerEnd ; ++showerItr )
example_shower    {
example_shower       report( INFO, kFacilityString )
example_shower          << "shower "
example_shower          << (*showerItr).identifier()
example_shower          << endl;
example_shower       report( INFO, kFacilityString )
example_shower          << "  energy: "
example_shower          << (*showerItr).attributes().energy()
example_shower          << endl;
example_shower    }
example_pi0_dchain    FATable<NavPi0ToGG> pi0Table;
example_pi0_dchain    extract(iFrame.record(Stream::kEvent), pi0Table);
example_pi0_dchain 
example_pi0_dchain    FATable<NavPi0ToGG>::const_iterator pi0TableBegin = pi0Table.begin();
example_pi0_dchain    FATable<NavPi0ToGG>::const_iterator pi0TableEnd = pi0Table.end();
example_pi0 
example_pi0    for(FATable<NavPi0ToGG>::const_iterator pi0Itr = pi0TableBegin;
example_pi0        pi0Itr != pi0TableEnd; ++pi0Itr)
example_pi0    {
example_pi0       const PhdPi0& pi0 = (*pi0Itr).pi0();
example_pi0 
example_pi0       //use -shower to see other things you can do with NavShower
example_pi0       const NavShower& hiEnergy = (*pi0Itr).hiEnShower();
example_pi0       const NavShower& loEnergy = (*pi0Itr).loEnShower();
example_pi0       
example_pi0       report(INFO, kFacilityString)
example_pi0          <<"Pi0: "<<(*pi0Itr).identifier()
example_pi0          <<", momentum: "<<pi0.momentum()
example_pi0          <<", mass: "<<pi0.mass()
example_pi0          <<", made from high energy shower: "<<hiEnergy.identifier()
example_pi0          <<", made from low energy shower: "<<loEnergy.identifier()
example_pi0          <<endl;
example_pi0    }
example_kshort_dchain    FATable<NavKs> kshortTable;
example_kshort_dchain    extract(iFrame.record(Stream::kEvent), kshortTable);
example_kshort_dchain 
example_kshort_dchain    FATable<NavKs>::const_iterator kshortTableBegin = kshortTable.begin();
example_kshort_dchain    FATable<NavKs>::const_iterator kshortTableEnd = kshortTable.end();
example_kshort 
example_kshort    for(FATable<NavKs>::const_iterator kshortItr = kshortTableBegin;
example_kshort        kshortItr != kshortTableEnd; ++kshortItr)
example_kshort    {
example_kshort        const VXFitVeeKShort& kshort = (*kshortItr).kShort();
example_kshort
example_kshort       //use -track to see other things you can do with NavTrack
example_kshort       const NavTrack& piPlus = (*kshortItr).piPlus();
example_kshort       const NavTrack& piMinus = (*kshortItr).piMinus();
example_kshort
example_kshort       report(INFO, kFacilityString)
example_kshort          <<"K short: "<<(*kshortItr).identifier()
example_kshort          <<", momentum: "<<kshort.momentum()
example_kshort          <<", mass: "<<kshort.mass()
example_kshort          <<", decay distance: "<<kshort.position().distance()
example_kshort          <<", made from pi+: "<<piPlus.identifier()
example_kshort          <<" and pi-: "<<piMinus.identifier()
example_kshort          <<endl;
example_kshort    }
example_mc    // ************************
example_mc    // MC Decay Tree example
example_mc    // ************************
example_mc
example_mc    // Extract decay tree for this event
example_mc    // N.B. Default usage tag is appropriate for DriverDelivery, where we
example_mc    //   just want whatever is reconstituted from the roar file.
example_mc    // The "Generator" usage tag is used with QQDriverDelivery to access
example_mc    //   just the QQ decay tree before/without the particles added by cleog.
example_mc    // This is only relevant for MC generation when one needs to
example_mc    //   distinguish between the two.
example_mc    FAItem< MCDecayTree > decayTree;
example_mc    extract( iFrame.record( Stream::kEvent ), decayTree );
example_mc 
example_mc    // Some things we can do with the decay tree:
example_mc
example_mc    // A. Let's see what we got
example_mc    //  cout << (*m_decayTree) << endl;
example_mc
example_mc    // B. Iterate over all particles in the tree and count the number
example_mc    //    of Klongs
example_mc
example_mc    // Get access to the underlying MCParticlePropertyStore
example_mc    // (The only way to do this right now)
example_mc    const MCParticlePropertyStore& mcppstore =
example_mc      decayTree->topParticle().properties().store();
example_mc  
example_mc    // For convenience, let's turn the particle name into a QQ Id
example_mc    int qqid1 = mcppstore.nameToQQId("K0L");
example_mc  
example_mc    // And we'll want the charge conjugate as well
example_mc    // (Well, not for Klong, but you might want it for other types
example_mc    //   of particles)
example_mc    int qqid2 = mcppstore.conjugateQQ(qqid1);
example_mc   
example_mc    int numKlong = 0;
example_mc
example_mc    // Now step through all particles in the tree
example_mc    MCPartConstIt treeBegin = decayTree->pBegin();
example_mc    MCPartConstIt treeEnd   = decayTree->pEnd();
example_mc    for( MCPartConstIt partItr = treeBegin; 
example_mc         partItr != treeEnd ; ++partItr )
example_mc    {
example_mc       const MCParticleProperty& partProp = partItr->properties();
example_mc
example_mc       // Print out particle name and it's four-momentum
example_mc       report( INFO, kFacilityString )
example_mc          << "Particle: "
example_mc          << partItr->properties().name()
example_mc          << " (QQ Id: " << partItr->properties().QQId() << ") "
example_mc          << "p4 = " << partItr->lorentzMomentum()
example_mc          << endl;
example_mc
example_mc       // Check if this is a Klong
example_mc       if ((partProp.QQId() == qqid1) || (partProp.QQId() == qqid2))
example_mc       {
example_mc         ++numKlong;
example_mc       }
example_mc    }
example_mc 
example_mc    report( INFO, kFacilityString )
example_mc       << "Number of KL: " << numKlong << endl;
example_mc
example_mc    // C. Look for a B -> X_u l nu decay by iterating over all
example_mc    //    vertices in the decay tree
example_mc
example_mc    // Start/stop
example_mc    MCVertexConstIt vtxBegin = decayTree->vBegin();
example_mc    MCVertexConstIt vtxEnd   = decayTree->vEnd();
example_mc  
example_mc    for (MCVertexConstIt vtx = vtxBegin; vtx != vtxEnd; ++vtx)
example_mc    {
example_mc       // Check if this is (the) signal vertex
example_mc       if (isBXulnu(*vtx))
example_mc       {
example_mc          // Loop over daughters and find the neutrino
example_mc          MCChildConstIt   childEnd = vtx->pEnd();
example_mc          for (MCChildConstIt child = vtx->pBegin();
example_mc               child != childEnd; ++child)
example_mc          {
example_mc             const MCParticleProperty& childProp = child->properties();
example_mc             
example_mc             // Identify the neutrino flavor
example_mc             if (childProp.neutrino())
example_mc             {
example_mc                report( DEBUG, kFacilityString )
example_mc                  << "Found the signal decay. The neutrino is a "
example_mc                  << childProp.name() << endl;
example_mc             }
example_mc          }
example_mc          
example_mc          // Break out of loop since we found what we wanted
example_mc          // You could do whatever else you wanted here instead
example_mc          break;
example_mc       }
example_mc    }
example_histogram
example_histogram    FAItem< DBEventHeader > eventHeader;
example_histogram    extract( iFrame.record( Stream::kEvent ) , eventHeader );
example_histogram
example_histogram    (*m_histo1).fill( (*eventHeader).number() );

example_rich    //Loop over the NavTrack table to get rich info for each track
example_rich    for( FATable< NavTrack >::const_iterator navItrForRich = trackTableBegin; 
example_rich         navItrForRich != trackTableEnd; ++navItrForRich )
example_rich    {
example_rich
example_rich       //Retrieve the rich info associated with the track
example_rich       FAItem<NavRich> richInfo = (*navItrForRich).richInfo();
example_rich
example_rich       if( richInfo.valid() )
example_rich       {
example_rich          //Obtain the likelihood to be a Kaon 
example_rich          double kaonLLikelihood = (*richInfo).kaonLogLikelihood();
example_rich          //Obtain the likelihood to be a Pion
example_rich          double pionLLikelihood = (*richInfo).pionLogLikelihood();
example_rich
example_rich          //if the difference is less than zero, then it is more
example_rich          //likely to be a kaon than a pion
example_rich          double likelihoodToBeKaon = 
example_rich            kaonLLikelihood - pionLLikelihood;
example_rich       }
example_rich     }

example_dedx    //Loop over the NavTrack table to get dedx info for each track
example_dedx    for( FATable< NavTrack >::const_iterator navItrForDedx = trackTableBegin;
example_dedx    	navItrForDedx != trackTableEnd; ++navItrForDedx )
example_dedx    {  
example_dedx        
example_dedx       if( ( (*navItrForDedx).dedxInfo() ).valid() )
example_dedx       { 
example_dedx           FAItem< DedxInfo > dedxInfo( (*navItrForDedx).dedxInfo() );    
example_dedx           double aTruncatedMean = (*dedxInfo).truncatedMean();
example_dedx           //get pion hypothesis info 
example_dedx           double piSigma = (*dedxInfo).piSigma();    
example_dedx
example_dedx           //check the fraction of hits remaining after truncation
example_dedx           double totDedxHits = (*dedxInfo).numOfDedxHits();
example_dedx           double dedxHitsUsed = (*dedxInfo).numOfDedxHitsUsed();
example_dedx
example_dedx           //Expect this number to be about 70%
example_dedx           double fractAfterTruc = dedxHitsUsed/totDedxHits;
example_dedx       }
example_dedx 
example_dedx    }      

example_eventshape    //We need to get the Beam energy to initialize EventShape
example_eventshape    GeV beamEnergy ;
example_eventshape
example_eventshape    FAItem< BeamEnergy > cesrEnergy ;
example_eventshape    extract( iFrame.record( Stream::kStartRun ), cesrEnergy ) ;
example_eventshape    if( cesrEnergy.valid() )
example_eventshape    
example_eventshape    {
example_eventshape       beamEnergy = (*cesrEnergy).value() ;
example_eventshape    }   
example_eventshape    else
example_eventshape    {
example_eventshape       beamEnergy = 5.29 ; 
example_eventshape    }
example_eventshape
example_eventshape    //Initialize Event Shape using the NavTrack Table
example_eventshape    //We do this by making a list of tracks for EventShape
example_eventshape    STL_VECTOR( KTKinematicData ) tracksForEventShape;
example_eventshape
example_eventshape    //Loop over the tracks
example_eventshape    for( FATable< NavTrack >::const_iterator navItrForES = trackTableBegin;
example_eventshape         navItrForES != trackTableEnd; ++navItrForES )
example_eventshape    {
example_eventshape      //Using the pion hypothesis for the tracks
example_eventshape      tracksForEventShape.push_back( *((*navItrForES).pionFit()) );
example_eventshape    }
example_eventshape
example_eventshape    for( FATable< NavShower >::const_iterator showerItrForES = showerBegin; 
example_eventshape         showerItrForES != showerEnd; ++showerItrForES )
example_eventshape    {
example_eventshape       //first check to see that it is an unmatched shower
example_eventshape       if( (*showerItrForES).noTrackMatch() )
example_eventshape       {
example_eventshape 	   tracksForEventShape.push_back( (*showerItrForES).photon() ) ;
example_eventshape       }
example_eventshape    }
example_eventshape
example_eventshape    //Now Pass the list to EventShape
example_eventshape    EventShape eventShape( beamEnergy, tracksForEventShape.begin(), 
example_eventshape      tracksForEventShape.end() ); 
example_eventshape   
example_eventshape    //Now we can get the thrust axis
example_eventshape    Hep3Vector thrustAxis = eventShape.thrust();
example_eventshape   
example_eventshape    //...or R2/R0 
example_eventshape    Count nthMoment = 2; 
example_eventshape    double momentRatio = eventShape.nthFoxWolframMoment( nthMoment ); 
example_dchain 
example_dchain    CDChargedPionList pionList;
example_dchain    CDChargedKaonList kaonList;
example_dchain    CDPhotonList photonList;
example_dchain    CDPi0List pi0List;
example_dchain    CDKsList kShortList;
example_dchain 
example_dchain #if !defined(NO_TEMPLATED_MEMBER_FUNCTIONS_BUG)
example_dchain    pionList = trackTable;
example_dchain    kaonList = trackTable;
example_dchain    photonList = showerTable;
example_dchain    pi0List = pi0Table;
example_dchain    kShortList = kshortTable;
example_dchain #else
example_dchain    dc_fill(pionList, trackTableBegin, trackTableEnd);
example_dchain    dc_fill(kaonList, trackTableBegin,trackTableEnd);
example_dchain    dc_fill(photonList, showerBegin, showerEnd);
example_dchain    dc_fill(pi0List, pi0TableBegin, pi0TableEnd);
example_dchain    dc_fill(kShortList, kshortTableBegin, kshortTableEnd);
example_dchain #endif
example_dchain 
example_dchain    // charge conjugate modes automatically included
example_dchain    CDDecayList KStarPlusList(kStarPlusSelection);
example_dchain    KStarPlusList = kaonList.plus()*photonList;
example_dchain    
example_dchain    CDDecayList DtoKPiList(d0Selection);
example_dchain    DtoKPiList = kaonList.minus()*pionList.plus();
example_dchain 
example_dchain    CDDecayList DtoKPiPi0List(d0Selection);
example_dchain    DtoKPiPi0List = kaonList.minus()*pionList.plus()*pi0List;
example_dchain 
example_dchain    CDDecayList DtoK0PiPiList(d0Selection);
example_dchain    DtoK0PiPiList = kShortList*pionList.plus()*pionList.minus();
example_dchain 
example_dchain    // have to make sure we have charge of slow pion right!
example_dchain    CDDecayList DStarList(dStarSelection);
example_dchain    DStarList = DtoKPiList*pionList.plus();
example_dchain 
example_dchain    // example of looping over dchain candidates
example_dchain    CDDecayList::iterator dStarEnd = DStarList.particle_end();
example_dchain    CDDecayList::iterator dStar = DStarList.particle_begin();
example_dchain    for( ; dStar != dStarEnd; ++dStar )
example_dchain    {
example_dchain       const CDDecay& dStarCand = (*dStar).particle();
example_dchain       double dStarMass = dStarCand.mass();
example_dchain       HepVector3D threeMomentum = dStarCand.momentum();
example_dchain       const CDDecay& d0 = dStarCand.child(DCChildren::First).decay();
example_dchain       double dMass = d0.mass();
example_dchain       double massDifference = dStarMass - dMass;
example_dchain       const NavTrack& slowpi =
example_dchain          dStarCand.child(DCChildren::Second).track();
example_dchain       const NavTrack& kaon = d0.child(DCChildren::First).track();
example_dchain       const NavTrack& pion = d0.child(DCChildren::Second).track();
example_dchain       float tuple[kDStarNum];
example_dchain       tuple[kDMass] = dMass;
example_dchain       tuple[kDStarMass] = dStarMass;
example_dchain       tuple[kDMom] = d0.momentum().mag();
example_dchain       m_dStarNtuple->fill(tuple);
example_dchain    }
example_tuple_tuplevector    example= myTuple;
example_tuple_tuplevector    //fill myTuple here
example_tuple_tuplevector
example_tuple    m_example=Inserter.insert(new example=(myTuple) );
example_tuplevector    //copy this entry to our list
example_tuplevector    m_example=List.push_back(myTuple);
example_tuplevector
example_tuplevector    //put this list into the Frame
example_tuplevector    // NOTE: in constructor told inserter not to delete
example_tuplevector    m_example=Inserter.insert( &m_example=List );
   return ActionBase::kPassed;
}

/*
ActionBase::ActionResult
procname::beginRun( Frame& iFrame )       // anal2 equiv.
{
   report( DEBUG, kFacilityString ) << "here in beginRun()" << endl;

   return ActionBase::kPassed;
}
*/

/*
ActionBase::ActionResult
procname::endRun( Frame& iFrame )         // anal4 equiv.
{
   report( DEBUG, kFacilityString ) << "here in endRun()" << endl;

   return ActionBase::kPassed;
}
*/

//
// const member functions
//

//
// static member functions
//
