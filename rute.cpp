#include "rute.h"

adrGedung createGedung(string newGedung) {
    adrGedung V = new gedung;
    infoGedung(V) = newGedung;
    nextGedung(V) = NULL;
    firstJalan(V) = NULL;
    return V;
}

adrJalan createJalan(string destGedung, int bobot) {
    adrJalan P = new jalan;
    destGedung(P) = destGedung;
    bobotJalan(P) = bobot;
    nextJalan(P) = NULL;
    return P;
}

void initGraph(graph &G) {
    firstGedung(G) = NULL;
}

adrGedung findGedung(graph G, string gedungID) {
    adrGedung current = firstGedung(G);
    while (current != NULL) {
        if (infoGedung(current) == gedungID) {
            return current;
        }
        current = nextGedung(current);
    }
    return NULL;
}

adrJalan findJalan(graph G, string sourceGedungID, string destGedungID) {
    adrGedung sourceGedung = findGedung(G, sourceGedungID);
    if (sourceGedung == NULL) {
        return NULL;
    }

    adrJalan current = firstJalan(sourceGedung);
    while (current != NULL) {
        if (destGedung(current) == destGedungID) {
            return current;
        }
        current = nextJalan(current);
    }
    return NULL;
}

void addGedung(graph &G, string newGedungID) {
    adrGedung newGedung = createGedung(newGedungID);
    if (firstGedung(G) == NULL) {
        firstGedung(G) = newGedung;
    } else {
        adrGedung temp = firstGedung(G);
        while (nextGedung(temp) != NULL) {
            temp = nextGedung(temp);
        }
        nextGedung(temp) = newGedung;
    }
}

void addJalan(graph &G, string sourceGedungID, string destGedungID, int bobot) {
    adrGedung sourceGedung = findGedung(G, sourceGedungID);
    adrJalan newJalan = createJalan(destGedungID, bobot);
    if (sourceGedung != NULL) {
        nextJalan(newJalan) = firstJalan(sourceGedung);
        firstJalan(sourceGedung) = newJalan;
    }
}
void JalanTerpendek(graph G, string startID, string endID) {
    adrGedung startGedung = findGedung(G, startID);
    adrGedung endGedung = findGedung(G, endID);

    if (startGedung == NULL || endGedung == NULL) {
        cout << "Error: Gedung tidak ditemukan" << endl;
        return;
    }

    adrGedung current = firstGedung(G);
    while (current != NULL) {
        current->jarak = INT_MAX;
        current->dikunjungi = false;
        current->tracking = NULL;
        current = nextGedung(current);
    }

    startGedung->jarak = 0;

    while (true) {
        adrGedung minGedung = NULL;
        int minJarak = INT_MAX;

        current = firstGedung(G);
        while (current != NULL) {
            if (!current->dikunjungi && current->jarak < minJarak) {
                minGedung = current;
                minJarak = current->jarak;
            }
            current = nextGedung(current);
        }

        if (minGedung == NULL || minGedung == endGedung) break;

        minGedung->dikunjungi = true;
        adrJalan jalan = firstJalan(minGedung);
        while (jalan != NULL) {
            adrGedung tetangga = findGedung(G, destGedung(jalan));
            if (tetangga != NULL && !tetangga->dikunjungi) {
                int jarakBaru = minGedung->jarak + bobotJalan(jalan);
                if (jarakBaru < tetangga->jarak) {
                    tetangga->jarak = jarakBaru;
                    tetangga->tracking = minGedung;
                }
            }
            jalan = nextJalan(jalan);
        }
    }

    if (endGedung->jarak == INT_MAX) {
        cout << "Tidak ada jalur dari " << startID << " ke " << endID << "." << endl;
        return;
    }

    cout << "Jarak terpendek dari " << startID << " ke " << endID << ": " << endGedung->jarak << endl;
    cout << "Jalur: ";

    adrGedung traverse = endGedung;
    string jalur = "";
    while (traverse != NULL) {
        jalur = infoGedung(traverse) + (jalur.empty() ? "" : " -> ") + jalur;
        traverse = traverse->tracking;
    }
    cout << jalur << endl;
}

void buildGraph(graph &G) {
    initGraph(G);

    addGedung(G, "Rektorat");
    addGedung(G, "Asrama Putra");
    addGedung(G, "TULT");
    addGedung(G, "BTP");
    addGedung(G, "TUCH");
    addGedung(G, "MSU");
    addGedung(G, "GKU1");

    addJalan(G, "Rektorat", "Asrama Putra", 100);
    addJalan(G, "Asrama Putra", "TULT", 30);
    addJalan(G, "Asrama Putra", "BTP", 70);
    addJalan(G, "BTP", "TUCH", 80);
    addJalan(G, "TUCH", "MSU", 100);
    addJalan(G, "MSU", "GKU1", 50);
    addJalan(G, "GKU1", "Rektorat", 40);
}

void showGraph(graph G) {
    adrGedung gedung = firstGedung(G);
    while (gedung != NULL) {
        cout << "Gedung: " << infoGedung(gedung) << endl;
        adrJalan jalan = firstJalan(gedung);
        while (jalan != NULL) {
            cout << "  -> " << destGedung(jalan) << " (bobot: " << bobotJalan(jalan) << ")" << endl;
            jalan = nextJalan(jalan);
        }
        gedung = nextGedung(gedung);
    }
}

void printGedungDenganCabangTerbanyak(graph G) {
    adrGedung gedung = firstGedung(G);
    adrGedung maxGedung = NULL;
    int maxCabang = 0;

    while (gedung != NULL) {
        int jumlahCabang = 0;
        adrJalan jalan = firstJalan(gedung);
        while (jalan != NULL) {
            jumlahCabang++;
            jalan = nextJalan(jalan);
        }
        if (jumlahCabang > maxCabang) {
            maxCabang = jumlahCabang;
            maxGedung = gedung;
        }
        gedung = nextGedung(gedung);
    }

    if (maxGedung != NULL) {
        cout << "Gedung dengan cabang terbanyak: " << infoGedung(maxGedung) << " (" << maxCabang << " cabang)" << endl;
    } else {
        cout << "Tidak ada gedung yang ditemukan." << endl;
    }
}

void CariJalanAlternatif(graph G, string startID, string endID, string avoidID) {
    adrGedung startGedung = findGedung(G, startID);
    adrGedung endGedung = findGedung(G, endID);
    adrGedung avoidGedung = findGedung(G, avoidID);

    if (startGedung == NULL || endGedung == NULL || avoidGedung == NULL) {
        cout << "Error: Gedung tidak ditemukan" << endl;
        return;
    }

    adrGedung current = firstGedung(G);
    while (current != NULL) {
        current->jarak = INT_MAX;
        current->dikunjungi = false;
        current->tracking = NULL;
        current = nextGedung(current);
    }

    startGedung->jarak = 0;

    while (true) {
        adrGedung minGedung = NULL;
        int minJarak = INT_MAX;

        current = firstGedung(G);
        while (current != NULL) {
            if (!current->dikunjungi && current->jarak < minJarak && current != avoidGedung) {
                minGedung = current;
                minJarak = current->jarak;
            }
            current = nextGedung(current);
        }

        if (minGedung == NULL || minGedung == endGedung) break;
        minGedung->dikunjungi = true;

        adrJalan jalan = firstJalan(minGedung);
        while (jalan != NULL) {
            adrGedung tetangga = findGedung(G, destGedung(jalan));
            if (tetangga != NULL && !tetangga->dikunjungi && tetangga != avoidGedung) {
                int jarakBaru = minGedung->jarak + bobotJalan(jalan);
                if (jarakBaru < tetangga->jarak) {
                    tetangga->jarak = jarakBaru;
                    tetangga->tracking = minGedung;
                }
            }
            jalan = nextJalan(jalan);
        }
    }

    if (endGedung->jarak == INT_MAX) {
        cout << "Tidak ada jalan alternatif dari " << startID << " ke " << endID << " menghindari " << avoidID << "." << endl;
        return;
    }

    cout << "Jarak terpendek alternatif dari " << startID << " ke " << endID << " menghindari " << avoidID << ": " << endGedung->jarak << endl;
    cout << "Rute: ";

    adrGedung traverse = endGedung;
    string rute = "";
    while (traverse != NULL) {
        rute = infoGedung(traverse) + (rute.empty() ? "" : " -> ") + rute;
        traverse = traverse->tracking;
    }

    cout << rute << endl;
}
