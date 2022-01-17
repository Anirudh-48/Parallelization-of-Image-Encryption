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
 
 
