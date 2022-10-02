#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <Functions.h>
#include <conio.h>

using namespace std;

// for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "";

sql::Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::PreparedStatement *pstmt;

void initConnectionMysql()
{
    driver = get_driver_instance();
    con = driver->connect(server, username, password);
}

int main()
{

    try
    {
        initConnectionMysql();
    }
    catch (sql::SQLException e)
    {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    // please create database "quickstartdb" ahead of time
    con->setSchema("submission_1_c_plus_plus");

    clearScreen();
    cout << "Hello :)" << endl;

    // Variables
    int chooseOneFromMenu = 0;
    char exitSurity;
    int num = 1;
    int fin = 0;
    // Variables End

    welcomeMessage();
    for (int i = 0; i < 1; i++)
    {
        fin = num;
        cout << fin << ". Lihat semua daftar Siswa" << endl; // 1
        fin += num;
        cout << fin << ". Tambah data Siswa baru" << endl; // 2
        fin += num;
        cout << fin << ". Ubah data Siswa" << endl; // 3
        fin += num;
        cout << fin << ". Hapus data Siswa" << endl; // 4
        fin += num;
        cout << fin << ". Tambah Nilai Siswa" << endl; // 5
        fin += num;
        cout << fin << ". Lihat Detail Siswa" << endl; // 6
        fin += num;
        cout << fin << ". Exit" << endl; // 7
        cout << "================================================" << endl;
        cout << "Pilih menu 1-7: ";
    }
    cin >> chooseOneFromMenu;

    switch (chooseOneFromMenu)
    {
    case 1:
        cout << "list all";
        break;
    case 2:
        storeStudent(con, pstmt);
        main();
        break;
    case 3:
        // FindItemFromList();
        // break;
    case 4:
        // AddIteminStock();
        // break;
    case 5:
        // UpdateStockItem();
        // break;
    case 6:
        cout << "Masuk menu";
        break;
    case 7:
    ExitProgram:
        cout << "Program terminating. Are you sure? (y/n): ";
        cin >> exitSurity;
        if (exitSurity == 'y' || exitSurity == 'Y')
        {
            delete con;
            return 0;
        }
        else if (exitSurity == 'n' || exitSurity == 'N')
        {
            system("cls");
            main();
        }
        else
        {
            cout << "Next time choose after read the corresponding line." << endl;
            goto ExitProgram;
        }
        break;
    default:
        cout << "Please choose between 1 - 7. Press Enter To Continue..." << endl;
        main();
        break;
    }
}