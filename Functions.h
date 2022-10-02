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
    cout << "Aplikasi Mahasiswa Sederhana Banget by: Muhammad Abdullah Sa'id" << endl
         << endl;
    cout << "== Menu Utama ";
    garisSamaDengan(100, true);
}

void newLine()
{
    cout << endl;
}

void separator()
{
    garisSamaDengan(100, true);
}

void storeStudent(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{

    string npm = "";
    string name = "";
    string kelas = "";
    string alamat = "";

    newLine();
    cout << "== Tambah data siswa baru ";
    garisSamaDengan(100, true);
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

    pstmt = con->prepareStatement("SELECT * FROM students WHERE npm = ?;");
    pstmt->setString(1, npm);
    result = pstmt->executeQuery();

    if (result->rowsCount() > 0)
    {
        newLine();
        cout << "== NPM sudah tersedia, silahkan coba lagi" << endl;
        newLine();
        cout << "Tekan sembarang untuk ke Menu Utama, ";
        system("pause");
        return;
    }

    pstmt = con->prepareStatement("INSERT INTO students(npm, name, kelas, address) VALUES(?,?,?,?)");
    pstmt->setString(1, npm);
    pstmt->setString(2, name);
    pstmt->setString(3, kelas);
    pstmt->setString(4, alamat);
    pstmt->execute();

    newLine();
    separator();
    cout << "== Berhasil menambahkan siswa baru" << endl;
    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}

void listData(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{
    pstmt = con->prepareStatement("SELECT * FROM students;");
    result = pstmt->executeQuery();

    const char *columnSize = "| %-15s | %-35s | %-20s | %-50s |\n";

    newLine();
    cout << "== List Data Siswa ";
    garisSamaDengan(100, true);

    printf(columnSize, "NPM", "Nama Siswa", "Kelas", "Alamat");
    separator();

    if (result->rowsCount() == 0)
    {
        cout << "Data siswa kosong" << endl;
    }
    else
    {
        while (result->next())
            printf(columnSize, result->getString(2).c_str(), result->getString(3).c_str(), result->getString(5).c_str(), result->getString(4).c_str());
    }

    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}

void deleteData(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{
    string npm = "";

    cout << "Masukkan NPM siswa yang ingin dihapus: ";
    getline(cin, npm);
    getline(cin, npm);

    pstmt = con->prepareStatement("SELECT * FROM students WHERE npm = ?;");
    pstmt->setString(1, npm);
    result = pstmt->executeQuery();

    if (result->rowsCount() == 0)
    {
        newLine();
        cout << "== Siswa dengan NPM " << npm << " tidak ada, silahkan coba lagi" << endl;
        newLine();
        cout << "Tekan sembarang untuk ke Menu Utama, ";
        system("pause");
        return;
    }

    pstmt = con->prepareStatement("DELETE FROM students WHERE npm = ?;");
    pstmt->setString(1, npm);
    result = pstmt->executeQuery();
    separator();
    cout << "== Berhasil menghapus data siswa" << endl;
    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}

void updateData(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{
    string npm = "";
    string oldNpm = "";
    string name = "";
    string kelas = "";
    string alamat = "";

    cout << "Masukkan NPM siswa yang ingin diubah: ";
    getline(cin, npm);
    getline(cin, npm);

    pstmt = con->prepareStatement("SELECT * FROM students WHERE npm = ?;");
    pstmt->setString(1, npm);
    result = pstmt->executeQuery();

    if (result->rowsCount() == 0)
    {
        newLine();
        cout << "== Siswa dengan NPM " << npm << " tidak ada, silahkan coba lagi" << endl;
        newLine();
        cout << "Tekan sembarang untuk ke Menu Utama, ";
        system("pause");
        return;
    }

    while (result->next())
    {
        oldNpm = result->getString(2).c_str();

        newLine();
        cout << "Masukkan NPM Siswa[" << result->getString(2).c_str() << "]: ";
        getline(cin, npm);
        if (npm == "")
        {
            npm = result->getString(2).c_str();
        }

        cout << "Masukkan Nama Siswa[" << result->getString(3).c_str() << "]: ";
        getline(cin, name);
        if (name == "")
        {
            name = result->getString(3).c_str();
        }

        cout << "Masukkan Kelas Siswa[" << result->getString(5).c_str() << "]: ";
        getline(cin, kelas);
        if (kelas == "")
        {
            kelas = result->getString(5).c_str();
        }

        cout << "Masukkan Alamat Siswa[" << result->getString(4).c_str() << "]: ";
        getline(cin, alamat);
        if (alamat == "")
        {
            alamat = result->getString(4).c_str();
        }
        newLine();

        cout << "Proses mengubah siswa ...";
        newLine();
    }

    if (oldNpm != npm)
    {
        pstmt = con->prepareStatement("SELECT * FROM students WHERE npm = ?;");
        pstmt->setString(1, npm);
        result = pstmt->executeQuery();

        if (result->rowsCount() > 0)
        {
            newLine();
            cout << "== NPM sudah tersedia, silahkan coba lagi" << endl;
            newLine();
            cout << "Tekan sembarang untuk ke Menu Utama, ";
            system("pause");
            return;
        }
    }

    pstmt = con->prepareStatement("UPDATE students SET npm = ?, name = ?, kelas = ?, address = ? WHERE npm = ?");
    pstmt->setString(1, npm);
    pstmt->setString(2, name);
    pstmt->setString(3, kelas);
    pstmt->setString(4, alamat);
    pstmt->setString(5, oldNpm);
    pstmt->execute();

    newLine();
    separator();
    cout << "== Berhasil mengubah siswa baru" << endl;
    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}

void storeScoreData(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{
    string studentId = "";
    string npm = "";
    string pelajaran = "";
    string score = "";

    cout << "Masukkan NPM siswa : ";
    getline(cin, npm);
    getline(cin, npm);

    pstmt = con->prepareStatement("SELECT * FROM students WHERE npm = ?;");
    pstmt->setString(1, npm);
    result = pstmt->executeQuery();

    if (result->rowsCount() == 0)
    {
        newLine();
        cout << "== Siswa dengan NPM " << npm << " tidak ada, silahkan coba lagi" << endl;
        newLine();
        cout << "Tekan sembarang untuk ke Menu Utama, ";
        system("pause");
        return;
    }

    while (result->next())
    {
        studentId = result->getString(1).c_str();
        newLine();
        separator();
        cout << "NPM: " << result->getString(2).c_str() << endl;
        cout << "Nama Siswa: " << result->getString(3).c_str() << endl;
        newLine();
    }

    cout << "Masukkan Nama Pelajaran: ";
    getline(cin, pelajaran);

    cout << "Masukkan Nilai: ";
    getline(cin, score);

    pstmt = con->prepareStatement("INSERT INTO scores(student_id, name, score) VALUES(?,?,?)");
    pstmt->setString(1, studentId);
    pstmt->setString(2, pelajaran);
    pstmt->setString(3, score);
    pstmt->execute();

    newLine();
    separator();
    cout << "== Berhasil menambahkan nilai" << endl;
    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
    return;
}

void showData(sql::Connection *con, sql::PreparedStatement *pstmt, sql::ResultSet *result)
{
    string npm = "";
    string studentId = "";

    cout << "Masukkan NPM siswa: ";
    getline(cin, npm);
    getline(cin, npm);

    pstmt = con->prepareStatement("SELECT * FROM students WHERE npm = ?;");
    pstmt->setString(1, npm);
    result = pstmt->executeQuery();

    if (result->rowsCount() == 0)
    {
        newLine();
        cout << "== Siswa dengan NPM " << npm << " tidak ada, silahkan coba lagi" << endl;
        newLine();
        cout << "Tekan sembarang untuk ke Menu Utama, ";
        system("pause");
        return;
    }

    while (result->next())
    {
        studentId = result->getString(1).c_str();
        newLine();
        cout << "== Detail Siswa ";
        garisSamaDengan(100, true);
        cout << "NPM: " << result->getString(2).c_str() << endl;
        cout << "Nama Siswa: " << result->getString(3).c_str() << endl;
        newLine();
    }

    pstmt = con->prepareStatement("SELECT * FROM scores WHERE student_id = ?;");
    pstmt->setString(1, studentId);
    result = pstmt->executeQuery();

    const char *columnSize = "| %-30s | %-15s |\n";
    cout << "== Daftar Nilai Siswa ";
    garisSamaDengan(100, true);

    printf(columnSize, "Nama Pelajaran", "Nilai");
    separator();

    if (result->rowsCount() == 0)
    {
        cout << "Data nilai kosong" << endl;
    }
    else
    {
        while (result->next())
            printf(columnSize, result->getString(3).c_str(), result->getString(4).c_str());
    }

    separator();
    cout << "Tekan sembarang untuk ke Menu Utama, ";
    system("pause");
}