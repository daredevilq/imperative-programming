void linspace(double v[], double start, double stop, int n) {
		
   
    double r;
	double m;
    m=n-1;
    r=abs(start-stop)/m;
	

    for ( int i = 0; i < n; i++)
    {   
		v[i]=start+r*i;
        
    }  
	
}
