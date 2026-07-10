#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================================================
   STRUCT NODE
   ========================================================= */

typedef struct Node {
    int id;
    char nama[50];
    char noTelp[20];
    char tipeKamar[20];
    char checkIn[15];
    char checkOut[15];
    int jumlahMalam;
    int hargaKamar;
    int totalBayar;

    struct Node *next;
} Node;


/* =========================================================
   HEAD LINKED LIST
   ========================================================= */

Node *head = NULL;


/* =========================================================
   PROTOTYPE FUNGSI
   ========================================================= */

void menuUtama();

void tambahReservasi();
void tampilkanReservasi();
void ubahReservasi();
void hapusReservasi();

void cariReservasi();
void urutkanNama();

void simpanFile();
void bacaFile();

void pilihKamar(Node *data);
void tampilSatuData(Node *data);
int cekId(int id);
void pauseProgram();
void hapusSemuaMemori();


/* =========================================================
   FUNGSI MAIN
   ========================================================= */

int main() {
    system("cls");

    /* Membaca data dari file */
    bacaFile();

    /* Menjalankan menu utama */
    menuUtama();

    /* Membebaskan memori */
    hapusSemuaMemori();

    return 0;
}


/* =========================================================
   MENU UTAMA
   ========================================================= */

void menuUtama() {
    int pilihan;

    do {
        system("cls");

        printf("========================================\n");
        printf("       SISTEM RESERVASI HOTEL\n");
        printf("========================================\n");
        printf("1. Tambah Reservasi\n");
        printf("2. Tampilkan Reservasi\n");
        printf("3. Ubah Reservasi\n");
        printf("4. Hapus Reservasi\n");
        printf("5. Cari Reservasi\n");
        printf("6. Urutkan Nama Tamu\n");
        printf("0. Keluar\n");
        printf("========================================\n");
        printf("Pilih menu : ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahReservasi();
                break;

            case 2:
                tampilkanReservasi();
                break;

            case 3:
                ubahReservasi();
                break;

            case 4:
                hapusReservasi();
                break;

            case 5:
                cariReservasi();
                break;

            case 6:
                urutkanNama();
                break;

            case 0:
                simpanFile();
                system("cls");

                printf("========================================\n");
                printf("          PROGRAM SELESAI\n");
                printf("========================================\n");
                printf("Data telah disimpan.\n");
                printf("Terima kasih.\n");
                printf("========================================\n");
                break;

            default:
                printf("\nPilihan tidak tersedia!\n");
                pauseProgram();
                break;
        }

    } while (pilihan != 0);
}


/* =========================================================
   CREATE
   TAMBAH RESERVASI
   ========================================================= */

void tambahReservasi() {
    Node *baru;
    Node *bantu;

    int idBaru;
    int hari, bulan, tahun;

    system("cls");

    printf("========================================\n");
    printf("         TAMBAH RESERVASI\n");
    printf("========================================\n");

    /* Membuat node baru */
    baru = (Node *) malloc(sizeof(Node));

    /* Cek memori */
    if (baru == NULL) {
        printf("\nMemori tidak tersedia!\n");
        pauseProgram();
        return;
    }

    /* Input ID */
    printf("Masukkan ID Reservasi : ");
    scanf("%d", &idBaru);

    /* Cek ID */
    if (cekId(idBaru) == 1) {
        printf("\nID sudah digunakan!\n");
        free(baru);
        pauseProgram();
        return;
    }

    baru->id = idBaru;

    /* Input nama */
    printf("Masukkan Nama Tamu    : ");
    scanf(" %[^\n]", baru->nama);

    /* Input telepon */
    printf("Masukkan No Telepon   : ");
    scanf(" %[^\n]", baru->noTelp);

    /* Pilih kamar */
    pilihKamar(baru);

    /* Input Check-In */
    printf("\n========================================\n");
    printf("          TANGGAL CHECK-IN\n");
    printf("========================================\n");
    printf("Masukkan tanggal (DD MM YYYY): ");
    scanf("%d %d %d", &hari, &bulan, &tahun);2
    

    /* Ubah menjadi DD/MM/YYYY */
    sprintf(
        baru->checkIn,
        "%02d/%02d/%04d",
        hari,
        bulan,
        tahun
    );

    /* Input Check-Out */
    printf("\n========================================\n");
    printf("         TANGGAL CHECK-OUT\n");
    printf("========================================\n");
    printf("Masukkan tanggal (DD MM YYYY): ");
    scanf("%d %d %d", &hari, &bulan, &tahun);

    /* Ubah menjadi DD/MM/YYYY */
    sprintf(
        baru->checkOut,
        "%02d/%02d/%04d",
        hari,
        bulan,
        tahun
    );

    /* Input jumlah malam */
    printf("\nJumlah Malam : ");
    scanf("%d", &baru->jumlahMalam);

    /* Validasi sederhana */
    if (baru->jumlahMalam <= 0) {
        printf("\nJumlah malam harus lebih dari 0!\n");
        free(baru);
        pauseProgram();
        return;
    }

    /* Hitung total bayar */
    baru->totalBayar =
        baru->hargaKamar * baru->jumlahMalam;

    /* Node baru belum terhubung */
    baru->next = NULL;

    /* Jika linked list kosong */
    if (head == NULL) {
        head = baru;
    }

    /* Jika linked list sudah ada */
    else {
        bantu = head;

        /* Cari node terakhir */
        while (bantu->next != NULL) {
            bantu = bantu->next;
        }

        /* Sambungkan node */
        bantu->next = baru;
    }

    /* Simpan ke file */
    simpanFile();

    system("cls");

    printf("========================================\n");
    printf("      RESERVASI BERHASIL DITAMBAH\n");
    printf("========================================\n");
    printf("ID Reservasi : %d\n", baru->id);
    printf("Nama Tamu    : %s\n", baru->nama);
    printf("No Telepon   : %s\n", baru->noTelp);
    printf("Tipe Kamar   : %s\n", baru->tipeKamar);
    printf("Check-In     : %s\n", baru->checkIn);
    printf("Check-Out    : %s\n", baru->checkOut);
    printf("Jumlah Malam : %d\n", baru->jumlahMalam);
    printf("Harga Kamar  : Rp %d\n", baru->hargaKamar);
    printf("Total Bayar  : Rp %d\n", baru->totalBayar);
    printf("========================================\n");

    pauseProgram();
}


/* =========================================================
   READ
   TAMPILKAN SEMUA RESERVASI
   ========================================================= */

void tampilkanReservasi() {
    Node *bantu;
    int nomor = 1;

    system("cls");

    printf("==================================================\n");
    printf("              DATA RESERVASI HOTEL\n");
    printf("==================================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");
        pauseProgram();
        return;
    }

    /* Mulai dari head */
    bantu = head;

    /* Traversal Linked List */
    while (bantu != NULL) {
        printf("\nData Reservasi Ke-%d\n", nomor);
        printf("--------------------------------------------------\n");
        printf("ID Reservasi  : %d\n", bantu->id);
        printf("Nama Tamu     : %s\n", bantu->nama);
        printf("No Telepon    : %s\n", bantu->noTelp);
        printf("Tipe Kamar    : %s\n", bantu->tipeKamar);
        printf("Check-In      : %s\n", bantu->checkIn);
        printf("Check-Out     : %s\n", bantu->checkOut);
        printf("Jumlah Malam  : %d\n", bantu->jumlahMalam);
        printf("Harga Kamar   : Rp %d\n", bantu->hargaKamar);
        printf("Total Bayar   : Rp %d\n", bantu->totalBayar);
        printf("--------------------------------------------------\n");

        /* Pindah node */
        bantu = bantu->next;
        nomor++;
    }

    pauseProgram();
}


/* =========================================================
   UPDATE
   UBAH RESERVASI
   ========================================================= */

void ubahReservasi() {
    Node *bantu;

    int idCari;
    int hari, bulan, tahun;

    system("cls");

    printf("========================================\n");
    printf("          UBAH RESERVASI\n");
    printf("========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");
        pauseProgram();
        return;
    }

    /* Input ID */
    printf("Masukkan ID yang diubah : ");
    scanf("%d", &idCari);

    /* Mulai dari head */
    bantu = head;

    /* Mencari data */
    while (bantu != NULL) {

        if (bantu->id == idCari) {
            system("cls");

            printf("========================================\n");
            printf("           DATA DITEMUKAN\n");
            printf("========================================\n");
            printf("ID          : %d\n", bantu->id);
            printf("Nama Lama   : %s\n", bantu->nama);
            printf("Kamar Lama  : %s\n", bantu->tipeKamar);
            printf("Check-In    : %s\n", bantu->checkIn);
            printf("Check-Out   : %s\n", bantu->checkOut);
            printf("========================================\n");

            /* Input nama baru */
            printf("\nMasukkan Nama Baru    : ");
            scanf(" %[^\n]", bantu->nama);

            /* Input telepon baru */
            printf("Masukkan No Telp Baru : ");
            scanf(" %[^\n]", bantu->noTelp);

            /* Pilih kamar baru */
            pilihKamar(bantu);

            /* Check-In baru */
            printf("\n========================================\n");
            printf("        TANGGAL CHECK-IN BARU\n");
            printf("========================================\n");
            printf("Format DD MM YYYY\n");
            printf("Contoh 07 08 2026\n");
            printf("Masukkan tanggal : ");
            scanf("%d %d %d", &hari, &bulan, &tahun);

            sprintf(
                bantu->checkIn,
                "%02d/%02d/%04d",
                hari,
                bulan,
                tahun
            );

            /* Check-Out baru */
            printf("\n========================================\n");
            printf("       TANGGAL CHECK-OUT BARU\n");
            printf("========================================\n");
            printf("Format DD MM YYYY\n");
            printf("Contoh 10 08 2026\n");
            printf("Masukkan tanggal : ");
            scanf("%d %d %d", &hari, &bulan, &tahun);

            sprintf(
                bantu->checkOut,
                "%02d/%02d/%04d",
                hari,
                bulan,
                tahun
            );

            /* Jumlah malam baru */
            printf("\nJumlah Malam Baru : ");
            scanf("%d", &bantu->jumlahMalam);

            /* Validasi sederhana */
            if (bantu->jumlahMalam <= 0) {
                bantu->jumlahMalam = 1;
            }

            /* Hitung ulang total */
            bantu->totalBayar =
                bantu->hargaKamar * bantu->jumlahMalam;

            /* Simpan perubahan */
            simpanFile();

            system("cls");

            printf("========================================\n");
            printf("    DATA RESERVASI BERHASIL DIUBAH\n");
            printf("========================================\n");
            printf("ID          : %d\n", bantu->id);
            printf("Nama        : %s\n", bantu->nama);
            printf("Tipe Kamar  : %s\n", bantu->tipeKamar);
            printf("Check-In    : %s\n", bantu->checkIn);
            printf("Check-Out   : %s\n", bantu->checkOut);
            printf("Total Bayar : Rp %d\n", bantu->totalBayar);
            printf("========================================\n");

            pauseProgram();
            return;
        }

        /* Pindah node */
        bantu = bantu->next;
    }

    printf("\nID reservasi tidak ditemukan!\n");
    pauseProgram();
}


/* =========================================================
   DELETE
   HAPUS RESERVASI
   ========================================================= */

void hapusReservasi() {
    Node *bantu;
    Node *sebelum;

    int idHapus;
    char yakin;

    system("cls");

    printf("========================================\n");
    printf("         HAPUS RESERVASI\n");
    printf("========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");
        pauseProgram();
        return;
    }

    /* Input ID */
    printf("Masukkan ID yang dihapus : ");
    scanf("%d", &idHapus);

    /* Posisi awal */
    bantu = head;
    sebelum = NULL;

    /* Mencari data */
    while (bantu != NULL) {

        if (bantu->id == idHapus) {
            system("cls");

            printf("========================================\n");
            printf("           DATA DITEMUKAN\n");
            printf("========================================\n");
            printf("ID          : %d\n", bantu->id);
            printf("Nama        : %s\n", bantu->nama);
            printf("Tipe Kamar  : %s\n", bantu->tipeKamar);
            printf("Check-In    : %s\n", bantu->checkIn);
            printf("Check-Out   : %s\n", bantu->checkOut);
            printf("Total Bayar : Rp %d\n", bantu->totalBayar);
            printf("========================================\n");

            /* Konfirmasi */
            printf("\nYakin ingin menghapus? (y/n) : ");
            scanf(" %c", &yakin);

            if (yakin == 'y' || yakin == 'Y') {

                /* Jika menghapus head */
                if (sebelum == NULL) {
                    head = bantu->next;
                }

                /* Jika bukan head */
                else {
                    sebelum->next = bantu->next;
                }

                /* Hapus node */
                free(bantu);

                /* Simpan perubahan */
                simpanFile();

                printf("\nData berhasil dihapus!\n");
            }

            else {
                printf("\nPenghapusan dibatalkan.\n");
            }

            pauseProgram();
            return;
        }

        /* Pindah node */
        sebelum = bantu;
        bantu = bantu->next;
    }

    printf("\nID tidak ditemukan!\n");
    pauseProgram();
}


/* =========================================================
   SEARCHING
   LINEAR SEARCH BERDASARKAN ID
   ========================================================= */

void cariReservasi() {
    Node *bantu;
    int idCari;

    system("cls");

    printf("========================================\n");
    printf("          CARI RESERVASI\n");
    printf("========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");
        pauseProgram();
        return;
    }

    /* Input ID */
    printf("Masukkan ID Reservasi : ");
    scanf("%d", &idCari);

    /* Mulai dari head */
    bantu = head;

    /* Linear Search */
    while (bantu != NULL) {

        if (bantu->id == idCari) {
            system("cls");

            printf("========================================\n");
            printf("          DATA DITEMUKAN\n");
            printf("========================================\n");

            tampilSatuData(bantu);

            pauseProgram();
            return;
        }

        /* Pindah node */
        bantu = bantu->next;
    }

    printf("\nData tidak ditemukan!\n");
    pauseProgram();
}


/* =========================================================
   SORTING
   BUBBLE SORT BERDASARKAN NAMA
   ========================================================= */

void urutkanNama() {
    Node *i;
    Node *j;

    int tempId;
    int tempJumlah;
    int tempHarga;
    int tempTotal;

    char tempNama[50];
    char tempTelp[20];
    char tempKamar[20];
    char tempCheckIn[15];
    char tempCheckOut[15];

    system("cls");

    printf("========================================\n");
    printf("      URUTKAN BERDASARKAN NAMA\n");
    printf("========================================\n");

    /* Cek data kosong */
    if (head == NULL) {
        printf("\nBelum ada data reservasi.\n");
        pauseProgram();
        return;
    }

    /* Jika hanya satu data */
    if (head->next == NULL) {
        printf("\nData hanya satu.\n");
        printf("Tidak perlu melakukan sorting.\n");
        pauseProgram();
        return;
    }

    /* Bubble Sort */
    for (i = head; i != NULL; i = i->next) {

        for (j = head; j->next != NULL; j = j->next) {

            /* Bandingkan nama */
            if (strcmp(j->nama, j->next->nama) > 0) {

                /* Tukar ID */
                tempId = j->id;
                j->id = j->next->id;
                j->next->id = tempId;

                /* Tukar nama */
                strcpy(tempNama, j->nama);
                strcpy(j->nama, j->next->nama);
                strcpy(j->next->nama, tempNama);

                /* Tukar telepon */
                strcpy(tempTelp, j->noTelp);
                strcpy(j->noTelp, j->next->noTelp);
                strcpy(j->next->noTelp, tempTelp);

                /* Tukar kamar */
                strcpy(tempKamar, j->tipeKamar);
                strcpy(j->tipeKamar, j->next->tipeKamar);
                strcpy(j->next->tipeKamar, tempKamar);

                /* Tukar Check-In */
                strcpy(tempCheckIn, j->checkIn);
                strcpy(j->checkIn, j->next->checkIn);
                strcpy(j->next->checkIn, tempCheckIn);

                /* Tukar Check-Out */
                strcpy(tempCheckOut, j->checkOut);
                strcpy(j->checkOut, j->next->checkOut);
                strcpy(j->next->checkOut, tempCheckOut);

                /* Tukar jumlah malam */
                tempJumlah = j->jumlahMalam;
                j->jumlahMalam = j->next->jumlahMalam;
                j->next->jumlahMalam = tempJumlah;

                /* Tukar harga */
                tempHarga = j->hargaKamar;
                j->hargaKamar = j->next->hargaKamar;
                j->next->hargaKamar = tempHarga;

                /* Tukar total */
                tempTotal = j->totalBayar;
                j->totalBayar = j->next->totalBayar;
                j->next->totalBayar = tempTotal;
            }
        }
    }

    /* Simpan hasil sorting */
    simpanFile();

    system("cls");

    printf("========================================\n");
    printf("         SORTING BERHASIL\n");
    printf("========================================\n");
    printf("Data telah diurutkan berdasarkan nama.\n");
    printf("Urutan dari A sampai Z.\n");
    printf("========================================\n");

    pauseProgram();
}


/* =========================================================
   PILIH JENIS KAMAR
   ========================================================= */

void pilihKamar(Node *data) {
    int pilihan;

    printf("\n========================================\n");
    printf("          PILIH JENIS KAMAR\n");
    printf("========================================\n");
    printf("1. Standard  Rp 300000 / malam\n");
    printf("2. Deluxe    Rp 500000 / malam\n");
    printf("3. Suite     Rp 800000 / malam\n");
    printf("========================================\n");
    printf("Pilih kamar : ");
    scanf("%d", &pilihan);

    /* Standard */
    if (pilihan == 1) {
        strcpy(data->tipeKamar, "Standard");
        data->hargaKamar = 300000;
    }

    /* Deluxe */
    else if (pilihan == 2) {
        strcpy(data->tipeKamar, "Deluxe");
        data->hargaKamar = 500000;
    }

    /* Suite */
    else if (pilihan == 3) {
        strcpy(data->tipeKamar, "Suite");
        data->hargaKamar = 800000;
    }

    /* Pilihan salah */
    else {
        printf("\nPilihan salah!\n");
        printf("Otomatis memilih Standard.\n");

        strcpy(data->tipeKamar, "Standard");
        data->hargaKamar = 300000;
    }
}


/* =========================================================
   TAMPILKAN SATU DATA
   ========================================================= */

void tampilSatuData(Node *data) {
    printf("----------------------------------------\n");
    printf("ID Reservasi  : %d\n", data->id);
    printf("Nama Tamu     : %s\n", data->nama);
    printf("No Telepon    : %s\n", data->noTelp);
    printf("Tipe Kamar    : %s\n", data->tipeKamar);
    printf("Check-In      : %s\n", data->checkIn);
    printf("Check-Out     : %s\n", data->checkOut);
    printf("Jumlah Malam  : %d\n", data->jumlahMalam);
    printf("Harga Kamar   : Rp %d\n", data->hargaKamar);
    printf("Total Bayar   : Rp %d\n", data->totalBayar);
    printf("----------------------------------------\n");
}


/* =========================================================
   CEK ID
   ========================================================= */

int cekId(int id) {
    Node *bantu;

    /* Mulai dari head */
    bantu = head;

    /* Cari ID */
    while (bantu != NULL) {

        if (bantu->id == id) {
            return 1;
        }

        bantu = bantu->next;
    }

    return 0;
}


/* =========================================================
   FILE HANDLING
   SIMPAN DATA KE FILE
   ========================================================= */

void simpanFile() {
    FILE *file;
    Node *bantu;

    /* Buka file mode write */
    file = fopen("reservasi.txt", "w");

    /* Cek file */
    if (file == NULL) {
        printf("\nFile gagal dibuka!\n");
        return;
    }

    /* Mulai dari head */
    bantu = head;

    /* Simpan semua data */
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
            bantu->hargaKamar,
            bantu->totalBayar
        );

        /* Pindah node */
        bantu = bantu->next;
    }

    /* Tutup file */
    fclose(file);
}


/* =========================================================
   FILE HANDLING
   BACA DATA DARI FILE
   ========================================================= */

void bacaFile() {
    FILE *file;
    Node *baru;
    Node *bantu;

    /* Buka file mode read */
    file = fopen("reservasi.txt", "r");

    /* Jika file belum ada */
    if (file == NULL) {
        return;
    }

    /* Membaca sampai selesai */
    while (1) {

        /* Membuat node baru */
        baru = (Node *) malloc(sizeof(Node));

        /* Cek memori */
        if (baru == NULL) {
            break;
        }

        /* Membaca satu data */
        if (fscanf(
                file,
                "%d|%49[^|]|%19[^|]|%19[^|]|%14[^|]|%14[^|]|%d|%d|%d\n",
                &baru->id,
                baru->nama,
                baru->noTelp,
                baru->tipeKamar,
                baru->checkIn,
                baru->checkOut,
                &baru->jumlahMalam,
                &baru->hargaKamar,
                &baru->totalBayar
            ) == 9) {

            /* Node baru belum terhubung */
            baru->next = NULL;

            /* Jika list kosong */
            if (head == NULL) {
                head = baru;
            }

            /* Jika sudah ada data */
            else {
                bantu = head;

                /* Cari node terakhir */
                while (bantu->next != NULL) {
                    bantu = bantu->next;
                }

                /* Sambungkan node */
                bantu->next = baru;
            }
        }

        /* Jika gagal membaca */
        else {
            free(baru);
            break;
        }
    }

    /* Tutup file */
    fclose(file);
}


/* =========================================================
   PAUSE PROGRAM
   ========================================================= */

void pauseProgram() {
    printf("\nTekan ENTER untuk kembali...");

    /* Membersihkan ENTER sebelumnya */
    getchar();

    /* Menunggu ENTER user */
    getchar();

    /* Bersihkan layar */
    system("cls");
}


/* =========================================================
   HAPUS SEMUA MEMORI
   ========================================================= */

void hapusSemuaMemori() {
    Node *bantu;

    /* Hapus semua node */
    while (head != NULL) {

        /* Simpan head */
        bantu = head;

        /* Geser head */
        head = head->next;

        /* Hapus node */
        free(bantu);
    }
}