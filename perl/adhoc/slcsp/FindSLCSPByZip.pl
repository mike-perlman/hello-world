#!/bin/perl

%ratesByStAr = ();
%zipGeos = ();
@searchzips = ();
@fields = ();
%ambiguousZips = ();

####################
# set these to enable stderr logging
#
$stderrLog = undef;
$stderrLogCsvline = undef;
$stderrLogAdd = undef;
$stderrLogRateMap = undef;
$stderrLogAmbiguous = undef;

####################
#file paths + defaults
#
$filenameSearch = exists $ENV{'SLCSP_SEARCH_ZIPS'} ? $ENV{'SLCSP_SEARCH_ZIPS'} :  '<.\slcsp.csv';
$filenameGeo    = exists $ENV{'SLCSP_GEO_INFO'} ? $ENV{'SLCSP_GEO_INFO'}       :  '<.\zips.csv';
$filenameRates  = exists $ENV{'SLCSP_PLAN_INFO'} ? $ENV{'SLCSP_PLAN_INFO'}     :  '<.\plans.csv';


open SEARCHFILE, $filenameSearch;                            #load into searchCritera.
<SEARCHFILE>;
while ($line = <SEARCHFILE>) {
   my ($zip) = makeCsvLine($line,(0)); 
   push @searchZips, $zip;
}
close SEARCHFILE;


open ZIPFILE, $filenameGeo;
<ZIPFILE>;
while ($line = <ZIPFILE>) {                                  # load into {zip => StAr} hash
  my ($zip, $state, $area) = makeCsvLine($line, 0,1,4);
  next unless grep {$_ == $zip} @searchZips;                #desired zipcodes only
  my $stateArea = $state . $area;
  if (defined ($zipGeos{$zip}) && $zipGeos{$zip} ne $stateArea) { 
    $ambiguousZips{$zip} = $stateArea 
  };
  $zipGeos{$zip} = $stateArea;
}
close ZIPFILE;


open PLANFILE, $filenameRates;
<PLANFILE>;
while ($line = <PLANFILE>) {                                #load into {star => (rates)} hash.
  next if $line !~ /Silver/;                                #silver plans only
  my ($state, $area, $rate) = makeCsvLine($line,(1,4,3));
  my $stateArea = $state . $area;
  $ratesByStAr{$stateArea} = [] unless exists $ratesByStAr{$stateArea}->[0];
  print stderr "Loading $val to $stateArea: ".join(',', @{$ratesByStAr{$stateArea}}) . "\n" if ($stderrLogAdd);
  addOrdered($ratesByStAr{$stateArea}, $rate);
}
close PLANFILE;

################
# logging
#
if ($stderrLogRateMap){
  while (($k,$v) = each(%ratesByStAr)) {
    print stderr "$k" . ':' . join (',', @{$v}) . "\n";
  }
}

if ($stderrLogAmbiguous) {
  while (($k,$v) = each(%ambiguousZips)) {
    print stderr "$k" . ':' . join (',', @{$v}) . "\n";
  }
}

######################3
# output.  match each zip -> star -> (rate list), pick the second one if it exists.
#
print "zipcode,rate\n";
my $out;
for $zip (@searchZips) {
  $out = 0;
  if (exists $ambiguousZips{$zip}) {
    print stderr "$zip maps to multiple state/areas. skipping..." if ($stderrLogAmbiguous);
  }
  ######
  # match both hashes, and the resulting rate list has > 1 rate.
  #
  elsif (defined ($zipGeos{$zip}) && $#{$ratesByStAr{$zipGeos{$zip}}} >= 1) {
     $out = $ratesByStAr{$zipGeos{$zip}}->[1] + 0;
  }
  
  if ($out > 0) {
    printf "%s,%.2f\n", $zip, $out;
  }
  else {
    print $zip . ",\n";
  }
}



#######################################

sub makeCsvLine {
  my $line = shift;
  my @offsets = @_;
  my @out;

  chomp $line;
  my @fields = split /,/ , $line;
  
  print stderr "makeCsvLine() offsets= " . join(':',@offsets) . ", fields= " . join (' - ', @fields)  if ($stderrLogCsvline);

  for $o (@offsets) {
    push @out, $fields[$o];
  }
 
  print stderr " ... output: " . join(',',@out)  . "\n" if ($stderrLogCsvline);
  
  return @out;
}


###################
# Inserts an element into a list, creating a list if needed.
# Attempts to preserve numeric order with each insert.
# Skips insert if a value already exists in @$listRef.
# 
# Returns the index of the inserted (or located) value.
#
sub addOrdered($listRef, $val) {
  ($listRef,$val) = @_;
  $val += 0;

  if ($#{$listRef} < 0) {
    $listRef->[0]= $val; return 0;
  }

  for $i (0..$#{$listRef}) {
    return $i if ($val == $listRef->[$i]);
 
    if ($val < $listRef->[$i]) {
      splice(@{$listRef},$i,0, $val);
      return $i;
    }
  }

   # new max value   
   $listRef->[$#{$listRef}+1] = $val;
   return $#{$listRef}
}

