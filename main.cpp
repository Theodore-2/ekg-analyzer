#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;


class EKG{
    private:
        string name;
        vector<double> zamanlar;
        vector<double> voltajlar;
        vector<double> pikZamanlar;
        vector<double> pikVoltajlar;
        vector<double> normal_T;
        vector<double> bradikardi_T;
        vector<double> tasikardi_T;
        vector<double> normal_V;
        vector<double> bradikardi_V;
        vector<double> tasikardi_V;
    public:
    
        void analizEt(string isim){
            name = isim;
            dosyadanVeriOku();
            pikHesaplama();
            sınıflandırma();
            dosyaYazdırma();
        }

   
        void dosyadanVeriOku() {

            ifstream dosyaOku(name+".txt");
            if (!dosyaOku.is_open()) {
                cout << "Dosya acilamadi!" << endl;
                return;
            }

            string satir;
            getline(dosyaOku, satir);
            double zaman, voltaj;

            while (dosyaOku >> zaman >> voltaj){
                zamanlar.push_back(zaman);
                voltajlar.push_back(voltaj);
            }

            dosyaOku.close();
        }


        void pikHesaplama() {

            pikZamanlar.push_back(0);
            pikVoltajlar.push_back(0);

            for(size_t i = 1; i < voltajlar.size()-1; ++i){
                if(voltajlar[i] >= 0.06 && voltajlar[i] > voltajlar[i-1] && voltajlar[i] > voltajlar[i+1]){
                    bool result = true;
                    for(int j = 1; j <= 500; j++){
                        if(voltajlar[i] < voltajlar[i+j]){
                            result = false;
                            break;
                        }
                    }
                    if(result){
                        pikZamanlar.push_back(zamanlar[i]);
                        pikVoltajlar.push_back(voltajlar[i]);
                        i = i + 500;
                    }
                }
            }
        }

    
        
        void sınıflandırma(){

            double zamanFark = 0, voltajFark = 0;

            for(size_t i = 1; i < pikZamanlar.size(); ++i){
                voltajFark = abs(pikVoltajlar[i] - pikVoltajlar[i-1]);
                if(voltajFark > 0.0033){
                    zamanFark = abs(pikZamanlar[i] - pikZamanlar[i+1]);
                    if(zamanFark <= 0.6) {
                        tasikardi_T.push_back(pikZamanlar[i]);
                        tasikardi_V.push_back(pikVoltajlar[i]);
                    }
                   else if(zamanFark > 1) {
                       bradikardi_T.push_back(pikZamanlar[i]);
                       bradikardi_V.push_back(pikVoltajlar[i]);
                   }
                   else {
                       normal_T.push_back(pikZamanlar[i]);
                       normal_V.push_back(pikVoltajlar[i]);
                   }
                }
                else{
                    zamanFark = abs(pikZamanlar[i] - pikZamanlar[i-1]);
                    if(zamanFark <= 0.6){
                        tasikardi_T.push_back(pikZamanlar[i]);
                        tasikardi_V.push_back(pikVoltajlar[i]);
                    }
                    else if(zamanFark > 1){
                        bradikardi_T.push_back(pikZamanlar[i]);
                        bradikardi_V.push_back(pikVoltajlar[i]);
                    }
                    else{
                        normal_T.push_back(pikZamanlar[i]);
                        normal_V.push_back(pikVoltajlar[i]);
                    }
                }
            }

        }

    
        
        void dosyaYazdırma(){

            ofstream normalYazdır(name+"-normal.txt");
            ofstream bradikardiYazdır(name+"-bradikardi.txt");
            ofstream tasikardiYazdır(name+"-tasikardi.txt");

            normalYazdır << left << setw(15) << "ZAMAN" << "VOLTAJ" << endl;
            normalYazdır << string(30, '-') << endl;
            for(size_t i = 0; i < normal_T.size(); ++i) {
                normalYazdır << left << setw(15) << fixed << setprecision(4) << normal_T[i]
                << fixed << setprecision(4) << normal_V[i] << endl;
            }

            bradikardiYazdır << left << setw(15) << "ZAMAN" << "VOLTAJ" << endl;
            bradikardiYazdır << string(30, '-') << endl;
            for(size_t i = 0; i < bradikardi_T.size(); ++i) {
                bradikardiYazdır << left << setw(15) << fixed << setprecision(4) << bradikardi_T[i]
                << fixed << setprecision(4) << bradikardi_V[i] << endl;
            }

            tasikardiYazdır << left << setw(15) << "ZAMAN" << "VOLTAJ" << endl;
            tasikardiYazdır << string(30, '-') << endl;
            for(size_t i = 0; i < tasikardi_T.size(); ++i) {
                tasikardiYazdır << left << setw(15) << fixed << setprecision(4) << tasikardi_T[i]
                << fixed << setprecision(4) << tasikardi_V[i] << endl;
            }

            return;

        }

};


void dosyaBirleştir(const string& inputFile1, const string& inputFile2, const string& inputFile3,
                    const string& outputFile) {

    ifstream inFile1(inputFile1);
    ifstream inFile2(inputFile2);
    ifstream inFile3(inputFile3);
    ofstream outFile(outputFile);

    if (!inFile1) {
        cout << "Hata: " << inputFile1 << " dosyası açılamadı!" << endl;
        return;
    }
    if (!inFile2) {
        cout << "Hata: " << inputFile2 << " dosyası açılamadı!" << endl;
        return;
    }
    if (!inFile3) {
        cout << "Hata: " << inputFile3 << " dosyası açılamadı!" << endl;
        return;
    }

    if (!outFile) {
        cout << "Hata: " << outputFile << " dosyası oluşturulamadı!" << endl;
        return;
    }

    outFile << left << setw(15) << "ZAMAN" << "VOLTAJ" << endl;
    outFile << string(30, '-') << endl;
    string line;

    int count = 0;
    while (getline(inFile1, line)) {
        if (count <= 1) {
            count ++;
            continue;
        }
        outFile << line << endl;
    }
    inFile1.close();
    outFile << "***************************" << endl;
    count = 0;
    while (getline(inFile2, line)) {
        if (count <= 1) {
            count ++;
            continue;
        }
        outFile << line << endl;
    }
    inFile2.close();
    outFile << "***************************" << endl;
    count = 0;
    while (getline(inFile3, line)) {
        if (count <= 1) {
            count ++;
            continue;
        }
        outFile << line << endl;
    }
    inFile3.close();

    cout << "Dosya islemleri tamamlandı!" << endl;
    outFile.close();
}


int main(){
    EKG person1, person2, person3;

    person1.analizEt("person1");
    person2.analizEt("person2");
    person3.analizEt("person3");

    dosyaBirleştir("person1-normal.txt", "person2-normal.txt", "person3-normal.txt",
                   "normal-person-1-2-3.txt");
    dosyaBirleştir("person1-bradikardi.txt", "person2-bradikardi.txt", "person3-bradikardi.txt",
                   "bradikardi-person-1-2-3.txt");
    dosyaBirleştir("person1-tasikardi.txt", "person2-tasikardi.txt", "person3-tasikardi.txt",
                   "tasikardi-person-1-2-3.txt");
    return 0;
}






