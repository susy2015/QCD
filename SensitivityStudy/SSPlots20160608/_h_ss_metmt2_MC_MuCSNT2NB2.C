void _h_ss_metmt2_MC_MuCSNT2NB2()
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
   Double_t xAxis11[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis11[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT2NB2 = new TH2D("h_ss_metmt2_MC_MuCSNT2NB2","",4, xAxis11,3, yAxis11);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(7,5810);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(8,418);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(9,50);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(10,7);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(13,521);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(14,154);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(15,22);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(16,9);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(19,16);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(20,59);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(21,18);
   h_ss_metmt2_MC_MuCSNT2NB2->SetBinContent(22,12);
   h_ss_metmt2_MC_MuCSNT2NB2->SetEntries(7096);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContour(20);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(0,7);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(1,297.15);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(2,587.3);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(3,877.45);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(4,1167.6);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(5,1457.75);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(6,1747.9);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(7,2038.05);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(8,2328.2);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(9,2618.35);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(10,2908.5);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(11,3198.65);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(12,3488.8);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(13,3778.95);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(14,4069.1);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(15,4359.25);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(16,4649.4);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(17,4939.55);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(18,5229.7);
   h_ss_metmt2_MC_MuCSNT2NB2->SetContourLevel(19,5519.85);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_MuCSNT2NB2);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT2NB2->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT2NB2->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT2NB2->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT2NB2->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT2NB2->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB2->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB2->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB2->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB2->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT2NB2->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB2->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB2->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB2->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB2->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB2->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB2->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB2->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB2->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : 2 Top, 2 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
