void _h_ss_metmt2_MC_ElCSNT3NB3()
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
   Double_t xAxis20[4] = {200, 350, 500, 800}; 
   Double_t yAxis20[2] = {200, 500}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT3NB3 = new TH2D("h_ss_metmt2_MC_ElCSNT3NB3","",3, xAxis20,1, yAxis20);
   h_ss_metmt2_MC_ElCSNT3NB3->SetBinContent(6,45);
   h_ss_metmt2_MC_ElCSNT3NB3->SetBinContent(7,12);
   h_ss_metmt2_MC_ElCSNT3NB3->SetBinContent(8,5);
   h_ss_metmt2_MC_ElCSNT3NB3->SetEntries(62);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContour(20);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(0,5);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(1,7);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(2,9);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(3,11);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(4,13);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(5,15);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(6,17);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(7,19);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(8,21);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(9,23);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(10,25);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(11,27);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(12,29);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(13,31);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(14,33);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(15,35);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(16,37);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(17,39);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(18,41);
   h_ss_metmt2_MC_ElCSNT3NB3->SetContourLevel(19,43);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_ElCSNT3NB3);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT3NB3->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT3NB3->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT3NB3->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT3NB3->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT3NB3->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT3NB3->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB3->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB3->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT3NB3->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT3NB3->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT3NB3->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB3->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB3->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT3NB3->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT3NB3->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB3->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB3->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT3NB3->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : >= 3 Top, >=3 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
