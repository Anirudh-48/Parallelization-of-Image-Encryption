# Parallelization AES based Encryption
The project mainly uses OpenMP in order to perform parallelization.

Serial Algorithm for image encryption using AES:
AES_img_encryption(IMG,key):
  1. Result=new Matrix(IMG.rows,IMG.cols,CV_8UC3)
  2. for i=0 to IMG.rows:
  3. for j=0 to IMG.cols*IMG.channels & j=j+16:
  4. temp<-new uint8_t[16]
  5. for k=j to k<j+16 and k<IMG.cols*IMG.channels
  6. temp[k-j]<-IMG.at(i,k)
  7. aes_encrypt(temp,key)
  8. for k=j to k<j+16 and k<IMG.cols*IMG.channels
  9. Result.at(i,k)=temp[k-j]
  10. return Result

Serial Algorithm for image decryption using AES:
AES_img_decryption(IMG,key):
  1. Result=new Matrix(IMG.rows,IMG.cols,CV_8UC3)
  2. for i=0 to IMG.rows:
  3. for j=0 to IMG.cols*IMG.channels & j=j+16:
  4. temp<-new uint8_t[16]
  5. for k=j to k<j+16 and k<IMG.cols*IMG.channels
  6. temp[k-j]<-IMG.at(i,k)
  7. aes_decrypt(temp,key)
  8. for k=j to k<j+16 and k<IMG.cols*IMG.channels
  9. Result.at(i,k)=temp[k-j]
  10. return Result
 
SAMPLE OUTPUT:
Original Image(Iron man: 400x400):
![ironman400](https://user-images.githubusercontent.com/62154803/149721083-068ff6b6-0679-4450-9073-596314b3c70b.png)
Encrypted Image(Iron man: 400x400):
![ironman400enc](https://user-images.githubusercontent.com/62154803/149721089-16b7e755-74c8-4163-9f2b-a34c9e932c81.png)
Original Image(Iron man:800x800):
![ironman800](https://user-images.githubusercontent.com/62154803/149721092-09225fcc-e39f-4b9f-b686-b39181c086c3.png)
Encrypted Image(Iron man:800x800):
![ironman800enc](https://user-images.githubusercontent.com/62154803/149721095-997a8a3e-6212-480c-833e-8fc7e722cb1c.png)
