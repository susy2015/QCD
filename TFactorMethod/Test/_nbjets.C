void _nbjets()
{
//=========Macro generated from canvas: c/
//=========  (Tue Aug  8 11:48:23 2017) by ROOT version6.06/01
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
   pad->Range(-0.625,-0.3965957,5.625,3.711877);
   pad->SetFillColor(0);
   pad->SetBorderMode(0);
   pad->SetBorderSize(5);
   pad->SetLogy();
   pad->SetBottomMargin(0);
   pad->SetFrameBorderMode(0);
   pad->SetFrameBorderMode(0);
   
   TH1D *h_exp_nbjets__29 = new TH1D("h_exp_nbjets__29","",20,0,20);
   h_exp_nbjets__29->SetBinContent(2,323.0209);
   h_exp_nbjets__29->SetBinContent(3,129.2073);
   h_exp_nbjets__29->SetBinContent(4,13.76809);
   h_exp_nbjets__29->SetBinContent(5,3.461234);
   h_exp_nbjets__29->SetBinError(2,41.75732);
   h_exp_nbjets__29->SetBinError(3,23.67817);
   h_exp_nbjets__29->SetBinError(4,4.536283);
   h_exp_nbjets__29->SetBinError(5,2.658754);
   h_exp_nbjets__29->SetMaximum(2000);
   h_exp_nbjets__29->SetEntries(526);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#ff0000");
   h_exp_nbjets__29->SetLineColor(ci);
   h_exp_nbjets__29->SetLineWidth(3);

   ci = TColor::GetColor("#ff0000");
   h_exp_nbjets__29->SetMarkerColor(ci);
   h_exp_nbjets__29->SetMarkerStyle(20);
   h_exp_nbjets__29->SetMarkerSize(0.9);
   h_exp_nbjets__29->GetXaxis()->SetTitle("N_{b}");
   h_exp_nbjets__29->GetXaxis()->SetRange(1,5);
   h_exp_nbjets__29->GetXaxis()->SetLabelFont(42);
   h_exp_nbjets__29->GetXaxis()->SetLabelSize(0.2);
   h_exp_nbjets__29->GetXaxis()->SetTitleSize(0.035);
   h_exp_nbjets__29->GetXaxis()->SetTitleFont(42);
   h_exp_nbjets__29->GetYaxis()->SetTitle("Events");
   h_exp_nbjets__29->GetYaxis()->SetLabelFont(42);
   h_exp_nbjets__29->GetYaxis()->SetLabelSize(0.05);
   h_exp_nbjets__29->GetYaxis()->SetTitleSize(0.075);
   h_exp_nbjets__29->GetYaxis()->SetTitleOffset(0.6);
   h_exp_nbjets__29->GetYaxis()->SetTitleFont(42);
   h_exp_nbjets__29->GetZaxis()->SetLabelFont(42);
   h_exp_nbjets__29->GetZaxis()->SetLabelSize(0.035);
   h_exp_nbjets__29->GetZaxis()->SetTitleSize(0.035);
   h_exp_nbjets__29->GetZaxis()->SetTitleFont(42);
   h_exp_nbjets__29->Draw("PEX0");
   
   TH1D *h_pred_nbjets_copy__30 = new TH1D("h_pred_nbjets_copy__30","",20,0,20);
   h_pred_nbjets_copy__30->SetBinContent(2,363.6556);
   h_pred_nbjets_copy__30->SetBinContent(3,88.5572);
   h_pred_nbjets_copy__30->SetBinContent(4,14.39944);
   h_pred_nbjets_copy__30->SetBinContent(5,2.794767);
   h_pred_nbjets_copy__30->SetBinContent(6,0.04930447);
   h_pred_nbjets_copy__30->SetBinError(2,11.00063);
   h_pred_nbjets_copy__30->SetBinError(3,4.762231);
   h_pred_nbjets_copy__30->SetBinError(4,1.815544);
   h_pred_nbjets_copy__30->SetBinError(5,0.8342527);
   h_pred_nbjets_copy__30->SetBinError(6,0.03836764);
   h_pred_nbjets_copy__30->SetMaximum(2000);
   h_pred_nbjets_copy__30->SetEntries(8121);
   h_pred_nbjets_copy__30->SetDirectory(0);

   ci = TColor::GetColor("#0000ff");
   h_pred_nbjets_copy__30->SetLineColor(ci);
   h_pred_nbjets_copy__30->SetLineWidth(3);

   ci = TColor::GetColor("#0000ff");
   h_pred_nbjets_copy__30->SetMarkerColor(ci);
   h_pred_nbjets_copy__30->SetMarkerStyle(20);
   h_pred_nbjets_copy__30->SetMarkerSize(0);
   h_pred_nbjets_copy__30->GetXaxis()->SetTitle("N_{b}");
   h_pred_nbjets_copy__30->GetXaxis()->SetRange(1,5);
   h_pred_nbjets_copy__30->GetXaxis()->SetLabelFont(42);
   h_pred_nbjets_copy__30->GetXaxis()->SetLabelSize(0.2);
   h_pred_nbjets_copy__30->GetXaxis()->SetTitleSize(0.035);
   h_pred_nbjets_copy__30->GetXaxis()->SetTitleFont(42);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitle("Events");
   h_pred_nbjets_copy__30->GetYaxis()->SetLabelFont(42);
   h_pred_nbjets_copy__30->GetYaxis()->SetLabelSize(0.05);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitleSize(0.075);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitleOffset(0.6);
   h_pred_nbjets_copy__30->GetYaxis()->SetTitleFont(42);
   h_pred_nbjets_copy__30->GetZaxis()->SetLabelFont(42);
   h_pred_nbjets_copy__30->GetZaxis()->SetLabelSize(0.035);
   h_pred_nbjets_copy__30->GetZaxis()->SetTitleSize(0.035);
   h_pred_nbjets_copy__30->GetZaxis()->SetTitleFont(42);
   h_pred_nbjets_copy__30->Draw("hist same");
   
   TH1D *h_pred_nbjets__31 = new TH1D("h_pred_nbjets__31","",20,0,20);
   h_pred_nbjets__31->SetBinContent(2,363.6556);
   h_pred_nbjets__31->SetBinContent(3,88.5572);
   h_pred_nbjets__31->SetBinContent(4,14.39944);
   h_pred_nbjets__31->SetBinContent(5,2.794767);
   h_pred_nbjets__31->SetBinContent(6,0.04930447);
   h_pred_nbjets__31->SetBinError(2,11.00063);
   h_pred_nbjets__31->SetBinError(3,4.762231);
   h_pred_nbjets__31->SetBinError(4,1.815544);
   h_pred_nbjets__31->SetBinError(5,0.8342527);
   h_pred_nbjets__31->SetBinError(6,0.03836764);
   h_pred_nbjets__31->SetMaximum(2000);
   h_pred_nbjets__31->SetEntries(8121);

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
   h_pred_nbjets__31->GetXaxis()->SetTitle("N_{b}");
   h_pred_nbjets__31->GetXaxis()->SetRange(1,5);
   h_pred_nbjets__31->GetXaxis()->SetLabelFont(42);
   h_pred_nbjets__31->GetXaxis()->SetLabelSize(0.2);
   h_pred_nbjets__31->GetXaxis()->SetTitleSize(0.035);
   h_pred_nbjets__31->GetXaxis()->SetTitleFont(42);
   h_pred_nbjets__31->GetYaxis()->SetTitle("Events");
   h_pred_nbjets__31->GetYaxis()->SetLabelFont(42);
   h_pred_nbjets__31->GetYaxis()->SetLabelSize(0.05);
   h_pred_nbjets__31->GetYaxis()->SetTitleSize(0.075);
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
   
   TH1D *Ratio__32 = new TH1D("Ratio__32","",20,0,20);
   Ratio__32->SetBinContent(2,0.8882603);
   Ratio__32->SetBinContent(3,1.459027);
   Ratio__32->SetBinContent(4,0.9561544);
   Ratio__32->SetBinContent(5,1.23847);
   Ratio__32->SetBinError(2,0.1179285);
   Ratio__32->SetBinError(3,0.2786513);
   Ratio__32->SetBinError(4,0.3373113);
   Ratio__32->SetBinError(5,1.020639);
   Ratio__32->SetMinimum(-1.5);
   Ratio__32->SetMaximum(4.9);
   Ratio__32->SetEntries(16.54237);
   Ratio__32->SetStats(0);

   ci = TColor::GetColor("#ff0000");
   Ratio__32->SetLineColor(ci);

   ci = TColor::GetColor("#ff0000");
   Ratio__32->SetMarkerColor(ci);
   Ratio__32->SetMarkerStyle(20);
   Ratio__32->GetXaxis()->SetTitle("N_{b}");
   Ratio__32->GetXaxis()->SetRange(1,5);
   Ratio__32->GetXaxis()->SetLabelFont(42);
   Ratio__32->GetXaxis()->SetLabelOffset(0.01);
   Ratio__32->GetXaxis()->SetLabelSize(0.15);
   Ratio__32->GetXaxis()->SetTitleSize(0.15);
   Ratio__32->GetXaxis()->SetTickLength(0.1);
   Ratio__32->GetXaxis()->SetTitleFont(42);
   Ratio__32->GetYaxis()->SetTitle("#frac{Direct}{Prediction}");
   Ratio__32->GetYaxis()->SetNdivisions(505);
   Ratio__32->GetYaxis()->SetLabelFont(42);
   Ratio__32->GetYaxis()->SetLabelOffset(0.01);
   Ratio__32->GetYaxis()->SetLabelSize(0.1);
   Ratio__32->GetYaxis()->SetTitleSize(0.12);
   Ratio__32->GetYaxis()->SetTitleOffset(0.3);
   Ratio__32->GetYaxis()->SetTitleFont(42);
   Ratio__32->GetZaxis()->SetLabelFont(42);
   Ratio__32->GetZaxis()->SetLabelSize(0.035);
   Ratio__32->GetZaxis()->SetTitleSize(0.035);
   Ratio__32->GetZaxis()->SetTitleFont(42);
   Ratio__32->Draw("PEX0");
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
