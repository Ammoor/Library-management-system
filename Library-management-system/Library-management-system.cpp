#include <bits/stdc++.h>			// This system from the perspective of the admin.
using namespace std;
struct book_info
{
	short id = 0, total_quantity = 0;
	string name = "";
	short total_quantity_borrowed = 0;
	vector<string>user_names_borrowed_book;
};
struct user_info
{
	string name = "";
	int national_id = 0;
	vector<string>borrowed_books_names;
	vector<short>borrowed_books_ids;
};
vector<book_info>v1;    // Vector that contains the books in the system.
vector<user_info>v2;    // Vector that contains the users in the system.
void add_user(string user_name, int national_id)
{
	v2.push_back({user_name,national_id });
}
short search_book(string book_name)    // Return the position of specific book if exists.		
{
	for (short i = 0;i < v1.size();++i)
	{
		if (v1[i].name == book_name)
		{
			return i;
		}
	}
	return -1;  // The book does not exist in library system.
}
bool check_book_total_quantity(string book_name)  // Check if there available copies of specific book or not. 
{
	if (v1[search_book(book_name)].total_quantity > 0)
	{
		return 1;
	}
	return 0;
}
short search_user(string user_name)    // Return the position of specific user.
{
	for (short i = 0;i < v2.size();++i)
	{
		if (v2[i].name == user_name)
		{
			return i;
		}
	}
}
short search_borrowed_book_name(string user_name, string book_name)  // Return the position of specific book name that borrowed by specific user.
{
	short index_of_the_user = search_user(user_name);
	short size_of_borrowed_books_names = v2[index_of_the_user].borrowed_books_names.size();
	for (short i = 0;i <size_of_borrowed_books_names;++i)
	{
		if (v2[index_of_the_user].borrowed_books_names[i] == book_name)
		{
			return i;
		}
	}
}
short search_borrowed_book_ids(string user_name, string book_name)  // Return the position of specific book id that borrowed by specific user.
{
	short index_of_the_user = search_user(user_name);
	short size_of_borrowed_books_ids = v2[index_of_the_user].borrowed_books_ids.size();
	for (short i = 0;i < size_of_borrowed_books_ids;++i)
	{
		if (v2[index_of_the_user].borrowed_books_ids[i] == v1[search_book(book_name)].id)
		{
			return i;
		}
	}
}
short search_user_borrowed_book(string user_name, string book_name)
{
	short index_of_the_book = search_book(book_name);
	short size_of_users_borrowed_book = v1[index_of_the_book].user_names_borrowed_book.size();
	for (short i = 0;i < size_of_users_borrowed_book;++i)
	{
		if (v1[index_of_the_book].user_names_borrowed_book[i]==user_name)
		{
			return i;
		}
	}
}
void user_borrow_book(string user_name, string book_name)
{
	if (check_book_total_quantity(book_name))
	{
		v2[search_user(user_name)].borrowed_books_names.push_back(book_name); // Push book name to the user.
		v2[search_user(user_name)].borrowed_books_ids.push_back(v1[search_book(book_name)].id); // Push book id to the user.
		v1[search_book(book_name)].user_names_borrowed_book.push_back(user_name);
		--v1[search_book(book_name)].total_quantity;
		++v1[search_book(book_name)].total_quantity_borrowed;
	}
	else
	{
		cout << "There are no copies of this book available now\n";
	}
}
void user_return_book(string user_name, string book_name)
{
	auto it1 = v2[search_user(user_name)].borrowed_books_names.begin();      // Iterator to the begining of the borrowed books names list by the user.
	auto it2 = v2[search_user(user_name)].borrowed_books_ids.begin();	     // Iterator to the begining of the borrowed books ids list by the user.
	auto it3 = v1[search_book(book_name)].user_names_borrowed_book.begin(); // Iterator to the begining of the names of the users borrowed the book.
	v2[search_user(user_name)].borrowed_books_names.erase(it1+search_borrowed_book_name(user_name,book_name));
	v2[search_user(user_name)].borrowed_books_ids.erase(it2 + search_borrowed_book_ids(user_name, book_name));
	v1[search_book(book_name)].user_names_borrowed_book.erase(it3+search_user_borrowed_book(user_name,book_name));
	++v1[search_book(book_name)].total_quantity;
	--v1[search_book(book_name)].total_quantity_borrowed;
}
void add_book(short book_id, string book_name, short book_total_quantity)
{
	v1.push_back({ book_id,book_total_quantity,book_name });
}
void print_result_of_search(vector<string>result_of_search) // This funcition print the result of the search of the neaded book that was created by "find_book" funcition.
{
	if (result_of_search.empty())
	{
		cout << "No books with this name\n";
	}
	else
	{
		for (short i = 0;i < result_of_search.size();++i)
		{
			cout << result_of_search[i] << "\n";
		}
	}
}
void find_book(string book_name)     // Return books that contain the name you looking for.
{
	vector<string>result_of_search; // Vector that returnes the books that contain the name you looking for.
	for (short i = 0;i < v1.size();++i)
	{
		if (v1[i].name.find(book_name)!=string::npos)
		{
			result_of_search.push_back(v1[i].name);
		}
	}
	print_result_of_search(result_of_search);
}
bool sort_library_by_id(book_info x, book_info y)
{
	return x.id < y.id;
}
bool sort_library_by_name(book_info x, book_info y)
{
	return x.name < y.name;
}
void print_library_by_id(vector<book_info>v1)
{
	sort(v1.begin(), v1.end(), sort_library_by_id);
	for (short i = 0;i < v1.size();++i)
	{
		cout << "id = " << v1[i].id << " name = " << v1[i].name << " total quantity = " << v1[i].total_quantity
			<<" total quantity borrowed = "<<v1[i].total_quantity_borrowed<<"\n";
	}
}
void print_library_by_name(vector<book_info>v1)
{
	sort(v1.begin(), v1.end(), sort_library_by_name);
	for (short i = 0;i < v1.size();++i)
	{
		cout << "id = " << v1[i].id << " name = " << v1[i].name << " total quantity = " << v1[i].total_quantity
			<< " total quantity borrowed = " << v1[i].total_quantity_borrowed << "\n";
	}
}
void print_users(vector<user_info>v)
{
	for (short i = 0;i < v.size();++i)
	{
		cout << "user " << v[i].name << " id " << v[i].national_id << " borrowed books ids: ";
		for (short j = 0;j < v[i].borrowed_books_ids.size();++j)
		{
			cout << v[i].borrowed_books_ids[j] << ' ';
		}
		cout << '\n';
	}
}
void print_users_borrowed_book(string book_name) // This fun returns all users who borrowed a specific book.
{
	if (search_book(book_name) != -1)
	{
		for (short i = 0;i < v1[search_book(book_name)].user_names_borrowed_book.size();++i)
		{
			cout << v1[search_book(book_name)].user_names_borrowed_book[i] << "\n";
		}
	}
	else
	{
		cout << "This book name does not exist in the libarary system\n";
	}
}
void Library_System()
{
	short choice = 0;
	cout << "Library Menu:\n1) add_book\n2) search_book\n3) print_who_borrowed_book_by_name\n"
		<< "4) print_library_by_id\n5) print_library_by_name\n6) add_user\n7) user_borrow_book\n"
		<< "8) user_return_book\n9) print_users\n10) Exit\n\n";
	while (1)
	{
		cout << "Enter your menu choice [1-10]: ";
		cin >> choice;
		if (choice == 1)
		{
			short book_id = 0, book_total_quantity = 0;
			string book_name = "";
			cout << "Enter book info: id, name and total quantity: ";
			cin >> book_id >> book_name >> book_total_quantity;
			add_book(book_id, book_name, book_total_quantity);
		}
		else if (choice == 2)
		{
			string book_name = "";
			cout << "Enter book name: ";
			cin >> book_name;
			find_book(book_name);
		}
		else if (choice == 3)
		{
			cout << "\n";
			string book_name="";
			cout << "Enter book name: ";
			cin >> book_name;
			print_users_borrowed_book(book_name);
		}
		else if (choice == 4)
		{
			cout << "\n";
			print_library_by_id(v1);
		}
		else if (choice == 5)
		{
			cout << "\n";
			print_library_by_name(v1);
		}
		else if (choice == 6)
		{
			int user_national_id = 0;
			string user_name = "";
			cout << "Enter user name and national id: ";
			cin >> user_name >> user_national_id;
			add_user(user_name, user_national_id);
		}
		else if (choice == 7)
		{
			string user_name = "", book_name = "";
			cout << "Enter user name and book name: ";
			cin >> user_name >> book_name;
			user_borrow_book(user_name, book_name);
		}
		else if (choice == 8)
		{
			string user_name = "", book_name = "";
			cout << "Enter user name and book name: ";
			cin >> user_name >> book_name;
			user_return_book(user_name, book_name);
		}
		else if (choice == 9)
		{
			print_users(v2);
		}
		else if (choice == 10)
		{
			cout << "Thank you for choosing our library system management services.\n"
				<<"We appreciate your trust in us and hope to see you again soon!\n\n";
			cout << "\033[31mSeek knowledge from the Cradle to the Grave.\n"
				<<"Acquire knowledge and impart it to the people.\n\033[0m";
			// "\033[31m" => sets the statment to color red.
			// "\033[0m"  => reset the rest of the statments to default.
			break;
		}
		cout << '\n';
		cin.clear();
		cin.ignore(10000,'\n');
	}
}
int main()
{
	Library_System();
	return 0;
}
