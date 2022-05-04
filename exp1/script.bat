@echo off
for /l %%i in (0,1,9) do a.exe A_h1 input0%%i.txt target0%%i.txt
for /l %%i in (0,1,1) do a.exe A_h1 input1%%i.txt target1%%i.txt
for /l %%i in (0,1,9) do a.exe A_h2 input0%%i.txt target0%%i.txt
for /l %%i in (0,1,1) do a.exe A_h2 input1%%i.txt target1%%i.txt
for /l %%i in (0,1,9) do a.exe IDA_h1 input0%%i.txt target0%%i.txt
for /l %%i in (0,1,1) do a.exe IDA_h1 input1%%i.txt target1%%i.txt
for /l %%i in (0,1,9) do a.exe IDA_h2 input0%%i.txt target0%%i.txt
for /l %%i in (0,1,1) do a.exe IDA_h2 input1%%i.txt target1%%i.txt
pause

