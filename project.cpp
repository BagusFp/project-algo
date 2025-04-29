#include <iostream>
#include <fstream>
using namespace std;

struct tugas
{
    string judul, deskripsi, prioritas, deadline;
    bool selesai;
    tugas *next;
};
void tambah(tugas *&head, string judul, string deskripsi, string prioritas, string deadline, bool selesai = false)
{
    tugas *newTask = new tugas();
    newTask->judul = judul;
    newTask->deskripsi = deskripsi;
    newTask->prioritas = prioritas;
    newTask->deadline = deadline;
    newTask->selesai = selesai;
    newTask->next = head;
    head = newTask;
    cout << "Tugas berhasil ditambahkan!\n";
}
void tampilkan(tugas *head)
{
    cout << "\n=== Daftar Tugas ===\n";
    if (head == nullptr)
    {
        cout << "Belum ada tugas.\n";
        return;
    }
    while (head != nullptr)
    {
        cout << "Judul: " << head->judul << endl;
        cout << "Deskripsi: " << head->deskripsi << endl;
        cout << "Prioritas: " << head->prioritas << endl;
        cout << "Deadline: " << head->deadline << endl;
        cout << "Status: " << (head->selesai ? "Selesai" : "Belum Selesai") << endl;
        cout << "-------------------\n";
        head = head->next;
    }
}
void tampilanmenu()
{
    cout << "====================" << endl;
    cout << "1. Input Data" << endl;
    cout << "2. Lihat Data" << endl;
    cout << "3. Sorting" << endl;
    cout << "4. Searching" << endl;
    cout << "5. Tandai Tugas Selesai" << endl;
    cout << "6. Hapus Data" << endl;
    cout << "7. Simpan dan keluar Data" << endl;
    cout << "====================" << endl;
    cout << "Pilih menu: ";
}

int main()
{
    tugas *head = nullptr;
    int pilih;

    string judul, deskripsi, prioritas, deadline;
    do
    {
        tampilanmenu();
        cin >> pilih;
        cin.ignore();
        switch (pilih)
        {
        case 1:
        {

            cout << "Masukkan judul tugas: ";
            getline(cin, judul);
            cout << "Masukkan deskripsi tugas: ";
            getline(cin, deskripsi);
            cout << "Masukkan prioritas (Tinggi/Sedang/Rendah): ";
            getline(cin, prioritas);
            cout << "Masukkan deadline (YYYY-MM-DD): ";
            getline(cin, deadline);
            tambah(head, judul, deskripsi, prioritas, deadline);
            break;
        }
        case 2:
        {
            tampilkan(head);
            break;
        }
        case 3:
        {
            // Sorting
            break;
        }
        case 4:
        {
            // Searching
            break;
        }
        case 5:
        {
            // Tandai tugas selesai
            break;
        }
        case 6:
        {
            // Hapus data
            break;
        }
        case 7:
        {
            // Simpan dan keluar data
        }
        }
    } while (pilih != 7);
    {
        cout << "exit" << endl;
    }
}
