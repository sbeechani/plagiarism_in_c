#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
long long int charcount (FILE* f)//when passed a file pointer returns number of valid characters in the file
{
	char c;
	long long int count=0;
	while((c=fgetc(f))!=EOF)
	{
		if(c>='a' && c<='z'|| c>='A' && c<='Z' || c>='0'&& c<='9')
		{
			count++;
		}
	}
	return (count+1); //+1 to include null character
}
void getcharacters (FILE* f,char* chararray)//accepts a file pointer,pointer to a character array and adds all the valid characters into the array from file.
{
	char c;
	long long int i=0;
	while((c=fgetc(f))!=EOF)
	{

		if(c>='a' && c<='z'|| c>='A' && c<='Z' || c>='0'&& c<='9')
		{
			chararray[i]=c;
			i++;
		}
	}
	chararray[i]='\0';//appending null character at the end of character array
}

long long int comparefiles_lcs (char chararray1[],char chararray2[],long long int l1,long long int l2)//accepts character arrays corresponding to two files to be compared and returns the length of largest common string.
{
	long long int i1=0,i2=0,dup_i1,dup_i2;
	long long int max_commonlen=0,commonlen=0;
	while(i1<l1)
	{
		i2=0;
		while(i2<l2)
		{
			if(chararray1[i1]==chararray2[i2])
			{
				dup_i1=i1;
				dup_i2=i2;
				while(chararray1[i1]==chararray2[i2])//to calculate the length of the common string.
				{
					if(i1>=l1 || i2>=l2)
					{
						break;
					}
					commonlen++;
					i1++;
					i2++;									
				}
				if(commonlen>max_commonlen)
				{
					max_commonlen=commonlen;
				}
				commonlen=0;
				i1=dup_i1;
				i2=dup_i2+1;
			}
			else
			{
				i2++;
			}
		}
		i1++;
	}
	return max_commonlen;
}
double lcs(char file1[],char file2[])
{
	FILE *fp1,*fp2,*f;
	long long int LCS,length1,length2,charcount1,charcount2;
	double match_percent;
	fp1=fopen(file1,"r");
	fp2=fopen(file2,"r");
	f=fopen("logfile.txt","a");
	if(fp1==NULL || fp2==NULL)
		{
			return(101);
		}
	else
		{
			char *chararray1,*chararray2;
			charcount1=charcount(fp1);
			charcount2=charcount(fp2);
			chararray1=malloc(sizeof(char)*charcount1);//Dynamically allocating memory to array, which is equal to "number of valid characters" in the file. 
			chararray2=malloc(sizeof(char)*charcount2);
			if (charcount1==1 || charcount2==1)
				{
					return(102);
				}
			else
				{
					fseek(fp1,0,SEEK_SET);
					getcharacters(fp1,chararray1);//all the valid characters gets appended to the character array
					fseek(fp2,0,SEEK_SET);
					getcharacters(fp2,chararray2);
					length1=strlen(chararray1);
					length2=strlen(chararray2);
					LCS=comparefiles_lcs(chararray1,chararray2,charcount1,charcount2);
					// printf("%lli,%lli,%lli\n",LCS,length1,length2);
					match_percent=((double)2*LCS*100/(double)(length1+length2));
					return(match_percent);
					
				}
			
		}

}