/*
 * tokenizer.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*
 * Tokenizer type.  You need to fill in the type as part of your implementation.
 */

struct TokenizerT_ {
  char *str;
  char *type;

};

typedef struct TokenizerT_ TokenizerT;

/*This method is mainly to check if the string inputted into the function is octal 
 and returns 1 if it is octal*/

 int Octal(char *str){
  int i;
  int len = strlen(str);
  int type=1; 
  for(i=1; i<len ;i++){ 
    if(str[i]=='8' || str[i]=='9'){  //to make sure the element is between 0-7
      type=0 ; 
      break; 
    } 
    } 
     if(type==0){
        return 0; 
}
  return 1;
}

/*This method is mainly to check if the string inputted into the function is hexadecimal 
and returns 1 if it is hexadecimal*/

int Hexadecimal(char *str){
  int i;
  int len = strlen(str);
  int type = 0;
  for (i=3; i<len; i++){
    if(isxdigit(str[i])){ //isxdigit check if the current character is a valid hexadecimal digit
      type=1; 
     }
    else{ 
      type =0;
        break;
      }
   }
    if(type==0){
      return 0;
    }
  return 1; 
}

/*This method is mainly to check if the string inputted into the function is of the float type 
and returns 1 if it is float*/

int Float(char *str, int k){
  int len=strlen(str);
  int type=1;
  int i;
  int t=len-1;
  if(str[t]=='.' ||str[t]=='+' ||str[t]=='-'|| str[t]=='e'|| str[t]=='E') //to check last character
    return 0;
  
  for(i=(k+1);i<len;i++){
    if(isdigit(str[i])){
      type=1;
     }
    else if(str[i]=='e' || str[i]=='E'){ //checks if an e if followed by a digit,+,or -
        if(str[i+1]=='+' || str[i+1]=='-'){
         type=1;
         i++;
      }
        else if(isdigit(str[i+1])){
         type=1;
      }
   }
    else{ 
      type=0;
      break;
    }
  }// end of for loop
  if(type==0){
    return 0;
  }
  return 1; 
}//end of the method

/*This method is mainly to check if the string inputted into the function is an integer
and returns 1 if it is integer*/

int Integer(char *str){
  int i;
  int len=strlen(str);
  int type=1;
  int f=0;
  int k; 
  for(k=1;k<len;k++){
    if(str[k] == '.'|| str[k]=='e' || str[k]=='E'){ //checks the subscript that is a . or e
       f=1;
       break;
     }
  }
  if(f==1){
    if(Float(str, k)) // if it has a . or e it sends it to the float method 
      type=2;
    else 
      type =0; 
  }
  else{
  for(i=1; i<len;i++){
    if(isdigit(str[i])==0){
      type=0;
      break;   
    }//end of if statement 
   }//end of for loop
 }
  if(type==0){
    return 0;
  }
  else if(type==2){
    return 2;
  }

  return 1;
}//end of method

/*
 * TKCreate creates a new TokenizerT object for a given token stream
 * (given as a string).
 * 
 * TKCreate should copy the arguments so that it is not dependent on
 * them staying immutable after returning.  (In the future, this may change
 * to increase efficiency.)
 *
 * If the function succeeds, it returns a non-NULL TokenizerT.
 * Else it returns NULL.
 *
 * You need to fill in this function as part of your implementation.
 */

 /* DESCRIPTION: this method checks the type of each token and sends the entire token
 back to the main to be printed */

TokenizerT *TKCreate( char * ts ) {
  TokenizerT* T;
  T = (TokenizerT*)malloc(sizeof(TokenizerT)); // created memory for the tokenizer and the fields in it
  T->str =(char*)malloc(sizeof(char)*strlen(ts));
  T->type =(char*)malloc(sizeof(char)*20);
  strcpy(T->str,ts);  
  char Fchar=ts[0];
  char Schar=T->str[1];
  if(Fchar=='0' && strlen(T->str)==1){
    strcpy(T->type,"Zero");
  }
  else if(Fchar=='0'){//checks if the first character is zero
   if(isdigit(Schar)){ 
       if( Octal(T->str)==0){ // octal check
         strcpy(T->type,"Mal");
        }
        else{
         strcpy(T->type,"octal");
        }
    }//end of octal check
    else if(Schar=='x'|| Schar=='X'){ // hexadecimal check
      if(Hexadecimal(T->str)==0){ 
	        strcpy(T->type,"Mal");
	    }else{
	      strcpy(T->type,"Hexadecimal"); 
     }
    }// end of hexadecimal check
    else if(Schar=='.'){// float check
      if(Float(T->str, 1)==0){ 
        	strcpy(T->type,"Mal");
      }else{
	        strcpy(T->type,"Float");
      }
    }//end of float check 
  
  } //end of the zero check statement

  else if(isdigit(Fchar) && Fchar != '0'){ // check if first character is 1-9 
       if(Integer(T->str)==0){ //send to the integer method
	       strcpy(T->type,"Mal");
      }
       else if(Integer(T->str)==1){
	       strcpy(T->type,"Decimal");
     }    
       else{
         strcpy(T->type,"Float");
     }
}//end of one check statement
 return T; // returning the token
 free (T); //free the memory
}//end of TKCreate



/*
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically
 * allocated memory that is part of the object being destroyed.
 *
 * You need to fill in this function as part of your implementation.
 */

void TKDestroy( TokenizerT * tk ) {
  free (tk->type);
  free (tk->str);
}

/*
 * TKGetNextToken returns the next token from the token stream as a
 * character string.  Space for the returned token should be dynamically
 * allocated.  The caller is responsible for freeing the space once it is
 * no longer needed.
 *
 * If the function succeeds, it returns a C string (delimited by '\0')
 * containing the token.  Else it returns 0.
 *
 * You need to fill in this function as part of your implementation.
 */

char *TKGetNextToken( TokenizerT * tk ) {

  return NULL;
}

/* This method is to output escape characters in hexadecimal form*/

void Error_catch(char c){

        if(c=='n'){
          c='\n';
        }
        else if(c=='t'){
          c='\t';
        }
        else if(c=='\\'){
          c='\\';
        }
        else if(c=='v'){
          c='\v';
        }
        else if(c=='\''){
          c='\'';
        }
        else if(c=='?'){
          c='\?';
        }
        else {
          c=c;
        }
        printf( "Error in Hexadecimal form: [0x%02x]\n", c );
}

/* this method seperates the string into valid tokens */ 
char *Token_Seperator(char *str, int k){
  int i;
  int len = strlen(str);
  char *token=(char*)malloc(sizeof(char)* len);
  int iter=0;
  for (i=k;i<len ; i++){
        if(isxdigit(str[i])|| str[i]=='+'||str[i]=='-'||str[i]=='e'||str[i]=='E'||str[i]=='x'||str[i]=='X'|| str[i]=='.'){
         token[iter++]=str[i];    
    }
    else{
        char c = str[i];
        Error_catch(c);
        return (char*)token;
   }
      if(i==(len-1)){
      return (char*)token;
    }
  }
 return NULL;
}


/*
 * main will have a string argument (in argv[1]).
 * The string argument contains the tokens.
 * Print out the tokens in the second string in left-to-right order.
 * Each token should be printed on a separate line.
 */
 int main(int argc, char **argv){
  int i;
  int len;
  int k;
  TokenizerT* T;
  if(argc<2){
    printf("Error: No tokens have been inputted\n");
    return 0;
  }
  for(i=1; i<argc;i++){
    len = strlen(argv[i]);
    char str[len];
    strcpy(str, argv[i]);
    int l=strlen(str);
    k=0;
    while(k<l){
      char *c = Token_Seperator(str, k);
      int lc=strlen(c);
      int j;
      char *s=(char*)malloc(sizeof(char)* lc);
     if(isdigit(c[0])){
      for(j=0;j<lc;j++){
         if(isxdigit(c[j])){
            s[j]=c[j]; 
         }
         else if(c[j]=='.'){
          s[j]=c[j];
         }
         else if(c[j]=='e'||c[j]=='E'|| c[j]=='+'||c[j]=='-'){
            s[j]=c[j];    
        }
        else if(c[j]=='x'||c[j]=='X'){
          if(isxdigit(c[j+1])){
            s[j]=c[j];
          }
           else 
            break;
          }
       else{
        break;
       }
      } 
    }
    else {
      if(lc>1){
      printf("Error: String doesnt start with a digit");
    }
  }
      T = TKCreate(s);
      TKGetNextToken(T);
      printf("%s\t", T->type); 
      printf("%s\n", s);    
      k=k+lc+1;                                                                                                                                                                              
    }
    TKDestroy(T);
  }     
  return 0;
 } 