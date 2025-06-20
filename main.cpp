#include "Graphs.cpp"
#include <SFML/Audio.hpp>


int main() {
    Graph graph(12);

    graph.set_city_name(0, "Islamabad");
    graph.set_city_name(1, "Newyork");
    graph.set_city_name(2, "Paris");
    graph.set_city_name(3, "Tokyo");
    graph.set_city_name(4, "London");
    graph.set_city_name(5, "Amsterdam");
    graph.set_city_name(6, "Singapore");
    graph.set_city_name(7, "Sydney");
    graph.set_city_name(8, "Berlin");
    graph.set_city_name(9, "Seoul");
    graph.set_city_name(10, "HongKong");

    fstream file;
    file.open("Flights.txt", ios::in);

    if (!file) {
        cout << "Error in opening file." << endl;
        return 0;
    }

    string origin, destination, date, dep_time, arr_time, airline;
    string price;

    while (file >> origin >> destination >> date >> dep_time >> arr_time >> price >> airline) {
        int o = checkplace(origin);
        int d = checkplace(destination);
        int p = stoi(price);
        if (o != -1 && d != -1) {
            flightdata f1(dep_time, arr_time, p, airline, date);
            graph.add_flight(o, d, f1);
        }
    }

    file.close();


    visual v1;
    int choice=0;
    int ch1=0;
    const int MAX_EDGES = 12;  // Maximum number of edges in the path
    int path[MAX_EDGES][2];   // Array to store the path edges
    int path_size = 0;        // Number of edges in the path
    int path2[MAX_EDGES][2];   // Array to store the path edges
    int path_size2 = 0; 
    int arr1[3][4];
    int arr2[2][2];
    int arr3[12][2];
    int size=0;
    int size2=0;
    int count2=0;
    
    		
    	sf::RenderWindow window(sf::VideoMode(1024, 491), "City Map");
    	while (window.isOpen()) {
        	sf::Event event;
        	while (window.pollEvent(event)) {
        	    if (event.type == sf::Event::Closed)
        	        window.close();
        	}
        	
	
        	window.clear();
        	if(count2==0){
        	    v1.drawintro(window);
        	    window.display();
        	    sf::SoundBuffer buffer;
        	    if (!buffer.loadFromFile("intro.mp3")) {
        		std::cerr << "Error: Could not load audio file!" << std::endl;
        		return -1;
    		    }
    		    sf::Sound sound;
    		    sound.setBuffer(buffer);
    		    sound.play();
    		    while (sound.getStatus() == sf::Sound::Playing) {
       		    	//sf::sleep(sf::milliseconds(100));
     		    }
        	    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        	    count2++;
        	}
        	v1.drawBackground(window);
        	v1.drawCities(window);
        	if(choice==1)
        	{
               	//Complete visualization for direct flights
              	 if (size2 > 0) {
            for (int i = 0; i < size2; i++) {
                v1.drawArrows(window, arr2[i][0], arr2[i][1]);
            }
        }
               }
               else if(choice==2){
                //Complete visualization for indirect flights
             for (int i = 0; i < size2; i++) {
       		 v1.drawArrows(window, arr2[i][0], arr2[i][1]);
   			 }
        }

            	 
        	// Draw the shortest path if calculated
        	else if(choice==3){
        	for (int i = 0; i < path_size; i++) {
        	       v1.drawArrows(window, path[i][0], path[i][1]);
        	 }}
        	 else if(choice==7){
        	for (int i = 0; i < path_size; i++) {
        	       v1.drawArrows(window, path[i][0], path[i][1]);
        	 }}
        	 
        	 
                else if(choice==4)
            	{
            	for (int i = 0; i < size2; i++) {
       		 v1.drawArrows(window, arr2[i][0], arr2[i][1]);
   			 }
            	}
        	 
        	 else if(choice==5){
        	 	for(int i=0;i<size;i++){
        	 	    if(i!=size-1)
        	 	        v1.drawdash(window,arr1[i][1]);
        	 	    v1.drawArrows(window,arr1[i][0],arr1[i][1]);
        	 	}
        	 }
        	 else if(choice==6){
                  for (int i = 0; i < size2; i++) {
        		v1.drawArrows(window, arr1[i][0], arr1[i][1]);
    			}

             }
             else if(choice==8){
             	 v1.drawoutro(window);
        	    window.display();
        	    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        	    break;
             }
        	  
        	window.display();
        	
        	
                do{
                    cout<<"\033[34mEnter 1 to book direct flights,"<<endl;
    		    cout<<"\033[31m2 to book indirect flights,"<<endl;
    		    cout<<"\033[32m3 to see lowest cost flights from your city to destination city,"<<endl;
       		    cout<<"\033[35m4 to make custom flight"<<endl;
    		    cout<<"\033[36m5 to book flights with layover,"<<endl;
    		    cout<<"\033[34m6 to build multi-legged trip,"<<endl;
    		    cout<<"\033[37m7 to see shortest distance flights from your city to destination city: "<<endl;
    		    cin>>choice;
    		    
    		    if(choice==1){
    		    	int flightDetails[2];
        		bookdirectflight(graph, flightDetails);
        		size2=0;
       			 if (flightDetails[0] != -1 && flightDetails[1] != -1) {
            			arr2[0][0] = flightDetails[0];
            			arr2[0][1] = flightDetails[1];
            			size2 = 1;
    		  	  }
    		  	cout<<"Enter1 to Display"<<endl;
        		cin>>ch1;
    		    }
    		    
    		    else if(choice==2){
    		    	 int flightPaths[2][2];
      			  int pathCount = 0;
      			  size=0;
      			  string source;
      			  string destination;
      			  cout<<"Enter source city"<<endl;
      			  cin>>source;
      			  cout<<"Enter destination city"<<endl;
      			  cin>>destination;
      			  
      			  bookindirectflight(graph, source, destination, flightPaths, pathCount);
     			   size2 = 0;
     			   for (int i = 0; i < pathCount; i++) {
     			       arr2[size2][0] = flightPaths[i][0];
     			       arr2[size2][1] = flightPaths[i][1];
     			       size2++;
      			  }
      			cout<<"Enter1 to Display"<<endl;
        		cin>>ch1;
    		    	
    		    }
    		    
    		    else if(choice==3){ 
    			string source2;
    			path_size=0;
    		    	string destination2;
    		    	cout<<"Enter source city to fly from: ";
    		    	cin>>source2;
    		    	cout<<"Enter destination city to fly from: ";
    		    	cin>>destination2;
    			int count1=0;
    			
    			
	
        	// Call dijkstra only once and store the path
        	    if (path_size == 0) {
        	        graph.dijkstra(checkplace(source2), checkplace(destination2), path, path_size);
        	    }
        	    
        	    
        	    cout<<"Enter1 to Display"<<endl;
        	    cin>>ch1;
        	}
        	else if (choice == 4) {
   			 // Custom Flights
   			 int flightPaths[3][2];
   			 int pathCount = 0;
   			 customflightsearch(graph, flightPaths, pathCount);
			size2=0;
    			size = 0; // Reset the visualization array
    			for (int i = 0; i < pathCount; i++) {
        			arr2[size2][0] = flightPaths[i][0];
        			arr2[size2][1] = flightPaths[i][1];
        			size2++;
    				}
			} 
			
        	else if(choice==5){
        		Queue q1;
    			bool x=0; 
    			size=0;
    			int count1=0;
    			string source;
    			cout<<"Enter the source city: ";
    			cin>>source;
    			string destination1;
    			cout<<"Enter the destination city: ";
    			cin>>destination1;
    			int f;
    			graph.display_flights_specifictrip(checkplace(source),checkplace(destination1));
    			cout<<"Enter flight you want to select: ";
    			cin>>f; 
    			Node *n1=graph.display_flights_specifictrip(checkplace(source),checkplace(destination1),f);
    			arr1[0][0]=checkplace(source);
    			arr1[0][1]=checkplace(destination1);
    			size++;
    			float time;
    			cout<<"Enter the time of layover (in hours) of "<<destination1<<" :";
    			cin>>time;
    			string destination2;
    			cout<<"Enter the second destination city: ";
    			cin >> destination2;
    			arr1[1][0]=checkplace(destination1);
    			arr1[1][1]=checkplace(destination2);
    			size++;
    			count1++;
    			cout<<"Enter 1 to add another layover or 0 to end: ";
    			cin>>x;
    			if(x==1){
    			    q1.enqueue(checkplace(destination1),time);
    			    cout<<"Enter the time of layover (in hours) of "<<destination2<<" :";
    			    cin>>time;
    			    count1++;
    			    q1.enqueue(checkplace(destination2),time);
    			    destination1=destination2;
    			    cout<<"Enter the third destination city: ";
    			    cin >> destination2;
    			    q1.enqueue(checkplace(destination2),0);
    			    arr1[2][0]=checkplace(destination1);
    			    arr1[2][1]=checkplace(destination2);
    			    size++;
    			}
    			else{
        			q1.enqueue(checkplace(destination1),time);
        			q1.enqueue(checkplace(destination2),0);
    			}
    		int source1=checkplace(source);
    		for(int i=0;i<count1;i++){
    		cout<<"Hello"<<endl;
        		n1=graph.layovers(q1,*n1);
        		if(n1==NULL)
        		{
        			cout<<"No Flights are available with your layover timings"<<endl;
        			size--;
        		}
       			source1=q1.front->city_index;
    		}
    		cout<<"Enter1 to Display"<<endl;
        	cin>>ch1;
    		
        	
        }
        	else if(choice==6){
        		int flightPaths[12][2]; // Array to store up to 12 legs
    			int pathCount = 0;
			size=0;
			size2=0;
    			multileggedtrip(graph, flightPaths, pathCount);

    			size2 = 0; // Reset the visualization array
    			for (int i = 0; i < pathCount; i++) {
        			arr3[size2][0] = flightPaths[i][0];
        			arr3[size2][1] = flightPaths[i][1];
        			size2++;
    			}
    		cout<<"Enter1 to Display"<<endl;
        	cin>>ch1;
    			
        	}
        	else if(choice==7){
        		path_size = 0;
        		string source2;
    		    	string destination2;
    		    	cout<<"Enter source city to fly from: ";
    		    	cin>>source2;
    		    	cout<<"Enter destination city to fly from: ";
    		    	cin>>destination2;
    		    	if (path_size == 0)
        		graph.dijkstrapath(checkplace(source2),checkplace(destination2),path,path_size,v1);
        		cout<<"Enter1 to Display"<<endl;
        	    	cin>>ch1;
        	}
        	
        	if(ch1==1){
        	break;
        	}
        	}while(choice!=8);
        	}
    	
    

    

    return 0;
}
