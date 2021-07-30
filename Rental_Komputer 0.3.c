/*
	Name: Program Rental Komputer Manager
	Compiler: Dev C++ 5.11 
	Author: Alfan-191511037, Hadi-191511046, Nisrina-191511058
	Date: 28/12/19 19:43
	Description: Program Untuk menjalankan usaha rental komputer dengan melakukan pendataan pelanggan beserta mengatur komputer
*/

//Pemanggilan library
#include<stdio.h>
#include<conio.h>
#include<process.h>
#include<stdbool.h>
#include<strings.h>
#include<time.h>
#include <windows.h>
#define JUM_BLOK 1

//Deklarasi dan inisialisasi type//
typedef struct/*tipe data untuk waktu*/{
	int jam; 
	int menit;
	int detik;
}waktu;
typedef struct /*tipe data untuk data_rental*/{
	char Nama[12];
	int id_pelanggan;
	int nomor_komp;
	int paket;
	int total_biayakertas;
	int total_tambahan;
	int total_biaya;
	waktu jam_masuk;
	waktu jam_keluar;

}data;

//deklarasi secara global
int i,j;

//Fungsi&Prosedur (subprogram)
void mainmenu(int *c){ //Menampilkan halaman utama (c: parameter bertipe integer dengan passing parameter by address untuk menampung pilihan menu)
	printf("\n----------------------------------\n");
	printf("\t Rental Komputer\n| ALfan-037|Hadi-046|Nisrina-056 |\n----------------------------------\n|\t\t\t\t |\n|1. Register Rental\t\t |\n|2. Tampilkan status komputer\t |\n|3. Beli makan/minum\t\t |\n|4. Tampilkan pengguna tertentu\t |\n|5. Display Semua User\t\t |\n|6. Checkout\t\t\t |\n|7. Tampilkan Rekap\t\t |\n|8. Help\t\t\t |\n|9. Exit\t\t\t |\n\nPilihan Anda: ");
	scanf("%d",&*c);
}//dibuat oleh hadi

void inisialisasi(bool a[],int b[],data c[]){ //Untuk melakukan inisialisasi pada array komposit dt_komputer, dt_tambahan, dan dt_rental (a: parameter bertipe kom dengan passing by address, b: parameter bertipe tmb dengan passing by address, c: parameter bertipe data dengan passing by address )
	for(i=0;i<10;i++){	
		a[i]=true;
		strcpy(c[i].Nama,"?");
		c[i].id_pelanggan=0;
		c[i].nomor_komp=0;
		c[i].jam_masuk.jam=0,c[i].jam_masuk.menit=0,c[i].jam_masuk.detik=0;
		c[i].jam_keluar.jam=0,c[i].jam_keluar.menit=0,c[i].jam_keluar.detik=0;
		c[i].total_biayakertas=0;
		c[i].total_tambahan=0;
		c[i].total_biaya=0;
	}
	//Daftar harga makanan dan minuman
	b[0]=6000;//mie
	b[1]=3000;//basreng
	b[2]=9000;//nasgor
	b[3]=2500;//keripik
	b[4]=2000;//wafer
	b[5]=3000;//kopi
	b[6]=6000;//teh botol
	b[7]=4000;//teh kotak
	b[8]=3000;//aqua/mineral
	b[9]=6000;//jus buah
}// dibuat oleh Alfan,Hadi,Nisrina

void cleardatauser(data a[],bool b[],int x,int *jml){ //Untuk mengembalikan salahsatu data pelanggan ke situasi awal, setelah pelanggan keluar dari rental (a: parameter bertipe data dengan passing by address, b: parameter bertipe kom dengan passing by address, x: parameter bertipe integer dengan passing by value, jml:parameter bertipe integer dengan passing by address)
	for(i=0;i<10;i++){
		if(i+1==a[x].nomor_komp){
			b[i]=true;
		}
	}
	strcpy(a[x].Nama,"?");
	a[x].id_pelanggan=0;
	a[x].nomor_komp=0;
	a[x].jam_masuk.jam=0,a[x].jam_masuk.menit=0,a[x].jam_masuk.detik=0;
	a[x].jam_keluar.jam=0,a[x].jam_keluar.menit=0,a[x].jam_keluar.detik=0;
	a[x].total_biayakertas=0;
	a[x].total_tambahan=0;
	a[x].total_biaya=0;
	*jml=*jml-1;
}// dibuat oleh alfan

void displaykomputer(bool a[]){ //Untuk menunjukan daftar komputer beserta ID dan statusnya
	printf("-List Komputer-\n\n|ID\tStatus |\n");	
	for(i=0;i<10;i++){
		if(a[i]==true){
			printf("|%d\tVacant |\n",i+1);
		}
		else{
			printf("|%d\tIn Use |\n",i+1);	
		}
	}
}//dibuat oleh nisrina

void entrykomputer(bool b[],data a[],int x){ //Untuk melakukan entry id komputer yang akan digunakan ke dt_rental seorang pelanggan serta merubah status sebuah komputer menjadi "In Use"(sedang digunakan)
	int choice;
	bool valid=false;
	do{
		printf("\nSilahkan pilih komputer yang ingin digunakan (1-10): ");
		scanf("%d",&choice);
		if(choice>10 || choice<0){
			printf("\n[Maaf, hanya ada 10 komputer]\n\n");
		}
		else{
			for(i=0;i<10;i++){
				if(choice==i+1){
					if(b[i]==true){
						printf("\n[Komputer tersedia, silahkan pakai]\n\n");
						b[i]=false;
						a[x-1].nomor_komp=choice;
						valid=true;
						break;
					}
					else{
						printf("\n[Maaf komputer tidak tersedia]\n\n");
						break;
					}
				}	
			}
		}
	}while(valid==false);
}//dibuat oleh hadi

void entrydata(data a[],bool b[],int *jml){ //Untuk melakukan entry data pelanggan ke dt_rental seperti nama dan jam masuk 
	bool valid=false;
	int pil;
	displaykomputer(b);
	entrykomputer(b,a,*jml+1);
	//pilih paket
	do{
		printf("Pilih paket:\n 1. Paket Reguler(Rp.3000/Jam)\n 2. Paket VIP/Menggunakan AC (Rp.5000/Jam)\nPilihan anda: ");
		scanf("%d",&a[*jml].paket);
		if(a[*jml].paket<1||a[*jml].paket>2){
			printf("\n[Hanya ada 2 paket]\n");
		}
		else{
			valid=true;
		}
	}while(valid==false);
	printf("\nMasukan nama pelanggan: ");
	scanf("%s",&a[*jml].Nama);
	valid=false;
	do{	
		printf("\nMasukan jam masuk (hh:mm:ss): ");
		scanf("%d:%d:%d",&a[*jml].jam_masuk.jam,&a[*jml].jam_masuk.menit,&a[*jml].jam_masuk.detik);
		if(a[*jml].jam_masuk.jam>23|| a[*jml].jam_masuk.menit>59 || a[*jml].jam_masuk.detik>59 || a[*jml].jam_masuk.jam<0 || a[*jml].jam_masuk.menit<0 || a[*jml].jam_masuk.detik<0){
			valid=false;
			printf("\nWaktu tidak valid, silahkan ulangi lagi\n");	
		}
		else{
			printf("\nWaktu valid, silahkan lanjutkan\n\n");	
			valid=true;
		}
	}while(valid==false);	
	a[*jml].id_pelanggan=*jml+1;
	*jml=*jml+1;
}// dibuat oleh alfan

void displayuser(data a[],int jml){ //Untuk menamplkan data seorang pelanggan
	int choice;
	bool found=false;
	printf("Masukan ID pelanggan: ");
	scanf("%d",&choice);
	if(choice<=0 || choice >10){
		printf("\nID tidak ditemukan\n");
	}
	else{
			for(i=0;i<10;i++){
			if(choice==a[i].id_pelanggan){
				printf("\nID Pelanggan\t: %d\n",a[i].id_pelanggan);
				printf("ID Komputer\t: %d\n",a[i].nomor_komp);
				printf("Nama Pelanggan\t: %s\n",a[i].Nama);
				printf("Jam Masuk\t: %d:%d:%d\n",a[i].jam_masuk.jam,a[i].jam_masuk.menit,a[i].jam_masuk.detik);
				printf("Total tambahan\t: Rp.%d\n",a[i].total_tambahan);
				found=true;
			}
		}
		if(found==false){
			printf("\nPelanggan tidak ditemukan\n");
		}	
	}

}//dibuat oleh nisrina

void displayalluser(data a[],int jml){ //Untuk menamplkan data seorang pelanggan
	printf("\nID\tKomputer\tNama\t\tJam Masuk\tTotal tambahan\n");
	for(i=0;i<10;i++){
		printf(">%d\t%d\t\t%s\t\t%d:%d:%d\t\t%d\t\n",a[i].id_pelanggan,a[i].nomor_komp,a[i].Nama,a[i].jam_masuk.jam,a[i].jam_masuk.menit,a[i].jam_masuk.detik,a[i].total_tambahan);
		}
}//dibuat oleh alfan

int hitungtambahan(int b[]){ //Untuk menghitung total biaya dari makanan/minuman yang dibeli seorang pelanggan
	int choice,quantity;
	int total=0;
	printf("Pilih item : ");
	scanf("%d",&choice);
	for(j=0;j<10;j++){
		if(choice==j+1){
			printf("Jumlah item : ");
			scanf("%d",&quantity);
			total=b[j]*quantity;
			printf("\nTotal pembelian: Rp.%dx%d = Rp. %d\n",b[j],quantity,total);
		}
	}
	return total;
}//dibuat oleh nisrina

void printorder(int b[]){ //Untuk menampilkan menu makanan/minuman
	printf(" Nama\t\t\t\tHarga\n");
	printf(">1.  Mie\t\t\tRp. %d\n",b[0]);
	printf(">2.  Basreng\t\t\tRp. %d\n",b[1]);
	printf(">3.  Nasgor\t\t\tRp. %d\n",b[2]);
	printf(">4.  Keripik\t\t\tRp. %d\n",b[3]);
	printf(">5.  Wafer\t\t\tRp. %d\n",b[4]);
	printf(">6.  Kopi\t\t\tRp. %d\n",b[5]);
	printf(">7.  Teh Botol\t\t\tRp. %d\n",b[6]);
	printf(">8.  Teh Kotak\t\t\tRp. %d\n",b[7]);
	printf(">9.  Air mineral\t\tRp. %d\n",b[8]);
	printf(">10. Jus\t\t\tRp. %d\n",b[9]);
}//dibuat oleh hadi

void OrderTambahan(data a[],int b[],int jml){ //Untuk menghitung total biaya tambahan berupa makanan/minuman untuk seorang pelanggan
	int find;
	printf("\nMasukan ID pengguna: ");
	scanf("%d",&find);
	for(i=0;i<jml;i++){
		if(a[i].id_pelanggan==find){
			printorder(b);
			a[i].total_tambahan=a[i].total_tambahan+hitungtambahan(b);
			printf("Total tambahan %s : Rp. %d",a[i].Nama,a[i].total_tambahan);
		}
		else{
			printf("\nPelanggan tidak ditemukan\n");
		}	
	}
}//dibuat oleh nisrina

int biayapakai(data a[],int x){ //Untuk menghitung total biaya penggunaan komputer berdasarkan waktu seorang pelanggan
	int total,pph,secondout,secondin,tot;
	bool valid;
	do{	
		printf("\nMasukan jam keluar (hh:mm:ss): ");
		scanf("%d:%d:%d",&a[x].jam_keluar.jam,&a[x].jam_keluar.menit,&a[x].jam_keluar.detik);
		if(a[x].jam_keluar.jam>23|| a[x].jam_keluar.menit>59 || a[x].jam_keluar.detik>59 || a[x].jam_keluar.jam<0 || a[x].jam_keluar.menit<0 || a[x].jam_keluar.detik<0||a[x].jam_keluar.jam<a[x].jam_masuk.jam){
			valid=false;
			printf("\nWaktu tidak valid, silahkan ulangi lagi\n");	
		}
		else{
			printf("\nWaktu valid, silahkan lanjutkan\n\n");	
			valid=true;
		}
	}while(valid==false);
	//paket
	if(a[x].paket==2){
		pph=5000;
	}
	else{
		pph=3000;
	}
	//price calculation
	secondout=(a[x].jam_keluar.jam*3600)+(a[x].jam_keluar.menit*60)+a[x].jam_keluar.detik;
	secondin=(a[x].jam_masuk.jam*3600)+(a[x].jam_masuk.menit*60)+a[x].jam_masuk.detik;
	tot=secondout-secondin;
	if(tot%3600>0){
		total=((tot/3600)+1)*pph;
	}
	else{
		total=(tot/3600)*pph;
	}
	return total;
}//dibuat oleh alfan

int biayakertas(data a[],int x){  //Untuk menghitung total biaya kertas yang digunakan oleh seorang pelanggan
	int type,quantity;
	int total;
	bool done=false;
	do{
		printf("Masukan jenis kertas yang sudah dipakai \n1. Berwarna, 2. Tidak Berwarna,3. Tidak Print\nPilihan Anda:  ");
		scanf("%d",&type);
		if(type==1){
			printf("Masukan jumlah kertas yang digunakan: ");
			scanf("%d",&quantity);
			total=(500*quantity);
			done=true;
		}
		else if(type==2){
			printf("Masukan jumlah kertas yang digunakan: ");
			scanf("%d",&quantity);
			total=(250*quantity);
			done=true;
		}
		else if(type==3){
			total=0;
			done=true;
		}
		else{
			printf("\nHanya ada 3 jenis kertas\n");
		}
	}while(done==false);
	return total;
}// dibuat oleh alfan

void printstruk(data a[],int x){ //Untuk menampilkan data terakhir pelanggan ketika pelanggan keluar rental
	printf("\nID Pelanggan\t: %d\n",a[x].id_pelanggan);
	printf("ID Komputer\t: %d\n",a[x].nomor_komp);
	printf("Nama \t\t: %s\n",a[x].Nama);
	printf("Jam Masuk\t: %d:%d:%d\n",a[x].jam_masuk.jam,a[x].jam_masuk.menit,a[x].jam_masuk.detik);
	printf("Jam Keluar\t: %d:%d:%d\n",a[x].jam_keluar.jam,a[x].jam_keluar.menit,a[x].jam_keluar.detik);
	printf("Biaya tambahan\t: Rp.%d\n",a[x].total_tambahan);
	printf("Biaya kertas\t: Rp.%d\n",a[x].total_biayakertas);
	printf("Pilihan Paket\t: %d \n",a[x].paket);
	printf("Biaya akhir\t: Rp.%d\n",a[x].total_biaya);
}//dibuat oleh alfan

void addtofile(data A[],int x){	//prosedur untuk menambahkan data ke File dari record terakhir
	
    FILE *fp ;
    data temp;
	
    fp = fopen("DataUser.dat", "ab") ;
    if ( fp == NULL ){ 
        printf( "File failed to open." ) ; 
    } 
    else{
		fwrite(&A[x],sizeof(A[x]),JUM_BLOK,fp);
    }
	fclose(fp);
}//dibuat oleh hadi

void viewfile(){//Untuk menampilkan file rekap datauser yang pernah menggunakan rental
	
	FILE *fp;
	data temp;
	
	if((fp=fopen("DataUser.dat","rb"))== NULL){
		printf("File tidak dapat dibuka! \r\n");
		exit(1);
	}
	printf("\n							---Data Pengguna---\n\n\n");
	printf("\t\tKomputer Nama\t\tJam Masuk\tJam Keluar\tTambahan\tKertas\tPaket\tBiaya Akhir\n");
	rewind(fp);
	while ((fread(&temp, sizeof(temp), JUM_BLOK, fp)) == JUM_BLOK){
		printf("\t\t %d\t %s\t\t%d:%d:%d\t\t%d:%d:%d\t\tRp.%d\t\tRp.%d\t%d\tRp.%d\n", temp.nomor_komp, temp.Nama, temp.jam_masuk.jam, temp.jam_masuk.menit, temp.jam_masuk.detik, 
		temp.jam_keluar.jam, temp.jam_keluar.menit, temp.jam_keluar.detik, temp.total_tambahan, temp.total_biayakertas, temp.paket, temp.total_biaya);
	}
	fclose(fp);
}//dibuat oleh alfan

void checkout(data a[],bool b[],int *jml){ //Untuk menghitung biaya total yang harus dibayarkan oleh pelanggan berdasarkan penggunaan komputer, kertas yang digunakan, dan makanan/minuman yang dibeli
	int choice=0;
	bool found=false;
	printf("Masukan ID :");
	scanf("%d",&choice);
	if(choice<=0 || choice >10){
		printf("\nID tidak ditemukan\n");
	}
	else{
		for(i=0;i<*jml;i++){
			if(choice==a[i].id_pelanggan){
				found=true;
				a[i].total_biayakertas=biayakertas(a,i);
				a[i].total_biaya=a[i].total_tambahan+a[i].total_biayakertas+biayapakai(a,i);
				printstruk(a,i);
				addtofile(a,i);
				cleardatauser(a,b,i,&*jml);
			}
		}
		if(found==false){
			printf("\nPelanggan tidak ditemukan\n");
		}
	}
}//dibuat oleh hadi

void help(){//Menampilkan file berisi User Manual
		
	FILE *fp;
	char ch;
	
	if((fp=fopen("Help.txt","rt"))== NULL){
		printf("File tidak dapat dibuka! \r\n");
	}
	else{
		ch = fgetc(fp);	
		while (ch != EOF){
        	printf ("%c", ch);
        	ch = fgetc(fp);
    	}
	}
    fclose(fp);
}//dibuat oleh nisrina

//Modul Utama
main(){
	//Deklarasi lokal
	int choice=0,pelanggan=0;
	data dt_rental[10];
	bool dt_komputer[10];
	int dt_tambahan[10];
	system("COLOR F0");
	//Algoritma
	inisialisasi(dt_komputer,dt_tambahan,dt_rental);
	do
	{
		system("cls");
		mainmenu(&choice);
		switch(choice)
		{
			case 1:{//regist
				entrydata(dt_rental,dt_komputer,&pelanggan);
				break;
			}
			case 2:{//display komputer
				displaykomputer(dt_komputer);
				break;
			}
			case 3:{//makan/minum
				OrderTambahan(dt_rental,dt_tambahan,pelanggan);
				break;
			}
			case 4:{//display 1 data user
				displayuser(dt_rental,pelanggan);
				break;
			}
			case 5:{//display semua user
				displayalluser(dt_rental,pelanggan);
				break;
			}
			case 6:{//checkout
				checkout(dt_rental,dt_komputer,&pelanggan);
				break;
			}
			case 7:{
				viewfile();
				break;
			}
			case 8:{//help
				help();
				break;
			}
			case 9:{
				printf("\n\n\nHave a nice day!\n\n");
				return 0;				
			}
			default:{
				printf("\nHanya ada 7 opsi\n");
				break;
			}
		}
		getch();
	}while(choice!=9);
}//dibuat oleh Alfan,Hadi,Nisrina
