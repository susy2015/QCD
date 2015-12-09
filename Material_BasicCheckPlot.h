TH1* merge_hist_list(const TList& hists)
{
  TIter next(hists.MakeIterator());
  TH1* hist = NULL;
  TH1* res = NULL;
  int icount = 0;
  while ((hist = (TH1*) next()))
  {
    if(icount == 0)
    {
      res = (TH1*) hist->Clone("my_all");
    }
    else
    {
      res->Add(hist);
    }
  }
  return res;
}

TH1* merge_stack(const THStack& stack)
{
  TList* hists = stack.GetHists();
  return merge_hist_list(*hists);
}

TPad* BasicCheckHistgram::add_ratio_pad(TH1* h_signal, const TList& h_bkgs)
{
  TPad* pad1 = new TPad("pad1","pad1",0, 0.15,1.00,1.00);
  pad1->SetBottomMargin(0.161);
  TPad* pad2 = new TPad("pad2","pad2",0., 0.010, 1.00, 0.286);
  pad2->SetBottomMargin(0.28);
  pad1->Draw();
  pad2->Draw();

  // plot the ratio
  pad2->cd();
  // cout << "background size: " << h_bkgs.GetSize() << endl;
  TIter next(h_bkgs.MakeIterator());
  TH1F* h_bkg = NULL;
  int icount = 0;
  while ((h_bkg = (TH1F*) next()))
  {
    TH1F* h_copy = (TH1F*) h_bkg->Clone(Form("r_%s", h_bkg->GetName()));
    if(!h_copy->GetDefaultSumw2())  h_copy->Sumw2();
    h_copy->Divide(h_signal);
    h_copy->SetMarkerSize(0.02);
    h_copy->SetMarkerColor(h_bkg->GetMarkerColor());
    h_copy->SetLineColor(h_bkg->GetLineColor());
    if(icount == 0)
    {
      h_copy->GetYaxis()->SetRangeUser(0.5, 1.5);
      h_copy->GetYaxis()->SetNdivisions(7);
      h_copy->GetYaxis()->SetLabelSize(0.1);
      h_copy->GetYaxis()->SetTitleSize(0.15);
      h_copy->GetYaxis()->SetTitle("Ratio");
      h_copy->GetYaxis()->SetTitleOffset(0.3);
      h_copy->GetXaxis()->SetLabelSize(0.1);
      h_copy->GetXaxis()->SetTitleSize(0.15);
      h_copy->GetXaxis()->SetTitleOffset(0.78);
      h_copy->Draw("HIST");
      icount ++;
    }
    else
    {
      h_copy->Draw("HIST SAME");
    }
  }
  //AddLine(h_signal, 1);
  // plot the comparison
  pad1->cd();
  return pad1;
}

TPad* BasicCheckHistgram::add_ratio_pad(TH1* h_signal, TH1* h_bkg )
{
  TList* list = new TList();
  list->Add(h_bkg);
  TPad* res = add_ratio_pad(h_signal, *list);
  delete list;
  return res;
}

void BasicCheckHistgram::BasicCheckPlotsGen()
{
  TLegend* leg = new TLegend(0.6,0.75,0.85,0.85);
  leg->AddEntry(h_b_met_Data,"Data","l");

  for( Int_t i = 0 ; i < BCBin ; i++ )
  {
    hs_b_met_MC->Add(h_b_met_MC[i]);
    hs_b_mt2_MC->Add(h_b_mt2_MC[i]);
    hs_b_ntopjets_MC->Add(h_b_ntopjets_MC[i]);
    hs_b_nbjets_MC->Add(h_b_nbjets_MC[i]);
    hs_b_ht_MC->Add(h_b_ht_MC[i]);
    hs_b_mht_MC->Add(h_b_mht_MC[i]);
    hs_b_njets_MC->Add(h_b_njets_MC[i]);

    std::string smalltag;
    if (i == 0) smalltag = "LLHadTau";
    else if (i == 1) smalltag = "Zinv";
    else if (i == 2) smalltag = "QCD";
    else smalltag = "TTZ";

    leg->AddEntry(h_b_met_MC[i],smalltag.c_str(),"l");
  }

  std::ostringstream strs;
  strs << (LUMI/1000);
  std::string lumi_str = strs.str();
  const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";

  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  TCanvas *c = new TCanvas("c", "c",0,51,1920,1004);
  c->SetFillColor(0);
  c->Divide(2,2);
  gStyle->SetOptStat(0);
  //gStyle->SetPaintTextFormat("1.2f");
  std::cout << "123" << std::endl;

  c->cd(1);
  add_ratio_pad( h_b_met_Data, merge_stack( *hs_b_met_MC ) );
  h_b_met_Data->Draw("p");
  hs_b_met_MC->Draw("same hist");
  title->Draw("same");
  leg->Draw("same");

  std::cout << "456" << std::endl;

  c->cd(2);
  add_ratio_pad( h_b_mt2_Data, merge_stack( *hs_b_mt2_MC ) );
  h_b_mt2_Data->Draw("p");
  hs_b_mt2_MC->Draw("same hist");
  title->Draw("same");
  leg->Draw("same");

  c->cd(3);
  add_ratio_pad( h_b_ntopjets_Data, merge_stack( *hs_b_ntopjets_MC ) );
  h_b_ntopjets_Data->Draw("p");
  hs_b_ntopjets_MC->Draw("same hist");
  title->Draw("same");
  leg->Draw("same");

  c->cd(4);
  //add_ratio_pad( h_b_nbjets_Data, merge_stack( *hs_b_nbjets_MC ) );
  h_b_nbjets_Data->Draw("p");
  hs_b_nbjets_MC->Draw("same hist");
  title->Draw("same");
  leg->Draw("same");

  c->SaveAs( "_BasicCheck_sb.png" );
  c->SaveAs( "_BasicCheck_sb.pdf" );
  c->SaveAs( "_BasicCheck_sb.C" );
  c->Close();

  return ;
}


  hs_b_met_MC = new THStack("hs_b_met_MC","");
  hs_b_mt2_MC = new THStack("hs_b_mt2_MC","");
  hs_b_ntopjets_MC = new THStack("hs_b_ntopjets_MC","");
  hs_b_nbjets_MC = new THStack("hs_b_nbjets_MC","");
  hs_b_ht_MC = new THStack("hs_b_ht_MC","");
  hs_b_mht_MC = new THStack("hs_b_mht_MC","");
  hs_b_njets_MC = new THStack("hs_b_njets_MC","");

  THStack *hs_b_met_MC, *hs_b_mt2_MC, *hs_b_ntopjets_MC, *hs_b_nbjets_MC;;
  THStack *hs_b_ht_MC, *hs_b_mht_MC, *hs_b_njets_MC;


