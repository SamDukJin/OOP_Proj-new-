# Bank Management System

A Qt-based application simulating a bank management system with user and admin functionalities.

## Description

This project is a comprehensive bank management system developed using Qt, providing a user-friendly GUI for banking operations. It features secure login and registration, detailed user account management, transaction history, loan management, and administrative control.

## Features

-   **Secure Login and Registration:** Robust error handling for user authentication and unique account number generation.

-   **User Account Management:**
    -   Display of user details (username, account number, balance).
    -   Transaction history tracking.
    -   Deposit, withdrawal, and transfer functionalities.
    -   Loan management with due date tracking and status updates.
    -   Account settings for username and password changes.
-   **Admin Panel:**
    -   Database account management (activate, deactivate, delete).
    -   Account number modification.
    -   Display of all user accounts.
-   **Loan Management:**
    -   Loan status tracking (paid/unpaid).
    -   Automatic disabling of withdrawal and transfer for unpaid loans.
    -   Due date implementation.
    -   Loan payment and loan taking functionality.
-   **Error Handling:** Comprehensive error checking throughout the application.
-   **Database Integration:** Utilizes a SQLite database for persistent data storage.

## Installation

1.  **Prerequisites:**
    -   Qt 5 or 6 (with necessary modules like `QtSql`).
    -   A compatible database system (SQLite).
2.  **Clone the Repository:**

    ```bash
    git clone [your-repository-url.git](your-repository-url.git)
    cd bank-management-system
    ```

3.  **Open with Qt Creator:**
    -   Open the `bank-management-system.pro` file with Qt Creator.
4.  **Configure Database:**
    -   The application uses SQLite, and the database file (`bank_system.db`) is created automatically.
5.  **Build and Run:**
    -   Build the project in Qt Creator.
    -   Run the executable.

## Usage

1.  **User Login/Registration:**

    -   Launch the application to access the login/registration screen.

2.  **User Interface:**

    -   Users can view their account details and access transaction features.

3.  **Admin Panel:**

    -   Admin users can manage accounts through the admin panel.

4.  **Loan Management:**

    -   Users can request and manage loans, and the system will control loan status.

5.  **Account Settings:**

    -   Users can change their username and password.

## Code Structure

-   `main.cpp`: Entry point of the application.
-   `mainwindow.cpp`: Login and registration window.
-   `mainbankgui.cpp`: Main user interface.
-   `featureswindow.cpp`: Transaction features window (deposit, withdrawal, transfer).
-   `depositwindow.cpp`, `withdrawwindow.cpp`, `transferwindow.cpp`: Specific transaction windows.
-   `settingwindow.cpp`: Account settings window.
-   `adminpanel.cpp`: Admin control panel.
-   `loanwindow.cpp`: Loan management window.
-   `databasemanager.cpp`: Database connection and management, including table creation and schema updates.
-   `registerwin.cpp`: Registration window.
-   UI files (`.ui`): Qt Designer files for GUI elements.

## Key Components

-   **DatabaseManager:**

    -   Manages the SQLite database connection using the singleton pattern.
    -   Provides a `getDatabase()` method to access the database instance.
    -   `createTables()` method handles table creation and schema updates, ensuring database integrity.
-   **MainBankGUI:**

    -   Manages the main user interface for both regular users and administrators.
    -   Fetches user details from the database using `fetchUserDetails()`.
    -   Handles navigation to other windows (Features, Admin Panel, Settings, Loan).
-   **FeaturesWindow:**

    -   Manages the transaction features (deposit, withdrawal, transfer).
    -   Checks the loan status using `checkLoanStatus()` to determine if transactions should be restricted.
-   **LoanWindow:**

    -   Handles loan requests and payments.
    -   Tracks loan status and enforces due date restrictions using `checkDueDate()`.
    -   Updates the UI using `updateUI()` and the database using `updateDatabase()`.
    -   Allows users to pay their loans with `payloan()`.

-   **RegisterWin:**
    -   Handles user registration.
    -   Generates unique account numbers using `generateAccountNumber()`.
    -   Validates user inputs using `validateInputs()`.
-   **SettingWindow:**
    -   Manages user account settings, including username and password changes.
    -   Handles account deletion and logout.
-   **AdminPanel:**
    -   Manages admin functionalities, such as account activation, deactivation, and deletion.
    -   Loads account data for display using `loadAccounts()`.
    -   Allows admin to change account numbers with `changeaccnum()`.
-   **Transferwindow:**
    -   Handles the transfer of funds between accounts.
    -   Uses `checkAccountAvailability()` to verify recipient accounts.
    -   Manages the transfer process with `processTransfer()`.
-   **DepositWindow/WithdrawWindow:**
    -   Handles deposit and withdraw operations.
    -   Provides user feedback and updates the balance display.

## Contributing

1.  Fork the repository.
2.  Create a new branch for your feature or bug fix.
3.  Make your changes and commit them.
4.  Push your changes to your fork.
5.  Submit a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](https://github.com/SamDukJin/OOP_Proj-new-/blob/main/LICENSE) file for details.

[![License: MIT](https://img.shields.io/badge/License-MIT-red.svg)](https://github.com/SamDukJin/OOP_Proj-new-/blob/main/LICENSE) [![Static Badge](https://custom-icon-badges.demolab.com/badge/-OPENSORUCE-red?logo=heart&style=flat)]()

## Acknowledgments

This project was developed as part of the Year 1 Semester 2 curriculum for Software Engineering students at KMITL.

**Contributors:**

-   67011336 Thanaphat Chongkananurak: Primarily responsible for GUI development and backend functionality related to registration, login, deposit, and withdrawal.
-   67011627 Nopparath Nonraksanukul: Responsible for the remaining backend code, as well as providing GUI advice and rearrangement suggestions.
