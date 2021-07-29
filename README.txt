Author: Lalitha Viswanathan
Affiliation: Tata Consultancy Services 
rebase.pl converts REBASE.TXT into rebaseparsed.txt
rebase.cpp is main .cpp file
kmp is file for exact pattern matching
kmp.cpp also contains code done for [patetrn searching with mismatches (rules
of grammr)
rulesofgrammar.txt contains rules of grammar (pattern searching with
mismatches)
results of finding recleavage site are in resultsREcleavagesite.txt
REBASE at times gives enzyme as (x/y) enxyme pattern (w/z)
it means at x postions upstream on fwd strand and w posns dwnstream on fwd
strand at y posns upstream on rev strand and z posns dwnstraem on rev strand
sometimes a ^ is found in the pattern as shown aa^aa 
it cuts at ^ posn  
sometimes none of the above is there
in such a case am showing the location at which the pattern is found as , the
posn of cutting

