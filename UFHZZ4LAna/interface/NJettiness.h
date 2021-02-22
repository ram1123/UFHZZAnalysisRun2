// For additional jet veto
// Reference: PRL 105, 092002 (2010)
// Implementing equation number 9 from the above paper.

#ifndef NJETTINESS_H
#define NJETTINESS_H
class NJettiness {
public:

	NJettiness();
	~NJettiness();
	
    double GeneralizedTaunN(edm::Handle<pat::PackedCandidateCollection> pfcands, edm::Handle<edm::View<pat::Jet> > jets, Q, Y);
};

#endif

#ifndef NJETTINESS_CC
#define NJETTINESS_CC

NJettiness::GeneralizedTaunN(edm::Handle<pat::PackedCandidateCollection> pfcands, edm::Handle<edm::View<pat::Jet> > jets, Q, Y)
{
    // FIXME: Remember to remove the selected particles from the collection of pfCandidates.
    for (const pat::PackedCandidate &pfc : *pfcands)
    {
        double dA = (pfc.pt()*TMath::Exp(Y-pfc.eta()))/Q;
        double dB = (pfc.pt()*TMath::Exp(-Y+pfc.eta()))/Q;

        double tauN = TMath::Min(dA,dB)

        for (const pat::Jet &jet : *jets)
        {
            double dEta = pfc.eta() - jet.eta();
            double dPhi = pfc.phi() - jet.phi();
            double dJ = ( pfc.pt() * ( 2*TMath::CosH(dEta) - 2*TMath::Cos(dPhi) ) )/Q;
            tauN = TMath::Min(tauN, dJ)
        }   // END: for (const pat::Jet &jet : *jets)
    }   // END: for (const pat::PackedCandidate &pfc : *pfcands)

    return tauN;
}
#endif