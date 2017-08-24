void _ntopjets()
{
//=========Macro generated from canvas: c/
//=========  (Tue Aug  8 11:48:22 2017) by ROOT version6.06/01
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0,0,1,1);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
  
// ------------>Primitives in pad: 
   TPad *pad = new TPad("", "",0,0.3,1,1);
   pad->Draw();
   pad->cd();
   pad->Range(-0.625,-1.174625,5.625,3.798325);
   pad->SetFillColor(0);
   pad->SetBorderMode(0);
   pad->SetBorderSize(5);
   pad->SetLogy();
   pad->SetBottomMargin(0);
   pad->SetFrameBorderMode(0);
   pad->SetFrameBorderMode(0);
   
   TH1D *h_exp_ntopjets__25 = new TH1D("h_exp_ntopjets__25","",20,0,20);
   h_exp_ntopjets__25->SetBinContent(2,417.0608);
   h_exp_ntopjets__25->SetBinContent(3,52.2629);
   h_exp_ntopjets__25->SetBinContent(4,0.1337842);
   h_exp_ntopjets__25->SetBinError(2,44.5952);
   h_exp_ntopjets__25->SetBinError(3,18.52638);
   h_exp_ntopjets__25->SetBinError(4,0.1337842);
   h_exp_ntopjets__25->SetMaximum(2000);
   h_exp_ntopjets__25->SetEntries(526);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   h_exp_ntopjets__25->SetLineColor(ci);
   h_exp_ntopjets__25->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   h_exp_ntopjets__25->SetMarkerColor(ci);
   h_exp_ntopjets__25->SetMarkerStyle(20);
   h_exp_ntopjets__25->SetMarkerSize(0.9);
   h_exp_ntopjets__25->GetXaxis()->SetTitle("N_{t}");
   h_exp_ntopjets__25->GetXaxis()->SetRange(1,5);
   h_exp_ntopjets__25->GetXaxis()->SetLabelFont(42);
   h_exp_ntopjets__25->GetXaxis()->SetLabelSize(0.2);
   h_exp_ntopjets__25->GetXaxis()->SetTitleSize(0.035);
   h_exp_ntopjets__25->GetXaxis()->SetTitleFont(42);
   h_exp_ntopjets__25->GetYaxis()->SetTitle("Events");
   h_exp_ntopjets__25->GetYaxis()->SetLabelFont(42);
   h_exp_ntopjets__25->GetYaxis()->SetLabelSize(0.05);
   h_exp_ntopjets__25->GetYaxis()->SetTitleSize(0.075);
   h_exp_ntopjets__25->GetYaxis()->SetTitleOffset(0.6);
   h_exp_ntopjets__25->GetYaxis()->SetTitleFont(42);
   h_exp_ntopjets__25->GetZaxis()->SetLabelFont(42);
   h_exp_ntopjets__25->GetZaxis()->SetLabelSize(0.035);
   h_exp_ntopjets__25->GetZaxis()->SetTitleSize(0.035);
   h_exp_ntopjets__25->GetZaxis()->SetTitleFont(42);
   h_exp_ntopjets__25->Draw("PEX0");
   
   TH1D *h_pred_ntopjets_copy__26 = new TH1D("h_pred_ntopjets_copy__26","",20,0,20);
   h_pred_ntopjets_copy__26->SetBinContent(2,442.3689);
   h_pred_ntopjets_copy__26->SetBinContent(3,26.95481);
   h_pred_ntopjets_copy__26->SetBinContent(4,0.1326463);
   h_pred_ntopjets_copy__26->SetBinError(2,11.91612);
   h_pred_ntopjets_copy__26->SetBinError(3,2.385336);
   h_pred_ntopjets_copy__26->SetBinError(4,0.05008996);
   h_pred_ntopjets_copy__26->SetMaximum(2000);
   h_pred_ntopjets_copy__26->SetEntries(8121);
   h_pred_ntopjets_copy__26->SetDirectory(0);

   ci = TColor::GetColor("#0000ff");
   h_pred_ntopjets_copy__26->SetLineColor(ci);
   h_pred_ntopjets_copy__26->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   h_pred_ntopjets_copy__26->SetMarkerColor(ci);
   h_pred_ntopjets_copy__26->SetMarkerStyle(20);
   h_pred_ntopjets_copy__26->SetMarkerSize(0);
   h_pred_ntopjets_copy__26->GetXaxis()->SetTitle("N_{t}");
   h_pred_ntopjets_copy__26->GetXaxis()->SetRange(1,5);
   h_pred_ntopjets_copy__26->GetXaxis()->SetLabelFont(42);
   h_pred_ntopjets_copy__26->GetXaxis()->SetLabelSize(0.2);
   h_pred_ntopjets_copy__26->GetXaxis()->SetTitleSize(0.035);
   h_pred_ntopjets_copy__26->GetXaxis()->SetTitleFont(42);
   h_pred_ntopjets_copy__26->GetYaxis()->SetTitle("Events");
   h_pred_ntopjets_copy__26->GetYaxis()->SetLabelFont(42);
   h_pred_ntopjets_copy__26->GetYaxis()->SetLabelSize(0.05);
   h_pred_ntopjets_copy__26->GetYaxis()->SetTitleSize(0.075);
   h_pred_ntopjets_copy__26->GetYaxis()->SetTitleOffset(0.6);
   h_pred_ntopjets_copy__26->GetYaxis()->SetTitleFont(42);
   h_pred_ntopjets_copy__26->GetZaxis()->SetLabelFont(42);
   h_pred_ntopjets_copy__26->GetZaxis()->SetLabelSize(0.035);
   h_pred_ntopjets_copy__26->GetZaxis()->SetTitleSize(0.035);
   h_pred_ntopjets_copy__26->GetZaxis()->SetTitleFont(42);
   h_pred_ntopjets_copy__26->Draw("hist same");
   
   TH1D *h_pred_ntopjets__27 = new TH1D("h_pred_ntopjets__27","",20,0,20);
   h_pred_ntopjets__27->SetBinContent(2,442.3689);
   h_pred_ntopjets__27->SetBinContent(3,26.95481);
   h_pred_ntopjets__27->SetBinContent(4,0.1326463);
   h_pred_ntopjets__27->SetBinError(2,11.91612);
   h_pred_ntopjets__27->SetBinError(3,2.385336);
   h_pred_ntopjets__27->SetBinError(4,0.05008996);
   h_pred_ntopjets__27->SetMaximum(2000);
   h_pred_ntopjets__27->SetEntries(8121);

   ci = TColor::GetColor("#3333ff");
   h_pred_ntopjets__27->SetFillColor(ci);
   h_pred_ntopjets__27->SetFillStyle(3001);

   ci = TColor::GetColor("#0000ff");
   h_pred_ntopjets__27->SetLineColor(ci);
   h_pred_ntopjets__27->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   h_pred_ntopjets__27->SetMarkerColor(ci);
   h_pred_ntopjets__27->SetMarkerStyle(20);
   h_pred_ntopjets__27->SetMarkerSize(0);
   h_pred_ntopjets__27->GetXaxis()->SetTitle("N_{t}");
   h_pred_ntopjets__27->GetXaxis()->SetRange(1,5);
   h_pred_ntopjets__27->GetXaxis()->SetLabelFont(42);
   h_pred_ntopjets__27->GetXaxis()->SetLabelSize(0.2);
   h_pred_ntopjets__27->GetXaxis()->SetTitleSize(0.035);
   h_pred_ntopjets__27->GetXaxis()->SetTitleFont(42);
   h_pred_ntopjets__27->GetYaxis()->SetTitle("Events");
   h_pred_ntopjets__27->GetYaxis()->SetLabelFont(42);
   h_pred_ntopjets__27->GetYaxis()->SetLabelSize(0.05);
   h_pred_ntopjets__27->GetYaxis()->SetTitleSize(0.075);
   h_pred_ntopjets__27->GetYaxis()->SetTitleOffset(0.6);
   h_pred_ntopjets__27->GetYaxis()->SetTitleFont(42);
   h_pred_ntopjets__27->GetZaxis()->SetLabelFont(42);
   h_pred_ntopjets__27->GetZaxis()->SetLabelSize(0.035);
   h_pred_ntopjets__27->GetZaxis()->SetTitleSize(0.035);
   h_pred_ntopjets__27->GetZaxis()->SetTitleFont(42);
   h_pred_ntopjets__27->Draw("E2 same");
   pad->Modified();
   c->cd();
  
// ------------>Primitives in pad: ratio
   TPad *ratio = new TPad("ratio", "",0,0,1,0.3);
   ratio->Draw();
   ratio->cd();
   ratio->Range(-0.625,-6.736363,5.625,4.9);
   ratio->SetFillColor(0);
   ratio->SetBorderMode(0);
   ratio->SetBorderSize(5);
   ratio->SetTopMargin(0);
   ratio->SetBottomMargin(0.45);
   ratio->SetFrameBorderMode(0);
   ratio->SetFrameBorderMode(0);
   
   TH1D *Ratio__28 = new TH1D("Ratio__28","",20,0,20);
   Ratio__28->SetBinContent(2,0.9427898);
   Ratio__28->SetBinContent(3,1.938908);
   Ratio__28->SetBinContent(4,1.008578);
   Ratio__28->SetBinError(2,0.1039596);
   Ratio__28->SetBinError(3,0.7084058);
   Ratio__28->SetBinError(4,1.078093);
   Ratio__28->SetMinimum(-1.5);
   Ratio__28->SetMaximum(4.9);
   Ratio__28->SetEntries(9.035746);
   Ratio__28->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Ratio__28->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   Ratio__28->SetMarkerColor(ci);
   Ratio__28->SetMarkerStyle(20);
   Ratio__28->GetXaxis()->SetTitle("N_{t}");
   Ratio__28->GetXaxis()->SetRange(1,5);
   Ratio__28->GetXaxis()->SetLabelFont(42);
   Ratio__28->GetXaxis()->SetLabelOffset(0.01);
   Ratio__28->GetXaxis()->SetLabelSize(0.15);
   Ratio__28->GetXaxis()->SetTitleSize(0.15);
   Ratio__28->GetXaxis()->SetTickLength(0.1);
   Ratio__28->GetXaxis()->SetTitleFont(42);
   Ratio__28->GetYaxis()->SetTitle("#frac{Direct}{Prediction}");
   Ratio__28->GetYaxis()->SetNdivisions(505);
   Ratio__28->GetYaxis()->SetLabelFont(42);
   Ratio__28->GetYaxis()->SetLabelOffset(0.01);
   Ratio__28->GetYaxis()->SetLabelSize(0.1);
   Ratio__28->GetYaxis()->SetTitleSize(0.12);
   Ratio__28->GetYaxis()->SetTitleOffset(0.3);
   Ratio__28->GetYaxis()->SetTitleFont(42);
   Ratio__28->GetZaxis()->SetLabelFont(42);
   Ratio__28->GetZaxis()->SetLabelSize(0.035);
   Ratio__28->GetZaxis()->SetTitleSize(0.035);
   Ratio__28->GetZaxis()->SetTitleFont(42);
   Ratio__28->Draw("PEX0");
   TLine *line = new TLine(0,1,5,1);
   line->SetLineStyle(2);
   line->SetLineWidth(2);
   line->Draw();
   ratio->Modified();
   c->cd();
   TLatex *   tex = new TLatex(0.9,0.935,"35.9 fb^{-1} (13 TeV)");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.1,0.935,"CMS");
tex->SetNDC();
   tex->SetTextFont(61);
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.18,0.935,"Preliminary");
tex->SetNDC();
   tex->SetTextFont(52);
   tex->SetTextSize(0.0342);
   tex->SetLineWidth(2);
   tex->Draw();
   
   TLegend *leg = new TLegend(0.6,0.77,0.9,0.93,NULL,"brNDC");
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
   entry=leg->AddEntry("h_exp_ntopjets","Direct from simulation","P");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ff0000");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(0.9);
   entry->SetTextFont(42);
   entry=leg->AddEntry("h_pred_ntopjets","Treat simulation like data","lpf");

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
