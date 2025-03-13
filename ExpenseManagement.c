#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define FILE_NAME "expenses.dat"

typedef struct {
    int id;
    char category[30];
    float amount;
    int day, month, year;
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

// Function to load expenses from a file
void loadExpensesFromFile() {
    FILE *file = fopen(FILE_NAME, "rb");
    if (file) {
        while (fread(&expenses[expenseCount], sizeof(Expense), 1, file)) {
            expenseCount++;
        }
        fclose(file);
    }
}

// Function to save expenses to a file
void saveExpensesToFile() {
    FILE *file = fopen(FILE_NAME, "wb");
    if (file) {
        fwrite(expenses, sizeof(Expense), expenseCount, file);
        fclose(file);
    } else {
        printf("Error saving data to file.\n");
    }
}

void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Expense list is full!\n");
        return;
    }
    Expense e;
    e.id = expenseCount + 1;
    printf("Enter category: ");
    scanf("%s", e.category);
    printf("Enter amount: ");
    scanf("%f", &e.amount);
    printf("Enter date (DD MM YYYY): ");
    scanf("%d %d %d", &e.day, &e.month, &e.year);
    expenses[expenseCount++] = e;
    saveExpensesToFile(); // Save data to file after adding
    printf("Expense added successfully!\n");
}

void showExpensesList() {
    if (expenseCount == 0) {
        printf("No expenses available.\n");
        return;
    }
    printf("Current Expenses:\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("ID: %d - Category: %s - Amount: %.2f - Date: %d/%d/%d\n",
               expenses[i].id, expenses[i].category, expenses[i].amount, expenses[i].day, expenses[i].month, expenses[i].year);
    }
}

void updateExpense() {
    int id;
    showExpensesList(); // Show list of expenses with IDs
    printf("Enter expense ID to update: ");
    scanf("%d", &id);
    if (id <= 0 || id > expenseCount) {
        printf("Invalid expense ID!\n");
        return;
    }
    printf("Enter new category: ");
    scanf("%s", expenses[id - 1].category);
    printf("Enter new amount: ");
    scanf("%f", &expenses[id - 1].amount);
    printf("Enter new date (DD MM YYYY): ");
    scanf("%d %d %d", &expenses[id - 1].day, &expenses[id - 1].month, &expenses[id - 1].year);
    saveExpensesToFile(); // Save data to file after updating
    printf("Expense updated successfully!\n");
}

void deleteExpense() {
    int id;
    showExpensesList(); // Show list of expenses with IDs
    printf("Enter expense ID to delete: ");
    scanf("%d", &id);
    if (id <= 0 || id > expenseCount) {
        printf("Invalid expense ID!\n");
        return;
    }
    for (int i = id - 1; i < expenseCount - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    expenseCount--;
    saveExpensesToFile(); // Save data to file after deleting
    printf("Expense deleted successfully!\n");
}

void viewExpenses() {
    for (int i = 0; i < expenseCount; i++) {
        printf("ID: %d\n", expenses[i].id);
        printf("Category: %s\n", expenses[i].category);
        printf("Amount: %.2f\n", expenses[i].amount);
        printf("Date: %d/%d/%d\n", expenses[i].day, expenses[i].month, expenses[i].year);
        printf("-------------------\n\n"); // Separator line
    }
}

void viewExpenseByMonth() {
    int month, year;
    printf("Enter month and year (MM YYYY): ");
    scanf("%d %d", &month, &year);

    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].month == month && expenses[i].year == year) {
            printf("ID: %d\n", expenses[i].id);
            printf("Category: %s\n", expenses[i].category);
            printf("Amount: %.2f\n", expenses[i].amount);
            printf("Date: %d/%d/%d\n", expenses[i].day, expenses[i].month, expenses[i].year);
            printf("-------------------\n\n"); // Separator line
        }
    }
}

void sortExpenses() {
    for (int i = 0; i < expenseCount - 1; i++) {
        for (int j = 0; j < expenseCount - i - 1; j++) {
            if (expenses[j].amount > expenses[j + 1].amount) {
                Expense temp = expenses[j];
                expenses[j] = expenses[j + 1];
                expenses[j + 1] = temp;
            }
        }
    }
    saveExpensesToFile(); // Save data to file after sorting
    printf("Expenses sorted by amount!\n");
}

void monthlyAnalysis() {
    int month, year;
    float total = 0, highest = 0, lowest = 1e9;
    printf("Enter month and year (MM YYYY): ");
    scanf("%d %d", &month, &year);
    for (int i = 0; i < expenseCount; i++) {
        if (expenses[i].month == month && expenses[i].year == year) {
            total += expenses[i].amount;
            if (expenses[i].amount > highest) highest = expenses[i].amount;
            if (expenses[i].amount < lowest) lowest = expenses[i].amount;
        }
    }
    if (total == 0) {
        printf("No expenses found for this month.\n");
    } else {
        printf("Total Expense: %.2f\n", total);
        printf("Highest Expense: %.2f\n", highest);
        printf("Lowest Expense: %.2f\n", lowest);
    }
}

int main() {
    loadExpensesFromFile(); // Load data from file when the program starts

    int choice;
    while (1) {
        printf("\nExpense Management System\n");
        printf("1. Add Expense\n2. Update Expense\n3. Delete Expense\n4. View Expenses\n5. View Expense by Month\n6. Sort Expenses\n7. Monthly Analysis\n8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addExpense(); break;
            case 2: updateExpense(); break;
            case 3: deleteExpense(); break;
            case 4: viewExpenses(); break;
            case 5: viewExpenseByMonth(); break;
            case 6: sortExpenses(); break;
            case 7: monthlyAnalysis(); break;
            case 8: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
