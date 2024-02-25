@echo off
setlocal enabledelayedexpansion

REM 创建一个临时文件来存储git diff的输出
set tempfile=%temp%\git-diff.txt

REM 获取已修改的文件列表
git diff --name-only > %tempfile%

REM 获取当前文件夹名称
for %%* in (.) do set foldername=%%~n*

REM 获取时间戳yyyyMMddHHmmss
set datetime=%date:~0,4%%date:~5,2%%date:~8,2%

REM 创建一个新的zip文件
set zipfile=%foldername%_modified_files_%datetime%.zip

REM 如果zip文件已经存在，删除它
if exist %zipfile% del %zipfile%

7z a %zipfile% @%tempfile%

REM 打印输出的文件路径
echo.
echo zip文件路径: %cd%\%zipfile%

REM 删除临时文件
del %tempfile%

REM 保持命令窗口打开
pause

endlocal
