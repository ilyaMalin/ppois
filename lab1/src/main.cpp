#include "ui.hpp"

int main()
{
    std::cout << "Enter workplace (0 - multiset, 1 - Post machine): ";
    unsigned choice = 0;
    std::cin >> choice;

    if (choice == 0)
    {
        UI ui;
        ui.menu();
    }
    else if (choice == 1)
    {
        UIPost uiPost;
        uiPost.menu();
    }
    else
    {
        std::cout << "Invalid choice!\n";
    }
}