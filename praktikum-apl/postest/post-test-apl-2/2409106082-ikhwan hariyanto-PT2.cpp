#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    // Kredensial login
    const string CORRECT_NAME = "ikhwanhariyanto";
    const string CORRECT_NIM = "2409106082";
    
    // Variabel untuk login
    string inputName, inputNim;
    int loginAttempts = 0;
    bool isLoggedIn = false;
    
    // Arrays untuk menyimpan data
    string names[100];
    string nims[100];
    int totalData = 0;
    
    // Menu pilihan

    // Arrays untuk menyimpan data tanaman (menggantikan struct)
    vector<string> cropNames;
    vector<int> seedPrices;
    vector<int> growthTimes;
    vector<int> sellingPrices;
    vector<string> growSeasons;
    vector<string> harvestTypes;
    
    // Array tambahan yang dibutuhkan
    vector<string> seasons = {"Spring", "Summer", "Fall"};
    vector<int> cropsPerSeason = {0, 0, 0}; // Jumlah tanaman per musim
    #ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    // Login system
    cout << "===== LOGIN SYSTEM =====" << endl;
    
    while (loginAttempts < 3 && !isLoggedIn) {
        cout << "Masukkan Nama: ";
        cin >> inputName;
        cout << "Masukkan NIM: ";
        cin >> inputNim;
        
        if (inputName == CORRECT_NAME && inputNim == CORRECT_NIM) {
            cout << "Login berhasil!" << endl;
            isLoggedIn = true;
        } else {
            loginAttempts++;
            #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
            cout << "Login gagal! Percobaan ke-" << loginAttempts << " dari 3" << endl;
        }
    }
    
    if (!isLoggedIn) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
        return 0;
        #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    }
    
    cropNames.push_back("Blue Jazz");
    seedPrices.push_back(30);
    growthTimes.push_back(7);
    sellingPrices.push_back(50);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Cauliflower");
    seedPrices.push_back(80);
    growthTimes.push_back(12);
    sellingPrices.push_back(175);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Garlic");
    seedPrices.push_back(40);
    growthTimes.push_back(4);
    sellingPrices.push_back(60);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Kale");
    seedPrices.push_back(70);
    growthTimes.push_back(6);
    sellingPrices.push_back(110);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Parsnip");
    seedPrices.push_back(20);
    growthTimes.push_back(4);
    sellingPrices.push_back(35);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Potato");
    seedPrices.push_back(50);
    growthTimes.push_back(6);
    sellingPrices.push_back(80);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Rhubarb");
    seedPrices.push_back(100);
    growthTimes.push_back(13);
    sellingPrices.push_back(220);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Tulip");
    seedPrices.push_back(20);
    growthTimes.push_back(6);
    sellingPrices.push_back(30);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Unmilled Rice");
    seedPrices.push_back(40);
    growthTimes.push_back(6);
    sellingPrices.push_back(30);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Carrot");
    seedPrices.push_back(0);
    growthTimes.push_back(3);
    sellingPrices.push_back(35);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("single");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Coffee Bean");
    seedPrices.push_back(2500);
    growthTimes.push_back(10);
    sellingPrices.push_back(60);
    growSeasons.push_back("Spring, Summer");
    harvestTypes.push_back("multiple");
    cropsPerSeason[0]++;
    cropsPerSeason[1]++;
    
    cropNames.push_back("Green Bean");
    seedPrices.push_back(60);
    growthTimes.push_back(10);
    sellingPrices.push_back(40);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("multiple");
    cropsPerSeason[0]++;
    
    cropNames.push_back("Strawberry");
    seedPrices.push_back(100);
    growthTimes.push_back(8);
    sellingPrices.push_back(120);
    growSeasons.push_back("Spring");
    harvestTypes.push_back("multiple");
    cropsPerSeason[0]++;
    
    // Data Summer
    cropNames.push_back("Melon");
    seedPrices.push_back(80);
    growthTimes.push_back(12);
    sellingPrices.push_back(250);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Poppy");
    seedPrices.push_back(100);
    growthTimes.push_back(7);
    sellingPrices.push_back(140);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Radish");
    seedPrices.push_back(40);
    growthTimes.push_back(6);
    sellingPrices.push_back(90);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Red Cabbage");
    seedPrices.push_back(100);
    growthTimes.push_back(9);
    sellingPrices.push_back(260);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Starfruit");
    seedPrices.push_back(400);
    growthTimes.push_back(13);
    sellingPrices.push_back(750);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Summer Spangle");
    seedPrices.push_back(50);
    growthTimes.push_back(8);
    sellingPrices.push_back(90);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Wheat");
    seedPrices.push_back(10);
    growthTimes.push_back(4);
    sellingPrices.push_back(25);
    growSeasons.push_back("Summer, Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    cropsPerSeason[2]++;
    
    cropNames.push_back("Sunflower");
    seedPrices.push_back(200);
    growthTimes.push_back(8);
    sellingPrices.push_back(80);
    growSeasons.push_back("Summer, Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[1]++;
    cropsPerSeason[2]++;
    
    cropNames.push_back("Blueberry");
    seedPrices.push_back(80);
    growthTimes.push_back(13);
    sellingPrices.push_back(150);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("multiple");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Corn");
    seedPrices.push_back(150);
    growthTimes.push_back(14);
    sellingPrices.push_back(50);
    growSeasons.push_back("Summer, Fall");
    harvestTypes.push_back("multiple");
    cropsPerSeason[1]++;
    cropsPerSeason[2]++;
    
    cropNames.push_back("Hops");
    seedPrices.push_back(50);
    growthTimes.push_back(11);
    sellingPrices.push_back(25);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("multiple");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Hot Pepper");
    seedPrices.push_back(40);
    growthTimes.push_back(5);
    sellingPrices.push_back(40);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("multiple");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Tomato");
    seedPrices.push_back(50);
    growthTimes.push_back(11);
    sellingPrices.push_back(60);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("multiple");
    cropsPerSeason[1]++;
    
    cropNames.push_back("Summer Squash");
    seedPrices.push_back(0);
    growthTimes.push_back(6);
    sellingPrices.push_back(45);
    growSeasons.push_back("Summer");
    harvestTypes.push_back("multiple");
    cropsPerSeason[1]++;
    
    // Data Fall
    cropNames.push_back("Amaranth");
    seedPrices.push_back(70);
    growthTimes.push_back(7);
    sellingPrices.push_back(150);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Artichoke");
    seedPrices.push_back(30);
    growthTimes.push_back(8);
    sellingPrices.push_back(160);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Beet");
    seedPrices.push_back(20);
    growthTimes.push_back(6);
    sellingPrices.push_back(100);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Bok Choy");
    seedPrices.push_back(50);
    growthTimes.push_back(4);
    sellingPrices.push_back(80);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Fairy Rose");
    seedPrices.push_back(200);
    growthTimes.push_back(12);
    sellingPrices.push_back(290);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Pumpkin");
    seedPrices.push_back(100);
    growthTimes.push_back(13);
    sellingPrices.push_back(320);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Sweet Gem Berry");
    seedPrices.push_back(1000);
    growthTimes.push_back(24);
    sellingPrices.push_back(3000);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Yam");
    seedPrices.push_back(60);
    growthTimes.push_back(10);
    sellingPrices.push_back(160);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("single");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Cranberries");
    seedPrices.push_back(240);
    growthTimes.push_back(7);
    sellingPrices.push_back(75);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("multiple");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Eggplant");
    seedPrices.push_back(20);
    growthTimes.push_back(5);
    sellingPrices.push_back(60);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("multiple");
    cropsPerSeason[2]++;
    
    cropNames.push_back("Grape");
    seedPrices.push_back(60);
    growthTimes.push_back(10);
    sellingPrices.push_back(80);
    growSeasons.push_back("Fall");
    harvestTypes.push_back("multiple");
    cropsPerSeason[2]++;

    // Variabel untuk program utama
    bool running = true;
    int choice;
    #ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    while (running) {
        // Tampilkan menu
        cout << "\n===== STARDEW VALLEY CROPS MANAGER =====" << endl;
        cout << "1. Tampilkan Semua Tanaman" << endl;
        cout << "2. Tambah Tanaman Baru" << endl;
        cout << "3. Perbarui Tanaman" << endl;
        cout << "4. Hapus Tanaman" << endl;
        cout << "5. Cari Tanaman" << endl;
        cout << "6. Keluar" << endl;
        cout << "Pilihan Anda: ";
        
        // Validasi input
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka." << endl;
            continue;
        }
        
        // Proses pilihan menu
        if (choice == 1) {
            // Tampilkan semua tanaman
            #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
            cout << string(36, '=') << " DAFTAR SEMUA TANAMAN " << string(36, '=')  << endl;
            cout << left << setw(5) << "No" << setw(20) << "Nama" 
                 << setw(15) << "Harga Bibit" << setw(15) << "Waktu Tumbuh" 
                 << setw(15) << "Harga Jual" << setw(15) << "Musim" 
                 << setw(10) << "Tipe" << endl;
            cout << string(94, '-') << endl;
            
            for (size_t i = 0; i < cropNames.size(); i++) {
                cout << left << setw(5) << (i + 1)
                     << setw(20) << cropNames[i]
                     << setw(15) << seedPrices[i]
                     << setw(15) << growthTimes[i]
                     << setw(15) << sellingPrices[i]
                     << setw(15) << growSeasons[i]
                     << setw(10) << harvestTypes[i] << endl;
            }
            
            // Tampilkan statistik
            cout << "\nStatistik Tanaman per Musim:" << endl;
            for (size_t i = 0; i < seasons.size(); i++) {
                cout << seasons[i] << ": " << cropsPerSeason[i] << " tanaman" << endl;
            }
        }
        else if (choice == 2) {
            // Tambah tanaman baru
            string nama;
            int hargaBibit, waktuTumbuh, hargaJual;
            string musimTanam, tipeHarvest;
            
            cin.ignore();
            cout << "\n===== TAMBAH TANAMAN BARU =====" << endl;
            cout << "Nama Tanaman: ";
            getline(cin, nama);
            
            cout << "Harga Bibit: ";
            cin >> hargaBibit;
            
            cout << "Waktu Tumbuh (hari): ";
            cin >> waktuTumbuh;
            
            cout << "Harga Jual: ";
            cin >> hargaJual;
            
            cin.ignore();
            cout << "Musim Tanam (Spring/Summer/Fall): ";
            getline(cin, musimTanam);
            
            cout << "Tipe Harvest (single/multiple): ";
            getline(cin, tipeHarvest);
            
            // Tambahkan data ke array
            cropNames.push_back(nama);
            seedPrices.push_back(hargaBibit);
            growthTimes.push_back(waktuTumbuh);
            sellingPrices.push_back(hargaJual);
            growSeasons.push_back(musimTanam);
            harvestTypes.push_back(tipeHarvest);
            
            // Update statistik
            if (musimTanam == "Spring") {
                cropsPerSeason[0]++;
            } else if (musimTanam == "Summer") {
                cropsPerSeason[1]++;
            } else if (musimTanam == "Fall") {
                cropsPerSeason[2]++;
            } else if (musimTanam == "Summer, Fall") {
                cropsPerSeason[1]++;
                cropsPerSeason[2]++;
            }
            
            cout << "Tanaman berhasil ditambahkan!" << endl;
        }
        else if (choice == 3) {
            // Perbarui tanaman
            int index;
            
            cout << "\n===== PERBARUI TANAMAN =====" << endl;
            cout << "Daftar Tanaman:" << endl;
            for (size_t i = 0; i < cropNames.size(); i++) {
                cout << (i + 1) << ". " << cropNames[i] << endl;
            }
            
            cout << "Masukkan nomor tanaman yang ingin diperbarui: ";
            cin >> index;
            
            if (index < 1 || index > static_cast<int>(cropNames.size())) {
                cout << "Nomor tanaman tidak valid!" << endl;
                continue;
            }
            
            index--;
            
            if (growSeasons[index] == "Spring") {
                cropsPerSeason[0]--;
            } else if (growSeasons[index] == "Summer") {
                cropsPerSeason[1]--;
            } else if (growSeasons[index] == "Fall") {
                cropsPerSeason[2]--;
            } else if (growSeasons[index] == "Summer, Fall") {
                cropsPerSeason[1]--;
                cropsPerSeason[2]--;
            }
            
            cin.ignore();
            cout << "Nama Tanaman [" << cropNames[index] << "]: ";
            string input;
            getline(cin, input);
            if (!input.empty()) {
                cropNames[index] = input;
            }
            
            cout << "Harga Bibit [" << seedPrices[index] << "]: ";
            string priceInput;
            getline(cin, priceInput);
            if (!priceInput.empty()) {
                seedPrices[index] = stoi(priceInput);
            }
            
            cout << "Waktu Tumbuh [" << growthTimes[index] << "]: ";
            string growthInput;
            getline(cin, growthInput);
            if (!growthInput.empty()) {
                growthTimes[index] = stoi(growthInput);
            }
            
            cout << "Harga Jual [" << sellingPrices[index] << "]: ";
            string sellInput;
            getline(cin, sellInput);
            if (!sellInput.empty()) {
                sellingPrices[index] = stoi(sellInput);
            }
            
            cout << "Musim Tanam [" << growSeasons[index] << "]: ";
            string seasonInput;
            getline(cin, seasonInput);
            if (!seasonInput.empty()) {
                growSeasons[index] = seasonInput;
            }
            
            cout << "Tipe Harvest [" << harvestTypes[index] << "]: ";
            string typeInput;
            getline(cin, typeInput);
            if (!typeInput.empty()) {
                harvestTypes[index] = typeInput;
            }
            
            // Update statistik untuk musim baru
            if (growSeasons[index] == "Spring") {
                cropsPerSeason[0]++;
            } else if (growSeasons[index] == "Summer") {
                cropsPerSeason[1]++;
            } else if (growSeasons[index] == "Fall") {
                cropsPerSeason[2]++;
            } else if (growSeasons[index] == "Summer, Fall") {
                cropsPerSeason[1]++;
                cropsPerSeason[2]++;
            }
            
            cout << "Tanaman berhasil diperbarui!" << endl;
        }
        else if (choice == 4) {
            // Hapus tanaman
            int index;
            
            cout << "\n===== HAPUS TANAMAN =====" << endl;
            
            // Tampilkan daftar singkat untuk referensi
            cout << "Daftar Tanaman:" << endl;
            for (size_t i = 0; i < cropNames.size(); i++) {
                cout << (i + 1) << ". " << cropNames[i] << endl;
            }
            
            cout << "Masukkan nomor tanaman yang ingin dihapus: ";
            cin >> index;
            
            if (index < 1 || index > static_cast<int>(cropNames.size())) {
                cout << "Nomor tanaman tidak valid!" << endl;
                continue;
            }
            
            index--; // Konversi ke indeks array (0-based)
            
            // Hapus dari statistik
            if (growSeasons[index] == "Spring") {
                cropsPerSeason[0]--;
            } else if (growSeasons[index] == "Summer") {
                cropsPerSeason[1]--;
            } else if (growSeasons[index] == "Fall") {
                cropsPerSeason[2]--;
            } else if (growSeasons[index] == "Summer, Fall") {
                cropsPerSeason[1]--;
                cropsPerSeason[2]--;
            }
            
            cout << "Tanaman " << cropNames[index] << " akan dihapus. Lanjutkan? (y/n): ";
            char confirmation;
            cin >> confirmation;
            
            if (confirmation == 'y' || confirmation == 'Y') {
                // Hapus data dari semua array
                cropNames.erase(cropNames.begin() + index);
                seedPrices.erase(seedPrices.begin() + index);
                growthTimes.erase(growthTimes.begin() + index);
                sellingPrices.erase(sellingPrices.begin() + index);
                growSeasons.erase(growSeasons.begin() + index);
                harvestTypes.erase(harvestTypes.begin() + index);
                
                cout << "Tanaman berhasil dihapus!" << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
        else if (choice == 5) {
            // Cari tanaman
            string searchTerm;
            bool found = false;
            
            cout << "\n===== CARI TANAMAN =====" << endl;
            cout << "1. Cari berdasarkan nama" << endl;
            cout << "2. Cari berdasarkan musim" << endl;
            cout << "3. Cari berdasarkan tipe harvest" << endl;
            cout << "Pilihan: ";
            
            int searchChoice;
            cin >> searchChoice;
            cin.ignore();
            
            if (searchChoice == 1) {
                cout << "Masukkan nama tanaman: ";
                getline(cin, searchTerm);
                
                cout << "\nHasil Pencarian untuk '" << searchTerm << "':" << endl;
                cout << left << setw(5) << "No" << setw(20) << "Nama" 
                     << setw(15) << "Harga Bibit" << setw(15) << "Waktu Tumbuh" 
                     << setw(15) << "Harga Jual" << setw(15) << "Musim" 
                     << setw(10) << "Tipe" << endl;
                cout << string(95, '-') << endl;
                
                int count = 0;
                for (size_t i = 0; i < cropNames.size(); i++) {
                    // Pencarian sederhana (case-insensitive tidak diimplementasikan)
                    if (cropNames[i].find(searchTerm) != string::npos) {
                        count++;
                        cout << left << setw(5) << count
                             << setw(20) << cropNames[i]
                             << setw(15) << seedPrices[i]
                             << setw(15) << growthTimes[i]
                             << setw(15) << sellingPrices[i]
                             << setw(15) << growSeasons[i]
                             << setw(10) << harvestTypes[i] << endl;
                        found = true;
                    }
                }
            }
            else if (searchChoice == 2) {
                cout << "Masukkan musim (Spring/Summer/Fall): ";
                getline(cin, searchTerm);
                
                cout << "\nHasil Pencarian untuk musim '" << searchTerm << "':" << endl;
                cout << left << setw(5) << "No" << setw(20) << "Nama" 
                     << setw(15) << "Harga Bibit" << setw(15) << "Waktu Tumbuh" 
                     << setw(15) << "Harga Jual" << setw(15) << "Musim" 
                     << setw(10) << "Tipe" << endl;
                cout << string(95, '-') << endl;
                
                int count = 0;
                for (size_t i = 0; i < cropNames.size(); i++) {
                    if (growSeasons[i].find(searchTerm) != string::npos) {
                        count++;
                        cout << left << setw(5) << count
                             << setw(20) << cropNames[i]
                             << setw(15) << seedPrices[i]
                             << setw(15) << growthTimes[i]
                             << setw(15) << sellingPrices[i]
                             << setw(15) << growSeasons[i]
                             << setw(10) << harvestTypes[i] << endl;
                        found = true;
                    }
                }
            }
            else if (searchChoice == 3) {
                cout << "Masukkan tipe harvest (single/multiple): ";
                getline(cin, searchTerm);
                
                cout << "\nHasil Pencarian untuk tipe '" << searchTerm << "':" << endl;
                cout << left << setw(5) << "No" << setw(20) << "Nama" 
                     << setw(15) << "Harga Bibit" << setw(15) << "Waktu Tumbuh" 
                     << setw(15) << "Harga Jual" << setw(15) << "Musim" 
                     << setw(10) << "Tipe" << endl;
                cout << string(95, '-') << endl;
                
                int count = 0;
                for (size_t i = 0; i < cropNames.size(); i++) {
                    if (harvestTypes[i] == searchTerm) {
                        count++;
                        cout << left << setw(5) << count
                             << setw(20) << cropNames[i]
                             << setw(15) << seedPrices[i]
                             << setw(15) << growthTimes[i]
                             << setw(15) << sellingPrices[i]
                             << setw(15) << growSeasons[i]
                             << setw(10) << harvestTypes[i] << endl;
                        found = true;
                    }
                }
            }
            else {
                cout << "Pilihan pencarian tidak valid!" << endl;
                continue;
            }
            
            if (!found) {
                cout << "Tidak ada hasil yang ditemukan." << endl;
            }
        }
        else if (choice == 6) {
            // Keluar dari program
            cout << "Terima kasih telah menggunakan program Stardew Valley Crops Manager!" << endl;
            running = false;
        }
        else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
    }
    
    return 0;
}