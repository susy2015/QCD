void _nbjets()
{
//=========Macro generated from canvas: c/
//=========  (Mon Feb 13 05:57:22 2017) by ROOT version6.06/01
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: 
   TPad *pad = new TPad("", "",0,0.2,1,1);
   pad->Draw();
   pad->cd();
   pad->Range(-0.625,0,5.625,519.383);
   pad->SetFillColor(0);
   pad->SetBorderMode(0);
   pad->SetBorderSize(5);
   pad->SetBottomMargin(0);
   pad->SetFrameBorderMode(0);
   pad->SetFrameBorderMode(0);
   
   TH1D *h_exp_nbjets__29 = new TH1D("h_exp_nbjets__29","",20,0,20);
   h_exp_nbjets__29->SetBinContent(2,397.3848);
   h_exp_nbjets__29->SetBinContent(3,149.4217);
   h_exp_nbjets__29->SetBinContent(4,25.08571);
   h_exp_nbjets__29->SetBinContent(5,0.9113614);
   h_exp_nbjets__29->SetBinError(2,47.80059);
   h_exp_nbjets__29->SetBinError(3,27.91323);
   h_exp_nbjets__29->SetBinError(4,9.691631);
   h_exp_nbjets__29->SetBinError(5,0.5568519);
   h_exp_nbjets__29->SetEntries(532);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   h_exp_nbjets__29->SetLineColor(ci);
   h_exp_nbjets__29->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   h_exp_nbjets__29->SetMarkerColor(ci);
   h_exp_nbjets__29->SetMarkerStyle(20);
   h_exp_nbjets__29->SetMarkerSize(0.9);
   h_exp_nbjets__29->GetXaxis()->SetTitle("Number of B Jets");
   h_exp_nbjets__29->GetXaxis()->SetRange(1,5);
   h_exp_nbjets__29->GetXaxis()->SetLabelFont(42);
   h_exp_nbjets__29->GetXaxis()->SetLabelSize(0.035);
   h_exp_nbjets__29->GetXaxis()->SetTitleSize(0.035);
   h_exp_nbjets__29->GetXaxis()->SetTitleFont(42);
   h_exp_nbjets__29->GetYaxis()->SetTitle("Events");
   h_exp_nbjets__29->GetYaxis()->SetLabelFont(42);
   h_exp_nbjets__29->GetYaxis()->SetLabelSize(0.05);
   h_exp_nbjets__29->GetYaxis()->SetTitleSize(0.065);
   h_exp_nbjets__29->GetYaxis()->SetTitleOffset(0.6);
   h_exp_nbjets__29->GetYaxis()->SetTitleFont(42);
   h_exp_nbjets__29->GetZaxis()->SetLabelFont(42);
   h_exp_nbjets__29->GetZaxis()->SetLabelSize(0.035);
   h_exp_nbjets__29->GetZaxis()->SetTitleSize(0.035);
   h_exp_nbjets__29->GetZaxis()->SetTitleFont(42);
   h_exp_nbjets__29->Draw("PE1");
   
   TH1D *h_pred_nbjets_copy__30 = new TH1D("h_pred_nbjets_copy__30","",20,0,20);
   h_pred_nbjets_copy__30->SetBinContent(2,448.6572);
   h_pred_nbjets_copy__30->SetBinContent(3,98.13286);
   h_pred_nbjets_copy__30->SetBinContent(4,23.86168);
   h_pred_nbjets_copy__30->SetBinContent(5,2.087108);
   h_pred_nbjets_copy__30->SetBinContent(6,0.06495361);
   h_pred_nbjets_copy__30->SetBinError(2,13.06585);
   h_pred_nbjets_copy__30->SetBinError(3,5.245778);
   h_pred_nbjets_copy__30->SetBinError(4,3.145193);
   h_pred_nbjets_copy__30->SetBinError(5,0.814816);
   h_pred_nbjets_copy__30->SetBinError(6,0.05478936);
   h_pred_nbjets_copy__30->SetEntries(8602);
   h_pred_nbjets_copy__30->SetDirectory(0);

   ci = TColor::GetColor("#0000ff");
   h_pred_nbjets_copy__30->SetLineColor(ci);
   h_pred_nbjets_copy__30->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   h_pred_nbjets_copy__30->SetMarkerColor(ci);
   h_pred_nbjets_copy__30->SetMarkerStyle(20);
   h_pred_nbjets_copy__30->SetMarkerSize(0);
   h_pred_nbjets_copy__30->GetXaxis()->SetTitle("Number of B Jets");
   h_pred_nbjets_copy__30->GetXaxis()->SetRange(1,5);
   h_pred_nbjets_copy__30->GetXaxis()->SetLabelFont(42);
   h_pred_nbjets_copy__30->GetXaxis()->SetLabelSize(0.035);
   h_pred_nbjets_copy__30->GetXaxis()->SetTitleSize(0.035);
   h_pred_nbjets_copy__30->GetXaxis()->SetTitleFont(42);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitle("Events");
   h_pred_nbjets_copy__30->GetYaxis()->SetLabelFont(42);
   h_pred_nbjets_copy__30->GetYaxis()->SetLabelSize(0.05);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitleSize(0.065);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitleOffset(0.6);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitleFont(42);
   h_pred_nbjets_copy__30->GetZaxis()->SetLabelFont(42);
   h_pred_nbjets_copy__30->GetZaxis()->SetLabelSize(0.035);
   h_pred_nbjets_copy__30->GetZaxis()->SetTitleSize(0.035);
   h_pred_nbjets_copy__30->GetZaxis()->SetTitleFont(42);
   h_pred_nbjets_copy__30->Draw("hist same");
   
   TH1D *h_pred_nbjets__31 = new TH1D("h_pred_nbjets__31","",20,0,20);
   h_pred_nbjets__31->SetBinContent(2,448.6572);
   h_pred_nbjets__31->SetBinContent(3,98.13286);
   h_pred_nbjets__31->SetBinContent(4,23.86168);
   h_pred_nbjets__31->SetBinContent(5,2.087108);
   h_pred_nbjets__31->SetBinContent(6,0.06495361);
   h_pred_nbjets__31->SetBinError(2,13.06585);
   h_pred_nbjets__31->SetBinError(3,5.245778);
   h_pred_nbjets__31->SetBinError(4,3.145193);
   h_pred_nbjets__31->SetBinError(5,0.814816);
   h_pred_nbjets__31->SetBinError(6,0.05478936);
   h_pred_nbjets__31->SetEntries(8602);

   ci = TColor::GetColor("#3333ff");
   h_pred_nbjets__31->SetFillColor(ci);
   h_pred_nbjets__31->SetFillStyle(3001);

   ci = TColor::GetColor("#0000ff");
   h_pred_nbjets__31->SetLineColor(ci);
   h_pred_nbjets__31->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   h_pred_nbjets__31->SetMarkerColor(ci);
   h_pred_nbjets__31->SetMarkerStyle(20);
   h_pred_nbjets__31->SetMarkerSize(0);
   h_pred_nbjets__31->GetXaxis()->SetTitle("Number of B Jets");
   h_pred_nbjets__31->GetXaxis()->SetRange(1,5);
   h_pred_nbjets__31->GetXaxis()->SetLabelFont(42);
   h_pred_nbjets__31->GetXaxis()->SetLabelSize(0.035);
   h_pred_nbjets__31->GetXaxis()->SetTitleSize(0.035);
   h_pred_nbjets__31->GetXaxis()->SetTitleFont(42);
   h_pred_nbjets__31->GetYaxis()->SetTitle("Events");
   h_pred_nbjets__31->GetYaxis()->SetLabelFont(42);
   h_pred_nbjets__31->GetYaxis()->SetLabelSize(0.05);
   h_pred_nbjets__31->GetYaxis()->SetTitleSize(0.065);
   h_pred_nbjets__31->GetYaxis()->SetTitleOffset(0.6);
   h_pred_nbjets__31->GetYaxis()->SetTitleFont(42);
   h_pred_nbjets__31->GetZaxis()->SetLabelFont(42);
   h_pred_nbjets__31->GetZaxis()->SetLabelSize(0.035);
   h_pred_nbjets__31->GetZaxis()->SetTitleSize(0.035);
   h_pred_nbjets__31->GetZaxis()->SetTitleFont(42);
   h_pred_nbjets__31->Draw("E2 same");
   pad->Modified();
   c->cd();
  
// ------------>Primitives in pad: ratio
   TPad *ratio = new TPad("ratio", "",0,0,1,0.2);
   ratio->Draw();
   ratio->cd();
   ratio->Range(-0.625,-5,5.625,5);
   ratio->SetFillColor(0);
   ratio->SetBorderMode(0);
   ratio->SetBorderSize(5);
   ratio->SetTopMargin(0);
   ratio->SetBottomMargin(0.3);
   ratio->SetFrameBorderMode(0);
   ratio->SetFrameBorderMode(0);
   
   TH1D *Ratio__32 = new TH1D("Ratio__32","",20,0,20);
   Ratio__32->SetBinContent(2,0.8857204);
   Ratio__32->SetBinContent(3,1.522647);
   Ratio__32->SetBinContent(4,1.051297);
   Ratio__32->SetBinContent(5,0.4366622);
   Ratio__32->SetBinError(2,0.1096194);
   Ratio__32->SetBinError(3,0.2958598);
   Ratio__32->SetBinError(4,0.4291466);
   Ratio__32->SetBinError(5,0.3166178);
   Ratio__32->SetMinimum(-2);
   Ratio__32->SetMaximum(5);
   Ratio__32->SetEntries(39.5386);
   Ratio__32->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Ratio__32->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   Ratio__32->SetMarkerColor(ci);
   Ratio__32->SetMarkerStyle(20);
   Ratio__32->GetXaxis()->SetTitle("Number of B Jets");
   Ratio__32->GetXaxis()->SetRange(1,5);
   Ratio__32->GetXaxis()->SetLabelFont(42);
   Ratio__32->GetXaxis()->SetLabelOffset(0.01);
   Ratio__32->GetXaxis()->SetLabelSize(0.15);
   Ratio__32->GetXaxis()->SetTitleSize(0.16);
   Ratio__32->GetXaxis()->SetTitleFont(42);
   Ratio__32->GetYaxis()->SetTitle("#frac{Direct}{Prediction}");
   Ratio__32->GetYaxis()->SetLabelFont(42);
   Ratio__32->GetYaxis()->SetLabelSize(0.1);
   Ratio__32->GetYaxis()->SetTitleSize(0.15);
   Ratio__32->GetYaxis()->SetTitleOffset(0.6);
   Ratio__32->GetYaxis()->SetTitleFont(42);
   Ratio__32->GetZaxis()->SetLabelFont(42);
   Ratio__32->GetZaxis()->SetLabelSize(0.035);
   Ratio__32->GetZaxis()->SetTitleSize(0.035);
   Ratio__32->GetZaxis()->SetTitleFont(42);
   Ratio__32->Draw("PE1");
   TLine *line = new TLine(0,1,5,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   ratio->Modified();
   c->cd();
   TLatex *   tex = new TLatex(0.9,0.925,"36.8 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.1,0.925,"CMS");
tex->SetNDC();
   tex->SetTextFont(61);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.925,"Preliminary");
tex->SetNDC();
   tex->SetTextFont(52);
   tex->SetTextSize(0.0342);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.55,0.75,0.9,0.9,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextSize(0.03);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(2);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("NULL","QCD background","h");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_exp_nbjets","Direct from simulation","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_pred_nbjets","Treat simulation like data","lpf");

   ci = TColor::GetColor("#3333ff");
   entry->SetFillColor(ci);
   entry->SetFillStyle(3001);

   ci = TColor::GetColor("#0000ff");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
