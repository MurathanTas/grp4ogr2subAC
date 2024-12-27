
# Linux Shell Uygulaması

## Proje Özeti
Bu proje, **Sakarya Üniversitesi İşletim Sistemleri** dersi kapsamında geliştirilmiş basit bir Linux Shell uygulamasıdır. Proje, temel komut yürütme işlevlerinin yanı sıra **pipe işlemleri**, **giriş/çıkış yönlendirme** ve **arka plan işlemleri** gibi özellikleri desteklemektedir.

## Geliştirici Ekibi
- **Murathan Taş**  
- **Buğra Akşit**  
- **Selva Maramaei**  
- **İrem Kabil**  
- **Elif Yerlikaya**  

## Temel Özellikler
- **Komut Yürütme**: Standart komut satırı işlevselliği.  
- **Pipe (`|`) Desteği**: Bir komutun çıktısını diğerine giriş olarak aktarır.  
- **Giriş/Çıkış Yönlendirme**:  
  - `>`: Çıktıyı bir dosyaya yönlendirme.  
  - `<`: Girişi bir dosyadan alma.  
- **Arka Plan İşlemleri**: `&` ile arka planda komut çalıştırma.  
- **Yerleşik Komut**: `quit` ile shell'den çıkış.  

## Kurulum ve Kullanım
1. **Depoyu klonlayın**:  
   ```bash
   git clone https://github.com/MurathanTas/grp4ogr2subAC
   cd grp4ogr2subAC
   ```

2. **Proje dosyalarını derleyin**:  
   ```bash
   make
   ```

3. **Shell uygulamasını çalıştırın**:  
   ```bash
   ./shell
   ```

## Kullanım Örnekleri
- **Temel Komut**:  
  ```bash
  ls -l
  ```
- **Pipe Kullanımı**:  
  ```bash
  ls | grep txt
  ```
- **Giriş/Çıkış Yönlendirme**:  
  ```bash
  cat < input.txt > output.txt
  ```
- **Arka Plan İşlemi**:  
  ```bash
  sleep 10 &
  ```
- **Çıkış**:  
  ```bash
  quit
  ```
