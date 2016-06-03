program math;
var
	i: integer;
begin
	i := (1 + 3) * 4;
	if i = 16 then
		write('first test passed.\n')
	else begin
		write('first test failed i = ');
		write(i);
		write('.\n');
	end;

	i := 1 + 3 * 4;
	if i = 13 then
		write('second test passed.\n');
	else begin
		write('second test failed i = ');
		write(i);
		write('.\n');
	end;

	i := 16 div 2 + 3;
	if i = 11 then
		write('third test passed.\n');
	else begin
		write('third test failed = ');
		write(i);
		write('.\n');
	end;

	i := 32769 * 2 - 2;
	if i =  65536 then
		write('fourth test passed.\n');
	else begin
		write('fourth test failed = ');
		write(i);
		write('.\n');
	end;

end