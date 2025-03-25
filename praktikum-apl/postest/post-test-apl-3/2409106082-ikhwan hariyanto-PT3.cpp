#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

// Struct to store crop data
struct Crop {
    string name;
    int seedPrice;
    int growthTime;
    int sellingPrice;
    string growSeason;
    string harvestType;
};

// Struct for user credentials (for multi-user support)
struct User {
    string name;
    string nim;
    bool isActive = false;
};

int main() {
    // Predefined login credentials for main user
    const string CORRECT_NAME = "ikhwanhariyanto";
    const string CORRECT_NIM = "2409106082";
    
    // Variables for login
    string inputName, inputNim;
    int loginAttempts = 0;
    bool isLoggedIn = false;
    
    // Array to store users (for multi-user support)
    vector<User> users;
    
    // Add default user
    User defaultUser;
    defaultUser.name = CORRECT_NAME;
    defaultUser.nim = CORRECT_NIM;
    defaultUser.isActive = true;
    users.push_back(defaultUser);
    
    // Array to store crops data using struct
    vector<Crop> crops;
    
    // Additional data needed
    vector<string> seasons = {"Spring", "Summer", "Fall"};
    vector<int> cropsPerSeason = {0, 0, 0}; // Number of crops per season
    
    // Clear screen
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
        
        // Check login against all users
        for (const User& user : users) {
            if (inputName == user.name && inputNim == user.nim) {
                cout << "Login berhasil!" << endl;
                isLoggedIn = true;
                break;
            }
        }
        
        if (!isLoggedIn) {
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
    }
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    // Initialize predefined crop data
    // Spring crops
    crops.push_back({"Blue Jazz", 30, 7, 50, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Cauliflower", 80, 12, 175, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Garlic", 40, 4, 60, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Kale", 70, 6, 110, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Parsnip", 20, 4, 35, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Potato", 50, 6, 80, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Rhubarb", 100, 13, 220, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Tulip", 20, 6, 30, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Unmilled Rice", 40, 6, 30, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Carrot", 0, 3, 35, "Spring", "single"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Coffee Bean", 2500, 10, 60, "Spring, Summer", "multiple"});
    cropsPerSeason[0]++;
    cropsPerSeason[1]++;
    
    crops.push_back({"Green Bean", 60, 10, 40, "Spring", "multiple"});
    cropsPerSeason[0]++;
    
    crops.push_back({"Strawberry", 100, 8, 120, "Spring", "multiple"});
    cropsPerSeason[0]++;
    
    // Summer crops
    crops.push_back({"Melon", 80, 12, 250, "Summer", "single"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Poppy", 100, 7, 140, "Summer", "single"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Radish", 40, 6, 90, "Summer", "single"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Red Cabbage", 100, 9, 260, "Summer", "single"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Starfruit", 400, 13, 750, "Summer", "single"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Summer Spangle", 50, 8, 90, "Summer", "single"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Wheat", 10, 4, 25, "Summer, Fall", "single"});
    cropsPerSeason[1]++;
    cropsPerSeason[2]++;
    
    crops.push_back({"Sunflower", 200, 8, 80, "Summer, Fall", "single"});
    cropsPerSeason[1]++;
    cropsPerSeason[2]++;
    
    crops.push_back({"Blueberry", 80, 13, 150, "Summer", "multiple"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Corn", 150, 14, 50, "Summer, Fall", "multiple"});
    cropsPerSeason[1]++;
    cropsPerSeason[2]++;
    
    crops.push_back({"Hops", 50, 11, 25, "Summer", "multiple"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Hot Pepper", 40, 5, 40, "Summer", "multiple"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Tomato", 50, 11, 60, "Summer", "multiple"});
    cropsPerSeason[1]++;
    
    crops.push_back({"Summer Squash", 0, 6, 45, "Summer", "multiple"});
    cropsPerSeason[1]++;
    
    // Fall crops
    crops.push_back({"Amaranth", 70, 7, 150, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Artichoke", 30, 8, 160, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Beet", 20, 6, 100, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Bok Choy", 50, 4, 80, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Fairy Rose", 200, 12, 290, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Pumpkin", 100, 13, 320, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Sweet Gem Berry", 1000, 24, 3000, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Yam", 60, 10, 160, "Fall", "single"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Cranberries", 240, 7, 75, "Fall", "multiple"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Eggplant", 20, 5, 60, "Fall", "multiple"});
    cropsPerSeason[2]++;
    
    crops.push_back({"Grape", 60, 10, 80, "Fall", "multiple"});
    cropsPerSeason[2]++;

    // Variables for main program
    bool running = true;
    int choice;
    
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    while (running) {
        // Display menu
        cout << "\n===== STARDEW VALLEY CROPS MANAGER =====" << endl;
        cout << "1. Tampilkan Semua Tanaman" << endl;
        cout << "2. Tambah Tanaman Baru" << endl;
        cout << "3. Perbarui Tanaman" << endl;
        cout << "4. Hapus Tanaman" << endl;
        cout << "5. Cari Tanaman" << endl;
        cout << "6. Daftar Pengguna Baru" << endl;  // New option for registration
        cout << "7. Keluar" << endl;
        cout << "Pilihan Anda: ";
        
        // Input validation
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input tidak valid! Masukkan angka." << endl;
            continue;
        }
        
        // Process menu choice
        if (choice == 1) {
            // Display all crops
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
            
            for (size_t i = 0; i < crops.size(); i++) {
                cout << left << setw(5) << (i + 1)
                     << setw(20) << crops[i].name
                     << setw(15) << crops[i].seedPrice
                     << setw(15) << crops[i].growthTime
                     << setw(15) << crops[i].sellingPrice
                     << setw(15) << crops[i].growSeason
                     << setw(10) << crops[i].harvestType << endl;
            }
            
            // Display statistics
            cout << "\nStatistik Tanaman per Musim:" << endl;
            for (size_t i = 0; i < seasons.size(); i++) {
                cout << seasons[i] << ": " << cropsPerSeason[i] << " tanaman" << endl;
            }
        }
        else if (choice == 2) {
            // Add new crop
            Crop newCrop;
            
            cin.ignore();
            cout << "\n===== TAMBAH TANAMAN BARU =====" << endl;
            cout << "Nama Tanaman: ";
            getline(cin, newCrop.name);
            
            cout << "Harga Bibit: ";
            cin >> newCrop.seedPrice;
            
            cout << "Waktu Tumbuh (hari): ";
            cin >> newCrop.growthTime;
            
            cout << "Harga Jual: ";
            cin >> newCrop.sellingPrice;
            
            cin.ignore();
            cout << "Musim Tanam (Spring/Summer/Fall): ";
            getline(cin, newCrop.growSeason);
            
            cout << "Tipe Harvest (single/multiple): ";
            getline(cin, newCrop.harvestType);
            
            // Add data to array
            crops.push_back(newCrop);
            
            // Update statistics
            if (newCrop.growSeason == "Spring") {
                cropsPerSeason[0]++;
            } else if (newCrop.growSeason == "Summer") {
                cropsPerSeason[1]++;
            } else if (newCrop.growSeason == "Fall") {
                cropsPerSeason[2]++;
            } else if (newCrop.growSeason == "Summer, Fall") {
                cropsPerSeason[1]++;
                cropsPerSeason[2]++;
            }
            
            cout << "Tanaman berhasil ditambahkan!" << endl;
        }
        else if (choice == 3) {
            // Update crop
            int index;
            
            cout << "\n===== PERBARUI TANAMAN =====" << endl;
            cout << "Daftar Tanaman:" << endl;
            for (size_t i = 0; i < crops.size(); i++) {
                cout << (i + 1) << ". " << crops[i].name << endl;
            }
            
            cout << "Masukkan nomor tanaman yang ingin diperbarui: ";
            cin >> index;
            
            if (index < 1 || index > static_cast<int>(crops.size())) {
                cout << "Nomor tanaman tidak valid!" << endl;
                continue;
            }
            
            index--; // Convert to array index (0-based)
            
            // Decrease previous season count
            if (crops[index].growSeason == "Spring") {
                cropsPerSeason[0]--;
            } else if (crops[index].growSeason == "Summer") {
                cropsPerSeason[1]--;
            } else if (crops[index].growSeason == "Fall") {
                cropsPerSeason[2]--;
            } else if (crops[index].growSeason == "Summer, Fall") {
                cropsPerSeason[1]--;
                cropsPerSeason[2]--;
            }
            
            cin.ignore();
            cout << "Nama Tanaman [" << crops[index].name << "]: ";
            string input;
            getline(cin, input);
            if (!input.empty()) {
                crops[index].name = input;
            }
            
            cout << "Harga Bibit [" << crops[index].seedPrice << "]: ";
            string priceInput;
            getline(cin, priceInput);
            if (!priceInput.empty()) {
                crops[index].seedPrice = stoi(priceInput);
            }
            
            cout << "Waktu Tumbuh [" << crops[index].growthTime << "]: ";
            string growthInput;
            getline(cin, growthInput);
            if (!growthInput.empty()) {
                crops[index].growthTime = stoi(growthInput);
            }
            
            cout << "Harga Jual [" << crops[index].sellingPrice << "]: ";
            string sellInput;
            getline(cin, sellInput);
            if (!sellInput.empty()) {
                crops[index].sellingPrice = stoi(sellInput);
            }
            
            cout << "Musim Tanam [" << crops[index].growSeason << "]: ";
            string seasonInput;
            getline(cin, seasonInput);
            if (!seasonInput.empty()) {
                crops[index].growSeason = seasonInput;
            }
            
            cout << "Tipe Harvest [" << crops[index].harvestType << "]: ";
            string typeInput;
            getline(cin, typeInput);
            if (!typeInput.empty()) {
                crops[index].harvestType = typeInput;
            }
            
            // Update statistics for new season
            if (crops[index].growSeason == "Spring") {
                cropsPerSeason[0]++;
            } else if (crops[index].growSeason == "Summer") {
                cropsPerSeason[1]++;
            } else if (crops[index].growSeason == "Fall") {
                cropsPerSeason[2]++;
            } else if (crops[index].growSeason == "Summer, Fall") {
                cropsPerSeason[1]++;
                cropsPerSeason[2]++;
            }
            
            cout << "Tanaman berhasil diperbarui!" << endl;
        }
        else if (choice == 4) {
            // Delete crop
            int index;
            
            cout << "\n===== HAPUS TANAMAN =====" << endl;
            
            // Display brief list for reference
            cout << "Daftar Tanaman:" << endl;
            for (size_t i = 0; i < crops.size(); i++) {
                cout << (i + 1) << ". " << crops[i].name << endl;
            }
            
            cout << "Masukkan nomor tanaman yang ingin dihapus: ";
            cin >> index;
            
            if (index < 1 || index > static_cast<int>(crops.size())) {
                cout << "Nomor tanaman tidak valid!" << endl;
                continue;
            }
            
            index--; // Convert to array index (0-based)
            
            // Remove from statistics
            if (crops[index].growSeason == "Spring") {
                cropsPerSeason[0]--;
            } else if (crops[index].growSeason == "Summer") {
                cropsPerSeason[1]--;
            } else if (crops[index].growSeason == "Fall") {
                cropsPerSeason[2]--;
            } else if (crops[index].growSeason == "Summer, Fall") {
                cropsPerSeason[1]--;
                cropsPerSeason[2]--;
            }
            
            cout << "Tanaman " << crops[index].name << " akan dihapus. Lanjutkan? (y/n): ";
            char confirmation;
            cin >> confirmation;
            
            if (confirmation == 'y' || confirmation == 'Y') {
                // Delete data from all arrays
                crops.erase(crops.begin() + index);
                
                cout << "Tanaman berhasil dihapus!" << endl;
            } else {
                cout << "Penghapusan dibatalkan." << endl;
            }
        }
        else if (choice == 5) {
            // Search for crops
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
                for (size_t i = 0; i < crops.size(); i++) {
                    // Simple search (case-insensitive not implemented)
                    if (crops[i].name.find(searchTerm) != string::npos) {
                        count++;
                        cout << left << setw(5) << count
                             << setw(20) << crops[i].name
                             << setw(15) << crops[i].seedPrice
                             << setw(15) << crops[i].growthTime
                             << setw(15) << crops[i].sellingPrice
                             << setw(15) << crops[i].growSeason
                             << setw(10) << crops[i].harvestType << endl;
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
                for (size_t i = 0; i < crops.size(); i++) {
                    if (crops[i].growSeason.find(searchTerm) != string::npos) {
                        count++;
                        cout << left << setw(5) << count
                             << setw(20) << crops[i].name
                             << setw(15) << crops[i].seedPrice
                             << setw(15) << crops[i].growthTime
                             << setw(15) << crops[i].sellingPrice
                             << setw(15) << crops[i].growSeason
                             << setw(10) << crops[i].harvestType << endl;
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
                for (size_t i = 0; i < crops.size(); i++) {
                    if (crops[i].harvestType == searchTerm) {
                        count++;
                        cout << left << setw(5) << count
                             << setw(20) << crops[i].name
                             << setw(15) << crops[i].seedPrice
                             << setw(15) << crops[i].growthTime
                             << setw(15) << crops[i].sellingPrice
                             << setw(15) << crops[i].growSeason
                             << setw(10) << crops[i].harvestType << endl;
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
            // New user registration
            User newUser;
            
            cin.ignore();
            cout << "\n===== DAFTAR PENGGUNA BARU =====" << endl;
            cout << "Masukkan Nama: ";
            getline(cin, newUser.name);
            
            cout << "Masukkan NIM: ";
            getline(cin, newUser.nim);
            
            // Check if user already exists
            bool userExists = false;
            for (const User& user : users) {
                if (user.name == newUser.name && user.nim == newUser.nim) {
                    userExists = true;
                    break;
                }
            }
            
            if (userExists) {
                cout << "Pengguna sudah terdaftar!" << endl;
            } else {
                newUser.isActive = true;
                users.push_back(newUser);
                cout << "Pengguna berhasil terdaftar!" << endl;
            }
        }
        else if (choice == 7) {
            // Exit program
            cout << "Terima kasih telah menggunakan program Stardew Valley Crops Manager!" << endl;
            running = false;
        }
        else {
            cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        
        // Pause before showing menu again
        if (running) {
            cout << "\nTekan Enter untuk lanjut...";
            cin.ignore();
            cin.get();
            
            #ifdef _WIN32
                system("cls");
            #else
                system("clear");
            #endif
        }
    }
    
    return 0;
}