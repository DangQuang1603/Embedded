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

<details>
  <summary>Macro</summary>
  
### Macro là gì?
- Macro là một đoạn mã trong chương trình, sẽ được thay thế bằng giá trị của macro trong quá trình tiền xử lý. Macro được định nghĩa bởi cấu trúc #define và không cần kết thúc bằng dấu ";".
- Dưới đây là một đoạn mã ví dụ dùng macro trong C/C++:
  ```c
  // C program to illustrate macros
  #include <stdio.h>
  
  // Macro definition
  #define LIMIT 5
  
  // Driver Code
  int main()
  {
  	// Print the value of macro defined
  	printf("The value of LIMITis %d",LIMIT);
  	return 0;
  }
  ```c
  
>Output: The value of LIMIT is 5

## Một số macro

### Macro hàm
```
  void test()
  {
      printf("Hello world");
  }
  #define TEST test()
```
### Macro có tham số truyền vào (Function-like Macros)
```
  #define TONG(a,b) a+b
```
### Macro hàm có tham số truyền vào (Stringizing Operator (#))
```
  #define INPUT_DISPLAY(var,cmd,cond) \
    int var;                          \
    do                                \
    {                                 \
      printf(cmd);                    \
      scanf(%d, &var);                \
    } while(cond)                     \
    printf(#var);                     \
    printf("= %d\n", var);
```
>Dấu '#' để biến var trong trường hợp trên thành chuỗi.
### Nối chuỗi trong macro (Token Pasting Operator (##))
```
  #define variable(name)  \
  double double_##name    \
  int    int_##name       \
  char    char_##name     
```
### Variadic macro
- Variadic macro trong C/C++ cho phép người dùng định nghĩa một macro có thể nhận số lượng tham số tùy ý (variadic parameter). Variadic macro được hỗ trợ từ phiên bản C99 trở đi.
- Một ví dụ về macro:
```
    #include <stdio.h>
    #include <stdarg.h>

    // Variadic macro to calculate the sum of variable arguments
    #define SUM_VALUES(...) \
        sum_values(__VA_ARGS__, 0)

    // Helper function to calculate the sum of values
    int sum_values(int first, ...) {
        int sum = first;
        va_list args;
        va_start(args, first);

        int value;
        while ((value = va_arg(args, int)) != 0) {
            sum += value;
        }

        va_end(args);
        return sum;
    }

    int main() {
        int result = SUM_VALUES(1, 2, 3, 4, 5, 0);
        printf("Sum: %d\n", result);

        result = SUM_VALUES(10, 20, 30, 40, 0);
        printf("Sum: %d\n", result);

        return 0;
    }
```
>Trong đoạn mã trên, SUM_VALUES là một variadic macro, và nó gọi đến một hàm hỗ trợ sum_values. Hàm này sử dụng va_list, va_start, và va_arg từ thư viện stdarg.h để duyệt qua các tham số biến đổi và tính tổng của chúng. Để kết thúc danh sách tham số biến đổi, ta sử dụng giá trị 0.

### Macro có điều kiện (Conditional Compilation Directives)

```
    #ifdef DEBUG
    // Code chỉ được biên dịch khi macro DEBUG được định nghĩa
    // ...
#endif
```
>Sử dụng để kiểm soát quá trình biên dịch dựa trên các điều kiện
```
  #ifndef DEBUG
    // Code chỉ được biên dịch khi macro DEBUG chưa được định nghĩa
    // ...
#endif
```
> sử dụng #ifndef để kiểm tra nếu macro chưa được định nghĩa

</details>

<details>
  <summary>Variable</summary>

### Biến static
1. Cục bộ
   - Chỉ khởi tạo một lần và chỉ bị hủy khi dừng chương trình
   - Chỉ được gọi trong hàm nó được khai báo
   - Ứng dụng: biến milis trong hàm millis arduino
2. Toàn cục
   - Chỉ file chứa nó mới gọi được
   - Ứng dụng: không cho gọi ở file khác để tránh trường hợp gán sai dẫn đến lỗi.
### Biến external
Trong C/C++ biến external được khai báo thường để dùng ở file nguồn khác. Khai báo external không cấp phát bộ nhớ cho biến, nó chỉ cung cấp thông tin về biến (Khai báo external không tạo ra bộ nhớ mới cho biến, nó chỉ thông báo cho trình biên dịch rằng biến này đã được khai báo ở nơi khác và chương trình sẽ sử dụng nó)
1. Biến external trong C
```
    // File1.c
    int globalVar = 42;  // Khai báo và cấp phát bộ nhớ

    // File2.c
    extern int globalVar;  // Khai báo để sử dụng biến ở nơi khác
```
2. Biến external trong C++
```
    // File1.c
    int globalVar = 42;  // Khai báo và cấp phát bộ nhớ

    // File2.c
    extern int globalVar;  // Khai báo để sử dụng biến ở nơi khác
```
### Biến register
Trong C và C++, biến register được sử dụng để gợi ý trình biên dịch rằng biến được khai báo với từ khóa này thường xuyên được sử dụng và nên được lưu trữ trong thanh ghi (register) của CPU để truy cập nhanh chóng. Tuy nhiên, hiện đại các trình biên dịch thường xuyên hiểu và tối ưu hóa mã máy mà không cần sự can thiệp của register, nên việc sử dụng nó thường ít phổ biến và có thể không có ảnh hưởng nhiều đến hiệu suất.

### Biến volatile
Trong C và C++, volatile là một từ khóa được sử dụng để thông báo cho trình biên dịch rằng giá trị của biến có thể thay đổi ngẫu nhiên mà không cần sự can thiệp của chương trình, chẳng hạn do các sự kiện ngoại vi như ngắt (interrupts) hoặc do các tiến trình khác. Từ khóa này ngăn cách việc tối ưu hóa của trình biên dịch có thể làm giảm hiệu suất khi giả sử rằng giá trị của biến không thay đổi trong quá trình thực thi.
```
#include <stdio.h>
    int main() {
        volatile int sensorValue = 0;  // Biến volatile

        while (1) {
            // Đọc giá trị từ cảm biến
            sensorValue = readSensor();

            // Thực hiện các xử lý dựa trên giá trị cảm biến
            processSensorValue(sensorValue);
        }

        return 0;
    }
```
Trong ví dụ này, biến sensorValue được khai báo với từ khóa volatile. Điều này có ý nghĩa rằng trình biên dịch không nên tối ưu hóa, cache, hoặc thực hiện bất kỳ biện pháp tối ưu hóa nào khác liên quan đến việc truy cập hoặc sử dụng biến này. Thông thường, biến volatile được sử dụng khi biến có thể thay đổi không đồng bộ, chẳng hạn trong các ứng dụng liên quan đến đọc/ghi từ/xuất các thanh ghi của phần cứng, đọc dữ liệu từ các cổng vào/ra, hoặc trong việc xử lý ngắt.
</details>

<details>
  <summary>Struct and union</summary>

###Struct
#####Syntax
```
    Struct struture name{
      datatype member_name1;
      datatype member_name2;
      ....
      ....
    }
```

#####C Structure Definition
With struct template
```
    struct struture name{
      datatype member_name1;
      datatype member_name2;
      ....
      ....
    } variable1, variable2,...;
```
After struct template
```
    struct struct_name variable1, variable2,...;
```

#####Access Structure Members
We can access structure members by using the ( . ) dot operator.
>variable1.member1;

#####Initialize Structure Members
Structure members cannot be initialized with the declaration.
The reason for the above error is simple. When a datatype is declared, no memory is allocated for it. Memory is allocated only when variables are created.
We can initialize structure members in 3 ways which are as follows:
1.	Using Assignment Operator.
```
    struct struct_name str;
    str.member1 = 10;
    str.member2 = 20;
    str.member3 = 30;
    .
    .
```
2.	Using Initializer List.
```
      struct struct_name str = {10,20,30};
```
3.	Using Designated Initializer List.
```
    struct struct_name str = {.member1 = 10, .member2 = 20, .member3 = 30};
```

#####Typedef for Structures
We can use the typedef to define some new shorter name for the structure.
```

typedef struct{
  datatype member1;
  datatype member2;
} struct name;
```

#####Nested Structures
Embedded Structure Nesting
```
    struct struct_name{
      int member1;
      struct str member2{
        int str_member1;
        char str_member2;
        ...
      };
      ...
    }
```
Separate Structure Nesting
```
    struct struct_name1{
      int str_member1;
      char str_member2;
      ...
    };

    struct struct_name2{
      double member1;
      struct struct_name1 member2;
      ...
    };
```
Accessing Nested Members
```
  struct_name2.struct_name1.str_member1;
```

#####Structure Pointer in C
We can define a pointer that points to the structure like any other variable. Such pointers are generally called Structure Pointers. We can access the members of the structure pointed by the structure pointer using the ( -> ) arrow operator.
```
      / C program to illustrate the structure pointer 
      #include <stdio.h> 
  
      // structure declaration 
      struct Point { 
          int x, y; 
      }; 
        
      int main() 
      { 
          struct Point str = { 1, 2 }; 
        
          // p2 is a pointer to structure p1 
          struct Point* ptr = &str; 
        
          // Accessing structure members using structure pointer 
          printf("%d %d", ptr->x, ptr->y); 
        
          return 0; 
      }
```

#####Self-Referential Structures
The self-referential structures in C are those structures that contain references to the same type as themselves i.e. they contain a member of the type pointer pointing to the same structure type.
```
    // C program to illustrate the self referential structures 
    #include <stdio.h> 

    // structure template 
    typedef struct str { 
      int mem1; 
      int mem2; 
      struct str* next; 
    }str; 

    // driver code 
    int main() 
    { 
      str var1 = { 1, 2, NULL }; 
      str var2 = { 10, 20, NULL }; 

      // assigning the address of var2 to var1.next 
      var1.next = &var2; 

      // pointer to var1 
      str *ptr1 = &var1; 

      // accessing var2 members using var1 
      printf("var2.mem1: %d\nvar2.mem2: %d", ptr1->next->mem1, 
        ptr1->next->mem2); 

      return 0; 
    }
```

#####C Structure Padding and Packing
Structure padding is the concept of adding multiple empty bytes in the structure to naturally align the data members in the memory. It is done to minimize the CPU read cycles to retrieve different data members in the structure.
There are some situations where we need to pack the structure tightly by removing the empty bytes. In such cases, we use Structure Packing. C language provides two ways for structure packing:
1.	Using #pragma pack(1)
2.	Using __attribute((packed))__
```
    // C program to illustrate structure padding and packing 
    #include <stdio.h> 

    // structure with padding 
    struct str1 { 
      char c; 
      int i; 
    }; 

    struct str2 { 
      char c; 
      int i; 
    } __attribute((packed)) __; // using structure packing 

    // driver code 
    int main() 
    { 
      printf("Size of str1: %d\n", sizeof(struct str1)); 
      printf("Size of str2: %d\n", sizeof(struct str2)); 
      return 0; 
    }
```

Output
>Size of str1: 8
>Size of str1: 5

#####Bit Fields
Bit Fields are used to specify the length of the structure members in bits. When we know the maximum length of the member, we can use bit fields to specify the size and reduce memory consumption.

Syntax
```
      struct structure_name {
        data_type member_name: width_of_bit-field;
      };
```

```
    // C Program to illustrate bit fields in structures 
    #include <stdio.h> 

    // declaring structure for reference 
    struct str1 { 
      int a; 
      char c; 
    }; 

    // structure with bit fields 
    struct str2 { 
      int a : 24; // size of 'a' is 3 bytes = 24 bits 
      char c; 
    }; 

    // driver code 
    int main() 
    { 
      printf("Size of Str1: %d\nSize of Str2: %d", 
        sizeof(struct str1), sizeof(struct str2)); 
      return 0; 
    }
```

Ouput
>Size of Str1: 8
Size of Str2: 4

#####Uses of Structure in C
C structures are used for the following:
1.	The structure can be used to define the custom data types that can be used to create some complex data types such as dates, time, complex numbers, etc. which are not present in the language.
2.	It can also be used in data organization where a large amount of data can be stored in different fields.
3.	Structures are used to create data structures such as trees, linked lists, etc.
4.	They can also be used for returning multiple values from a function

#####Limitations of C Structures
In C language, structures provide a method for packing together data of different types. A Structure is a helpful tool to handle a group of logically related data items. However, C structures also have some limitations.

Higher Memory Consumption: It is due to structure padding.
No Data Hiding: C Structures do not permit data hiding. Structure members can be accessed by any function, anywhere in the scope of the structure.
Functions inside Structure: C structures do not permit functions inside the structure so we cannot provide the associated functions.
Static Members: C Structure cannot have static members inside its body.
Construction creation in Structure: Structures in C cannot have a constructor inside Structures.
</details>