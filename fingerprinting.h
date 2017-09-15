#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
struct words //user defined datatype to store a word
{
	char word[40];
};
struct hashing // user defined datatype to store hash as well as mod value
{
	char hash[6];
	long hashvalue;
	long modvalue;
};
long long word_count_fp(FILE *f) //when sent a file pointer returns number of words in the file by counting ' ' and '\n'
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

void remove_stopwords(char word[])//accepts a word and checks if the word is a part of stop words and makes it null if it is.
{
	FILE* f;
	char stopword[50];
	f=fopen("stop_words.txt","r");
	fseek(f,0,SEEK_SET);
	for(int i=0;i<319;i++)
	{
		fscanf(f,"%s",stopword);
		if(!(strcmp(stopword,word)))
		{
			word[0]='\0';
			break;
		}
	}

}

void return_word_fp(FILE *f,char word[])//when passed a file pointer and an array, updates the array with a word from the file with valid characters.
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
	remove_stopwords(word);

}

void get_words_fp(FILE *f,struct words struct_array[],long long int wordcount)//when passed a file pointer,array of structures updates
{																				//all the "word" elements in structures with words in the file.
	int i=0;
	while(i<wordcount)
	{
		return_word_fp(f,struct_array[i].word);
		i++;
	}
	
}
long long get_string_len(struct words array[],long long int wordcount) //when passed an array of type words structure, returns the collective length of all the words in it
{
	int i=0;
	long long int count=0;
	for (i;i<wordcount;i++)
	{
		count+=strlen(array[i].word);
	}
	return(count+1);
}

void get_wholestring(struct words array[],long long int wordcount,char s[]) //when passed an array of structure words, returns a common string with all the words
{
	int i=0,k=0;
	for(i;i<wordcount;i++)
	{
		for (int j = 0; array[i].word[j]!='\0'; j++)
		{
			s[k]=array[i].word[j];
			k++;
		}
	}
	s[k]='\0';
}

int isprime(long long i) //recieves a number and returns if the number is prime or not
{
	int j=0,flag=0;
	for(j=2;j<sqrt(i);j++)
	{
		if(i%j==0)
		{
			return 0;
		}
	}
	return 1;
}
long long genprime(long long i)// recieves a number and returns next immediate prime number
{
	while(1)
	{
		if(isprime(i))
		{
			return i;
		}
		else
		{
			i++;
		}
	}
}

void generate_hashvalues(struct hashing list[],char string[],long long int prime)// accepts a array od structure hashing, string of all the words in a file
{																		//and a prime number and generates hashes with corresponding mod values for them. 
	long long int len=strlen(string);
	long long int i=0;
	long long int j=0;
	long long int k=0;

	for(i;i<len-4;i++)
	{
		list[i].hashvalue=0;
		k=i;
		for(j=0;j<5;j++)
		{
			list[i].hash[j]=string[k];
			k++;
			list[i].hashvalue+=(((int)string[k])*pow(5,j));
		}
		list[i].hash[j]='\0';
		list[i].modvalue=(list[i].hashvalue)%prime;
	}
}

double comparefiles_fp(struct hashing list1[], struct hashing list2[],long long int l1, long long int l2)//when passed arrays of structure hashing returns percent match
{
	long long i=0,j=0;
	double count=0;
	for (i=0;i<l1;i++)
	{
		for(j=0;j<l2;j++)
		{
			if(list1[i].modvalue==list2[j].modvalue)
			{
				if(list2[j].modvalue!=0)
				{
					count+=2;
					list2[j].modvalue=0;
					list1[i].modvalue=0;
				}
				
			}
		}
	}
	return (count/(double)(l1+l2-2));
}

double fingerprinting(char file1[], char file2[])
{
	FILE *fp1,*fp2;
	FILE *f;
	f=fopen("logfile.txt","a");
	long long int wordcount1,wordcount2,stringlen1,stringlen2,prime;
	struct words *wordarray1,*wordarray2;
	struct hashing *hashes1, *hashes2;
	double match_percent;
	char *string1,*string2;
	fp1=fopen(file1,"r");
	fp2=fopen(file2,"r");
	wordcount1=word_count_fp(fp1);
	wordcount2=word_count_fp(fp2);
	if(wordcount1==0 || wordcount2==0)//to handle empty files or files containing only special characters
		{
			return(101);
		}
	else
		{
			wordarray1 = malloc(sizeof(struct words)*wordcount1);
			wordarray2 = malloc(sizeof(struct words)*wordcount2);
			fseek(fp1,0,SEEK_SET);
			fseek(fp2,0,SEEK_SET);
			get_words_fp(fp1,wordarray1,wordcount1);
			get_words_fp(fp2,wordarray2,wordcount2);
			stringlen1= get_string_len(wordarray1,wordcount1);
			stringlen2= get_string_len(wordarray2,wordcount2);
			if(stringlen1<5 || stringlen2<5)//to handle files having less than 5 valid characters
			{
				return(102);
			}
			else
			{
			string1=malloc(sizeof(char)*stringlen1);
			string2=malloc(sizeof(char)*stringlen2);
			get_wholestring(wordarray1,wordcount1,string1);
			get_wholestring(wordarray2,wordcount2,string2);
			hashes1=malloc(sizeof(struct hashing)*(stringlen1-4));
			hashes2=malloc(sizeof(struct hashing)*(stringlen2-4));
			prime=genprime((stringlen1>stringlen2?stringlen1:stringlen2)*100);
			generate_hashvalues(hashes1,string1,prime);
			generate_hashvalues(hashes2,string2,prime);
			match_percent=comparefiles_fp(hashes1,hashes2,(stringlen1-4),(stringlen2-4));
			return(match_percent*100);
			}
		}
			
	}
