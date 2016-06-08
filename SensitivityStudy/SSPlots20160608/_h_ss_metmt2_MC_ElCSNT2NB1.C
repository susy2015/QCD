void _h_ss_metmt2_MC_ElCSNT2NB1()
{
//=========Macro generated from canvas: c/
//=========  (Wed Jun  8 08:54:43 2016) by ROOT version6.02/05
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(99.99999,150,1100,650);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis10[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis10[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT2NB1 = new TH2D("h_ss_metmt2_MC_ElCSNT2NB1","",4, xAxis10,3, yAxis10);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(7,6989);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(8,513);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(9,53);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(10,4);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(13,632);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(14,186);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(15,28);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(16,6);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(19,28);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(20,85);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(21,33);
   h_ss_metmt2_MC_ElCSNT2NB1->SetBinContent(22,6);
   h_ss_metmt2_MC_ElCSNT2NB1->SetEntries(8563);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContour(20);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(0,4);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(1,353.25);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(2,702.5);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(3,1051.75);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(4,1401);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(5,1750.25);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(6,2099.5);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(7,2448.75);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(8,2798);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(9,3147.25);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(10,3496.5);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(11,3845.75);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(12,4195);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(13,4544.25);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(14,4893.5);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(15,5242.75);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(16,5592);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(17,5941.25);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(18,6290.5);
   h_ss_metmt2_MC_ElCSNT2NB1->SetContourLevel(19,6639.75);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_ElCSNT2NB1);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT2NB1->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT2NB1->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT2NB1->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT2NB1->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT2NB1->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT2NB1->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB1->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB1->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT2NB1->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT2NB1->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT2NB1->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB1->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB1->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT2NB1->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT2NB1->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB1->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB1->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT2NB1->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : 2 Top, 1 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
