#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct reader
{
    int id;
    char name[20];
    char due;
    int duebookid[3];
    struct reader *next;
} reader;

typedef struct books
{
    int id;
    char title[40];
    char author[20];
    char available;
    int readerid;
    struct books *next;
} book;

book *createBook()
{
    printf("Enter name of the book: ");
    book *temp = (book *)malloc(sizeof(book));
    scanf("%s", temp->title);
    printf("Enter Author's Name : ");
    fflush(stdin);
    scanf("%s", temp->author);
    printf("Enter book ID: ");
    fflush(stdin);
    scanf("%d", &temp->id);
    temp->available = 'y';
    temp->readerid = 0;
    temp->next = NULL;
    return temp;
}

reader *createReader()
{
    reader *newreader = (reader *)malloc(sizeof(reader));

    printf("Enter Reader's name: ");
    fflush(stdin);
    scanf("%[^\n]s", newreader->name);
    printf("Enter your ID: ");
    fflush(stdin);
    scanf("%d", &newreader->id);
    newreader->due = 'n';

    for (int i = 0; i < 3; i++)
    {
        newreader->duebookid[i] = 0;
    }
    newreader->next = NULL;
    return newreader;
}

void insertBook(book **head)
{
    if (*head == NULL)
    {
        *head = createBook();
    }
    else
    {
        book *newbook = *head;
        while (newbook->next != NULL)
        {
            newbook = newbook->next;
        }
        book *new = createBook();
        newbook->next = new;
    }
}

void insertReader(reader **head)
{
    if (*head == NULL)
    {
        *head = createReader();
    }
    else
    {
        reader *nextreader = *head;
        while (nextreader->next != NULL)
        {
            nextreader = nextreader->next;
        }
        reader *new = createReader();
        nextreader->next = new;
    }
}

void searchBook(book *head, int searchId)
{
    book *bookName = head;
    while (bookName != NULL)
    {
        if (bookName->id == searchId)
        {
            fflush(stdin);
            printf("\n\tBook Information\nBook ID: %d\tBook Name: %s\nAuthor Name: %s\nAvailable: %c\tDue by Reader ID: %d\n", bookName->id, bookName->title, bookName->author, bookName->available, bookName->readerid);
            return;
        }
        bookName = bookName->next;
    }
    printf("Book not found.\n\n");
}


void searchReader(reader *head, int searchId)
{
    reader *seachingReader = head;
    while (seachingReader != NULL)
    {
        if (seachingReader->id == searchId)
        {
            fflush(stdin);
            printf("\n\tReader Information\n");
            printf("Reader's ID : %d\n", seachingReader->id);
            fflush(stdin);
            printf("Reader's name : %s\n ", seachingReader->name);
            fflush(stdin);
            printf("Due: %c\n",seachingReader->due);
            fflush(stdin);
            printf("Due book IDs: %d\n",seachingReader->duebookid[0]);
            return;
        }
        seachingReader = seachingReader->next;
    }
    printf("Reader not found.\n\n");
}

void issueBook(book *bookList, reader *readerList, int bookId, int readerid)
{
    // Implementation for issuing a book to a reader
    book *bookPtr = bookList;
    reader *readerPtr = readerList;

    while (bookPtr != NULL)
    {
        if (bookPtr->id == bookId)
        {
            if (bookPtr->available == 'y')
            {
                while (readerPtr != NULL)
                {
                    if (readerPtr->id == readerid)
                    {
                        if (readerPtr->due == 'n')
                        {
                            // Issue the book
                            bookPtr->available = 'n';
                            bookPtr->readerid = readerid;
                            readerPtr->due = 'y';
                            for (int i = 0; i < 3; i++)
                            {
                                if (readerPtr->duebookid[i] == 0)
                                {
                                    readerPtr->duebookid[i] = bookId;
                                    break;
                                }
                            }
                            printf("Book issued successfully.\n\n");
                            return;
                        }
                        else
                        {
                            printf("Book not issued. Reader has a due book.\n\n");
                            return;
                        }
                    }
                    readerPtr = readerPtr->next;
                }
            }
            else
            {
                printf("Book not issued. Book is not available.\n\n");
                return;
            }
        }
        bookPtr = bookPtr->next;
    }
    printf("Book not found.\n\n");
}

void submitBook(book *bookList, reader *readerList, int bookId)
{
    book *bookPtr = bookList;
    reader *readerPtr = readerList;

    while (bookPtr != NULL)
    {
        if (bookPtr->id == bookId)
        {
            if (bookPtr->available == 'n')
            {
                while (readerPtr != NULL)
                {
                    if (readerPtr->id == bookPtr->readerid)
                    {
                        bookPtr->available = 'y';
                        bookPtr->readerid = 0;
                        readerPtr->due = 'n';
                        for (int i = 0; i < 3; i++)
                        {
                            readerPtr->duebookid[i] = 0;
                        }
                        printf("Book ID - %d has been submitted successfully.\n\n", bookId);
                        return;
                    }
                    readerPtr = readerPtr->next;
                }
            }
            else
            {
                printf("Book not submitted. Book is not issued.\n\n");
                return;
            }
        }
        bookPtr = bookPtr->next;
    }
    printf("Book not found.\n\n");
}

void deleteBook(book **head, int bookId)
{
    book *prev = NULL;
    book *current = *head;

    while (current != NULL)
    {
        if (current->id == bookId)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Book ID %d deleted.\n\n", bookId);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Book not found.\n\n");
}

void deleteReader(reader **head, int readerid)
{
    reader *prev = NULL;
    reader *current = *head;

    while (current != NULL)
    {
        if (current->id == readerid)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Reader ID %d deleted.\n\n", readerid);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Reader not found.\n\n");
}

void listBooks(book *head)
{
    int n = 0;
    book *p = head;
    printf("\n\t\tBook list\nTotal books: %d\n\nID\tName\t\tAuthor\t\tAvailable\tReader ID\n\n", n);
    while (p != NULL)
    {
        printf("%d\t%s\t\t%s\t\t%c\t\t%d\n", p->id, p->title, p->author, p->available, p->readerid);
        n++;
        p = p->next;
    }
}

void listReaders(reader *head)
{
    int n = 0;
    reader *p = head;
    printf("\n\t\tReader list\n\nID\tName\tDue\tDue Book ID\n\n");
    while (p != NULL)
    {
        printf("%d\t%s\t%c\t%d\n", p->id, p->name, p->due, p->duebookid[0]);
        n++;
        p = p->next;
    }
    printf("\nTotal Readers : %d\n",n);
}


int main()
{
    printf("\n\t\tWELCOME!\n");
    int choice, searchid, searchid1, n, m;
    book *book_list = NULL;
    reader *reader_list = NULL;
    int searchBookId, searchreaderid, issueBookId, issuereaderid, submitBookId, deleteBookId, deletereaderid;

    do {
        printf("\n\tLibrary Management System\n\t=========================\n1. Add new book\t\t2. Search book\n3. Add new reader\t4. Search reader\n5. Issue book\t\t6. Submit book\n7. Delete book\t\t8. Delete reader\n9. List of books\t10. List of readers\n11. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                insertBook(&book_list);
                printf("Book added successfully.\n\n");
                break;

            case 2:
                printf("Enter book ID: ");
                scanf("%d", &searchBookId);
                searchBook(book_list, searchBookId);
                break;

            case 3:
                insertReader(&reader_list);
                printf("Reader added successfully.\n\n");
                break;

            case 4:
                printf("Enter Reader ID: ");
                scanf("%d", &searchreaderid);
                searchReader(reader_list, searchreaderid);
                break;

            case 5:
                printf("Enter book ID: ");
                scanf("%d", &issueBookId);
                printf("Enter reader ID: ");
                scanf("%d", &issuereaderid);
                issueBook(book_list, reader_list, issueBookId, issuereaderid);
                break;

            case 6:
                printf("Enter book ID: ");
                scanf("%d", &submitBookId);
                submitBook(book_list, reader_list, submitBookId);
                break;

            case 7:
                printf("Enter book ID to be deleted: ");
                scanf("%d", &deleteBookId);
                deleteBook(&book_list, deleteBookId);
                break;

            case 8:
                printf("Enter reader ID to be deleted: ");
                scanf("%d", &deletereaderid);
                deleteReader(&reader_list, deletereaderid);
                break;

            case 9:
                listBooks(book_list);
                break;

            case 10:
                listReaders(reader_list);
                break;

            case 11:
                printf("\n\t\tTHANK YOU!\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n\n");
        }
    } while (choice != 11);

    while (book_list != NULL) 
    {
        book *temp = book_list;
        book_list = book_list->next;
        free(temp);
    }

    while (reader_list != NULL) 
    {
        reader *temp = reader_list;
        reader_list = reader_list->next;
        free(temp);
    }

    return 0;
}
