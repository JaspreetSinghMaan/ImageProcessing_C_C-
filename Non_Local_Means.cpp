void Non_local_means( unsigned long ImageLength, unsigned long ImageWidthByte, 
				unsigned char fxyout[MAXSIZE][3*MAXSIZE] , unsigned char fxy[MAXSIZE][3*MAXSIZE] )

{
/*	int temp[5][5] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
		21, 22, 23, 24, 25};
*/	int tempout[5][5], f = 1, t = 2, h = 10;
	printf("\nEnter rsim and ssim:");
	scanf("%d%d",&f,&t);
	copy_to_new( ImageLength, ImageWidth, fxy , 2*f+1 );
	int rmin, rmax, smin, smax, weight;
	double **kernel, d = 0, w, wmax , average , sweight;
	int i, j;
	int **w1, **w2;
	double sum = 0 , value = 0 , **tempw;
	cout<<"\nImageLength:"<<ImageLength;
	cout<<"\nImageWidth:"<<ImageWidth;
	cout<<"\nImageWidthByte:"<<ImageWidthByte;
	getch();
	tempw = (double **)malloc((2*f+1)*sizeof(double *));
	for( i = 0 ; i < 2*f+1 ; i++ )
	{
		*( tempw + i ) = (double *)malloc((2*f+1) * sizeof( double ));
	}
	w1 = (int **)malloc((2*f+1)*sizeof(int *));
	for( i = 0 ; i < 2*f+1 ; i++ )
	{
		*( w1 + i ) = (int *)malloc((2*f+1) * sizeof( int ));
	}
	w2 = (int **)malloc((2*f+1)*sizeof(int *));
	for( i = 0 ; i < 2*f+1 ; i++ )
	{
		*( w2 + i ) = (int *)malloc((2*f+1) * sizeof( int ));
	}
	//ImageLength = ImageWidthByte = ImageWidth = 5;
	kernel = (double **)malloc( (2*f+1)*sizeof( double *));
	for( i = 0; i < 2*f+1 ; i++)
	{
		*( kernel + i ) = (double *) malloc( (2*f+1) * sizeof( double ));
	}

	for( int x = 1 ; x <= f ; x++ )
	{
		value = 1 /((double)( 2*x+1 ) * ( 2*x+1 ));
		for( int i = -x ; i <= x ; i++ )
		{
			for( int j = -x ; j <= x ; j++ )
			{
				kernel[f-i][f-j] = kernel[f-i][f-j] + value;
			}
		}
	}
	for( i = 0 ; i < 2*f+1 ; i++ )
	{
		for( j = 0 ; j < 2*f+1 ; j++ )
		{
			kernel[i][j] /= f;
			sum += kernel[i][j];
		}
	}
//	printf("Kernel matrix:\n");
	for( i = 0 ; i < 2*f+1 ; i++ )
	{
		for( j = 0 ; j < 2*f+1 ; j++ )
		{
			kernel[i][j] /= sum;
			//printf("%f\t",kernel[i][j]);
		}
		//printf("\n");
	}
	//getch();
	int c_h = h;
	for( int z = 135 ; z <= 135 ; z++ )
	{
		h = z*z;
		//cout<<"ImageLength:"<<ImageLength;
		//getch();
		for( int i = 0 ; i < ImageLength ; i++ )
		{
			for( int j = 0 ; j < ImageWidthByte ; j++ )
			{
				int i1 = i + f;
				int j1 = j + f;
				//printf("window 1 around whom weights are calculated:\n");
				for( int x = i1-f ; x <= i1+f ; x++)
				{
					for( int y = j1-f ; y <= j1+f ; y++ )
					{
						w1[x-(i1-f)][y-(j1-f)] = new_image[x][y];
						//printf("%d\t",w1[x-(i1-f)][y-(j1-f)]);
					}
					//printf("\n");
				}
				//getch();
				wmax = 0;
				average = 0;
				sweight = 0;

				rmin = max(i1-t, f);
				rmax = min(i1+t, (ImageLength-1)+f);
				smin = max(j1-t, f);
				smax = min(j1+t, (ImageWidthByte-1)+f);

				for( int r = rmin ; r <= rmax ; r++)
				{
					for( int s = smin ; s <= smax ; s++)
					{
						if( r == i1 && s == j1 )
						{
							continue;
						}
						//printf("window i:\n");
						for( int x = r-f ; x <= r+f ; x++)
						{	
							for( int y = s-f ; y <= s+f ; y++ )
							{
								w2[x-(r-f)][y-(s-f)] = new_image[x][y];
								//printf("%d\t",w2[x-(r-f)][y-(s-f)]);
							}
							//printf("\n");
						}
						d = 0;
						for( int x = 0 ; x < 2*f+1 ; x++ )
						{
							for( int y = 0 ; y < 2*f+1 ; y++ )
							{
								tempw[x][y] = w1[x][y] - w2[x][y];
								tempw[x][y] *= tempw[x][y];
								//tempw[x][y] *= kernel[x][y];
								d += tempw[x][y];
							}
						}
						w = exp( -d/h );

						if( w > wmax )
							wmax = w;
						sweight += w;
						average = average + w * new_image[r][s];
					}
				}

				average = average + wmax * new_image[i1][j1];
				sweight = sweight + wmax;

				if( sweight > 0 )
				{
					fxyout[i][j] = average / sweight;
					//printf("\n%f",(average / sweight));
				}
				else
				{
					fxyout[i][j] = fxy[i][j];
					//printf("\n%f",temp[i][j]);
				}
				//printf("tempout, variable i and j:%d %d %d\n",tempout[i][j],i,j);
			
			}
		}
		double t1, mse , di, psnr;
		t1 = 0.0;
		for( unsigned i = 0 ; i < ImageLength ; i++ )
		{
			for( unsigned j = 0 ; j < ImageWidthByte ; j++ )
			{
				t1 += ( fxy[i][j] - fxyout[i][j] ) * ( fxy[i][j] - fxyout[i][j] );
			}
		}
		mse = t1 / ( ImageLength * ImageWidthByte );
		di = ( 255 * 255 ) / mse;
		psnr = 10*log10(di);
		cout<<"\n\nPSNR is ="<<psnr<<"\t at h*h =" <<h<<"\t with sim windows size ="<<2*f+1<<"\t search window size is="<<2*t+1;
	}
	cout<<"\n"<<"Note the results";
	getch();
}
