#include "QCDFactors.h"

void QCDFactors::NumbertoTFactor()
{
  //TFactors value calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int k_cal = 0 ; k_cal < QCD_BINS ; k_cal++)
      {
         nQCDNormal_all[i_cal][j_cal] += nQCDNormal[k_cal][i_cal][j_cal];
         nQCDInverted_all[i_cal][j_cal] += nQCDInverted[k_cal][i_cal][j_cal];
         MET_sum_all[i_cal][j_cal] += MET_sum[k_cal][i_cal][j_cal];
         MET_sum_weight_all[i_cal][j_cal] += MET_sum_weight[k_cal][i_cal][j_cal];
         if(MET_sum_weight[k_cal][i_cal][j_cal]>0) MET_mean_err[i_cal][j_cal] += MET_sum[k_cal][i_cal][j_cal]/MET_sum_weight[k_cal][i_cal][j_cal]/MET_sum_weight[k_cal][i_cal][j_cal];
      }
      QCDTFactor[i_cal][j_cal] = nQCDNormal_all[i_cal][j_cal]/nQCDInverted_all[i_cal][j_cal];
      MET_mean[i_cal][j_cal] = MET_sum_all[i_cal][j_cal]/MET_sum_weight_all[i_cal][j_cal];
      MET_mean_err[i_cal][j_cal] = std::sqrt(MET_mean_err[i_cal][j_cal]);
    }
  }

  //TFactor uncertainty calculation
  for(int i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(int j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int k_cal = 0 ; k_cal < QCD_BINS ; k_cal++)
      {
        nQCDNormal_all_err[i_cal][j_cal] += nQCDNormal_MC[k_cal][i_cal][j_cal] * QCDWeights[k_cal] * QCDWeights[k_cal] ;
        nQCDInverted_all_err[i_cal][j_cal] += nQCDInverted_MC[k_cal][i_cal][j_cal] * QCDWeights[k_cal] * QCDWeights[k_cal];
      }
      nQCDNormal_all_err[i_cal][j_cal] = std::sqrt( nQCDNormal_all_err[i_cal][j_cal] );
      nQCDInverted_all_err[i_cal][j_cal] = std::sqrt( nQCDInverted_all_err[i_cal][j_cal] );
      QCDTFactor_err[i_cal][j_cal] = get_aoverb_Error( nQCDNormal_all[i_cal][j_cal] , nQCDInverted_all[i_cal][j_cal] , nQCDNormal_all_err[i_cal][j_cal], nQCDInverted_all_err[i_cal][j_cal] );
    }
  }
 
  double tmp_QCDTNJF[NJETS_BINS] = {0};
  for(int i_cal = 0 ; i_cal < NJETS_BINS ; i_cal++)
  {
    tmp_QCDTNJF[i_cal] = nQCDNormal_NJF_MC_all[i_cal]/nQCDInverted_NJF_MC_all[i_cal];
  }
  for(int i_cal = 0 ; i_cal < NJETS_BINS ; i_cal++)
  {
    //normalized to first bin
    QCDTNJF[i_cal] = tmp_QCDTNJF[i_cal]/tmp_QCDTNJF[0];
    std::cout << "NJet 30 correction factor, Bin " << i_cal << ": " << QCDTNJF[i_cal] << std::endl;
  }
  //MT2 and met mean value calculation in each search bin
  for(int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++)
  {
    if( MET_sum_weight_all_exp_sb[i_cal] > 0 && MT2_sum_weight_all_exp_sb[i_cal] > 0 )
    {
      std::cout << "Bin" << i_cal << ", MET: "<< MET_sum_all_exp_sb[i_cal] << ", " << MET_sum_weight_all_exp_sb[i_cal] << std::endl;
      std::cout << "Bin" << i_cal << ", MT2: "<< MT2_sum_all_exp_sb[i_cal] << ", " << MT2_sum_weight_all_exp_sb[i_cal] << std::endl;
      MET_mean_exp_sb[i_cal] = MET_sum_all_exp_sb[i_cal]/MET_sum_weight_all_exp_sb[i_cal];
      MT2_mean_exp_sb[i_cal] = MT2_sum_all_exp_sb[i_cal]/MT2_sum_weight_all_exp_sb[i_cal];
    }
  }

  std::cout << "Last bin MET: "<< MET_sum_all_exp_sb[NSEARCH_BINS-1] << ", " << MET_sum_weight_all_exp_sb[NSEARCH_BINS-1] << std::endl;
  std::cout << "Last bin MT2: "<< MT2_sum_all_exp_sb[NSEARCH_BINS-1] << ", " << MT2_sum_weight_all_exp_sb[NSEARCH_BINS-1] << std::endl;

  return ;
}

Double_t fitf(Double_t *v, Double_t *par)
{
  //Double_t arg = 0;
  //if (par[2] != 0) arg = (v[0] - par[1])/par[2];

  //Double_t fitval = par[0]*TMath::Exp(-0.5*arg*arg);
  //return fitval;
  Double_t arg = 0;
  arg = v[0];

  Double_t fitval = par[0] + par[1]*arg;
  return fitval;
}

void QCDFactors::TFactorFit()
{
  //const std::string titre="CMS Simulation 2015, #sqrt{s} = 13 TeV";
  //TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  //title->SetNDC();
  //title->SetTextSize(0.045);

  for(int i = 0; i < MT2_BINS; i++)
  {
    std::string pname = "TFactorfit_MT2BIN" + std::to_string(i);

    TCanvas * c = new TCanvas("c", "", 50, 50, 1000, 600);
    gStyle->SetOptStat(0);
    gPad->SetBottomMargin(0.16);
    gPad->SetLeftMargin(0.16);
    gPad->SetTicks();

    TH1F *frame = new TH1F("frame","",10,170.,720.);
    frame->SetMinimum(0.0);
    frame->SetMaximum(0.2);
    frame->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
    frame->GetYaxis()->SetTitle("Translation Factor");
    frame->SetTitleSize(0.045,"X");
    frame->SetTitleSize(0.045,"Y");
    //frame->SetTitle(pname.c_str());
    frame->Draw();

    const Int_t n = MET_BINS;
    Double_t x[n], y[n], ex[n], ey[n], zero[n];
    for (int j = 0 ; j < MET_BINS ; j++)
    {
      x[j] = MET_mean[j][i];
      y[j] = QCDTFactor[j][i];
      ex[j] = MET_mean_err[j][i];
      ey[j] = QCDTFactor_err[j][i];
      zero[j] = 0;
    }
  
    TGraph *gr = new TGraphErrors(n,x,y,ex,ey);

    gr->SetLineColor(2);
    gr->SetLineWidth(4);
    gr->SetMarkerColor(4);
    gr->SetMarkerStyle(21);
    gr->GetXaxis()->SetTitle("#slash{E}_{T} [GeV]");
    gr->GetYaxis()->SetTitle("Translation Factor");

    //create a function with 2 parameters in the range [0,1000]
    TF1 *func = new TF1("fit",fitf,0,1000,2);
    func->SetParameters(0,0.01);
    func->SetParNames("Offset","Slope");
    gr->Fit("fit");

    TFitResultPtr fitRes = gr->Fit(func,"S");
    TMatrixDSym covMat = fitRes->GetCorrelationMatrix();
    covMat.Print();

    double parErrp0 = fitRes->ParError(0), parErrp1 = fitRes->ParError(1);
    printf("parErrp0 : %9.5e  parErrp1 : %9.5e\n", parErrp0, parErrp1);

    double fiterr[MET_BINS];
    double METUpperBand[MET_BINS], METLowerBand[MET_BINS];
    for(int ip=0; ip<MET_BINS; ip++)
    {
      double ptMET = x[ip];
      double perErr = sqrt( ptMET*ptMET*parErrp1*parErrp1*covMat(1, 1)*covMat(1, 1)
                          + parErrp0*parErrp0*covMat(0, 0)*covMat(0, 0)
                          + 2*ptMET*parErrp0*parErrp1*covMat(0, 1) );
      double centralVal = func->Eval(ptMET);
      fiterr[ip] = perErr;
      METUpperBand[ip] = func->Eval(ptMET) + perErr;
      METLowerBand[ip] = func->Eval(ptMET) - perErr;
    }

    TGraphErrors * METUpperBandGraph = new TGraphErrors(MET_BINS, x, METUpperBand, zero, zero);
    TGraphErrors * METLowerBandGraph = new TGraphErrors(MET_BINS, x, METLowerBand, zero, zero);
    TGraph *grshade = new TGraph(2*MET_BINS);
    for (int ip=0;ip<MET_BINS;ip++) 
    {
      grshade->SetPoint(ip,x[ip],METUpperBand[ip]);
      grshade->SetPoint(MET_BINS+ip,x[MET_BINS-ip-1],METLowerBand[MET_BINS-ip-1]);
    }

    grshade->SetFillStyle(3013);
    grshade->Draw("f");
    METUpperBandGraph->SetLineColor(kBlue); METUpperBandGraph->Draw("same");
    METLowerBandGraph->SetLineColor(kBlue); METLowerBandGraph->Draw("same");
    gr->Draw("P");

    //CMSStylePlot::CMS_lumi( c, 0, 0 );

    c->SaveAs( ("_" + pname + ".png").c_str() );
    c->SaveAs( ("_" + pname + ".pdf").c_str() );
    c->SaveAs( ("_" + pname + ".C").c_str() );

    //Get value and uncertainty for Fit TFactor
    for (int j = 0 ; j < MET_BINS ; j++)
    {
      QCDTFactorFit[j][i] = func->Eval( MET_mean[j][i] );
      //temporary solution
      QCDTFactorFit_err[j][i] = fiterr[j];
    }
  }
  return ;
}

void QCDFactors::TFactorScale()
{
  double TFactorsDataMCRatio[MT2_BINS] = {0}, TFactorsDataMCDiff[MT2_BINS] = {0}, TFactorsDataMCUnc[MT2_BINS] = {0};

  for(int i=0;i<MT2_BINS;i++)
  {
    TFactorsDataMCRatio[i] = head_QCDTFactorData[i]/QCDTFactor[0][i];
    //TFactorsDataMCDiff[i] = head_QCDTFactorData[i] - QCDTFactorFit[0][i];
    TFactorsDataMCDiff[i] = head_QCDTFactorData[i] - QCDTFactor[0][i];
    //double r = head_QCDTFactorData[i]/QCDTFactorFit[0][i];
    TFactorsDataMCUnc[i] = head_QCDTFactorData_err[i];
    //r = exp/pred;
    //e = std::sqrt( exp_err*exp_err + pred_err*pred_err*r*r ) / pred;
    //std::sqrt( exp_err*exp_err + pred_err*pred_err*r*r ) * r
    
  }

  for(int i=0;i<MET_BINS;i++)
  {
    for(int j=0;j<MT2_BINS;j++)
    {
      //QCDTFactorScaled[i][j] = QCDTFactorFit[i][j] + TFactorsDataMCDiff[j];
      //QCDTFactorScaled[i][j] = QCDTFactor[i][j] + TFactorsDataMCDiff[j];
      QCDTFactorScaled[i][j] = QCDTFactor[i][j] * TFactorsDataMCRatio[j];
      double tmpunc = QCDTFactor[i][j] + TFactorsDataMCDiff[j];
      if( tmpunc < 0 )
      { 
        std::cout << "METBIN,MT2BIN,TFactorScaled: " << i << "," << j << "," << tmpunc << std::endl;
        tmpunc = 0.000000000001;
      }
      tmpunc = std::abs(QCDTFactorScaled[i][j] - tmpunc);
      //uncertainty of scaled tfactor have 3 parts: statistical, fit, and data MC difference
      //QCDTFactorScaled_err[i][j] = std::sqrt( QCDTFactor_err[i][j]*QCDTFactor_err[i][j]);
      if(i!=0) QCDTFactorScaled_err[i][j] = tmpunc;
      else QCDTFactorScaled_err[i][j] = TFactorsDataMCUnc[j];
      //QCDTFactorScaled_err[i][j] = std::sqrt( QCDTFactor_err[i][j]*QCDTFactor_err[i][j] + QCDTFactorFit_err[i][j]*QCDTFactorFit_err[i][j] + TFactorsDataMCUnc[j]*TFactorsDataMCUnc[j] );
    }
  }

  return ;
}

void QCDFactors::printQCDFactorInfo()
{
  int i_cal,j_cal,k_cal;

  std::cout << "Counting Normal MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < MT2_BINS ; k_cal++)
      {
        std::cout << "QCD Files:" << i_cal << ", METBin:" << j_cal << ",MT2Bin:" << k_cal << "; :" << nQCDNormal_MC[i_cal][j_cal][k_cal] << std::endl;
      }
    }
  }

  std::cout << "Counting Normal: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << nQCDNormal_all[i_cal][j_cal] << "(" << nQCDNormal_all_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  std::cout << "Counting Inverted MC: " << std::endl;
  for( i_cal=0 ; i_cal < QCD_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MET_BINS ; j_cal++)
    {
      for(k_cal = 0 ; k_cal < MT2_BINS ; k_cal++)
      {
        std::cout << "QCD Files:" << i_cal << ", METBin:" << j_cal << ",MT2Bin:" << k_cal << "; :" << nQCDInverted_MC[i_cal][j_cal][k_cal] << std::endl;
      }
    }
  }

  std::cout << "Counting Inverted: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << nQCDInverted_all[i_cal][j_cal] << "(" << nQCDInverted_all_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }


  std::cout << "Mean MET in QCD Bin: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << MET_mean[i_cal][j_cal] << "(" << MET_mean_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }

  std::cout << "Translation Factors: " << std::endl;
  for( i_cal=0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      std::cout << "PreFit, METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactor[i_cal][j_cal] << "(" << QCDTFactor_err[i_cal][j_cal] << ")"<< std::endl;
      std::cout << "PostFit, METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactorFit[i_cal][j_cal] << "(" << QCDTFactorFit_err[i_cal][j_cal] << ")"<< std::endl;
      std::cout << "Scaled, METBin:" << i_cal << ",MT2Bin:" << j_cal << "; :" << QCDTFactorScaled[i_cal][j_cal] << "(" << QCDTFactorScaled_err[i_cal][j_cal] << ")"<< std::endl;
    }
  }
}

void QCDFactors::getAndprintTFactorsfromDataHeader(std::string pred_type)
{
  std::cout << "TFactor in low MET region from Real Data:" << std::endl;
  for( int i=0 ; i<MT2_BINS ; i++ )
  {
    if( pred_type == "MCDriven" )
    { 
      QCDTFactorData[i] = (nQCDNormal_Data_all[i]-nQCDNormal_hadtauMC_all[i]-nQCDNormal_lostleptMC_all[i]-nQCDNormal_zinvMC_all[i]-nQCDNormal_ttzMC_all[i])/(nQCDInverted_Data_all[i]-nQCDInverted_hadtauMC_all[i]-nQCDInverted_lostleptMC_all[i]-nQCDInverted_zinvMC_all[i]-nQCDInverted_ttzMC_all[i]);
      QCDTFactorData_err[i] = get_aoverb_Error( nQCDNormal_Data_all[i] , nQCDInverted_Data_all[i] , nQCDNormal_Data_all_err[i], nQCDInverted_Data_all_err[i] );
    }
    else if( pred_type == "DataDriven" ) 
    {
      QCDTFactorData[i] = (nQCDNormal_Data_all[i]-nQCDNormal_hadtau_all[i]-nQCDNormal_lostlept_all[i]-nQCDNormal_zinvMC_all[i]-nQCDNormal_ttzMC_all[i])/(nQCDInverted_Data_all[i]-nQCDInverted_hadtau_all[i]-nQCDInverted_lostlept_all[i]-nQCDInverted_zinvMC_all[i]-nQCDInverted_ttzMC_all[i]);
      QCDTFactorData_err[i] = get_aoverb_Error( nQCDNormal_Data_all[i] , nQCDInverted_Data_all[i] , nQCDNormal_Data_all_err[i], nQCDInverted_Data_all_err[i] );
    }
    else
    {
      std::cout << "Wrong pred_type! the valid types are : MCDriven and DataDriven!" << std::endl;
    }
    std::cout << "METBin0, MT2Bin (Data)       " << i << " : " << nQCDNormal_Data_all[i]       << "," << nQCDInverted_Data_all[i]       << std::endl;
    std::cout << "METBin0, MT2Bin (HadTau_MC)  " << i << " : " << nQCDNormal_hadtauMC_all[i]   << "," << nQCDInverted_hadtauMC_all[i]   << std::endl;
    std::cout << "METBin0, MT2Bin (HadTau_Data)" << i << " : " << nQCDNormal_hadtau_all[i]     << "," << nQCDInverted_hadtau_all[i]     << std::endl;
    std::cout << "METBin0, MT2Bin (LL_MC)      " << i << " : " << nQCDNormal_lostleptMC_all[i] << "," << nQCDInverted_lostleptMC_all[i] << std::endl;
    std::cout << "METBin0, MT2Bin (LL_Data)    " << i << " : " << nQCDNormal_lostlept_all[i]   << "," << nQCDInverted_lostlept_all[i]   << std::endl;
    std::cout << "METBin0, MT2Bin (Zinv_MC)    " << i << " : " << nQCDNormal_zinvMC_all[i]     << "," << nQCDInverted_zinvMC_all[i]     << std::endl;
    std::cout << "METBin0, MT2Bin (TTZ/W_MC)   " << i << " : " << nQCDNormal_ttzMC_all[i]      << "," << nQCDInverted_ttzMC_all[i]      << std::endl;
    std::cout << pred_type << ":" << std::endl;
    std::cout << "METBin0, MT2Bin" << i << " : " << QCDTFactorData[i] << "(" << QCDTFactorData_err[i] << ")" << std::endl;
  }

  std::ofstream TFactorsfromDataHeader;
  TFactorsfromDataHeader.open ( (header_out + "TFactorsfromDataHeader.h").c_str() );
  
  int i_cal = 0;

  TFactorsfromDataHeader << "  const double head_QCDTFactorData[" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MT2_BINS ; i_cal++ )
  {
    if( i_cal == 0 ) { TFactorsfromDataHeader << "{"; }

    TFactorsfromDataHeader << QCDTFactorData[i_cal];
    
    if( i_cal != MT2_BINS-1 ) { TFactorsfromDataHeader << ","; }
    else { TFactorsfromDataHeader << "};" << std::endl; }
  }

  TFactorsfromDataHeader << "  const double head_QCDTFactorData_err[" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MT2_BINS ; i_cal++ )
  {
    if( i_cal == 0 ) { TFactorsfromDataHeader << "{"; }

    TFactorsfromDataHeader << QCDTFactorData_err[i_cal];

    if( i_cal != MT2_BINS-1 ) { TFactorsfromDataHeader << ","; }
    else { TFactorsfromDataHeader << "};"; }
  }

  return ;
}

void QCDFactors::printTFactorsHeader()
{
  std::ofstream TFactorsHeader;
  TFactorsHeader.open ( (header_out + "TFactorsHeader.h").c_str() );

  int i_cal = 0;
  int j_cal = 0;

  TFactorsHeader << "  const double head_QCDTFactor[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactor[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double head_QCDTFactor_err[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactor_err[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double head_QCDTFactorFit[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorFit[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double head_QCDTFactorFit_err[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorFit_err[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double head_QCDTFactorScaled[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorScaled[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double head_QCDTFactorScaled_err[" << MET_BINS << "][" << MT2_BINS << "] = ";
  for( i_cal = 0 ; i_cal < MET_BINS ; i_cal++ )
  {
    for( j_cal = 0 ; j_cal < MT2_BINS ; j_cal++ )
    {
      if( i_cal == 0 && j_cal == 0 ) { TFactorsHeader << "{{"; }
      if( i_cal != 0 && j_cal == 0 ) { TFactorsHeader << "{"; }

      TFactorsHeader << QCDTFactorScaled_err[i_cal][j_cal];
      if( j_cal != MT2_BINS-1 ) { TFactorsHeader << ","; }

      if( i_cal != MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "},"; }
      if( i_cal == MET_BINS-1 && j_cal == MT2_BINS-1 ) { TFactorsHeader << "}};" << std::endl; }
    }
  }

  TFactorsHeader << "  const double head_QCDTNJF[" << NJETS_BINS << "] = ";
  for(int i_cal = 0 ; i_cal < NJETS_BINS ; i_cal++)
  {
    if(i_cal == 0 ) { TFactorsHeader << "{"; }
    TFactorsHeader << QCDTNJF[i_cal];
    if(i_cal != NJETS_BINS -1 ) { TFactorsHeader << ","; }
    if(i_cal == NJETS_BINS -1 ) { TFactorsHeader << "};" << std::endl; }
  }

  TFactorsHeader << "  const double head_QCDTNJF_err[" << NJETS_BINS << "] = ";
  for(int i_cal = 0 ; i_cal < NJETS_BINS ; i_cal++)
  {
    if(i_cal == 0 ) { TFactorsHeader << "{"; }
    TFactorsHeader << QCDTNJF_err[i_cal];
    if(i_cal != NJETS_BINS -1 ) { TFactorsHeader << ","; }
    if(i_cal == NJETS_BINS -1 ) { TFactorsHeader << "};" << std::endl; }
  }


  TFactorsHeader << "  const double head_QCD_meanMET_exp_sb[" << NSEARCH_BINS << "] = ";
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    if(i_cal == 0 ) { TFactorsHeader << "{"; }
    TFactorsHeader << MET_mean_exp_sb[i_cal];
    if(i_cal != NSEARCH_BINS -1 ) { TFactorsHeader << ","; }
    if(i_cal == NSEARCH_BINS -1 ) { TFactorsHeader << "};" << std::endl; }
  }

  TFactorsHeader << "  const double head_QCD_meanMT2_exp_sb[" << NSEARCH_BINS << "] = ";
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    if(i_cal == 0 ) { TFactorsHeader << "{"; }
    TFactorsHeader << MT2_mean_exp_sb[i_cal];
    if(i_cal != NSEARCH_BINS -1 ) { TFactorsHeader << ","; }
    if(i_cal == NSEARCH_BINS -1 ) { TFactorsHeader << "};" << std::endl; }
  }

  TFactorsHeader.close();
}
/*
void QCDFactors::printQCDClosureExp(ClosureHistgram& myClosureHistgram)
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    myClosureHistgram.h_exp_sb->SetBinContent( i_cal+1 , nQCD_exp_sb[i_cal] );
    myClosureHistgram.h_exp_sb->SetBinError( i_cal+1 , nQCD_exp_sb_err[i_cal] );
  }
  return ;
}

void QCDFactors::printQCDClosurePred(ClosureHistgram& myClosureHistgram)
{
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << nQCD_pred_sb[i_cal] << "," << std::endl;
    myClosureHistgram.h_pred_sb->SetBinContent( i_cal+1 , nQCD_pred_sb[i_cal] );
    myClosureHistgram.h_pred_sb->SetBinError( i_cal+1 , nQCD_pred_sb_err[i_cal] );
  }
  return ;
}
*/
void QCDFactors::TFactorsPlotsGen()
{
  TCanvas *c_prefit = new TCanvas("c_prefit", "",50,50,1200,600);
  c_prefit->SetFillColor(0);
  c_prefit->cd();

  TH2D *tfactors2dPreFit = new TH2D("tfactors_prefit","TFactors PreFit",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  tfactors2dPreFit->SetMarkerSize(1.6);

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2dPreFit->SetBinContent( i_cal+1 , j_cal+1, QCDTFactor[i_cal][j_cal] );
      tfactors2dPreFit->SetBinError( i_cal+1 , j_cal+1, QCDTFactor_err[i_cal][j_cal] );
    }
  }

  tfactors2dPreFit->SetTitle("");
  tfactors2dPreFit->SetXTitle("#slash{E}_{T} [GeV]");
  tfactors2dPreFit->GetXaxis()->SetLabelSize(0.045);
  tfactors2dPreFit->GetXaxis()->SetTitleSize(0.045);
  tfactors2dPreFit->SetYTitle("M_{T2} [GeV]");
  tfactors2dPreFit->GetYaxis()->SetLabelSize(0.045);
  tfactors2dPreFit->GetYaxis()->SetTitleSize(0.045);
  tfactors2dPreFit->GetZaxis()->SetLabelSize(0.045);
  tfactors2dPreFit->GetZaxis()->SetTitleSize(0.045);
  tfactors2dPreFit->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dPreFit->Draw("colztexte");
  //CMSStylePlot::CMS_lumi( c_prefit, 0, 0 );

  c_prefit->SaveAs( (plot_out + "_tfactors2dPreFit.png").c_str() );
  c_prefit->SaveAs( (plot_out + "_tfactors2dPreFit.pdf").c_str() );
  c_prefit->SaveAs( (plot_out + "_tfactors2dPreFit.C").c_str() );
  c_prefit->Close();

  /*
  //Post fit Tfactor plot
  TCanvas *c_postfit = new TCanvas("c_postfit", "",50,50,1200,600);
  c_postfit->SetFillColor(0);
  c_postfit->cd();
  TH2D *tfactors2dPostFit = new TH2D("tfactors_postfit","TFactors PostFit",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  tfactors2dPostFit->SetMarkerSize(1.6);
  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  { 
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    { 
      tfactors2dPostFit->SetBinContent( i_cal+1 , j_cal+1, QCDTFactorFit[i_cal][j_cal] );
      tfactors2dPostFit->SetBinError( i_cal+1 , j_cal+1, QCDTFactorFit_err[i_cal][j_cal] );
    }
  }
  tfactors2dPostFit->SetTitle("");
  tfactors2dPostFit->SetXTitle("#slash{E}_{T} [GeV]");
  tfactors2dPostFit->GetXaxis()->SetLabelSize(0.045);
  tfactors2dPostFit->GetXaxis()->SetTitleSize(0.045);
  tfactors2dPostFit->SetYTitle("M_{T2} [GeV]");
  tfactors2dPostFit->GetYaxis()->SetLabelSize(0.045);
  tfactors2dPostFit->GetYaxis()->SetTitleSize(0.045);
  tfactors2dPostFit->GetZaxis()->SetLabelSize(0.045);
  tfactors2dPostFit->GetZaxis()->SetTitleSize(0.045);
  tfactors2dPostFit->SetStats(0);
  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dPostFit->Draw("colztexte");
  CMSStylePlot::CMS_lumi( c_postfit, 0, 0 );
  c_postfit->SaveAs( (plot_out + "_tfactors2dPostFit.png").c_str() );
  c_postfit->SaveAs( (plot_out + "_tfactors2dPostFit.pdf").c_str() );
  c_postfit->SaveAs( (plot_out + "_tfactors2dPostFit.C").c_str() );
  c_postfit->Close();
  */
  //Scaled Tfactor plot
  TCanvas *c_scaled = new TCanvas("c_scaled", "",50,50,1200,600);
  c_scaled->SetFillColor(0);
  c_scaled->cd();

  TH2D *tfactors2dScaled = new TH2D("tfactors_scaled","TFactors Scaled",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  tfactors2dScaled->SetMarkerSize(1.6);

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      tfactors2dScaled->SetBinContent( i_cal+1 , j_cal+1, QCDTFactorScaled[i_cal][j_cal] );
      tfactors2dScaled->SetBinError( i_cal+1 , j_cal+1, QCDTFactorScaled_err[i_cal][j_cal] );
    }
  }

  tfactors2dScaled->SetTitle("");
  tfactors2dScaled->SetXTitle("#slash{E}_{T} [GeV]");
  tfactors2dScaled->GetXaxis()->SetLabelSize(0.045);
  tfactors2dScaled->GetXaxis()->SetTitleSize(0.045);
  tfactors2dScaled->SetYTitle("M_{T2} [GeV]");
  tfactors2dScaled->GetYaxis()->SetLabelSize(0.045);
  tfactors2dScaled->GetYaxis()->SetTitleSize(0.045);
  tfactors2dScaled->GetZaxis()->SetLabelSize(0.045);
  tfactors2dScaled->GetZaxis()->SetTitleSize(0.045);
  tfactors2dScaled->SetStats(0);

  gStyle->SetPaintTextFormat("1.2f");
  tfactors2dScaled->Draw("colztexte");
  //CMSStylePlot::CMS_lumi( c_scaled, 4, 0 );

  c_scaled->SaveAs( (plot_out + "_tfactors2dScaled.png").c_str() );
  c_scaled->SaveAs( (plot_out + "_tfactors2dScaled.pdf").c_str() );
  c_scaled->SaveAs( (plot_out + "_tfactors2dScaled.C").c_str() );
  c_scaled->Close();

  return ;
}

void QCDFactors::CountingPlotsGen()
{
  TH2D *countNormal_MC  = new TH2D("countNormal_MC","countNormal_MC",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  TH2D *countNormal  = new TH2D("countNormal","countNormal",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  TH2D *countInverted_MC  = new TH2D("countInverted_MC","countInverted_MC",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
  TH2D *countInverted  = new TH2D("countInverted","countInverted",MET_BINS,metbins_edge,MT2_BINS,mt2bins_edge);
      
  double nQCDNormal_MC_all[MET_BINS][MT2_BINS] = {{0}}, nQCDInverted_MC_all[MET_BINS][MT2_BINS] = {{0}};

  int i_cal;
  int j_cal;

  for(i_cal = 0 ; i_cal < MET_BINS ; i_cal++)
  {
    for(j_cal = 0 ; j_cal < MT2_BINS ; j_cal++)
    {
      for(int tmp = 0 ; tmp < QCD_BINS ; tmp++)
      {
        nQCDNormal_MC_all[i_cal][j_cal] +=nQCDNormal_MC[tmp][i_cal][j_cal];
        nQCDInverted_MC_all[i_cal][j_cal] +=nQCDInverted_MC[tmp][i_cal][j_cal];
      }

      countNormal_MC->SetBinContent( i_cal+1 , j_cal+1, nQCDNormal_MC_all[i_cal][j_cal] );
      countNormal->SetBinContent( i_cal+1 , j_cal+1, nQCDNormal_all[i_cal][j_cal] );
      countNormal->SetBinError( i_cal+1 , j_cal+1, nQCDNormal_all_err[i_cal][j_cal] );

      countInverted_MC->SetBinContent( i_cal+1 , j_cal+1, nQCDInverted_MC_all[i_cal][j_cal] );
      countInverted->SetBinContent( i_cal+1 , j_cal+1, nQCDInverted_all[i_cal][j_cal] );
      countInverted->SetBinError( i_cal+1 , j_cal+1, nQCDInverted_all_err[i_cal][j_cal] );
    }
  }

  countNormal_MC->SetTitle("QCD Signal MC");
  countNormal_MC->SetXTitle("#slash{E}_{T} [GeV]");
  countNormal_MC->SetYTitle("M_{T2} [GeV]");
  countNormal_MC->SetStats(0);
  countNormal->SetTitle("QCD Signal Normalized");
  countNormal->SetXTitle("#slash{E}_{T} [GeV]");
  countNormal->SetYTitle("M_{T2} [GeV]");
  countNormal->SetStats(0);
  countInverted_MC->SetTitle("QCD Inverted DeltaPhi MC");
  countInverted_MC->SetXTitle("#slash{E}_{T} [GeV]");
  countInverted_MC->SetYTitle("M_{T2} [GeV]");
  countInverted_MC->SetStats(0);
  countInverted->SetTitle("QCD Inverted DeltaPhi Normalized");
  countInverted->SetXTitle("#slash{E}_{T} [GeV]");
  countInverted->SetYTitle("M_{T2} [GeV]");
  countInverted->SetStats(0);

  //std::ostringstream strs;
  //strs << (LUMI/1000);
  //std::string lumi_str = strs.str();
  //const std::string titre="CMS Preliminary 2015, "+ lumi_str + " fb^{-1}, #sqrt{s} = 13 TeV";
  const std::string titre="CMS Preliminary 2016, 4.0 fb^{-1}, #sqrt{s} = 13 TeV";
  TLatex *title = new TLatex(0.09770115,0.9194915,titre.c_str());
  title->SetNDC();
  title->SetTextSize(0.045);

  TCanvas *c = new TCanvas("c", "c",0,51,1920,1004);
  c->Divide(2,2);
  c->SetFillColor(0);
  gStyle->SetPaintTextFormat("1.2f");
  
  c->cd(1);
  countNormal_MC->Draw("colztexte");
  title->Draw("same");

  c->cd(2);
  countNormal->Draw("colztexte");
  title->Draw("same");

  c->cd(3);
  countInverted_MC->Draw("colztexte");
  title->Draw("same");

  c->cd(4);
  countInverted->Draw("colztexte");
  title->Draw("same");

  c->SaveAs( (plot_out + "_Allcount2d.png").c_str() );
  c->SaveAs( (plot_out + "_Allcount2d.pdf").c_str() );
  c->SaveAs( (plot_out + "_Allcount2d.C").c_str() );
  c->Close();

  return ;
}

void QCDFactors::printSBInfo()
{
  std::cout << "#QCD in Search Bins: " << std::endl;
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << "Search Bin Id:" << i_cal << "; Exp: " << nQCD_exp_sb[i_cal] << "(" << nQCD_exp_sb_err[i_cal] << "); Pred: " << nQCD_pred_sb[i_cal] << "(" << nQCD_pred_sb_err[i_cal] << "); (exp - pred)/pred: " << (nQCD_exp_sb[i_cal] - nQCD_pred_sb[i_cal])/nQCD_pred_sb[i_cal] << std::endl;
  }
  return ;
}

void QCDFactors::printDataCard(std::string pred_type)
{
  std::cout << "Setting Data Card with Pred Type : " << pred_type << std::endl;
  for( int i = 0 ; i < NSEARCH_BINS ; i++ )
  {
    QCD_Data_CS[i] = DC_sb_Data[i];
    DC_sb_Data[i] > 0 ? QCD_Data_CS_relative_err[i] = DC_sb_Data_err[i]/DC_sb_Data[i] : QCD_Data_CS_relative_err[i] = 0;
    if( pred_type == "MCDriven" )
    {
      QCD_otherBG_CS[i] = DC_sb_hadtauMC[i] + DC_sb_lostleptMC[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i];
      QCD_otherBG_CS_relative_errup[i] = std::sqrt( DC_sb_hadtauMC_err[i]*DC_sb_hadtauMC_err[i] + DC_sb_lostleptMC_err[i]*DC_sb_lostleptMC_err[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtauMC[i] + DC_sb_lostleptMC[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
      QCD_otherBG_CS_relative_errdown[i] = std::sqrt( DC_sb_hadtauMC_err[i]*DC_sb_hadtauMC_err[i] + DC_sb_lostleptMC_err[i]*DC_sb_lostleptMC_err[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtauMC[i] + DC_sb_lostleptMC[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
    } 
    else if( pred_type == "DataDriven" )
    {
      QCD_otherBG_CS[i] = DC_sb_hadtau[i] + DC_sb_lostlept[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i];
      QCD_otherBG_CS_relative_errup[i] = std::sqrt( DC_sb_hadtau_errup[i]*DC_sb_hadtau_errup[i] + DC_sb_lostlept_errup[i]*DC_sb_lostlept_errup[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtau[i] + DC_sb_lostlept[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
      QCD_otherBG_CS_relative_errdown[i] = std::sqrt( DC_sb_hadtau_errdown[i]*DC_sb_hadtau_errdown[i] + DC_sb_lostlept_errdown[i]*DC_sb_lostlept_errdown[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtau[i] + DC_sb_lostlept[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
    }
    QCD_TFactor[i] = DC_sb_TFactor[i];
    QCD_TFactor_relative_err[i] = DC_sb_TFactor_err[i];
    //QCD_NonClosure_relative_err[i] = ;
  }

  std::cout << "Printing Data Card..." << std::endl;
	std::cout << printDataCardLine("QCD_Data_CS"                    ,QCD_Data_CS);
  std::cout << printDataCardLine("QCD_Data_CS_relative_err"       ,QCD_Data_CS_relative_err);
  std::cout << printDataCardLine("QCD_otherBG_CS"                 ,QCD_otherBG_CS);
  std::cout << printDataCardLine("QCD_otherBG_CS_relative_errup"  ,QCD_otherBG_CS_relative_errup);
  std::cout << printDataCardLine("QCD_otherBG_CS_relative_errdown",QCD_otherBG_CS_relative_errdown);
  std::cout << printDataCardLine("QCD_TFactor"                    ,QCD_TFactor);
  std::cout << printDataCardLine("QCD_TFactor_relative_err"       ,QCD_TFactor_relative_err);
  std::cout << printDataCardLine("QCD_NonClosure_relative_err"    ,QCD_NonClosure_relative_err);

  /*
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    std::cout << "HadTau: " << DC_sb_hadtau[i_cal] << "(" << DC_sb_hadtau_errup[i_cal] << ")" << std::endl;
    std::cout << "LostLept: " << DC_sb_lostlept[i_cal] << "(" << DC_sb_lostlept_errup[i_cal] << ")" << std::endl;
    std::cout << "Zinv: " << DC_sb_zinvMC[i_cal] << "(" << DC_sb_zinvMC_err[i_cal] << ")" << std::endl;
    std::cout << "TTZ: " << DC_sb_ttzMC[i_cal] << "(" << DC_sb_ttzMC_err[i_cal] << ")" << std::endl;
  }
  */
  return ; 
}

void QCDFactors::printSysHeader(std::string pred_type)
{
  std::cout << "Setting SysHeader with Pred Type : " << pred_type << std::endl;
  for( int i = 0 ; i < NSEARCH_BINS ; i++ )
  {
    QCD_Data_CS[i] = DC_sb_Data[i];
    DC_sb_Data[i] > 0 ? QCD_Data_CS_relative_err[i] = DC_sb_Data_err[i]/DC_sb_Data[i] : QCD_Data_CS_relative_err[i] = 0;
    if( pred_type == "MCDriven" )
    {
      QCD_otherBG_CS[i] = DC_sb_hadtauMC[i] + DC_sb_lostleptMC[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i];
      QCD_otherBG_CS_relative_errup[i] = std::sqrt( DC_sb_hadtauMC_err[i]*DC_sb_hadtauMC_err[i] + DC_sb_lostleptMC_err[i]*DC_sb_lostleptMC_err[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtauMC[i] + DC_sb_lostleptMC[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
      QCD_otherBG_CS_relative_errdown[i] = std::sqrt( DC_sb_hadtauMC_err[i]*DC_sb_hadtauMC_err[i] + DC_sb_lostleptMC_err[i]*DC_sb_lostleptMC_err[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtauMC[i] + DC_sb_lostleptMC[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
    }
    else if( pred_type == "DataDriven" )
    {
      QCD_otherBG_CS[i] = DC_sb_hadtau[i] + DC_sb_lostlept[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i];
      QCD_otherBG_CS_relative_errup[i] = std::sqrt( DC_sb_hadtau_errup[i]*DC_sb_hadtau_errup[i] + DC_sb_lostlept_errup[i]*DC_sb_lostlept_errup[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtau[i] + DC_sb_lostlept[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
      QCD_otherBG_CS_relative_errdown[i] = std::sqrt( DC_sb_hadtau_errdown[i]*DC_sb_hadtau_errdown[i] + DC_sb_lostlept_errdown[i]*DC_sb_lostlept_errdown[i] + DC_sb_zinvMC_err[i]*DC_sb_zinvMC_err[i] + DC_sb_ttzMC_err[i]*DC_sb_ttzMC_err[i] )/(DC_sb_hadtau[i] + DC_sb_lostlept[i] + DC_sb_zinvMC[i] + DC_sb_ttzMC[i]);
    }
    QCD_TFactor[i] = DC_sb_TFactor[i];
    QCD_TFactor_relative_err[i] = DC_sb_TFactor_err[i];
    //QCD_NonClosure_relative_err[i] = ;
  }

  std::ofstream SysHeader;
  SysHeader.open ( (header_out + "SysHeader.h").c_str() );
  SysHeader << "//Printing SysHeader..." << std::endl;
  SysHeader << printSysHeaderLine("head_QCD_Data_CS"                ,QCD_Data_CS);
  //SysHeader << printSysHeaderLine("head_QCD_Data_CS_relative_err" ,QCD_Data_CS_relative_err);
  SysHeader << printSysHeaderLine("head_QCD_otherBG_CS"             ,QCD_otherBG_CS);
  SysHeader << printSysHeaderLine("head_QCD_otherBG_sysup"          ,QCD_otherBG_CS_relative_errup);
  SysHeader << printSysHeaderLine("head_QCD_otherBG_sysdn"          ,QCD_otherBG_CS_relative_errdown);
  SysHeader << printSysHeaderLine("head_QCD_TFactor"                ,QCD_TFactor);  
  SysHeader << printSysHeaderLine("head_QCD_TFactor_relative_err"   ,QCD_TFactor_relative_err);
  //SysHeader << printSysHeaderLine("head_QCD_NonClosure_relative_err",QCD_NonClosure_relative_err);
  
  return ;
}

double QCDFactors::get_aoverb_Error(
                                    double a,
                                    double b,
                                    double ea,
                                    double eb
                                   )
{
  double r = std::abs(a/b);
  double e = std::abs( std::sqrt( ea*ea + eb*eb*r*r ) / b );

  return e;
}

std::string QCDFactors::printDataCardLine(std::string name,double (&nums)[NSEARCH_BINS])
{
  std::string outstr;
  outstr.append(name); outstr.append(" = "); 
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    outstr.append(std::to_string(nums[i_cal])); outstr.append(" ");
    if(i_cal == NSEARCH_BINS-1 ) outstr.append("\n");
  }
  return outstr;
}

std::string QCDFactors::printSysHeaderLine(std::string name,double (&nums)[NSEARCH_BINS])
{
  std::string outstr;
  outstr.append("  const double "); outstr.append(name); outstr.append("["); outstr.append(std::to_string(NSEARCH_BINS)); outstr.append("] = {");
  for( int i_cal = 0 ; i_cal < NSEARCH_BINS ; i_cal++ )
  {
    outstr.append(std::to_string(nums[i_cal]));
    if(i_cal != NSEARCH_BINS-1 ) outstr.append(",");
    else outstr.append("};\n");
  }
  return outstr;
}
