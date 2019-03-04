int plotAbsorp() {

	TString filename1 = "J02_Absorp";
	TString filename2 = "J11_Absorp";
	TString filename3 = "J15_Absorp";
	TString filename4 = "J17_Absorp";
	TString filename5 = "J32_Absorp";
	TString filename6 = "J36_Absorp";
	TString filename7 = "J38_Absorp";
	TString filename8 = "J40_Absorp";
	TString filename9 = "J44_Absorp";
	TString filename10 = "J45_Absorp";


	TString foutname = "Crystal ID";
	TString leg1 = "J02";
	TString leg2 = "J11";
	TString leg3 = "J15";
	TString leg4 = "J17";
	TString leg5 = "J32";
	TString leg6 = "J36";
	TString leg7 = "J38";
	TString leg8 = "J40";
	TString leg9 = "J44";
	TString leg10 = "J45";

	

	TTree *tr1 = new TTree("tr1","tr1");
	Int_t ndata1 = tr1->ReadFile(filename1,"w:t");
	TTree *tr2 = new TTree("tr2","tr2");
	Int_t ndata2 = tr2->ReadFile(filename2,"w:t");
	TTree *tr3 = new TTree("tr3","tr3");
	Int_t ndata3 = tr3->ReadFile(filename3,"w:t");
	TTree *tr4 = new TTree("tr4","tr4");
	Int_t ndata4 = tr4->ReadFile(filename4,"w:t");
	TTree *tr5 = new TTree("tr5","tr5");
	Int_t ndata5 = tr5->ReadFile(filename5,"w:t");
	TTree *tr6 = new TTree("tr6","tr6");
	Int_t ndata6 = tr6->ReadFile(filename6,"w:t");
	TTree *tr7 = new TTree("tr7","tr7");
	Int_t ndata7 = tr7->ReadFile(filename7,"w:t");
	TTree *tr8 = new TTree("tr8","tr8");
	Int_t ndata8 = tr8->ReadFile(filename8,"w:t");
	TTree *tr9 = new TTree("tr9","tr9");
	Int_t ndata9 = tr9->ReadFile(filename9,"w:t");
	TTree *tr10 = new TTree("tr10","tr10");
	Int_t ndata10 = tr10->ReadFile(filename10,"w:t");



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
	tr5->Draw("w:t","","goff");
	Double_t *w5 = tr5->GetV1();
	Double_t *t5 = tr5->GetV2();
	tr6->Draw("w:t","","goff");
	Double_t *w6 = tr6->GetV1();
	Double_t *t6 = tr6->GetV2();
	tr7->Draw("w:t","","goff");
	Double_t *w7 = tr7->GetV1();
	Double_t *t7 = tr7->GetV2();
	tr8->Draw("w:t","","goff");
	Double_t *w8 = tr8->GetV1();
	Double_t *t8 = tr8->GetV2();
	tr9->Draw("w:t","","goff");
	Double_t *w9 = tr9->GetV1();
	Double_t *t9 = tr9->GetV2();
	tr10->Draw("w:t","","goff");
	Double_t *w10 = tr10->GetV1();
	Double_t *t10 = tr10->GetV2();



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
	TGraph *gr01 = new TGraph(ndata1,w1,t1);
	gr01->SetLineColor(2);
	gr01->SetLineWidth(2);
	gr01->GetYaxis()->SetRangeUser(0,2);
	gr01->GetXaxis()->SetRangeUser(350,800);;
	gr01->SetTitle(";Wavelength (nm);Absorption Coefficient, dk (cm^-1)");
	gr01->Draw("al");
	TGraph *gr02 = new TGraph(ndata2,w2,t2);
	gr02->SetLineColor(3);
	gr02->SetLineWidth(2);
	gr02->Draw("lsame");
	TGraph *gr03 = new TGraph(ndata3,w3,t3);
	gr03->SetLineColor(4);
	gr03->SetLineWidth(2);
	gr03->Draw("lsame");
	TGraph *gr04 = new TGraph(ndata4,w4,t4);
	gr04->SetLineColor(5);
	gr04->SetLineWidth(2);
	gr04->Draw("lsame");
	TGraph *gr05 = new TGraph(ndata5,w5,t5);
	gr05->SetLineColor(6);
	gr05->SetLineWidth(2);
	gr05->Draw("lsame");
	TGraph *gr06 = new TGraph(ndata6,w6,t6);
	gr06->SetLineColor(7);
	gr06->SetLineWidth(2);
	gr06->Draw("lsame");
	TGraph *gr07 = new TGraph(ndata7,w7,t7);
	gr07->SetLineColor(8);
	gr07->SetLineWidth(2);
	gr07->Draw("lsame");
	TGraph *gr08 = new TGraph(ndata8,w8,t8);
	gr08->SetLineColor(9);
	gr08->SetLineWidth(2);
	gr08->Draw("lsame");
	TGraph *gr09 = new TGraph(ndata9,w9,t9);
	gr09->SetLineColor(14);
	gr09->SetLineWidth(2);
	gr09->Draw("lsame");
	TGraph *gr010 = new TGraph(ndata10,w10,t10);
	gr010->SetLineColor(11);
	gr010->SetLineWidth(2);
	gr010->Draw("lsame");


	l0 = new TLegend(.5,0.7,.2,0.85);
	l0->AddEntry(gr01,leg1,"l");
	l0->AddEntry(gr02,leg2,"l");
	l0->AddEntry(gr03,leg3,"l");
	l0->AddEntry(gr04,leg4,"l");
	l0->AddEntry(gr05,leg5,"l");
	l0->AddEntry(gr06,leg6,"l");
	l0->AddEntry(gr07,leg7,"l");
	l0->AddEntry(gr08,leg8,"l");
	l0->AddEntry(gr09,leg9,"l");
	l0->AddEntry(gr010,leg10,"l");
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

