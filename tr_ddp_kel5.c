#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

struct Mahasiswa {
    int id;
    char nim[20];
    char nama[50];
    int umur;
    float ipk;
    char status[30];
} data[MAX];

int jumlah = 0;

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
    printf("Masukkan Nama    : ");
    scanf(" %[^\n]", m->nama);
    printf("Masukkan Umur    : ");
    scanf("%d", &m->umur);
    printf("Masukkan IPK     : ");
    scanf("%f", &m->ipk);
    printf("Masukkan Status  (Aktif/Alumni/Mengundurkan Diri): ");
    scanf(" %[^\n]", m->status);

    jumlah++;
    printf("\nData berhasil ditambahkan!\n");
}

void tampilData() {
    if (jumlah == 0) {
        printf("\n Belum ada data.\n");
        return;
    }

    printf("\n===== DAFTAR MAHASISWA =====\n");
    printf("%-4s %-10s %-20s %-6s %-5s %-20s\n",
           "ID", "NIM", "Nama", "Umur", "IPK", "Status");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        printf("%-4d %-10s %-20s %-6d %-5.2f %-20s\n",
               data[i].id,
               data[i].nim,
               data[i].nama,
               data[i].umur,
               data[i].ipk,
               data[i].status);
    }
}

void editData() {
    if (jumlah == 0) {
        printf("\n Tidak ada data untuk diedit!\n");
        return;
    }

    int idEdit;
    printf("\nMasukkan ID yang ingin diedit: ");
    scanf("%d", &idEdit);

    if (idEdit < 1 || idEdit > jumlah) {
        printf(" ID tidak ditemukan!\n");
        return;
    }

    struct Mahasiswa *m = &data[idEdit - 1];

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
    printf("Masukkan Status  (Aktif/Alumni/Mengundurkan Diri): ");
    scanf(" %[^\n]", m->status);

    printf("\n Data berhasil diperbarui!\n");
}


void hapusData() {
    if (jumlah == 0) {
        printf("\n  Tidak ada data untuk dihapus!\n");
        return;
    }

    int idHapus;
    printf("\nMasukkan ID yang ingin dihapus: ");
    scanf("%d", &idHapus);

    if (idHapus < 1 || idHapus > jumlah) {
        printf(" ID tidak valid!\n");
        return;
    }

    for (int i = idHapus - 1; i < jumlah - 1; i++) {
        data[i] = data[i + 1];
        data[i].id = i + 1;
    }

    jumlah--;
    printf(" Data berhasil dihapus!\n");
}

void cariData() {
    if (jumlah == 0) {
        printf("\n Tidak ada data untuk dicari!\n");
        return;
    }

    char keyword[50];
    int ditemukan = 0;

    printf("\nMasukkan NIM atau Nama yang ingin dicari: ");
    scanf(" %[^\n]", keyword);

    printf("\nHasil pencarian untuk '%s':\n", keyword);
    printf("-----------------------------------------------------------------\n");
    printf("%-4s %-10s %-20s %-6s %-5s %-20s\n",
           "ID", "NIM", "Nama", "Umur", "IPK", "Status");
    printf("-----------------------------------------------------------------\n");

    for (int i = 0; i < jumlah; i++) {
        if (strstr(data[i].nim, keyword) || strstr(data[i].nama, keyword)) {
            printf("%-4d %-10s %-20s %-6d %-5.2f %-20s\n",
                   data[i].id,
                   data[i].nim,
                   data[i].nama,
                   data[i].umur,
                   data[i].ipk,
                   data[i].status);
            ditemukan = 1;
        }
    }

    if (!ditemukan)
        printf(" Data tidak ditemukan.\n");
    printf("-----------------------------------------------------------------\n");
}

//FILE HANDLING
//simpan data ke file teks
void simpanData(){
    FILE *f = fopen("data_mahasiswa.txt", "w");
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
    FILE *f = fopen("data_mahasiswa.txt", "r");
    if(!f){
        printf("File data tidak ditemukan (belum ada file).\n");
        return;
    }
    jumlah = 0;
    while(fscanf(f, "%d;%[^;];%[^;];%d;%f;%[^\n]\n", &data[jumlah].id, &data[jumlah].nim, &data[jumlah].nama, &data[jumlah].umur, &data[jumlah].ipk, &data[jumlah].status) == 6){
        jumlah++;
    }
    fclose(f);
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
    printf("\nData berhasil diurutkan berdasarkan IPK (Tertinggi ke Terendah).\n");
    tampilData();
}

int main() {
    int pilihan;

    do {
        printf("\n===== MENU MAHASISWA =====\n");
        printf("1. Tambah Data\n");
        printf("2. Tampilkan Data\n");
        printf("3. Edit Data\n");
        printf("4. Hapus Data\n");
        printf("5. Cari Data\n");
        printf("6. Sorting Data berdasarkan IPK\n");
        printf("7. Simpan ke File\n");
        printf("8. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahData(); break;
            case 2: tampilData(); break;
            case 3: editData(); break;
            case 4: hapusData(); break;
            case 5: cariData(); break;
            case 6: urutkanData(); break;
            case 7: simpanData(); break;
            case 8: printf("\nProgram selesai. Terima kasih!\n"); break;
            default: printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 8);

    return 0;
}