#include "rute.h"

adrGedung createGedung(string newGedung) {
    adrGedung g = new gedung;
    infoGedung(g) = newGedung;
    firstJalan(g) = NULL;
    nextGedung(g) = NULL;
    return g;
}

adrJalan createJalan(string destGedung, int bobot) {
    adrJalan p = new jalan;
    destGedung(p) = destGedung;
    bobotJalan(p) = bobot;
    nextJalan(p) = NULL;
    return p;
}

adrGedung findGedung(graph G, string gedungID) {
    adrGedung currentGedung = firstGedung(G);
    while (currentGedung != NULL) {
        if (infoGedung(currentGedung) == gedungID) {
            return currentGedung;
        }
        currentGedung = nextGedung(currentGedung);
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
    nextJalan(newJalan) = firstJalan(sourceGedung);
    firstJalan(sourceGedung) = newJalan;
}

void initGraph(graph &G) {
    firstGedung(G) = NULL;
}

void buildGraph(graph &G) {
    initGraph(G);

    addGedung(G, "MSU");
    addGedung(G, "GKU1");
    addGedung(G, "Rektorat");
    addGedung(G, "TUCH");
    addGedung(G, "BTP");
    addGedung(G, "Asrama Putra");
    addGedung(G, "TULT");
    addJalan(G, "MSU", "GKU1", 50);
    addJalan(G, "GKU1", "Rektorat", 40);
    addJalan(G, "Rektorat", "Asrama Putra", 100);
    addJalan(G, "MSU", "TUCH", 100);
    addJalan(G, "TUCH", "BTP", 80);
    addJalan(G, "BTP", "Asrama Putra", 70);
    addJalan(G, "Asrama Putra", "TULT", 30);
}

void showGraph(graph G) {
    adrGedung gedung = firstGedung(G);
    while (gedung != NULL) {
        cout << "-Gedung: " << infoGedung(gedung) << endl;
        adrJalan jalan = firstJalan(gedung);
        while (jalan != NULL) {
            cout << "ke " << destGedung(jalan) << " dengan jarak " << bobotJalan(jalan) << " langkah" << endl;
            jalan = nextJalan(jalan);
        }
        gedung = nextGedung(gedung);
    }
}

void JalanTerpendek(graph G, string startID, string endID) {
    adrGedung startGedung = findGedung(G, startID);
    adrGedung endGedung = findGedung(G, endID);

    if (startGedung == NULL || endGedung == NULL) {
        cout << "Error: Gedung Tidak Ditemukan" << endl;
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
            adrGedung neighbor = findGedung(G, destGedung(jalan));
            if (neighbor != NULL && !neighbor->dikunjungi) {
                int newJarak = minGedung->jarak + bobotJalan(jalan);
                if (newJarak < neighbor->jarak) {
                    neighbor->jarak = newJarak;
                    neighbor->tracking = minGedung;
                }
            }
            jalan = nextJalan(jalan);
        }
    }

    if (endGedung->jarak == INT_MAX) {
        cout << "Tidak ada jalur dari " << startID << " ke " << endID << "." << endl;
    } else {
        cout << "Jarak terpendek dari " << startID << " ke " << endID << " adalah: ";
        string path = "";
        adrGedung tracking = endGedung;
        while (tracking != NULL) {
            path = infoGedung(tracking) + (path.empty() ? "" : " -> ") + path;
            tracking = tracking->tracking;
        }
        cout << path << endl;
        cout << "dengan jarak " << endGedung->jarak << " langkah" << endl;
    }
}

void printGedungDenganCabangTerbanyak(graph G) {
    adrGedung gedung = firstGedung(G);
    adrGedung maxGedung = NULL;
    int maxJalan = 0;

    while (gedung != NULL) {
        int jalanCount = 0;
        adrJalan jalan = firstJalan(gedung);
        while (jalan != NULL) {
            jalanCount++;
            jalan = nextJalan(jalan);
        }
        if (jalanCount > maxJalan) {
            maxJalan = jalanCount;
            maxGedung = gedung;
        }
        gedung = nextGedung(gedung);
    }

    if (maxGedung != NULL) {
        cout << "Gedung dengan jalur terbanyak: " << infoGedung(maxGedung) << " dengan " << maxJalan << " cabang jalur." << endl;
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
            adrGedung neighbor = findGedung(G, destGedung(jalan));
            if (neighbor != NULL && !neighbor->dikunjungi && neighbor != avoidGedung) {
                int newJarak = minGedung->jarak + bobotJalan(jalan);
                if (newJarak < neighbor->jarak) {
                    neighbor->jarak = newJarak;
                    neighbor->tracking = minGedung;
                }
            }
            jalan = nextJalan(jalan);
        }
    }
    if (endGedung->jarak == INT_MAX) {
        cout << "Tidak ada jalur alternatif dari " << startID << " ke " << endID << "." << endl;
        return;
    }
    cout << "Jalur alternatif dari " << startID << " ke " << endID << " adalah: ";
    adrGedung traverse = endGedung;
    string path = "";
    while (traverse != NULL) {
        path = infoGedung(traverse) + (path.empty() ? "" : " -> ") + path;
        traverse = traverse->tracking;
    }

    cout << path << endl;
    cout << "Dengan jarak " << endGedung->jarak << " langkah" << endl;
}
