#!/usr/bin/perl

# 
# File:    rotate.pl 
# Purpose: to create rotating html web pages based on summary.html
# Author:  pc2@ecs.csus.edu
# Revised: Wed Jun 11 00:08:38 PDT 2003
# 
# $Id: rotate.pl 326 2006-10-25 02:53:57Z laned $
# 

#
# Input
#
# summary.html in current directory or $PC2HOME/html directory.
#
# Ouptut 
#
# Creates a number of new summary html files in current directory
# named in the form of summary#.html where summary1.html is the first
# file created.
#
# Directions:
# 
# These two variables should be changed.  They should be
# set according to the number of teams in the summary.html
# file and which order the pages should be rotated.
# 

$perpage=14;  # number of teams per page
@nextpage=(0,2,3,4,5,1);  # order that the pages are rotated

#

$nomoreupdates=0;
 
$enableflag=0;  # flag mode 
$flagheight=30; # good
$flagheight=20; # for john

$maxretry=4;
$refresh=15;  # rotate/refresh in seconds
$maxpage=$#nextpage;

&load_flags("flag.team.txt") if $enableflag == 1;

$f="summary.html";  # Input file name
$done=0;
$rowcount=0;

for($retry=0;(($retry < $maxretry ) && $done == 0); $retry++) {
  open(IN,"$f") || die("Unable to read $f: $!\n");
  while(<IN>) {
    chomp;
    if (/\<tr\>/) {
      if ($firstrow eq "") {
	s/tr/tr BGCOLOR="#EEEEFF"/ if $rowcount % 2 == 0;
	s#<th><strong><u>Name</u></strong></th>#<th><strong><u>Flag</u><strong></th><th><strong><u>Name</u></strong></th># if $enableflag == 1;
        $firstrow=$_;
      } elsif (/\<td\>Summary\<\/td\>/i) {
        $summary=$_;
	if ($enableflag == 1 ) {
	  	$summary =~ s#Summary#</td><td><b>Total Summary</b>#;
	} else {
	  	$summary =~ s#Summary#Total Summary#;
	}
	$summary =~ s/tr/tr BGCOLOR="#EEEEFF"/;
	$summary =~ s#<td>(\d+/(--|\d+)(/\d+)?)</td>#<td align=center>$1</td>#g;
      } elsif (/\<tr\>/) {
	$rowcount++;
	s/tr/tr BGCOLOR="#EEEEFF"/ if $rowcount % 2 == 0;
	$val = $1;
	s#<td>(\d+/(--|\d+))</td>#<td align=center>$val</td>#g;
	if ($enableflag == 1 && m#<td>\d+</td>(<td>)([^\<]*)</td>#) {
          $t=$2;
	  if (!defined($flag{$t})) {
		 warn("No flag{t} for '$t'\n");
	  }
          s#<td>$t#<td align=center><img src="flags/$flag{$t}" height=$flagheight/></td><td>$t#;
	  if (! -f "flags/$flag{$t}") {
            warn("Missing flag flags/$flag{$t} for $t\n");
          }
	}
	$val = $1;
	s@<td>(\d+)</td>@<td align=right>$val&nbsp;&nbsp;</td>@g;
        push(@rows,$_);
      }
    } elsif (/^Created by/i) {
      $created="<p>Created by California State University, Sacramento PC<sup>2</sup><br>\nhttp://www.ecs.csus.edu/pc2/<br>\n";
      $created.= <IN>; # Last Updated
      $created.= <IN>; # Date
    }
    $done=1 if (/\<\/html\>/);
  } # while <IN>
  close(IN);
  sleep 1 if ($done == 0);
}
if ($done == 0) {
  die("Unable to read a complete $f\n");
}

foreach($page=1;$page <= $#nextpage; $page++) {
  &print_page($page,$nextpage[$page],($page-1)*$perpage+1,$page*$perpage);
} 

sub print_page {
  my($thispage,$nextpage,$start,$end)=@_;
#  warn("print_page($thispage,$nextpage,$start,$end)\n");

  open(OUT,">summary$thispage.html")
       || warn("Unable to write summary$thispage.html");
  $nextfile="summary$nextpage.html";          
  print OUT <<EOM;
<html>
<!-- next page is summary$nextpage.html -->
<META HTTP-EQUIV="REFRESH" CONTENT="$refresh; URL=$nextfile">
<META HTTP-EQUIV="CACHE-CONTROL" CONTENT="no-cache">
<META HTTP-EQUIV="Pragma" CONTENT="no-cache">
<head>
<title>
$start thru $end
</title>
</head>
<body>
<center>
<table border=0 cellpadding=2>
$firstrow
EOM
  $end=$#rows+1 if $end > ($#rows+1);
  foreach($i=$start ; $i <= $end; $i++) {
    print OUT $rows[$i-1]."\n";
  }
  print OUT <<EOM;
$summary
</table>
</center>
<font size=-1 face="verdana, arial, helvetica">
<p align=right>Page $page of $maxpage</p>
EOM
  if ($nomoreupdates==1) {
#    print OUT "<p align=center><font size=+2><b>No More Updates</b></font></p>";
    print OUT "<p align=center><font size=+1><b>Standings with 1 hour left. There will be no more scoreboard updates.</b></font></p>";
  } else {
    print OUT "<br><br>";
  }
  print OUT <<EOM;
$created</font>
</body>
</html>
EOM

}

# format of flag.team.txt:
# filename Team Title (must match title on summary.html)
# ca-flag.gif	University of T
# ca-flag.gif	University of W
# us-flag.gif	C University
# us-flag.gif	D University
# us-flag.gif	F Institute of Technology
# us-flag.gif	H University

# filename can be in current or flags/ directory

sub load_flags {
  my($f)=shift;
#  warn("load_flags($f)\n");
  open(IN,"$f") || die("Unable to $f: $1\n");
  while(<IN>) {
    chomp;
    @t=split(m#\t#);
    $flag{$t[1]}=$t[0];
    $k=$t[1];
    $k=~ s/^"//;
    $k=~ s/"$//;
    $flag{$k}=$t[0];
  }
  close(IN);
}

# eof rotate.pl
