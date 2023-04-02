void AdapMedian_filter( unsigned long ImageLength, unsigned long ImageWidthByte, 
				unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
		int i,j,s,t,xps,ypt,min,m,n,a,b,u,v,max,median,smax=7;
	    int M,N;
		M=ImageLength;
		N=ImageWidthByte;
		int arr[50];
		int count=0;
		for(i=0;i<M;i++)
		{
			for(j=0;j<N;j++)
			{	
				m=n=3;
				 count++;
				  //cout<<"outer loop.."<<count<<endl;
                       level_a: a=(m-1)/2;
		                     b=(n-1)/2;
			                 int k=0;
							 //cout<<"In level a"<<endl;
					for(s=-a;s<=a;s++)
					{
						for(t=-b;t<=b;t++)
						{
							xps=i+s;
							if(xps<0)
								xps=0;
							if(xps>=M)
								xps=M-1;
							ypt=j+t;
							if(ypt<0)
								ypt=0;
							if(ypt>=N)
								ypt=N-1;
							arr[k++]=fxy[xps][ypt];
						}
					}
					//cout<<"\n Array sizze : "<<k<<endl;
				
					sort( arr , arr+(m*n) );
					median=arr[(m*n)/2];
					min=arr[0];
					max=arr[((m*n)-1)];
						
			        double a1,a2,b1,b2;
					a1=median-min;
					a2=median-max;

					if(a1>0 && a2<0)
					{
						b1=fxy[i][j]-min;
						b2=fxy[i][j]-max;

						if(b1>0 && b2<0)
							fxyout[i][j]=fxy[i][j];
						else
							fxyout[i][j]=median;
					}
					else
					{
						
						m=m+2;
						n=n+2;
						//cout<<"in size increasing loop.."<<(m*n);
						if(m>smax)
						{
							fxyout[i][j]=median;
							//cout<<"exiting.."<<endl;
						}
						else if(m<=smax)
						{
							goto level_a;
						}
					 
					}
		
			}
		
		}
}
