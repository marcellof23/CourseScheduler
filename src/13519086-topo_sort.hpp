#ifndef TOPO_SORT_HPP
#define TOPO_SORT_HPP
using namespace std;
#include <bits/stdc++.h>

typedef struct { 
  map< string, list< string > > adjList; // vektor untuk menampung mata kuliah dari file teks
  vector<vector<string>> erased; // vektor untuk menampung mata kuliah yang sudah diambil, baris menandai semester
  vector<string>currMK,solved; // vektor solved untuk menampung mata kuliah akhir yang sudah dihapus saat iterasi terakhir
  int total_size = 0, semester = 0;
  bool vis[10000];
} MataKuliah;

void topo_sortUtil(MataKuliah * M);

void topo_sort(MataKuliah * M);

string ConvertToRomawi(int n);

void mains();

#endif
