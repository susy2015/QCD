void _h_ss_metmt2_MC_ElCSNT1NB3()
{
//=========Macro generated from canvas: c/
//=========  (Wed Jun  8 08:54:42 2016) by ROOT version6.02/05
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(125,162.5,875,537.5);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis8[4] = {200, 350, 500, 800}; 
   Double_t yAxis8[3] = {200, 350, 500}; 
   
   TH2D *h_ss_metmt2_MC_ElCSNT1NB3 = new TH2D("h_ss_metmt2_MC_ElCSNT1NB3","",3, xAxis8,2, yAxis8);
   h_ss_metmt2_MC_ElCSNT1NB3->SetBinContent(6,1494);
   h_ss_metmt2_MC_ElCSNT1NB3->SetBinContent(7,112);
   h_ss_metmt2_MC_ElCSNT1NB3->SetBinContent(8,14);
   h_ss_metmt2_MC_ElCSNT1NB3->SetBinContent(11,97);
   h_ss_metmt2_MC_ElCSNT1NB3->SetBinContent(12,52);
   h_ss_metmt2_MC_ElCSNT1NB3->SetBinContent(13,15);
   h_ss_metmt2_MC_ElCSNT1NB3->SetEntries(1784);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContour(20);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(0,14);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(1,88);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(2,162);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(3,236);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(4,310);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(5,384);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(6,458);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(7,532);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(8,606);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(9,680);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(10,754);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(11,828);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(12,902);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(13,976);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(14,1050);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(15,1124);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(16,1198);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(17,1272);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(18,1346);
   h_ss_metmt2_MC_ElCSNT1NB3->SetContourLevel(19,1420);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_ElCSNT1NB3);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_ElCSNT1NB3->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_ElCSNT1NB3->SetLineColor(ci);
   h_ss_metmt2_MC_ElCSNT1NB3->SetMarkerSize(2);
   h_ss_metmt2_MC_ElCSNT1NB3->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_ElCSNT1NB3->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB3->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB3->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB3->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB3->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_ElCSNT1NB3->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB3->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB3->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB3->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB3->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_ElCSNT1NB3->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB3->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_ElCSNT1NB3->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_ElCSNT1NB3->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"ElCS : 1 Top, >=3 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
