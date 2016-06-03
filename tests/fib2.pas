program fib2;
var
	fib: array[1..20] of integer;
	response, i: integer;

begin
	fib[1] := 1;
	fib[2] := 1;
	i := 3;
	while i <= 20 do begin
		fib[i] := fib[i-1] + fib[i-2];
		i := i + 1;
	end;

	i := 0;
	while i = 0 do begin
		write('Enter a number from 1 to 20 (0 to quit) : ');
		read(response);
		if response < 1 then
			i := 1
		else if response > 20 then
			write('I said ...')
		else
			writeln('Fib(',response,') = ', fib[response]);
	end
end.
