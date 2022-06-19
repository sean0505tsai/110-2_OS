#include <iostream>
#include "stdio.h"
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

void fcfs(int pos, vector<int> req){
    int _pos = pos;
    int moved = 0;
    int i = 0;
    while(i < req.size()){
        moved += abs(req.at(i) - _pos);
        _pos = req.at(i);
        i++;
    }
    cout<<"The distance disk head moved (FCFS): "<< moved <<endl;
}

void sstf(int pos, int max, vector<int> req){

    vector<int> requests = req;                 // the request queue
    sort(requests.begin(), requests.end());
    int moved_dis = 0;                          // total moved distance
    int index = 0;
    int _pos = pos;                             // save the current disk head position
    int min = 0;
    int dis = 0;

    while (requests.size() != 0)
    {
        min = max;

        // find closest request
        for(int i = 0; i<requests.size(); i++){
            dis = abs(_pos - requests.at(i));
            if(min > dis){
                min = dis;
                index = i;
            }
        }
        moved_dis += min;
        _pos = requests.at(index);
        requests.erase(requests.begin() + index);
    }
    
    cout<<"The distance disk head moved (SSTF): "<< moved_dis <<endl;

}

void scan(int pos, int max, vector<int> req){

    vector<int> _req = req;
    req.push_back(pos);
    sort(_req.begin(), _req.end());
    int min_req = _req.front();
    int max_req = _req.back();

    int left_moved = pos + max_req;
    int right_moved = (max - pos) + (max - min_req);

    cout<<"The distance disk head moved (SCAN-left): "<<left_moved<<endl;
    cout<<"The distance disk head moved (SCAN-right): "<<right_moved<<endl;
}

void cscan(int pos, int max, vector<int> req){
    
    vector<int> _req = req;
    _req.push_back(pos);
    sort(_req.begin(), _req.end());

    int index = 0;
    while (_req.at(index) != pos)
    {
        index += 1;
    }

    int left_moved = 2*max - abs(pos - _req.at(index + 1));
    int right_moved = 2*max - abs(pos - _req.at(index - 1));

    cout<<"The distance disk head moved (C-SCAN-left): "<<left_moved<<endl;
    cout<<"The distance disk head moved (C-SCAN-right): "<<right_moved<<endl;
}

int main(){
    int max = 0;
    int pos = 0;
    int temp = 0;
    vector<int> req_queue;
    
    cout<<"Enter the maximum of the disk storage: ";
    cin>>max;
    cout<<"Enter the current cylinder: ";
    cin>>pos;
    
    cout<<"Enter the queue of pending requests in FIFO order (enter -1 to stop): "<<endl;
    while (temp != -1)
    {
        scanf("%d", &temp);
        if (temp != -1 && temp >= 0 && temp < max)
            req_queue.push_back(temp);
    }

    cout<<"The request queue: ";
    for(int i = 0; i < req_queue.size(); i++){
        cout<<req_queue.at(i)<<" ";
    }
    cout<<endl;
    cout<<"Current disk head position: "<< pos <<endl;
        
    max-=1;

    fcfs(pos, req_queue);
    sstf(pos, max, req_queue);
    scan(pos, max, req_queue);
    cscan(pos, max, req_queue);
    
    return 0;
}
