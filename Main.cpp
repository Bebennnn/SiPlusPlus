#include <iostream>
#include "rute.h"
using namespace std;

int main() {
    graph G;
    initGraph(G);
    buildGraph(G);

    int pilihan;

    do {
        cout << "\nMENU UTAMA" << endl;
        cout << "1. Tampilkan Semua Rute" << endl;
        cout << "2. Tampilkan Gedung dengan Jalan Terbanyak" << endl;
        cout << "3. Jalur Terpendek (Dijkstra)" << endl;
        cout << "4. Jalur Alternatif dengan Menghindari Gedung" << endl;
        cout << "0. Keluar" << endl;
        cout << "Silahkan Pilih Menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "\nRute yang Tersedia:" << endl;
                showGraph(G);
                break;
            }
            case 2: {
                cout << "\nGedung dengan Jalan Terbanyak:" << endl;
                printGedungDenganCabangTerbanyak(G);
                break;
            }
            case 3: {
                string startID, endID;
                cout << "\nMasukkan ID Gedung Awal: ";
                cin >> startID;
                cout << "Masukkan ID Gedung Tujuan: ";
                cin >> endID;
                JalanTerpendek(G, startID, endID);
                break;
            }
            case 4: {
                string startID, endID, avoidID;
                cout << "\nMasukkan ID Gedung Awal: ";
                cin >> startID;
                cout << "Masukkan ID Gedung Tujuan: ";
                cin >> endID;
                cout << "Masukkan ID Gedung yang Dihindari: ";
                cin >> avoidID;
                CariJalanAlternatif(G, startID, endID, avoidID); // Menampilkan jalur alternatif
                break;
            }
            case 0: {
                cout << "\nKeluar dari aplikasi. Terima kasih!" << endl;
                break;
            }
            default: {
                cout << "\nPilihan Tidak Tersedia. Silakan pilih lagi." << endl;
                break;
            }
        }
    } while (pilihan != 0);

    return 0;
}
