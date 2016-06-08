void _h_ss_metmt2_MC_MuCSNT3NB2()
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
   Double_t xAxis17[4] = {200, 350, 500, 800}; 
   Double_t yAxis17[2] = {200, 500}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT3NB2 = new TH2D("h_ss_metmt2_MC_MuCSNT3NB2","",3, xAxis17,1, yAxis17);
   h_ss_metmt2_MC_MuCSNT3NB2->SetBinContent(6,225);
   h_ss_metmt2_MC_MuCSNT3NB2->SetBinContent(7,25);
   h_ss_metmt2_MC_MuCSNT3NB2->SetBinContent(8,5);
   h_ss_metmt2_MC_MuCSNT3NB2->SetEntries(255);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContour(20);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(0,5);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(1,16);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(2,27);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(3,38);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(4,49);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(5,60);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(6,71);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(7,82);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(8,93);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(9,104);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(10,115);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(11,126);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(12,137);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(13,148);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(14,159);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(15,170);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(16,181);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(17,192);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(18,203);
   h_ss_metmt2_MC_MuCSNT3NB2->SetContourLevel(19,214);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_MuCSNT3NB2);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT3NB2->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT3NB2->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT3NB2->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT3NB2->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT3NB2->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT3NB2->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB2->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB2->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT3NB2->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT3NB2->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT3NB2->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB2->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB2->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT3NB2->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT3NB2->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB2->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT3NB2->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT3NB2->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : >= 3 Top, 2 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
