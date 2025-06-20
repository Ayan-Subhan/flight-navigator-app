#include <iostream>
#include <string>
#include <fstream>
#include <thread> // Include this for std::this_thread::sleep_for
#include <chrono> // Include this for std::chrono::milliseconds
#include "minheap.cpp"
#include "graphics.cpp"
#include "Queue.cpp"

using namespace std;
class flightdata {
public:
    string departure_time;
    string arrival_time;
    int price;
    string airline_name;
    string date;
	
	    flightdata() : departure_time(""), arrival_time(""), price(0), airline_name(""), date("") {}

    flightdata(string dep_time, string arr_time, int p, string airline, string date)
        : departure_time(dep_time), arrival_time(arr_time), price(p), airline_name(airline), date(date) {}

    float get_duration() {
        auto to_minutes = [](const string& time) {
        int hours = stoi(time.substr(0, 2));  // Extract hours
        int minutes = stoi(time.substr(3, 2));  // Extract minutes
        return hours * 60 + minutes;  // Convert to total minutes
    };

    // Convert departure and arrival times to total minutes
    int dep_minutes = to_minutes(departure_time);
    int arr_minutes = to_minutes(arrival_time);

    // Calculate the difference, considering next-day arrival
    int duration_minutes;
    if (arr_minutes >= dep_minutes) {
        duration_minutes = arr_minutes - dep_minutes;
    } else {
        duration_minutes = (24 * 60 - dep_minutes) + arr_minutes;  // Next day arrival
    }

    // Convert duration to hours as a float
    return duration_minutes / 60.0;
    }
};

class Node {
public:
    int destination; 
    flightdata data;
    Node* next; 

    Node(int dest, flightdata& f1) : destination(dest), data(f1), next(nullptr) {}
};

class linkedlist {
public:
    Node* head; 

    linkedlist() : head(nullptr) {}

    void add_flight(int dest, flightdata& f1) {
        Node* new_node = new Node(dest, f1);
        new_node->next = head;
        head = new_node;
    }

    void display_allflights(const string& city_name, const string* city_names) 
    {
        Node* temp = head;
        cout << "Flights from " << city_name << ":" << endl;
        while (temp) {
            cout << "  To: " << city_names[temp->destination]
                 << ", Departure: " << temp->data.departure_time
                 << ", Arrival: " << temp->data.arrival_time
                 << ", Price: " << temp->data.price
                 << ", Airline: " << temp->data.airline_name
                 << ", Duration: " << temp->data.get_duration() << " hours" << endl;
            temp = temp->next;
        }
    }
    int checkspecifictrip(int source, int destinationn)
    {
        Node* temp = head;
        int count=0;
        while (temp) 
        {
            if(temp->destination==destinationn)
            {
                count++;
            }
            temp = temp->next;
        }
        return count;
    }

    int display_specifictrip(int source, int destinationn)
    {
        Node* temp = head;
        int count=0;
        cout << "Flights from " << source << ":" << endl;
        while (temp) 
        {
            if(temp->destination==destinationn)
            {
            cout << "  Date " << temp->data.date
                 << ", Departure: " << temp->data.departure_time
                 << ", Arrival: " << temp->data.arrival_time
                 << ", Price: " << temp->data.price
                 << ", Airline: " << temp->data.airline_name
                 << ", Duration: " << temp->data.get_duration() << " hours" << endl;
                    count++;
            }
            temp = temp->next;
        }
        return count;
    }
    Node* display_specifictrip(int source, int destinationn,int ch)
    {
        int count=0;
        Node* temp = head;
        auto to_minutes = [](const string& time) {
        int hours = stoi(time.substr(0, 2));  // Extract hours
        int minutes = stoi(time.substr(3, 2));  // Extract minutes
        return hours * 60 + minutes;  // Convert to total minutes
        };
        
        while (temp) 
        {
            if(temp->destination==destinationn)
            {
                count++;
            if(count==ch){
                cout << "  Date " << temp->data.date
                 << ", Departure: " << temp->data.departure_time
                 << ", Arrival: " << temp->data.arrival_time
                 << ", Price: " << temp->data.price
                 << ", Airline: " << temp->data.airline_name
                 << ", Duration: " << temp->data.get_duration() << " hours" << endl;
                return temp;
                break;
            }
            }
            
            temp = temp->next;
        }
        int arrival_min=to_minutes(temp->data.arrival_time);
        return temp;
    }

};

class Graph 
{
    public:

    linkedlist* adjacency_list;  // Array of linked lists
    string* city_names;          // Array of city names
    int vert;                    // Number of vertices (cities)

    Graph(int num_cities) : vert(num_cities) {
        adjacency_list = new linkedlist[vert];
        city_names = new string[vert];
    }

    ~Graph() {
        delete[] adjacency_list;
        delete[] city_names;
    }

    void set_city_name(int city_index, string name) {
        city_names[city_index] = name;
    }

    void add_flight(int origin, int destination, flightdata& f1) {
        adjacency_list[origin].add_flight(destination, f1);
    }

    void display_flights(int city_index) {
        adjacency_list[city_index].display_allflights(city_names[city_index], city_names);
    }

    void display_flights_specifictrip(int source, int destination)
    {
        adjacency_list[source].display_specifictrip(source, destination);
    }

    Node* display_flights_specifictrip(int source, int destination,int ch)
    {
        return adjacency_list[source].display_specifictrip(source, destination,ch);
    }


    Node* layovers(Queue &q1,Node n1){     
        NodeQueue* current_layover;
        current_layover = q1.Nodef();
        int city_index = current_layover->city_index;
        int city_index1 = current_layover->city_index;
        float layover_time = current_layover->staytime;
        int charges = current_layover->charges;
        Node *temp=adjacency_list[city_index].head;
        auto to_minutes = [](const string& time) {
        int hours = stoi(time.substr(0, 2));  // Extract hours
        int minutes = stoi(time.substr(3, 2));  // Extract minutes
        return hours * 60 + minutes;  // Convert to total minutes
        };
        
        auto to_date_int = [](const string& date) {
        int day = stoi(date.substr(0, 2));
        int month = stoi(date.substr(3, 2));
        int year = stoi(date.substr(6, 4));
        return day;// YYYYMMDD format
    	};
    	
    	int arrival_day=to_date_int(n1.data.date);
    	int departure_day=to_date_int(temp->data.date);
        int arrival_min=to_minutes(n1.data.arrival_time);
        int departure_min=to_minutes(temp->data.departure_time);
        cout<<"\nFollowing are the flights available in accordance with your layover time: \n"<<endl;
        while(temp){
            if(temp->destination==q1.front->next->city_index){
                departure_min=to_minutes(temp->data.departure_time);
                departure_day=to_date_int(temp->data.date);
                if(departure_day>=arrival_day&&departure_min>(current_layover->staytime*60)+arrival_min){
                    cout<<"\nFrom "<<city_names[city_index1]<<" to "<<city_names[temp->destination]<<" via airline "
                    <<temp->data.airline_name<<" Date "<<temp->data.date<<" arrival time: "
                    <<temp->data.arrival_time<<" departure time: "<<temp->data.departure_time<<" price: "
                    <<temp->data.price<<" layover price per day: "<<current_layover->charges
                    <<" total charges: "<<(current_layover->charges)+temp->data.price<<endl;

                }
            }
            temp=temp->next;
        }
        int x;
        cout<<"\n\nEnter the flight you want to select: ";
        cin>>x;
        int count=0;
        temp=adjacency_list[city_index].head;
        cout<<"Flight selected: ";
        while(temp){
            if(temp->destination==q1.front->next->city_index){
                    count++;
                    if(count==x){
                    cout<<"\nFrom "<<city_names[city_index1]<<" to "<<city_names[temp->destination]<<" via airline "
                    <<temp->data.airline_name<<" Date "<<temp->data.date<<" arrival time: "
                    <<temp->data.arrival_time<<" departure time: "<<temp->data.departure_time<<" price: "
                    <<temp->data.price<<" layover price per day: "<<current_layover->charges
                    <<" total charges: "<<(current_layover->charges*current_layover->staytime/24)+temp->data.price<<endl;
                    return temp;
                    break;
                }
            }

            temp=temp->next;
        }
        q1.dequeue();
        return temp;
    }


   void dijkstra(int source, int destination, int path[][2], int& path_size) {
    float* min_cost = new float[vert];
    bool* processed = new bool[vert];
    int* previous = new int[vert];

    for (int i = 0; i < vert; i++) {
        min_cost[i] = FLT_MAX;
        processed[i] = false;
        previous[i] = -1;
    }
    min_cost[source] = 0;

    MinHeap pq(vert);
    pq.insert(NodeCost(source, 0));

    while (!pq.empty()) {
        NodeCost current = pq.extract_min();
        int current_city = current.city_index;

        if (processed[current_city]) continue;
        processed[current_city] = true;

        if (current_city == destination) break;

        Node* temp = adjacency_list[current_city].head;
        while (temp) {
            int neighbor = temp->destination;
            float new_cost = min_cost[current_city] + temp->data.price;

            if (new_cost < min_cost[neighbor]) {
                min_cost[neighbor] = new_cost;
                previous[neighbor] = current_city;
                pq.insert(NodeCost(neighbor, new_cost));
            }
            temp = temp->next;
        }
    }

    if (min_cost[destination] != FLT_MAX) {
        path_size = 0;
        int city = destination;

            cout << "Shortest path from " << city_names[source] << " to " << city_names[destination] << " is: " << min_cost[destination] << endl;
            // Reconstruct the path
            cout << "Path: ";
            print_path(destination, previous, city_names, city_names);
        
        while (previous[city] != -1) {
            path[path_size][0] = previous[city];
            path[path_size][1] = city;
            path_size++;
            city = previous[city];
        }
        
        for (int i = 0; i < path_size / 2; i++) {
            std::swap(path[i], path[path_size - 1 - i]);
        }
    } else {
        path_size = 0;  // No path found
        cout << "No path found between " << city_names[source] << " and " << city_names[destination] << endl;
    }

    delete[] min_cost;
    delete[] processed;
    delete[] previous;
}


    void print_path(int city, int* previous, string* city_names, string* city_names_str) {
    if (city == -1) return; 
    print_path(previous[city], previous, city_names, city_names_str);
    int prev_city = previous[city];
    if (prev_city != -1) {
        // Find the flight details between prev_city and city
        Node* temp = adjacency_list[prev_city].head;
        while (temp) {
            if (temp->destination == city) {
                // Print flight details
                cout << "From " << city_names_str[prev_city] << " to " << city_names_str[city] << ": "
                     << "Airline: " << temp->data.airline_name
                     << ", Departure: " << temp->data.departure_time
                     << ", Arrival: " << temp->data.arrival_time
                     << ", Duration: " << temp->data.get_duration() << " hours"
                     << endl;
                     
                break;
            }
            temp = temp->next;
        }
    }

    
    
    }
    void dijkstrapath(int source, int destination, int path[][2], int& path_size, visual v1) {
    float* min_cost = new float[vert];
    bool* processed = new bool[vert];
    int* previous = new int[vert];

    // Initialize the data structures
    for (int i = 0; i < vert; i++) {
        min_cost[i] = FLT_MAX;
        processed[i] = false;
        previous[i] = -1; 
    }

   
    min_cost[source] = 0;

    MinHeap pq(vert);
    pq.insert(NodeCost(source, 0));

    while (!pq.empty()) {
        NodeCost current = pq.extract_min();
        int current_city = current.city_index;

        if (processed[current_city]) continue; 
        processed[current_city] = true;

        if (current_city == destination) break; 

        Node* temp = adjacency_list[current_city].head;
        while (temp) {
            int neighbor = temp->destination;
            float distance = v1.calculatedis(current_city, neighbor);
            float new_cost = min_cost[current_city] + distance;

            if (new_cost < min_cost[neighbor]) {
                min_cost[neighbor] = new_cost;
                previous[neighbor] = current_city;
                pq.insert(NodeCost(neighbor, new_cost));
            }
            temp = temp->next;
        }
    }

    if (min_cost[destination] != FLT_MAX) {
        path_size = 0;
        int city = destination;

        cout << "Shortest path from " << city_names[source] << " to " << city_names[destination] << " is: " << min_cost[destination] << " units" << endl;


        cout << "Path: ";
        print_path(destination, previous, city_names, city_names);

        while (previous[city] != -1) {
            path[path_size][0] = previous[city];
            path[path_size][1] = city;
            path_size++;
            city = previous[city];
        }

        for (int i = 0; i < path_size / 2; i++) {
            swap(path[i], path[path_size - 1 - i]);
        }
    } else {
        path_size = 0;
        cout << "No path found between " << city_names[source] << " and " << city_names[destination] << endl;
    }

    // Clean up
    delete[] min_cost;
    delete[] processed;
    delete[] previous;
}

};
int checkplace(string name){
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


void bookindirectflight(Graph& G1, string source, string destination, int flightPaths[][2], int& pathCount) {
    int s = checkplace(source);
    int d = checkplace(destination);

    if (s == -1 || d == -1) {
        cout << "Invalid source or destination" << endl;
        pathCount = 0;
        return;
    }

    int connectingcities[12];
    int cc = 0;

    for (int st = 0; st < G1.vert; st++) {
        if (st == s || st == d || 
            G1.adjacency_list[s].checkspecifictrip(s, st) == 0 ||
            G1.adjacency_list[st].checkspecifictrip(st, d) == 0) {
            continue;
        }
        connectingcities[cc] = st;
        cc++;
    }

    if (cc == 0) {
        cout << "No connecting cities available" << endl;
        pathCount = 0;
        return;
    }

    cout << "These are the connecting cities available:::" << endl;
    for (int i = 0; i < cc; i++) {
        cout << i + 1 << ". " << G1.city_names[connectingcities[i]] << endl;
    }

    cout << "Enter the number of the city you want to connect through: ";
    int stopcitychosen;
    cin >> stopcitychosen;

    if (stopcitychosen < 1 || stopcitychosen > cc) {
        cout << "Invalid Choice" << endl;
        pathCount = 0;
        return;
    }

    int intermediate = connectingcities[stopcitychosen - 1];
    flightPaths[0][0] = s;
    flightPaths[0][1] = intermediate;
    flightPaths[1][0] = intermediate;
    flightPaths[1][1] = d;
    pathCount = 2;

    cout << "Flights from " << G1.city_names[intermediate] << " to " << G1.city_names[d] << ":" << endl;
    G1.adjacency_list[intermediate].display_specifictrip(intermediate, d);

    cout << "Enter 1 to book one of these flights: ";
    int subchoice;
    cin >> subchoice;
 if (subchoice == 1) {
        cout << "Enter the flight number you want to book: ";
        int flight;
        cin >> flight;

        Node* temp = G1.adjacency_list[intermediate].head;
        int count = 1;
        while (temp && count < flight) {
            temp = temp->next;
            count++;
        }

        if (!temp) {
            cout << "Invalid flight number" << endl;
            pathCount = 0;
            return;
        }

        cout << "Flight Booked" << endl;
        cout << "Flight itinerary:::" << endl;
        cout << "Departure: " << G1.city_names[s] << " Time(GMT+5)::" << temp->data.departure_time << endl;
        cout << "Destination: " << G1.city_names[d] << " Time(GMT+5)::" << temp->data.arrival_time << endl;
        cout << "Airline: " << temp->data.airline_name << endl;
        
    } else {
        cout << "Invalid Choice" << endl;
        pathCount = 0;
    }
}

//Direct Flights
void bookdirectflight(Graph &G1,int* flightDetails) {
    string source, destination;
    cout << "Enter the source city: ";
    cin >> source;
    cout << "Enter the destination city: ";
    cin >> destination;

    int s = checkplace(source);
    int d = checkplace(destination);

    if (s == -1 || d == -1) {
        cout << "Invalid source or destination" << endl;
        flightDetails[0] = -1;
        flightDetails[1] = -1;
        return;
    }

    if (G1.adjacency_list[s].checkspecifictrip(s, d) == 0) {
        cout << "No direct flights available" << endl;
        cout << "You are now being rerouted to check for indirect flights" << endl;
        flightDetails[0] = -1;
        flightDetails[1] = -1;
        return;
    }

    cout << "These are all the direct flights available:::" << endl;
    G1.display_flights_specifictrip(s, d);

    cout << "Enter 1 to book one of these flights: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter the flight number you want to book: ";
        int flight;
        cin >> flight;

        Node* temp = G1.adjacency_list[s].head;
        int count = 1;
        while (temp && count < flight) {
            temp = temp->next;
            count++;
        }

        if (!temp) {
            cout << "Invalid flight number" << endl;
            flightDetails[0] = -1;
            flightDetails[1] = -1;
            return;
        }

        cout << "Flight Booked" << endl;
        cout << "Flight itinerary:::" << endl;
        cout << "Departure: " << source << " Time(GMT+5)::" << temp->data.departure_time << endl;
        cout << "Destination: " << destination << " Time(GMT+5)::" << temp->data.arrival_time << endl;
        cout << "Airline: " << temp->data.airline_name << endl;

        flightDetails[0] = s;
        flightDetails[1] = d;
    } else {
        cout << "Invalid Choice" << endl;
        flightDetails[0] = -1;
        flightDetails[1] = -1;
    }
    

}

//Custom Flights
void customflightsearch(Graph& G1, int flightPaths[][2], int& pathCount) {
    string source, destination, stop, airline;
    cout << "Enter the source city: ";
    cin >> source;
    cout << "Enter the destination city: ";
    cin >> destination;
    cout << "Enter the stop city: ";
    cin >> stop;
    cout << "Enter the airline name: ";
    cin >> airline;

    int s = checkplace(source);
    int d = checkplace(destination);
    int intermediate = checkplace(stop);

    if (s == -1 || d == -1 || intermediate == -1) {
        cout << "Invalid source, stop, or destination city" << endl;
        pathCount = 0;
        return;
    }

    cout << "Checking for flights connecting with " << stop << " on " << airline << " Airways:" << endl;
    pathCount = 0;

    // Check source to stop
    Node* temp = G1.adjacency_list[s].head;
    while (temp) {
        if (temp->destination == intermediate && temp->data.airline_name == airline) {
            flightPaths[pathCount][0] = s;
            flightPaths[pathCount][1] = intermediate;
            pathCount++;
        }
        temp = temp->next;
    }

    // Check stop to destination
    temp = G1.adjacency_list[intermediate].head;
    while (temp) {
        if (temp->destination == d && temp->data.airline_name == airline) {
            flightPaths[pathCount][0] = intermediate;
            flightPaths[pathCount][1] = d;
            pathCount++;
        }
        temp = temp->next;
    }

    if (pathCount == 0) {
        cout << "No custom flights found" << endl;
    } else {
        cout << "Flights Found! They will be visualized on the map." << endl;
    }
}

void multileggedtrip(Graph& G1, int flightPaths[][2], int& pathCount) {   
    string sourcecities[12];       // Array to store source city names
    string destinationcities[12]; // Array to store destination city names
    flightdata flightdeets[12];    // Array to store flight data
    int count = 0;                 // Counter for the number of booked flights

    string source;
    string stopcity;
    cout << "Enter the source city: ";
    cin >> source;
    int s = checkplace(source);
    if (s == -1) {
        cout << "Invalid source city" << endl;
        pathCount = 0;
        return;
    }

    do {
        cout << "You are currently at " << source << endl;
        cout << "Enter your next stop or type 'end' to finish: ";
        cin >> stopcity;

        if (stopcity == "end") {
            cout << "End of trip" << endl;
            break;
        }

        int stop = checkplace(stopcity);
        if (stop == -1) {
            cout << "Invalid stop city" << endl;
            continue;  // Skip invalid input and continue to the next iteration
        }

        // Check if there's a flight available between source and stop
        if (G1.adjacency_list[s].checkspecifictrip(s, stop) == 0) {
            cout << "No flights available from " << source << " to " << stopcity << endl;
            continue;  // Skip to the next iteration if no flights are found
        }

        // Display available flights between source and stop
        cout << "Flights from " << source << " to " << stopcity << ":" << endl;
        G1.adjacency_list[s].display_specifictrip(s, stop);

        // Ask the user to choose a flight
        cout << "Enter the flight number you want to book: ";
        int flight;
        cin >> flight;

        // Find the selected flight and store its data
        Node* temp = G1.adjacency_list[s].head;
        int flight_counter = 1;
        while (temp && flight_counter < flight) {
            temp = temp->next;
            flight_counter++;
        }

        if (!temp) {
            cout << "Invalid flight number" << endl;
            continue;  // Skip if an invalid flight number is provided
        }

        // Store the source and destination city names and flight data
        sourcecities[count] = source;
        destinationcities[count] = G1.city_names[stop];
        flightdeets[count] = temp->data;

        // Add to visualization paths
        flightPaths[count][0] = s;
        flightPaths[count][1] = stop;
        count++;

        // Update the source city for the next leg of the journey
        source = stopcity;
        s = stop;

    } while (true);

    // Display all the booked flights at the end of the journey
    cout << "\nYour Multi-Leg Journey: " << endl;
    for (int i = 0; i < count; i++) {
        cout << "From " << sourcecities[i] 
             << " to " << destinationcities[i]
             << ", Departure: " << flightdeets[i].departure_time
             << ", Arrival: " << flightdeets[i].arrival_time
             << ", Airline: " << flightdeets[i].airline_name
             << ", Price: " << flightdeets[i].price
             << ", Duration: " << flightdeets[i].get_duration() << " hours" << endl;
    }

    pathCount = count; // Update the pathCount to the total number of legs
    return;
}


