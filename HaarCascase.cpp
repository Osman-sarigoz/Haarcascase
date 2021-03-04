#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <conio.h>
#include <fstream>
#include <string>
using namespace std;
using namespace cv;
void anaMenu();
int pozitifResimSiniri = 200;
int negatifResimSiniri = 100;
void cascadeKlasoruSil()
{
char komut[200];
snprintf(komut, 200, "rm cascade/*");
system(komut);
anaMenu();
}

void cascadeKlasoruSil1()
{
char komut[200];
snprintf(komut, 200, "rm cascade/*");
system(komut);
}
void dosyalariSil()
{
char komut[200];
snprintf(komut, 200, "rm pozitif/*");
system(komut);
snprintf(komut, 200, "rm negatif/*");
system(komut);
system("rm pozitifResim.vec");
ofstream file;
file.open("negatif.txt");
file << "";
file.close();
file.open("pozitif.txt");
file << "";
file.close();
file.open("resimSayisiPozitif.txt");
file << 0;
file.close();
file.open("resimSayisiNegatif.txt");
file << 0;
file.close();
anaMenu();
}
char kameraPenceresiAdi[60] = "Ekran";
int negatifResimSayisi()
{
string satir;
ifstream myfile("resimSayisiNegatif.txt");
getline(myfile, satir);
getline(myfile, satir);
myfile.close();
int sayi = atoi(satir.c_str()); 
return sayi;
}
int pozitifResimSayisi()
{
string satir;
ifstream myfile("resimSayisiPozitif.txt");
getline(myfile, satir);
myfile.close();
int sayi = atoi(satir.c_str());
return sayi;
}
void negatifResimSayisiKaydet(int sayi)
{
ofstream file;
file.open("resimSayisiNegatif.txt");
file << sayi;
}
void pozitifResimSayisiKaydet(int sayi)
{
ofstream file;
file.open("resimSayisiPozitif.txt");
file << sayi;
}
int pozitifSayici = 0;
void pozitifResimKaydet()
{
int height(240);
int width(320);
cv::VideoCapture vid(0);
vid.set(CV_CAP_PROP_FRAME_HEIGHT, height);
vid.set(CV_CAP_PROP_FRAME_WIDTH, width);
vid.set(cv::CAP_PROP_FOURCC, 0x21);
vid.set(cv::CAP_PROP_FPS, 32);
pozitifSayici = pozitifResimSayisi();
namedWindow(kameraPenceresiAdi, CV_WINDOW_AUTOSIZE);
ofstream file;
file.open("pozitif.txt", ios::app);
Mat arka; 
vector<int> sparam;
sparam.push_back(CV_IMWRITE_JPEG_QUALITY);
sparam.push_back(50);
char yazi[250]; 
int genislik = 80;
createTrackbar("Genislik", kameraPenceresiAdi, &genislik, 160);
int yukseklik = 60;
createTrackbar("Yukseklik", kameraPenceresiAdi, &yukseklik, 120);
int xeks1 = 100, xeks2 = 220, yeks1 =60, yeks2 = 180;
int basla = -1;
while (true)
{
char a = waitKey(33);
if ((a == 27) || (pozitifSayici > pozitifResimSiniri - 1))
{
file.close();
destroyAllWindows();
pozitifResimSayisiKaydet(pozitifSayici);
break;
}
Mat frame;
vid.read(frame);
xeks1 = (320 - (genislik * 2)) / 2;
xeks2 = xeks1 + (genislik * 2);
yeks1 = (240 - (yukseklik * 2)) / 2;
yeks2 = yeks1 + (yukseklik * 2);
arka = Mat::zeros(frame.size(), frame.type());
line(arka, Point(xeks1, 0), Point(xeks1, 240), Scalar(0, 255, 0), 1); 
line(arka, Point(xeks2, 0), Point(xeks2, 240), Scalar(0, 255, 0), 1);
line(arka, Point(0, yeks1), Point(320, yeks1), Scalar(0, 255, 0), 1);
line(arka, Point(0, yeks2), Point(320, yeks2), Scalar(0, 255, 0), 1);
if (a == 'b') 
basla = basla*(-1);
if (basla == 1)
{
pozitifSayici++;
char resimYazisi[15];  
snprintf(resimYazisi,15, "%d", pozitifSayici);
putText(arka,resimYazisi,Point(10,30),CV_FONT_HERSHEY_COMPLEX,1,Scalar(255,255,255));
snprintf(yazi,250,"pozitif/%d.jpg",pozitifSayici);
imwrite(yazi, frame, sparam);
snprintf(yazi,250,"pozitif/\%d.jpg",pozitifSayici);
file<<yazi<<" 1 "<<xeks1<<" "<<yeks1<<" "<<(genislik*2)<<" "<<(yukseklik*2)<<endl; 
}
frame = frame + arka; 
imshow(kameraPenceresiAdi, frame);
}
}
void pozitifResimKyrp()
{
char komut[200];
snprintf(komut,200,"opencv_createsamples -info pozitif.txt -w 24 -h 24 -vec pozitifResim.vec ");
system(komut);
char komut1[200];
snprintf(komut1,200,"opencv_createsamples -vec pozitifResim.vec -w 24 -h 24");
system(komut1);
anaMenu();
}
int negatifSayici;
void negatifResimKaydet()
{
int height(240);
int width(320);
cv::VideoCapture vid(0);
vid.set(CV_CAP_PROP_FRAME_HEIGHT, height);
vid.set(CV_CAP_PROP_FRAME_WIDTH, width);
vid.set(cv::CAP_PROP_FOURCC, 0x21);
vid.set(cv::CAP_PROP_FPS, 32);
negatifSayici = negatifResimSayisi();
ofstream file;
file.open("negatif.txt", ios::app);
vector<int> sparam;
sparam.push_back(CV_IMWRITE_JPEG_QUALITY);
sparam.push_back(50);
char yazi[250];
while (true)
{
if ((waitKey(33) == 27) || (negatifSayici > negatifResimSiniri - 1))
{
file.close();
destroyAllWindows();
negatifResimSayisiKaydet(negatifSayici);
break;
}
Mat frame;
vid.read(frame);
negatifSayici++;
snprintf(yazi, 250, "negatif/%d.jpg", negatifSayici);
imwrite(yazi, frame, sparam);
snprintf(yazi, 250, "negatif/\%d.jpg", negatifSayici);
file << yazi << endl;
char resimYazisi[15]; 
snprintf(resimYazisi, 15, "%d", negatifSayici);
putText(frame, resimYazisi, Point(15, 25), CV_FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255));
imshow(kameraPenceresiAdi, frame);
}
vid.release(); 
anaMenu();
}
void yapay_zeka()
{
int height(240);
int width(320);
cv::VideoCapture vid(0);
vid.set(CV_CAP_PROP_FRAME_HEIGHT, height);
vid.set(CV_CAP_PROP_FRAME_WIDTH, width);
vid.set(cv::CAP_PROP_FOURCC, 0x21);
vid.set(cv::CAP_PROP_FPS, 32);
CascadeClassifier face_cascade;
face_cascade.load("cascade/cascade.xml");
while (waitKey(10) != 27) 
{
Mat frame;
vid >> frame;
std::vector<Rect> faces;
face_cascade.detectMultiScale(frame, faces, 1.1, 3,0, Size(20, 20));
for(size_t i = 0; i < faces.size(); i++) {
putText(frame,"NESNE ALGILANDI", Point(30, 30), CV_FONT_HERSHEY_COMPLEX, 0.75, Scalar(0, 255, 255),2);
rectangle(frame, faces[i], Scalar(0, 0, 255), 1, 1, 0);
}
imshow("frame", frame);
}
destroyAllWindows();
vid.release();
anaMenu();
}
void xmlDosyasiOlustur()
{
float minHitRate = 0.995;
int asamaSayisi;
cout << "Asama sayisini giriniz. Ornegin 17 olabilir)" << endl;
cin >> asamaSayisi;
pozitifSayici = pozitifResimSayisi();
negatifSayici = negatifResimSayisi();
cout << "Pozitif Resim Sayisi: " << pozitifSayici << endl;
cout << "Negatif Resim Sayisi: " << negatifSayici << endl;
cout << "Asama Sayisi: " << asamaSayisi << endl;
cout << "minHitRate: " << minHitRate << endl;
int numPos=floor((pozitifSayici-negatifSayici)/(1+(asamaSayisi-1)*(1-minHitRate)));
cout<<"numPos: "<<numPos<<endl;
char komut[700];
snprintf(komut, 700, "opencv_traincascade -data cascade  \
					\-vec pozitifResim.vec -bg negatif.txt -precalcValBufSize 1024 \
					\-precalcIdxBufSize 1024 -numPos %d -numNeg %d -numStages %d \
					\-maxFalseAlarmRate 0.25 -w 24 -h 24 \
					\-minHitRate 0.995 -nonsym -baseFormatSave", 
					numPos, negatifSayici, asamaSayisi);
system(komut);
anaMenu();
}
void ilkKurulum()
{
system("mkdir cascade");
system("mkdir negatif");
system("mkdir pozitif");
}
void anaMenu()
{
cout << "----------------------------------------" << endl;
cout << "	Hosgeldiniz." << endl;
cout << "	Ne yapmak istersiniz?" << endl;
cout << "----------------------------------------" << endl;
cout << "	1. Pozitif resim kaydet" << endl;
cout << "	2. Negatif resim kaydet" << endl;
cout << "	3. XML dosyasi olustur" << endl;
cout << "	4. Yapay zeka" << endl;
cout << "	5. XML dosyasi sil" << endl;
cout << "	6. Tum verileri sil" << endl;
cout << "	0. Programi Kapat" << endl;
cout << "----------------------------------------" << endl;
cout << "	Seciminiz: ";
int secim;
cin >> secim;
switch (secim)
{
	case 0:
		return;
		break;
	case 1:
		pozitifResimKaydet();
		pozitifResimKyrp();
		break;
	case 2:
		negatifResimKaydet();
		break;
	case 3:
		xmlDosyasiOlustur();
		break;
	case 4:
		yapay_zeka();
		break;
	case 5:
		cascadeKlasoruSil();
		break;
	case 6:
		cascadeKlasoruSil1();
		dosyalariSil();
		break;
	}
}
int main(int argc, const char** argv)
{
	ilkKurulum(); 
	anaMenu();
	return 0;
}
