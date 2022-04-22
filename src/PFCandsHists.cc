#include "LEAF/VBFTagger/include/PFCandsHists.h"

using namespace std;

PFCandsHists::PFCandsHists(TString dir_, TString selection_) : BaseHists(dir_), selection(selection_) {

  for ( const ParticleType& type : types) { type_names.push_back(type2str(type));}
  size_t n_types = type_names.size();

  bool isLowpt = FindInString("pt>0.2", selection.Data());

  book<TH1F>("sumweights",            ";sum of event weights; Events / bin",     1,      0.5,      1.5);
  book<TH1F>("n_pfcands",             ";number of pf cands ; Events / bin",    100,      0.,    (selection=="")? 1000: 100);
  book<TH1F>("n_pfcands_density",     ";density of pf cands ; Events / bin",    60,      0.,     isLowpt? 100: 30);
  book<TH1F>("n_pfcands_density2",    ";density of pf cands ; Events / bin",    60,      0.,     isLowpt? 100: 30);
  book<TH1F>("n_pfcands_density3",    ";density of pf cands ; Events / bin",    10,      0.,      30);
  book<TH1F>("n_charged_pfcands",     ";# charged pf cands ; Events / bin",     50,      0.,    (selection=="")? 1000: 50);
  book<TH1F>("n_neutral_pfcands",     ";# neutral pf cands ; Events / bin",     50,      0.,    (selection=="")? 1000: 50);
  book<TH1F>("UEin_UEout_ratio",      ";UEin/UEout; Events / bin",              20,      0.,      0.5);

  book<TH1F>("HT_pfcands",            ";H_{T} from PF; Events / bin",          150,      0.,    1500);

  book<TH1F>("pf_cand_pt",            ";p_{T}; Events / bin",                  150,      0.,      30);
  book<TH1F>("pf_cand_eta",           ";#eta; Events / bin",                   100,     -5.,       5.);
  book<TH1F>("pf_cand_phi",           ";#phi; Events / bin",                    70,     -3.5,      3.5);
  book<TH1F>("pf_cand_m",             ";mass; Events / bin",                    50,      0.,       2);
  book<TH1F>("pf_cand_e",             ";Energy; Events / bin",                  50,      0.,     500);
  book<TH1F>("pf_cand_charge",        ";charge; Events / bin",                   3,     -1.5,      1.5);

  book<TH1F>("pf_cand_type",          ";type; Events / bin",               n_types,      0,  n_types);
  book<TH1F>("pf_cand_puppi_w",       ";puppi weight; Events / bin",            20,      0.,       1.);
  book<TH1F>("pf_cand_puppi_w_nolep", ";puppi weight (no lep.); Events / bin",  20,      0.,       1.);
  book<TH1F>("pf_cand_fromPV",        ";fromPV ; Events / bin",                  4,     -0.5,      3.5);

  book<TH1F>("pf_cand_calo_frac",     ";calo. frac.; Events / bin",             20,      0,        1);
  book<TH1F>("pf_cand_hcal_frac",     ";hcal. frac.; Events / bin",             20,      0,        1);
  book<TH1F>("pf_cand_is_iso_ch_had", ";IsIsoChHad; Events / bin",               2,      0,        2);

  book<TH1F>("pf_cand_dz",            ";dz; Events / bin",                     100,     -0.10,     0.10);
  book<TH1F>("pf_cand_dxy",           ";dxy; Events / bin",                    100,     -0.10,     0.10);

  book<TH1F>("pf_cand_dz_err",        ";dz^{err}; Events / bin",                50,      0,        0.05);
  book<TH1F>("pf_cand_dxy_err",       ";dxy_{err}; Events / bin",               50,      0,        0.05);

  book<TH1F>("pf_cand_vertex_x",      ";ass. vertex pos(x); Events / bin",     500,     -1,        1);
  book<TH1F>("pf_cand_vertex_y",      ";ass. vertex pos(y); Events / bin",     500,     -1,        1);
  book<TH1F>("pf_cand_vertex_z",      ";ass. vertex pos(z); Events / bin",     400,    -20,       20);

  book<TH1F>("pf_cand_DR_from_jet",   ";DR from tagged jet; Events / bin",     160,      0,        8);
  book<TH1F>("Zeppenfeld1",           ";Zeppenfeld1; Events / bin",            100,      0,       10);
  book<TH1F>("Zeppenfeld2",           ";Zeppenfeld2; Events / bin",             50,      0,        5);
  book<TH1F>("Zeppenfeld3",           ";Zeppenfeld3; Events / bin",             50,      0,        5);

  book<TH2F>("pf_cand_pt_vs_eta",             ";p_{T}; #eta",                   50,      0.,      50,      100,    -5.,       5.);
  book<TH2F>("pf_cand_eta_vs_phi",            ";#eta; #phi",                   100,     -5.,       5.,      70,    -3.5,      3.5);


  book<TH2F>("n_pfcands_vs_type",       ";number of pf cands ; type",          100,      0.,   10000,    n_types,    0,  n_types);
  book<TH2F>("HT_pfcands_vs_type",            ";H_{T} from PF ; type",         100,      0.,   10000,    n_types,    0,  n_types);

  book<TH2F>("pf_cand_pt_vs_type",            ";p_{T}; type",                   50,      0.,      50,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_eta_vs_type",           ";#eta; type",                   100,     -5.,       5.,   n_types,    0,  n_types);
  book<TH2F>("pf_cand_phi_vs_type",           ";#phi; type",                    70,     -3.5,      3.5,  n_types,    0,  n_types);
  book<TH2F>("pf_cand_m_vs_type",             ";mass; type",                    50,      0.,       2,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_e_vs_type",             ";Energy; type",                  50,      0.,     500,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_charge_vs_type",        ";charge; type",                   3,     -1.5,      1.5,  n_types,    0,  n_types);
  book<TH2F>("pf_cand_puppi_w_vs_type",       ";puppi weight; type",            20,      0.,       1.,   n_types,    0,  n_types);
  book<TH2F>("pf_cand_puppi_w_nolep_vs_type", ";puppi weight (no lep.); type",  20,      0.,       1.,   n_types,    0,  n_types);
  book<TH2F>("pf_cand_calo_frac_vs_type",     ";calo. frac.; type",             20,      0.,       1,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_hcal_frac_vs_type",     ";hcal. frac.; type",             20,      0.,       1,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_is_iso_ch_had_vs_type", ";IsIsoChHad; type",               2,      0.,       2,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_dz_vs_type",            ";dz; type",                     100,     -0.10,     0.10, n_types,    0,  n_types);
  book<TH2F>("pf_cand_dxy_vs_type",           ";dxy; type",                    100,     -0.10,     0.10, n_types,    0,  n_types);
  book<TH2F>("pf_cand_dz_err_vs_type",        ";dz^{err}; type",                50,      0,        0.05, n_types,    0,  n_types);
  book<TH2F>("pf_cand_dxy_err_vs_type",       ";dxy_{err}; type",               50,      0,        0.05, n_types,    0,  n_types);
  book<TH2F>("pf_cand_vertex_x_vs_type",      ";ass. vertex pos(x); type",     500,     -1.,       1,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_vertex_y_vs_type",      ";ass. vertex pos(y); type",     500,     -1.,       1,    n_types,    0,  n_types);
  book<TH2F>("pf_cand_vertex_z_vs_type",      ";ass. vertex pos(z); type",     400,     -20.,     20,    n_types,    0,  n_types);


  for(size_t i=1; i<=n_types; i++) {
    hist<TH1F>("pf_cand_type")->GetXaxis()->SetBinLabel(i,type_names[i-1].c_str());
    for ( const auto& name : {"pt", "eta", "phi", "m", "e", "charge", "puppi_w", "puppi_w_nolep", "calo_frac", "hcal_frac", "is_iso_ch_had", "dz", "dxy", "dz_err", "dxy_err", "vertex_x", "vertex_y", "vertex_z"}){
      TString name_ = "pf_cand_"; name_+= name; name_ += "_vs_type";
      hist<TH2F>(name_)->GetYaxis()->SetBinLabel(i,type_names[i-1].c_str());
    }
  }

  // jetidx

}

void PFCandsHists::fill(const VBFTaggerEvent & event){

  int n_pfcands = 0;
  int n_pfcands2 = 0;
  int n_charged_pfcands = 0;
  int n_neutral_pfcands = 0;
  int n_UEin = 0;
  int n_UEout = 0;

  double HT_total = 0;
  vector<float> type_numbers;
  vector<float> HTs;

  for(size_t i=0; i<type_names.size(); i++) {
    HTs.push_back(0);
    type_numbers.push_back(0);
  }

  if (event.jets_ak4chs->size()<2) return;


  double weight = event.weight;
  float eta_min, eta_max, dEta_jets, dEta_jets2, eta_average, dEta_jets3 = 0.8;
  Jet jet1 = event.jets_ak4chs->at(0);
  Jet jet2 = event.jets_ak4chs->at(1);
  hist<TH1F>("sumweights")->Fill(1, weight);

  if (FindInString("UE", selection.Data())){
    if (event.identifier_VBFjet1()<0) return;
    if (event.identifier_VBFjet2()<0) return;
    for(unsigned index = 0; index < event.jets_ak4chs->size(); index++ ) {
      if(event.jets_ak4chs->at(index).identifier()== event.identifier_VBFjet1()) {
        jet1 = event.jets_ak4chs->at(index);
      }
      if(event.jets_ak4chs->at(index).identifier()== event.identifier_VBFjet2()) {
        jet2 = event.jets_ak4chs->at(index);
      }
    }
  }

  eta_min = std::min(jet1.eta(), jet2.eta());
  eta_max = std::max(jet1.eta(), jet2.eta());
  dEta_jets = deltaEta(jet1, jet2);
  dEta_jets2 = FindInString("UEout", selection.Data())? 5.2*2-dEta_jets: dEta_jets;
  eta_average = (eta_min+eta_max)/2;

  for(const PFCandidate& cand: *event.pfcands){
    // float pfweight = cand.puppiweight();
    float pfweight = 1;

    double DR_from_tagged_jet = -1;
    double pt_pfcand = cand.pt()*pfweight;

    if (FindInString("pt>1",   selection.Data()) && (pt_pfcand)<1)   continue;
    if (FindInString("pt>0.2", selection.Data()) && (pt_pfcand)<0.2) continue;

    float dR1 = deltaR(cand, jet1);
    float dR2 = deltaR(cand, jet2);
    if (dR1<0.4 || dR2<0.4) continue;

    bool is_within;
    if (eta_min+0.4 < cand.eta() && cand.eta() < eta_max-0.4) is_within = true;
    if (eta_min-0.4 > cand.eta() || cand.eta() > eta_max+0.4) is_within = false;

    if (FindInString("UE", selection.Data())) {
      DR_from_tagged_jet = std::min(dR1, dR2);
      if (FindInString("UEin", selection.Data()) && !is_within) continue;
      if (FindInString("UEout", selection.Data()) && is_within)  continue;
    }

    if (FindInString("charge!=0", selection.Data()) && cand.charge()==0) continue;
    if (FindInString("charge==0", selection.Data()) && cand.charge()!=0) continue;

    if (FindInString("fromPV==0", selection.Data()) && cand.fromPV()!=0) continue;
    if (FindInString("fromPV==1", selection.Data()) && cand.fromPV()!=1) continue;
    if (FindInString("fromPV==2", selection.Data()) && cand.fromPV()!=2) continue;
    if (FindInString("fromPV==3", selection.Data()) && cand.fromPV()!=3) continue;

    if (is_within) n_UEin += 1;
    else n_UEout += 1;

    n_pfcands += 1;
    if (fabs(eta_average-cand.eta())<dEta_jets3) n_pfcands2 +=1;
    if (cand.charge()==0) n_neutral_pfcands += 1;
    else n_charged_pfcands += 1;

    float Zeppenfeld = fabs(cand.eta()-(jet1.eta()+jet2.eta())/2);
    HT_total += pt_pfcand;

    string type = type2str(fabs(cand.type()));
    for(size_t i=0; i<type_names.size(); i++) {
      if (type==type_names[i]) {
        type_numbers[i]+=1;
        HTs[i]+= pt_pfcand;
      }
    }

    hist<TH1F>("pf_cand_pt")->Fill(pt_pfcand, weight);
    hist<TH1F>("pf_cand_eta")->Fill(cand.eta(), weight);
    hist<TH1F>("pf_cand_phi")->Fill(cand.phi(), weight);
    hist<TH1F>("pf_cand_m")->Fill(cand.m()*pfweight, weight);
    hist<TH1F>("pf_cand_e")->Fill(cand.e()*pfweight, weight);
    hist<TH1F>("pf_cand_charge")->Fill(cand.charge(), weight);

    hist<TH1F>("pf_cand_type")->Fill(type.c_str(), weight);

    hist<TH1F>("pf_cand_puppi_w")->Fill(cand.puppiweight(), weight);
    hist<TH1F>("pf_cand_puppi_w_nolep")->Fill(cand.puppiweight_nolep(), weight);
    hist<TH1F>("pf_cand_fromPV")->Fill(cand.fromPV(), weight);
    hist<TH1F>("pf_cand_calo_frac")->Fill(cand.calo_frac(), weight);
    hist<TH1F>("pf_cand_hcal_frac")->Fill(cand.hcal_frac(), weight);
    hist<TH1F>("pf_cand_is_iso_ch_had")->Fill(cand.is_iso_ch_had(), weight);
    hist<TH1F>("pf_cand_dz")->Fill(cand.dz(), weight);
    hist<TH1F>("pf_cand_dxy")->Fill(cand.dxy(), weight);
    hist<TH1F>("pf_cand_dz_err")->Fill(cand.dz_err(), weight);
    hist<TH1F>("pf_cand_dxy_err")->Fill(cand.dxy_err(), weight);
    hist<TH1F>("pf_cand_vertex_x")->Fill(cand.vertex_x(), weight);
    hist<TH1F>("pf_cand_vertex_y")->Fill(cand.vertex_y(), weight);
    hist<TH1F>("pf_cand_vertex_z")->Fill(cand.vertex_z(), weight);

    hist<TH1F>("pf_cand_DR_from_jet")->Fill(DR_from_tagged_jet, weight);
    hist<TH1F>("Zeppenfeld1")->Fill(Zeppenfeld, weight);
    hist<TH1F>("Zeppenfeld2")->Fill(Zeppenfeld/dEta_jets, weight);
    hist<TH1F>("Zeppenfeld3")->Fill(Zeppenfeld/dEta_jets2, weight);

    hist<TH2F>("pf_cand_pt_vs_eta")->Fill(pt_pfcand, cand.eta(), weight);
    hist<TH2F>("pf_cand_eta_vs_phi")->Fill(cand.eta(), cand.phi(), weight);

    hist<TH2F>("pf_cand_pt_vs_type")->Fill(pt_pfcand, type.c_str(), weight);
    hist<TH2F>("pf_cand_eta_vs_type")->Fill(cand.eta(), type.c_str(), weight);
    hist<TH2F>("pf_cand_phi_vs_type")->Fill(cand.phi(), type.c_str(), weight);
    hist<TH2F>("pf_cand_m_vs_type")->Fill(cand.m()*pfweight, type.c_str(), weight);
    hist<TH2F>("pf_cand_e_vs_type")->Fill(cand.e()*pfweight, type.c_str(), weight);
    hist<TH2F>("pf_cand_charge_vs_type")->Fill(cand.charge(), type.c_str(), weight);
    hist<TH2F>("pf_cand_puppi_w_vs_type")->Fill(cand.puppiweight(), type.c_str(), weight);
    hist<TH2F>("pf_cand_puppi_w_nolep_vs_type")->Fill(cand.puppiweight_nolep(), type.c_str(), weight);
    hist<TH2F>("pf_cand_calo_frac_vs_type")->Fill(cand.calo_frac(), type.c_str(), weight);
    hist<TH2F>("pf_cand_hcal_frac_vs_type")->Fill(cand.hcal_frac(), type.c_str(), weight);
    hist<TH2F>("pf_cand_is_iso_ch_had_vs_type")->Fill(cand.is_iso_ch_had(), type.c_str(), weight);
    hist<TH2F>("pf_cand_dz_vs_type")->Fill(cand.dz(), type.c_str(), weight);
    hist<TH2F>("pf_cand_dxy_vs_type")->Fill(cand.dxy(), type.c_str(), weight);
    hist<TH2F>("pf_cand_dz_err_vs_type")->Fill(cand.dz_err(), type.c_str(), weight);
    hist<TH2F>("pf_cand_dxy_err_vs_type")->Fill(cand.dxy_err(), type.c_str(), weight);
    hist<TH2F>("pf_cand_vertex_x_vs_type")->Fill(cand.vertex_x(), type.c_str(), weight);
    hist<TH2F>("pf_cand_vertex_y_vs_type")->Fill(cand.vertex_y(), type.c_str(), weight);
    hist<TH2F>("pf_cand_vertex_z_vs_type")->Fill(cand.vertex_z(), type.c_str(), weight);
  }

  for(size_t i=0; i<type_names.size(); i++) {
    hist<TH2F>("n_pfcands_vs_type")->Fill(type_numbers[i], type_names[i].c_str(), weight);
    hist<TH2F>("HT_pfcands_vs_type")->Fill(HTs[i], type_names[i].c_str(), weight);
  }

  hist<TH1F>("n_pfcands")->Fill(n_pfcands, weight);
  hist<TH1F>("n_pfcands_density")->Fill(n_pfcands/dEta_jets, weight);
  hist<TH1F>("n_pfcands_density2")->Fill(n_pfcands/dEta_jets2, weight);
  hist<TH1F>("n_pfcands_density3")->Fill(n_pfcands2/dEta_jets3, weight);
  hist<TH1F>("n_neutral_pfcands")->Fill(n_neutral_pfcands, weight);
  hist<TH1F>("n_charged_pfcands")->Fill(n_charged_pfcands, weight);
  hist<TH1F>("UEin_UEout_ratio")->Fill((n_UEout!=0)? 1.*n_UEin/n_UEout: -1, weight);

  hist<TH1F>("HT_pfcands")->Fill(HT_total, weight);

}
