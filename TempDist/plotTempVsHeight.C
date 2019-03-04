int plotTempVsHeight(){

  TString filename1 = "TempProfile_Given";
  //TString filename1 = "TempVsHeight_NI";
  // TString filename2 = "TempVsHeight_1I";
  //TString filename3 = "TempVsHeight_1IFan"; 

  TString foutname = "TempProfile_Shaft";
  // TString foutname = "TempVsHeight";
  //TString leg1 = "No Insulator";
  //TString leg2 = "1 inch Insulator";
  //TString leg3 = "1 inch Insulator with fan";

  TTree *tr1 = new TTree("tr1","tr1");
  Int_t ndata1 = tr1->ReadFile(filename1,"w:t");
  /* TTree *tr2 = new TTree("tr2","tr2");
  Int_t ndata2 = tr2->ReadFile(filename2,"w:t");
  TTree *tr3 = new TTree("tr3","tr3");
  Int_t ndata3 = tr3->ReadFile(filename3,"w:t");//*/

  tr1->Draw("w:t","","goff");
  Double_t *w1 = tr1->GetV1();
  Double_t *t1 = tr1->GetV2();
  /* tr2->Draw("w:t","","goff");
  Double_t *w2 = tr2->GetV1();
  Double_t *t2 = tr2->GetV2();
  tr3->Draw("w:t","","goff");
  Double_t *w3 = tr3->GetV1();
  Double_t *t3 = tr3->GetV2();//*/

  TCanvas *c0 = new TCanvas("c0","c0",970,600);
  c0->SetTicks(1,1);
  TGraph *gr1 = new TGraph(ndata1,w1,t1);
  gr1->SetLineColor(2);
  gr1->SetLineWidth(2);
  gr1->GetXaxis()->SetRangeUser(0,.22);
  gr1->GetYaxis()->SetRangeUser(1300,1600);
  //gr1->GetYaxis()->SetRangeUser(20,225);
  //gr1->GetXaxis()->SetRangeUser(0,6);
  //gr1->SetTitle(";Height (in);Temperature (C)");
  gr1->SetTitle(";Height (m);Temperature (C)");
  gr1->Draw("al");
  /* TGraph *gr2 = new TGraph(ndata2,w2,t2);
  gr2->SetLineColor(3);
  gr2->SetLineWidth(2);
  gr2->Draw("lsame");
  TGraph *gr3  = new TGraph(ndata3,w3,t3);
  gr3->SetLineColor(4);
  gr3->SetLineWidth(2);
  gr3->Draw("lsame");
  
  
  lnd = new TLegend(.6,.7,.8,.85);
  lnd->AddEntry(gr1,leg1,"l");
  lnd->AddEntry(gr2,leg2,"l");
  lnd->AddEntry(gr3,leg3,"l");
  lnd->Draw();//*/

  c0->Print(foutname+".png");

  return 0;
}
