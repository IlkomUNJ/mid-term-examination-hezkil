[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/ZCO_vauY)
Repository for final lesson before mid term of computer graphic course

1313623070 Yehezkiel Tornagogo Lumbantoruan
AI link :
https://gemini.google.com/share/b529c0c4b122
https://www.perplexity.ai/search/finding-correct-window-size-in-JJJBUio1SmqX9vf26gqxxQ (down)


Jawaban soal no. 1
ukuran windows size yang sedang digunakan (3x3) adalah ukuran standard yang biasanya dioperasikan pada line segmen detection. ukuran standar terkecil ini dapat secara efektif menghitung gradien dan arah di sekitar piksel pusat. Filter seperti operator Sobel, Prewitt, dan Laplacian sering menggunakan 3×3 untuk mendeteksi tepi dan segmen garis. Sebagai contoh ukuran selain 3x3, yaitu 5x5. 5x5 mendeteksi wilayah dan segmen yang lebih banyak dan detail tetapi lebih lambat dan kompleks. Tetapi 5x5 juga dapat menghandel noise yang tinggi. 5x5 biasa digunakan untuk advance filter seperti blur dan sharpness. Untuk line detection 3x3 is good enough untuk menhandle segment for line detection.

Jawaban soal no.2
Pola 1,Horizontal,(​010,​010,​010​​),"Garis lurus horizontal
Pola 2,Vertikal,(​000,​111,​000)​​,"Garis lurus vertikal
Pola 3,Diagonal Kiri Atas ke Kanan Bawah,(​100,​010,​001​​), atau ​(001,​010​,100​​)
pola 4, endpoint, (​000​,010,​010​​) dapat horinzontal kanan dan kiri dan vertikal atas dan bawah