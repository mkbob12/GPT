#include <fstream>
#include <iostream>
#include <string> 
#include <stdint.h> // uint8_t 타입을 사용하기 위해 추가 

using namespace std;


int main(){
    string filename = "gpt_128.dd";
    ifstream fin;
    fin.open(filename, ios::binary);
    uint8_t number;

    
    if(!fin) {
        printf("파일을 열 수 없습니다.");
        return 1;
    }

    /*
        reinterpret_cast는 형변환 연산자로 
    */

    uint8_t FLBA[8];
    uint8_t LLBA[8];
    int i = 0;
    int f = 0;
    while(fin.read(reinterpret_cast<char*>(&number), sizeof(number))){
     
        if (i >= 1056 && i < 1056 + 8){
            if (i == 1056){
                printf("First LBA\n");
            }
            FLBA[f] = number;
            //printf("%02x",FLBA[f]);
            printf("%02x ",number);
            f += 1;
        }


        f = 0;
        if (i >= 1056+8 && i < 1056 + 16){
            if (i == 1064){
                printf("\nLast LBA\n");
            }
            LLBA[f] = number;
            printf("%02x ",number);
            f++;
        }
      

        if (i == 1072){
            printf("\n");
            break;
        }

        i++;
    };





    fin.close();
    return -1;

}
