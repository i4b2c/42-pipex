# Pipex

## Usage

``make`` to create the **pipex** executable

``./pipex file1 cmd1 cmd2 file2`` to execute

#### It must behave exactly the same as the shell command below:

``$> < file1 cmd1 | cmd2 > file2``

#### Examples

``./pipex infile "ls -l" "wc -l" outfile``

``./pipex infile "grep a1" "wc -w" outfile``

If you want to test your project you can use this repository : https://github.com/vfurmane/pipex-tester.
