@echo off

setlocal enabledelayedexpansion

set DELETE_DIR=build

for /r . %%a in (!DELETE_DIR!) do (
	if exist %%a (
		echo "remove "%%a
		rd /s /q "%%a"
	)
)

pause