#include "13519086-topo_sort.hpp"

void topo_sortUtil(MataKuliah * M )
{
    //program untuk mengeliminasi node yang terdapat dalam semester sekarang
    for(auto i : M->currMK)
    {
        for(auto& val : M->adjList)
        {
            auto& adjV = val.second;
            auto itr = adjV.begin();
            while (itr != adjV.end()) 
            {
                if(*itr == i)
                {   
                    // hapus node jika node sekarang terdapat dalam list semester sekarang
                    adjV.remove(i);
                    M->total_size--;
                    break;
                }
                ++itr;
            }
        }
    }
    return;
}

void topo_sort(MataKuliah * M)
{
    M->currMK.clear();
    for(auto val = M->adjList.begin(); val != M->adjList.end();)
    {
        string v = (*val).first;
        int idx = distance(M->adjList.begin(),val);
        // disini jika kolom pertama tidak dikaitkan dengan null, maka akan dilewati oleh iterasi vektor
        // dicek juga apabila sudah visited/belum jika sudah maka dilewati
        if ((*val).second.size() == 1 && !M->vis[++idx])
        {
            M->solved.push_back(v);
            M->vis[idx] = true; // mengeset idx sekarang menjadi visited
            M->erased[M->semester].push_back(v); 
            M->currMK.push_back(v);
        }
        else
        {
          ++val;
        }
    }
    topo_sortUtil(M);
    M->semester++;
    if(M->total_size != M->adjList.size())
    {
        // jika jumlah matkul sekarang belum sama dengan jumlah null maka akan dilakukan
        // pemanggilan ulang topo_sort
        topo_sort(M);
    }
    else
    {
        // kasus basis, jika jumlah matkul sekarang = jumlah null maka return
        return;
    }
}

string ConvertToRomawi(int n) 
{
    // program untuk mengonversi integer ke romawi
    string arrRomawi[] = {"X", "IX", "V", "IV", "I"};
    int val[] = {10, 9, 5, 4, 1};
    string res = "";    
    for (int i = 0; i < 5; i++)
    {
        while(n - val[i] > -1)
        {
            n -= val[i];
            res = res + arrRomawi[i];
        }
    }
    return res;
}

void mains() {
    fstream input_stream;
    ofstream output_stream;
    MataKuliah M;   
    string filename,str,v1,v2; // filename untuk menampung string nama file, str untuk menampung array of string per baris
                               // v1 dan v2 untuk menampung vertices
    vector <string> input_data;// input_data untuk vector 2 dimensi dari file input
    cout<<"Masukkan input nama file : ";
    cin >> filename;
    filename = "../test/" + filename;
    memset(M.vis,false,sizeof(M.vis));
    input_stream.open(filename,ios::in);
    output_stream.open("../bin/output.txt");
    // Menginput per baris, lalu dimasukkan ke vector 2 dimensi
    while(getline (input_stream,str))
    {
        input_data.push_back(str);
    }
    M.erased.resize(2001,vector<string>(input_data.size()));
    for(int i=0;i<input_data.size();i++)
    {
        int j = 0;
        int count = 0;
        while(j < input_data[i].size())
        {
            int k = j;
            vector<char>mk; //Vektor untuk menampung node mata kuliah
            while(k < input_data[i].size())
            {
                // jika menemukan titik atau koma, maka lanjut ke node baru
                if(input_data[i][k] == ',' || input_data[i][k] == '.' )
                {
                    string s(mk.begin(),mk.end());
                    if(count == 0)
                    {
                        // setiap baris kolom pertama akan dikaitkan dengan null untuk menandai
                        // pada vektor dan digunakan untuk kasus basis pada rekursif
                        v1 = s;
                        v2 = "null";
                    }
                    else
                    {
                        v2 = s;
                    }
                    M.adjList[v1].push_back(v2);
                    count++;
                    j = k+1;
                    break;
                }
                mk.push_back(input_data[i][k]);
                k++;
            }
            j++;
        }
    } 
    for(auto itr : M.adjList)
    {
        //total_
        M.total_size+=itr.second.size();
    }
    clock_t tStart = clock();
    float time;
    topo_sort(&M);
    
    for(auto i = M.adjList.begin(); i!= M.adjList.end();)
    {
        auto it = find (M.solved.begin(), M.solved.end(), (*i).first);
        // ini merupakan iterasi untuk menambahkan vektor mata kuliah pada semester akhir
        // karena tidak dilewati oleh iterasi (kondisi basis sudah ditemukan dahulu)
        if(it == M.solved.end())
        {
            M.erased[M.semester].push_back((*i).first);
        }
        i++;
    }
    for(int i =0 ;i<=M.semester;i++)
    {
        cout<<"Semester "<<ConvertToRomawi(i+1)<<" : "; 
        output_stream<<"Semester "<<ConvertToRomawi(i+1)<<" : ";
        for(int j=0;j<M.erased[i].size();j++)
        {
            if(M.erased[i][j] =="")
                continue;
            cout<<M.erased[i][j];
            output_stream<<M.erased[i][j];
            if(j!=M.erased[i].size()-1)
            {
                cout<<", ";
                output_stream<<", ";
            }
            else
            {
                cout<<".";
                output_stream<<".";
            }
        }
        cout<<endl;
        output_stream<<endl;
    }
    time=(double)(clock() - tStart)/CLOCKS_PER_SEC;
    cout << "Waktu yang dibutuhkan : " << time << " detik" << endl;
    output_stream << "Waktu yang dibutuhkan : " << time << " detik" << endl;
}