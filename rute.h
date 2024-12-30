#ifndef RUTE_H_INCLUDED
#define RUTE_H_INCLUDED

#define firstGedung(G) G.firstGedung
#define nextGedung(V) V->nextGedung
#define infoGedung(V) V->infoGedung
#define firstJalan(V) V->firstJalan
#define destGedung(p) p->destGedung
#define nextJalan(p) p->nextJalan
#define bobotJalan(p) p->bobotJalan

#include <iostream>
#include <string>
using namespace std;

typedef struct gedung *adrGedung;
typedef struct jalan *adrJalan;

struct gedung {
    string infoGedung;
    adrGedung nextGedung;
    adrJalan firstJalan;
    int jarak;
    bool dikunjungi;
    adrGedung tracking;
};

struct jalan {
    string destGedung;
    int bobotJalan;
    adrJalan nextJalan;
};

struct graph {
    adrGedung firstGedung;
};

adrGedung createGedung(string newGedung);
adrJalan createJalan(string destGedung, int bobot);
adrGedung findGedung(graph G, string gedungID);
void addGedung(graph &G, string newGedungID);
void addJalan(graph &G, string sourceGedungID, string destGedungID, int bobot);
void initGraph(graph &G);
void buildGraph(graph &G);
void showGraph(graph G);
void JalanTerpendek(graph G, string startID, string endID);
void CariJalanAlternatif(graph G, string startID, string endID, string avoidID);
void printGedungDenganCabangTerbanyak(graph G);

#endif // RUTE_H_INCLUDED
