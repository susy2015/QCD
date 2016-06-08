void _h_ss_metmt2_MC_MuCSNT3NB1()
{
//=========Macro generated from canvas: c/
//=========  (Wed Jun  8 08:54:43 2016) by ROOT version6.02/05
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(125,162.5,875,537.5);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis15[4] = {200, 350, 500, 800}; 
   Double_t yAxis15[2] = {200, 500}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT3NB1 = new TH2D("h_ss_metmt2_MC_MuCSNT3NB1","",3, xAxis15,1, yAxis15);
   h_ss_metmt2_MC_MuCSNT3NB1->SetBinContent(6,223);
   h_ss_metmt2_MC_MuCSNT3NB1->SetBinContent(7,42);
   h_ss_metmt2_MC_MuCSNT3NB1->SetBinContent(8,9);
   h_ss_metmt2_MC_MuCSNT3NB1->SetEntries(274);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContour(20);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(0,9);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(1,19.7);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(2,30.4);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(3,41.1);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(4,51.8);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(5,62.5);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(6,73.2);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(7,83.9);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(8,94.6);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(9,105.3);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(10,116);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(11,126.7);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(12,137.4);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(13,148.1);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(14,158.8);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(15,169.5);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(16,180.2);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(17,190.9);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(18,201.6);
   h_ss_metmt2_MC_MuCSNT3NB1->SetContourLevel(19,212.3);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_MuCSNT3NB1);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT3NB1->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT3NB1->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT3NB1->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT3NB1->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT3NB1->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT3NB1->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB1->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB1->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT3NB1->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT3NB1->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT3NB1->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB1->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB1->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT3NB1->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT3NB1->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB1->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB1->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT3NB1->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : >= 3 Top, 1 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
