void power_spect(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
 {
	//Fourier transform
	double temp , min,max , angle , t1 , t2 , temp1 , phie[1000][1000] = {0};
	unsigned int i , j;
	int u,v,x,y,M=ImageLength,N=ImageWidthByte;	double pi=4.0*atan(1.0);
	pi = pi * 2;
	int MN = ImageLength*ImageWidthByte , flag = 1 ;
	double fr[1000][1000],fi[1000][1000],Fr[1000][1000],Fi[1000][1000],sumr,sumi , res , result[1000][1000];
	cout<<"Enter 1 for power spectrum 2 for phas angle:";
	cin>>flag;
	cout<<"in loop";
	//Forward FT
	for(u=0;u<ImageLength;u++)
	{
		for(v=0;v<ImageWidthByte;v++)
		{
			sumr = 0.0;
			sumi = 0.0;
			for(x=0;x<ImageLength;x++)
			{
				for(y=0;y<ImageWidthByte;y++)
				{
					sumr = sumr+(fxy[x][y] * cos(pi*((double)(u*x)/M+(double)(v*y)/N)));
					sumi = sumi-(fxy[x][y] * sin(pi*((double)(u*x)/M+(double)(v*y)/N)));
				}
			}
			Fr[u][v] = sumr/(double)(MN);
			Fi[u][v] = sumi/(double)(MN);
		}
		cout<<"F";
	}
	switch( flag )
	{
	case 1:
		for(u=0;u<ImageLength;u++)
		{
			for(v=0;v<ImageWidthByte;v++)
			{

				 res = ( Fr[u][v] * Fr[u][v] )  + ( Fi[u][v] * Fi[u][v] );
				 result[u][v] = sqrt( res );
			}
		}
		min = 255;
		max = 0;
		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{
				temp =	(log(double(1+result[i][j])));
				if(temp<min)
					min = temp;
				if(temp>max)
					max = temp;
			}
		}
		printf("min and max values:%f\t%f",min, max);
		getch();
		for(i=0; i<ImageLength; i++)
		{
			for(j=0; j<ImageWidthByte; j++)
			{
				temp = (log(double(1+result[i][j])));
				fxyout[i][j] =  (unsigned char)0+((double)(255-0)/(double)(max-min))*(double)(temp-min);
			}
		}
	break;
	case 2:
		for(u=0;u<ImageLength;u++)
		{
			for(v=0;v<ImageWidthByte;v++)
			{
			    phie[u][v]=atan(Fi[u][v]/Fr[u][v]);
				if(phie[u][v]<0.0)
					phie[u][v]=phie[u][v]+(2*pi);
					
			}
		}

		double s1,s2,sout1,sout2;
		s1=255;
		s2=0;
		sout1=0;
		sout2=255;
		for(x=0;x<M;x++)
		{
			for(y=0;y<N;y++)
			{	

			  if(s1>phie[x][y])
				  s1=phie[x][y];
			  if(s2<phie[x][y])
				  s2=phie[x][y];
			}
		
		}
		//	cout<<"\n s1="<<s1<<"  s2= "<<s2<<endl;
		for(x=0;x<M;x++)
		{	
			for(y=0;y<N;y++)
			{
				fxyout[x][y]=(unsigned char)(sout1+((sout2-sout1)*(phie[x][y]-s1))/(s2-s1));
				cout<<endl<<(int)fxyout[x][y]<<endl;
			}
		
		}
	break;
	default:
		cout<<"Wrong input.";
	}
}