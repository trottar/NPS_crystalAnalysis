int LYscan_simpleSICCAnofit() {

	// SICCA J21
	Int_t run = 3473;
	Double_t crystalSize = 20; // cm - just for x-scale (was 20 cm)
	Int_t startPos = 1; // (0 is the first point), (1 is the second, so ignore first point)
	Double_t timeRun = 440.0; //min
	Double_t timeStep = 20.0; //min
	
	// Other information
	TString dirname = "~/ResearchNP/";
	TString dirout = "../LY_plots/";
	Double_t step = 1; //cm
	Int_t ADCchannel = 1;
	Double_t sepRange[] = {50,110};//70,100

	// One gain - all together
	TCanvas *c00 = new TCanvas("c00","c00",970,600);
	c00->SetTicks(1,1);
	gPad->SetLogy();
	TH1F *hh0 = new TH1F("hh0",Form("%d;ADC channel;counts",run),1201,0,1200);
	TChain *T0 = new TChain("T");
	T0->Add(dirname+Form("/%d.root",run));
	T0->Draw(Form("ch%d>>hh0",ADCchannel));
	TF1 *sig00 = new TF1("sig00","gaus",160,700);//170,800
	TF1 *sep00 = new TF1("sep00","gaus",sepRange[0],sepRange[1]);
	TF1 *ped00 = new TF1("ped00","gaus",25,35);//25,35
	sig00->SetLineColor(2);
	sep00->SetLineColor(3);
	ped00->SetLineColor(4);
	hh0->Fit("sig00","RM+");
	hh0->Fit("sep00","RM+");
	hh0->Fit("ped00","RM+");
	Double_t SEP00 = sep00->GetParameter(1);
	Double_t sSEP00 = sep00->GetParError(1);
	Double_t PED00 = ped00->GetParameter(1);
	Double_t sPED00 = ped00->GetParError(1);
	c00->Print(dirout+Form("/%d_c00.png",run));

	// Number of points
	Int_t nruns = (int)(timeRun/timeStep);
	Double_t rate = T0->GetEntries()/timeRun;
	nruns -= startPos;

	TCanvas *c0 = new TCanvas("c0","c0",1600,1200);
	Int_t nx = (int)(sqrt(nruns));
	Int_t ny;
	if(nruns%nx==0) ny = nruns/nx;
	else ny = 1+nruns/nx;
	c0->Divide(nx,ny);
	TH1F **h = new TH1F*[nruns];
	TF1 **sig   = new TF1*[nruns];
	TF1 **sep  = new TF1*[nruns];
	TF1 **ped  = new TF1*[nruns];
	Double_t *peak   = new Double_t[nruns];
	Double_t *speak  = new Double_t[nruns];
	Double_t *PED    = new Double_t[nruns];
	Double_t *sPED   = new Double_t[nruns];
	Double_t *SEP    = new Double_t[nruns];
	Double_t *sSEP   = new Double_t[nruns];
	Double_t *pos    = new Double_t[nruns];
	Double_t *LY    = new Double_t[nruns];
	Double_t *sLY    = new Double_t[nruns];
	Int_t *nevts    = new Int_t[nruns];
	Int_t i=0;
	for(i=0; i<nruns; i++) {
		c0->cd(i+1);
		gPad->SetLogy();
		h[i] = new TH1F(Form("h%d",i),Form("pos %d;ADC channel;counts",i+startPos),1201,0,1200);
		h[i]->SetLineWidth(2);
		T0->Draw(Form("ch%d>>h%d",ADCchannel,i),Form("Entry$>=%d && Entry$<%d",(int)((i+startPos)*(rate*timeStep)),(int)((i+startPos+1)*(rate*timeStep))));
		sig[i] = new TF1(Form("sig%d",i),"gaus",160,700);//170,1000
		sep[i] = new TF1(Form("sep%d",i),"gaus",sepRange[0],sepRange[1]);
		ped[i] = new TF1(Form("ped%d",i),"gaus",25,35);//25,35
		sig[i]->SetLineColor(2);
		sep[i]->SetLineColor(3);
		ped[i]->SetLineColor(4);
		h[i]->Fit(Form("sig%d",i),"RM+");
		h[i]->Fit(Form("sep%d",i),"RM+");
		h[i]->Fit(Form("ped%d",i),"RM+");
		pos[i] = startPos+i*step;
		peak[i]  = sig[i]->GetParameter(1);
		speak[i] = sig[i]->GetParError(1);
		PED[i] = ped[i]->GetParameter(1);
		sPED[i] = (Double_t)ped[i]->GetParError(1);
		SEP[i] = sep[i]->GetParameter(1);
		sSEP[i] = sep[i]->GetParError(1);
		LY[i] = (peak[i]-PED[i])/(SEP00-PED00)/0.511;
		sLY[i] = LY[i]*sqrt(pow(speak[i]/(peak[i]-PED[i]),2)+pow(sSEP[i]/(SEP[i]-PED[i]),2)+pow(sPED[i]*(SEP[i]-peak[i])/((peak[i]-PED[i])*(SEP[i]-PED[i])),2));
		//sLY[i] = 0.5;
	}
	c0->Print(dirname+Form("/%d_c0.png",run));

	TCanvas *c1 = new TCanvas("c1","c1",970,600);
	c1->SetTicks(1,1);
	TGraphErrors *gr1 = new TGraphErrors(nruns,pos,LY,0,sLY);//////////////////////////////////////////////////
	gr1->SetMarkerStyle(20);
	gr1->SetLineWidth(2);
	gr1->SetTitle(Form("%d;Position (cm);LY (pe/MeV)",run));
	gr1->GetXaxis()->SetLimits(-0.5,crystalSize+0.5);
	gr1->GetYaxis()->SetRangeUser(0.0,28.0);
	gr1->Draw("ap");
	c1->Print(dirname+Form("/%d.png",run));
	//fit?
	//TGraph *g = new TGraph((sizeof(x) / sizeof(Double_t)), crystal, LY);
	//TF1 *g = new TF1("g", "pol0", 0, 100);
	//gr1->Fit("g");
	//gr1->Draw("lsame");
	// Printing final results
	cout << endl << endl << "step\tpos\tLY\tsLY\tsep-ped" << endl;
	for(Int_t i=0; i<nruns; i++) cout << i+startPos << "\t" << pos[i] << "\t" << LY[i] << "\t" << sLY[i] << "\t" << SEP00-PED00 << endl;
	cout << endl << endl;
	cout << "Double_t x[] = {";
	for(Int_t i=0; i<nruns-1; i++) cout << pos[i] << ",";
	cout << pos[i] << "};" << endl;
	cout << "Double_t LY[] = {";
	for(Int_t i=0; i<nruns-1; i++) cout << LY[i] << ",";
	cout << LY[i] << "};" << endl;
	cout << "Double_t sLY[] = {";
	for(Int_t i=0; i<nruns-1; i++) cout << sLY[i] << ",";
	cout << sLY[i] << "};" << endl << endl;

	cout << "--> Mean = " << TMath::Mean(nruns,LY,sLY) << " +/- " << sqrt(pow(TMath::RMS(nruns,LY),2.0)+pow(sLY[0],2.0)) << endl;
	
	return 0;
}

