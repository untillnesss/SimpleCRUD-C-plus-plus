#pragma once
#include <iostream>

using namespace std;

void clearScreen()
{
    system("cls");
}

void welcomeMessage()
{
    cout << "Aplikasi Mahasiswa Sederhana Banget" << endl
         << endl;
    cout << "== Menu Utama ==================================" << endl;
}

void newLine()
{
    cout << endl;
}

void storeStudent(sql::Connection *con, sql::PreparedStatement *pstmt)
{

    string npm = "";
    string name = "";
    string kelas = "";
    string alamat = "";

    cout << "Masukkan NPM Siswa: ";
    cin >> npm;
    newLine();

    cout << "Masukkan Nama Siswa: ";
    cin >> name;
    newLine();

    cout << "Masukkan Kelas Siswa: ";
    cin >> kelas;
    newLine();

    cout << "Masukkan Alamat Siswa: ";
    cin >> alamat;
    newLine();

    cout << "Proses menambahkan siswa ...";
    newLine();

	pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
	pstmt->setString(1, "banana");
	pstmt->setInt(2, 150);
	pstmt->execute();
	cout << "One row inserted." << endl;

    cout << name << " " << npm << " " << kelas << " " << alamat << " " << endl;
}