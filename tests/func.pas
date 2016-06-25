
program funcTest;       
var
        i, j, k:integer;

procedure Sum(a,b:integer);
var ret:integer;
begin
        ret := a + b;
        writeln(ret);
end;

begin
        i := 10;
        j := 20;
        Sum(i,j);
end.