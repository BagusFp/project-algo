#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

struct tugas
{
    char judul[100];
    char deskripsi[500];
    char prioritas[20];
    char deadline[20];
    bool selesai;
    tugas *next;
};
void saveToFile(tugas *head)
{
    FILE *file = fopen("tugas.dat", "wb");
    if (!file)
    {
        cout << "Gagal membuka file!\n";
        return;
    }
    tugas *curr = head;
    while (curr)
    {
        fwrite(curr, sizeof(tugas), 1, file);
        curr = curr->next;
    }
    fclose(file);
}
tugas *loadFromFile()
{
    FILE *file = fopen("tugas.dat", "rb");
    if (!file)
        return nullptr;

    tugas *head = nullptr;
    tugas *tail = nullptr;
    tugas temp;

    while (fread(&temp, sizeof(tugas), 1, file))
    {
        tugas *baru = new tugas;
        *baru = temp;
        baru->next = nullptr;

        if (!head)
        {
            head = tail = baru;
        }
        else
        {
            tail->next = baru;
            tail = baru;
        }
    }
    fclose(file);
    return head;
}
void tambah(tugas *&head)
{
    int n;
    cout << "-------menu tambah-------" << endl;
    cout << "jumlah tugas ditambahkan: ";
    cin >> n;
    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "tugas ke-" << i + 1 << endl;
        tugas *newTask = new tugas;

        cout << "Judul: ";
        cin.getline(newTask->judul, sizeof(newTask->judul));

        cout << "Deskripsi: ";
        cin.getline(newTask->deskripsi, sizeof(newTask->deskripsi));

        cout << "Prioritas (Tinggi/Sedang/Rendah): ";
        cin.getline(newTask->prioritas, sizeof(newTask->prioritas));

        cout << "Deadline (YYYY-MM-DD): ";
        cin.getline(newTask->deadline, sizeof(newTask->deadline));

        newTask->selesai = false;
        newTask->next = head;
        head = newTask;
    }
    saveToFile(head);
    cout << "Tugas ditambahkan!\n";
}
void tampilkan(tugas *head)
{
    if (!head)
    {
        cout << "Tidak ada tugas!\n";
        return;
    }

    while (head)
    {
        cout << "Judul: " << head->judul << endl;
        cout << "Deskripsi: " << head->deskripsi << endl;
        cout << "Prioritas: " << head->prioritas << endl;
        cout << "Deadline: " << head->deadline << endl;
        cout << "Status: " << (head->selesai ? "Selesai" : "Belum") << endl;
        cout << "-------------------\n";
        head = head->next;
    }
}
void menu()
{
    cout << "\n|--------Menu--------|\n";
    cout << "|1. Tambah Tugas     |\n";
    cout << "|2. Lihat Tugas      |\n";
    cout << "|3. Urutkan Tugas    |\n";
    cout << "|4. Cari Tugas       |\n";
    cout << "|5. Tandai Selesai   |\n";
    cout << "|6. Hapus Tugas      |\n";
    cout << "|7. Keluar           |\n";
    cout << "|Pilih: ";
}

int main()
{
    tugas *head = loadFromFile();
    int pilihan;
    do
    {
        menu();
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tambah(head);
            break;
        case 2:
            tampilkan(head);
            break;
        case 3:
            // sorting;
            break;
        case 4:
            // Searching
            break;
        case 5:
            // Tandai tugas selesai
            break;
        case 6:
            // Hapus data
            break;
        case 7:
            cout << "Keluar...\n";
            break;
        default:
            cout << "Pilihan salah!\n";
        }

    } while (pilihan != 7);

    while (head)
    {
        tugas *temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
