$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
$binary = Join-Path $root 'output\CPU.exe'
$testBinary = Join-Path $root 'output\CPU_tests.exe'
New-Item -ItemType Directory -Force -Path (Split-Path -Parent $binary) | Out-Null

$libSources = @(Get-ChildItem (Join-Path $root 'src') -Filter *.cpp | Where-Object { $_.Name -ne 'main.cpp' } | Select-Object -ExpandProperty FullName)
$appSources = @((Join-Path $root 'src\main.cpp')) + $libSources
$testSources = @((Join-Path $root 'tests\cpu_tests.cpp')) + $libSources

& g++ -std=c++17 -Wall -Wextra -pedantic -I (Join-Path $root 'include') $appSources -o $binary
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

& g++ -std=c++17 -Wall -Wextra -pedantic -I (Join-Path $root 'include') $testSources -o $testBinary
if ($LASTEXITCODE -ne 0) { exit $LASTEXITCODE }

Write-Host "Built: $binary"
Write-Host "Built: $testBinary"
