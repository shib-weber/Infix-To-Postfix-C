#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* substring(char* str,int s,int e){
    char * substr = (char*)malloc((e*sizeof(char)));
    strncpy(substr,str+s,e);
    substr[e]='\0';

    return substr;
}
char* postfix(char str[]){
    int l =strlen(str);
    for(int i=0; i < l;i++){
        if(str[i]=='/' || str[i]=='*'){
            char *a =substring(str,0,i);
            char* b =substring(str,i+1,l-1);
            
            if(str[i]=='/'){
                char * c= strcat(postfix(a),postfix(b));
                char * d= strcat(c,"/");
                return(d);
                free(c);
                free(d);
            }else{
                char * c= strcat(postfix(a),postfix(b));
                char * d= strcat(c,"*");
                return(d);
                free(c);
                free(d);
            }
        }
    }
    return str;
}
int main(){
    char str[100];
    printf("Enter an Expression\t");
    scanf("%s",str);
    char* p = postfix(str);
    printf("The post Expression from main is %s",p);
    return 0;
}