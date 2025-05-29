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

        while (true)
        {
            cout << "Prioritas (Tinggi/Sedang/Rendah): ";
            cin.getline(newTask->prioritas, sizeof(newTask->prioritas));
            string prioritasStr = newTask->prioritas;
            if (prioritasStr == "Tinggi" || prioritasStr == "Sedang" || prioritasStr == "Rendah")
            {
                break;
            }
            cout << "Prioritas harus Tinggi, Sedang, atau Rendah! Silakan coba lagi.\n";
        }

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
void swapNodes(tugas *a, tugas *b)
{
    swap(a->judul, b->judul);
    swap(a->deskripsi, b->deskripsi);
    swap(a->prioritas, b->prioritas);
    swap(a->deadline, b->deadline);
    swap(a->selesai, b->selesai);
}
tugas *getTail(tugas *head)
{
    while (head != nullptr && head->next != nullptr)
    {
        head = head->next;
    }
    return head;
}
int caseInsensitiveCompare(const char *a, const char *b)
{
    while (*a && *b)
    {
        int diff = tolower(*a) - tolower(*b);
        if (diff != 0)
            return diff;
        a++;
        b++;
    }
    return *a - *b;
}
tugas *partition(tugas *head, tugas *end, tugas *&newHead, tugas *&newEnd)
{
    tugas *pivot = end;
    tugas *prev = nullptr, *cur = head, *tail = pivot;

    newHead = nullptr;

    while (cur != pivot)
    {
        if (caseInsensitiveCompare(cur->judul, pivot->judul) < 0)
        {
            if (newHead == nullptr)
                newHead = cur;
            prev = cur;
            cur = cur->next;
        }
        else
        {
            if (prev)
                prev->next = cur->next;
            tugas *tmp = cur->next;
            cur->next = nullptr;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    if (newHead == nullptr)
        newHead = pivot;

    newEnd = tail;
    return pivot;
}
tugas *quickSortRecur(tugas *head, tugas *end)
{
    if (!head || head == end)
        return head;

    tugas *newHead = nullptr, *newEnd = nullptr;
    tugas *pivot = partition(head, end, newHead, newEnd);

    if (newHead != pivot)
    {
        tugas *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = nullptr;

        newHead = quickSortRecur(newHead, tmp);

        tmp = getTail(newHead);
        tmp->next = pivot;
    }

    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}
void quickSort(tugas *&headRef)
{
    if (!headRef)
        return;

    headRef = quickSortRecur(headRef, getTail(headRef));
}

int prioritasValue(const string &prioritas)
{
    if (prioritas == "Tinggi")
        return 3;
    if (prioritas == "Sedang")
        return 2;
    return 1;
}
void selectionSortByPrioritas(tugas *head)
{
    for (tugas *i = head; i != nullptr; i = i->next)
    {
        tugas *min = i;
        for (tugas *j = i->next; j != nullptr; j = j->next)
        {
            if (prioritasValue(j->prioritas) > prioritasValue(min->prioritas))
            {
                min = j;
            }
        }
        if (min != i)
        {
            swapNodes(min, i);
        }
    }
}
void bubbleSortByDeadline(tugas *head)
{
    if (!head)
        return;

    bool swapped;
    tugas *ptr1;
    tugas *lptr = nullptr;

    do
    {
        swapped = false;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (strcmp(ptr1->deadline, ptr1->next->deadline) > 0)
            {
                swapNodes(ptr1, ptr1->next);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}
void sortMenu(tugas *&head)
{
    if (!head)
    {
        cout << "Tidak ada tugas untuk diurutkan!\n";
        return;
    }
    cout << "\n1. Sort by Judul (Quick Sort)\n";
    cout << "2. Sort by Prioritas (Selection Sort)\n";
    cout << "3. Sort by Deadline (Bubble Sort)\n";
    cout << "4. Kembali ke menu\n";
    cout << "Pilih: ";
    int choice;
    cin >> choice;
    cin.ignore();
    switch (choice)
    {
    case 1:
        quickSort(head);
        cout << "Tugas diurutkan berdasarkan judul!\n";
        tampilkan(head);
        break;
    case 2:
        selectionSortByPrioritas(head);
        cout << "Tugas diurutkan berdasarkan prioritas!\n";
        tampilkan(head);
        break;
    case 3:
        bubbleSortByDeadline(head);
        cout << "Tugas diurutkan berdasarkan deadline!\n";
        tampilkan(head);
        break;
    case 4:
        return;
    default:
        cout << "Pilihan tidak valid!\n";
        return;
    }
    saveToFile(head);
}
void sequentialSearchByJudul(tugas *head)
{
    if (!head)
    {
        cout << "Tidak ada tugas!\n";
        return;
    }
    string keyword;
    cout << "Masukkan judul yang dicari: ";
    getline(cin, keyword);

    bool found = false;
    while (head)
    {
        if (head->judul == keyword)
        {
            cout << "Tugas ditemukan:\n";
            cout << "Judul: " << head->judul << endl;
            cout << "Deskripsi: " << head->deskripsi << endl;
            cout << "Prioritas: " << head->prioritas << endl;
            cout << "Deadline: " << head->deadline << endl;
            cout << "Status: " << (head->selesai ? "Selesai" : "Belum") << endl;
            cout << "-------------------\n";
            found = true;
        }
        head = head->next;
    }
    if (!found)
    {
        cout << "Tidak ditemukan tugas dengan judul tersebut!\n";
    }
}
void binarySearchByPrioritas(tugas *head)
{
    if (!head)
    {
        cout << "Tidak ada tugas!\n";
        return;
    }

    selectionSortByPrioritas(head);

    string keyword;
    cout << "Masukkan prioritas yang dicari (Tinggi/Sedang/Rendah): ";
    getline(cin, keyword);

    bool found = false;
    while (head)
    {
        if (head->prioritas == keyword)
        {
            cout << "Tugas ditemukan:\n";
            cout << "Judul: " << head->judul << endl;
            cout << "Deskripsi: " << head->deskripsi << endl;
            cout << "Prioritas: " << head->prioritas << endl;
            cout << "Deadline: " << head->deadline << endl;
            cout << "Status: " << (head->selesai ? "Selesai" : "Belum") << endl;
            cout << "-------------------\n";
            found = true;
        }
        else if (prioritasValue(head->prioritas) < prioritasValue(keyword))
        {
            break;
        }
        head = head->next;
    }
    if (!found)
    {
        cout << "Tidak ditemukan tugas dengan prioritas tersebut!\n";
    }
}
void sequentialSearchByDeadline(tugas *head)
{
    if (!head)
    {
        cout << "Tidak ada tugas!\n";
        return;
    }
    string keyword;
    cout << "Masukkan deadline yang dicari (YYYY-MM-DD): ";
    getline(cin, keyword);

    bool found = false;
    while (head)
    {
        if (head->deadline == keyword)
        {
            cout << "Tugas ditemukan:\n";
            cout << "Judul: " << head->judul << endl;
            cout << "Deskripsi: " << head->deskripsi << endl;
            cout << "Prioritas: " << head->prioritas << endl;
            cout << "Deadline: " << head->deadline << endl;
            cout << "Status: " << (head->selesai ? "Selesai" : "Belum") << endl;
            cout << "-------------------\n";
            found = true;
        }
        head = head->next;
    }
    if (!found)
    {
        cout << "Tidak ditemukan tugas dengan deadline tersebut!\n";
    }
}
void searchMenu(tugas *head)
{
    cout << "\n1. Search by Judul (Sequential)\n";
    cout << "2. Search by Prioritas (Binary)\n";
    cout << "3. Search by Deadline (Sequential)\n";
    cout << "4. Kembali ke menu\n";
    cout << "Pilih: ";

    int choice;
    cin >> choice;
    cin.ignore();

    switch (choice)
    {
    case 1:
        sequentialSearchByJudul(head);
        break;
    case 2:
        binarySearchByPrioritas(head);
        break;
    case 3:
        sequentialSearchByDeadline(head);
        break;
    case 4:
        cout << "Kembali ke menu\n";
        break;
    default:
        cout << "Pilihan tidak valid!\n";
    }
}
void tandaiSelesai(tugas *head)
{
    if (!head)
    {
        cout << "Tidak ada tugas!\n";
        return;
    }
    int count = 1;
    tugas *curr = head;
    while (curr)
    {
        cout << count++ << ". " << curr->judul;
        if (curr->selesai)
            cout << " (Selesai)";
        cout << endl;
        curr = curr->next;
    }
    cout << "Pilih nomor tugas: ";
    int pilihan;
    cin >> pilihan;
    cin.ignore();
    curr = head;
    for (int i = 1; i < pilihan && curr; i++)
    {
        curr = curr->next;
    }

    if (curr)
    {
        curr->selesai = true;
        saveToFile(head);
        cout << "Tugas ditandai selesai!\n";
    }
    else
    {
        cout << "Nomor tidak valid!\n";
    }
}
void hapusTugas(tugas *&head)
{
    if (!head)
    {
        cout << "Tidak ada tugas!\n";
        return;
    }
    int pilihan;
    do
    {
        cout << "------menu hapus------" << endl;
        cout << "1. pilih tugas yg di hapus " << endl;
        cout << "2. hapus semua tugas" << endl;
        cout << "3. kembali ke menu" << endl;
        cout << "pilih: ";
        cin >> pilihan;
        cin.ignore();
        if (pilihan == 3)
        {
            cout << "kembali ke menu" << endl;
            break;
        }
        else if (pilihan == 2)
        {
            while (head)
            {
                tugas *temp = head;
                head = head->next;
                delete temp;
            }
            saveToFile(head);
            cout << "Semua tugas dihapus!\n";
            return;
        }
        else if (pilihan == 1)
        {
            int count = 1;
            tugas *curr = head;
            while (curr)
            {
                cout << count++ << ". " << curr->judul << endl;
                curr = curr->next;
            }

            cout << "Pilih nomor yang akan dihapus: ";
            int pilihan;
            cin >> pilihan;
            cin.ignore();

            if (pilihan == 1)
            {
                tugas *temp = head;
                head = head->next;
                delete temp;
                saveToFile(head);
                cout << "Tugas dihapus!\n";
                return;
            }

            tugas *prev = head;
            for (int i = 1; i < pilihan - 1 && prev; i++)
            {
                prev = prev->next;
            }

            if (prev && prev->next)
            {
                tugas *temp = prev->next;
                prev->next = temp->next;
                delete temp;
                saveToFile(head);
                cout << "Tugas dihapus!\n";
            }
            else
            {
                cout << "Nomor tidak valid!\n";
            }
        }
        else
        {
            cout << "pilihan tidak valid" << endl;
        }
    } while (pilihan != 1 && pilihan != 2 && pilihan != 3);
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
            sortMenu(head);
            break;
        case 4:
            searchMenu(head);
            break;
        case 5:
            tandaiSelesai(head);
            break;
        case 6:
            hapusTugas(head);
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
