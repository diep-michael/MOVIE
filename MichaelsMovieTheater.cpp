#include "MichaelsMovieTheater.h"

const int g_kArraySize = 8;				// number of movies that will be available at our theater

int main ()
{
	Movie movie_objects[g_kArraySize];

	MovieTicketMaster * p_MovieTicketMaster = new MovieTicketMaster ("AMC15","SAN JOSE, CA");
	p_MovieTicketMaster->Init(movie_objects, g_kArraySize);
	p_MovieTicketMaster->Run();

	delete p_MovieTicketMaster;
	return 0;
}

//default constructor setting pointer to NULL

MovieTicketMaster::MovieTicketMaster()
{
	p_MovieList =NULL;
}

//non-default constructor getting parameters for 
//theater name and location and still initializing the pointer

MovieTicketMaster::MovieTicketMaster(string my_theater_name, string my_theater_location)
{
	theater_name = my_theater_name;
	theater_location = my_theater_location;
	p_MovieList = NULL;
}

// public destructor
MovieTicketMaster::~MovieTicketMaster()
{
	cout << "Theater " << theater_name << ",Location " << theater_location 
		<< " has been closed.." << endl;
}

// Init is filling the array of movie objects

void MovieTicketMaster::Init(Movie * p_my_MovieList, int array_size)
{
	string movie_titles[g_kArraySize] = {"Avengers",
		"Black Panther",
		"Isle of Dogs",
		"Zootopia",
		"Limitless",
		"Love After Love",
		"Miracles from Heaven",
		"The Divergent Series: Allegiant"};

	int theater_tickets[g_kArraySize] = {100,75,90,90,75,115,120,130};

	double movie_price[g_kArraySize] = {11.5,11.5,11.5,11.5,11.5,13.5,13.5,15.0};

	Movie * p = p_my_MovieList;

	for(int i=0;i <= g_kArraySize - 1;i++){
		p->set_movie_name(movie_titles[i]);
		p->set_tickets_available(theater_tickets[i]);
		p->set_ticket_price(movie_price[i]);
		p++;
	}

	p_MovieList = p_my_MovieList;

}

// this member is running a do while loop to ask for user selection

void MovieTicketMaster::Run()
{
	int option;

	do{

		DisplayMenu();

		cout << endl << "Please select an option: " << endl;

		cin >> option;

		switch (option)
		{

		case 1:
			ViewMovies();
			break;

		case 2:

			SearchMovie();
			break;

		case 3:

			PurchaseTicket();
			break;

		case 4:
			
			cout <<"Exiting Menu" << endl;
			break;
			
		default:

			cout <<"Please choose a valid option:" << endl
				<< "=============================" << endl;
			cin.ignore();

		}
	}
	while (option != 4);
}

// this member has menu with banner, stating the name and location while showing options

void MovieTicketMaster::DisplayMenu()
{
	cout << "MOVIE TICKET MASTER" << endl << endl
		<<"Theater: " << theater_name << " at " << theater_location << endl
		<< endl <<"  ***********************  " << endl
		<<"||                       ||" << endl
		<<"||     WELCOME   TO      ||" << endl
		<<"||         AMC 15        ||" << endl
		<<"||                       ||" << endl
		<<"  ***********************  " << endl << endl
		<<"Welcome to AMC 15!" << endl
		<<"==================" << endl
		<<"Please select an option: " << endl
		<<"1. View all movies" << endl
		<<"2. Search a movie" << endl
		<<"3. Purchase a ticket" << endl
		<<"4. Quit" << endl;
	
}

// this member uses a for loop to show movie objects (title,tickets available, price)

void MovieTicketMaster::ViewMovies()
{

	Movie * p_view_movies = p_MovieList;

	cout << endl
		<<"Here are the movies that are showing " << endl
		<<"at AMC 15:" << endl
		<<"=========================" << endl << endl;

	for (int i = 0; i < g_kArraySize; i++){
		cout << "Movie showing at theater "  << i + 1  << ": " << endl;
		p_view_movies->Display();
		++p_view_movies;
	}
}

// this member asks the user to enter a movie name, then uses FindMovie to
// get a pointer, then displays the object

Movie * MovieTicketMaster::SearchMovie()
{
	string search_movie_name;
	
	cout << "Please enter a movie name: " << endl;
	cin.sync();
	std::getline(std::cin, search_movie_name);

	Movie * p = FindMovie(search_movie_name);

	if (p != NULL){
		p->Display();
	} 
	else {
		cout << endl << "Error: Movie not found." << endl << endl;
		return NULL;
	}
	return p;
}

// this member uses a for loop to search through the objects' names
// then uses an if loop to match them up and return a pointer back to the object

Movie * MovieTicketMaster::FindMovie(string find_movie_name)
{

	Movie * p_find_movie = p_MovieList;

	for (int i = 0; i < g_kArraySize; i++){
		if (p_find_movie->get_movie_name() == find_movie_name){
			cout << endl << "Movie found" << endl;
			return p_find_movie;
		}
		else {
			p_find_movie++;
		}
	}
	return NULL;
}

// this member allows the user to purchase a certain amount of tickets
// by using the returned pointer from the FindMovie member

void MovieTicketMaster::PurchaseTicket()
{
	string purchase_movie_name;

	int total_tickets;

	cout << "Please enter a movie name: " << endl;
	cin.sync();
	std::getline(std::cin, purchase_movie_name);

	cout << "Please enter the total amount of tickets you wish to purchase: " << endl;
	cin >> total_tickets;

	Movie * p = FindMovie(purchase_movie_name);

		if (p != NULL){
		double total_cost =	p-> PurchaseTicket(total_tickets); 
				if ( total_cost == -1){
					cout << "This movie has been sold out or there are" << endl
						<< "not enough tickets available per your request" << endl << endl;
				} 
				else {
					cout << "Your total comes out to: " << total_cost << endl;
				}
		} 
		else {
			cout << "No movie has been found" << endl;
		}
		
}


Movie::Movie()
{
	movie_name = "";
	tickets_available = 0;
	ticket_price = 0.0;
}


Movie::Movie(string my_movie_name, int my_tickets_available, double my_ticket_price)
{
	movie_name = my_movie_name;
	tickets_available = my_tickets_available;
	ticket_price = my_ticket_price;
}


Movie::~Movie()
{
	cout << movie_name << " is no longer showing.." << endl;
}


string Movie::get_movie_name()
{
	return movie_name;
}


int Movie::get_tickets_available()
{
	return tickets_available;
}


double Movie::get_ticket_price()
{
	return ticket_price;
}


void Movie::set_movie_name(string new_movie_name)
{
	movie_name = new_movie_name;
}


void Movie::set_tickets_available(int new_tickets_available)
{
	tickets_available = new_tickets_available;
}


void Movie::set_ticket_price(double new_ticket_price)
{
	ticket_price = new_ticket_price;
}

// this member uses the users wanted tickets to calculate their total

double Movie::PurchaseTicket(int purchase_tickets_available)
{
	double total_price;

	if (purchase_tickets_available <= tickets_available) {
		total_price = purchase_tickets_available * ticket_price;
		tickets_available = tickets_available - purchase_tickets_available;
		return total_price;
	} else {
		return -1;
	}
}

// this member displays all three aspects of the movie object

void Movie::Display()
{
		cout.setf(ios::fixed, ios::floatfield); 
		cout.setf(ios::showpoint); 
		cout.precision(2);
		cout << endl << "Movie name: " << movie_name << endl
			<<"Tickets available: " << tickets_available << endl
			<<"Price per ticket: " << ticket_price << endl << endl;
}
