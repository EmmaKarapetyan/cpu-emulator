$ErrorActionPreference = 'Stop'
$root = Split-Path -Parent $MyInvocation.MyCommand.Path
& (Join-Path $root 'build.ps1')
& (Join-Path $root 'output\CPU_tests.exe')
exit $LASTEXITCODE
