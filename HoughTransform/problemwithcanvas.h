
void HT() {
	TCanvas* c2 = new TCanvas("c2","c2");
	h->GetXaxis()->SetTitle("#theta");
    h->GetYaxis()->SetTitle("#rho");
	h->Draw("colz");


	TCanvas* c4 = new TCanvas("c4","found lines");
	hPs.Draw("A*");
	for (unsigned int i=0; i<lines.size(); i++){
		//if (i == 0) lines->at(i).Draw();
		//else lines->at(i).Draw("same");
		lines[i].Draw("same");
	}
	c4->Update();
}

int main(int argc, char *argv[]) {

TApplication theApp("App",&argc,argv);
HT();
theApp.Run();
return 0;
}
	
	