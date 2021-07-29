# Author: Lalitha Viswanathan
# Affilition: Tata Consultancy Services 
$arg1=@ARGV[0];

open(fh,$arg1);
open(fhw,">rebaseparsed.txt");
#levae the first 118 lines
for($i=0;$i<118;$i++)
{
$waste=<fh>;
}

$"="\t";
while($waste)
{
chomp($waste);	
	if($waste =~m/</)
	{
		$caret=0;
		for($x=1;$x<=8;$x++)
		{
			chomp($waste);
			#remove <1>  <2>..... from line
			$waste=~s/(<\d>)|(\s)//g;
			#in the fifth posn is the sqeuence code, if its a question mark , no processing further
			if($x==1)
			{
			 print fhw $waste."\t";
			}
			elsif($x==5)
			{
			 #if the sequence is ?, then no further processig
			 if($waste =~ m/\?/)
			 {
			   print fhw "0\t0\t$waste\t0\t0\t0\n"; 
			 }
			 else
			 {		
			 $temp=$waste;
			 #in temp replace brackets and \ sign with spaces
			 $temp=~ s/([()\/])/ /g;
			 @arr1=split(/ /,$temp);
			 # in waste, remove everthing other than sequence with carets 
			 #in waste hunt for the caret, if any
			 $waste=~ s/([()\/-])|(\d)|(\^M)//g;
			 #print $waste;
			 #exit(1);	
				for($e=0;$e<length($waste);$e++)
				{
				  if(substr($waste,$e,1)eq '^')
				  {
				    #print $e;	
				    $caret=$e+1;	
				  }	
				}
			#after locating caret, eliminate it
			$waste=~ s/\^//g;
			#arr1 is done to obtain the posns in a seq((x/y)<seq(with ot w/o a caret)(w/z)>)
			if((scalar(@arr1)==3)||(scalar(@arr1)==1))
			{
			print fhw "0\t0\t";
			}
			for($i=0;$i<scalar(@arr1);$i++)
			{
				#we have already located caret, hence we can eliminate it n write seq to file
				if($arr1[$i]=~ m/\^/)
					{$arr1[$i]=~s/\^//g;}
				print fhw $arr1[$i]."\t";
			}
			if(scalar(@arr1)==1)
			{
			print fhw "0\t0\t";}
			print fhw $caret."\n";
			}
			}
		$waste=<fh>;
		}
	}
	else
	{
	$waste=<fh>;	
	}
}

