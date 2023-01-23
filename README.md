# Lexical-and-Syntax-Analyzer

This project is an implementation of a Lexical and a Syntax Analyzer for the P-- programming language. 

This is an educational programming language designed to help the study of how compilers work. The syntax rules of this language can be found in the pdf: [Linguagem P--.pdf](https://github.com/mmussatto/Lexical-and-Syntax-Analyzer/blob/main/School%20Files/Linguagem%20P--.pdf)

## Authors

- Che Fan Pan ([@Che-Fan](https://github.com/Che-Fan))
- Eduardo Cavalari Valença ([@EduardoCavValenca](https://github.com/EduardoCavValenca))
- Marcos Vinicius Firmino Pietrucci ([@Marcos-Pietrucci](https://github.com/Marcos-Pietrucci))
- Murilo Mussatto ([@mmussatto](https://github.com/mmussatto))

## Compiling

To compile this project, just use the following command

<code>$ make </code>

## Running

To run the program, you must use the following command

<code>$ make run</code>

After that, you will be asked for the name of the text file containing the P-- code.

## Lexical Analyzer
 
The project was built in two parts. The first one was the development of a Lexical Analyzer to break the source code in a series of tokens. This was achieved by using state machines that read each character of the source code and create a token corresponding to what was read. 
 
After running the program, the output of the lexical analysis, with all the tokens created, can be found in the [tokens.txt](https://github.com/mmussatto/Lexical-and-Syntax-Analyzer/blob/main/Output/tokens.txt) file.
 
 
## Syntax Analyzer
 
The second part of the project was to perform a syntax analysis in the source code, following the syntax rules of the P-- language. In order to do this, numerous functions were created to simulate a derivation tree.
 
After running the program, the output of the syntax analysis can be found in the [errors.txt](https://github.com/mmussatto/Lexical-and-Syntax-Analyzer/blob/main/Output/errors.txt) file.


