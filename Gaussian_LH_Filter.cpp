void gaussian_LHfilter(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				   unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
		unsigned int i , j ;
		int x,y,u,v;
		double pi,Fr[1500][1500],Fi[1500][1500],sumr,sumi;
		int M,N;
		double t1,t2,temp1;
		int choice;
		M=ImageLength;
		N=ImageWidthByte;

		pi=4.0*atan(1.0);

		double fp[1500][1500] = {0.0},f1[1500][1500];
		cout<<"Enter 1 for gaussian low pass filter and 2 for gaussian high pass filter:";
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

		double d,d0=5;
		double gr[1500][1500],gi[1500][1500];
		//int  n = 2 ;
		double f ;
		d0 = (d0 * d0) * 2;
		switch( choice )
		{
		case 1:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=(double)((x-M)*(x-M)+(y-N)*(y-N));

					f = exp( -(( d ) / d0) ) ; 
					//cout<<f;
					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		case 2:
			for(x=0;x<(2*M);x++)
			{
				for(y=0;y<(2*N);y++)
				{
					d=sqrt((double)((x-M)*(x-M)+(y-N)*(y-N)));
					f = 1 - exp( -( d ) / d0 ) ;

					gr[x][y]=f*Fr[x][y];
					gi[x][y]=f*Fi[x][y];
				}
			}
		break;
		default:
			cout<<"Wrong choice.";
		}
		//getch();
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
				   
						fxyout[i][j]=f1[i][j];
			  }
		}
}
