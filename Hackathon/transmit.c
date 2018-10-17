#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structure
typedef struct point{
  int a;
  int b;
  int c;
}Point;

typedef struct user{
  char name[20];
  char pubKey[10];
  char pvtKey[10];
  Point point;
}User;

typedef struct contract{
  char senderPubKey[10];
  char receiverPubKey[10];
  char kindOfPoint;
  int amount;
}Contract;

//Global var
User users[10];
int n;
//Function

void addUser(char* name,char* pubKey,char* pvtKey)
{
  strcpy(users[n].name,name);
  strcpy(users[n].pubKey,pubKey);
  strcpy(users[n].pvtKey,pvtKey);
  users[n].point.a = 0;
  users[n].point.b = 0;
  users[n].point.c = 0;
  n++;
}

Contract createContract(char* sender,char* receiver,char kindOfPoint,int amount)
{
  Contract contract;
  strcpy(contract.senderPubKey,sender);
  strcpy(contract.receiverPubKey,receiver);
  contract.kindOfPoint = kindOfPoint;
  contract.amount = amount;
  return contract;
}
  
int checkSender(Contract contract)
{
  
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(contract.senderPubKey,users[i].pubKey) == 0)
      break;
  }
  if(i<10){
    //Enter user's password
    char pass[10];
    printf("PLEASE enter your password:");
    scanf("%s",pass);
    //check
    if(strcmp(pass,users[i].pvtKey) == 0)
      return 1;
    else {
      printf("Wrong password\n");
      return 0;
    }
  }else
    printf("Cannot find this user\n");
  return 0;
}

int checkBalance(Contract contract){
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(contract.senderPubKey,users[i].pubKey) == 0)
      break;
  }

  //checkBalance
  char kind = contract.kindOfPoint;
  switch(kind){
  case 'a':
    {
      if(users[i].point.a >= contract.amount)
	return 1;
      else return 0;
      break;
    }
  case 'b':
    {
      if(users[i].point.b >= contract.amount)
	return 1;
      else return 0;
      break;
    }
  case 'c':
    {
      if(users[i].point.c >= contract.amount)
	return 1;
      else return 0;
      break;
    }
  default:
    printf("Dont have this point type in Wallet\n");
  }
}

// ADD/MINUS POINT

void addPoint_A(char* pubKey,int amount)
{
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(pubKey,users[i].pubKey) == 0)
      break;
  }
  if(i >= 10){
    printf("Cannot find this user\n");
    return;
  }else{
    users[i].point.a += amount;
  }
}

void addPoint_B(char pubKey[10],int amount)
{
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(pubKey,users[i].pubKey) == 0)
      break;
  }
  if(i >= 10){
    printf("Cannot find this user\n");
    return;
  }else{
    users[i].point.b += amount;
  }
}

void addPoint_C(char pubKey[10],int amount)
{
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(pubKey,users[i].pubKey) == 0)
      break;
  }
  if(i >= 10){
    printf("Cannot find this user\n");
    return;
  }else{
    users[i].point.c += amount;
  }
}

void minusPoint_A(char pubKey[10],int amount)
{
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(pubKey,users[i].pubKey) == 0)
      break;
  }
  if(i >= 10){
    printf("Cannot find this user\n");
    return;
  }else{
    users[i].point.a -= amount;
  }
}

void minusPoint_B(char pubKey[10],int amount)
{
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(pubKey,users[i].pubKey) == 0)
      break;
  }
  if(i >= 10){
    printf("Cannot find this user\n");
    return;
  }else{
    users[i].point.b -= amount;
  }
}

void minusPoint_C(char pubKey[10],int amount)
{
  //find
  int i;
  for(i = 0;i<10;i++){
    if(strcmp(pubKey,users[i].pubKey) == 0)
      break;
  }
  if(i >= 10){
    printf("Cannot find this user\n");
    return;
  }else{
    users[i].point.c -= amount;
  }
}
///////////////////////////////////


void exchange(Contract contract)
{
  //find sender
  int sender,receiver;
  for(sender = 0;sender<10;sender++){
    if(strcmp(contract.senderPubKey,users[sender].pubKey) == 0)
      break;
  }
  //find receiver
  for(receiver = 0;receiver<10;receiver++){
    if(strcmp(contract.senderPubKey,users[receiver].pubKey) == 0)
      break;
  }
  //modify
  char kind = contract.kindOfPoint;
  switch(kind){
  case 'a':
    {
      minusPoint_A(contract.senderPubKey,contract.amount);
      addPoint_A(contract.receiverPubKey,contract.amount);
      break;
    }
  case 'b':
    {
      minusPoint_B(contract.senderPubKey,contract.amount);
      addPoint_B(contract.receiverPubKey,contract.amount);
      break;
    }
  case 'c':
    {
      minusPoint_C(contract.senderPubKey,contract.amount);
      addPoint_C(contract.receiverPubKey,contract.amount);
      break;
    }
  }
}

void transmit(Contract contract)
{
  if(checkSender(contract) == 0){
    return;
  }
  if(checkBalance(contract) == 0)
    return;
  exchange(contract);
}

int main()
{
  n = 0;
  addUser("Dung","zyot249","12345678");
  addUser("gnud","zyot2409","87654321");
  addPoint_A("zyot249",100);
  addPoint_B("zyot249",100);
  addPoint_C("zyot249",100);

  Contract contract1 = createContract("zyot249","zyot2409",'a',40);
  transmit(contract1);
  printf("%d\n",users[0].point.a);
  return 0;
}
