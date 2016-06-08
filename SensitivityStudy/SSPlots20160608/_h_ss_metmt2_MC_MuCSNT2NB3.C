void _h_ss_metmt2_MC_MuCSNT2NB3()
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
   Double_t xAxis13[4] = {200, 350, 500, 800}; 
   Double_t yAxis13[3] = {200, 350, 500}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT2NB3 = new TH2D("h_ss_metmt2_MC_MuCSNT2NB3","",3, xAxis13,2, yAxis13);
   h_ss_metmt2_MC_MuCSNT2NB3->SetBinContent(6,718);
   h_ss_metmt2_MC_MuCSNT2NB3->SetBinContent(7,60);
   h_ss_metmt2_MC_MuCSNT2NB3->SetBinContent(8,8);
   h_ss_metmt2_MC_MuCSNT2NB3->SetBinContent(11,89);
   h_ss_metmt2_MC_MuCSNT2NB3->SetBinContent(12,29);
   h_ss_metmt2_MC_MuCSNT2NB3->SetBinContent(13,17);
   h_ss_metmt2_MC_MuCSNT2NB3->SetEntries(921);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContour(20);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(0,8);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(1,43.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(2,79);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(3,114.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(4,150);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(5,185.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(6,221);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(7,256.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(8,292);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(9,327.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(10,363);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(11,398.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(12,434);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(13,469.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(14,505);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(15,540.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(16,576);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(17,611.5);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(18,647);
   h_ss_metmt2_MC_MuCSNT2NB3->SetContourLevel(19,682.5);
   
   TPaletteAxis *palette = new TPaletteAxis(803.75,200,837.5,500,h_ss_metmt2_MC_MuCSNT2NB3);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT2NB3->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT2NB3->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT2NB3->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT2NB3->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT2NB3->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB3->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB3->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB3->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB3->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT2NB3->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB3->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB3->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB3->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB3->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB3->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB3->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB3->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB3->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : 2 Top, >=3 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
