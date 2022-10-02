#pragma once
#include <iostream>
#include <string>

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

    newLine();
    cout << "== Tambah data siswa baru ============================" << endl;
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