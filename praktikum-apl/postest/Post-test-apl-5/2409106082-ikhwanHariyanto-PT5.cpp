#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>

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


struct User {
    string name;
    string nim;
    bool isActive = false;
};

// Global variables
vector<User> users;
vector<Crop> crops;
vector<string> seasons = {"Spring", "Summer", "Fall"};
vector<int> cropsPerSeason = {0, 0, 0}; // Number of crops per season

// Function prototypes
bool loginSystem();
void registerUser();
void initializeCrops();
void displayAllCrops();
void addNewCrop();
void updateCrop();
void deleteCrop();
void searchCrop();
void clearScreen();
void pauseScreen();
void simpanPengguna();
void muatPengguna();
void simpanCrops();
void muatCrops();

// New function using pointers
void displayCropByPointer(const Crop* cropPtr);
void displayCropByPointer(const Crop* cropPtr, int index);
void updateCropByPointer(Crop* cropPtr);
void updateSeasonsStats(string* seasonPtr, vector<int>* statsPtr);
void swapCrops(Crop* crop1, Crop* crop2);
int calculateProfitByPtr(const Crop* cropPtr, int days, int plantCount = 1);
void incrementSeasonCount(vector<int>* seasonCountPtr, const string& season);
void decrementSeasonCount(vector<int>* seasonCountPtr, const string& season);
void processCropInput(int* valuePtr);
bool validateIndex(int* indexPtr, int maxSize);

// Function overloading examples
void displayStats(const vector<int>& stats, const vector<string>& labels);
void displayStats(const string& title, const vector<int>& stats, const vector<string>& labels);
void displayCrop(const Crop& crop);
void displayCrop(const Crop& crop, int index);

// Recursive function to calculate profit
int calculateProfit(const Crop& crop, int days, int plantCount = 1);

int main() {
    // Load saved data
    muatPengguna();
    
              //If no users exist, add default user
    if (users.empty()) {
        // Predefined login credentials for main user
        const string CORRECT_NAME = "ikhwanhariyanto";
        const string CORRECT_NIM = "2409106082";
        
        // Add default user
        User defaultUser;
        defaultUser.name = CORRECT_NAME;
        defaultUser.nim = CORRECT_NIM;
        defaultUser.isActive = true;
        users.push_back(defaultUser);
        
        // Save the default user
        simpanPengguna();
    }
    
    // Initialize crops data
    initializeCrops();
    
    // Clear screen
    clearScreen();

    // Login system
    if (!loginSystem()) {
        cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
        return 0;
    }
    
    clearScreen();

    // Variables for main program
    bool running = true;
    int choice;

    while (running) {
        // Display menu
        cout << "\n===== STARDEW VALLEY CROPS MANAGER =====" << endl;
        cout << "1. Tampilkan Semua Tanaman" << endl;
        cout << "2. Tambah Tanaman Baru" << endl;
        cout << "3. Perbarui Tanaman" << endl;
        cout << "4. Hapus Tanaman" << endl;
        cout << "5. Cari Tanaman" << endl;
        cout << "6. Daftar Pengguna Baru" << endl;
        cout << "7. Urutkan Tanaman" << endl;  // New option for sorting using pointers
        cout << "8. Simpan Data" << endl;
        cout << "9. Keluar" << endl;
        cout << "Pilihan Anda: ";
        
        // Input validation using pointer
        processCropInput(&choice);
        
        // Process menu choice
        switch (choice) {
            case 1:
                displayAllCrops();
                break;
            case 2:
                addNewCrop();
                break;
            case 3:
                updateCrop();
                break;
            case 4:
                deleteCrop();
                break;
            case 5:
                searchCrop();
                break;
            case 6:
                registerUser();
                break;
            case 7: {
                // Sort crops by profit (using pointers)
                cout << "\n===== URUTKAN TANAMAN =====" << endl;
                cout << "Mengurutkan tanaman berdasarkan keuntungan..." << endl;
                
                // Simple bubble sort using pointers
                for (size_t i = 0; i < crops.size() - 1; i++) {
                    for (size_t j = 0; j < crops.size() - i - 1; j++) {
                        int profit1 = calculateProfitByPtr(&crops[j], 28);
                        int profit2 = calculateProfitByPtr(&crops[j + 1], 28);
                        
                        if (profit1 < profit2) {
                            swapCrops(&crops[j], &crops[j + 1]);
                        }
                    }
                }
                
                cout << "Tanaman berhasil diurutkan berdasarkan keuntungan!" << endl;
                cout << "Gunakan pilihan '1' untuk melihat hasil pengurutan." << endl;
                break;
            }
            case 8:
                simpanPengguna();
                simpanCrops();
                cout << "Data berhasil disimpan!" << endl;
                break;
            case 9:
                cout << "Menyimpan data sebelum keluar..." << endl;
                simpanPengguna();
                simpanCrops();
                cout << "Terima kasih telah menggunakan program Stardew Valley Crops Manager!" << endl;
                running = false;
                break;
            default:
                cout << "Pilihan tidak valid. Silakan coba lagi." << endl;
        }
        
        // Pause before showing menu again
        if (running) {
            pauseScreen();
            clearScreen();
        }
    }
    
    return 0;
}

// New function to validate input using pointer
void processCropInput(int* valuePtr) {
    if (!(cin >> *valuePtr)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid! Masukkan angka." << endl;
        *valuePtr = 0; // Set default value
    }
}

// New function to validate index using pointer (returns boolean)
bool validateIndex(int* indexPtr, int maxSize) {
    if (*indexPtr < 1 || *indexPtr > maxSize) {
        cout << "Nomor tanaman tidak valid!" << endl;
        return false;
    }
    
    // Adjust index to 0-based
    (*indexPtr)--;
    return true;
}

// Function to handle the login system
bool loginSystem() {
    string inputName, inputNim;
    int loginAttempts = 0;
    bool isLoggedIn = false;
    
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
            clearScreen();
            
            cout << "Login gagal! Percobaan ke-" << loginAttempts << " dari 3" << endl;
        }
    }
    
    return isLoggedIn;
}

// Procedure to register a new user
void registerUser() {
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
        
        // Save user data immediately after registration
        simpanPengguna();
        
        cout << "Pengguna berhasil terdaftar!" << endl;
    }
}

// Procedure to initialize predefined crops
void initializeCrops() {
    // Try to load crops from file first
    muatCrops();
    
    // Only initialize if no crops were loaded
    if (crops.empty()) {
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
    }
}

// Procedure to display all crops
void displayAllCrops() {
    clearScreen();
    
    cout << string(36, '=') << " DAFTAR SEMUA TANAMAN " << string(36, '=')  << endl;
    cout << left << setw(5) << "No" << setw(20) << "Nama" 
         << setw(15) << "Harga Bibit" << setw(15) << "Waktu Tumbuh" 
         << setw(15) << "Harga Jual" << setw(15) << "Musim" 
         << setw(10) << "Tipe" << setw(15) << "Profit (28 hari)" << endl;
    cout << string(110, '-') << endl;
    
    for (size_t i = 0; i < crops.size(); i++) {
        // Using pointer version of displayCrop
        displayCropByPointer(&crops[i], i + 1);
    }
    
    // Display statistics
    cout << "\nStatistik Tanaman per Musim:" << endl;
    displayStats(cropsPerSeason, seasons);
}

// Procedure to add a new crop
void addNewCrop() {
    Crop newCrop;
    
    cin.ignore();
    cout << "\n===== TAMBAH TANAMAN BARU =====" << endl;
    cout << "Nama Tanaman: ";
    getline(cin, newCrop.name);
    
    cout << "Harga Bibit: ";
    processCropInput(&newCrop.seedPrice);
    
    cout << "Waktu Tumbuh (hari): ";
    processCropInput(&newCrop.growthTime);
    
    cout << "Harga Jual: ";
    processCropInput(&newCrop.sellingPrice);
    
    cin.ignore();
    cout << "Musim Tanam (Spring/Summer/Fall): ";
    getline(cin, newCrop.growSeason);
    
    cout << "Tipe Harvest (single/multiple): ";
    getline(cin, newCrop.harvestType);
    
    // Add data to array
    crops.push_back(newCrop);
    
    // Update statistics using a pointer
    incrementSeasonCount(&cropsPerSeason, newCrop.growSeason);
    
    cout << "Tanaman berhasil ditambahkan!" << endl;
    
    // Show profit calculation using our pointer function
    int plantDays = 28; // Typical season length
    cout << "Perkiraan keuntungan dalam " << plantDays << " hari: " 
         << calculateProfitByPtr(&newCrop, plantDays) << " gold" << endl;
}

// Procedure to update a crop
void updateCrop() {
    int index;
    
    cout << "\n===== PERBARUI TANAMAN =====" << endl;
    cout << "Daftar Tanaman:" << endl;
    for (size_t i = 0; i < crops.size(); i++) {
        cout << (i + 1) << ". " << crops[i].name << endl;
    }
    
    cout << "Masukkan nomor tanaman yang ingin diperbarui: ";
    cin >> index;
    
    // Validate index using pointer function
    if (!validateIndex(&index, crops.size())) {
        return;
    }
    
    // Decrease previous season count
    decrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
    
    // Update crop using pointer function
    Crop* cropPtr = &crops[index];
    updateCropByPointer(cropPtr);
    
    // Update statistics for new season
    incrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
    
    cout << "Tanaman berhasil diperbarui!" << endl;
}

// New function to update crop by pointer (parameter dereference)
void updateCropByPointer(Crop* cropPtr) {
    cin.ignore();
    cout << "Nama Tanaman [" << cropPtr->name << "]: ";
    string input;
    getline(cin, input);
    if (!input.empty()) {
        cropPtr->name = input;
    }
    
    cout << "Harga Bibit [" << cropPtr->seedPrice << "]: ";
    string priceInput;
    getline(cin, priceInput);
    if (!priceInput.empty()) {
        cropPtr->seedPrice = stoi(priceInput);
    }
    
    cout << "Waktu Tumbuh [" << cropPtr->growthTime << "]: ";
    string growthInput;
    getline(cin, growthInput);
    if (!growthInput.empty()) {
        cropPtr->growthTime = stoi(growthInput);
    }
    
    cout << "Harga Jual [" << cropPtr->sellingPrice << "]: ";
    string sellInput;
    getline(cin, sellInput);
    if (!sellInput.empty()) {
        cropPtr->sellingPrice = stoi(sellInput);
    }
    
    cout << "Musim Tanam [" << cropPtr->growSeason << "]: ";
    string seasonInput;
    getline(cin, seasonInput);
    if (!seasonInput.empty()) {
        cropPtr->growSeason = seasonInput;
    }
    
    cout << "Tipe Harvest [" << cropPtr->harvestType << "]: ";
    string typeInput;
    getline(cin, typeInput);
    if (!typeInput.empty()) {
        cropPtr->harvestType = typeInput;
    }
}

// Procedure to delete a crop
void deleteCrop() {
    int index;
    
    cout << "\n===== HAPUS TANAMAN =====" << endl;
    
    // Display brief list for reference
    cout << "Daftar Tanaman:" << endl;
    for (size_t i = 0; i < crops.size(); i++) {
        cout << (i + 1) << ". " << crops[i].name << endl;
    }
    
    cout << "Masukkan nomor tanaman yang ingin dihapus: ";
    cin >> index;
    
    // Validate index using pointer function
    if (!validateIndex(&index, crops.size())) {
        return;
    }
    
    // Remove from statistics using pointer function
    decrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
    
    cout << "Tanaman " << crops[index].name << " akan dihapus. Lanjutkan? (y/n): ";
    char confirmation;
    cin >> confirmation;
    
    if (confirmation == 'y' || confirmation == 'Y') {
        // Delete data from all arrays
        crops.erase(crops.begin() + index);
        cout << "Tanaman berhasil dihapus!" << endl;
    } else {
        cout << "Penghapusan dibatalkan." << endl;
        
        // Restore statistics since deletion was cancelled
        incrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
    }
}

// Function to increment season count using pointer (parameter address-of)
void incrementSeasonCount(vector<int>* seasonCountPtr, const string& season) {
    if (season == "Spring") {
        (*seasonCountPtr)[0]++;
    } else if (season == "Summer") {
        (*seasonCountPtr)[1]++;
    } else if (season == "Fall") {
        (*seasonCountPtr)[2]++;
    } else if (season == "Spring, Summer") {
        (*seasonCountPtr)[0]++;
        (*seasonCountPtr)[1]++;
    } else if (season == "Summer, Fall") {
        (*seasonCountPtr)[1]++;
        (*seasonCountPtr)[2]++;
    } else if (season == "Spring, Fall") {
        (*seasonCountPtr)[0]++;
        (*seasonCountPtr)[2]++;
    }
}

// Function to decrement season count using pointer (parameter address-of)
void decrementSeasonCount(vector<int>* seasonCountPtr, const string& season) {
    if (season == "Spring") {
        (*seasonCountPtr)[0]--;
    } else if (season == "Summer") {
        (*seasonCountPtr)[1]--;
    } else if (season == "Fall") {
        (*seasonCountPtr)[2]--;
    } else if (season == "Spring, Summer") {
        (*seasonCountPtr)[0]--;
        (*seasonCountPtr)[1]--;
    } else if (season == "Summer, Fall") {
        (*seasonCountPtr)[1]--;
        (*seasonCountPtr)[2]--;
    } else if (season == "Spring, Fall") {
        (*seasonCountPtr)[0]--;
        (*seasonCountPtr)[2]--;
    }
}

// Function to swap crops using pointers (parameter address-of)
void swapCrops(Crop* crop1, Crop* crop2) {
    Crop temp = *crop1;
    *crop1 = *crop2;
    *crop2 = temp;
}

// Procedure to search for crops
void searchCrop() {
    string searchTerm;
    bool found = false;
    
    cout << "\n===== CARI TANAMAN =====" << endl;
    cout << "1. Cari berdasarkan nama" << endl;
    cout << "2. Cari berdasarkan musim" << endl;
    cout << "3. Cari berdasarkan tipe harvest" << endl;
    cout << "Pilihan: ";
    
    int searchChoice;
    processCropInput(&searchChoice); // Using pointer function
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
                // Using pointer version of displayCrop
                displayCropByPointer(&crops[i], count);
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
                // Using pointer version of displayCrop
                displayCropByPointer(&crops[i], count);
                found = true;
            }
        }
        
        // Display season statistics using function overloading
        if (found) {
            vector<int> seasonStats = {count};
            vector<string> seasonLabel = {searchTerm};
            // Using pointer versions
            updateSeasonsStats(&searchTerm, &seasonStats);
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
                // Using pointer version of displayCrop
                displayCropByPointer(&crops[i], count);
                found = true;
            }
        }
    }
    else {
        cout << "Pilihan pencarian tidak valid!" << endl;
        return;
    }
    
    if (!found) {
        cout << "Tidak ada hasil yang ditemukan." << endl;
    }
}

// New function that uses pointers to update season stats (parameter address-of)
void updateSeasonsStats(string* seasonPtr, vector<int>* statsPtr) {
    cout << "\nStatistik Pencarian:" << endl;
    cout << *seasonPtr << ": " << (*statsPtr)[0] << " tanaman" << endl;
}

// Function to clear screen (cross-platform)
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Function to pause screen
void pauseScreen() {
    cout << "\nTekan Enter untuk lanjut...";
    cin.ignore();
    cin.get();
}

// Function overloading for displaying statistics
void displayStats(const vector<int>& stats, const vector<string>& labels) {
    for (size_t i = 0; i < stats.size(); i++) {
        cout << labels[i] << ": " << stats[i] << " tanaman" << endl;
    }
}

// Function overloading with custom title
void displayStats(const string& title, const vector<int>& stats, const vector<string>& labels) {
    cout << "\n" << title << endl;
    for (size_t i = 0; i < stats.size(); i++) {
        cout << labels[i] << ": " << stats[i] << " tanaman" << endl;
    }
}

// Function overloading for displaying crops
void displayCrop(const Crop& crop) {
    cout << left << "Nama: " << crop.name << endl
         << "Harga Bibit: " << crop.seedPrice << endl
         << "Waktu Tumbuh: " << crop.growthTime << " hari" << endl
         << "Harga Jual: " << crop.sellingPrice << endl
         << "Musim Tanam: " << crop.growSeason << endl
         << "Tipe Harvest: " << crop.harvestType << endl;
}

// Function overloading with index parameter
void displayCrop(const Crop& crop, int index) {
    cout << left << setw(5) << index
         << setw(20) << crop.name
         << setw(15) << crop.seedPrice
         << setw(15) << crop.growthTime
         << setw(15) << crop.sellingPrice
         << setw(15) << crop.growSeason
         << setw(10) << crop.harvestType << endl;
}

// New function to display crop using pointer (parameter dereference)
void displayCropByPointer(const Crop* cropPtr) {
    cout << left << "Nama: " << cropPtr->name << endl
         << "Harga Bibit: " << cropPtr->seedPrice << endl
         << "Waktu Tumbuh: " << cropPtr->growthTime << " hari" << endl
         << "Harga Jual: " << cropPtr->sellingPrice << endl
         << "Musim Tanam: " << cropPtr->growSeason << endl
         << "Tipe Harvest: " << cropPtr->harvestType << endl;
}

// New function to display crop with index using pointer (parameter dereference)
void displayCropByPointer(const Crop* cropPtr, int index) {
    int profit = calculateProfitByPtr(cropPtr, 28);
    cout << left << setw(5) << index
         << setw(20) << cropPtr->name
         << setw(15) << cropPtr->seedPrice
         << setw(15) << cropPtr->growthTime
         << setw(15) << cropPtr->sellingPrice
         << setw(15) << cropPtr->growSeason
         << setw(10) << cropPtr->harvestType 
         << setw(15) << profit << endl;
}

// Recursive function to calculate potential profit over days
int calculateProfit(const Crop& crop, int days, int plantCount) {
    // Base case: no more days left
    if (days <= 0) {
        return 0;
    }
    
    // If growth time is more than remaining days, no profit
    if (crop.growthTime > days) {
        return 0;
    }
    
    int profit = 0;
    
    if (crop.harvestType == "single") {
        // Single harvest crops: calculate how many harvests we can get in the days
        int numHarvests = days / crop.growthTime;
        profit = numHarvests * (crop.sellingPrice - crop.seedPrice) * plantCount;
    } else if (crop.harvestType == "multiple") {
        // Multiple harvest crops: get one harvest every 2-3 days after initial growth
        int harvestInterval = 3; // Average regrow time
        
        // Initial harvest after growth time
        profit = crop.sellingPrice * plantCount;
        
        // Remaining days for additional harvests
        int remainingDays = days - crop.growthTime;
        
        // Additional harvests
        profit += (remainingDays / harvestInterval) * crop.sellingPrice * plantCount;
        
        // Subtract seed cost once per plant
        profit -= crop.seedPrice * plantCount;
    }
    
    return profit;
}
// Function to save user data to file
void simpanPengguna() {
    ofstream file("users.txt");
    if (file.is_open()) {
        for (const User& user : users) {
            file << user.name << "," << user.nim << "," << user.isActive << endl;
        }
        file.close();
    } else {
        cout << "Gagal menyimpan data pengguna!" << endl;
    }
}

// Function to load user data from file
void muatPengguna() {
    ifstream file("users.txt");
    if (file.is_open()) {
        users.clear(); // Clear existing data
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, nim, active;
            
            getline(ss, name, ',');
            getline(ss, nim, ',');
            getline(ss, active, ',');
            
            User user;
            user.name = name;
            user.nim = nim;
            user.isActive = (active == "1");
            
            users.push_back(user);
        }
        file.close();
    }
}

// Function to save crops data to file
void simpanCrops() {
    ofstream file("crops.txt");
    if (file.is_open()) {
        for (const Crop& crop : crops) {
            file << crop.name << "," << crop.seedPrice << "," 
                 << crop.growthTime << "," << crop.sellingPrice << "," 
                 << crop.growSeason << "," << crop.harvestType << endl;
        }
        file.close();
    } else {
        cout << "Gagal menyimpan data tanaman!" << endl;
    }
}

// Function to load crops data from file
void muatCrops() {
    ifstream file("crops.txt");
    if (file.is_open()) {
        crops.clear(); // Clear existing data
        cropsPerSeason = {0, 0, 0}; // Reset season counts
        
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, seedPrice, growthTime, sellingPrice, growSeason, harvestType;
            
            getline(ss, name, ',');
            getline(ss, seedPrice, ',');
            getline(ss, growthTime, ',');
            getline(ss, sellingPrice, ',');
            getline(ss, growSeason, ',');
            getline(ss, harvestType, ',');
            
            Crop crop;
            crop.name = name;
            crop.seedPrice = stoi(seedPrice);
            crop.growthTime = stoi(growthTime);
            crop.sellingPrice = stoi(sellingPrice);
            crop.growSeason = growSeason;
            crop.harvestType = harvestType;
            
            crops.push_back(crop);
            
            // Update season statistics
            incrementSeasonCount(&cropsPerSeason, crop.growSeason);
        }
        file.close();
    }
}

// Implementation of calculateProfitByPtr function (using pointer)
int calculateProfitByPtr(const Crop* cropPtr, int days, int plantCount) {
    // Base case: no more days left
    if (days <= 0) {
        return 0;
    }
    
    // If growth time is more than remaining days, no profit
    if (cropPtr->growthTime > days) {
        return 0;
    }
    
    int profit = 0;
    
    if (cropPtr->harvestType == "single") {
        // Single harvest crops: calculate how many harvests we can get in the days
        int numHarvests = days / cropPtr->growthTime;
        profit = numHarvests * (cropPtr->sellingPrice - cropPtr->seedPrice) * plantCount;
    } else if (cropPtr->harvestType == "multiple") {
        // Multiple harvest crops: get one harvest every 2-3 days after initial growth
        int harvestInterval = 3; // Average regrow time
        
        // Initial harvest after growth time
        profit = cropPtr->sellingPrice * plantCount;
        
        // Remaining days for additional harvests
        int remainingDays = days - cropPtr->growthTime;
        
        // Additional harvests
        profit += (remainingDays / harvestInterval) * cropPtr->sellingPrice * plantCount;
        
        // Subtract seed cost once per plant
        profit -= cropPtr->seedPrice * plantCount;
    }
    
    return profit;
}