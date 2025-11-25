#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> // untuk fungsi manipulasi karakter seperti tolower()
#include <time.h>

#define MAX 100

struct Mahasiswa {
    int id;
    char nim[20];
    char nama[50];
    int umur;
    float ipk;
    char status[30];
} data[MAX];

struct User{
    char username[30];
    char password [20];
    char role[10];
};

int jumlah = 0;

//Fungsi untuk cari berdasarkan NIM
int findIndexByNIM(char nim[]){
    for(int i = 0; i < jumlah; i++){
        if(strcmp(data[i].nim, nim) == 0){
            return i;
        }
    }
    return -1;
}

//Fungsi konversi string ke lowercase
void toLowerStr(const char *src, char *dst, size_t dstSize){
    size_t i = 0;
    if(dstSize == 0) return;
    while(src[i] != '\0' && i < dstSize - 1){
        dst[i] = (char)tolower((unsigned char)src[i]);
        i++;
    }
    dst[i] = '\0';
}

//Fungsi Validasi Status Mahasiswa
int validasiStatus(const char *status){
    char s[256];
    toLowerStr(status, s, sizeof s);
    if(strstr(s, "aktif") || strstr(s, "alumni") || strstr(s, "mengundurkan"))
        return 1;
    return 0;
}

//CRUD
void tambahData() {
    if (jumlah == MAX) {
        printf("  Data penuh!\n");
        return;
    }

    struct Mahasiswa *m = &data[jumlah];
    m->id = jumlah + 1;

    printf("\n=== TAMBAH DATA MAHASISWA ===\n");
    printf("Masukkan NIM     : ");
    scanf(" %[^\n]", m->nim);
    if(findIndexByNIM(m->nim) != -1){
        printf("NIM sudah terdaftar! Gunakan NIM lain.\n");
        return;
    }
    printf("Masukkan Nama    : ");
    scanf(" %[^\n]", m->nama);
    printf("Masukkan Umur    : ");
    scanf("%d", &m->umur);
    printf("Masukkan IPK     : ");
    scanf("%f", &m->ipk);

    do{
        printf("Masukkan Status (Aktif/Alumni/Mengundurkan Diri): ");
        scanf(" %[^\n]", m->status);
        if(!validasiStatus(m->status)){
            printf("Status tidak valid! Ulangi.\n");
        }
    }while(!validasiStatus(m->status));

    jumlah++;
    printf("\nData berhasil ditambahkan!\n");
}

void tampilData() {
    if (jumlah == 0) {
        printf("\n Belum ada data.\n");
        return;
    }

    printf("\n===== DAFTAR MAHASISWA =====\n");
    printf("+------+------------+-------------------------------------+--------+-------+----------------------+\n");
    printf("| %-4s | %-10s | %-35s | %-6s | %-5s | %-20s |\n",
           "ID", "NIM", "Nama", "Umur", "IPK", "Status");
    printf("+------+------------+-------------------------------------+--------+-------+----------------------+\n");
    for (int i = 0; i < jumlah; i++) {
        printf("| %-4d | %-10s | %-35s | %-6d | %-5.2f | %-20s |\n",
               data[i].id,
               data[i].nim,
               data[i].nama,
               data[i].umur,
               data[i].ipk,
               data[i].status);
    }
    printf("+------+------------+-------------------------------------+--------+-------+----------------------+\n");
}

void editData() {
    if (jumlah == 0){
        printf("\n Tidak ada data untuk diedit!\n");
        return;
    }

    char nimEdit[20];
    printf("\nMasukkan NIM yang ingin diedit: ");
    scanf(" %[^\n]", nimEdit);

    int index = findIndexByNIM(nimEdit);
    if (index == -1){
        printf(" NIM tidak ditemukan!\n");
        return;
    }

    struct Mahasiswa *m = &data[index];

    printf("\n=== DATA LAMA ===\n");
    printf("NIM     : %s\n", m->nim);
    printf("Nama    : %s\n", m->nama);
    printf("Umur    : %d\n", m->umur);
    printf("IPK     : %.2f\n", m->ipk);
    printf("Status  : %s\n", m->status);

    char konfirmasi;
    printf("\nApakah Anda yakin ingin mengedit data ini? (y/n): ");
    scanf(" %c", &konfirmasi);
    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        printf(" Edit dibatalkan.\n");
        return;
    }

    printf("\n=== MASUKKAN DATA BARU ===\n");
    printf("Masukkan NIM     : ");
    scanf(" %[^\n]", m->nim);
    printf("Masukkan Nama    : ");
    scanf(" %[^\n]", m->nama);
    printf("Masukkan Umur    : ");
    scanf("%d", &m->umur);
    printf("Masukkan IPK     : ");
    scanf("%f", &m->ipk);

    do{
        printf("Masukkan Status (Aktif/Alumni/Mengundurkan Diri): ");
        scanf(" %[^\n]", m->status);
        if(!validasiStatus(m->status)){
            printf("Status tidak valid! Ulangi.\n");
        }
    }while(!validasiStatus(m->status));

    printf("\nData berhasil diperbarui!\n");
}


void hapusData() {
    if(jumlah == 0) {
        printf("\nTidak ada data untuk dihapus!\n");
        return;
    }

    char nimHapus[20];
    printf("\nMasukkan NIM yang ingin dihapus: ");
    scanf(" %[^\n]", nimHapus);

    int index = findIndexByNIM(nimHapus);
    if(index == -1) {
        printf("NIM tidak ditemukan!\n");
        return;
    }

    struct Mahasiswa *m = &data[index];

    printf("\n======= DATA YANG AKAN DIHAPUS =======\n");
    printf("NIM     : %s\n", m->nim);
    printf("Nama    : %s\n", m->nama);
    printf("Umur    : %d\n", m->umur);
    printf("IPK     : %.2f\n", m->ipk);
    printf("Status  : %s\n", m->status);

    char konfirmasi;
    printf("\nApakah Anda yakin ingin menghapus data ini? (y/n): ");
    scanf(" %c", &konfirmasi);
    if(konfirmasi != 'y' && konfirmasi != 'Y'){
        printf("\nPenghapusan dibatalkan.\n");
        return;
    }

    for(int i = index; i < jumlah - 1; i++) {
        data[i] = data[i + 1];
        data[i].id = i + 1;
    }

    jumlah--;
    printf("Data berhasil dihapus!\n");
}

void cariData() {
    if (jumlah == 0) {
        printf("\nTidak ada data untuk dicari!\n");
        return;
    }

    char nimCari[20];
    int ditemukan = 0;

    printf("\nMasukkan NIM yang ingin dicari: ");
    scanf(" %[^\n]", nimCari);

    printf("\nHasil pencarian untuk '%s':\n", nimCari);
    printf("+------+------------+-------------------------------------+--------+-------+----------------------+\n");
    printf("| %-4s | %-10s | %-35s | %-6s | %-5s | %-20s |\n",
           "ID", "NIM", "Nama", "Umur", "IPK", "Status");
    printf("+------+------------+-------------------------------------+--------+-------+----------------------+\n");

    for (int i = 0; i < jumlah; i++) {
        if (strcmp(data[i].nim, nimCari) == 0) {
            printf("| %-4d | %-10s | %-35s | %-6d | %-5.2f | %-20s |\n",
                   data[i].id,
                   data[i].nim,
                   data[i].nama,
                   data[i].umur,
                   data[i].ipk,
                   data[i].status);
            ditemukan = 1;
            break; //karena NIM bersifat unik, cukup tampilkan satu hasil
        }
    }

    if (!ditemukan)
        printf("Data tidak ditemukan.\n");
    printf("+------+------------+-------------------------------------+--------+-------+----------------------+\n");
}

//FILE HANDLING
//simpan data ke file teks
void simpanData(){
    FILE *f = fopen("data_mahasiswa.csv", "w");
    if(!f){
        printf("Gagal membuka file untuk menyimpan data!\n");
        return;
    }
    for(int i = 0; i < jumlah; i++){
        fprintf(f, "%d;%s;%s;%d;%.2f;%s\n", data[i].id, data[i].nim, data[i].nama, data[i].umur, data[i].ipk, data[i].status);
    }
    fclose(f);
    printf("Data berhasil disimpan ke file!\n");
}

void bacaData(){
    FILE *f = fopen("data_mahasiswa.csv", "r");
    if(f == NULL){
        printf("File data tidak ditemukan (belum ada data tersimpan).\n");
        return;
    }
    jumlah = 0;
    while(fscanf(f, "%d;%19[^;];%49[^;];%d;%f;%29[^\n]\n",
                 &data[jumlah].id,
                 data[jumlah].nim,
                 data[jumlah].nama,
                 &data[jumlah].umur,
                 &data[jumlah].ipk,
                 data[jumlah].status) == 6){
        jumlah++;
    }
    fclose(f);

    for(int i = 0; i < jumlah; i++){
        data[i].id = i + 1;
    }

    printf("Data berhasil dibaca dari file! (%d data)\n", jumlah);
}

//SORTING BERDASARKAN IPK
void urutkanData(){
    if(jumlah == 0){
        printf("\nTidak ada data untuk di urutkan!\n");
        return;
    }
    struct Mahasiswa temp;
    for(int i = 0; i < jumlah - 1; i++){
        for(int j = i + 1; j < jumlah; j++){
            if(data[i].ipk < data[j].ipk){
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }

    for(int i = 0; i < jumlah; i++){
        data[i].id = i + 1;
    }

    printf("\nData berhasil diurutkan berdasarkan IPK (Tertinggi ke Terendah).\n");
    tampilData();
}

void statistikMahasiswa(){
    if(jumlah == 0){
        printf("\nBelum ada data untuk statistik.\n");
        return;
    }
    float total = 0.0;
    float maxIPK = data[0].ipk;
    float minIPK = data[0].ipk;
    int idxMax = 0, idxMin = 0;

    for(int i = 0; i < jumlah; i++){
        total += data[i].ipk;
        if(data[i].ipk > maxIPK){
            maxIPK = data[i].ipk;
            idxMax = i;
        }
        if(data[i].ipk < minIPK){
            minIPK = data[i].ipk;
            idxMin = i;
        }
    }
    printf("\n======= STATISTIK MAHASISWA =======\n");
    printf("Total Mahasiswa : %d\n", jumlah);
    printf("Rata-rata IPK   : %.2f\n", total / jumlah);
    printf("IPK Tertinggi   : %.2f (%s)\n", maxIPK, data[idxMax].nama);
    printf("IPK Terendah    : %.2f (%s)\n", minIPK, data[idxMin].nama);
}

void cetakPDF(struct Mahasiswa m) {
    FILE *pdf = fopen("laporan_mahasiswa.pdf", "w");

    if (!pdf) {
        printf("Gagal membuat PDF!\n");
        return;
    }

    // ambil tanggal current
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char tanggal[40];
    strftime(tanggal, sizeof(tanggal), "%d-%m-%Y %H:%M", t);

    const char *UNIVERSITAS = "Universitas Kristen Satya Wacana";

    fprintf(pdf, "%%PDF-1.1\n");
    fprintf(pdf, "1 0 obj << /Type /Catalog /Pages 2 0 R >> endobj\n");
    fprintf(pdf, "2 0 obj << /Type /Pages /Kids [3 0 R] /Count 1 >> endobj\n");
    fprintf(pdf, "3 0 obj << /Type /Page /Parent 2 0 R /MediaBox [0 0 595 842] /Contents 4 0 R >> endobj\n");

    char content[6000] = "";
    char line[300];

    // Judul
    sprintf(line, "BT /F1 18 Tf 50 800 Td (Laporan Data Mahasiswa) Tj ET\n");
    strcat(content, line);

    // Dicetak oleh
    sprintf(line, "\nBT /F1 12 Tf 50 780 Td (Dicetak oleh: %s) Tj ET\n", UNIVERSITAS);
    strcat(content, line);

    // Tanggal
    sprintf(line, "BT /F1 12 Tf 50 760 Td (Tanggal Cetak: %s) Tj ET\n", tanggal);
    strcat(content, line);

    // Garis
    sprintf(line, "BT /F1 12 Tf 50 740 Td (--------------------------------------------) Tj ET\n");
    strcat(content, line);

    // Data mahasiswa
    sprintf(line, "BT /F1 12 Tf 50 710 Td (ID: %d) Tj ET\n", m.id);
    strcat(content, line);

    sprintf(line, "BT /F1 12 Tf 50 690 Td (NIM: %s) Tj ET\n", m.nim);
    strcat(content, line);

    sprintf(line, "BT /F1 12 Tf 50 670 Td (Nama: %s) Tj ET\n", m.nama);
    strcat(content, line);

    sprintf(line, "BT /F1 12 Tf 50 650 Td (Umur: %d tahun) Tj ET\n", m.umur);
    strcat(content, line);

    sprintf(line, "BT /F1 12 Tf 50 630 Td (IPK: %.2f) Tj ET\n", m.ipk);
    strcat(content, line);

    sprintf(line, "BT /F1 12 Tf 50 610 Td (Status: %s) Tj ET\n", m.status);
    strcat(content, line);

    fprintf(pdf, "4 0 obj << /Length %lu >> stream\n", strlen(content));
    fprintf(pdf, "%s", content);
    fprintf(pdf, "endstream endobj\n");

    fprintf(pdf, "xref\n0 5\n0000000000 65535 f \n");
    fprintf(pdf, "trailer << /Root 1 0 R /Size 5 >>\n");
    fprintf(pdf, "startxref\n500\n%%EOF");

    fclose(pdf);

    printf("\nPDF berhasil dibuat: laporan_mahasiswa.pdf\n");
}

void tekanEnter(){
    printf("\nTekan ENTER untuk kembali ke menu utama...");
    while (getchar() != '\n');
    getchar();
}


// Sistem Login
int login(struct User *loggedIn){
    FILE *f = fopen("akun.txt", "r");
    if(!f){
        f = fopen("akun.txt", "w");
        fprintf(f, "admin;admin123;admin\n");
        fprintf(f, "user;user123;user\n");
        fclose(f);
        f = fopen("akun.txt", "r");
    }

    char username[30], password[20];
    printf("\n======= SISTEM LOGIN =======\n");
    printf("Username: ");
    scanf(" %[^\n]", username);
    printf("Password: ");
    scanf(" %[^\n]", password);

    struct User temp;
    int found = 0;
    while(fscanf(f, "%29[^;];%29[^;];%9[^\n]\n", temp.username, temp.password, temp.role) == 3){
        if(strcmp(temp.username, username) == 0 && strcmp(temp.password, password) == 0){
            *loggedIn = temp;
            found = 1;
            break;
        }
    }
    fclose(f);
    return found;
}

int main() {
    struct User user;
    bacaData();

    if (!login(&user)) {
        printf("Login Gagal! Username atau password salah.\n");
        return 0;
    }

    printf("\nSelamat Datang, %s! (Role: %s)\n\n", user.username, user.role);
    printf("Tekan ENTER untuk melanjutkan...");
    getchar();
    getchar();


    int pilihan;

    if (strcmp(user.role, "admin") == 0) {
        do {
            system("cls");
            printf("\n======= MENU MAHASISWA =======\n");
            printf("1. Tambah Data\n");
            printf("2. Tampilkan Data\n");
            printf("3. Edit Data\n");
            printf("4. Hapus Data\n");
            printf("5. Cari Data\n");
            printf("6. Sorting Data berdasarkan IPK\n");
            printf("7. Statistik Mahasiswa\n");
            printf("8. Simpan ke File\n");
            printf("9. Cetak PDF\n");
            printf("10. Keluar\n");
            printf("==========================\n");
            printf("Pilih menu: ");
            scanf("%d", &pilihan);

            switch (pilihan) {
                case 1:
                    system("cls");
                    tambahData();
                    tekanEnter();
                    break;
                case 2:
                    system("cls");
                    tampilData();
                    tekanEnter();
                    break;
                case 3:
                    system("cls");
                    editData();
                    tekanEnter();
                    break;
                case 4:
                    system("cls");
                    hapusData();
                    tekanEnter();
                    break;
                case 5:
                    system("cls");
                    cariData();
                    tekanEnter();
                    break;
                case 6:
                    system("cls");
                    urutkanData();
                    tekanEnter();
                    break;
                case 7:
                    system("cls");
                    statistikMahasiswa();
                    tekanEnter();
                    break;
                case 8:
                    system("cls");
                    simpanData();
                    tekanEnter();
                    break;
                case 9: {
                    system("cls");
                    char nimCetak[20];
                    printf("Masukkan NIM mahasiswa yang ingin dicetak: ");
                    scanf(" %[^\n]", nimCetak);

                    int idx = findIndexByNIM(nimCetak);
                    if (idx == -1) {
                            printf("NIM tidak ditemukan!\n");
                    } else {
                        cetakPDF(data[idx]);
                    }
                    tekanEnter();
                    break;
                    }
                case 10:
                    printf("\nProgram selesai. Terima kasih!\n");
                    break;
                default:
                    printf("Pilihan tidak valid!\n");
            }
            printf("\nTekan Enter untuk kembali ke Menu Utama...");
        } while (pilihan != 9);

    } else if (strcmp(user.role, "user") == 0) {
        do {
            system("cls");
            printf("\n======= MENU MAHASISWA =======\n");
            printf("1. Tampilkan Data\n");
            printf("2. Cari Data\n");
            printf("3. Keluar\n");
            printf("=========================\n");
            printf("Pilih menu: ");
            scanf("%d", &pilihan);

            switch (pilihan) {
                case 1:
                    system("cls");
                    tampilData();
                    tekanEnter();
                    break;
                case 2:
                    system("cls");
                    cariData();
                    tekanEnter();
                    break;
                case 3:
                    printf("Keluar dari sistem...\n");
                    break;
                default:
                    printf("Menu tidak tersedia! Silakan pilih 1, 2, atau 3.\n");
            }
        } while (pilihan != 3);
    }

    return 0;
}