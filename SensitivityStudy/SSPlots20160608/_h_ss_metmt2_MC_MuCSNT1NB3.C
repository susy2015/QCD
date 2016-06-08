void _h_ss_metmt2_MC_MuCSNT1NB3()
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
   Double_t xAxis7[4] = {200, 350, 500, 800}; 
   Double_t yAxis7[3] = {200, 350, 500}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT1NB3 = new TH2D("h_ss_metmt2_MC_MuCSNT1NB3","",3, xAxis7,2, yAxis7);
   h_ss_metmt2_MC_MuCSNT1NB3->SetBinContent(6,1616);
   h_ss_metmt2_MC_MuCSNT1NB3->SetBinContent(7,141);
   h_ss_metmt2_MC_MuCSNT1NB3->SetBinContent(8,21);
   h_ss_metmt2_MC_MuCSNT1NB3->SetBinContent(11,117);
   h_ss_metmt2_MC_MuCSNT1NB3->SetBinContent(12,52);
   h_ss_metmt2_MC_MuCSNT1NB3->SetBinContent(13,20);
   h_ss_metmt2_MC_MuCSNT1NB3->SetEntries(1967);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContour(20);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(0,20);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(1,99.8);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(2,179.6);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(3,259.4);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(4,339.2);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(5,419);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(6,498.8);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(7,578.6);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(8,658.4);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(9,738.2);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(10,818);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(11,897.8);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(12,977.6);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(13,1057.4);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(14,1137.2);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(15,1217);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(16,1296.8);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(17,1376.6);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(18,1456.4);
   h_ss_metmt2_MC_MuCSNT1NB3->SetContourLevel(19,1536.2);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_MuCSNT1NB3);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT1NB3->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT1NB3->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT1NB3->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT1NB3->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT1NB3->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB3->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB3->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB3->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB3->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT1NB3->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB3->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB3->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB3->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB3->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT1NB3->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB3->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT1NB3->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT1NB3->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : 1 Top, >=3 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
