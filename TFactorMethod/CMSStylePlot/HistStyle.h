#ifndef HIST_STYLE_H
#define HIST_STYLE_H

#include "TCanvas.h"
#include "TStyle.h"

class HistStyle 
{
 public:
	static void init();
  static void adaptForColZ(TCanvas* can);
};

void HistStyle::init()
{
  // Zero horizontal error bars
  gStyle->SetErrorX(0);

  // For the canvas
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetCanvasDefH(800); //Height of canvas
  gStyle->SetCanvasDefW(600); //Width of canvas
  gStyle->SetCanvasDefX(0);   //Position on screen
  gStyle->SetCanvasDefY(0);
  
  // For the frame
  gStyle->SetFrameBorderMode(0);
  gStyle->SetFrameBorderSize(1);
  gStyle->SetFrameFillColor(kBlack);
  gStyle->SetFrameFillStyle(0);
  gStyle->SetFrameLineColor(kBlack);
  gStyle->SetFrameLineStyle(0);
  gStyle->SetFrameLineWidth(1);
    
  // For the Pad
  gStyle->SetPadBorderMode(0);
  gStyle->SetPadColor(kWhite);
  gStyle->SetPadGridX(false);
  gStyle->SetPadGridY(false);
  gStyle->SetGridColor(0);
  gStyle->SetGridStyle(3);
  gStyle->SetGridWidth(1);
  
  // Margins
  gStyle->SetPadTopMargin(0.08);
  gStyle->SetPadBottomMargin(0.19);
  gStyle->SetPadLeftMargin(0.20);
  gStyle->SetPadRightMargin(0.07);

  // For the histo:
  gStyle->SetHistLineColor(kBlack);
  gStyle->SetHistLineStyle(0);
  gStyle->SetHistLineWidth(2);
  gStyle->SetMarkerSize(1.4);
  gStyle->SetEndErrorSize(4);
  
  //  For the statistics box:
  gStyle->SetOptStat(0);
  
  // For the axis
  gStyle->SetAxisColor(1,"XYZ");
  gStyle->SetTickLength(0.03,"XYZ");
  gStyle->SetNdivisions(510,"XYZ");
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetStripDecimals(kFALSE);
  
  // For the axis labels and titles
  gStyle->SetTitleColor(1,"XYZ");
  gStyle->SetLabelColor(1,"XYZ");
  gStyle->SetLabelFont(42,"XYZ");
  gStyle->SetLabelOffset(0.007,"XYZ");
  gStyle->SetLabelSize(0.045,"XYZ");
  gStyle->SetTitleFont(42,"XYZ");
  gStyle->SetTitleSize(0.06,"XYZ");
  gStyle->SetTitleXOffset(1.2);
  gStyle->SetTitleYOffset(1.6);

  // For the title
  gStyle->SetTitleFont(42,"");
  gStyle->SetTitleBorderSize(0);
  gStyle->SetTitleAlign(13);
  gStyle->SetTitleX(0.16);
  gStyle->SetTitleH(0.05);

  // For the legend
  gStyle->SetLegendBorderSize(0);
}

void HistStyle::adaptForColZ(TCanvas* can) 
{
  can->SetRightMargin(can->GetRightMargin()+0.07);
  can->SetBottomMargin(can->GetBottomMargin()+0.03);
  can->SetTopMargin(can->GetTopMargin()+0.04);
}
#endif
