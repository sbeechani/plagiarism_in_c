#include "bagofwords.h"
#include "lcs.h"
#include "fingerprinting.h"
#include <dirent.h>
#include <time.h>

int main(int argc, char const *argv[])
{

	DIR *d;
    struct dirent *dir;
    d = opendir(argv[1]);
    // char path[100];
    FILE* f;
    f=fopen("logfile.txt","a");
    time_t t = time(NULL);
    fprintf(f,"\n%s\n",ctime(&t));
    printf("plagiarism test using various algorithms\n");
    fprintf(f,"%s\n","plagiarism test using various algorithms");
    // printf("%s\n",argv[1] );
    // printf("Enter directory: ");
    // gets(path);
    // path=argv[1];
    char files[10][20];
   
    int len;
    int i=0;
    int j=0,k=0;
    double res;
    
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {  
        int length = strlen(dir->d_name);
     	 if (strncmp(dir->d_name + length - 4, ".txt", 4) == 0) 
         { 
            if(strcmp("stop_words.txt",dir->d_name) && strcmp("logfile.txt",dir->d_name))
            {
                strcpy(files[i],dir->d_name);
                i++;
            }     	
        	
         }
     }
      
        
        closedir(d);
    }

    for(int j=0;j<i;j++)
    {
    	for(int k=j+1;k<i;k++)
    	{
            printf("\n-----------------------------------------");
            fprintf(f,"\n%s","-------------------------------------");
    		printf("\nFor files %s, %s",files[j],files[k] );
            fprintf(f,"\n%s %s,%s","For files",files[j],files[k] );
    		printf("\nBag of words: ");
            fprintf(f,"\n%s","Bag of words: ");
    		res=bagofwords(files[j],files[k]);
            if(res==101)
            {
                printf("one or both of the files are empty or contains only special characters");
                fprintf(f,"%s","one or both of the files are empty or contains only special characters");
            }
             else
            {
                printf("%.2lf",res);
                fprintf(f,"%.2lf",res);
            }
    		printf("\nLCS: ");
            fprintf(f,"\n%s","LCS: ");
    		res=lcs(files[j],files[k]);
            if(res==101)
            {
                printf("Something went wrong while opening files");
                fprintf(f,"%s","Something went wrong while opening files");
            }
            else if(res==102)
            {
                printf("one or both the files are empty or contains only special characters");
                fprintf(f,"%s","one or both the files are empty or contains only special characters");
            }
            else
            {
                printf("%.2lf",res);
                fprintf(f,"%.2lf",res);
            }
    		printf("\nFinger printing: ");
            fprintf(f,"\n%s","Finger printing: ");
    		res=fingerprinting(files[j],files[k]);
            if(res==101)
            {
                printf("one or both of the files are empty or contains only special characters");
                fprintf(f,"%s","one or both of the files are empty or contains only special characters");
            }
            else if(res==102)
            {
                printf("One or both the files are too small to create a finger print");
                fprintf(f,"%s","One or both the files are too small to create a finger print");
            }
            else
            {
                printf("%.2lf",res);
                fprintf(f,"%.2lf",res);
            }


    	}
    }
    fclose(f);
	return 0;
}