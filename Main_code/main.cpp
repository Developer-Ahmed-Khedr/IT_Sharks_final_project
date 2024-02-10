#include<iostream>
#include<stdlib.h>
#include<string>
#include<vector>
#include"menus\menu.cpp"
using namespace std;

class Book {
private:
    string title, author, ISBN, publicationyear;
    bool isavailable;
public:
    void set_book(string t, string a, string i, string p, bool is) {
        title = t;
        author = a;
        ISBN = i;
        publicationyear = p;
        isavailable = is;
    }
    string get_title() {
        return title;
    }
    string get_author() {
        return author;
    }
    string get_ISBN() {
        return ISBN;
    }
    string get_publicationyear() {
        return publicationyear;
    }
    void set_isavailable( bool isa){
        isavailable = isa;
    }
};

class Borrowed_book : public Book {
private:
    vector<Book> book;
    int day, month;
public:
    void set_borrowed_book(int da, int mo,Book b) {
        day = da;
        month = mo;
        book.push_back(b);
    }
    vector<Book> get_book() {
        return book;
    }
    int get_day() {
        return day;
    }
    int get_month() {
        return month;
    }

};

class Member : public Borrowed_book {
private:
    string name, contactinfo;
    int age;
    vector<Borrowed_book> borrowed_books;
public:
    void set_member(string n, int a, string contact) {
        name = n;
        age = a;
        contactinfo = contact;
        return;
    }
    string get_name() {
        return name;
    }
    int get_age() {
        return age;
    }
    string get_contactinfo() {
        return contactinfo;
    }
    void add_boorowed_book(Borrowed_book bb){
        Borrowed_book bbob;
        bbob=bb;
        borrowed_books.push_back(bbob);
        return;
    }
    Book remove_boorowed_book(string isbn_to_search_for){
        Book b;
        long long z=borrowed_books.size();
        for (long long y=0 ; y<z ; y++)
        {
            b=borrowed_books.at(y);
            if (b.get_ISBN()==isbn_to_search_for)
            {
                cout<<"The book has been found in the borrowed book section in the member's account:\n";
                cout << "The book " << b.get_title() << " has been found .\n";
                cout << "The author is: " << b.get_author() << " .\n";
                cout << "The ISBN is: " << b.get_ISBN() << " .\n";
                cout << "The publication year is: " << b.get_publicationyear() << " .\n";
                cout << "--------------------------------------------------------------\n\n";
                borrowed_books.erase(borrowed_books.begin()+y);
                return b;
            }
        }
    }
    vector<Borrowed_book> get_borrowed_books() {
        return borrowed_books;
    }
};

class Mo : public Member {
private:
    Menus Mi;
    vector<Book>book;
    vector<Member>member;
    vector<Borrowed_book>borrow_book;
public:

    void bubble_sort_for_books() {
        long long x = book.size();
        bool flage;
        do {
            flage = true;
            for (long long i = 0; i < x - 1; ++i) {
                if (book[i].get_title() > book[i + 1].get_title()) {
                    swap(book[i], book[i + 1]);
                    flage = false;
                }
            }
        } while(!flage);
    }

    void bubble_sort_for_members() {
        long long x = member.size();
        bool flage;
        do {
            flage = true;
            for (long long i = 0; i < x - 1; ++i) {
                if (member[i].get_name() > member[i + 1].get_name()) {
                    swap(member[i], member[i + 1]);
                    flage = false;
            }
            }
        } while(!flage);
    }

    void add_book() {
        string title, author, ISBN, pupl_year;
        cout << "Please enter the title of the book:\n";
        cin >> title;
        cout << "Please enter the author of the book:\n";
        cin >> author;
        cout << "Please enter the ISBN of the book:\n";
        cin >> ISBN;
        cout << "Please enter the publication year of the book:\n";
        cin >> pupl_year;
        Book b;
        b.set_book(title, author, ISBN, pupl_year, true);
        book.push_back(b);
        bubble_sort_for_books();
    }

    void remove_book() {
        if (book.size() == 0)
        {
            cout << "The library has no books.\n";
            return;
        }
        string index;
        long long x = book.size(), i = 0;
        cout << "Please enter the title of the book you want to remove:\n";
        cin >> index;
        while (i <= x)
        {
            if (book.at(i).get_title() == index)
            {
                cout << "The book " << book.at(i).get_title() << " has been found and will be deleted.\n";
                book.erase(book.begin() + i);
                return;
            }
            i++;
        }
        cout << "The book is not in the library.\n";
        return;
    }

    void search_book_return(long long ind) {
        cout << "The book " << book.at(ind).get_title() << " has been found at index " << ind + 1 << " .\n";
        cout << "The author is: " << book.at(ind).get_author() << " .\n";
        cout << "The ISBN is: " << book.at(ind).get_ISBN() << " .\n";
        cout << "The publication year is: " << book.at(ind).get_publicationyear() << " .\n";
        cout << "--------------------------------------------------------------\n\n";
        return;
    }
    
    void search_book_binary() {
        if (book.size() == 0) {
            cout << "The library has no books.\n";
            return;
        }
        string index;
        int opt;
        long long high = book.size();
        long long low = 0;
        Mi.Options_for_searching_books();
        cin >> opt;
        // system("CLS");
        if (opt==1)
        {
            index="title";
        }
        else if (opt==2)
        {
            index="autor";
        }
        else if (opt==3)
        {
            index="ISBN";
        }
        else
        {
            cout<<"Wrong choise:\n";
            return;
        }
        cout << "Please enter the " << index << " of the book you want to search for:\n";
        cin >> index;
        // system("CLS");
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            switch (opt) {
            case 1:
                 if (book.at(mid).get_title() == index) {
                    search_book_return(mid);
                    return;
                }
                else if (book.at(mid).get_title() < index) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
                break;
            case 2:
                if (book.at(mid).get_author() == index) {
                    search_book_return(mid);
                    return;
                } else if (book.at(mid).get_author() < index) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case 3:
                if (book.at(mid).get_ISBN() == index) {
                    search_book_return(mid);
                    return;
                } else if (book.at(mid).get_ISBN() < index) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            default:
                cout << "Wrong choice.\n";
                return;
            }
        }
        cout << "The member is not in the library.\n";
    }

    void add_member() {
        string name, contactinfo;
        int age;
        cout << "Please enter the name of the member:\n";
        cin >> name;
        cout << "Please enter the age of the member:\n";
        cin >> age;
        cout << "Please enter the contact info of the member:\n";
        cin >> contactinfo;
        Member m;
        m.set_member(name, age, contactinfo);
        member.push_back(m);
        bubble_sort_for_members();
    }

    void remove_member() {
        if (book.size() == 0)
        {
            cout << "The library has no books.\n";
            return;
        }
        string index;
        long long x = member.size(), i = 0;
        cout << "Please enter the name of the member you want to remove:\n";
        cin >> index;
        while (i <= x)
        {
            if (member.at(i).get_name() == index)
            {
                cout << "The member " << member.at(i).get_name() << " has been found and wil be deleted.\n";
                member.erase(member.begin() + i);
                return;
            }
            i++;
        }
        cout << "The member is not in the library.\n";
        return;
    }

    void search_member_return(long long ind) {
        cout << "The member " << member.at(ind).get_name() << " has been found at index " << ind + 1 << ".\n";
        cout << "The age is: " << member.at(ind).get_age() << " .\n";
        cout << "The contact info is: " << member.at(ind).get_contactinfo() << " .\n";
        cout << "--------------------------------------------------------------\n\n";
        return;
    }

    void search_member_binary() {
        if (member.size() == 0) {
            cout << "The library has no members.\n";
            return;
        }
        string index;
        int opt;
        long long high = member.size(), low = 0;
        Mi.Options_for_searching_members();
        cin >> opt;
        // system("CLS");
        if (opt==1)
        {
            index="name";
        }
        else if (opt==2)
        {
            index="contact info";
        }
        else
        {
            cout<<"Wrong choise:\n";
            return;
        }
        cout << "Please enter the " << opt << " of the member you want to search for:\n";
        cin >> index;
        while (low <= high) {
            long long mid = low + (high - low) / 2;
            switch (opt) {
            case 1:
                if (member.at(mid).get_name() == index) {
                    search_member_return(mid);
                    return;
                } else if (member.at(mid).get_name() < index) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            case 2:
                if (member.at(mid).get_contactinfo() == index) {
                    search_member_return(mid);
                    return;
                } else if (member.at(mid).get_contactinfo() < index) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                break;
            default:
                cout << "Wrong choice.\n";
                return;
            }
        }
        cout << "The member is not in the library.\n";
    }

    void borrow_a_book() {
        string index, isbn;
        int d, m;
        long long x = member.size(), i = 0,z=book.size(),y=0;
        cout<<"Please enter the name of the member:\n";
        cin >> index;
        while (i <= x)
            {
                if (member.at(i).get_name() == index)
                {
                    cout<<"----------The member is : ----------\n";
                    cout<<"Please enter the day:\n";
                    cin>>d;
                    cout<<"Please enter the month:\n";
                    cin>>m;
                    cout << "Please enter the ISBN of the book you want to borrow:\n";
                    cin >> isbn;
                    while (y<=z)
                    {
                        if (book.at(i).get_ISBN() == isbn)
                        {
                            search_book_return(i);
                            Book b;
                            b=book.at(i);
                            Borrowed_book bbo;
                            bbo.set_borrowed_book(d,m,b);
                            Member me;
                            member.at(i).add_boorowed_book(bbo);
                            book.erase(book.begin()+i);
                            return;
                        }
                        y++;
                    }
                    cout<<"The book wasn't found in the library.\n";
                    return;
                }
                i++;
            }
            cout<<"The member has not been found in the library.\n";
            return;
    }

    void return_a_book() {
        string index, isbn;
        Book b;
        long long x = member.size(), i = 0;
        cout<<"Please enter the name of the member:\n";
        cin >> index;
        while (i <= x)
            {
                if (member.at(i).get_name() == index)
                {
                    cout<<"----------The member is "<<member.at(i).get_name()<<" : ----------\n";
                    if (member.at(i).get_borrowed_books().size()==0)
                    {
                        cout<<"The member has not borrowed any books:\n";
                        return;
                    }
                    cout << "Please enter the ISBN of the book you want to return:\n";
                    cin >> isbn;
                    b=member.at(i).remove_boorowed_book(isbn);
                    book.push_back(b);
                    cout<<"The book has been returned.\n";
                    bubble_sort_for_books();
                }
                i++;
            }
            cout<<"The member has not been found in the library.\n";
            return;
    }

    void display_all_books() {
        if (book.size() == 0)
        {
            cout << "The library has no books.\n";
            return;
        }
        long long x = book.size(), i = 0;
        while (i < x)
        {
            cout << "The " << i + 1 << " book is:\n";
            cout << "The title is " << book.at(i).get_title() << " .\n";
            cout << "The author is " << book.at(i).get_author() << " .\n";
            cout << "The ISBN is " << book.at(i).get_ISBN() << " .\n";
            cout << "The publication year is " << book.at(i).get_publicationyear() << " .\n";
            cout << "--------------------------------------------------------------\n\n";
            i++;
        }
        return;
    }

    void display_all_members() {
        if (member.size() == 0)
        {
            cout << "The library has no members.\n";
            return;
        }
        long long x = member.size(), i = 0;
        while (i < x)
        {
            cout << "The " << i + 1 << " member is:\n";
            cout << "The name is " << member.at(i).get_name() << " .\n";
            cout << "The age is " << member.at(i).get_age() << " .\n";
            cout << "The contact info is " << member.at(i).get_contactinfo() << " .\n";
            cout << "--------------------------------------------------------------\n\n";
            i++;
        }
        return;
    }

};
int main()
{
    Menus M;
    Mo d;
    char Continue;
    int opt, number;
    do {
        M.Options();
        cin >> opt;
        // system("CLS");
        switch (opt)
        {
        case 1:
            M.Options_for_books();
            cin >> opt;
            // system("CLS");
            if (opt == 1)
            {
                M.Options_for_management_of_books();
                cin >> opt;
                // system("CLS");
                if (opt == 1)
                {
                    cout<<"Please enter the number of books to add:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.add_book();
                    }                    
                }
                else if (opt == 2)
                {
                    cout<<"Please enter the number of books to remove:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.remove_book();
                    }
                }
                else
                {
                    // system("CLS");
                    cout << "Wrong choise.\n";
                }
            }
            else if (opt == 2)
            {
                M.Options_for_borrowing_books();
                cin >> opt;
                // system("CLS");
                if (opt == 1)
                {
                    cout<<"Please enter the number of books to borrow:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.borrow_a_book();
                    }
                }
                else if (opt == 2)
                {
                    cout<<"Please enter the number of books to return:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.return_a_book();
                    }
                }
                else
                {
                    cout << "Wrong choise.\n";
                }
            }
            else if (opt == 3)
            {
                cout<<"Please enter the number of books to search for:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.search_book_binary();
                    }
            }
            else if (opt == 4)
            {
                // system("CLS");
                d.display_all_books();
            }
            else
            {
                cout << "Wrong choise.\n";
            }
            break;
        case 2:
            M.Options_for_members();
            cin >> opt;
            // system("CLS");
            if (opt == 1)
            {
                M.Options_for_management_of_members();
                cin >> opt;
                // system("CLS");
                if (opt == 1)
                {
                    cout<<"Please enter the number of members to add:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.add_member();
                    }
                }
                else if (opt == 2)
                {
                    cout<<"Please enter the number of members to remove:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.remove_member();
                    }
                }
                else
                {
                    cout << "Wrong choise.\n";
                }
            }
            else if (opt == 2)
            {
                cout<<"Please enter the number of members to search for:\n";
                    cin>>number;
                    for (int q = 0; q < number; q++)
                    {
                        d.search_member_binary();
                    }
            }
            else if (opt == 3)
            {
                // system("CLS");
                d.display_all_members();
            }
            else
            {
                cout << "Wrong choise.\n";
            }
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Wrong choise.\n";
            break;
        }
        cout << "If you want to continue:\nPlease enter y:\n";
        cin >> Continue;
    } while (Continue == 'Y' || Continue == 'y');
    return 0;
}