#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
using namespace std;

int frame_size;
int page_seq[20];

void get_page_frame_size();
int repeat_place(int frames[], int number);
int earliest_place(int frames[], int number[]);
int last_use(int frames[], int pos);
void print_frame(int frames[]);

void fifo();
void lru();
void optimal();

int main(){
    srand(time(NULL));
    int min = 0;
    int max = 9;
    int pf_fifo = 0;
    int pf_lru = 0;
    int pf_optimal = 0;

    get_page_frame_size();

    // generate random page-reference string
    for(int i = 0; i<20; i++){
        page_seq[i] = rand() % (max - min + 1) + min;
    }
    cout<<"Random page-reference string: "<<endl;
    for(int i = 0; i < 20; i++){
        cout << page_seq[i] << " ";
    }
    cout<<endl;

    fifo();
    lru();
    optimal();

    return 0;
}

void get_page_frame_size(){
    int size;
    while(size < 1 || size > 7){
        cout<<"Enter the size of frame (1~7): ";
        cin>>size;
    }
    frame_size = size;
}

int last_use(int frame[], int pos){
    int result = 0, index = 0;

    for(int i = 0; i < frame_size; i++){
        int n = 20;
        for(int j = pos + 1; j < 20; j++){
            if(frame[i] == page_seq[j]){
                n = j;
                break;
            }
        }
        if(n > index){
            index = n;
            result = i;
        }
    }

    return result;
}

int repeat_place(int frame[], int number){
    int result = -1;

    for(int i = 0; i < frame_size; i++){
        if(number == frame[i])
            result = i;
    }

    return result;
}

int earliestPlace(int frame[], int number[]){
    int result, compare = 20;

    for(int i = 0; i < frame_size; i++){
        if(compare > number[frame[i]]){
            compare = number[frame[i]];
            result = i;
        }
    }
    
    return result;
}

void print_frame(int frame[]){
    std::cout << "frame: ";
    for(int i = 0; i < frame_size; i++)
        std::cout << " " << frame[i];
    std::cout << std::endl;
}

void fifo(){
    int pageFault = 0, pointer = 0, j = 0;
    int frame[frame_size];

    std::fill_n(frame, frame_size, -1);

    for(int i = 0; i < 20; i++){
        if(repeat_place(frame, page_seq[i]) != -1)
            continue;
        if(j < frame_size){
            frame[i] = page_seq[i];
            j++;
        }else{
            frame[pointer] = page_seq[i];
            pointer = (pointer + 1) % frame_size;
        }
        pageFault++;
        print_frame(frame);
    }

    cout << "The number of page faults incurred by the FIFO page-replacement algorithm: " << pageFault << endl;
}

void lru(){
    int pageFault = 0, j = 0;
    int frame[frame_size];
    int number[10];

    std::fill_n(frame, frame_size, -1);
    std::fill_n(number, 10, -1);

    for(int i = 0; i < 20; i++){
        if(repeat_place(frame, page_seq[i]) != -1){
            number[page_seq[i]] = i;
            continue;
        }
        number[page_seq[i]] = i;
        if(j < frame_size){
            frame[i] = page_seq[i];
            j++;
        }else{
            int place = earliest_place(frame, number);
            frame[place] = page_seq[i];
        }
        pageFault++;
        print_frame(frame);
    }

    cout << "The number of page faults incurred by the LRU page-replacement algorithm: " << pageFault << endl;
}

void optimal(){
    int pageFault = 0, j = 0;
    int frame[frame_size];   

    std::fill_n(frame, frame_size, -1);

    for(int i = 0; i < 20; i++){
        if(repeat_place(frame, page_seq[i]) != -1){
            continue;
        }       
        if(j < frame_size){
            frame[i] = page_seq[i];
            j++;
        }else{
            int place = last_use(frame, i);
            frame[place] = page_seq[i];
        }
        pageFault++;
        print_frame(frame);
    }

    cout << "The number of page faults incurred by the optimal page-replacement algorithm: " << pageFault << endl;
}