void _h_ss_ntopnbot_MC_ElCS()
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
   Double_t xAxis2[4] = {1, 2, 3, 4}; 
   Double_t yAxis2[4] = {1, 2, 3, 4}; 
   
   TH2D *h_ss_ntopnbot_MC_ElCS = new TH2D("h_ss_ntopnbot_MC_ElCS","",3, xAxis2,3, yAxis2);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(6,14622);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(7,8563);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(8,259);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(11,11686);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(12,6246);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(13,227);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(16,1784);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(17,804);
   h_ss_ntopnbot_MC_ElCS->SetBinContent(18,62);
   h_ss_ntopnbot_MC_ElCS->SetEntries(44253);
   h_ss_ntopnbot_MC_ElCS->SetContour(20);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(0,62);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(1,790);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(2,1518);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(3,2246);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(4,2974);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(5,3702);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(6,4430);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(7,5158);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(8,5886);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(9,6614);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(10,7342);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(11,8070);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(12,8798);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(13,9526);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(14,10254);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(15,10982);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(16,11710);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(17,12438);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(18,13166);
   h_ss_ntopnbot_MC_ElCS->SetContourLevel(19,13894);
   
   TPaletteAxis *palette = new TPaletteAxis(4.01875,1,4.1875,4,h_ss_ntopnbot_MC_ElCS);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_ntopnbot_MC_ElCS->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_ntopnbot_MC_ElCS->SetLineColor(ci);
   h_ss_ntopnbot_MC_ElCS->SetMarkerSize(2);
   h_ss_ntopnbot_MC_ElCS->GetXaxis()->SetTitle("NTops");
   h_ss_ntopnbot_MC_ElCS->GetXaxis()->SetLabelFont(42);
   h_ss_ntopnbot_MC_ElCS->GetXaxis()->SetLabelSize(0.035);
   h_ss_ntopnbot_MC_ElCS->GetXaxis()->SetTitleSize(0.035);
   h_ss_ntopnbot_MC_ElCS->GetXaxis()->SetTitleFont(42);
   h_ss_ntopnbot_MC_ElCS->GetYaxis()->SetTitle("NBottoms");
   h_ss_ntopnbot_MC_ElCS->GetYaxis()->SetLabelFont(42);
   h_ss_ntopnbot_MC_ElCS->GetYaxis()->SetLabelSize(0.035);
   h_ss_ntopnbot_MC_ElCS->GetYaxis()->SetTitleSize(0.035);
   h_ss_ntopnbot_MC_ElCS->GetYaxis()->SetTitleFont(42);
   h_ss_ntopnbot_MC_ElCS->GetZaxis()->SetLabelFont(42);
   h_ss_ntopnbot_MC_ElCS->GetZaxis()->SetLabelSize(0.035);
   h_ss_ntopnbot_MC_ElCS->GetZaxis()->SetTitleSize(0.035);
   h_ss_ntopnbot_MC_ElCS->GetZaxis()->SetTitleFont(42);
   h_ss_ntopnbot_MC_ElCS->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
