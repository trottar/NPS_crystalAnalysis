int plotLY() {

	TString filename1 = "Accum_LY";
	TString filename2 = "StandDev_LY";
	
	TString foutname = "BTCP 3 LT";
	TString leg1 = "BTCP ### - LT - Not Annealed (12/17/2015)";
	

	TTree *tr1 = new TTree("tr1","tr1");
	Int_t ndata1 = tr1->ReadFile(filename1,"w:t");
	TTree *tr2 = new TTree("tr2","tr2");
	Int_t nerror = tr2->ReadFile(filename2,"w:t");
	

	tr1->Draw("w:t","","goff");
	Double_t *w1 = tr1->GetV1();
	Double_t *t1 = tr1->GetV2();
	
	tr2->Draw("w:t","","goff");
	Double_t *w2 = tr2->GetV1();
	Double_t *ey = tr2->GetV2();

	// Plot 1 graph
	TCanvas *c0 = new TCanvas("c0","c0",970,600);
	c0->SetTicks(1,1);
	TGraphErrors *gr0a = new TGraphErrors(ndata1,w1,t1,0,ey);
	gr0a->SetMarkerStyle(20);
	gr0a->SetMarkerColor(2);
	gr0a->GetYaxis()->SetRangeUser(0,30);
	gr0a->GetXaxis()->SetRangeUser(0,45);;
	gr0a->SetTitle(";Crystal ID;Light Yield");
	gr0a->Draw("ap");
	/*TLegend *l0 = new TLegend(0.5,0.15,0.88,0.3);*/
	l0->AddEntry(gr0a,leg1,"l");
	l0->Draw();
	c0->Print(foutname+".png");
	return 0;
}

