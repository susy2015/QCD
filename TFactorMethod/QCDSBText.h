void QCDdrawSBregionDef(const double ymin_Yields, const double ymax_Yields, const bool logscale, const bool drawOnlyLines)
{
  int NSB = 84;
  const double adjHalfBin = 0.5;
  const double deltaY = ymax_Yields - ymin_Yields;
  //-----------------------------------------------------------
  // Putting lines and labels explaining search region definitions
  //-----------------------------------------------------------
  // Best result seen for NSB == 84
  // Y axis Max = max*100 for logscale
  // Y axis max  = max_yields* 1.1 for non log case
  //----------------------------------------------------------- 

  // Ntop separation lines
  TLine *tl_ntop = new TLine();
  tl_ntop->SetLineStyle(2);
  if(NSB == 84) 
  {
    tl_ntop->DrawLine(47.5 + adjHalfBin,ymin_Yields,47.5 + adjHalfBin,ymax_Yields);
    tl_ntop->DrawLine(77.5 + adjHalfBin,ymin_Yields,77.5 + adjHalfBin,ymax_Yields);
  }
  else if(NSB == 59)
  {
    tl_ntop->DrawLine(27.5 + adjHalfBin,ymin_Yields,27.5 + adjHalfBin,ymax_Yields);
    tl_ntop->DrawLine(52.5 + adjHalfBin,ymin_Yields,52.5 + adjHalfBin,ymax_Yields);
  }
  else if(NSB == 45)
  {
    tl_ntop->DrawLine(23.5 + adjHalfBin,ymin_Yields,23.5 + adjHalfBin,ymax_Yields);
    tl_ntop->DrawLine(41.5 + adjHalfBin,ymin_Yields,41.5 + adjHalfBin,ymax_Yields);
  } 
  else if(NSB == 37)
  {
    tl_ntop->DrawLine(20.5 + adjHalfBin,ymin_Yields,20.5 + adjHalfBin,ymax_Yields);
  }

  // Ntop labels
  TLatex * ttext_ntop = new TLatex();
  ttext_ntop->SetTextFont(42);
  ttext_ntop->SetTextSize(0.045);
  ttext_ntop->SetTextAlign(22);

  if( !drawOnlyLines )
  {
    if(logscale)
    {
      if(NSB == 84)
      {
        ttext_ntop->DrawLatex(20.5 + adjHalfBin, ymax_Yields/2 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(57.5 + adjHalfBin, ymax_Yields/10. ,"N_{t} = 2");
        ttext_ntop->SetTextAngle(90.);
        ttext_ntop->DrawLatex(79.5 + adjHalfBin, ymax_Yields/10. ,"N_{t} #geq 3");
      }
      else if(NSB == 59)
      {
        ttext_ntop->DrawLatex(11.5 + adjHalfBin, ymax_Yields/2 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(39.5 + adjHalfBin, ymax_Yields/2000. ,"N_{t} = 2");
        ttext_ntop->SetTextAngle(90.);
        ttext_ntop->DrawLatex(54.5 + adjHalfBin, ymax_Yields/20. ,"N_{t} #geq 3");
      }
      else if(NSB == 45)
      {
        ttext_ntop->DrawLatex(11.5 + adjHalfBin, ymax_Yields/3 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(32.5 + adjHalfBin, ymax_Yields/300. ,"N_{t} = 2");
        ttext_ntop->SetTextAngle(90.);
        ttext_ntop->DrawLatex(42.5 + adjHalfBin, ymax_Yields/30. ,"N_{t} #geq 3"); 
      } 
      else if (NSB == 37)
      {
        ttext_ntop->DrawLatex(10 + adjHalfBin, ymax_Yields/1.8 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(29.5 + adjHalfBin, ymax_Yields/70. ,"N_{t} #geq 2");
      }
    }
    else
    {
      if(NSB == 84)
      {
        ttext_ntop->DrawLatex(17.5 + adjHalfBin, ymax_Yields*0.85 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(55.5 + adjHalfBin, ymax_Yields*0.85 ,"N_{t} = 2");
        ttext_ntop->SetTextAngle(90.);
        ttext_ntop->DrawLatex(78.5 + adjHalfBin, ymax_Yields*0.64 ,"N_{t} #geq 3");
      }
      else if(NSB == 59)
      {
        ttext_ntop->DrawLatex(11.5 + adjHalfBin, ymax_Yields*0.93 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(38.5 + adjHalfBin, ymax_Yields*0.93 ,"N_{t} = 2");
        ttext_ntop->SetTextAngle(90.);
        ttext_ntop->DrawLatex(55.5 + adjHalfBin, ymax_Yields*0.85 ,"N_{t} #geq 3");
      }
      else if(NSB == 45)
      {
        ttext_ntop->DrawLatex(11.5 + adjHalfBin, ymax_Yields*0.93 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(35.5 + adjHalfBin, ymax_Yields*0.93 ,"N_{t} = 2");
        ttext_ntop->SetTextAngle(90.);
        ttext_ntop->DrawLatex(43. + adjHalfBin, ymax_Yields*0.85 ,"N_{t} #geq 3");
      }
      else if(NSB == 37)
      {
        ttext_ntop->DrawLatex(10 + adjHalfBin, ymax_Yields*0.93 ,"N_{t} = 1");
        ttext_ntop->DrawLatex(29.5 + adjHalfBin, ymax_Yields*0.93 ,"N_{t} #geq 2");
      }
    }
  }
  // Nb separation lines
  TLine *tl_nb = new TLine();
  tl_nb->SetLineStyle(3);
  tl_nb->SetLineColor(32);
  if(logscale)
  {
    if(NSB == 84)
    {
      //To be filled
      tl_nb->DrawLine(20.5 + adjHalfBin,ymin_Yields,20.5 + adjHalfBin,ymax_Yields/5.);
      tl_nb->DrawLine(36.5 + adjHalfBin,ymin_Yields,36.5 + adjHalfBin,ymax_Yields/5.);
      tl_nb->DrawLine(57.5 + adjHalfBin,ymin_Yields,57.5 + adjHalfBin,ymax_Yields/50.);
      tl_nb->DrawLine(67.5 + adjHalfBin,ymin_Yields,67.5 + adjHalfBin,ymax_Yields/50.);
      tl_nb->DrawLine(79.5 + adjHalfBin,ymin_Yields,79.5 + adjHalfBin,ymax_Yields/50.);
      tl_nb->DrawLine(81.5 + adjHalfBin,ymin_Yields,81.5 + adjHalfBin,ymax_Yields/50.);
    }
    else if(NSB == 59)
    {
      tl_nb->DrawLine(11.5 + adjHalfBin,ymin_Yields,11.5 + adjHalfBin,ymax_Yields/60);
      tl_nb->DrawLine(22.5 + adjHalfBin,ymin_Yields,22.5 + adjHalfBin,ymax_Yields/600.);
      tl_nb->DrawLine(39.5 + adjHalfBin,ymin_Yields,39.5 + adjHalfBin,ymax_Yields/16000.);
      tl_nb->DrawLine(48.5 + adjHalfBin,ymin_Yields,48.5 + adjHalfBin,ymax_Yields/16000.);
      tl_nb->DrawLine(54.5 + adjHalfBin,ymin_Yields,54.5 + adjHalfBin,ymax_Yields/16000.);
      tl_nb->DrawLine(56.5 + adjHalfBin,ymin_Yields,56.5 + adjHalfBin,ymax_Yields/16000.);  
    }
    else if(NSB == 45)
    {
      tl_nb->DrawLine(10.5 + adjHalfBin,ymin_Yields,10.5 + adjHalfBin,ymax_Yields/40.);
      tl_nb->DrawLine(20.5 + adjHalfBin,ymin_Yields,20.5 + adjHalfBin,ymax_Yields/40.);
      tl_nb->DrawLine(31.5 + adjHalfBin,ymin_Yields,31.5 + adjHalfBin,ymax_Yields/400.);
      tl_nb->DrawLine(39.5 + adjHalfBin,ymin_Yields,39.5 + adjHalfBin,ymax_Yields/400.);
      tl_nb->DrawLine(42.5 + adjHalfBin,ymin_Yields,42.5 + adjHalfBin,ymax_Yields/400.);
      tl_nb->DrawLine(43.5 + adjHalfBin,ymin_Yields,43.5 + adjHalfBin,ymax_Yields/400.);
    }
    else if (NSB == 37)
    {
      tl_nb->DrawLine(10.5 + adjHalfBin,ymin_Yields,10.5 + adjHalfBin,ymax_Yields/4.);
      tl_nb->DrawLine(28.5 + adjHalfBin,ymin_Yields,28.5 + adjHalfBin,ymax_Yields/160.);
    }
  }
  else
  {
    if(NSB == 84)
    {
      tl_nb->DrawLine(20.5 + adjHalfBin,ymin_Yields,20.5 + adjHalfBin,ymax_Yields*0.85);
      tl_nb->DrawLine(36.5 + adjHalfBin,ymin_Yields,36.5 + adjHalfBin,ymax_Yields*0.85);
      tl_nb->DrawLine(57.5 + adjHalfBin,ymin_Yields,57.5 + adjHalfBin,ymax_Yields*0.85);
      tl_nb->DrawLine(67.5 + adjHalfBin,ymin_Yields,67.5 + adjHalfBin,ymax_Yields*0.85);
      tl_nb->DrawLine(79.5 + adjHalfBin,ymin_Yields,79.5 + adjHalfBin,ymax_Yields*0.85);
      tl_nb->DrawLine(81.5 + adjHalfBin,ymin_Yields,81.5 + adjHalfBin,ymax_Yields*0.85);
    }
    else if(NSB == 59)
    {
      tl_nb->DrawLine(11.5 + adjHalfBin,ymin_Yields,11.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(22.5 + adjHalfBin,ymin_Yields,22.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(39.5 + adjHalfBin,ymin_Yields,39.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(48.5 + adjHalfBin,ymin_Yields,48.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(54.5 + adjHalfBin,ymin_Yields,54.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(56.5 + adjHalfBin,ymin_Yields,56.5 + adjHalfBin,ymax_Yields*0.8);
    }
    else if(NSB == 45)
    {
      tl_nb->DrawLine(10.5 + adjHalfBin,ymin_Yields,10.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(20.5 + adjHalfBin,ymin_Yields,20.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(31.5 + adjHalfBin,ymin_Yields,31.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(39.5 + adjHalfBin,ymin_Yields,39.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(42.5 + adjHalfBin,ymin_Yields,42.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(43.5 + adjHalfBin,ymin_Yields,43.5 + adjHalfBin,ymax_Yields*0.8);
    } 
    else if (NSB == 37)
    {
      tl_nb->DrawLine(10.5 + adjHalfBin,ymin_Yields,10.5 + adjHalfBin,ymax_Yields*0.8);
      tl_nb->DrawLine(28.5 + adjHalfBin,ymin_Yields,28.5 + adjHalfBin,ymax_Yields*0.8);
    }
  }
  // Nb labels
  TLatex * ttext2 = new TLatex();
  ttext2->SetTextFont(42);
  //ttext2->SetTextColor(32);
  ttext2->SetTextColor(kBlack);
  ttext2->SetTextSize(0.045);
  ttext2->SetTextAlign(22);
  ttext2->Draw();

  if( !drawOnlyLines )
  {
    if(logscale)
    {
      ttext2->DrawLatex( 9.5 + adjHalfBin, ymax_Yields/5., "N_{b} = 1");
      if(NSB == 84)
      {
        ttext2->DrawLatex(27.5 + adjHalfBin, ymax_Yields/5, "N_{b} = 2");
        ttext2->SetTextAngle(90.);
        ttext2->DrawLatex(41.5  + adjHalfBin, ymax_Yields/5, "N_{b} #geq 3");
      }
      else if(NSB == 59)
      {
        ttext2->DrawLatex(17.5 + adjHalfBin, ymax_Yields/1000., "N_{b} = 2");
        ttext2->SetTextAngle(90.);
        ttext2->DrawLatex(23.5  + adjHalfBin, ymax_Yields/30000 , "N_{b} #geq 3");
      }
      else if(NSB == 37) ttext2->DrawLatex(14.5 + adjHalfBin, ymax_Yields/3.5, "N_{b} #geq 2");
      else if(NSB == 45)
      {
        ttext2->DrawLatex(14.5 + adjHalfBin, ymax_Yields/7, "N_{b} = 2");
        ttext2->SetTextAngle(90.);
        ttext2->DrawLatex(22.5  + adjHalfBin, ymax_Yields/20 , "N_{b} #geq 3");
      }
    }
    else
    {
      ttext2->DrawLatex( 4.5 + adjHalfBin, ymax_Yields*0.87, "N_{b} = 1");
      if(NSB == 84)
      {
        ttext2->DrawLatex(27.5 + adjHalfBin, ymax_Yields*0.87, "N_{b} = 2");
        ttext2->SetTextAngle(90.);
        ttext2->DrawLatex(40.5 + adjHalfBin + 0.5, ymax_Yields*0.8, "N_{b} #geq 3");
      }
      else if(NSB == 37) ttext2->DrawLatex(14.5 + adjHalfBin, ymax_Yields*0.8, "N_{b} #geq 2");
      else if(NSB == 45)
      {
        ttext2->DrawLatex(14.5 + adjHalfBin, ymax_Yields*0.87, "N_{b} = 2");
        ttext2->SetTextAngle(90.);
        ttext2->DrawLatex(21.5 + adjHalfBin + 0.5, ymax_Yields*0.87, "N_{b} #geq 3");
      }
      else if(NSB == 59)
      {
        ttext2->DrawLatex(17.5 + adjHalfBin, ymax_Yields*0.87, "N_{b} = 2");
        ttext2->SetTextAngle(90.);
        ttext2->DrawLatex(25.5 + adjHalfBin + 0.5, ymax_Yields*0.87, "N_{b} #geq 3");
      }
    }
  }

  // MT2 separation lines
  TLine *tl_mt2 = new TLine();
  tl_mt2->SetLineStyle(4);
  tl_mt2->SetLineColor(49);
  if(logscale)
  {
    tl_mt2->DrawLine(3.5 + adjHalfBin,ymin_Yields,3.5 + adjHalfBin,ymax_Yields/100.);
    tl_mt2->DrawLine(7.5 + adjHalfBin,ymin_Yields,7.5 + adjHalfBin,ymax_Yields/100.);
    if(NSB == 84)
    { 
      tl_mt2->DrawLine(11.5 + adjHalfBin,ymin_Yields,11.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(16.5 + adjHalfBin,ymin_Yields,16.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(24.5 + adjHalfBin,ymin_Yields,24.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(29.5 + adjHalfBin,ymin_Yields,29.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(33.5 + adjHalfBin,ymin_Yields,33.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(40.5 + adjHalfBin,ymin_Yields,40.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(44.5 + adjHalfBin,ymin_Yields,44.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(50.5 + adjHalfBin,ymin_Yields,50.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(54.5 + adjHalfBin,ymin_Yields,54.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(61.5 + adjHalfBin,ymin_Yields,61.5 + adjHalfBin,ymax_Yields/100.);
      tl_mt2->DrawLine(72.5 + adjHalfBin,ymin_Yields,72.5 + adjHalfBin,ymax_Yields/100.);
    }
    else if(NSB == 59)
    {
      tl_mt2->DrawLine(15.5 + adjHalfBin,ymin_Yields,15.5 + adjHalfBin,ymax_Yields/400000.);
      tl_mt2->DrawLine(19.5 + adjHalfBin,ymin_Yields,19.5 + adjHalfBin,ymax_Yields/400000.);
      tl_mt2->DrawLine(25.5 + adjHalfBin,ymin_Yields,25.5 + adjHalfBin,ymax_Yields/10000.);
      tl_mt2->DrawLine(31.5 + adjHalfBin,ymin_Yields,31.5 + adjHalfBin,ymax_Yields/10000.);
      tl_mt2->DrawLine(35.5 + adjHalfBin,ymin_Yields,35.5 + adjHalfBin,ymax_Yields/32000.);
      tl_mt2->DrawLine(42.5 + adjHalfBin,ymin_Yields,42.5 + adjHalfBin,ymax_Yields/32000.);
      tl_mt2->DrawLine(45.5 + adjHalfBin,ymin_Yields,45.5 + adjHalfBin,ymax_Yields/32000.);
      tl_mt2->DrawLine(50.5 + adjHalfBin,ymin_Yields,50.5 + adjHalfBin,ymax_Yields/32000.);
    }
    else if(NSB == 45)
    {
      tl_mt2->DrawLine(14.5 + adjHalfBin,ymin_Yields,14.5 + adjHalfBin,ymax_Yields/300.);
      tl_mt2->DrawLine(18.5 + adjHalfBin,ymin_Yields,18.5 + adjHalfBin,ymax_Yields/300.);
      tl_mt2->DrawLine(26.5 + adjHalfBin,ymin_Yields,26.5 + adjHalfBin,ymax_Yields/300.);
      tl_mt2->DrawLine(29.5 + adjHalfBin,ymin_Yields,29.5 + adjHalfBin,ymax_Yields/300.);
      tl_mt2->DrawLine(34.5 + adjHalfBin,ymin_Yields,34.5 + adjHalfBin,ymax_Yields/300.);
      tl_mt2->DrawLine(37.5 + adjHalfBin,ymin_Yields,37.5 + adjHalfBin,ymax_Yields/300.);
    } 
    else if(NSB == 37)
    {
      tl_mt2->DrawLine(14.5 + adjHalfBin,ymin_Yields,14.5 + adjHalfBin,ymax_Yields/500.);
      tl_mt2->DrawLine(18.5 + adjHalfBin,ymin_Yields,18.5 + adjHalfBin,ymax_Yields/500.);
      tl_mt2->DrawLine(23.5 + adjHalfBin,ymin_Yields,23.5 + adjHalfBin,ymax_Yields/320.);
      tl_mt2->DrawLine(26.5 + adjHalfBin,ymin_Yields,26.5 + adjHalfBin,ymax_Yields/320.);
      tl_mt2->DrawLine(31.5 + adjHalfBin,ymin_Yields,31.5 + adjHalfBin,ymax_Yields/320.);
      tl_mt2->DrawLine(34.5 + adjHalfBin,ymin_Yields,34.5 + adjHalfBin,ymax_Yields/320.);
    }
  } 
  else
  {
    tl_mt2->DrawLine( 3.5 + adjHalfBin, ymin_Yields,  3.5 + adjHalfBin, ymax_Yields*0.6);
    tl_mt2->DrawLine( 7.5 + adjHalfBin, ymin_Yields,  7.5 + adjHalfBin, ymax_Yields*0.6);
    if(NSB == 84)
    {
      //To be filled
      tl_mt2->DrawLine(24.5 + adjHalfBin,ymin_Yields,24.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(29.5 + adjHalfBin,ymin_Yields,29.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(33.5 + adjHalfBin,ymin_Yields,33.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(40.5 + adjHalfBin,ymin_Yields,40.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(44.5 + adjHalfBin,ymin_Yields,44.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(50.5 + adjHalfBin,ymin_Yields,50.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(54.5 + adjHalfBin,ymin_Yields,54.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(61.5 + adjHalfBin,ymin_Yields,61.5 + adjHalfBin,ymax_Yields*0.6);
      tl_mt2->DrawLine(72.5 + adjHalfBin,ymin_Yields,72.5 + adjHalfBin,ymax_Yields*0.6);
    }
    else if(NSB == 59)
    { 
      tl_mt2->DrawLine(15.5 + adjHalfBin, ymin_Yields, 15.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(19.5 + adjHalfBin, ymin_Yields, 19.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(25.5 + adjHalfBin, ymin_Yields, 25.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(31.5 + adjHalfBin, ymin_Yields, 31.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(35.5 + adjHalfBin, ymin_Yields, 35.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(42.5 + adjHalfBin, ymin_Yields, 42.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(45.5 + adjHalfBin, ymin_Yields, 45.5 + adjHalfBin, ymax_Yields*0.06);
      tl_mt2->DrawLine(50.5 + adjHalfBin, ymin_Yields, 50.5 + adjHalfBin, ymax_Yields*0.06);
    }
    else if(NSB == 45)
    {
      tl_mt2->DrawLine(14.5 + adjHalfBin, ymin_Yields, 14.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(18.5 + adjHalfBin, ymin_Yields, 18.5 + adjHalfBin, ymax_Yields*0.6);  
      tl_mt2->DrawLine(26.5 + adjHalfBin, ymin_Yields, 26.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(29.5 + adjHalfBin, ymin_Yields, 29.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(34.5 + adjHalfBin, ymin_Yields, 34.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(37.5 + adjHalfBin, ymin_Yields, 37.5 + adjHalfBin, ymax_Yields*0.6);
    } 
    else if(NSB == 37)
    {
      tl_mt2->DrawLine(14.5 + adjHalfBin, ymin_Yields, 14.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(18.5 + adjHalfBin, ymin_Yields, 18.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(23.5 + adjHalfBin, ymin_Yields, 23.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(26.5 + adjHalfBin, ymin_Yields, 26.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(31.5 + adjHalfBin, ymin_Yields, 31.5 + adjHalfBin, ymax_Yields*0.6);
      tl_mt2->DrawLine(34.5 + adjHalfBin, ymin_Yields, 34.5 + adjHalfBin, ymax_Yields*0.6);
    }
  }

  // MT2 labels
  TLatex * ttextmt2 = new TLatex();
  ttextmt2->SetTextFont(42);
  //ttextmt2->SetTextColor(49);
  ttextmt2->SetTextColor(kBlack);
  ttextmt2->SetTextSize(0.040);
  ttextmt2->SetTextAlign(12);
  ttextmt2->SetTextAngle(90);

  if( !drawOnlyLines )
  {
    if(logscale)
    {
      if(NSB == 84)
      {
        ttextmt2->DrawLatex( 3.0, ymax_Yields/100. , "M_{T2} #in [200,300]");
        ttextmt2->DrawLatex( 12.0, ymax_Yields/100. , "M_{T2} #in [400, 550]");
        ttextmt2->DrawLatex( 18.5, ymax_Yields/100. , "M_{T2} #geq 750 GeV");
        ttextmt2->DrawLatex( 39.5, ymax_Yields/70. , "H_{T} #in [300,1000]");
        ttextmt2->DrawLatex( 46.5, ymax_Yields/70. , "H_{T} #geq 1500 GeV");
        ttextmt2->DrawLatex( 76.5, ymax_Yields/200. , "H_{T} #geq 1300 GeV");
        //ttextmt2->DrawLatex( 80.5, ymax_Yields/1500000. , "H_{T}#geq300 GeV");
      }
      else if(NSB == 59)
      {
        ttextmt2->DrawLatex( 2.0, ymax_Yields/10000. , "M_{T2} #in [200,350]");
        ttextmt2->DrawLatex( 6.0, ymax_Yields/10000. , "M_{T2} #in [350,450]");
        ttextmt2->DrawLatex( 10.5, ymax_Yields/10000. , "M_{T2} #geq 450 GeV");
        ttextmt2->DrawLatex( 27.5, ymax_Yields/10000. , "M_{T2} #geq 350 GeV");
      }
      else if(NSB == 37 || NSB == 45)
      {
        ttextmt2->DrawLatex( 2.0, ymax_Yields/2000. , "M_{T2} #in [200,300]");
        ttextmt2->DrawLatex( 6.0, ymax_Yields/2000. , "M_{T2} #in [300,400]");
        ttextmt2->DrawLatex( 9.5, ymax_Yields/2000. , "M_{T2} #geq 400 GeV");
      } 
    }
    else
    {
      if(NSB == 84)
      {
        ttextmt2->DrawLatex( 3.0, ymax_Yields*0.52 , "M_{T2} #in [250,300]");
        ttextmt2->DrawLatex( 8.0, ymax_Yields*0.52 , "M_{T2} #in [300,400]");
        ttextmt2->DrawLatex( 12.5, ymax_Yields*0.52 , "M_{T2} #in [400, 550]");
        ttextmt2->DrawLatex( 16.5, ymax_Yields*0.52 , "M_{T2} #in [550, 800]");
        ttextmt2->DrawLatex( 19.5, ymax_Yields*0.52 , "M_{T2} #geq 800 GeV");
        ttextmt2->DrawLatex( 39.5, ymax_Yields*0.32 , "H_{T} #in [300,1000]");
        ttextmt2->DrawLatex( 46.5, ymax_Yields*0.32 , "H_{T} #geq 1500 GeV");
        ttextmt2->DrawLatex( 76.5, ymax_Yields*0.32 , "H_{T} #geq 1300 GeV");
        ttextmt2->DrawLatex( 80.5, ymax_Yields*0.32 , "H_{T} #geq 300 GeV");
      }
      else if(NSB == 59)
      {
        ttextmt2->DrawLatex( 2.0, deltaY*0.52 + ymin_Yields , "M_{T2} #in [200,350]");
        ttextmt2->DrawLatex( 6.0, deltaY*0.52 + ymin_Yields , "M_{T2} #in [350,450]");
        ttextmt2->DrawLatex( 10.5, deltaY*0.52 + ymin_Yields , "M_{T2} #geq 450 GeV");
        ttextmt2->DrawLatex( 27.5, deltaY*0.52 + ymin_Yields , "M_{T2} #geq 350 GeV");
      }
      else if(NSB == 37 || NSB == 45)
      {
        ttextmt2->DrawLatex( 2.0, deltaY*0.52 + ymin_Yields , "M_{T2} #in [200,300]");
        ttextmt2->DrawLatex( 6.0, deltaY*0.52 + ymin_Yields , "M_{T2} #in [300,400]");
        ttextmt2->DrawLatex( 9.5, deltaY*0.52 + ymin_Yields , "M_{T2} #geq 400 GeV");
      }
    }
  }
}
