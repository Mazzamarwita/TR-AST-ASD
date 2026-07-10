<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "reservasi.txt"

/* =========================================================
   STRUCT NODE LINKED LIST
   ========================================================= */
typedef struct Node {
    int id;
    char nama[50];
    char noTelp[20];
    char tipeKamar[30];
    char checkIn[15];
    char checkOut[15];
    int jumlahMalam;
    int hargaPerMalam;
    int totalBayar;

    struct Node *next;
} Node;

/* Head Linked List */
Node *head = NULL;


/* =========================================================
   PROTOTYPE FUNCTION
   ========================================================= */
void menuUtama();

void tambahReservasi();
void tampilkanReservasi();
void ubahReservasi();
void hapusReservasi();

void cariReservasi();
void urutkanNama();

void simpanKeFile();
void muatDariFile();

void tampilkanSatuData(Node *data);

int idSudahAda(int id);

void inputString(char str[], int ukuran);
void bersihkanBuffer();
void tekanEnter();
void bebaskanMemori();


/* =========================================================
   FUNGSI MAIN
   ========================================================= */
int main() {

    /* Bersihkan layar saat program dimulai */
    system("cls");

    /* Membaca data dari file */
    muatDariFile();

    /* Masuk menu utama */
    menuUtama();

    /* Membebaskan memori */
    bebaskanMemori();

    return 0;
}


/* =========================================================
   MENU UTAMA
   ========================================================= */
void menuUtama() {
    int pilihan;

    do {
        /* Bersihkan layar setiap kembali ke menu */
        system("cls");

        printf("=========================================\n");
        printf("      SISTEM RESERVASI HOTEL\n");
        printf("=========================================\n");
        printf("1. Tambah Reservasi\n");
        printf("2. Tampilkan Semua Reservasi\n");
        printf("3. Ubah Reservasi\n");
        printf("4. Hapus Reservasi\n");
        printf("5. Cari Reservasi\n");
        printf("6. Urutkan Berdasarkan Nama\n");
        printf("0. Keluar\n");
        printf("=========================================\n");
        printf("Pilih menu: ");

        if (scanf("%d", &pilihan) != 1) {
            bersihkanBuffer();
            pilihan = -1;
        } else {
            bersihkanBuffer();
        }

        switch (pilihan) {

            case 1:
                system("cls");
                tambahReservasi();
                break;

            case 2:
                system("cls");
                tampilkanReservasi();
                break;

            case 3:
                system("cls");
                ubahReservasi();
                break;

            case 4:
                system("cls");
                hapusReservasi();
                break;

            case 5:
                system("cls");
                cariReservasi();
                break;

            case 6:
                system("cls");
                urutkanNama();
                break;

            case 0:
                system("cls");

                simpanKeFile();

                printf("=========================================\n");
                printf("           PROGRAM SELESAI\n");
                printf("=========================================\n");
                printf("Data telah disimpan.\n");
                printf("Terima kasih telah menggunakan program.\n");
                printf("=========================================\n");
                break;

            default:
                printf("\nPilihan tidak valid!\n");
                tekanEnter();
                system("cls");
        }

    } while (pilihan != 0);
}


/* =========================================================
   CREATE - TAMBAH RESERVASI
   ========================================================= */
void tambahReservasi() {
    Node *baru;
    Node *bantu;

    int idBaru;
    int pilihanKamar;

    /* Bersihkan layar */
    system("cls");

    printf("=========================================\n");
    printf("          TAMBAH RESERVASI\n");
    printf("=========================================\n");

    printf("Masukkan ID Reservasi : ");

    if (scanf("%d", &idBaru) != 1) {
        bersihkanBuffer();

        printf("\nID harus berupa angka!\n");

        tekanEnter();
        system("cls");
        return;
    }

    bersihkanBuffer();

    /* Cek apakah ID sudah digunakan */
    if (idSudahAda(idBaru)) {
        printf("\nID reservasi sudah digunakan!\n");

        tekanEnter();
        system("cls");
        return;
    }

    /* Alokasi memori node baru */
    baru = (Node *)malloc(sizeof(Node));

    if (baru == NULL) {
        printf("\nGagal mengalokasikan memori!\n");

        tekanEnter();
        system("cls");
        return;
    }

    /* Isi ID */
    baru->id = idBaru;

    /* Input nama tamu */
    printf("Masukkan Nama Tamu    : ");
    inputString(baru->nama, sizeof(baru->nama));

    /* Input nomor telepon */
    printf("Masukkan No. Telepon  : ");
    inputString(baru->noTelp, sizeof(baru->noTelp));

    /* Pilihan tipe kamar */
    printf("\n=========================================\n");
    printf("             JENIS KAMAR\n");
    printf("=========================================\n");
    printf("1. Standard  - Rp 300000 / malam\n");
    printf("2. Deluxe    - Rp 500000 / malam\n");
    printf("3. Suite     - Rp 800000 / malam\n");
    printf("=========================================\n");

    printf("Pilih tipe kamar      : ");

    if (scanf("%d", &pilihanKamar) != 1) {
        bersihkanBuffer();
        pilihanKamar = 1;
    } else {
        bersihkanBuffer();
    }

    /* Menentukan tipe kamar */
    switch (pilihanKamar) {

        case 1:
            strcpy(baru->tipeKamar, "Standard");
            baru->hargaPerMalam = 300000;
            break;

        case 2:
            strcpy(baru->tipeKamar, "Deluxe");
            baru->hargaPerMalam = 500000;
            break;

        case 3:
            strcpy(baru->tipeKamar, "Suite");
            baru->hargaPerMalam = 800000;
            break;

        default:
            printf("\nPilihan tidak valid!\n");
            printf("Otomatis memilih kamar Standard.\n");

            strcpy(baru->tipeKamar, "Standard");
            baru->hargaPerMalam = 300000;
            break;
    }

    /* Input tanggal */
    printf("\nTanggal Check-In       : ");
    inputString(baru->checkIn, sizeof(baru->checkIn));

    printf("Tanggal Check-Out      : ");
    inputString(baru->checkOut, sizeof(baru->checkOut));

    /* Input jumlah malam */
    printf("Jumlah Malam           : ");

    if (scanf("%d", &baru->jumlahMalam) != 1) {
        bersihkanBuffer();

        free(baru);

        printf("\nJumlah malam harus berupa angka!\n");

        tekanEnter();
        system("cls");
        return;
    }

    bersihkanBuffer();

    /* Validasi jumlah malam */
    if (baru->jumlahMalam <= 0) {
        free(baru);

        printf("\nJumlah malam minimal 1!\n");

        tekanEnter();
        system("cls");
        return;
    }

    /* Hitung total bayar */
    baru->totalBayar =
        baru->hargaPerMalam *
        baru->jumlahMalam;

    /* Next awalnya NULL */
    baru->next = NULL;

    /* Memasukkan node ke Linked List */
    if (head == NULL) {

        head = baru;

    } else {

        bantu = head;

        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        bantu->next = baru;
    }

    /* Simpan otomatis ke file */
    simpanKeFile();

    printf("\n=========================================\n");
    printf("     RESERVASI BERHASIL DITAMBAHKAN\n");
    printf("=========================================\n");
    printf("ID Reservasi : %d\n", baru->id);
    printf("Nama Tamu    : %s\n", baru->nama);
    printf("Tipe Kamar   : %s\n", baru->tipeKamar);
    printf("Total Bayar  : Rp %d\n", baru->totalBayar);
    printf("=========================================\n");

    tekanEnter();

    /* Bersihkan layar setelah selesai */
    system("cls");
}


/* =========================================================
   READ - TAMPILKAN SEMUA RESERVASI
   ========================================================= */
void tampilkanReservasi() {
    Node *bantu;
    int nomor = 1;

    /* Bersihkan layar */
    system("cls");

    printf("============================================================\n");
    printf("                  DATA RESERVASI HOTEL\n");
    printf("============================================================\n");

    /* Cek apakah data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");

        tekanEnter();
        system("cls");
        return;
    }

    bantu = head;

    /* Traversal Linked List */
    while (bantu != NULL) {

        printf("\nReservasi Ke-%d\n", nomor);
        printf("------------------------------------------------------------\n");
        printf("ID Reservasi    : %d\n", bantu->id);
        printf("Nama Tamu       : %s\n", bantu->nama);
        printf("No. Telepon     : %s\n", bantu->noTelp);
        printf("Tipe Kamar      : %s\n", bantu->tipeKamar);
        printf("Check-In        : %s\n", bantu->checkIn);
        printf("Check-Out       : %s\n", bantu->checkOut);
        printf("Jumlah Malam    : %d\n", bantu->jumlahMalam);
        printf("Harga / Malam   : Rp %d\n", bantu->hargaPerMalam);
        printf("Total Bayar     : Rp %d\n", bantu->totalBayar);
        printf("------------------------------------------------------------\n");

        bantu = bantu->next;
        nomor++;
    }

    tekanEnter();

    /* Bersihkan layar */
    system("cls");
}


/* =========================================================
   UPDATE - UBAH RESERVASI
   ========================================================= */
void ubahReservasi() {
    Node *bantu;

    int idCari;
    int pilihanKamar;

    /* Bersihkan layar */
    system("cls");

    printf("=========================================\n");
    printf("           UBAH RESERVASI\n");
    printf("=========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");

        tekanEnter();
        system("cls");
        return;
    }

    printf("Masukkan ID yang akan diubah: ");

    if (scanf("%d", &idCari) != 1) {
        bersihkanBuffer();

        printf("\nID harus berupa angka!\n");

        tekanEnter();
        system("cls");
        return;
    }

    bersihkanBuffer();

    /* Mulai mencari dari head */
    bantu = head;

    while (bantu != NULL) {

        if (bantu->id == idCari) {

            system("cls");

            printf("=========================================\n");
            printf("           DATA DITEMUKAN\n");
            printf("=========================================\n");
            printf("ID Reservasi : %d\n", bantu->id);
            printf("Nama Lama    : %s\n", bantu->nama);
            printf("Tipe Kamar   : %s\n", bantu->tipeKamar);
            printf("=========================================\n");

            /* Input data baru */
            printf("\nMasukkan Nama Baru     : ");
            inputString(
                bantu->nama,
                sizeof(bantu->nama)
            );

            printf("Masukkan No. Telp Baru : ");
            inputString(
                bantu->noTelp,
                sizeof(bantu->noTelp)
            );

            printf("\n=========================================\n");
            printf("          JENIS KAMAR BARU\n");
            printf("=========================================\n");
            printf("1. Standard - Rp 300000\n");
            printf("2. Deluxe   - Rp 500000\n");
            printf("3. Suite    - Rp 800000\n");
            printf("=========================================\n");

            printf("Pilih tipe kamar: ");

            if (scanf("%d", &pilihanKamar) != 1) {
                bersihkanBuffer();
                pilihanKamar = 1;
            } else {
                bersihkanBuffer();
            }

            switch (pilihanKamar) {

                case 1:
                    strcpy(
                        bantu->tipeKamar,
                        "Standard"
                    );

                    bantu->hargaPerMalam = 300000;
                    break;

                case 2:
                    strcpy(
                        bantu->tipeKamar,
                        "Deluxe"
                    );

                    bantu->hargaPerMalam = 500000;
                    break;

                case 3:
                    strcpy(
                        bantu->tipeKamar,
                        "Suite"
                    );

                    bantu->hargaPerMalam = 800000;
                    break;

                default:
                    strcpy(
                        bantu->tipeKamar,
                        "Standard"
                    );

                    bantu->hargaPerMalam = 300000;
                    break;
            }

            printf("Check-In Baru           : ");
            inputString(
                bantu->checkIn,
                sizeof(bantu->checkIn)
            );

            printf("Check-Out Baru          : ");
            inputString(
                bantu->checkOut,
                sizeof(bantu->checkOut)
            );

            printf("Jumlah Malam Baru       : ");

            if (scanf("%d", &bantu->jumlahMalam) != 1) {
                bersihkanBuffer();

                printf("\nInput jumlah malam tidak valid!\n");

                tekanEnter();
                system("cls");
                return;
            }

            bersihkanBuffer();

            /* Validasi jumlah malam */
            if (bantu->jumlahMalam <= 0) {
                bantu->jumlahMalam = 1;
            }

            /* Hitung ulang total */
            bantu->totalBayar =
                bantu->hargaPerMalam *
                bantu->jumlahMalam;

            /* Simpan perubahan */
            simpanKeFile();

            printf("\n=========================================\n");
            printf("     RESERVASI BERHASIL DIUBAH\n");
            printf("=========================================\n");

            tekanEnter();

            /* Bersihkan layar */
            system("cls");

            return;
        }

        bantu = bantu->next;
    }

    printf("\nID reservasi tidak ditemukan!\n");

    tekanEnter();

    /* Bersihkan layar */
    system("cls");
}


/* =========================================================
   DELETE - HAPUS RESERVASI
   ========================================================= */
void hapusReservasi() {
    Node *bantu;
    Node *sebelum;

    int idHapus;
    char konfirmasi;

    /* Bersihkan layar */
    system("cls");

    printf("=========================================\n");
    printf("          HAPUS RESERVASI\n");
    printf("=========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");

        tekanEnter();
        system("cls");
        return;
    }

    printf("Masukkan ID yang akan dihapus: ");

    if (scanf("%d", &idHapus) != 1) {
        bersihkanBuffer();

        printf("\nID harus berupa angka!\n");

        tekanEnter();
        system("cls");
        return;
    }

    bersihkanBuffer();

    bantu = head;
    sebelum = NULL;

    /* Mencari node */
    while (bantu != NULL) {

        if (bantu->id == idHapus) {

            system("cls");

            printf("=========================================\n");
            printf("           DATA DITEMUKAN\n");
            printf("=========================================\n");
            printf("ID         : %d\n", bantu->id);
            printf("Nama       : %s\n", bantu->nama);
            printf("Tipe Kamar : %s\n", bantu->tipeKamar);
            printf("Total      : Rp %d\n", bantu->totalBayar);
            printf("=========================================\n");

            printf("\nYakin ingin menghapus? (y/n): ");
            scanf("%c", &konfirmasi);

            bersihkanBuffer();

            if (konfirmasi == 'y' ||
                konfirmasi == 'Y') {

                /* Jika node yang dihapus adalah head */
                if (sebelum == NULL) {

                    head = bantu->next;

                } else {

                    sebelum->next = bantu->next;
                }

                /* Hapus node */
                free(bantu);

                /* Update file */
                simpanKeFile();

                printf("\n=========================================\n");
                printf("   RESERVASI BERHASIL DIHAPUS\n");
                printf("=========================================\n");

            } else {

                printf("\nPenghapusan dibatalkan.\n");
            }

            tekanEnter();

            /* Bersihkan layar */
            system("cls");

            return;
        }

        sebelum = bantu;
        bantu = bantu->next;
    }

    printf("\nID reservasi tidak ditemukan!\n");

    tekanEnter();

    /* Bersihkan layar */
    system("cls");
}


/* =========================================================
   SEARCHING - CARI BERDASARKAN ID
   LINEAR SEARCH
   ========================================================= */
void cariReservasi() {
    Node *bantu;

    int idCari;

    /* Bersihkan layar */
    system("cls");

    printf("=========================================\n");
    printf("           CARI RESERVASI\n");
    printf("=========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");

        tekanEnter();
        system("cls");
        return;
    }

    printf("Masukkan ID Reservasi: ");

    if (scanf("%d", &idCari) != 1) {
        bersihkanBuffer();

        printf("\nID harus berupa angka!\n");

        tekanEnter();
        system("cls");
        return;
    }

    bersihkanBuffer();

    bantu = head;

    /* Linear Search */
    while (bantu != NULL) {

        if (bantu->id == idCari) {

            /* Bersihkan sebelum hasil ditampilkan */
            system("cls");

            printf("=========================================\n");
            printf("           DATA DITEMUKAN\n");
            printf("=========================================\n");

            tampilkanSatuData(bantu);

            tekanEnter();

            /* Bersihkan layar */
            system("cls");

            return;
        }

        bantu = bantu->next;
    }

    printf("\nData dengan ID %d tidak ditemukan!\n", idCari);

    tekanEnter();

    /* Bersihkan layar */
    system("cls");
}


/* =========================================================
   SORTING - URUTKAN BERDASARKAN NAMA
   BUBBLE SORT
   ========================================================= */
void urutkanNama() {
    Node *i;
    Node *j;

    int tempId;
    int tempJumlahMalam;
    int tempHarga;
    int tempTotal;

    char tempNama[50];
    char tempTelp[20];
    char tempTipe[30];
    char tempCheckIn[15];
    char tempCheckOut[15];

    /* Bersihkan layar */
    system("cls");

    printf("=========================================\n");
    printf("       URUTKAN BERDASARKAN NAMA\n");
    printf("=========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");

        tekanEnter();
        system("cls");
        return;
    }

    /* Bubble Sort */
    for (i = head; i != NULL; i = i->next) {

        for (j = head;
             j->next != NULL;
             j = j->next) {

            if (strcmp(
                    j->nama,
                    j->next->nama
                ) > 0) {

                /* Tukar ID */
                tempId = j->id;
                j->id = j->next->id;
                j->next->id = tempId;

                /* Tukar Nama */
                strcpy(tempNama, j->nama);
                strcpy(j->nama, j->next->nama);
                strcpy(j->next->nama, tempNama);

                /* Tukar Telepon */
                strcpy(tempTelp, j->noTelp);
                strcpy(j->noTelp, j->next->noTelp);
                strcpy(j->next->noTelp, tempTelp);

                /* Tukar Tipe Kamar */
                strcpy(tempTipe, j->tipeKamar);
                strcpy(j->tipeKamar, j->next->tipeKamar);
                strcpy(j->next->tipeKamar, tempTipe);

                /* Tukar Check-In */
                strcpy(tempCheckIn, j->checkIn);
                strcpy(j->checkIn, j->next->checkIn);
                strcpy(j->next->checkIn, tempCheckIn);

                /* Tukar Check-Out */
                strcpy(tempCheckOut, j->checkOut);
                strcpy(j->checkOut, j->next->checkOut);
                strcpy(j->next->checkOut, tempCheckOut);

                /* Tukar Jumlah Malam */
                tempJumlahMalam = j->jumlahMalam;
                j->jumlahMalam =
                    j->next->jumlahMalam;
                j->next->jumlahMalam =
                    tempJumlahMalam;

                /* Tukar Harga */
                tempHarga = j->hargaPerMalam;
                j->hargaPerMalam =
                    j->next->hargaPerMalam;
                j->next->hargaPerMalam =
                    tempHarga;

                /* Tukar Total */
                tempTotal = j->totalBayar;
                j->totalBayar =
                    j->next->totalBayar;
                j->next->totalBayar =
                    tempTotal;
            }
        }
    }

    /* Simpan hasil sorting */
    simpanKeFile();

    printf("\n=========================================\n");
    printf("       SORTING BERHASIL\n");
    printf("=========================================\n");
    printf("Data berhasil diurutkan berdasarkan nama.\n");
    printf("Urutan: A sampai Z\n");
    printf("=========================================\n");

    tekanEnter();

    /* Bersihkan layar */
    system("cls");
}


/* =========================================================
   FILE HANDLING - SIMPAN KE FILE
   ========================================================= */
void simpanKeFile() {
    FILE *file;
    Node *bantu;

    file = fopen(FILE_NAME, "w");

    if (file == NULL) {
        printf("\nGagal membuka file!\n");
        return;
    }

    bantu = head;

    /* Menyimpan seluruh Linked List */
    while (bantu != NULL) {

        fprintf(
            file,
            "%d|%s|%s|%s|%s|%s|%d|%d|%d\n",
            bantu->id,
            bantu->nama,
            bantu->noTelp,
            bantu->tipeKamar,
            bantu->checkIn,
            bantu->checkOut,
            bantu->jumlahMalam,
            bantu->hargaPerMalam,
            bantu->totalBayar
        );

        bantu = bantu->next;
    }

    fclose(file);
}


/* =========================================================
   FILE HANDLING - BACA DARI FILE
   ========================================================= */
void muatDariFile() {
    FILE *file;

    Node *baru;
    Node *bantu;

    file = fopen(FILE_NAME, "r");

    /* Jika file belum ada */
    if (file == NULL) {
        return;
    }

    while (1) {

        /* Alokasi node baru */
        baru = (Node *)malloc(sizeof(Node));

        if (baru == NULL) {
            break;
        }

        /* Membaca data dari file */
        if (fscanf(
                file,
                "%d|%49[^|]|%19[^|]|%29[^|]|%14[^|]|%14[^|]|%d|%d|%d\n",
                &baru->id,
                baru->nama,
                baru->noTelp,
                baru->tipeKamar,
                baru->checkIn,
                baru->checkOut,
                &baru->jumlahMalam,
                &baru->hargaPerMalam,
                &baru->totalBayar
            ) != 9) {

            free(baru);
            break;
        }

        baru->next = NULL;

        /* Masukkan ke Linked List */
        if (head == NULL) {

            head = baru;

        } else {

            bantu = head;

            while (bantu->next != NULL) {
                bantu = bantu->next;
            }

            bantu->next = baru;
        }
    }

    fclose(file);
}


/* =========================================================
   TAMPILKAN SATU DATA
   ========================================================= */
void tampilkanSatuData(Node *data) {

    printf("\n=========================================\n");
    printf("ID Reservasi    : %d\n", data->id);
    printf("Nama Tamu       : %s\n", data->nama);
    printf("No. Telepon     : %s\n", data->noTelp);
    printf("Tipe Kamar      : %s\n", data->tipeKamar);
    printf("Check-In        : %s\n", data->checkIn);
    printf("Check-Out       : %s\n", data->checkOut);
    printf("Jumlah Malam    : %d\n", data->jumlahMalam);
    printf("Harga / Malam   : Rp %d\n", data->hargaPerMalam);
    printf("Total Bayar     : Rp %d\n", data->totalBayar);
    printf("=========================================\n");
}


/* =========================================================
   CEK APAKAH ID SUDAH ADA
   ========================================================= */
int idSudahAda(int id) {
    Node *bantu;

    bantu = head;

    while (bantu != NULL) {

        if (bantu->id == id) {
            return 1;
        }

        bantu = bantu->next;
    }

    return 0;
}


/* =========================================================
   INPUT STRING DENGAN FGETS
   ========================================================= */
void inputString(char str[], int ukuran) {

    if (fgets(str, ukuran, stdin) != NULL) {

        /* Menghapus newline */
        str[strcspn(str, "\n")] = '\0';
    }
}


/* =========================================================
   MEMBERSIHKAN BUFFER INPUT
   ========================================================= */
void bersihkanBuffer() {
    int c;

    while ((c = getchar()) != '\n' &&
           c != EOF) {
        /* Kosong */
    }
}


/* =========================================================
   TEKAN ENTER UNTUK MELANJUTKAN
   ========================================================= */
void tekanEnter() {

    printf("\nTekan ENTER untuk melanjutkan...");

    getchar();
}


/* =========================================================
   MEMBEBASKAN MEMORI LINKED LIST
   ========================================================= */
void bebaskanMemori() {
    Node *bantu;

    while (head != NULL) {

        bantu = head;

        head = head->next;

        free(bantu);
    }
=======
#include<stdio.h>
int main(){
    printf("halo ajg");
>>>>>>> 016ed59e01a094f6430848478d809509da99526d
}