#include<stdio.h>
#include<stdint.h>

// Khởi tạo giỏ hàng
uint8_t GIO_HANG;

//khởi tạo enum
typedef enum SAN_PHAM{
    AO          = 1<<0,
    QUAN        = 1<<1,
    VAY         = 1<<2,
    DAM         = 1<<3,
    NHAN        = 1<<4,
    VONGTAY     = 1<<5,
    GIAY        = 1<<6,
    TUI         = 1<<7,
} SAN_PHAM;

/*
Function: Analysis
Mô tả: chuyển đổi binnary thành 8bit nhị phân,
       mỗi bit sẽ được lưu vào thành một phần
       tử của mảng array[8]
Input: mã nhị phân của sản phẩm/giỏ hàng
Output: mảng[8] chứa mã nhị phân của sản phẩm/giỏ hàng
*/
void Analysis (uint8_t binnary, uint8_t* array){
    uint8_t i = 0;
    while (binnary > 0)
    {
        *(array + i) = binnary%2;
        i++;
        binnary /= 2;
    }
}

/*
Function: Product_name
Mô tả: trả về tên sản phẩm phù hợp với index
Input: chỉ số index
Output: tên sản phẩm
*/
char* Product_name(uint8_t index){
    switch (index)
    {
    case 0:
        return "AO";
        break;

    case 1:
        return "QUAN";
        break;

    case 2:
        return "VAY";
        break;

    case 3:
        return "DAM";
        break;

    case 4:
        return "NHAN";
        break;

    case 5:
        return "VONGTAY";
        break;

    case 6:
        return "GIAY";
        break;

    case 7:
        return "TUI";
        break;
    
    default:
        break;
    }
}

/*
Function: Ađd
Mô tả: Thêm sản phẩm vào giỏ hàng bằng cách
       Or mã nhị phân được lưu bởi GIO_HANG
       với mã nhị phân lưu bởi San_pham_add
Input: mã nhị phân của giỏ hàng và sản phẩm
*/
void Add(uint8_t* GIO_HANG, uint8_t San_pham_add){
    *GIO_HANG |= San_pham_add;
}


/*
Function: Remove
Mô tả: Xóa sản phẩm khỏi giỏ hàng bằng cách
       And mã nhị phân được lưu bởi GIO_HANG
       với mã nhị phân lưu đảo bởi San_pham_add
Input: mã nhị phân của giỏ hàng và sản phẩm
*/
void Remove(uint8_t* GIO_HANG, uint8_t San_pham_remove){
    *GIO_HANG &= ~ San_pham_remove;
}


/*
Function: check
Mô tả: Kiểm tra những sản phẩm được chọn có trong giỏ hàng hay không,
       bằng cách tạo các mảng lưu mã nhị phân của giỏ hàng và sản phẩm
       sau đó so sánh phần tử của mảng sản phẩm với 1 rồi so sánh phần
       tử của mảng giỏ hàng với 1, nếu cả hai bằng 1 thì xuất ra sản phẩm
Input: mã nhị phân của sản phẩm và giỏ hàng
Output: trạng thái của sản phẩm trong giỏ hàng
*/
    char check_gio_hang[8];
void Check(uint8_t GIO_HANG, uint8_t San_pham_check){
    char check_san_pham[8];
    Analysis(GIO_HANG, check_gio_hang);
    Analysis(San_pham_check, check_san_pham);
    printf("---------------------\n");
    printf("Kiem tra gio hang:\n");
    uint8_t so_luong_do = 0;
    for (uint8_t i = 0; i < 8; i++){
        if (check_san_pham[i] == 1 ){
                if(check_gio_hang[i] == 1){
                    printf("Co %s\n", Product_name(i));
                }else{
                    printf("Chua co %s\n", Product_name(i));
                }
        }
    }
}


/*
Function: check
Mô tả: in tất cả sản phẩm trong giỏ hàng
Input: mã nhị phân của sản phẩm và giỏ hàng
Output: cá sản phẩm trong giỏ hàng
*/
void Print(uint8_t GIO_HANG){
    if (GIO_HANG == 0) printf("Gio hang rong!\n");

    char gio_hang[8];
    uint8_t index = 0;
    Analysis(GIO_HANG, gio_hang);
    printf("---------------------\n");
    printf("Gio hang bao gom:\nIndex  Product\n");
    for (uint8_t i = 0; i < 8; i++)
    {
        if (gio_hang[i] == 1){
            printf("  %d    %s\n", ++index, Product_name(i));
        }
    }
    

}

int main()
{
    Add(&GIO_HANG,NHAN|AO|GIAY|TUI);
    Print(GIO_HANG);
    Check(GIO_HANG, NHAN|AO|VONGTAY);
    Remove(&GIO_HANG,AO);
    Print(GIO_HANG);
    Check(GIO_HANG, AO|GIAY|DAM); 
    return 0;
}