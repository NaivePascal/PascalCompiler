import os
files = [
'array.pas'
'array1.pas',
'arrayref.pas',
'bool.pas',
'expression.pas',
'exptest.pas',
'fib.pas',
'fib2.pas',
'func.pas',
'if.pas',
'math.pas',
'mod.pas',
'noparm.pas',
'or.pas',
'proc.pas',
'recursion.pas',
'rel.pas',
'simple.pas',
'test.pas',
'test1.pas',
'test2.pas',
'ult-corrected.pas',
'ult.pas',
'unaryminus.pas',
'while.pas']

command = 'wget http://www.cs.vassar.edu/\~cs331/semantic_actions/examples/';
for f in files:
	os.system(command+f)