

{
*
* File:    sum1.pas
* Purpose: prints the sum of the positive integers in sumit.dat
* Author:  pc2@ecs.csus.edu or http://www.ecs.csus.edu/pc2
*
* $Id: sumit.pas 326 2006-10-25 02:53:57Z laned $
*
}

var
  tf  : text;
  i   : integer;
  sum : integer;

begin
   assign (tf,'sumit.dat');
   {$i-} reset (tf); {$i+}
   if ioresult <> 0 then
      writeln('could not open file sumit.dat ')
   else
   begin

   sum := 0;
   while not eof (tf) do
   begin
       readln(tf,i);
       if (i > 0) then
            sum := sum + i;
   end;

   writeln('The sum of the integers is ',sum);
   end;

end.
{ EOF }
