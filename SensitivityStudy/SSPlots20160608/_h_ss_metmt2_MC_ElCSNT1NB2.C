void _h_ss_metmt2_MC_ElCSNT1NB2()
{
//=========Macro generated from canvas: c/
//=========  (Wed Jun  8 08:54:42 2016) by ROOT version6.02/05
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(99.99999,150,1100,650);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis6[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis6[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT1NB2 = new TH2D("h_ss_metmt2_MC_ElCSNT1NB2","",4, xAxis6,3, yAxis6);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(7,9946);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(8,926);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(9,89);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(10,17);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(13,383);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(14,182);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(15,30);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(16,7);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(19,8);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(20,59);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(21,30);
   h_ss_metmt2_MC_ElCSNT1NB2->SetBinContent(22,9);
   h_ss_metmt2_MC_ElCSNT1NB2->SetEntries(11686);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContour(20);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(0,7);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(1,503.95);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(2,1000.9);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(3,1497.85);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(4,1994.8);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(5,2491.75);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(6,2988.7);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(7,3485.65);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(8,3982.6);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(9,4479.55);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(10,4976.5);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(11,5473.45);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(12,5970.4);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(13,6467.35);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(14,6964.3);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(15,7461.25);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(16,7958.2);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(17,8455.15);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(18,8952.1);
   h_ss_metmt2_MC_ElCSNT1NB2->SetContourLevel(19,9449.05);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_ElCSNT1NB2);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT1NB2->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT1NB2->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT1NB2->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT1NB2->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT1NB2->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB2->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB2->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB2->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB2->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT1NB2->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB2->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB2->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB2->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB2->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB2->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB2->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB2->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB2->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : 1 Top, 2 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
