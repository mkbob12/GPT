#include <fstream>
#include <iostream>
#include <string> 
#include <stdint.h> // uint8_t 타입을 사용하기 위해 추가 
#include <vector>

using namespace std;


int main(){
    ifstream file;
    string filename="gpt_128.dd";
    file.open(filename, ios::binary);

    /*
        reinterpret_cast는 형변환 연산자로 
    */
    //move the file pointer forward by 400 bytes 

    file.seekg(1024,ios::beg);
    int i = 0;
    int f = 0;
    uint8_t number;


    while(file.read(reinterpret_cast<char*>(&number), sizeof(number))){
        
        
        if(i >= 0 & i <16){
            if( i == 0){
                printf("%s","\nPartition Type GUID\n");
            }
            printf("%02x ",number);
           
        }

        if(i >= 16 && i < 32){
            if( i ==  16){
                printf("%s","\nUnique Parition GUID\n");
            }
            printf("%02x ",number);
        }

        uint8_t hexValues[8];
        if(i >= 32 && i < 40){
            if( i ==  32){
                printf("%s","\nFLBA\n");
            }
            printf("%02x ",number);
            hexValues[i-32] = number;
        }

        if (i == 40){
            for(int j = 0; j < 8; j++){
                printf("%02x ",hexValues[j]);
            }
        }
        

        if ( i == 40 ){
            break;
        }

       
       
        i++;
    }

    file.close();
    return -1;

}