// Author: Lalitha Viswanathan
// Affiliation: Tata Consultancy Services 
#include<stdio.h>
#include<iostream.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include "kmp.cpp"
char *DNA_seq,*COMP_seq;int size;
void searchforre_patterns_infnafile(char* restrictionenzymepattern, Text);
int listofpotentialcutsites=0;
FILE* pointertorebasefile;
int fwdb,revb,fwda,reva,cutposn,flag;
char tempstr[100],name[50],pattern[50];
main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("\n enter in format <fna filename> <enzyme to cut with>");
		exit(1);
	}
	// Parse REBase file
	// Search for re enzymes in input fna file using kmp
	system("perl rebase.pl REBASE.txt");	
	printf("\n created file rebaseparsed.txt");
	Text text(argv[1]);
	if(!(pointertorebasefile=fopen("rebaseparsed.txt","r")))
	{
			printf("\nrebaseparsed.txt does not exist\n");
			exit(1);
	}
	while(!feof(pointertorebasefile))
	{	
	fgets(tempstr,100,pointertorebasefile);
	sscanf(tempstr,"%s %d %d %s %d %d %d",name,&fwdb,&revb,pattern,&fwda,&reva,&cutposn);
		if( (!strcmp(name,argv[2])) ||(!strcmp(pattern,argv[2])))
				{
				flag=1;		
				break;
				}
	}
	fclose(pointertorebasefile);
	if(flag)
	{
	pointertorebasefile=fopen("resultsREcleavage.txt","w+");
	fprintf(pointertorebasefile,"NAME:%s \nCUTS ON THE FWD strand at %d positions upstream\n CUTS ON THE REV STRAND AT %d positions upstream \nPATTERN is %s \nCUTS ON THE FORWARD STRAND AT %d positions downstream \nCUTS ON THE REVERSE STRAND AT %d positions downstream \nCUTS at %d\n",name,fwdb,revb,pattern,fwda,reva,cutposn);
	searchforre_patterns_infnafile(pattern,text);
	fclose(pointertorebasefile);
	}
	else
	{
			printf("\nPattern not found\n");
			exit(1);
	}
}
// Find Restriction Enzyme cut sites in input FNA file
void searchforre_patterns_infnafile(char *rebasepatternstring, Text text)
{
	long int *positionsofcutsitesinfinafile;
	KMPPattern pattern(rebasepatternstring);
  if( (!strchr(rebasepatternstring,'R')) && (!strchr(rebasepatternstring,'Y')) && (!strchr(rebasepatternstring,'M')) && (!strchr(rebasepatternstring,'K')) && (!strchr(rebasepatternstring,'S')) && (!strchr(rebasepatternstring,'W')) && (!strchr(rebasepatternstring,'B')) && (!strchr(rebasepatternstring,'D')) && (!strchr(rebasepatternstring,'H')) && (!strchr(rebasepatternstring,'V')) &&(!strchr(rebasepatternstring,'N')) )
  //then regular expression
	 positionsofcutsitesinfinafile=kmpwrapper(rebasepatternstring,text);
  else
      positionsofcutsitesinfinafile=generic(rebasepatternstring,text);	  
  	  
	for(long int matchposition=0;matchposition<listofpotentialcutsites;matchposition++)
	{
			if((cutposn!=0)&&(fwdb!=0)&&(revb!=0)&&(fwda!=0)&&(reva!=0))
			fprintf(pointertorebasefile,"\nPATTERN FOUND AT %ld \n\tcuts at %d upstream on fwd strand \n\tcuts at %d upstream on reverse strand\n\tcuts at %d downstream on forward strand\n\tcuts at %d downstream on reverse strand\n\tcuts at position %d",positionsofcutsitesinfinafile[matchposition],positionsofcutsitesinfinafile[matchposition]-fwdb,positionsofcutsitesinfinafile[matchposition]-revb,positionsofcutsitesinfinafile[matchposition]+fwda,positionsofcutsitesinfinafile[matchposition]+reva,positionsofcutsitesinfinafile[matchposition]+cutposn);
		    else if((cutposn!=0)&&(fwdb==0)&&(revb==0)&&(fwda==0)&&(reva==0))
				fprintf(pointertorebasefile,"\nPATTERN FOUND AT %ld \n\tcuts at position %d",positionsofcutsitesinfinafile[matchposition],positionsofcutsitesinfinafile[matchposition]+cutposn);
			else if((cutposn==0)&&(fwdb!=0)&&(revb!=0)&&(fwda!=0)&&(reva!=0))		   
				fprintf(pointertorebasefile,"\nPATTERN FOUND AT %ld \n\tcuts at %d upstream on fwd strand \n\tcuts at %d upstream on reverse strand\n\tcuts at %d downstream on forward strand\n\tcuts at %d downstream on reverse strand",positionsofcutsitesinfinafile[matchposition],positionsofcutsitesinfinafile[matchposition]-fwdb,positionsofcutsitesinfinafile[matchposition]-revb,positionsofcutsitesinfinafile[matchposition]+fwda,positionsofcutsitesinfinafile[matchposition]+reva);
			else if((cutposn==0)&&(fwdb!=0)&&(revb!=0)&&(fwda==0)&&(reva==0))		   
				fprintf(pointertorebasefile,"\nPATTERN FOUND AT %ld \n\tcuts at %d upstream on fwd strand \n\tcuts at %d upstream on reverse strand",positionsofcutsitesinfinafile[matchposition],positionsofcutsitesinfinafile[matchposition]-fwdb,positionsofcutsitesinfinafile[matchposition]-revb);
			else if((cutposn==0)&&(fwdb==0)&&(revb==0)&&(fwda!=0)&&(reva!=0))		   
				fprintf(pointertorebasefile,"\nPATTERN FOUND AT %ld \n\tcuts at %d downstream on fwd strand \n\tcuts at %d downstream on reverse strand",positionsofcutsitesinfinafile[matchposition],positionsofcutsitesinfinafile[matchposition]-fwda,positionsofcutsitesinfinafile[matchposition]-reva);
			else
				fprintf(pointertorebasefile,"\nPATTERN FOUND AT %ld",positionsofcutsitesinfinafile[matchposition]);		
	}
}
