int plot3CALTECH() {

	TString filename1 = "J02_Absorp";
	TString filename2 = "J11_Absorp";
	TString filename3 = "J15_Absorp";
	TString filename4 = "J17_Absorp";


	TString foutname = "Absorption Coefficients";
	TString leg1 = "J02";
	TString leg2 = "J11";
	TString leg3 = "J15";
	TString leg4 = "J17";

	

	TTree *tr1 = new TTree("tr1","tr1");
	Int_t ndata1 = tr1->ReadFile(filename1,"w:t");
	TTree *tr2 = new TTree("tr2","tr2");
	Int_t ndata2 = tr2->ReadFile(filename2,"w:t");
	TTree *tr3 = new TTree("tr3","tr3");
	Int_t ndata3 = tr3->ReadFile(filename3,"w:t");
	TTree *tr4 = new TTree("tr4","tr4");
	Int_t ndata4 = tr4->ReadFile(filename4,"w:t");



	tr1->Draw("w:t","","goff");
	Double_t *w1 = tr1->GetV1();
	Double_t *t1 = tr1->GetV2();
	tr2->Draw("w:t","","goff");
	Double_t *w2 = tr2->GetV1();
	Double_t *t2 = tr2->GetV2();
	tr3->Draw("w:t","","goff");
	Double_t *w3 = tr3->GetV1();
	Double_t *t3 = tr3->GetV2();
	tr4->Draw("w:t","","goff");
	Double_t *w4 = tr4->GetV1();
	Double_t *t4 = tr4->GetV2();



/*
	Double_t *diff = new Double_t[ndata1];
	for(Int_t i=0; i<ndata1; i++) {
		// Checking is w1 equals w2
		if(w1[i]!=w2[i]) {
			cout << "ERROR! Wavelength of files are different." << endl;
			return 1;
		}
		// Making difference
		diff[i] = t1[i]-t2[i];
	}
*/

	// Plot both supperposed
	TCanvas *c0 = new TCanvas("c0","c0",970,600);
	c0->SetTicks(1,1);
	TGraph *gr0a = new TGraph(ndata1,w1,t1);
	gr0a->SetLineColor(2);
	gr0a->SetLineWidth(2);
	gr0a->GetYaxis()->SetRangeUser(-1,1);
	gr0a->GetXaxis()->SetRangeUser(350,800);;
	gr0a->SetTitle(";Wavelength (nm);Absorption Coefficient (cm^-1)");
	gr0a->Draw("al");
	TGraph *gr0b = new TGraph(ndata2,w2,t2);
	gr0b->SetLineColor(3);
	gr0b->SetLineWidth(2);
	gr0b->Draw("lsame");
	TGraph *gr0c = new TGraph(ndata3,w3,t3);
	gr0c->SetLineColor(4);
	gr0c->SetLineWidth(2);
	gr0c->Draw("lsame");
	TLegend *l0 = new TLegend(0.5,0.15,0.88,0.5);
	l0->AddEntry(gr0a,leg1,"l");
	l0->AddEntry(gr0b,leg2,"l");
	l0->AddEntry(gr0c,leg3,"l");
	l0->AddEntry(gr0c,leg4,"l");
	l0->Draw();
	c0->Print(foutname+".png");

	// Plot diff
/*
	TCanvas *c1 = new TCanvas("c1","c1",970,600);
	c1->SetTicks(1,1);
	TGraph *gr1 = new TGraph(ndata1,w1,diff);
	gr1->SetLineColor(4);
	gr1->SetLineWidth(2);
	gr1->GetXaxis()->SetRangeUser(200,800);
	gr1->GetYaxis()->SetRangeUser(-10,10);
	gr1->SetTitle(";Wavelength (nm);#Delta_{Transmittance} (%)");
	gr1->Draw("al");
	c1->Print(foutname+"_diff.png");
*/

	return 0;
}

