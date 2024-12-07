#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Mahasiswa{
    public:
        string Nama;
        string NIM;
        string Jurusan;
        double IPK;
        string Gelar;

        //constructor dengan parameter
        Mahasiswa(string Nama,string NIM, string Jurusan, double IPK){
            Mahasiswa::Nama = Nama;
            Mahasiswa::NIM = NIM;
            Mahasiswa::Jurusan = Jurusan;
            Mahasiswa::IPK = IPK;
        }

        //method tanpa parameter dan tanpa return
        void tampilkanData(){
            cout<<"Nama saya adalah "<<Nama<<endl;
            cout<<" NIM ku adalah "<< NIM<< endl;
            cout<<" Aku dari Prodi "<<Jurusan<<endl;
            cout<<"IPK ku "<<IPK<<endl;
        };

        //method dengan parameter dan tanpa return
       
};
class DBase{
    public:
        ifstream in;
        ofstream out;
        string fileName;

        DBase(const char* fileName){
            DBase::fileName = fileName;
        }

        void save(Mahasiswa data){
            cout<<data.Nama<<endl;
            cout<<data.NIM<<endl;
            cout<<data.Jurusan<<endl;
           
        }
};

int main(){
    Mahasiswa maba1 = Mahasiswa ("Sadhani", "535745", "Teknik Elektro", 3.50);
    maba1.tampilkanData();
    DBase database = DBase ("data.txt");

    database.save(maba1);
    

}