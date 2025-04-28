#include <iostream>
#include <fstream>
using namespace std;

struct tugas {
    string judul, deskripsi, prioritas, deadline;
    bool selesai;
    tugas* next;
};

void tampilanmenu() {
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
int main (){
    int pilih;
    tugas* head = nullptr;
    do{
        tampilanmenu();
        cin >> pilih;
        switch (pilih) {
            case 1: {
            // Input data
            break;
            }
            case 2: {
            // Lihat data
            break;
            }
            case 3:{
            // Sorting
            break;
            }
            case 4:{
            // Searching
            break;
            }
            case 5:{
            // Tandai tugas selesai
            break;
            }
            case 6:{
            // Hapus data
            break;
            }
            case 7:{
            // Simpan dan keluar data
            
            }
        }
    }
    while (pilih != 7);{
    cout <<"exit" << endl;}
}
