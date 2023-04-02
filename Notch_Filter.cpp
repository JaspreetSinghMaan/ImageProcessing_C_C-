void notch_filter( unsigned long ImageLength, unsigned long ImageWidthByte, 
	unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE])
{
		unsigned int i , j ;
		int x,y,u,v;
		double pi,Fr[MAXSIZE][MAXSIZE],Fi[MAXSIZE][MAXSIZE],sumr,sumi;
		int M,N;
		double t1,t2,temp1;
		int choice;
		M=ImageLength;
		N=ImageWidthByte;

		pi=4.0*atan(1.0);

		double fp[MAXSIZE][MAXSIZE] = { 0 },f1[MAXSIZE][MAXSIZE];
		cout<<"Enter 1 for ideal low pass filter and 2 for ideal high pass filter:";
		cin>>choice;
		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
			{
					fp[i][j]=fxy[i][j];
			}

		}
		for(i=0;i<(2*M);i++)
		{
			for(j=0;j<(2*N);j++)
			{
				fp[i][j]=fp[i][j]*pow(-1, (double)(i+j));
			}
		}



		for(u=0;u<(2*M);u++)
		{
		   for(v=0;v<(2*N);v++)
		   {
				sumr=0.0;
				sumi=0.0;
				for(x=0;x<(2*M);x++)
				{
					for(y=0;y<(2*N);y++)
					{
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						
						sumr=sumr+(fp[x][y]*(cos(temp1)));
						sumi=sumi-(fp[x][y]*(sin(temp1)));
						
					}
				}
				Fr[u][v]=sumr;
				Fi[u][v]=sumi;
		         	
		   }
		   cout<<"F"; 
		}
		//applying filter
		int d0 = 3 , n = 4;
		int uk = 42 , vk = 121;
		double dk = 0  , kd = 0 , h = 0 , gr[1000][1000] = {0} , gi[1000][1000] = {0};
		for( u  = 0 ; u < (2*M) ; u++ )
		{
			for( v = 0 ; v < (2*N) ; v++ )
			{
				dk = sqrt((( u - ( M / 2.0 ) - uk ) * ( u - ( M / 2 ) - uk )) + (( v - ( N / 2 ) - vk ) * ( v - ( N / 2 ) - vk )));
				kd = sqrt((( u - ( M / 2.0 ) - uk ) * ( u - ( M / 2 ) - uk )) + (( v - ( N / 2 ) - vk ) * ( v - ( N / 2 ) - vk )));
				h = ( 1 / ( 1 + pow( ( d0 / dk ) , (2*n)))) * ( 1 / ( 1 + pow( ( d0 / kd ) , (2*n))));
				gr[u][v] = h * Fr[u][v];
				gi[u][v] = h * Fi[u][v];
			}
		}
		//inverse filtering
		for(x=0;x<(2*M);x++)
		{
			for(y=0;y<(2*N);y++)
			{
				sumr=0.0;
				sumi=0.0;
				for(u=0;u<(2*M);u++)
				{
					  for(v=0;v<(2*N);v++)
					  {
						t1=(double)(u*x)/(2*M);
						t2=(double)(v*y)/(2*N);
						temp1=(2*pi*(t1+t2));
						sumr=sumr+(gr[u][v]*(cos(temp1))) - (gi[u][v]*(sin(temp1)));
						sumi=sumi+(gr[u][v]*(sin(temp1))) + (gi[u][v]*(cos(temp1)));
					}
				 }
				f1[x][y]= sumr/(4*M*N);
		
				
			}
					cout<<"I";
		}

		
		for(i=0;i<(2*M);i++)
		{
	        for(j=0;j<(2*N);j++)
			{
	             f1[i][j]=f1[i][j]*pow(-1,(double)(i+j));
			}
		}
	/*	int count1=0;
		int count2=0;
	*/
		for(i=0;i<M;i++)
		{
	          for(j=0;j<N;j++)
			  {
	               //if(i<M && j<N)
				   {
						fxyout[i][j]=f1[i][j];
						/*if(fxyout[i][j]>255)
							fxyout[i][j] = 255;
						else if (fxyout[i][j]<0)
							fxyout[i][j] = 0;*/
				   }
			  }

		}
}
