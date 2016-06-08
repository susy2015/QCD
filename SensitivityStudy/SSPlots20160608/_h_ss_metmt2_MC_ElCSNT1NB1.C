void _h_ss_metmt2_MC_ElCSNT1NB1()
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
   Double_t xAxis4[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis4[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT1NB1 = new TH2D("h_ss_metmt2_MC_ElCSNT1NB1","",4, xAxis4,3, yAxis4);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(7,11580);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(8,925);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(9,98);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(10,14);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(13,1136);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(14,482);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(15,20);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(16,8);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(19,28);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(20,238);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(21,77);
   h_ss_metmt2_MC_ElCSNT1NB1->SetBinContent(22,16);
   h_ss_metmt2_MC_ElCSNT1NB1->SetEntries(14622);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContour(20);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(0,8);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(1,586.6);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(2,1165.2);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(3,1743.8);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(4,2322.4);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(5,2901);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(6,3479.6);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(7,4058.2);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(8,4636.8);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(9,5215.4);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(10,5794);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(11,6372.6);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(12,6951.2);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(13,7529.8);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(14,8108.4);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(15,8687);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(16,9265.6);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(17,9844.2);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(18,10422.8);
   h_ss_metmt2_MC_ElCSNT1NB1->SetContourLevel(19,11001.4);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_ElCSNT1NB1);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT1NB1->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT1NB1->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT1NB1->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT1NB1->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT1NB1->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB1->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB1->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB1->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB1->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT1NB1->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB1->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB1->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB1->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB1->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB1->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB1->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB1->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB1->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : 1 Top, 1 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
