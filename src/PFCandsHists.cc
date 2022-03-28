#include "LEAF/VBFTagger/include/PFCandsHists.h"

using namespace std;

PFCandsHists::PFCandsHists(TString dir_, TString selection_) : BaseHists(dir_), selection(selection_) {

  for ( const ParticleType& type : types) { type_names.push_back(type2str(type)); type_numbers.push_back(0);}
  size_t n_types = type_names.size();

  book<TH1F>("sumweights",            ";sum of event weights; Events / bin",      1,  0.5, 1.5);
  book<TH1F>("number_pf_cands",       ";number of pf cands ; Events / bin",     101,  100., 1000);

  book<TH1F>("pf_cand_pt",            ";p_{T}; Events / bin",                   2000,  0., 500);
  book<TH1F>("pf_cand_eta",           ";#eta; Events / bin",                    100, -5., 5.);
  book<TH1F>("pf_cand_phi",           ";#phi; Events / bin",                    70, -3.5, 3.5);
  book<TH1F>("pf_cand_m",             ";mass; Events / bin",                    50,   0., 2);
  book<TH1F>("pf_cand_e",             ";Energy; Events / bin",                  50,   0., 1500);
  book<TH1F>("pf_cand_charge",        ";charge; Events / bin",                  3,  -1.5, 1.5);

  book<TH1F>("pf_cand_type",          ";type; Events / bin",                    types.size(), 0, types.size());
  book<TH1F>("pf_cand_puppi_w",       ";puppi weight; Events / bin",            10,  0., 1.);
  book<TH1F>("pf_cand_puppi_w_nolep", ";puppi weight (no lep.); Events / bin",  10,  0., 1.);

  book<TH1F>("pf_cand_calo_frac",     ";calo. frac.; Events / bin",             100,  0, 1);
  book<TH1F>("pf_cand_hcal_frac",     ";hcal. frac.; Events / bin",             100,  0, 1);
  book<TH1F>("pf_cand_is_iso_ch_had", ";IsIsoChHad; Events / bin",                2,  0, 2);

  book<TH1F>("pf_cand_dz",            ";dz; Events / bin",                      102,  -0.01, 1.01);
  book<TH1F>("pf_cand_dxy",           ";dxy; Events / bin",                     102,  -0.01, 1.01);

  book<TH1F>("pf_cand_dz_err",        ";dz^{err}; Events / bin",                300,  -1, 2);
  book<TH1F>("pf_cand_dxy_err",       ";dxy_{err}; Events / bin",               300,  -1, 2);

  book<TH1F>("pf_cand_vertex_x",      ";ass. vertex pos(x); Events / bin",      500,  -1,   1);
  book<TH1F>("pf_cand_vertex_y",      ";ass. vertex pos(y); Events / bin",      500,  -1,   1);
  book<TH1F>("pf_cand_vertex_z",      ";ass. vertex pos(z); Events / bin",      400,  -20, 20);

  book<TH2F>("number_pf_cands_vs_type",       ";number of pf cands ; type",     101,  100., 1000, types.size(), 0, types.size());
  book<TH2F>("pf_cand_pt_vs_type",            ";p_{T}; type",                          2000,  0., 500, types.size(), 0, types.size());
  book<TH2F>("pf_cand_eta_vs_type",           ";#eta; type",                            100, -5., 5., types.size(), 0, types.size());
  book<TH2F>("pf_cand_phi_vs_type",           ";#phi; type",                             70, -3.5, 3.5, types.size(), 0, types.size());
  book<TH2F>("pf_cand_m_vs_type",             ";mass; type",                             50,   0., 2, types.size(), 0, types.size());
  book<TH2F>("pf_cand_e_vs_type",             ";Energy; type",                           50,   0., 1500, types.size(), 0, types.size());
  book<TH2F>("pf_cand_charge_vs_type",        ";charge; type",                            3,  -1.5, 1.5, types.size(), 0, types.size());
  book<TH2F>("pf_cand_puppi_w_vs_type",       ";puppi weight; type",                     10,  0., 1., types.size(), 0, types.size());
  book<TH2F>("pf_cand_puppi_w_nolep_vs_type", ";puppi weight (no lep.); type",           10,  0., 1., types.size(), 0, types.size());
  book<TH2F>("pf_cand_calo_frac_vs_type",     ";calo. frac.; type",                     100,  0, 1, types.size(), 0, types.size());
  book<TH2F>("pf_cand_hcal_frac_vs_type",     ";hcal. frac.; type",                     100,  0, 1, types.size(), 0, types.size());
  book<TH2F>("pf_cand_is_iso_ch_had_vs_type", ";IsIsoChHad; type",                        2,  0, 2, types.size(), 0, types.size());
  book<TH2F>("pf_cand_dz_vs_type",            ";dz; type",                              102,  -0.01, 1.01, types.size(), 0, types.size());
  book<TH2F>("pf_cand_dxy_vs_type",           ";dxy; type",                             102,  -0.01, 1.01, types.size(), 0, types.size());
  book<TH2F>("pf_cand_dz_err_vs_type",        ";dz^{err}; type",                        300,  -1, 2, types.size(), 0, types.size());
  book<TH2F>("pf_cand_dxy_err_vs_type",       ";dxy_{err}; type",                       300,  -1, 2, types.size(), 0, types.size());
  book<TH2F>("pf_cand_vertex_x_vs_type",      ";ass. vertex pos(x); type",              500,  -1,   1, types.size(), 0, types.size());
  book<TH2F>("pf_cand_vertex_y_vs_type",      ";ass. vertex pos(y); type",              500,  -1,   1, types.size(), 0, types.size());
  book<TH2F>("pf_cand_vertex_z_vs_type",      ";ass. vertex pos(z); type",              400,  -20, 20, types.size(), 0, types.size());


  for(size_t i=1; i<=n_types; i++) {
    hist<TH1F>("pf_cand_type")->GetXaxis()->SetBinLabel(i,type_names[i-1].c_str());
    for ( const auto& name : {"pt", "eta", "phi", "m", "e", "charge", "puppi_w", "puppi_w_nolep", "calo_frac", "hcal_frac", "is_iso_ch_had", "dz", "dxy", "dz_err", "dxy_err", "vertex_x", "vertex_y", "vertex_z"}){
      TString name_ = "pf_cand_"; name_+= name; name_ += "_vs_type";
      hist<TH2F>(name_)->GetYaxis()->SetBinLabel(i,type_names[i-1].c_str());
    }
  }

  // jetidx

}

void PFCandsHists::fill(const RecoEvent & event){
  double weight = event.weight;
  hist<TH1F>("sumweights")->Fill(1, weight);
  hist<TH1F>("number_pf_cands")->Fill(event.pfcands->size(), weight);

  type_numbers.clear();

  for(size_t i=0; i<type_names.size(); i++) type_numbers[i] = 0;

  for(const PFCandidate& cand: *event.pfcands){
    // float pfweight = cand.puppiweight();
    float pfweight = 1;

    if (selection=="pt>1" && (cand.pt()*pfweight)<1) continue;

    string type = type2str(fabs(cand.type()));
    for(size_t i=0; i<type_names.size(); i++) {if (type==type_names[i]) type_numbers[i]+=1;}

    hist<TH1F>("pf_cand_pt")->Fill(cand.pt()*pfweight, weight);
    hist<TH1F>("pf_cand_eta")->Fill(cand.eta()*pfweight, weight);
    hist<TH1F>("pf_cand_phi")->Fill(cand.phi()*pfweight, weight);
    hist<TH1F>("pf_cand_m")->Fill(cand.m()*pfweight, weight);
    hist<TH1F>("pf_cand_e")->Fill(cand.e()*pfweight, weight);
    hist<TH1F>("pf_cand_charge")->Fill(cand.charge(), weight);

    hist<TH1F>("pf_cand_type")->Fill(type.c_str(), weight);

    hist<TH1F>("pf_cand_puppi_w")->Fill(cand.puppiweight(), weight);
    hist<TH1F>("pf_cand_puppi_w_nolep")->Fill(cand.puppiweight_nolep(), weight);
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

    hist<TH2F>("pf_cand_pt_vs_type")->Fill(cand.pt()*pfweight, type.c_str(), weight);
    hist<TH2F>("pf_cand_eta_vs_type")->Fill(cand.eta()*pfweight, type.c_str(), weight);
    hist<TH2F>("pf_cand_phi_vs_type")->Fill(cand.phi()*pfweight, type.c_str(), weight);
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
    hist<TH2F>("number_pf_cands_vs_type")->Fill(type_numbers[i], type_names[i].c_str(), weight);
  }

}
