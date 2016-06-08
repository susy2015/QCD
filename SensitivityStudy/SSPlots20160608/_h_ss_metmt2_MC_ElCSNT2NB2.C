void _h_ss_metmt2_MC_ElCSNT2NB2()
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
   Double_t xAxis12[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis12[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT2NB2 = new TH2D("h_ss_metmt2_MC_ElCSNT2NB2","",4, xAxis12,3, yAxis12);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(7,5110);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(8,389);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(9,36);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(10,9);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(13,457);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(14,116);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(15,17);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(16,5);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(19,18);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(20,61);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(21,24);
   h_ss_metmt2_MC_ElCSNT2NB2->SetBinContent(22,4);
   h_ss_metmt2_MC_ElCSNT2NB2->SetEntries(6246);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContour(20);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(0,4);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(1,259.3);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(2,514.6);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(3,769.9);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(4,1025.2);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(5,1280.5);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(6,1535.8);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(7,1791.1);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(8,2046.4);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(9,2301.7);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(10,2557);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(11,2812.3);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(12,3067.6);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(13,3322.9);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(14,3578.2);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(15,3833.5);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(16,4088.8);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(17,4344.1);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(18,4599.4);
   h_ss_metmt2_MC_ElCSNT2NB2->SetContourLevel(19,4854.7);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_ElCSNT2NB2);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT2NB2->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT2NB2->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT2NB2->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT2NB2->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT2NB2->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT2NB2->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB2->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB2->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT2NB2->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT2NB2->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT2NB2->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB2->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB2->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT2NB2->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT2NB2->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB2->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT2NB2->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT2NB2->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : 2 Top, 2 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
