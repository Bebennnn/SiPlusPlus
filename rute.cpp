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
