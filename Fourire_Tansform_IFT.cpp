void fourire_tansform(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
 {
	//Fourier transform
	int u,v,x,y,M=ImageLength,N=ImageWidthByte;
	double pi=4.0*atan(1.0);
	pi = 2*pi;
	int MN = ImageLength * ImageWidthByte;
	double fr[1000][1000],fi[1000][1000],Fr[1000][1000],Fi[1000][1000],sumr,sumi;
	cout<<"in loop";
	//Forward FT
	for(u=0;u<M;u++)
	{
		for(v=0;v<N;v++)
		{
			sumr = 0.0;
			sumi = 0.0;
			for(x=0;x<M;x++)
			{
				for(y=0;y<N;y++)
				{
					//sumr = sumr+(fxy[x][y] * cos(2*pi*((double)(u*x)/30+(double)(v*y)/30)));
					//sumi = sumi-(fxy[x][y] * sin(2*pi*((double)(u*x)/30+(double)(v*y)/30)));
					sumr = sumr+(fxy[x][y] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)));
					sumi = sumi-(fxy[x][y] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)));
				}
			}
			Fr[u][v] = sumr/(double)(MN);
			Fi[u][v] = sumi/(double)(MN);
			//fxyout[u][v] = Fr[u][v] + Fi[u][v];
		}
	}
	cout<<"\n done";
	//Inverse FT
	for(x=0;x<M;x++)
	{
		for(y=0;y<N;y++)
		{
			sumr = 0.0;
			sumi = 0.0;
			for(u=0;u<M;u++)
			{
				for(v=0;v<N;v++)
				{
					
					//sumr = sumr + (Fr[u][v] * cos(2*pi*((double)(u*x)/30+(double)(v*y)/30)))-(Fi[u][v] * sin(2*pi*((double)(u*x)/30+(double)(v*y)/30)));
					//sumi = sumi + (Fr[u][v] * sin(2*pi*((double)(u*x)/30+(double)(v*y)/30)))+(Fi[u][v] * cos(2*pi*((double)(u*x)/30+(double)(v*y)/30)));

					sumr = sumr + (Fr[u][v] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)))-(Fi[u][v] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)));
					sumi = sumi + (Fr[u][v] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)))+(Fi[u][v] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)));
				}
			}
			fr[x][y] = sumr;
			fi[x][y] = sumi;
			fxyout[x][y] = fr[x][y];
		}
	}
	cout<<"inverse is done";
}
