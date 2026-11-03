#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

// Each Book object stores the details of one book.
class Book
{
private:
    std::string title, author, id;
    int pages;
    bool borrowed;

public:
    Book(std::string t, std::string a, int p, std::string i, bool b)
        : title(t), author(a), id(i), pages(p), borrowed(b) {}

    std::string getId() const { return id; }

    void display() const
    {
        std::cout << "\nID: " << id << "\nTitle: " << title
                  << "\nAuthor: " << author << "\nPages: " << pages
                  << "\nStatus: " << (borrowed ? "Borrowed" : "Available") << '\n';
    }

    void borrowBook()
    {
        if (borrowed)
            std::cout << "This book is already borrowed.\n";
        else
        {
            borrowed = true;
            std::cout << "Book borrowed successfully.\n";
        }
    }

    void returnBook()
    {
        if (!borrowed)
            std::cout << "This book is already available.\n";
        else
        {
            borrowed = false;
            std::cout << "Book returned successfully.\n";
        }
    }
};

// Read comma-separated fields and create Book objects.
std::vector<Book> loadBooks(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Could not open " + filename);

    std::vector<Book> books;
    std::string line;
    while (std::getline(file, line))
    {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        if (line.empty())
            continue;

        std::istringstream row(line);
        std::string title, author, pagesText, id, status;
        if (!std::getline(row, title, ',') || !std::getline(row, author, ',')
            || !std::getline(row, pagesText, ',') || !std::getline(row, id, ',')
            || !std::getline(row, status) || title.empty() || author.empty()
            || id.empty() || (status != "true" && status != "false"))
            throw std::runtime_error("Invalid book record: " + line);

        std::size_t used;
        int pages = std::stoi(pagesText, &used);
        if (used != pagesText.size() || pages <= 0)
            throw std::runtime_error("Invalid page count: " + pagesText);
        for (const Book& book : books)
            if (book.getId() == id)
                throw std::runtime_error("Duplicate book ID: " + id);

        // Keep IDs as strings so leading zeros are preserved.
        books.emplace_back(title, author, pages, id, status == "true");
    }
    return books;
}

int main()
{
    try
    {
        auto books = loadBooks("bookData.txt");
        if (books.empty())
            throw std::runtime_error("The book file is empty.");
        std::string choice, id;

        // Return to the menu after each action until the user exits.
        while (true)
        {
            std::cout << "\nBook Manager\n1. View all books\n2. View one book\n"
                      << "3. Borrow a book\n4. Return a book\n5. Exit\nChoice: ";
            if (!std::getline(std::cin, choice) || choice == "5")
                break;
            if (choice == "1")
            {
                for (const Book& book : books)
                    book.display();
                continue;
            }
            if (choice != "2" && choice != "3" && choice != "4")
            {
                std::cout << "Please enter a choice from 1 to 5.\n";
                continue;
            }

            std::cout << "Enter book ID (for example, 001): ";
            if (!std::getline(std::cin, id))
                break;
            bool found = false;
            for (Book& book : books)
            {
                if (book.getId() == id)
                {
                    found = true;
                    if (choice == "2") book.display();
                    else if (choice == "3") book.borrowBook();
                    else book.returnBook();
                    break;
                }
            }
            if (!found)
                std::cout << "No book found with that ID.\n";
        }
        std::cout << "Goodbye!\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
    return 0;
}