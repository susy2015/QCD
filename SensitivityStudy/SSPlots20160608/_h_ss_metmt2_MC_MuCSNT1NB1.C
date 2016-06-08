void _h_ss_metmt2_MC_MuCSNT1NB1()
{
//=========Macro generated from canvas: c/
//=========  (Wed Jun  8 08:54:41 2016) by ROOT version6.02/05
   TCanvas *c = new TCanvas("c", "",0,0,800,600);
   gStyle->SetOptStat(0);
   c->SetHighLightColor(2);
   c->Range(99.99999,150,1100,650);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetFrameBorderMode(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis3[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis3[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT1NB1 = new TH2D("h_ss_metmt2_MC_MuCSNT1NB1","",4, xAxis3,3, yAxis3);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(7,12867);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(8,1004);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(9,99);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(10,11);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(13,1232);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(14,482);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(15,35);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(16,9);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(19,23);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(20,200);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(21,80);
   h_ss_metmt2_MC_MuCSNT1NB1->SetBinContent(22,16);
   h_ss_metmt2_MC_MuCSNT1NB1->SetEntries(16058);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContour(20);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(0,9);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(1,651.9);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(2,1294.8);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(3,1937.7);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(4,2580.6);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(5,3223.5);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(6,3866.4);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(7,4509.3);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(8,5152.2);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(9,5795.1);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(10,6438);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(11,7080.9);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(12,7723.8);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(13,8366.7);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(14,9009.6);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(15,9652.5);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(16,10295.4);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(17,10938.3);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(18,11581.2);
   h_ss_metmt2_MC_MuCSNT1NB1->SetContourLevel(19,12224.1);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_MuCSNT1NB1);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT1NB1->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT1NB1->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT1NB1->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT1NB1->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT1NB1->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB1->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB1->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB1->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB1->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT1NB1->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB1->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB1->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB1->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB1->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB1->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB1->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB1->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB1->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : 1 Top, 1 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
