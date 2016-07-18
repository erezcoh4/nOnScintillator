
TH1F * GetDetectionEfficiency( TTree * , double );
double PMin = 0 , PMax = 550 ;
int Nbins = 50;




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectionEfficiency( int run = 1 ) {
    gStyle->SetOptStat(0000);
    
    
    //....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
    TPlots * plot = new TPlots( Form("/Users/erezcohen/Desktop/Geant4Projects/root_files/nDetEffg4_run%d.root",run) , "Ntuple" );
    TTree * tree = plot->GetTree();
    const int N = 4;
    TH1F * hDetEff[N];
    TString Labels[N];
    int              colors[N] = {31 , 36  , 41 , 46    };
    double   ThrshldEdepMeV[N] = {0. , 5.5 , 7. , 11.   };
    double ThrshldEdepMeVee[N] = {0. , 2.  , 3. , 5.    };
    for (int i = 0 ; i < N ; i++){
        hDetEff[i] = GetDetectionEfficiency( tree , ThrshldEdepMeV[i] );
        Labels[i] = Form("Threshold = %.1f MeV (%.0f MeV_{ee}) ",ThrshldEdepMeV[i]  , ThrshldEdepMeVee[i] );
    }
    plot -> MultipleHistograms( N , (TH1**)hDetEff , Labels  , PMin , PMax , Form("def. eff. for n on 5cm thick scintillator") , "generated neutron momentum [MeV/c]" , "detection efficiency [%]" , colors  );
    
}






//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
TH1F * GetDetectionEfficiency( TTree * Tree , double ThrshldEdepMeV ){
    
    double Momentum;
    Tree -> SetBranchAddress("Momentum_g"           , &Momentum);
    int ParticleReachedDet;
    Tree -> SetBranchAddress("NeutronReachedDet"    , &ParticleReachedDet);
    double EnergyDeposition;
    Tree -> SetBranchAddress("EnergyDeposition"     , &EnergyDeposition);

    TH1F * hMomentum        = new TH1F (Form("hMomentum_%d",(int)ThrshldEdepMeV),"Momentum", Nbins , PMin , PMax);
    TH1F * hDet_Momentum    = new TH1F (Form("hDet_Momentum_%d",(int)ThrshldEdepMeV),"Detected Per Momentum", Nbins , PMin , PMax);
    for (int entry = 0 ; entry < Tree->GetEntries() ; entry++ ){
        Tree -> GetEntry(entry);
        if (ParticleReachedDet){
            hMomentum -> Fill(Momentum);
            if (EnergyDeposition > ThrshldEdepMeV){
                hDet_Momentum -> Fill(Momentum);
            }
        }
    }
    TH1F * hDetEff = new TH1F(Form("hDetEff_%d",(int)ThrshldEdepMeV)," ",Nbins , PMin , PMax);
    for (int bin = 0 ; bin < Nbins ; bin++){
        if (hMomentum -> GetBinContent(bin))
            hDetEff -> SetBinContent( bin , 100.*(double)hDet_Momentum->GetBinContent(bin)/(double)hMomentum->GetBinContent(bin) );
        else
            hDetEff -> SetBinContent( bin , 0 );
    }

    return hDetEff;
}







