// By Marco Carmignotto (07/12/2014)
//
// To convert run number 1000:
// root -l "HEX2root(1000)"

int HEX2root(Int_t filenum) {
	
	TString filename = Form("%d.txt",filenum);
	ifstream in;
//	in.open(file.Data());
	in.open(filename.Data());
	if(in.fail()) {
		cout << "Error opening file: " << filename << endl;
		return 1;
	}

	// output
	Int_t nchan = 12;
	TFile *f = new TFile(Form("%d.root",filenum),"RECREATE");
	TTree *tr = new TTree("T","From file " + filename);
	Int_t *ch = new Int_t[nchan];
	for(Int_t i=0; i<nchan; i++) tr->Branch(Form("ch%d",i),&ch[i],Form("ch%d/I",i),512000);

	char line[200];
	stringstream ss;
	Int_t i;
	cout << "Reading data from: " << filename << endl;
	Int_t tmp;
	Long64_t ndata = 0;
	Long64_t nbad = 0;
	while(1) {
		in.getline(line,200);
		if(in.eof() || in.fail()) break;
		ss << line;
		for(i=0;i<3;i++) ss.getline(line, 20, ',');
                sscanf(line,"%x",&ch[0]);
		if(ch[0]!=12) {
			nbad++;
			for(i=0;i<nchan;i++) ch[i]=0;
		}
		else {
	                for(i=0;i<nchan;i++) {
                	        ss.getline(line, 20, ',');
        	                sscanf(line,"%x",&ch[i]);
	                }
		}
		tr->Fill();
		if(ndata>10) {}
		else if(ndata<10) {for(i=0;i<nchan;i++) cout << ch[i] << ","; cout << endl;}
		else cout << "..." << endl << endl;
		ndata++;
	}
	cout << "Read " << ndata << " entries." << endl;
	if(nbad>0) cout << " **** Found " << nbad << " bad lines!" << endl;
	cout << endl << endl;

	tr->Write();
	f->Close();	

	return 0;
}

