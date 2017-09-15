#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct wordandfreq //user defined datatype to store word and frequency of corresponding word
{
	char word[40];
	int frequency;
};
long long word_count(FILE *f) //when sent a file pointer returns number of words in the file by counting ' ' and '\n'
{
	char c;
	int flag=0;
	long long int count=0;
	while((c=fgetc(f))!=EOF)
	{
		flag=1;
		if(c==' '||c=='\n')
		{
			count++;
		}
	}
	if(flag==0)
	{
		return(0);
	}
	else
	{
		return (count+1);
	}
	
}
void return_word(FILE *f,char word[])//when passed a file pointer and an array, updates the array with a word from the file with valid characters.
{
	int i=0;
	char ch;
	while(1)
	{
		ch=fgetc(f);
		if(ch==' '||ch=='\0'||ch==EOF)
		{
			break;
		}
		else if((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z')||ch=='_'||(ch>='0'||ch<='9'))
		{
			if(ch>='A'&&ch<='Z')
			{
				ch=tolower(ch);
			}
			word[i]=ch;
			i++;
		}
		
	}
	word[i]='\0';
}

void get_words(FILE *f,struct wordandfreq struct_array[],long long int wordcount)//when passed a file pointer,array of structures updates
{																				//all the "word" elements in structures with words in the file.
	int i=0;
	while(i<wordcount)
	{
		return_word(f,struct_array[i].word);
		i++;
	}
	
}
void get_frequency(struct wordandfreq struct_array[],long long int wordcount)//when passed array of structures along with its length,updates frequency for each structure
{																			//with respect to the frequency of word, in that particular structure, in the file.
	int i=0,j=0;
	for(i=0;i<wordcount;i++)
	{
		struct_array[i].frequency=1;
		for(j=i+1;j<wordcount;j++)
		{
			if(!(strcmp(struct_array[i].word,struct_array[j].word)))
			{
				struct_array[i].frequency++;
				struct_array[j].word[0]='\0';
			}
		}

	}
}
long long int comparefiles(struct wordandfreq array1[],struct wordandfreq array2[],long long int wordcount1,long long int wordcount2)
{								//when passed two arrays of structures along with their length returns the dot product for common words in both files.
	long long int common=0;
	int i=0,j=0;
	for(i;i<wordcount1;i++)
	{
		for(j=0;j<wordcount2;j++)
					
		{
			if(!(strcmp(array1[i].word,array2[j].word)))
			{
				if (strlen(array1[i].word)>0)
				{
					common+=(array1[i].frequency)*(array2[j].frequency);
				}
			}
			
		}
	}
	return common;
}
double freq_deno(struct wordandfreq array[],long long int wordcount)//returns the euclidian form of vector for caculating cosine function 
{																	//by accepting and array of structures
    double count=0;
	long long int i=0;
	for(i=0;i<wordcount;i++)
	{
		if(strlen(array[i].word)>0)
		{
			count+=((array[i].frequency)*(array[i].frequency));
		}
	}
	return(sqrt(count));

}

double bagofwords(char file1[], char file2[])
{
	FILE *fp1,*fp2,*f;
	long long int wordcount1,wordcount2,common;
	struct wordandfreq *wordarray1,*wordarray2;
	double match_percent,freq1,freq2;
	fp1=fopen(file1,"r");
	fp2=fopen(file2,"r");
	f=fopen("logfile.txt","a");
	wordcount1=word_count(fp1);
	wordcount2=word_count(fp2);
	if(wordcount1==0 || wordcount2==0)//to handle empty files or files containing only special characters
		{
			return(101);
		}
	else
		{
			wordarray1 = malloc(sizeof(struct wordandfreq)*wordcount1);
			wordarray2 = malloc(sizeof(struct wordandfreq)*wordcount2);
			fseek(fp1,0,SEEK_SET);
			fseek(fp2,0,SEEK_SET);
			get_words(fp1,wordarray1,wordcount1);
			get_words(fp2,wordarray2,wordcount2);
			get_frequency(wordarray1,wordcount1);
			get_frequency(wordarray2,wordcount2);
			common=comparefiles(wordarray1,wordarray2,wordcount1,wordcount2);
			freq1=freq_deno(wordarray1,wordcount1);
			freq2=freq_deno(wordarray2,wordcount2);
			match_percent=((double)common)/(freq1*freq2);
			return(match_percent*100);
			
		}
	
	
}
