# Embedded_For_Interview_T8
All of my knowledge and practice in this course is here
## C language
<details>
  <summary>C Basic</summary>

  ### Data type
  Table below include commonly used types in C programming
  |Type|Size (byte)|Range|Specifier|
  |:---|:---:|:---:|:---:|
  |signed char|1|-128 to 127|`%c`|
  |unsigned char|0 to 255|`%c`|
  |signed short|2|-32768 to 32767|`%hd`|
  |unsigned short|2|0 to 65535|`%hu`|
  |signed int|4|-2147483648 to 2147483647|`%d`|
  |unsigned int|4|0 to 4294967295|`%u`|
  |float|4|1.2E-38 to 3.4E+38|`%f`|
  |double|8|1.7E-308 to 1.7E+308|`%lf`|
  |long double|16|3.4E-4932 to 1.1E+4932|`%Lf`|
  |signed long long|8|-9223372036854775808 to 9223372036854775807|`%ll`|
  |unsigned long long|8|0 to 18446744073709551615|`%llu`|
  |int8_t|1|-128 to 127|`%d`|
  |uint8_t|1|0 to 255|`%d` `%u`|
  |int16_t|2|-32768 to 32767|`%d`|
  |uint16_t|2|0 to 65535|`%d`|
  |int32_t|4|-2147483648 to 2147483647|`%d`|
  |uint32_t|4|0 to 4294967295|`%d`|

</details>

<details>
    <summary>Compilation Process</summary>

### Brief

[Link tham khảo [1]](https://www.scaler.com/topics/c/compilation-process-in-c/)

- Compilation process is a process of converting a source code(C/C++, C#, Java, Python,...) into object code(Assembly code). The compiler will check syntacytical and structureal error before the program starts executing. The compilation process in C envolve 4 step:

  + Preprocessor.
  + Compiler.
  + Assembler.
  + Linker.

![compilation](compilation.png)

### Preprocessor
- Preproceccor convert source code to intermediate code, which has extension of .i, and it is the expanded form of C program containing all of content of header files, macro expansion and condition compilation.

  + Take the source code as an input.
  + Removeing all comments in program.
  + Process macros expandsion, condition compilation(ex: #ifndef, #elif, #endif,...).
  + Include header file.

### Compiler
- Compiler phase in C use an inbuilt compiler software to convert the intermediate file(.i) to Assembly file(.s) having Assembly lever instruction (Low-lever language).
- Compiler phase will Analyze syntax, tell us any syntax error or warning  in the source code through the terminal screen.

### Essembly
-  Essembly phase use an assembler to convert essembly code to machine - understandable code(in binary/hexadecimal format) known as object code, which has an extension of .obj in DOS and .o in UNIX OS.

### Linking
- Linking is a process of including the library file into our program, more details, we have an object file having machine-lever code, its passed through the linker which links the library files with the object file to generat an executable file with an extension of .exe in DOS and .out in UNIX OS.
- Library file are some predefine files that contain difines of the function in the machine language with the extension of .lib.
- There are some unkown statements in the object file that operate system can't understand. You can understand you read a book have some word you don't know and you'll use dictionary to find the meaning of those word. Similarly, we you library files to give meaning to unknown statements in out object files.
</details>

