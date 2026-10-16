//Selecione entre estas redes usando // nas que não serão usadas
//#define casa
#define Lasec
#ifdef casa
 const char* ssi = "AP 104 -2.4G";//nome da rede
 const char* passwor =  "falcon104";//senha
#elif defined(Lasec)
 const char* ssi = "LASEC";//nome da rede
 const char* passwor =  "lasecca123";//senha
#endif 