program noparmTest;
 var a, b : integer;
        c : real;
  function two: integer;
    var n : integer;
    begin
      c := a + b;
      two := -(a+b);
    end;
  begin
    a := 1;
    b := 2;
    c := a+b+two;
    write(c);
  end.
