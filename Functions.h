#pragma once
#include <iostream>
#include <string>

using namespace std;

void garisSamaDengan(int angka, bool withNewLine = false)
{
    for (size_t i = 0; i < angka; i++)
    {
        cout << "=";
    }

    if (withNewLine)
        cout << endl;
}

void clearScreen()
{
    system("cls");
}

void welcomeMessage()
{
    cout << "Aplikasi Mahasiswa Sederhana Banget" << endl
         << endl;
    cout << "== Menu Utama ";
    garisSamaDengan(70, true);
}

void newLine()
{
    cout << endl;
}

void separator()
{
    garisSamaDengan(70, true);
}

void storeStudent(sql::Connection *con, sql::PreparedStatement *pstmt)
{

    string npm = "";
    string name = "";
    string kelas = "";
    string alamat = "";

    newLine();
    cout << "== Tambah data siswa baru ";
    garisSamaDengan(70, true);
    newLine();

    cout << "Masukkan NPM Siswa: ";
    getline(cin, npm);
    getline(cin, npm);

    cout << "Masukkan Nama Siswa: ";
    getline(cin, name);

    cout << "Masukkan Kelas Siswa: ";
    getline(cin, kelas);

    cout << "Masukkan Alamat Siswa: ";
    getline(cin, alamat);
    newLine();

    cout << "Proses menambahkan siswa ...";
    newLine();

    pstmt = con->prepareStatement("INSERT INTO students(npm, name, kelas, address) VALUES(?,?,?,?)");
    pstmt->setString(1, npm);
    pstmt->setString(2, name);
    pstmt->setString(3, kelas);
    pstmt->setString(4, alamat);
    pstmt->execute();

    newLine();
    cout << "== Berhasil menambahkan siswa baru" << endl;
    newLine();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}

void listData(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{
    pstmt = con->prepareStatement("SELECT * FROM students;");
    result = pstmt->executeQuery();

    const char *columnSize = "| %-10s | %-20s | %-20s | %-30s |\n";

    newLine();
    cout << "== List Data Siswa ";
    garisSamaDengan(70, true);

    printf(columnSize, "NPM", "Nama Siswa", "Kelas", "Alamat");
    separator();

    while (result->next())
        printf(columnSize, result->getString(2).c_str(), result->getString(3).c_str(), result->getString(5).c_str(), result->getString(4).c_str());

    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}