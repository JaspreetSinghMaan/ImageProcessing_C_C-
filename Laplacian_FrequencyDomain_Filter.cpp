void laplacian_FDfilter(  unsigned long ImageLength, unsigned long ImageWidthByte, 
				unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )
{
	unsigned int i , j ;
	int x,y,u,v;
	double pi,Fr[1500][1500],Fi[1500][1500],sumr,sumi,NM_fxy[MAXSIZE][MAXSIZE];
	int M,N;
	double t1,t2,temp1 , del_max = 0 ;
	int choice , min = 255 , max = 0 ;
	double temp_fxy[MAXSIZE][MAXSIZE] ;
	M=ImageLength;
	N=ImageWidthByte;

	pi=4.0*atan(1.0);

	double fp[1500][1500] = {0.0},f1[1500][1500];

	// To find the maximum and minimum value in the image
	for( i = 0 ; i < M ; i++ )
	{
		for( j = 0 ; j < N ; j++ )
		{
			//temp_fxy[i][j] = fxy[i][j]; 
			if( min > fxy[i][j] )
				min = fxy[i][j];
			if( max < fxy[i][j] )
				max = fxy[i][j];
		}
	}
	cout<<"Values of Min and Max:"<<min<<"\t"<<max;
	getch();
	//To normalize the values in range from 0 to 1
	for( i = 0 ; i < M ; i++ )
	{
		for( j = 0 ; j < N ; j++ )
		{
			temp_fxy[i][j]=(0 + ((double)(1.0)/(max - min)) * (fxy[i][j] - min));
			//cout<<temp_fxy[i][j]<<"\t";
		}
	}
		
		//Extend the image
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
				fp[i][j]=temp_fxy[i][j];
		}
	
	}
	
	//shift origin to the center
	for(i=0;i<(2*M);i++)
	{
		for(j=0;j<(2*N);j++)
		{
			fp[i][j]=fp[i][j]*pow(-1, (double)(i+j));
		}
	}
	
	
	//forward fourier transformation
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
	// applying filter
	double d , f;
	double gr[1500][1500],gi[1500][1500];
	//d0 = (d0 * d0) * 2;
	for(x=0;x<(2*M);x++)
	{
		for(y=0;y<(2*N);y++)
		{
			d = ((double)(x-M)*(x-M)+(y-N)*(y-N));
	
			f = -4 * ( PI * PI ) * d ; 
	
			gr[x][y] = f*Fr[x][y];
			gi[x][y] = f*Fi[x][y];
		}
	}
	//double max = 0.0;
	//inverse of an image
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
			f1[x][y] = sumr/(4*M*N);
			}
				cout<<"I";
	}
			
	/*	int count1=0;
		int count2=0;
	*/
	for(i=0;i<(2*M);i++)
	{
	       for(j=0;j<(2*N);j++)
		{
	            f1[i][j] = f1[i][j]*pow(-1,(double)(i+j));
		}
	}
	
	//dividing delfxy by its maximum
	
	for(i=0;i<M;i++)
	{
	    for(j=0;j<N;j++)
		{
	            if( f1[i][j] > del_max )
				del_max = f1[i][j] ;
		}
	}
	for( i = 0 ; i < M ; i++)
	{
	    for(j=0;j<N;j++)
		{
	            f1[i][j] = f1[i][j] / del_max;
		}
	}
	double min1 = 255 , max1 = 0;
	for(i=0;i<M;i++)
	{
	      for(j=0;j<N;j++)
		  {
				temp_fxy[i][j] = temp_fxy[i][j] - f1[i][j] ;
				if( temp_fxy[i][j] > max1 )
					max1 = temp_fxy[i][j];
				else if( temp_fxy[i][j] < min1 )
					min1 = temp_fxy[i][j];
		  }
	}
	for( i = 0 ; i < M ; i++ )
	{
		for ( j = 0 ; j < N ; j++ )
		{
			fxyout[i][j] =  ((double)(255-0)/(double)(max1-min1))*(double)(temp_fxy[i][j]-min1);
		}
	}
}
