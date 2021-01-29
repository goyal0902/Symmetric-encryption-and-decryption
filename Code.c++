#include<stdio.h>
#include<strings.h>
#include<string.h>
float encrypt[3][1], decrypt[3][1], a[3][3], b[3][3], mes[3][1], c[3][3];//hill cipher
int choice;char data[50], temp;int key, count;//playfair
void hill_encryption();	
void hill_decryption();	
void hill_getKeyMessage();	
void hill_inverse();
char encryption_pf(char []);
void choice_fill();
void decryption_pf(char []);
void play_fair_cipher();
char key_pf[100],play[5][5],ct[255],txt[255],plain_text[255],c_text[255];
int myfair();	
int main()
{ 
    printf("    		SYMMETRIC ENCRYPTION AND DECRYPTION   	  \n");
    printf("	```1. PRESS 1 FOR HILL CIPHER```\n");
    printf("	```2. PRESS 2 FOR RAILFENCE```\n");
    printf("	```3. PRESS 3 FOR CAESAR CIPHER```\n");
    printf("	```4. PRESS 4 FOR PLAY FAIR```\n");
    int a;
    scanf("\t%d",&a);
    switch(a)
    {
       case 1:
       printf(" HILL CIPHER\n");
       hill_getKeyMessage();
       hill_encryption();
       hill_decryption();
       break;
       
       case 2:
       printf("RAILFENCE CIPHER\n");
       char plain[20];
       char encryp[20];
       int key;
       printf("Enter the plain text: ");
       scanf("%s",&plain);
       printf("Enter the key: ");
       scanf("%d",&key);
       printf("Original Message: %s", plain);
       rail_encryptMsg(plain, key);
       printf("\n");
       printf("Enter the cipher text: ");
       scanf("%s",&encryp);
       rail_decryptMsg(encryp,key);
       break;
       
       case 3:
       printf("``CAESAR CIPHER\n");
	cc_getmessage();
	cc_key_input();
	
	while (1) {
		printf("\n1. Encryption\n2. Decryption\n3. Exit\n");
		printf("\nEnter You Choice:\t");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			caesar_cipher_encryption();
			break;
		case 2:
			caesar_cipher_decryption();
			break;
		case 3:
			exit(0);
		default:
			printf("\nPlease select a correct option:\n");
		}
	}
	break;
	
	case 4:
			myfair();
			break;
	default:
		printf("\nPlease select a correct option\n");
			       
    }

    return 0;
}
//HILL CIPHER
void hill_encryption() {
	int i, j, k;
	
	for(i = 0; i < 3; i++)
		for(j = 0; j < 1; j++)
			for(k = 0; k < 3; k++)
				encrypt[i][j] = encrypt[i][j] + a[i][k] * mes[k][j];
	
	printf("\nEncrypted string is: ");
	for(i = 0; i < 3; i++)
		printf("%c", (char)(fmod(encrypt[i][0], 26) + 97));
 
}
 
void hill_decryption() {
	int i, j, k;
	
	hill_inverse();
	
	for(i = 0; i < 3; i++)
		for(j = 0; j < 1; j++)
			for(k = 0; k < 3; k++)
				decrypt[i][j] = decrypt[i][j] + b[i][k] * encrypt[k][j];
	
	printf("\nDecrypted string is: ");
	for(i = 0; i < 3; i++)
		printf("%c", (char)(fmod(decrypt[i][0], 26) + 97));
	
	printf("\n");
}
 
void hill_getKeyMessage() {
	int i, j;
	char msg[3];
 
	printf("Enter 3x3 matrix for key (It should be inversible):\n");
	
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++) {
			scanf("%f", &a[i][j]);
			c[i][j] = a[i][j];
		}
	
	printf("\nEnter a 3 letter string: ");
	scanf("%s", msg);
	
	for(i = 0; i < 3; i++)
		mes[i][0] = msg[i] - 97;
}
 
void hill_inverse() {
	int i, j, k;
	float p, q;
	
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++) {
			if(i == j)
				b[i][j]=1;
			else
				b[i][j]=0;
		}
		
	for(k = 0; k < 3; k++) {
		for(i = 0; i < 3; i++) {
			p = c[i][k];
			q = c[k][k];
				
			for(j = 0; j < 3; j++) {
				if(i != k) {
					c[i][j] = c[i][j]*q - p*c[k][j];
					b[i][j] = b[i][j]*q - p*b[k][j];
				}
			}
		}
	}
	
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			b[i][j] = b[i][j] / c[i][i];
	
	printf("\n\nInverse Matrix is:\n");
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 3; j++)
			printf("%d", b[i][j]);
		
		printf("\n");
	}
}
//HILL CIPHER END
//RAILFENCE START
void rail_encryptMsg(char plain[], int key){
int msgLen = strlen(plain), i, j, dir = -1, row = 0, col = 0;
char railMatrix[key][msgLen];
for(i = 0; i < key; ++i)
for(j = 0; j < msgLen; ++j)
railMatrix[i][j] = '\n';
for(i = 0; i < msgLen; ++i){
railMatrix[row][col++] = plain[i];
if(row == 0 || row == key-1)
dir= dir * (-1);
row = row + dir;
}
printf("\nEncrypted Message: ");

for(i = 0; i < key; ++i)
for(j = 0; j < msgLen; ++j)
if(railMatrix[i][j] != '\n')
printf("%c", railMatrix[i][j]);
}


void rail_decryptMsg(char enMsg[], int key){
int mlen = strlen(enMsg), i, j, k = -1, row = 0, col = 0, m = 0;
char railMatrix[key][mlen];

for(i = 0; i < key; ++i)
for(j = 0; j < mlen; ++j)
railMatrix[i][j] = '\n';
for(i = 0; i < mlen; ++i){
railMatrix[row][col++] = '*';
if(row == 0 || row == key-1)
k= k * (-1);
row = row + k;
}

for(i = 0; i < key; ++i)
for(j = 0; j < mlen; ++j)
if(railMatrix[i][j] == '*')
railMatrix[i][j] = enMsg[m++];
row = col = 0;
k = -1;
printf("\nDecrypted Message:    ");
for(i = 0; i < mlen; ++i){
printf("%c", railMatrix[row][col++]);
if(row == 0 || row == key-1)
k= k * (-1);
row = row + k;
}
}
//RAILFENCE END


//CAESAR CIPHER START
void caesar_cipher_encryption() {
	for (count = 0; data[count] != '\0'; count++) {
		temp = data[count];
		if (temp >= 'a' && temp <= 'z') {
			temp = temp + key;
			if (temp > 'z') {
				temp = temp - 'z' + 'a' - 1;
			}
			data[count] = temp;
		} else if (temp >= 'A' && temp <= 'Z') {
			temp = temp + key;
			if (temp > 'Z') {
				temp = temp - 'Z' + 'A' - 1;
			}
			data[count] = temp;
		}
	}
	printf("\nEncrypted Message:\t%s\n", data);
}
void cc_getmessage() {
	printf("Enter a String:\t");
	scanf("%s", data);
}

void cc_key_input() {
	printf("Enter a Key:\t");
	scanf("%d", &key);
}

void caesar_cipher_decryption() {
	for (count = 0; data[count] != '\0'; count++) {
		temp = data[count];
		if (temp >= 'a' && temp <= 'z') {
			temp = temp - key;
			if (temp < 'a') {
				temp = temp + 'z' - 'a' + 1;
			}
			data[count] = temp;
		} else if (temp >= 'A' && temp <= 'Z') {
			temp = temp - key;
			if (temp < 'A') {
				temp = temp + 'Z' - 'A' + 1;
			}
			data[count] = temp;
		}
	}
	printf("\nDecrypted Message:\t%s\n", data);
}
//CAESAR CIPHER END

//Play fair Start
void choice_fill(){
int choice,flag=0;
do{
     printf("\nPress 1 for Encryption\nPress 2 for Decryption\nPress '0' for exit\n");
     scanf("%d",&choice);
     switch(choice)
	 {
     case 1 : encryption_pf(txt); flag=1;break;
     case 2 : if(flag==1)decryption_pf(ct);
     else printf("First Perform Encryption");
     break;
     case 0:return;
     default : printf("\nPlease enter valid choice\n"); break;
	 }
}
while(choice!=0);
}


char encryption_pf(char pt[]){
int i,j,k,l,row1,row2,col1,col2,p,q;
printf("\n Plain text : %s",pt);
play_fair_cipher();
j=1;
for(i=0;i<strlen(pt);){
row1=0;row2=0;col1=0;col2=0;p=0;q=0;
p=pt[i];q=pt[j]; 
printf("\t "); 
putchar(pt[i]); 
putchar(pt[j]);printf("=");
if(p=='j'){ pt[i]='i';}
if(q=='j'){ pt[i]='i';}
for(k=0;k<5;k++){ for(l=0;l<5;l++)
{if(play[k][l]==p){ row1=k;col1=l;}if(play[k][l]==q){ row2=k;col2=l;}}}
if(row1==row2){
if(col2==4)
{ct[i]=play[row1][(col1+1)%5];
ct[j]=play[row2][0];
}else
{
ct[i]=play[row1][(col1+1)%5];
ct[j]=play[row2][(col2+1)%5];
}
putchar(ct[i]);putchar(ct[j]);
}
else if(col1==col2){
	if(row2==4)
	{
		ct[i]=play[(row1+1)%5][col1];
        ct[j]=play[0][col2];
	}
	else
{
    ct[i]=play[(row1+1)%5][col1];
    ct[j]=play[(row2+1)%5][col2];
}
putchar(ct[i]);
putchar(ct[j]);
}else{
ct[i]=play[row1][col2];
ct[j]=play[row2][col1];
putchar(ct[i]);putchar(ct[j]);}i=i+2;j=j+2;
}
printf("\n\n \tEncrypted Message : %s\n",ct);
}


void decryption_pf(char pt[]){
int i,j,k,l,row1,row2,col1,col2,p,q;
printf("\n Plain text : %s",pt);
j=1;
for(i=0;i<strlen(pt);){
row1=0;row2=0;col1=0;col2=0;p=0;q=0;
p=pt[i];q=pt[j]; printf("\t "); putchar(pt[i]); putchar(pt[j]);
printf("=");
if(p=='j'){ pt[i]='i';}
if(q=='j'){ pt[i]='i';}
for(k=0;k<5;k++){for(l=0;l<5;l++)
{if( play[k][l]==p )
{ row1=k;col1=l;}
if(play[k][l]==q){
 row2=k;col2=l;
 }
 }
 }
if(row1==row2){
if(col2==0)
{ct[i]=play[row1][(col1-1)%5];
ct[j]=play[row2][4];
}else
{ct[i]=play[row1][(col1-1)%5];ct[j]=play[row2][(col2-1)%5];
putchar(ct[i]);putchar(ct[j]);}}
else if(col1==col2){

if(row2==0)
	{
		ct[i]=play[(row1-1)%5][col1];
        ct[j]=play[4][col2];
	}else
	{ct[i]=play[(row1-1)%5][col1];ct[j]=play[(row2-1)%5][col2];
putchar(ct[i]);putchar(ct[j]);}}
else{ct[i]=play[row1][col2];ct[j]=play[row2][col1];putchar(ct[i]);
putchar(ct[j]);
}
i=i+2;j=j+2;
}
printf("\n\n \tDecrypted Message : %s\n",ct);
}


void play_fair_cipher(){//Creating playfair matrix
int i,k,j,size;
printf("\n Enter key : "); 
scanf("%s",key_pf);
strcat(key_pf,"abcdefghiklmnopqrstuvwxyz");
size=strlen(key_pf);
for(i=0;i<size;i++){
if(key_pf[i]=='j'){ key_pf[i]=='i';}
for(j=i+1;j<size;)
{if (key_pf[j] == key_pf[i])
 {
for (k = j; k < size; k++) 
 {
  key_pf[k] = key_pf[k + 1]; 
 }
 size--;
 }
else 
j++;
}
}
for(i=0,k=0;i<5;i++)
{ //generate play fair cipher block 5*5
   for(j=0;j<5;j++)
   {
   play[i][j]=key_pf[k];
   k++;
   }
}
for(i=0;i<5;i++){
for(j=0;j<5;j++){ printf(" ");
 putchar(play[i][j]); 
 } 
 printf("\n");
}
}


int myfair(){
int i,choice,flag=0,j,k,size;
printf("\n ~PLAY_FAIR_CIPHER~\n");
printf("Enter Plain Text :");

fgets(txt, 255, stdin );
fgets(txt, 255, stdin );

size=strlen(txt);
int count = 0;
for (i = 0; txt[i]; i++)
if (txt[i] != '*')
txt[count++] = txt[i];
txt[count] = '\0';
for(i=0;i<size;i=i+2)
{
        if(txt[i]==txt[i+1])
        {
            for(j=size;j>i;j--)
            {
                txt[j]=txt[size-1];size--;
            }
            txt[j+1]='x';
        }
}
size=strlen(txt);
if(size%2!=0)
{ 
txt[size]='x'; 
txt[size+1]='\0';
}
printf("\n Plain Text After Removing the space: %s",txt);
printf("\n Message for Encryption is : ");
for(i=0,j=0;txt[i];i++){putchar(txt[i]);
if(i%2!=0){printf(" ");}
}
choice_fill();
}
//playfair end
