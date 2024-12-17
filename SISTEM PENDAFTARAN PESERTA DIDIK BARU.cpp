/*
TUGAS BESAR ALGORITMA DAN PEMROGRAMMAN
DHENDI SYAFA ATHALLAH PUTRA 2405380 - NATASYA BUNGA SOPIAN 2400319
SISTEM PENDAFTARAN PESERTA DIDIK BARU SMA KOTA BANDUNG
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char USERNAME_ADMIN[16] = "admin";
char PASSWORD_ADMIN[10] = "admin123";
bool asAdmin = false;
int KUOTASEKOLAHTERDAFTAR = 100;
int jumlahSekolahTerdaftar = 0;
int jumlahPesertaDidikTerdaftar = 0;

struct DataSekolah {
  int id;
  char namaSekolah[30];
  char alamatSekolah[100];
  int kuotaPesertaDidikBaru;
  int kuotaJalurPrestasiRapor;
  int kuotaJalurZonasi;
};

enum JalurSeleksi { ZONASI, PRESTASI_RAPOR };

struct DataPesertaDidik {
  int id;
  char nomorPendaftaran[10];
  char namaLengkap[150];
  char jenisKelamin[10];
  char sekolahTujuan[50];
  char sekolahAsal[50];
  float nilaiBahasaIndonesia;
  float nilaiBahasaInggris;
  float nilaiMatematika;
  float rataRataNilai;
  float jarakRumah;
  enum JalurSeleksi jalurSeleksi;
};

struct DataSekolah informasiSekolah[100];
struct DataPesertaDidik dataPesertaDidik[100];

void clrscr() {
  system("PAUSE");
  system("CLS");
}

void printBorder() {
  printf("===============================================================\n");
}

void printHeader(const char *title) {
  printBorder();
  printf("%s\n", title);
  printBorder();
}

void displayMainMenu() {
  printHeader("Main Menu");
  printf("1. Login Sebagai Admin\n");
  printf("2. Pendaftaran Peserta Didik Baru\n");
  printf("3. Lihat Hasil Seleksi\n");
  printf("4. Lihat Semua Data Pendaftar\n");
  printf("5. Cari Data Pendaftar\n");
  printf("0. Keluar\n");
  printBorder();
}

void displayAdminMenu() {
  printHeader("Menu Admin");
  printf("1. Pendaftaran Sekolah\n");
  printf("2. Lihat Semua Data Sekolah\n");
  printf("3. Edit Alamat Sekolah\n");
  printf("4. Logout Sebagai Admin\n");
  printBorder();
}

void pendaftaranInformasiSekolah() {
  if(jumlahSekolahTerdaftar >= KUOTASEKOLAHTERDAFTAR) {
    printf("Pendaftaran sekolah telah penuh!\n");
    return;
  }

  struct DataSekolah sekolahBaru;
  sekolahBaru.id = jumlahSekolahTerdaftar + 1;

  printf("Masukkan nama sekolah: ");
  scanf(" %[^\n]", sekolahBaru.namaSekolah);

  printf("Masukkan alamat sekolah: ");
  scanf(" %[^\n]", sekolahBaru.alamatSekolah);

  printf("Masukkan kuota peserta didik baru: ");
  scanf("%d", &sekolahBaru.kuotaPesertaDidikBaru);

  // rapor: 60%, zonasi: 40%
  // sekolahBaru.kuotaJalurPrestasiRapor =
  //     sekolahBaru.kuotaPesertaDidikBaru * 0.60;
  // sekolahBaru.kuotaJalurZonasi = sekolahBaru.kuotaPesertaDidikBaru * 0.40;
  sekolahBaru.kuotaJalurPrestasiRapor =
      (sekolahBaru.kuotaPesertaDidikBaru * 0.60);
  sekolahBaru.kuotaJalurZonasi =
      sekolahBaru.kuotaPesertaDidikBaru - sekolahBaru.kuotaJalurPrestasiRapor;

  informasiSekolah[jumlahSekolahTerdaftar] = sekolahBaru;
  jumlahSekolahTerdaftar++;

  printf("Sekolah berhasil didaftarkan!\n");
}

void listSekolahTerdaftar() {
  if(jumlahSekolahTerdaftar == 0) {
    printf("Belum ada sekolah yang terdaftar.\n");
    return;
  }

  printf("Daftar Sekolah Terdaftar:\n");
  for(int i = 0; i < jumlahSekolahTerdaftar; i++) {
    printf("ID: %d\n", informasiSekolah[i].id);
    printf("Nama Sekolah: %s\n", informasiSekolah[i].namaSekolah);
    printf("Alamat Sekolah: %s\n", informasiSekolah[i].alamatSekolah);
    printf("Kuota Peserta Didik Baru: %d\n",
           informasiSekolah[i].kuotaPesertaDidikBaru);
    printf("Kuota Jalur Prestasi Rapor: %d\n",
           informasiSekolah[i].kuotaJalurPrestasiRapor);
    printf("Kuota Jalur Zonasi: %d\n", informasiSekolah[i].kuotaJalurZonasi);
    printf("------------------------\n");
  }
}

void logoutAdmin() {
  asAdmin = false;
  printf("\nAnda telah logout. Kembali ke Main Menu...\n");
}

int searchSekolahByName(char *namaSekolahTujuan,
                        struct DataSekolah *detailSekolah) {
  for(int i = 0; i < jumlahSekolahTerdaftar; i++) {
    if(strcmp(informasiSekolah[i].namaSekolah, namaSekolahTujuan) == 0) {
      if(detailSekolah != NULL) {
        *detailSekolah = informasiSekolah[i];
      }
      return i;
    }
  }
  printf("\nSekolah dengan nama '%s' tidak ditemukan.\n", namaSekolahTujuan);
  return -1;
}

void editAlamatSekolah() {
  int indexSekolahDicari;
  char namaSekolah[50];
  struct DataSekolah sekolahDicari;

  if(jumlahSekolahTerdaftar == 0) {
    printf("Belum ada peserta didik yang terdaftar.\n");
    return;
  } else {
    listSekolahTerdaftar();

    do {
      printf("\nPilih nama sekolah: ");
      scanf(" %[^\n]", namaSekolah);

      indexSekolahDicari = searchSekolahByName(namaSekolah, &sekolahDicari);

      if(indexSekolahDicari == -1) {
        printf("\nNama sekolah tidak valid, silakan coba lagi.\n");
      }
    } while(indexSekolahDicari == -1);

    printf("\nSekolah ditemukan:\n");
    printf("Nama Sekolah: %s\n", sekolahDicari.namaSekolah);
    printf("Alamat Sekolah: %s\n", sekolahDicari.alamatSekolah);

    printf("Masukkan alamat baru: ");
    scanf("%s", informasiSekolah[indexSekolahDicari].alamatSekolah);
  }
}

void adminMenu() {
  int selectMenu;

  do {
    displayAdminMenu();

    printf("Pilih menu: ");
    scanf("%d", &selectMenu);

    switch(selectMenu) {
      case 1:
        pendaftaranInformasiSekolah();
        clrscr();
        break;
      case 2:
        listSekolahTerdaftar();
        clrscr();
        break;
      case 3:
        editAlamatSekolah();
        clrscr();
        break;
      case 4:
        logoutAdmin();
        return;
      default:
        printf("Menu tidak valid, coba lagi.\n");
    }
  } while(true);
};

void adminLogin() {
  char username[16], password[10];

  printf("Masukkan username: ");
  scanf("%15s", username);

  printf("Masukkan password: ");
  scanf("%9s", password);

  if(strcmp(username, USERNAME_ADMIN) == 0 &&
     strcmp(password, PASSWORD_ADMIN) == 0) {
    asAdmin = true;
    printf("BERHASIL LOGIN SEBAGAI ADMIN!\n");
    adminMenu();
  } else {
    printf("GAGAL LOGIN ADMIN. PASTIKAN USERNAME DAN PASSWORD BENAR!\n");
    adminLogin();
  }
}

void jalurPrestasi(struct DataPesertaDidik *pesertaDidikBaru) {
  printf("Masukkan Nama Lengkap: ");
  scanf(" %[^\n]s", pesertaDidikBaru->namaLengkap);
  printf("Masukkan Jenis Kelamin (L/P): ");
  scanf("%s", pesertaDidikBaru->jenisKelamin);
  printf("Masukkan Sekolah Asal: ");
  scanf(" %[^\n]s", pesertaDidikBaru->sekolahAsal);
  printf("Masukkan Rata-Rata Bahasa Indonesia: ");
  scanf("%f", &pesertaDidikBaru->nilaiBahasaIndonesia);
  printf("Masukkan Rata-Rata Bahasa Inggris: ");
  scanf("%f", &pesertaDidikBaru->nilaiBahasaInggris);
  printf("Masukkan Rata-Rata Matematika: ");
  scanf("%f", &pesertaDidikBaru->nilaiMatematika);

  pesertaDidikBaru->rataRataNilai = (pesertaDidikBaru->nilaiBahasaIndonesia +
                                     pesertaDidikBaru->nilaiBahasaInggris +
                                     pesertaDidikBaru->nilaiMatematika) /
                                    3;
}

void jalurZonasi(struct DataPesertaDidik *pesertaDidikBaru) {
  printf("Masukkan Nama Lengkap: ");
  scanf(" %[^\n]s", pesertaDidikBaru->namaLengkap);
  printf("Masukkan Jenis Kelamin (L/P): ");
  scanf("%s", pesertaDidikBaru->jenisKelamin);
  printf("Masukkan Sekolah Asal: ");
  scanf(" %[^\n]s", pesertaDidikBaru->sekolahAsal);
  printf("Masukkan Jarak Rumah ke Sekolah Tujuan (dalam meter): ");
  scanf("%f", &pesertaDidikBaru->jarakRumah);
}

void generateNomorPendaftaran(struct DataPesertaDidik *pesertaDidikBaru,
                              int index) {
  sprintf(pesertaDidikBaru->nomorPendaftaran, "2024%03d", index);
}

void pendaftaranPesertaDidikBaru() {
  int pilihJalurSeleksi, indexSekolahTujuan;
  char namaSekolahTujuan[50];

  struct DataSekolah sekolahTujuan;
  struct DataPesertaDidik pesertaDidikBaru;
  pesertaDidikBaru.id = jumlahPesertaDidikTerdaftar + 1;

  if(jumlahSekolahTerdaftar == 0) {
    printf("Belum ada sekolah yang terdaftar.\n");
    return;
  } else {
    listSekolahTerdaftar();

    do {
      printf("\nPilih sekolah tujuan: ");
      scanf(" %[^\n]", namaSekolahTujuan);

      indexSekolahTujuan =
          searchSekolahByName(namaSekolahTujuan, &sekolahTujuan);

      if(indexSekolahTujuan == -1) {
        printf("\nNama sekolah tidak valid, silakan coba lagi.\n");
      } else {
        printf("\nSekolah ditemukan:\n");
        printf("Nama Sekolah: %s\n", sekolahTujuan.namaSekolah);
        printf("Alamat Sekolah: %s\n", sekolahTujuan.alamatSekolah);
        printf("Kuota Peserta Didik Baru: %d\n",
               sekolahTujuan.kuotaPesertaDidikBaru);
        printf("Kuota Jalur Prestasi Rapor: %d\n",
               sekolahTujuan.kuotaJalurPrestasiRapor);
        printf("Kuota Jalur Zonasi: %d\n", sekolahTujuan.kuotaJalurZonasi);
      }

    } while(indexSekolahTujuan == -1);

    strcpy(pesertaDidikBaru.sekolahTujuan, namaSekolahTujuan);

    printf("Pilih Jalur Seleksi:\n");
    printf("1. Prestasi (60%%)\n");
    printf("2. Zonasi (40%%)\n");
    printf("Masukkan pilihan Anda (1/2): ");
    scanf("%d", &pilihJalurSeleksi);

    switch(pilihJalurSeleksi) {
      case 1:
        printf("\nAnda memilih Jalur Prestasi Nilai Rapor.\n");
        pesertaDidikBaru.jalurSeleksi = PRESTASI_RAPOR;
        jalurPrestasi(&pesertaDidikBaru);
        break;
      case 2:
        printf("\nAnda memilih Jalur Zonasi.\n");
        pesertaDidikBaru.jalurSeleksi = ZONASI;
        jalurZonasi(&pesertaDidikBaru);
        break;
      default:
        printf("Pilihan tidak valid. Kembali ke menu utama.\n");
    }
  }

  generateNomorPendaftaran(&pesertaDidikBaru, jumlahPesertaDidikTerdaftar + 1);

  dataPesertaDidik[jumlahPesertaDidikTerdaftar] = pesertaDidikBaru;
  jumlahPesertaDidikTerdaftar++;

  printf("PENDAFTARAN PESERTA DIDIK BARU BERHASIL DISIMPAN\n");
}

void listPesertaDidikTerdaftar() {
  if(jumlahPesertaDidikTerdaftar == 0) {
    printf("Belum ada peserta didik yang terdaftar.\n");
    return;
  }

  for(int i = 0; i < jumlahPesertaDidikTerdaftar; i++) {
    printf("Nomor Pendaftaran: %s\n", dataPesertaDidik[i].nomorPendaftaran);
    printf("Nama Lengkap: %s\n", dataPesertaDidik[i].namaLengkap);
    printf("Jenis Kelamin: %s\n", dataPesertaDidik[i].jenisKelamin);
    printf("Sekolah Asal: %s\n", dataPesertaDidik[i].sekolahAsal);
    printf("Sekolah Tujuan: %s\n", dataPesertaDidik[i].sekolahTujuan);
    // printf("Jalur Seleksi: %s\n", dataPesertaDidik[i].jalurSeleksi);
    switch(dataPesertaDidik[i].jalurSeleksi) {
      case PRESTASI_RAPOR:
        printf("Jalur Seleksi: Prestasi Nilai Rapor\n");
      case ZONASI:
        printf("Jalur Seleksi: Zonasi\n");
    }

    if(dataPesertaDidik[i].jalurSeleksi == PRESTASI_RAPOR) {
      printf("Rata-rata nilai Bahasa Indonesia: %.2f\n",
             dataPesertaDidik[i].nilaiBahasaIndonesia);
      printf("Rata-rata nilai Bahasa Inggris: %.2f\n",
             dataPesertaDidik[i].nilaiBahasaInggris);
      printf("Rata-rata nilai Matematika: %.2f\n",
             dataPesertaDidik[i].nilaiMatematika);
      printf("Rata-rata nilai: %.2f\n", dataPesertaDidik[i].rataRataNilai);
    } else if(dataPesertaDidik[i].jalurSeleksi == ZONASI) {
      printf("Jarak dari rumah ke sekolah tujuan: %.2f\n",
             dataPesertaDidik[i].jarakRumah);
    }

    printBorder();
  }
}

void hasilSeleksiPesertaDidik() {
  int pilihJalurSeleksi, indexSekolahDicari;
  char namaSekolah[50];
  struct DataSekolah sekolahDicari;

  if(jumlahPesertaDidikTerdaftar == 0) {
    printf("Belum ada peserta didik yang terdaftar.\n");
    return;
  } else {
    listSekolahTerdaftar();

    do {
      printf("\nPilih nama sekolah: ");
      scanf(" %[^\n]", namaSekolah);

      indexSekolahDicari = searchSekolahByName(namaSekolah, &sekolahDicari);

      if(indexSekolahDicari == -1) {
        printf("\nNama sekolah tidak valid, silakan coba lagi.\n");
      } else {
        printf("\nSekolah ditemukan:\n");
        printf("Nama Sekolah: %s\n", sekolahDicari.namaSekolah);
        printf("Alamat Sekolah: %s\n", sekolahDicari.alamatSekolah);
        printf("Kuota Peserta Didik Baru: %d\n",
               sekolahDicari.kuotaPesertaDidikBaru);
        printf("Kuota Jalur Prestasi Rapor: %d\n",
               sekolahDicari.kuotaJalurPrestasiRapor);
        printf("Kuota Jalur Zonasi: %d\n", sekolahDicari.kuotaJalurZonasi);
      }

    } while(indexSekolahDicari == -1);

    // Pilih Jalur Seleksi
    printf("Pilih Jalur Seleksi:\n");
    printf("1. Prestasi (60%%)\n");
    printf("2. Zonasi (40%%)\n");
    printf("Masukkan pilihan Anda (1/2): ");
    scanf("%d", &pilihJalurSeleksi);

    // Menampilkan hasil seleksi berdasarkan jalur
    if(pilihJalurSeleksi == 1) {
      // Jalur Prestasi - Urutkan berdasarkan nilai rata-rata
      printf("\nHasil Seleksi Jalur Prestasi Rapor:\n");

      int kuotaPrestasi = sekolahDicari.kuotaJalurPrestasiRapor;
      int count = 0;
      // Mengurutkan berdasarkan rata-rata nilai tertinggi
      for(int i = 0; i < jumlahPesertaDidikTerdaftar; i++) {
        if(strcmp(dataPesertaDidik[i].sekolahTujuan,
                  sekolahDicari.namaSekolah) == 0 &&
           dataPesertaDidik[i].jalurSeleksi == PRESTASI_RAPOR) {
          count++;
        }
      }

      // Urutkan berdasarkan rata-rata nilai tertinggi
      for(int i = 0; i < count - 1; i++) {
        for(int j = i + 1; j < count; j++) {
          if(dataPesertaDidik[i].rataRataNilai <
             dataPesertaDidik[j].rataRataNilai) {
            struct DataPesertaDidik temp = dataPesertaDidik[i];
            dataPesertaDidik[i] = dataPesertaDidik[j];
            dataPesertaDidik[j] = temp;
          }
        }
      }

      // Tampilkan hasil seleksi sesuai kuota
      for(int i = 0; i < kuotaPrestasi; i++) {
        printf("Nama Peserta Didik: %s\n", dataPesertaDidik[i].namaLengkap);
        printf("Rata-rata Nilai: %.2f\n", dataPesertaDidik[i].rataRataNilai);
        printBorder();
      }

    } else if(pilihJalurSeleksi == 2) {
      // Jalur Zonasi - Urutkan berdasarkan jarak terdekat
      printf("\nHasil Seleksi Jalur Zonasi:\n");

      int kuotaZonasi = sekolahDicari.kuotaJalurZonasi;
      int count = 0;
      // Mengurutkan berdasarkan jarak
      for(int i = 0; i < jumlahPesertaDidikTerdaftar; i++) {
        if(strcmp(dataPesertaDidik[i].sekolahTujuan,
                  sekolahDicari.namaSekolah) == 0 &&
           dataPesertaDidik[i].jalurSeleksi == ZONASI) {
          count++;
        }
      }

      // Urutkan berdasarkan jarak terdekat
      for(int i = 0; i < count - 1; i++) {
        for(int j = i + 1; j < count; j++) {
          if(dataPesertaDidik[i].jarakRumah > dataPesertaDidik[j].jarakRumah) {
            struct DataPesertaDidik temp = dataPesertaDidik[i];
            dataPesertaDidik[i] = dataPesertaDidik[j];
            dataPesertaDidik[j] = temp;
          }
        }
      }

      // Tampilkan hasil seleksi sesuai kuota
      for(int i = 0; i < kuotaZonasi; i++) {
        printf("Nama Peserta Didik: %s\n", dataPesertaDidik[i].namaLengkap);
        printf("Jarak dari Rumah ke Sekolah: %.0f m\n",
               dataPesertaDidik[i].jarakRumah);
        printBorder();
      }

    } else {
      printf("Pilihan tidak valid, kembali ke menu utama.\n");
    }
  }
}

void cariDataPendaftar() {
  char nomorPendaftaran[10];
  bool ditemukan = false;

  printf("Masukkan nomor pendaftaran yang ingin dicari: ");
  scanf("%s", nomorPendaftaran);

  for(int i = 0; i < jumlahPesertaDidikTerdaftar; i++) {
    if(strcmp(dataPesertaDidik[i].nomorPendaftaran, nomorPendaftaran) == 0) {
      ditemukan = true;
      printf("\nData ditemukan!\n");
      printf("Nomor Pendaftaran: %s\n", dataPesertaDidik[i].nomorPendaftaran);
      printf("Nama Lengkap: %s\n", dataPesertaDidik[i].namaLengkap);
      printf("Jenis Kelamin: %s\n", dataPesertaDidik[i].jenisKelamin);
      printf("Sekolah Asal: %s\n", dataPesertaDidik[i].sekolahAsal);
      printf("Sekolah Tujuan: %s\n", dataPesertaDidik[i].sekolahTujuan);

      if(dataPesertaDidik[i].jalurSeleksi == PRESTASI_RAPOR) {
        printf("Jalur Seleksi: Prestasi Nilai Rapor\n");
        printf("Rata-rata nilai Bahasa Indonesia: %.2f\n",
               dataPesertaDidik[i].nilaiBahasaIndonesia);
        printf("Rata-rata nilai Bahasa Inggris: %.2f\n",
               dataPesertaDidik[i].nilaiBahasaInggris);
        printf("Rata-rata nilai Matematika: %.2f\n",
               dataPesertaDidik[i].nilaiMatematika);
        printf("Rata-rata nilai: %.2f\n", dataPesertaDidik[i].rataRataNilai);
      } else if(dataPesertaDidik[i].jalurSeleksi == ZONASI) {
        printf("Jalur Seleksi: Zonasi\n");
        printf("Jarak dari rumah ke sekolah tujuan: %.2f meter\n",
               dataPesertaDidik[i].jarakRumah);
      }
    }
  }

  if(!ditemukan) {
    printf("\nPeserta peserta dengan nomor pendaftaran '%s' tidak ditemukan.\n",
           nomorPendaftaran);
  }
}

void mainMenu() {
  int selectMenu;

  do {
    displayMainMenu();

    printf("Pilih menu: ");
    scanf("%d", &selectMenu);

    switch(selectMenu) {
      case 1:
        adminLogin();
        clrscr();
        break;
      case 2:
        pendaftaranPesertaDidikBaru();
        clrscr();
        break;
      case 3:
        hasilSeleksiPesertaDidik();
        clrscr();
        break;
      case 4:
        listPesertaDidikTerdaftar();
        clrscr();
        break;
      case 5:
        cariDataPendaftar();
        clrscr();
        break;
        //      default:
        //        printf("Menu tidak valid, coba lagi.\n");
    }
  } while(selectMenu != 0);
}

int main() {
  mainMenu();
  // clrscr();
  return 0;
}
