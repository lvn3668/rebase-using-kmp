// Author: Lalitha Viswanathan
//Affiliation: Tata Consultancy Services 
#include <iostream>
extern int listofpotentialcutsites;
class Text;
class KMPPattern{
int *suffixprefixvalues;
char* patternstring;
int lengthofpattern;
	public:
// Constructor
KMPPattern(char *);
// Destructor 
~KMPPattern();
//Print suffix prefix vals along pattern
void getsuffixprefixpreprocessedvals() const{
		     for(int counter=0;counter<lengthofpattern;counter++)
			std::cout<<" "<<suffixprefixvalues[counter];
		    }
// return length of pattern 
int getpatternlength() const{return lengthofpattern;}
// return pattern string
char* getpatternstring() const{return patternstring;}
void buildsuffixprefixvalarrayforpattern();
char *substringofpattern_prefix_suffix_to_buildspindex(int,int);
int getsuffixprefixvalueatposinpattern(int x)const{return suffixprefixvalues[x];}
};

// Text in which pattern is to be searched
class Text{
char* text,*complementarysequence;
int textlength;
	public:
	Text(char *,int);
	Text(char *);	
	~Text();
	// return length of text
	int getlength() const{return textlength;}
	// return substring within text
	char* getstr() const{return text;}
};
// Overloaded contrusctor along text string
	Text::Text(char *textstring,int size)
	{
		textlength=size;
		text=(char *)malloc(sizeof(char)*textlength);
		complementarysequence = (char*)malloc(sizeof(char) * textlength);
		strcpy(text,textstring);
	}
	// Overloaded constructor to build text object from file 
	Text::Text(char *filename)
	{
	FILE* pointertotextfile;
	  char tempstr[500],ch;
	  int temp=0,counterforcomplementarysequence=0,counter;
	  if(!(pointertotextfile=fopen(filename ,"r")))
	  {
			  printf("file %s  does not exist\n",filename);
			  exit(1);
	  }
	  fseek(pointertotextfile,0L,SEEK_END);
	  textlength=ftell(pointertotextfile);
	  text=(char *)(malloc(sizeof(char)*textlength));
	  complementarysequence=(char *)(malloc(sizeof(char)*textlength));
	  fseek(pointertotextfile,0L,SEEK_SET);
	  fgets(tempstr,500,pointertotextfile);
	  while(!feof(pointertotextfile))
	  {
	     ch=fgetc(pointertotextfile);
	     if((ch=='A')||(ch=='T')||(ch=='C')||(ch=='G'))
	       text[temp++]=ch;
  	  }
          fclose(pointertotextfile);
	  textlength=temp;

	  for(counter=textlength-1;counter>=0;counter--)
	  {
		  switch(text[counter])
		  {
			  case 'A':
		  		complementarysequence[counterforcomplementarysequence++]='T';
				break;
			  case 'T':
		  		complementarysequence[counterforcomplementarysequence++]='A';
				break;
			  case 'G':
		  		complementarysequence[counterforcomplementarysequence++]='C';
				break;
			  case 'C':
		  		complementarysequence[counterforcomplementarysequence++]='G';
				break;
		  }
	  }
	}
Text::~Text()
{
}

long int* generic(KMPPattern pattern, Text text)
{
	int patternlength=pattern.getpatternlength();
	int textlength=text.getlength();
	// pattern is pointer to str (pattern string) in KMPPattern class
	// text is pointer to text string in Text class
	char* pattern = pattern.getpatternstring();
	char* text = text.getstr();
	long int *results=(long int *)malloc(sizeof(long int)*(textlength/patternlength));

	for(int counter=0;counter<textlength;counter++)
	{
		 int counteralongpattern=0;
		 int counteralongtext=counter;	 
		while(counteralongpattern<patternlength)
		{
		 if(pattern[counteralongpattern]==text[counteralongtext])
		   {	 
		   counteralongtext++;
		   counteralongpattern++;
		   }
		 // move along till a mismatch is encountered
		 // 
		 else if(pattern[counteralongpattern]=='R')
		{
			if((text[counteralongtext]=='G')||(text[counteralongtext]=='A'))
			{counteralongtext++;
			counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='Y')
		{
			if((text[counteralongtext]=='C')||(text[counteralongtext]=='T'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='M')
		{
			if((text[counteralongtext]=='C')||(text[counteralongtext]=='A'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='K')
		{
			if((text[counteralongtext]=='G')||(text[counteralongtext]=='T'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='S')
		{
			if((text[counteralongtext]=='G')||(text[counteralongtext]=='C'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='W')
		{
			if((text[counteralongtext]=='T')||(text[counteralongtext]=='A'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='B')
		{
			if((text[counteralongtext]=='G')||(text[counteralongtext]=='C')||(text[counteralongtext]=='T'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='D')
		{
			if((text[counteralongtext]=='G')||(text[counteralongtext]=='A')||(text[counteralongtext]=='T'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='H')
		{
			if((text[counteralongtext]=='C')||(text[counteralongtext]=='A')||(text[counteralongtext]=='T'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='V')
		{
			if((text[counteralongtext]=='G')||(text[counteralongtext]=='A')||(text[counteralongtext]=='C'))
				{counteralongtext++;
				counteralongpattern++;}
			else
				break;
		}
		else if(pattern[counteralongpattern]=='N')
			{
			counteralongtext++;
			counteralongpattern++;
			}
		 else
			 break;
		}
		if(counteralongpattern>=patternlength)
			{
			results[listofpotentialcutsites]=counter;
			listofpotentialcutsites++;
			}
	}
	// results contains index positions where pattern and text match 
	return results;
}


// Function that sets suffix prefix values for a given index position in the pattern
void KMPPattern::buildsuffixprefixvalarrayforpattern()
{
	suffixprefixvalues=(int *)malloc(sizeof(int)*lengthofpattern);
	for(int counteralongpatternstring=0;counteralongpatternstring<lengthofpattern;counteralongpatternstring++)
		suffixprefixvalues[counteralongpatternstring]=0;
	if(patternstring[1]==patternstring[0])
		suffixprefixvalues[1]=1;
	else
		suffixprefixvalues[1]=0;
	int suffixprefixvalueatthatpositioninpatternstring;
	// flag when longest prefix that is also matching suffix is reached 
	for(int innercounteralongpatternstring=2,flag=0;innercounteralongpatternstring<lengthofpattern;innercounteralongpatternstring++,flag=0)
	{
		// find prefix , suffix
		// store index past the matching suffix (end of matching suffix string)
		// speeds up pattern search in function call kmpwrapper 
		// for a given index position i in pattern, find prefix and all suffixes along length of pattern
		// for a given position along the pattern string, store index of suffix 
	for(int lengthofprefixthatisalsopropersuffix=1;(lengthofprefixthatisalsopropersuffix-1)<(innercounteralongpatternstring-lengthofprefixthatisalsopropersuffix);lengthofprefixthatisalsopropersuffix++)
	{
		char* prefixsubstr=this->substringofpattern_prefix_suffix_to_buildspindex(innercounteralongpatternstring-lengthofprefixthatisalsopropersuffix,innercounteralongpatternstring-1);
		char* suffixsubstr=this->substringofpattern_prefix_suffix_to_buildspindex(0,lengthofprefixthatisalsopropersuffix-1);
		if(!strcmp(prefixsubstr,suffixsubstr))
		// if prefix and suffix don't match, move to start of next suffix string
		// store index of position along pattern string where prefix and suffix strings don't match
		// repeat process for all sub-suffixes 
		// these indices are used to jump that many positions along text string while searching for pattern in string 
		// 
		{suffixprefixvalueatthatpositioninpatternstring=lengthofprefixthatisalsopropersuffix;flag=1;}
	}
	if(flag)
	  suffixprefixvalues[innercounteralongpatternstring]=suffixprefixvalueatthatpositioninpatternstring;
	}
}
// Overloaded constructor
	KMPPattern::KMPPattern(char *pattern)
	{
		patternstring=(char *)malloc(sizeof(char)*strlen(pattern));
		strcpy(patternstring,pattern);
		lengthofpattern=strlen(pattern);
	}
	//Destructor
KMPPattern::~KMPPattern()
{
}

// return substring of pattern string 
// used to get suffixes / sub strings 

char* KMPPattern::substringofpattern_prefix_suffix_to_buildspindex(int index,int indexofkmppatternmatchsubstring)
{
	char* temp=(char*)malloc(sizeof(char)*(indexofkmppatternmatchsubstring-index+1));
	char *pointertostr=patternstring;
	for(int counteralongpattern=0;counteralongpattern<index;counteralongpattern++)
		pointertostr++;
	strncpy(temp,pointertostr,indexofkmppatternmatchsubstring-index+1);
	return temp;
}

// Function that builds the suffix prefix list for the pattern 
// uses the same to search for pattern in text
// returns position of matches 
long int* kmpwrapper(KMPPattern pattern, Text text)
{
	pattern.buildsuffixprefixvalarrayforpattern();
	char *pointertotext=text.getstr();
	int textlength=text.getlength();
	char *pointertopattern=pattern.getpatternstring();
	int patternlenggth=pattern.getpatternlength();
	long int *results=(long int *)malloc(sizeof(long int)*(textlength/patternlenggth));
	int counterforkmpsearch=0,matchpos;
	// use the suffix prefix values built in pattern.setsuffixprefixvalsforpattern 
	// to search for pattern in text
	// return index of matches

	while(counterforkmpsearch+patternlenggth<textlength)
	{
		int patterncounter=0,flag=0;
		matchpos=counterforkmpsearch;
		while((pointertopattern[patterncounter]==pointertotext[counterforkmpsearch])&&(patterncounter<patternlenggth))
		{
			patterncounter++;
			flag=1;
			counterforkmpsearch++;
		}
		if(!flag)
			counterforkmpsearch++;
		else
		{
			if(patterncounter==patternlenggth)
			{
				results[listofpotentialcutsites]=matchpos;
				counterforkmpsearch=matchpos+1;
				listofpotentialcutsites++;
			}
			else
			{
				int suffixprefixvalforgivenposalongpatternstring=pattern.getsuffixprefixvalueatposinpattern(patterncounter);
				// if value is zero, no characters are matching
				// move to next position along text
				// suffix prefix value gives number of matching characters and so how much to jump forward along text 
				if(suffixprefixvalforgivenposalongpatternstring==0)
				   counterforkmpsearch+=1;
				else
					// jump that many positions along text
				   counterforkmpsearch+=suffixprefixvalforgivenposalongpatternstring;		
			}
		}	
	}
return results;
}


