#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class NodeQueue{
    public:
    int city_index;
    int staytime;
    NodeQueue* next;
    int charges;
    NodeQueue(){next=NULL;}
};
class Queue{
    public:
    NodeQueue* front;
    NodeQueue* rear;

    Queue(){
        front = nullptr;
        rear = nullptr;
    }
    void enqueue(int city_index, float staytime){
        NodeQueue* new_node = new NodeQueue();
        new_node->city_index = city_index;
        new_node->staytime = staytime;
        new_node->charges = hotelcharges(city_index);
        new_node->next = nullptr;
        if(front == nullptr){
            front = new_node;
            rear = new_node;
        }
        else{
            rear->next = new_node;
            rear = new_node;
        }
    }
    void dequeue(){
        if (front) {
            NodeQueue* temp = front;
            front = front->next;
            if (!front) {
                rear = nullptr;
            }
            delete temp;
        }
    }

    bool is_empty() const {
        return front == nullptr;
    }

    NodeQueue* Nodef() const {
        return front;
    }

    int hotelcharges(int city_index){
    fstream file1;
    file1.open("HotelCharges_perday.txt", ios::in);
    int finalprice;
    
    if (!file1) {
        cout << "Error in opening file." << endl;
        return 0;
    }

    string place;
    string price;
    
    while (file1 >> place >> price )
    {
        int o=checkplace1(place);
        int p=stoi(price);
        
        if(o==city_index){
            finalprice=p;
        }
        
    }
    file1.close();
    return finalprice;

}

int checkplace1(string name){
    if(name == "Islamabad"){
        return 0;
    }
    else if(name == "Newyork"){
        return 1;
    }
    else if(name == "Paris"){
        return 2;
    }
    else if(name == "Tokyo"){
        return 3;
    }
    else if(name == "London"){
        return 4;
    }
    else if(name == "Amsterdam"){
        return 5;
    }
    else if(name == "Singapore"){
        return 6;
    }
    else if(name == "Sydney"){
        return 7;
    }
    else if(name == "Berlin"){
        return 8;
    }
    else if(name == "Seoul"){
        return 9;
    }
    else if(name == "HongKong"){
        return 10;
    }
    else{
        return -1;
    }
}
};

