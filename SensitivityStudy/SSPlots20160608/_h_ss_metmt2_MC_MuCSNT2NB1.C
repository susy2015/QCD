void _h_ss_metmt2_MC_MuCSNT2NB1()
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
   Double_t xAxis9[5] = {200, 350, 500, 650, 1000}; 
   Double_t yAxis9[4] = {200, 350, 450, 600}; 
   
   TH2D *h_ss_metmt2_MC_MuCSNT2NB1 = new TH2D("h_ss_metmt2_MC_MuCSNT2NB1","",4, xAxis9,3, yAxis9);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(7,7669);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(8,585);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(9,38);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(10,5);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(13,744);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(14,191);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(15,36);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(16,7);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(19,28);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(20,87);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(21,24);
   h_ss_metmt2_MC_MuCSNT2NB1->SetBinContent(22,15);
   h_ss_metmt2_MC_MuCSNT2NB1->SetEntries(9429);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContour(20);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(0,5);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(1,388.2);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(2,771.4);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(3,1154.6);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(4,1537.8);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(5,1921);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(6,2304.2);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(7,2687.4);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(8,3070.6);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(9,3453.8);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(10,3837);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(11,4220.2);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(12,4603.4);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(13,4986.6);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(14,5369.8);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(15,5753);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(16,6136.2);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(17,6519.4);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(18,6902.6);
   h_ss_metmt2_MC_MuCSNT2NB1->SetContourLevel(19,7285.8);
   
   TPaletteAxis *palette = new TPaletteAxis(1005,200,1050,600,h_ss_metmt2_MC_MuCSNT2NB1);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h_ss_metmt2_MC_MuCSNT2NB1->GetListOfFunctions()->Add(palette,"br");

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   h_ss_metmt2_MC_MuCSNT2NB1->SetLineColor(ci);
   h_ss_metmt2_MC_MuCSNT2NB1->SetMarkerSize(2);
   h_ss_metmt2_MC_MuCSNT2NB1->GetXaxis()->SetTitle("MET[GeV]");
   h_ss_metmt2_MC_MuCSNT2NB1->GetXaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB1->GetXaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB1->GetXaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB1->GetXaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB1->GetYaxis()->SetTitle("MT2[GeV]");
   h_ss_metmt2_MC_MuCSNT2NB1->GetYaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB1->GetYaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB1->GetYaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB1->GetYaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB1->GetZaxis()->SetLabelFont(42);
   h_ss_metmt2_MC_MuCSNT2NB1->GetZaxis()->SetLabelSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB1->GetZaxis()->SetTitleSize(0.035);
   h_ss_metmt2_MC_MuCSNT2NB1->GetZaxis()->SetTitleFont(42);
   h_ss_metmt2_MC_MuCSNT2NB1->Draw("colztexte");
   TLatex *   tex = new TLatex(0.09770115,0.9194915,"MuCS : 2 Top, 1 Bot  CMS 2016, 8 fb^{-1}, #sqrt{s} = 13 TeV");
tex->SetNDC();
   tex->SetTextSize(0.045);
   tex->SetLineWidth(2);
   tex->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
