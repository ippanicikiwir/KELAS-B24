#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>

using namespace std;

bool login() {
    string username, password;
    const string correct_username = "ikhwan hariyanto";
    const string correct_password = "2409106082";
    int attempts = 3;
    
    while (attempts > 0) {
        cout << "Masukkan Username: ";
        getline(cin, username);
        
        cout << "Masukkan Password: ";
        getline(cin, password);

        #ifdef _WIN32
        system("cls");
        #else
        system("clear"); 
        #endif
        
        if (username == correct_username && password == correct_password) {
            return true;
        } else {
            attempts--;
            cout << "LOGIN GAGAL! Anda memiliki " << attempts << " kesempatan lagi." << endl;
            if (attempts > 0) {
                cout << "Masukkan nama dan password dengan benar..." << endl;
            }
        }
    }
    
    cout << "Kesempatan telah habis! Program berhenti." << endl;
    return false;
}

void konversimatauang() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    int pilihan;
    double jumlah, hasil;

    const double IDR_TO_USD = 16347.0;
    const double IDR_TO_EUR = 17606.0;  
    const double USD_TO_EUR = 1.077;  

    cout << "\n=== Konversi Mata Uang ===\n";
    cout << "1. Rupiah ke Dolar AS\n";
    cout << "2. Rupiah ke Euro\n";
    cout << "3. Dolar AS ke Rupiah\n";
    cout << "4. Dolar AS ke Euro\n";
    cout << "5. Euro ke Rupiah\n";
    cout << "6. Euro ke Dolar AS\n";
    cout << "7. Kembali\n";
    cout << "Pilih opsi: ";

    if (!(cin >> pilihan)) {
        cout << "Input tidak valid! Masukkan angka.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("pause");
        return;
    }

    if (pilihan == 7) {
        cout << "Kembali ke menu utama...\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (pilihan >= 1 && pilihan <= 6) {
        cout << "Masukkan jumlah: ";
        if (!(cin >> jumlah)) {
            cout << "Input tidak valid! Masukkan angka.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("pause");
            return;
        }

        switch (pilihan) {
            case 1:
                hasil = jumlah / IDR_TO_USD;
                cout << jumlah << " IDR = " << hasil << " USD\n";
                break;
            case 2:
                hasil = jumlah / IDR_TO_EUR;
                cout << jumlah << " IDR = " << hasil << " EUR\n";
                break;
            case 3:
                hasil = jumlah * IDR_TO_USD;
                cout << jumlah << " USD = " << hasil << " IDR\n";
                break;
            case 4:
                hasil = jumlah * USD_TO_EUR;
                cout << jumlah << " USD = " << hasil << " EUR\n";
                break;
            case 5:
                hasil = jumlah * IDR_TO_EUR;
                cout << jumlah << " EUR = " << hasil << " IDR\n";
                break;
            case 6:
                hasil = jumlah / USD_TO_EUR;
                cout << jumlah << " EUR = " << hasil << " USD\n";
                break;
        }
    } else {
        cout << "Pilihan tidak valid!\n";
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void konversisuhu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    int pilihan;
    double suhu, hasil;

    cout << "\n=== Konversi Suhu ===" << endl;
    cout << "1. Celcius ke Fahrenheit" << endl;
    cout << "2. Fahrenheit ke Celcius" << endl;
    cout << "3. Kembali" << endl;
    cout << "Pilih opsi: ";
    
    if (!(cin >> pilihan)) {
        cout << "Input tidak valid! Masukkan angka." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    if (pilihan == 3) {
        cout << "Kembali ke menu utama..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (pilihan == 1) {
        cout << "Masukkan suhu dalam Celcius: ";
        if (!(cin >> suhu)) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return;
        }
        hasil = (suhu * 9.0 / 5.0) + 32;
        cout << suhu << " Celcius = " << hasil << " Fahrenheit" << endl;
    } else if (pilihan == 2) {
        cout << "Masukkan suhu dalam Fahrenheit: ";
        if (!(cin >> suhu)) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return;
        }
        hasil = (suhu - 32) * 5.0 / 9.0;
        cout << suhu << " Fahrenheit = " << hasil << " Celcius" << endl;
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void konversijarak() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    int pilihan;
    double jarak, hasil;

    cout << "\n=== Konversi Jarak ===" << endl;
    cout << "1. Kilometer ke Meter" << endl;
    cout << "2. Kilometer ke Centimeter" << endl;
    cout << "3. Meter ke Kilometer" << endl;
    cout << "4. Meter ke Centimeter" << endl;
    cout << "5. Centimeter ke Kilometer" << endl;
    cout << "6. Centimeter ke Meter" << endl;
    cout << "7. Kembali" << endl;
    cout << "Pilih opsi: ";
    
    if (!(cin >> pilihan)) {
        cout << "Input tidak valid! Masukkan angka." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    if (pilihan == 7) {
        cout << "Kembali ke menu utama..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (pilihan >= 1 && pilihan <= 6) {
        switch (pilihan) {
            case 1:
                cout << "Masukkan jarak dalam Kilometer: ";
                break;
            case 2:
                cout << "Masukkan jarak dalam Kilometer: ";
                break;
            case 3:
                cout << "Masukkan jarak dalam Meter: ";
                break;
            case 4:
                cout << "Masukkan jarak dalam Meter: ";
                break;
            case 5:
                cout << "Masukkan jarak dalam Centimeter: ";
                break;
            case 6:
                cout << "Masukkan jarak dalam Centimeter: ";
                break;
        }
        
        if (!(cin >> jarak)) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return;
        }

        switch (pilihan) {
            case 1: // Kilometer ke Meter
                hasil = jarak * 1000;
                cout << jarak << " Kilometer = " << hasil << " Meter" << endl;
                break;
            case 2: // Kilometer ke Centimeter
                hasil = jarak * 100000;
                cout << jarak << " Kilometer = " << hasil << " Centimeter" << endl;
                break;
            case 3: // Meter ke Kilometer
                hasil = jarak / 1000;
                cout << jarak << " Meter = " << hasil << " Kilometer" << endl;
                break;
            case 4: // Meter ke Centimeter
                hasil = jarak * 100;
                cout << jarak << " Meter = " << hasil << " Centimeter" << endl;
                break;
            case 5: // Centimeter ke Kilometer
                hasil = jarak / 100000;
                cout << jarak << " Centimeter = " << hasil << " Kilometer" << endl;
                break;
            case 6: // Centimeter ke Meter
                hasil = jarak / 100;
                cout << jarak << " Centimeter = " << hasil << " Meter" << endl;
                break;
        }
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void konversiwaktu() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    int pilihan;
    double waktu, hasil;

    cout << "\n=== Konversi Waktu ===" << endl;
    cout << "1. Jam ke Menit" << endl;
    cout << "2. Jam ke Detik" << endl;
    cout << "3. Menit ke Jam" << endl;
    cout << "4. Menit ke Detik" << endl;
    cout << "5. Detik ke Jam" << endl;
    cout << "6. Detik ke Menit" << endl;
    cout << "7. Kembali" << endl;
    cout << "Pilih opsi: ";
    
    if (!(cin >> pilihan)) {
        cout << "Input tidak valid! Masukkan angka." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nTekan Enter untuk melanjutkan...";
        cin.get();
        return;
    }

    if (pilihan == 7) {
        cout << "Kembali ke menu utama..." << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return;
    }

    if (pilihan >= 1 && pilihan <= 6) {
        cout << "Masukkan waktu: ";
        if (!(cin >> waktu)) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            return;
        }

        switch (pilihan) {
            case 1:
                hasil = waktu * 60;
                cout << waktu << " Jam = " << hasil << " Menit" << endl;
                break;
            case 2:
                hasil = waktu * 3600;
                cout << waktu << " Jam = " << hasil << " Detik" << endl;
                break;
            case 3:
                hasil = waktu / 60;
                cout << waktu << " Menit = " << hasil << " Jam" << endl;
                break;
            case 4:
                hasil = waktu * 60;
                cout << waktu << " Menit = " << hasil << " Detik" << endl;
                break;
            case 5:
                hasil = waktu / 3600;
                cout << waktu << " Detik = " << hasil << " Jam" << endl;
                break;
            case 6:
                hasil = waktu / 60;
                cout << waktu << " Detik = " << hasil << " Menit" << endl;
                break;
        }
    } else {
        cout << "Pilihan tidak valid!" << endl;
    }
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.get();
}

void menu() {
    while (true) {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        int pilihan;
        cout << "============================" << endl;
        cout << "===      Menu Utama      ===" << endl;
        cout << "============================" << endl;
        cout << "\n1. Konversi Suhu" << endl;
        cout << "2. Konversi Jarak" << endl;
        cout << "3. Konversi Waktu" << endl;
        cout << "4. Konversi Mata Uang" << endl;
        cout << "5. Logout" << endl;
        cout << "Pilih menu: ";
        
        if (!(cin >> pilihan)) {
            cout << "Input tidak valid! Masukkan angka." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nTekan Enter untuk melanjutkan...";
            cin.get();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (pilihan) {
            case 1:
                konversisuhu();
                break;
            case 2:
                konversijarak();
                break;
            case 3:
                konversiwaktu();
                break;
            case 4:
                konversimatauang();
                break;
            case 5:
                cout << "Logout Berhasil!\n" << endl;
                cout << "Terima kasih telah memakai program Ippan Icikiwir!" << endl;
                cout << "Semoga harimu menyenangkan!" << endl;
                return;
            default:
                cout << "Pilihan tidak valid, silakan coba lagi!" << endl;
                cout << "\nTekan Enter untuk melanjutkan...";
                cin.get();
        }
    }
}

int main() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    cout << "============================" << endl;
    cout << "==    Program Konversi    ==" << endl;
    cout << "============================" << endl;
    cout << "Silakan login terlebih dahulu" << endl;
    
    if (login()) {
        cout << "Login berhasil! Tekan Enter untuk melanjutkan..." << endl;
        cin.get();
        menu();
    }
    
    return 0;
}