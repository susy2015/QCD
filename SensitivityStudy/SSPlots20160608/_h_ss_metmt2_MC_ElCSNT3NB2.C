void _h_ss_metmt2_MC_ElCSNT3NB2()
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
   Double_t xAxis18[4] = {200, 350, 500, 800}; 
   Double_t yAxis18[2] = {200, 500}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT3NB2 = new TH2D("h_ss_metmt2_MC_ElCSNT3NB2","",3, xAxis18,1, yAxis18);
   h_ss_metmt2_MC_ElCSNT3NB2->SetBinContent(6,191);
   h_ss_metmt2_MC_ElCSNT3NB2->SetBinContent(7,31);
   h_ss_metmt2_MC_ElCSNT3NB2->SetBinContent(8,5);
   h_ss_metmt2_MC_ElCSNT3NB2->SetEntries(227);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContour(20);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(0,5);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(1,14.3);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(2,23.6);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(3,32.9);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(4,42.2);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(5,51.5);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(6,60.8);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(7,70.1);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(8,79.4);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(9,88.7);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(10,98);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(11,107.3);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(12,116.6);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(13,125.9);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(14,135.2);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(15,144.5);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(16,153.8);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(17,163.1);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(18,172.4);
   h_ss_metmt2_MC_ElCSNT3NB2->SetContourLevel(19,181.7);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_ElCSNT3NB2);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT3NB2->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT3NB2->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT3NB2->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT3NB2->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT3NB2->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT3NB2->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB2->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB2->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT3NB2->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT3NB2->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT3NB2->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB2->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB2->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT3NB2->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT3NB2->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB2->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT3NB2->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT3NB2->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : >= 3 Top, 2 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
