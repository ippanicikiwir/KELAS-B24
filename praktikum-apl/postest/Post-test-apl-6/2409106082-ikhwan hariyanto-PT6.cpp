#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept> // For exception handling

using namespace std;

// DEBUG flag - set to true to enable debug output
#define DEBUG true

// Macro for debug output
#define DEBUG_PRINT(msg) if(DEBUG) { cout << "[DEBUG] " << msg << endl; }

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

// New functions from paste-2.txt
double calculateProfitPerDay(const Crop* cropPtr);
string toLowercase(const string& str);

// New sorting functions with pointers
void sortCropsByNameDescending(vector<Crop>* cropsPtr);
void sortCropsByPriceAscending(vector<Crop>* cropsPtr);
void sortCropsByProfitPerDay(vector<Crop>* cropsPtr);
void showSortMenu();

int main() {
    try {
        DEBUG_PRINT("Program starting...");
        
        // Load saved data
        DEBUG_PRINT("Attempting to load user data...");
        muatPengguna();
        DEBUG_PRINT("User data loaded successfully!");
        
        //If no users exist, add default user
        if (users.empty()) {
            DEBUG_PRINT("No users found, creating default user");
            
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
            DEBUG_PRINT("Default user created and saved");
        }
        
        // Initialize crops data
        DEBUG_PRINT("Initializing crops data...");
        initializeCrops();
        DEBUG_PRINT("Crops data initialized successfully!");
        
        // Clear screen
        clearScreen();

        // Login system
        DEBUG_PRINT("Starting login system...");
        if (!loginSystem()) {
            cout << "Anda telah melebihi batas percobaan login. Program berhenti." << endl;
            return 0;
        }
        
        DEBUG_PRINT("Login successful!");
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
            
            DEBUG_PRINT("User selected option: " + to_string(choice));
            
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
                case 7:
                    showSortMenu(); // Show sorting menu
                    break;
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
        
        DEBUG_PRINT("Program terminating normally");
        return 0;
    } 
    catch (const exception& e) {
        cerr << "ERROR: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "ERROR: Unknown exception occurred" << endl;
        return 1;
    }
}

// Helper function to calculate profit per day for a crop
double calculateProfitPerDay(const Crop* cropPtr) {
    // Handle division by zero
    if (cropPtr->growthTime <= 0) {
        return 0.0;
    }
    
    // Season length in days
    const int SEASON_LENGTH = 28;
    
    if (cropPtr->harvestType == "single") {
        // For single harvest crops, profit per day is simply (selling price - seed price) / growth time
        return (double)(cropPtr->sellingPrice - cropPtr->seedPrice) / cropPtr->growthTime;
    } else { // multiple harvest type
        // Average regrow time for multiple harvest crops
        const int REGROW_TIME = 3;
        
        // Calculate potential harvests in a season
        int firstHarvestDay = cropPtr->growthTime;
        int remainingDays = SEASON_LENGTH - firstHarvestDay;
        int additionalHarvests = (remainingDays > 0) ? (remainingDays / REGROW_TIME) : 0;
        
        // Total harvests in a season
        int totalHarvests = 1 + additionalHarvests;
        
        // Total profit = all harvests - seed cost
        int totalProfit = (totalHarvests * cropPtr->sellingPrice) - cropPtr->seedPrice;
        
        // Return profit per day over the whole season
        return (double)totalProfit / SEASON_LENGTH;
    }
}

// Function to convert string to lowercase for case-insensitive comparison
string toLowercase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Improved function to show sorting menu
void showSortMenu() {
    int sortChoice;
    
    cout << "\n===== URUTKAN TANAMAN =====" << endl;
    cout << "1. Urutkan berdasarkan Nama (Z-A)" << endl;
    cout << "2. Urutkan berdasarkan Harga Bibit (Murah-Mahal)" << endl;
    cout << "3. Urutkan berdasarkan Profit per Hari (Tinggi-Rendah)" << endl;
    cout << "Pilihan Anda: ";
    
    processCropInput(&sortChoice);
    
    DEBUG_PRINT("Sort option selected: " + to_string(sortChoice));
    
    switch (sortChoice) {
        case 1:
            cout << "Mengurutkan tanaman berdasarkan nama secara descending (Z-A)..." << endl;
            sortCropsByNameDescending(&crops);
            cout << "Tanaman berhasil diurutkan berdasarkan nama (Z-A)!" << endl;
            break;
        case 2:
            cout << "Mengurutkan tanaman berdasarkan harga bibit secara ascending (Murah-Mahal)..." << endl;
            sortCropsByPriceAscending(&crops);
            cout << "Tanaman berhasil diurutkan berdasarkan harga bibit (Murah-Mahal)!" << endl;
            break;
        case 3:
            cout << "Mengurutkan tanaman berdasarkan profit per hari (Tinggi-Rendah)..." << endl;
            sortCropsByProfitPerDay(&crops);
            cout << "Tanaman berhasil diurutkan berdasarkan profit per hari (Tinggi-Rendah)!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
    
    cout << "Gunakan pilihan '1' untuk melihat hasil pengurutan." << endl;
}

// Improved function to sort crops by name in descending order (Z-A)
void sortCropsByNameDescending(vector<Crop>* cropsPtr) {
    try {
        DEBUG_PRINT("Sorting crops by name descending...");
        
        // Use selection sort with case-insensitive comparison
        for (size_t i = 0; i < cropsPtr->size() - 1; i++) {
            // Find the position of the lexicographically largest name
            size_t maxIdx = i;
            for (size_t j = i + 1; j < cropsPtr->size(); j++) {
                // Case-insensitive comparison (Z-A order)
                if (toLowercase((*cropsPtr)[j].name) > toLowercase((*cropsPtr)[maxIdx].name)) {
                    maxIdx = j;
                }
                // If names are the same (case-insensitive), use the original case as tie-breaker
                else if (toLowercase((*cropsPtr)[j].name) == toLowercase((*cropsPtr)[maxIdx].name) && 
                         (*cropsPtr)[j].name > (*cropsPtr)[maxIdx].name) {
                    maxIdx = j;
                }
            }
            
            // Swap if we found a larger element
            if (maxIdx != i) {
                swapCrops(&(*cropsPtr)[i], &(*cropsPtr)[maxIdx]);
            }
        }
        
        DEBUG_PRINT("Sorting by name completed successfully");
    }
    catch (const exception& e) {
        cerr << "Error sorting by name: " << e.what() << endl;
    }
}

// Improved function to sort crops by seed price in ascending order (Low-High)
void sortCropsByPriceAscending(vector<Crop>* cropsPtr) {
    try {
        DEBUG_PRINT("Sorting crops by price ascending...");
        
        // Use selection sort with secondary criteria
        for (size_t i = 0; i < cropsPtr->size() - 1; i++) {
            // Find the position of the smallest price
            size_t minIdx = i;
            for (size_t j = i + 1; j < cropsPtr->size(); j++) {
                // Primary: Compare seed prices in ascending order (Low-High)
                if ((*cropsPtr)[j].seedPrice < (*cropsPtr)[minIdx].seedPrice) {
                    minIdx = j;
                }
                // Secondary: If prices are equal, sort by name alphabetically (A-Z)
                else if ((*cropsPtr)[j].seedPrice == (*cropsPtr)[minIdx].seedPrice && 
                         toLowercase((*cropsPtr)[j].name) < toLowercase((*cropsPtr)[minIdx].name)) {
                    minIdx = j;
                }
            }
            
            // Swap if we found a smaller element
            if (minIdx != i) {
                swapCrops(&(*cropsPtr)[i], &(*cropsPtr)[minIdx]);
            }
        }
        
        DEBUG_PRINT("Sorting by price completed successfully");
    }
    catch (const exception& e) {
        cerr << "Error sorting by price: " << e.what() << endl;
    }
}

// Improved function to sort crops by profit per day (High-Low) with better algorithm
void sortCropsByProfitPerDay(vector<Crop>* cropsPtr) {
    try {
        if (cropsPtr->empty()) {
            DEBUG_PRINT("Warning: Attempting to sort an empty crop list");
            return;
        }
        
        DEBUG_PRINT("Sorting crops by profit per day...");
        
        // Step 1: Precalculate profit per day for each crop and store in a pair
        vector<pair<double, size_t>> profitWithIndex;
        profitWithIndex.reserve(cropsPtr->size());
        
        cout << "\nProfitabilitas tanaman per hari:" << endl;
        cout << left << setw(30) << "Nama Tanaman" << setw(20) << "Profit per Hari" << endl;
        cout << string(50, '-') << endl;
        
        for (size_t i = 0; i < cropsPtr->size(); i++) {
            // Use the same profit calculation as displayed in the table
            double profit = calculateProfitPerDay(&(*cropsPtr)[i]);
            profitWithIndex.push_back({profit, i});
            
            // Display profit calculation for transparency
            cout << left << setw(30) << (*cropsPtr)[i].name 
                 << setw(20) << fixed << setprecision(2) << profit << endl;
            
            DEBUG_PRINT("Crop: " + (*cropsPtr)[i].name + ", Profit per day: " + to_string(profit));
        }
        
        cout << endl;
        
        // Step 2: Sort the pairs by profit per day (descending)
        sort(profitWithIndex.begin(), profitWithIndex.end(), 
             [](const pair<double, size_t>& a, const pair<double, size_t>& b) {
                return a.first > b.first; // Sort by profit in descending order
             });
        
        // Step 3: Create a copy of the original crops vector
        vector<Crop> sortedCrops(cropsPtr->size());
        
        // Step 4: Reorder the crops based on the sorted profit values
        for (size_t i = 0; i < profitWithIndex.size(); i++) {
            sortedCrops[i] = (*cropsPtr)[profitWithIndex[i].second];
        }
        
        // Step 5: Copy the sorted crops back to the original vector
        *cropsPtr = sortedCrops;
        
        DEBUG_PRINT("Sorting by profit completed successfully");
        
        // Display sorted order for confirmation
        cout << "\nUrutan tanaman berdasarkan profit per hari (dari tertinggi):" << endl;
        for (size_t i = 0; i < min(size_t(10), cropsPtr->size()); i++) {
            cout << (i+1) << ". " << (*cropsPtr)[i].name << endl;
        }
        if (cropsPtr->size() > 10) {
            cout << "... dan " << (cropsPtr->size() - 10) << " tanaman lainnya" << endl;
        }
        cout << endl;
    }
    catch (const exception& e) {
        cerr << "Error sorting by profit: " << e.what() << endl;
    }
}

// New function to validate input using pointer
void processCropInput(int* valuePtr) {
    if (!(cin >> *valuePtr)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input tidak valid! Masukkan angka." << endl;
        *valuePtr = 0; // Set default value
        DEBUG_PRINT("Invalid input detected, reset to 0");
    }
    else {
        // Clear any remaining characters in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// New function to validate index using pointer (returns boolean)
bool validateIndex(int* indexPtr, int maxSize) {
    if (*indexPtr < 1 || *indexPtr > maxSize) {
        cout << "Nomor tanaman tidak valid!" << endl;
        DEBUG_PRINT("Invalid index: " + to_string(*indexPtr) + ", max allowed: " + to_string(maxSize));
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
        
        // Clear input buffer after reading input
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        DEBUG_PRINT("Login attempt with name: " + inputName + ", NIM: " + inputNim);
        
        // Check login against all users
        for (const User& user : users) {
            if (inputName == user.name && inputNim == user.nim) {
                cout << "Login berhasil!" << endl;
                isLoggedIn = true;
                DEBUG_PRINT("Login successful for user: " + inputName);
                break;
            }
        }
        
        if (!isLoggedIn) {
            loginAttempts++;
            clearScreen();
            
            cout << "Login gagal! Percobaan ke-" << loginAttempts << " dari 3" << endl;
            DEBUG_PRINT("Login failed, attempt " + to_string(loginAttempts) + " of 3");
        }
    }
    
    return isLoggedIn;
}

// Procedure to register a new user
void registerUser() {
    try {
        User newUser;
        
        DEBUG_PRINT("Starting user registration...");
        
        cout << "\n===== DAFTAR PENGGUNA BARU =====" << endl;
        cout << "Masukkan Nama: ";
        getline(cin, newUser.name);
        
        cout << "Masukkan NIM: ";
        getline(cin, newUser.nim);
        
        DEBUG_PRINT("New user registration: Name: " + newUser.name + ", NIM: " + newUser.nim);
        
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
            DEBUG_PRINT("Registration failed: User already exists");
        } else {
            newUser.isActive = true;
            users.push_back(newUser);
            
            // Save user data immediately after registration
            simpanPengguna();
            
            cout << "Pengguna berhasil terdaftar!" << endl;
            DEBUG_PRINT("User registered successfully");
        }
    }
    catch (const exception& e) {
        cerr << "Error registering user: " << e.what() << endl;
    }
}

// Procedure to initialize predefined crops
void initializeCrops() {
    try {
        // Try to load crops from file first
        DEBUG_PRINT("Attempting to load crops from file...");
        muatCrops();
        
        // Only initialize if no crops were loaded
        if (crops.empty()) {
            DEBUG_PRINT("No crops loaded from file, initializing default crops...");
            
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
            
            DEBUG_PRINT("Default crops initialized: " + to_string(crops.size()) + " crops added");
        } else {
            DEBUG_PRINT("Crops loaded from file: " + to_string(crops.size()) + " crops loaded");
        }
    }
    catch (const exception& e) {
        cerr << "Error initializing crops: " << e.what() << endl;
    }
}

// Procedure to display all crops
void displayAllCrops() {
    try {
        clearScreen();
        
        DEBUG_PRINT("Displaying all crops...");
        
        // Calculate dynamic column widths based on content
        size_t maxNameWidth = 20; // minimum width
        size_t maxSeasonWidth = 15; // minimum width
        size_t maxTypeWidth = 10; // minimum width
        
        // Adjust column widths based on actual content
        for (const Crop& crop : crops) {
            maxNameWidth = max(maxNameWidth, crop.name.length() + 2);
            maxSeasonWidth = max(maxSeasonWidth, crop.growSeason.length() + 2);
            maxTypeWidth = max(maxTypeWidth, crop.harvestType.length() + 2);
        }
        
        // Format header
        cout << string(36, '=') << " DAFTAR SEMUA TANAMAN " << string(36, '=')  << endl;
        cout << left 
             << setw(5) << "No" 
             << setw(maxNameWidth) << "Nama" 
             << setw(15) << "Harga Bibit" 
             << setw(15) << "Waktu Tumbuh" 
             << setw(15) << "Harga Jual" 
             << setw(maxSeasonWidth) << "Musim" 
             << setw(maxTypeWidth) << "Tipe" 
             << setw(15) << "Profit (28 hari)" << endl;
        
        // Calculate table width
        size_t tableWidth = 5 + maxNameWidth + 15 + 15 + 15 + maxSeasonWidth + maxTypeWidth + 15;
        cout << string(tableWidth, '-') << endl;
        
        // Display all crops with consistent formatting
        for (size_t i = 0; i < crops.size(); i++) {
            int profit28Days = calculateProfitByPtr(&crops[i], 28);
            
            cout << left 
                 << setw(5) << (i + 1) 
                 << setw(maxNameWidth) << crops[i].name 
                 << setw(15) << crops[i].seedPrice 
                 << setw(15) << crops[i].growthTime 
                 << setw(15) << crops[i].sellingPrice 
                 << setw(maxSeasonWidth) << crops[i].growSeason 
                 << setw(maxTypeWidth) << crops[i].harvestType 
                 << setw(15) << profit28Days << endl;
        }
        
        // Display statistics
        cout << "\nStatistik Tanaman per Musim:" << endl;
        displayStats(cropsPerSeason, seasons);
        
        DEBUG_PRINT("All crops displayed successfully");
    }
    catch (const exception& e) {
        cerr << "Error displaying crops: " << e.what() << endl;
    }
}

// Procedure to add a new crop
void addNewCrop() {
    try {
        Crop newCrop;
        
        DEBUG_PRINT("Starting to add new crop...");
        
        cout << "\n===== TAMBAH TANAMAN BARU =====" << endl;
        cout << "Nama Tanaman: ";
        getline(cin, newCrop.name);
        
        cout << "Harga Bibit: ";
        processCropInput(&newCrop.seedPrice);
        
        cout << "Waktu Tumbuh (hari): ";
        processCropInput(&newCrop.growthTime);
        
        cout << "Harga Jual: ";
        processCropInput(&newCrop.sellingPrice);
        
        cout << "Musim Tanam (Spring/Summer/Fall): ";
        getline(cin, newCrop.growSeason);
        
        cout << "Tipe Harvest (single/multiple): ";
        getline(cin, newCrop.harvestType);
        
        DEBUG_PRINT("New crop data: Name: " + newCrop.name + 
                    ", Seed Price: " + to_string(newCrop.seedPrice) +
                    ", Growth Time: " + to_string(newCrop.growthTime) +
                    ", Selling Price: " + to_string(newCrop.sellingPrice) +
                    ", Season: " + newCrop.growSeason +
                    ", Harvest Type: " + newCrop.harvestType);
        
        // Add data to array
        crops.push_back(newCrop);
        
        // Update statistics using a pointer
        incrementSeasonCount(&cropsPerSeason, newCrop.growSeason);
        
        cout << "Tanaman berhasil ditambahkan!" << endl;
        
        // Show profit calculation using our pointer function
        int plantDays = 28; // Typical season length
        cout << "Perkiraan keuntungan dalam " << plantDays << " hari: " 
             << calculateProfitByPtr(&newCrop, plantDays) << " gold" << endl;
        
        DEBUG_PRINT("New crop added successfully");
    }
    catch (const exception& e) {
        cerr << "Error adding new crop: " << e.what() << endl;
    }
}

// Procedure to update a crop
void updateCrop() {
    try {
        int index;
        
        DEBUG_PRINT("Starting crop update process...");
        
        cout << "\n===== PERBARUI TANAMAN =====" << endl;
        cout << "Daftar Tanaman:" << endl;
        for (size_t i = 0; i < crops.size(); i++) {
            cout << (i + 1) << ". " << crops[i].name << endl;
        }
        
        cout << "Masukkan nomor tanaman yang ingin diperbarui: ";
        cin >> index;
        
        // Validate index using pointer function
        if (!validateIndex(&index, crops.size())) {
            DEBUG_PRINT("Update cancelled: Invalid index");
            return;
        }
        
        DEBUG_PRINT("Updating crop index " + to_string(index) + ": " + crops[index].name);
        
        // Decrease previous season count
        decrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
        
        // Update crop using pointer function
        Crop* cropPtr = &crops[index];
        updateCropByPointer(cropPtr);
        
        // Update statistics for new season
        incrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
        
        cout << "Tanaman berhasil diperbarui!" << endl;
        DEBUG_PRINT("Crop updated successfully");
    }
    catch (const exception& e) {
        cerr << "Error updating crop: " << e.what() << endl;
    }
}

// New function to update crop by pointer (parameter dereference)
void updateCropByPointer(Crop* cropPtr) {
    try {
        DEBUG_PRINT("Updating crop details for: " + cropPtr->name);
        
        cin.ignore();
        cout << "Nama Tanaman [" << cropPtr->name << "]: ";
        string input;
        getline(cin, input);
        if (!input.empty()) {
            cropPtr->name = input;
            DEBUG_PRINT("Updated name to: " + cropPtr->name);
        }
        
        cout << "Harga Bibit [" << cropPtr->seedPrice << "]: ";
        string priceInput;
        getline(cin, priceInput);
        if (!priceInput.empty()) {
            try {
                cropPtr->seedPrice = stoi(priceInput);
                DEBUG_PRINT("Updated seed price to: " + to_string(cropPtr->seedPrice));
            }
            catch (const exception& e) {
                cout << "Input harga tidak valid, menggunakan harga lama." << endl;
                DEBUG_PRINT("Invalid price input: " + priceInput);
            }
        }
        
        cout << "Waktu Tumbuh [" << cropPtr->growthTime << "]: ";
        string growthInput;
        getline(cin, growthInput);
        if (!growthInput.empty()) {
            try {
                cropPtr->growthTime = stoi(growthInput);
                DEBUG_PRINT("Updated growth time to: " + to_string(cropPtr->growthTime));
            }
            catch (const exception& e) {
                cout << "Input waktu tidak valid, menggunakan waktu lama." << endl;
                DEBUG_PRINT("Invalid growth time input: " + growthInput);
            }
        }
        
        cout << "Harga Jual [" << cropPtr->sellingPrice << "]: ";
        string sellInput;
        getline(cin, sellInput);
        if (!sellInput.empty()) {
            try {
                cropPtr->sellingPrice = stoi(sellInput);
                DEBUG_PRINT("Updated selling price to: " + to_string(cropPtr->sellingPrice));
            }
            catch (const exception& e) {
                cout << "Input harga jual tidak valid, menggunakan harga lama." << endl;
                DEBUG_PRINT("Invalid selling price input: " + sellInput);
            }
        }
        
        cout << "Musim Tanam [" << cropPtr->growSeason << "]: ";
        string seasonInput;
        getline(cin, seasonInput);
        if (!seasonInput.empty()) {
            cropPtr->growSeason = seasonInput;
            DEBUG_PRINT("Updated growing season to: " + cropPtr->growSeason);
        }
        
        cout << "Tipe Harvest [" << cropPtr->harvestType << "]: ";
        string typeInput;
        getline(cin, typeInput);
        if (!typeInput.empty()) {
            cropPtr->harvestType = typeInput;
            DEBUG_PRINT("Updated harvest type to: " + cropPtr->harvestType);
        }
    }
    catch (const exception& e) {
        cerr << "Error updating crop details: " << e.what() << endl;
    }
}

// Procedure to delete a crop
void deleteCrop() {
    try {
        int index;
        
        DEBUG_PRINT("Starting crop deletion process...");
        
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
            DEBUG_PRINT("Deletion cancelled: Invalid index");
            return;
        }
        
        DEBUG_PRINT("Attempting to delete crop index " + to_string(index) + ": " + crops[index].name);
        
        // Remove from statistics using pointer function
        decrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
        
        cout << "Tanaman " << crops[index].name << " akan dihapus. Lanjutkan? (y/n): ";
        char confirmation;
        cin >> confirmation;
        
        if (confirmation == 'y' || confirmation == 'Y') {
            // Delete data from all arrays
            crops.erase(crops.begin() + index);
            cout << "Tanaman berhasil dihapus!" << endl;
            DEBUG_PRINT("Crop deleted successfully");
        } else {
            cout << "Penghapusan dibatalkan." << endl;
            DEBUG_PRINT("Deletion cancelled by user");
            
            // Restore statistics since deletion was cancelled
            incrementSeasonCount(&cropsPerSeason, crops[index].growSeason);
        }
    }
    catch (const exception& e) {
        cerr << "Error deleting crop: " << e.what() << endl;
    }
}

// Function to increment season count using pointer (parameter address-of)
void incrementSeasonCount(vector<int>* seasonCountPtr, const string& season) {
    try {
        DEBUG_PRINT("Incrementing season count for: " + season);
        
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
    catch (const exception& e) {
        cerr << "Error incrementing season count: " << e.what() << endl;
    }
}

// Function to decrement season count using pointer (parameter address-of)
void decrementSeasonCount(vector<int>* seasonCountPtr, const string& season) {
    try {
        DEBUG_PRINT("Decrementing season count for: " + season);
        
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
    catch (const exception& e) {
        cerr << "Error decrementing season count: " << e.what() << endl;
    }
}

// Function to swap crops using pointers (parameter address-of)
void swapCrops(Crop* crop1, Crop* crop2) {
    try {
        DEBUG_PRINT("Swapping crops: " + crop1->name + " <-> " + crop2->name);
        
        Crop temp = *crop1;
        *crop1 = *crop2;
        *crop2 = temp;
    }
    catch (const exception& e) {
        cerr << "Error swapping crops: " << e.what() << endl;
    }
}

// Procedure to search for crops
void searchCrop() {
    try {
        string searchTerm;
        bool found = false;
        
        DEBUG_PRINT("Starting crop search...");
        
        cout << "\n===== CARI TANAMAN =====" << endl;
        cin.ignore();
        cout << "Masukkan nama tanaman atau musim: ";
        getline(cin, searchTerm);
        
        DEBUG_PRINT("Searching for: " + searchTerm);
        
        // Calculate dynamic column widths based on content
        size_t maxNameWidth = 20; // minimum width
        size_t maxSeasonWidth = 15; // minimum width
        size_t maxTypeWidth = 10; // minimum width
        
        // Adjust column widths based on actual content for all crops
        for (const Crop& crop : crops) {
            maxNameWidth = max(maxNameWidth, crop.name.length() + 2);
            maxSeasonWidth = max(maxSeasonWidth, crop.growSeason.length() + 2);
            maxTypeWidth = max(maxTypeWidth, crop.harvestType.length() + 2);
        }
        
        cout << "\nHasil pencarian untuk '" << searchTerm << "':" << endl;
        cout << left 
             << setw(5) << "No" 
             << setw(maxNameWidth) << "Nama" 
             << setw(15) << "Harga Bibit" 
             << setw(15) << "Waktu Tumbuh" 
             << setw(15) << "Harga Jual" 
             << setw(maxSeasonWidth) << "Musim" 
             << setw(maxTypeWidth) << "Tipe" << endl;
        
        // Calculate table width
        size_t tableWidth = 5 + maxNameWidth + 15 + 15 + 15 + maxSeasonWidth + maxTypeWidth;
        cout << string(tableWidth, '-') << endl;
        
        int resultCount = 0;
        
        for (size_t i = 0; i < crops.size(); i++) {
            // Convert both to lowercase for case-insensitive search
            string cropNameLower = crops[i].name;
            string seasonLower = crops[i].growSeason;
            string searchTermLower = searchTerm;
            
            // Convert to lowercase
            transform(cropNameLower.begin(), cropNameLower.end(), cropNameLower.begin(), ::tolower);
            transform(seasonLower.begin(), seasonLower.end(), seasonLower.begin(), ::tolower);
            transform(searchTermLower.begin(), searchTermLower.end(), searchTermLower.begin(), ::tolower);
            
            // Check if search term is in name or season
            if (cropNameLower.find(searchTermLower) != string::npos || 
                seasonLower.find(searchTermLower) != string::npos) {
                
                // Display crop with consistent formatting
                cout << left 
                     << setw(5) << (i + 1) 
                     << setw(maxNameWidth) << crops[i].name 
                     << setw(15) << crops[i].seedPrice 
                     << setw(15) << crops[i].growthTime 
                     << setw(15) << crops[i].sellingPrice 
                     << setw(maxSeasonWidth) << crops[i].growSeason 
                     << setw(maxTypeWidth) << crops[i].harvestType << endl;
                
                found = true;
                resultCount++;
            }
        }
        
        if (!found) {
            cout << "Tidak ditemukan tanaman yang cocok dengan pencarian." << endl;
            DEBUG_PRINT("No matching crops found");
        } else {
            cout << "\nDitemukan " << resultCount << " hasil pencarian." << endl;
            DEBUG_PRINT("Found " + to_string(resultCount) + " matching crops");
        }
    }
    catch (const exception& e) {
        cerr << "Error searching for crops: " << e.what() << endl;
    }
}

// Function to display crop by pointer (parameter dereference)
void displayCropByPointer(const Crop* cropPtr) {
    try {
        // Calculate dynamic column widths based on content
        size_t maxNameWidth = max<size_t>(20, cropPtr->name.length() + 2);
        size_t maxSeasonWidth = max<size_t>(15, cropPtr->growSeason.length() + 2);
        size_t maxTypeWidth = max<size_t>(10, cropPtr->harvestType.length() + 2);
        
        cout << left 
             << setw(maxNameWidth) << cropPtr->name 
             << setw(15) << cropPtr->seedPrice 
             << setw(15) << cropPtr->growthTime 
             << setw(15) << cropPtr->sellingPrice 
             << setw(maxSeasonWidth) << cropPtr->growSeason 
             << setw(maxTypeWidth) << cropPtr->harvestType << endl;
    }
    catch (const exception& e) {
        cerr << "Error displaying crop: " << e.what() << endl;
    }
}

// Function overload to display crop with index by pointer
void displayCropByPointer(const Crop* cropPtr, int index) {
    try {
        // Calculate profit consistently using the same method as in sorting
        int profit28Days = calculateProfitByPtr(cropPtr, 28);
        
        // Calculate dynamic column widths based on content
        size_t maxNameWidth = max<size_t>(20, cropPtr->name.length() + 2);
        size_t maxSeasonWidth = max<size_t>(15, cropPtr->growSeason.length() + 2);
        size_t maxTypeWidth = max<size_t>(10, cropPtr->harvestType.length() + 2);
        
        cout << left 
             << setw(5) << index 
             << setw(maxNameWidth) << cropPtr->name 
             << setw(15) << cropPtr->seedPrice 
             << setw(15) << cropPtr->growthTime 
             << setw(15) << cropPtr->sellingPrice 
             << setw(maxSeasonWidth) << cropPtr->growSeason 
             << setw(maxTypeWidth) << cropPtr->harvestType 
             << setw(15) << profit28Days << endl;
    }
    catch (const exception& e) {
        cerr << "Error displaying crop with index: " << e.what() << endl;
    }
}

// Function to calculate profit using pointer (parameter dereference)
int calculateProfitByPtr(const Crop* cropPtr, int days, int plantCount) {
    try {
        if (cropPtr->harvestType == "single") {
            // How many full growing cycles fit in the given days
            int cycles = days / cropPtr->growthTime;
            return cycles * (cropPtr->sellingPrice - cropPtr->seedPrice) * plantCount;
        } else { // multiple harvest
            int profit = 0;
            int remainingDays = days;
            
            // Initial growth
            remainingDays -= cropPtr->growthTime;
            
            if (remainingDays >= 0) {
                // First harvest
                profit += cropPtr->sellingPrice * plantCount;
                
                // Regrowth (assume 3 days for regrowth on multiple harvest crops)
                int regrowthTime = 3;
                int additionalHarvests = remainingDays / regrowthTime;
                profit += additionalHarvests * cropPtr->sellingPrice * plantCount;
            }
            
            // Subtract seed costs once per plant
            profit -= cropPtr->seedPrice * plantCount;
            
            return profit > 0 ? profit : 0; // Ensure we don't return negative profit
        }
    }
    catch (const exception& e) {
        cerr << "Error calculating profit: " << e.what() << endl;
        return 0;
    }
}

// Recursive function to calculate profit
int calculateProfit(const Crop& crop, int days, int plantCount) {
    try {
        if (days <= 0) {
            return -crop.seedPrice * plantCount; // Only seed cost, no harvests
        }
        
        if (crop.harvestType == "single") {
            // Base case: not enough days to complete growing cycle
            if (days < crop.growthTime) {
                return -crop.seedPrice * plantCount;
            }
            
            // Recursive case: complete one growing cycle and recalculate
            int currentHarvest = crop.sellingPrice * plantCount;
            int futureProfits = calculateProfit(crop, days - crop.growthTime, plantCount);
            return currentHarvest + futureProfits;
        } else { // Multiple harvest
            // Base case: not enough days for initial growth
            if (days < crop.growthTime) {
                return -crop.seedPrice * plantCount;
            }
            
            int profit = 0;
            
            // Initial growth and first harvest
            profit += crop.sellingPrice * plantCount;
            days -= crop.growthTime;
            
            // Regrowth cycles (assume 3 days for regrowth)
            int regrowthTime = 3;
            while (days >= regrowthTime) {
                profit += crop.sellingPrice * plantCount;
                days -= regrowthTime;
            }
            
            // Subtract seed costs once per plant
            profit -= crop.seedPrice * plantCount;
            
            return profit;
        }
    }
    catch (const exception& e) {
        cerr << "Error in recursive profit calculation: " << e.what() << endl;
        return 0;
    }
}

// Function overloading for displaying stats
void displayStats(const vector<int>& stats, const vector<string>& labels) {
    try {
        cout << "Statistik:" << endl;
        for (size_t i = 0; i < stats.size(); i++) {
            cout << labels[i] << ": " << stats[i] << " tanaman" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error displaying stats: " << e.what() << endl;
    }
}

void displayStats(const string& title, const vector<int>& stats, const vector<string>& labels) {
    try {
        cout << title << ":" << endl;
        for (size_t i = 0; i < stats.size(); i++) {
            cout << labels[i] << ": " << stats[i] << " tanaman" << endl;
        }
    }
    catch (const exception& e) {
        cerr << "Error displaying stats with title: " << e.what() << endl;
    }
}

// Function overloading for displaying crops
void displayCrop(const Crop& crop) {
    try {
        cout << left << setw(20) << crop.name 
             << setw(15) << crop.seedPrice << setw(15) << crop.growthTime 
             << setw(15) << crop.sellingPrice << setw(15) << crop.growSeason 
             << setw(10) << crop.harvestType << endl;
    }
    catch (const exception& e) {
        cerr << "Error displaying crop: " << e.what() << endl;
    }
}

void displayCrop(const Crop& crop, int index) {
    try {
        int profit28Days = calculateProfit(crop, 28);
        
        cout << left << setw(5) << index << setw(20) << crop.name 
             << setw(15) << crop.seedPrice << setw(15) << crop.growthTime 
             << setw(15) << crop.sellingPrice << setw(15) << crop.growSeason 
             << setw(10) << crop.harvestType << setw(15) << profit28Days << endl;
    }
    catch (const exception& e) {
        cerr << "Error displaying crop with index: " << e.what() << endl;
    }
}

// Function to update seasons statistics
void updateSeasonsStats(string* seasonPtr, vector<int>* statsPtr) {
    try {
        DEBUG_PRINT("Updating season statistics for: " + *seasonPtr);
        
        if (*seasonPtr == "Spring") {
            (*statsPtr)[0]++;
        } else if (*seasonPtr == "Summer") {
            (*statsPtr)[1]++;
        } else if (*seasonPtr == "Fall") {
            (*statsPtr)[2]++;
        } else if (*seasonPtr == "Spring, Summer") {
            (*statsPtr)[0]++;
            (*statsPtr)[1]++;
        } else if (*seasonPtr == "Summer, Fall") {
            (*statsPtr)[1]++;
            (*statsPtr)[2]++;
        } else if (*seasonPtr == "Spring, Fall") {
            (*statsPtr)[0]++;
            (*statsPtr)[2]++;
        }
    }
    catch (const exception& e) {
        cerr << "Error updating season statistics: " << e.what() << endl;
    }
}

// Procedure to clear screen
void clearScreen() {
    try {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
        
        DEBUG_PRINT("Screen cleared");
    }
    catch (const exception& e) {
        cerr << "Error clearing screen: " << e.what() << endl;
    }
}

// Procedure to pause screen
void pauseScreen() {
    try {
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
        
        DEBUG_PRINT("Screen paused for user input");
    }
    catch (const exception& e) {
        cerr << "Error pausing screen: " << e.what() << endl;
    }
}

// Save user data to file
void simpanPengguna() {
    try {
        DEBUG_PRINT("Saving user data to file...");
        
        ofstream outFile("users.txt");
        if (outFile.is_open()) {
            for (const User& user : users) {
                outFile << user.name << "," << user.nim << "," << (user.isActive ? "1" : "0") << endl;
            }
            outFile.close();
            DEBUG_PRINT("User data saved successfully");
        } else {
            cout << "Tidak dapat menyimpan data pengguna!" << endl;
            DEBUG_PRINT("Failed to open users.txt for writing");
        }
    }
    catch (const exception& e) {
        cerr << "Error saving user data: " << e.what() << endl;
    }
}

// Load user data from file
void muatPengguna() {
    try {
        DEBUG_PRINT("Loading user data from file...");
        
        ifstream inFile("users.txt");
        if (inFile.is_open()) {
            users.clear();
            string line;
            
            while (getline(inFile, line)) {
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
                DEBUG_PRINT("Loaded user: " + name);
            }
            
            inFile.close();
            DEBUG_PRINT("User data loaded successfully, total users: " + to_string(users.size()));
        } else {
            DEBUG_PRINT("users.txt not found, will create new file");
        }
    }
    catch (const exception& e) {
        cerr << "Error loading user data: " << e.what() << endl;
    }
}

// Save crops data to file
void simpanCrops() {
    try {
        DEBUG_PRINT("Saving crops data to file...");
        
        ofstream outFile("crops.txt");
        if (outFile.is_open()) {
            // First line: season statistics
            outFile << cropsPerSeason[0] << "," << cropsPerSeason[1] << "," << cropsPerSeason[2] << endl;
            
            // Crop data
            for (const Crop& crop : crops) {
                outFile << crop.name << "|" 
                        << crop.seedPrice << "|" 
                        << crop.growthTime << "|" 
                        << crop.sellingPrice << "|" 
                        << crop.growSeason << "|" 
                        << crop.harvestType << endl;
            }
            outFile.close();
            cout << "Data tanaman berhasil disimpan!" << endl;
            DEBUG_PRINT("Crops data saved successfully, total crops: " + to_string(crops.size()));
        } else {
            cout << "Tidak dapat menyimpan data tanaman!" << endl;
            DEBUG_PRINT("Failed to open crops.txt for writing");
        }
    }
    catch (const exception& e) {
        cerr << "Error saving crops data: " << e.what() << endl;
    }
}

// Load crops data from file
void muatCrops() {
    try {
        DEBUG_PRINT("Loading crops data from file...");
        
        ifstream inFile("crops.txt");
        if (inFile.is_open()) {
            crops.clear();
            string line;
            
            // First line: season statistics
            getline(inFile, line);
            stringstream statsStream(line);
            string spring, summer, fall;
            
            getline(statsStream, spring, ',');
            getline(statsStream, summer, ',');
            getline(statsStream, fall, ',');
            
            try {
                cropsPerSeason[0] = stoi(spring);
                cropsPerSeason[1] = stoi(summer);
                cropsPerSeason[2] = stoi(fall);
                
                DEBUG_PRINT("Loaded season stats: Spring=" + spring + 
                           ", Summer=" + summer + ", Fall=" + fall);
            }
            catch (const exception& e) {
                // Reset statistics if conversion fails
                cropsPerSeason[0] = 0;
                cropsPerSeason[1] = 0;
                cropsPerSeason[2] = 0;
                DEBUG_PRINT("Error parsing season statistics: " + string(e.what()));
            }
            
            // Crop data
            while (getline(inFile, line)) {
                try {
                    stringstream ss(line);
                    string name, seedPrice, growthTime, sellingPrice, growSeason, harvestType;
                    
                    getline(ss, name, '|');
                    getline(ss, seedPrice, '|');
                    getline(ss, growthTime, '|');
                    getline(ss, sellingPrice, '|');
                    getline(ss, growSeason, '|');
                    getline(ss, harvestType, '|');
                    
                    Crop crop;
                    crop.name = name;
                    
                    try {
                        crop.seedPrice = stoi(seedPrice);
                        crop.growthTime = stoi(growthTime);
                        crop.sellingPrice = stoi(sellingPrice);
                    }
                    catch (const exception& e) {
                        // Use default values if conversion fails
                        crop.seedPrice = 0;
                        crop.growthTime = 1;
                        crop.sellingPrice = 0;
                        DEBUG_PRINT("Error parsing crop numeric values for " + name + ": " + string(e.what()));
                    }
                    
                    crop.growSeason = growSeason;
                    crop.harvestType = harvestType;
                    
                    crops.push_back(crop);
                    DEBUG_PRINT("Loaded crop: " + name);
                }
                catch (const exception& e) {
                    DEBUG_PRINT("Error parsing crop data line: " + string(e.what()));
                    // Continue to next line if there's an error
                    continue;
                }
            }
            
            inFile.close();
            cout << "Data tanaman berhasil dimuat!" << endl;
            DEBUG_PRINT("Crops data loaded successfully, total crops: " + to_string(crops.size()));
        } else {
            DEBUG_PRINT("crops.txt not found, will initialize default crops");
        }
    }
    catch (const exception& e) {
        cerr << "Error loading crops data: " << e.what() << endl;
    }
}