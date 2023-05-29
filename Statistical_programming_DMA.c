/*Statistical programming

1.Measure of Central tendency- Mean, Mode, Median
2.Mean deviation
3.Standard deviation
4.Correlation coefficient

*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int sortdata(float *a, int n)
{
	int i,j;
	for(i=0;i<n-1;i++)
	{
		int min=i;
		for(j=i+1;j<n;j++)
		{
			if(a[j]<a[min])
			{
				min=j;
			}
		}
		if(min!=i)
		{
			int temp;
			temp=a[i];
			a[i]=a[min];
			a[min]=temp;
		}
	}
}
float mean(float *Data,int size)
{
	int i;
	float mean,sum=0;
	for(i=0;i<size;i++)
	{
		sum+=Data[i];
	}
	return sum/size;
}
float meanwithfreq(float *Data,int *freq,int size)
{
	int i;
	float df_sum=0,freq_sum=0;
	for(i=0;i<size;i++)
	{
		df_sum+=Data[i]*freq[i];
		freq_sum+=freq[i];
	}
	return df_sum/freq_sum;
	
}
float median(float *Data,int size)
{
	float median;	
	if(size%2==0)
	{
		median=(Data[(size/2)-1]+Data[(size/2)])/2;
	}
	else
	{
		median=Data[size/2];
	}
	return median;
}
float medianwithfreq(float *Data,int *freq,int size)
{
	int i,flag;
	float median;
	int *cum_freq,num=0,total_freq=0;
	cum_freq=(int*)calloc(size,sizeof(int));
	for(i=0;i<size;i++)
	{
		total_freq+=freq[i];
		num+=freq[i];
		cum_freq[i]=num;
	}
	printf("Total Frequency is:%d\n",total_freq);
	printf("Cumulative frequency is:\n");
	for(i=0;i<size;i++)
	{
		
	    printf("%d ",cum_freq[i]);
	}
	float halffreq=total_freq/2;
	if((total_freq/2)%2!=0)
	{
		for(i=0;i<size;i++)
		{
			if(cum_freq[i]<halffreq)
			{
				continue;
			}
			else
			{
				median=Data[i];
				break;
			}
		}
	}
	else
	{
		for(i=0;i<size;i++)
		{
			if(cum_freq[i]<halffreq)
			{
				continue;
			}
			else
			{
				median=(Data[i]+Data[i+1])/2;
			}
		}
	}
	return median;
}
int samedatacount(float *Data,int length)
{
	int i,j;
	for(i=0;i<length;i++)
	{
		for(j=i+1;j<length;j++)
		{
			if(Data[i]!=Data[j])
			{
				return 1;
			}
		}
	}
}
void mode(float *Data, int size)
{
	int i,j,modecount=0,k=0;
	float *modearray;
	modearray=(float*)calloc(10,sizeof(float));
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if(Data[i]==Data[j])
			{
				//mode=Data[i];
				modecount++;
				modearray[k]=Data[i];
				k++;
				break;
			}
		}
	}
	int length=sizeof(modearray)/sizeof(modearray[0]);
	printf("\n\nLength of modal array:%d\n\n",length);
	if(sizeof(modearray)/sizeof(modearray[0])==1)
	printf("Mode is:%f",*modearray);
	else
	{
		printf("Given data has more than one mode.\n");
		if(modecount==2)
		{
			printf("Mode is:");
			for(i=0;i<2;i++)
			{
				printf("%0.2f ",*(modearray+i));
			}
			printf("\nGiven data is bimodal.\n");
		}
		else if(modecount==3)
		{
			printf("Mode is:");
			for(i=0;i<3;i++)
			{
				printf("%0.2f ",*(modearray+i));
			}
			printf("Given data is Trimodal.\n");
		}
		else
		{
			printf("Mode is:");
			for(i=0;i<length;i++)
			{
				printf("%0.2f ",*(modearray+i));
			}
			printf("\nGiven data is multimodal.\n");
		}
	}
}
float meandeviation(float *Data,int *freq,int size)
{
	int i;
	float M=meanwithfreq(Data,freq,size),total_freq=0,total_diff_fi_mean=0;
	printf("\nMean of data is:%0.2f\n",M);
	float *temp;
	temp=(float*)calloc(size,sizeof(float));
	for(i=0;i<size;i++)
	{
		temp[i]=(Data[i]-M);
		if(temp[i]<0)   				
		{
			temp[i]=-1*temp[i];                  //  |Data[i]-M|
		}
	}
	for(i=0;i<size;i++)
	{
		total_freq=total_freq+freq[i];
		total_diff_fi_mean+=temp[i]*freq[i];	
	}
	return total_diff_fi_mean/total_freq;
}
float stddeviation(float *Data,int *freq,int size)
{
	int i;
	float total=0,total_freq=0,M=meanwithfreq(Data,freq,size);
	for(i=0;i<size;i++)
	{
		total_freq=total_freq+freq[i];
		total=total+(Data[i]-M)*(Data[i]-M)*freq[i];
	}
	return sqrt(total/total_freq);
}
float correlationcoeff(float *Data,float *Data1,int size)
{
	int i;
	float *X_i,*Y_i,M1,M2,total_xiyi=0,total_xisquare=0,total_yisquare=0,r;
	M1=mean(Data,size);
	M2=mean(Data1,size);
	X_i=(float*)calloc(size,sizeof(float));
	Y_i=(float*)calloc(size,sizeof(float));
	for(i=0;i<size;i++)
	{
		X_i[i]=Data[i]-M1;                                  //M1-arithematic mean of Data
		Y_i[i]=Data1[i]-M2; 								//M2-arithematic mean of Data1
	}
	for(i=0;i<size;i++)
	{
		total_xisquare+=X_i[i]*X_i[i];
		total_yisquare+=Y_i[i]*Y_i[i];
		total_xiyi+=X_i[i]*Y_i[i];
	}
	printf("xiyi=%f\nxixi=%f\nyiyi=%f\n",total_xiyi,total_xisquare,total_yisquare);
	r=total_xiyi/sqrt(total_xisquare*total_yisquare);
	return r;
	
}
int main()
{
	float *Data;
	int i,j,size;
	printf("How many entries does your data contains ?\n");
	scanf("%d",&size);
	Data=(float*)calloc(size,sizeof(float));
	printf("Enter the data:\n");
	for(i=0;i<size;i++)
	{
		printf("Data[%d]=",i+1);
		scanf("%f",(Data+i));
	}
	printf("Your Entered Data is:\n");
	for(i=0;i<size;i++)
	{
		printf("%0.2f ",*(Data+i));
	}
	printf("\nSize of data is:%d",size);
	int choice;
	
	printf("\nEnter 1 to find mean of data\n");
	printf("Enter 2 to find median of data\n");
	printf("Enter 3 to find mode of data\n");
	printf("Enter 4 to find Mean deviation of data\n");
	printf("Enter 5 to find Standard deviation of data\n");
	printf("Enter 6 to find Correlation Coefficient between two data\n");
	printf("Enter your choice:");
	scanf("%d",&choice);
	
	switch(choice)
	{
		case 1:
			{
				char response;
				printf("Press A to find mean by data values\n");
				printf("Press B to find mean by data values along with frequency\n");
				scanf("%c");
				scanf("%c",&response);
				
				switch(response)
				{
					case 'A': 
					case 'a':
						{
							printf("Mean of the data is:%f",mean(Data,size));
							break;
						}
					case 'B':
					case 'b':
						{
							int *freq;
							freq=(int*)calloc(size,sizeof(int));
							printf("Enter the frequency of corresponding data:\n");
							for(i=0;i<size;i++)
							{
								printf("Freq[%d]=",i+1);
								scanf("%d",(freq+i));
							}
							printf("Mean of the data is:%0.2f",meanwithfreq(Data,freq,size));
							break;
						}
				}
			break;	
			}
		case 2:
			{
				char response;
				printf("Press A to find mean by data values\n");
				printf("Press B to find mean by data values along with frequency\n");
				scanf("%c");
				scanf("%c",&response);
				
				switch(response)
				{
						case 'A': 
						case 'a':
						{
							sortdata(Data,size);
							printf("Median is:%0.2f",median(Data,size));
							break;
						}
						case 'B':
						case 'b':
						{
							int *freq;
							freq=(int*)calloc(size,sizeof(int));
							sortdata(Data,size);
							printf("Enter the frequency of corresponding data after sorting:\n");
							for(i=0;i<size;i++)
							{
								printf("Freq[%d]=",i+1);
								scanf("%d",(freq+i));
							}
							printf("\nMedian of the data is:%0.2f",medianwithfreq(Data,freq,size));
							break;
						}
				}
				break;
			}
		case 3:
			{
				char response;
				printf("Press A to find mode by data values\n");
				printf("Press B to find mode by data values along with frequency\n");
				scanf("%c");
				scanf("%c",&response);
				switch(response)
				{
					case 'A':
					case 'a':
						{
							mode(Data,size);
						}
				}
				break;
			}
		case 4:
			{
				int *freq;
				freq=(int*)calloc(size,sizeof(int));
				printf("Enter the frequency of corresponding data:\n");
				for(i=0;i<size;i++)
				{
					printf("Freq[%d]=",i+1);
					scanf("%d",(freq+i));
				}
				printf("\nMean deviation is:%0.2f",meandeviation(Data,freq,size));
				break;
			}
		case 5:
			{
				int *freq;
				freq=(int*)calloc(size,sizeof(int));
				printf("Enter the frequency of corresponding data:\n");
				for(i=0;i<size;i++)
				{
					printf("Freq[%d]=",i+1);
					scanf("%d",(freq+i));
				}
				printf("\nStandard deviation is:%0.2f",stddeviation(Data,freq,size));
				break;
			}
		case 6:
			{
				printf("Enter next set of data:\n");
				float *Data1;
				Data1=(float*)calloc(size,sizeof(float));
				for(i=0;i<size;i++)
				{
					printf("Data1[%d]=",i+1);
					scanf("%f",(Data1+i));
				}
				float r=correlationcoeff(Data,Data1,size);
				printf("Correlation coefficient is:%0.2f",r);
				if(r==-1)
				printf("Perfect negative correlated\n");
				else if(r==1)
				printf("Perfect positive correlated\n");
				else if(r==0)
				printf("There is no proper correlation\n");
			}
	}
	return 0;
}


