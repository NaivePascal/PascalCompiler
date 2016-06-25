
program funcTest;       
var
        i, j, k:integer;

function Sum(a,b:integer):integer;
begin
        Sum := a + b;
end;

begin
        i := 10;
        j := 20;
        k := Sum(i,j);
        writeln(k);
end.