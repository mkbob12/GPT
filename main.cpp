#include <fstream>
#include <iostream>
#include <string> 
#include <stdint.h> // uint8_t 타입을 사용하기 위해 추가 

using namespace std;


int main(){
    ifstream file;
    string filename="gpt_128.dd";
    file.open(filename, ios::binary);

    if (!file.is_open()){
        printf("%s","error opening the file");
    }

    /*
        reinterpret_cast는 형변환 연산자로 
    */
    //move the file pointer forward by 400 bytes 

    file.seekg(1024,ios::beg);

    uint8_t number;
    int i = 0;
    int f = 0;
    while(file.read(reinterpret_cast<char*>(&number), sizeof(number))){
        
        printf("%0x",number);
        if(i == 50){
            break;
        }
        i++;
    }


    file.close();
    return -1;

}
