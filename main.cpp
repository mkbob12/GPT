#include <fstream>
#include <iostream>
#include <string> 
#include <stdint.h> // uint8_t 타입을 사용하기 위해 추가 
#include <vector>
#include <cstdint> // static_cast
#include <iomanip>
#include <codecvt>        // std::codecvt_utf8

using namespace std;


// ================================== 초기화 ========================================

int i = 0;
int f = 0;
int j = 0; 


bool file(int x){
    ifstream file;
    string filename="gpt_128.dd";
    file.open(filename, ios::binary);
    file.seekg(x, ios::beg);


    uint16_t number;
    uint32_t bit; 
    uint64_t numbers;
    bool type  = true;
    int zero_count = 0;

// ============================== 파일 읽기 선언 =====================================
    while(file.read(reinterpret_cast<char *>(&number), sizeof(number))){
       
        if(i >= 0 & i <8){
            if( i == 0){
                printf("===================================");
                printf("%s","\nPartition Type GUID\n");
                
            }
            printf("%04x ",number);
            if(number == 0){
                zero_count += 1;
            }
        }

// ============================== GUID가 0 이면 break ============================
        if(zero_count == 8){
            return true;

        }



        if(i >= 8 && i < 16){
            if( i ==  8){
                printf("%s","\nUnique Parition GUID\n");
            }
            printf("%04x ",number);
        }

        if(i == 16){
            
            ifstream file1;
            file1.open(filename, ios::binary);
            x = x + 32;
            file1.seekg(x,ios::beg);
            uint64_t number64;
            uint64_t FLBA;
            uint64_t LLBA;
            uint64_t size;
            j = 0;
            string utf8String;

//===================== FLBA LLBA 차이의 사이즈 , real_address ,Decoded UTF - 8 구하기 ===============================
            while(file1.read(reinterpret_cast<char *>(&number64), sizeof(number64))){
                
                if (j == 0){
                    printf("%s","\nFLBA ");
                    printf("%016lx ", number64);
                    FLBA = number64;
                
                };
               
                if( j == 1){
                    printf("%s","\nLLBA ");
                    printf("%016lx\n",number64);
                    LLBA = number64;
                    size = (LLBA - FLBA) * 512;
                    printf("size %ld\n",size);
                    printf("real_address  %ld\n", FLBA * 512);
                    file.seekg(LLBA * 512 + 3 ,ios::beg);
                    file.read(reinterpret_cast<char *>(&number64), sizeof(number64));
                    
                    
                    // Convert the number to a string
                    for (int i = 7; i >=0; --i) {
                        unsigned char byte = (number64 >> (i * 8)) & 0xFF;
                        utf8String.push_back(byte);
                    }

                    string reverseString; 
                    for (int i = utf8String.length() -1; i >=0; i--) {
                        reverseString.push_back(utf8String[i]);
                    }

                    cout << "Decoded UTF-8 : ";
                    cout <<  reverseString << endl;
                    printf("=================================== \n");
                    i = -1; 
                    j = 0; 
                    type = false;
                    file1.close();
                    break;
                };
                j++;
            };
            
        };    
        i++;
        if(type == false){
            return false;
        }
        
    }

            
    file.close();
    return false;
       
}
     
  
int main(){
   int x = 1024;
   bool judge;

   while(1){
        judge = file(x);
        if(judge){
            break;
        }
        x += 128;
   }

 }

