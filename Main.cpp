#include <iostream>
#include "rute.h"
using namespace std;

int main() {
    graph G;
    initGraph(G);
    buildGraph(G);

    int pilihan;

    do {
        cout << "-----MENU UTAMA-----" << endl;
        cout << "1. Tampilkan Semua Gedung dan Rute" << endl;
        cout << "2. Tampilkan Gedung dengan Jalur Terbanyak" << endl;
        cout << "3. Cari Jalur Terpendek" << endl;
        cout << "4. Cari Jalur Alternatif" << endl;
        cout << "0. Keluar" << endl;
        cout << "Silahkan Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                showGraph(G);
                break;
            }
            case 2: {
                printGedungDenganCabangTerbanyak(G);
                break;
            }
            case 3: {
                string startID, endID;
                cout << "\nMasukkan Gedung Asal: ";
                cin >> startID;
                cout << "Masukkan Gedung Tujuan: ";
                cin >> endID;
                JalanTerpendek(G, startID, endID);
                break;
            }
            case 4: {
                string startID, endID, avoidID;
                cout << "\nMasukkan Gedung Asal: ";
                cin >> startID;
                cout << "Masukkan Gedung Tujuan: ";
                cin >> endID;
                cout << "Masukkan Gedung yang Dihindari: ";
                cin >> avoidID;
                CariJalanAlternatif(G, startID, endID, avoidID);
                break;
            }
            case 0: {
                cout << "\nKeluar dari program!" << endl;
                break;
            }
            default: {
                cout << "\nMenu Tidak Tersedia." << endl;
                break;
            }
        }
    } while (pilihan != 0);

    return 0;
}
