void _h_ss_metmt2_MC_MuCSNT1NB2()
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
   Double_t xAxis5[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis5[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT1NB2 = new TH2D("h_ss_metmt2_MC_MuCSNT1NB2","",4, xAxis5,3, yAxis5);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(7,11255);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(8,1025);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(9,104);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(10,20);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(13,424);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(14,238);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(15,22);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(16,7);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(19,3);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(20,59);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(21,31);
   h_ss_metmt2_MC_MuCSNT1NB2->SetBinContent(22,9);
   h_ss_metmt2_MC_MuCSNT1NB2->SetEntries(13197);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContour(20);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(0,3);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(1,565.6);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(2,1128.2);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(3,1690.8);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(4,2253.4);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(5,2816);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(6,3378.6);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(7,3941.2);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(8,4503.8);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(9,5066.4);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(10,5629);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(11,6191.6);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(12,6754.2);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(13,7316.8);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(14,7879.4);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(15,8442);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(16,9004.6);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(17,9567.2);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(18,10129.8);
   h_ss_metmt2_MC_MuCSNT1NB2->SetContourLevel(19,10692.4);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_MuCSNT1NB2);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT1NB2->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT1NB2->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT1NB2->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT1NB2->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT1NB2->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB2->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB2->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB2->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB2->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT1NB2->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB2->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB2->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB2->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB2->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB2->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB2->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB2->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB2->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : 1 Top, 2 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
