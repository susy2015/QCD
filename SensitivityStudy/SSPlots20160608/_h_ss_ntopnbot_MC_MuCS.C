void _h_ss_ntopnbot_MC_MuCS()
{
//=========Macro generated from canvas: c/
//=========  (Wed Jun  8 08:54:41 2016) by ROOT version6.02/05
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(0.625,0.625,4.375,4.375);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[4] = {1, 2, 3, 4}; 
   Double_t yAxis1[4] = {1, 2, 3, 4}; 
   
   TH2D *h_ss_ntopnbot_MC_MuCS = new TH2D("h_ss_ntopnbot_MC_MuCS","",3, xAxis1,3, yAxis1);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(6,16058);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(7,9429);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(8,274);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(11,13197);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(12,7096);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(13,255);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(16,1967);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(17,921);
   h_ss_ntopnbot_MC_MuCS->SetBinContent(18,61);
   h_ss_ntopnbot_MC_MuCS->SetEntries(49258);
   h_ss_ntopnbot_MC_MuCS->SetContour(20);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(0,61);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(1,860.85);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(2,1660.7);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(3,2460.55);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(4,3260.4);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(5,4060.25);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(6,4860.1);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(7,5659.95);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(8,6459.8);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(9,7259.65);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(10,8059.5);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(11,8859.35);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(12,9659.2);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(13,10459.05);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(14,11258.9);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(15,12058.75);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(16,12858.6);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(17,13658.45);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(18,14458.3);
   h_ss_ntopnbot_MC_MuCS->SetContourLevel(19,15258.15);
   
   TPaletteAxis *palette = new TPaletteAxis(4.01875,1,4.1875,4,h_ss_ntopnbot_MC_MuCS);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_ntopnbot_MC_MuCS->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_ntopnbot_MC_MuCS->SetLineColor(ci);
   h_ss_ntopnbot_MC_MuCS->SetMarkerSize(2);
   h_ss_ntopnbot_MC_MuCS->GetXaxis()->SetTitle("NTops");
   h_ss_ntopnbot_MC_MuCS->GetXaxis()->SetLabelFont(42);
   h_ss_ntopnbot_MC_MuCS->GetXaxis()->SetLabelSize(0.035);
   h_ss_ntopnbot_MC_MuCS->GetXaxis()->SetTitleSize(0.035);
   h_ss_ntopnbot_MC_MuCS->GetXaxis()->SetTitleFont(42);
   h_ss_ntopnbot_MC_MuCS->GetYaxis()->SetTitle("NBottoms");
   h_ss_ntopnbot_MC_MuCS->GetYaxis()->SetLabelFont(42);
   h_ss_ntopnbot_MC_MuCS->GetYaxis()->SetLabelSize(0.035);
   h_ss_ntopnbot_MC_MuCS->GetYaxis()->SetTitleSize(0.035);
   h_ss_ntopnbot_MC_MuCS->GetYaxis()->SetTitleFont(42);
   h_ss_ntopnbot_MC_MuCS->GetZaxis()->SetLabelFont(42);
   h_ss_ntopnbot_MC_MuCS->GetZaxis()->SetLabelSize(0.035);
   h_ss_ntopnbot_MC_MuCS->GetZaxis()->SetTitleSize(0.035);
   h_ss_ntopnbot_MC_MuCS->GetZaxis()->SetTitleFont(42);
   h_ss_ntopnbot_MC_MuCS->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
