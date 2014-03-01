#include<iostream>

int main()
{
    char str[1000], temp[20];
    int top = 0;
    gets(str);
    
    int len = strlen(str);
    int nega = 1;
    int left = 1;
    int c=0,aph=0;
    char target;
    
    for(int i=0; i<len; i++)
    {
        switch(str[i])
        {
            case '+':
                if(top>0)//仓璸计
                {
                    temp[top] = '\0';
                    int num = atoi(temp);
                    top = 0;
                    num*=nega;
                    num*=left;
                    
                    c+=num;
                    //printf("+%d+\n",num); 
                }
                nega = 1;
                break;
            case '-':
                if(top>0)//仓璸计
                {
                    temp[top] = '\0';
                    int num = atoi(temp);
                    top = 0;
                    num*=nega;
                    num*=left;
                    
                    c+=num;
                    //printf("-%d-\n",num); 
                }
                nega = -1;
                break;
            case '=':
                if(top>0)//仓璸计
                {
                    temp[top] = '\0';
                    int num = atoi(temp);
                    top = 0;
                    num*=nega;
                    num*=left;
                    
                    c+=num;
                    //printf("=%d=\n",num);   
                }
                left = -1;
                nega = 1;
                break;
            case 'a'...'z':
                target = str[i];
                if(top==0)//盽计1 
                {
                    int num = 1;
                    num*=nega;
                    num*=left;
                    
                    aph+=num;
                    //printf("aph%daph\n",num); 
                    
                }
                else
                if(top>0)//仓璸计
                {
                    temp[top] = '\0';
                    int num = atoi(temp);
                    top = 0;
                    num*=nega;
                    num*=left;
                    
                    aph+=num;
                    //printf("aph%daph\n",num); 
                    
                }
                break;
            default://计 
                temp[top++] = str[i];
                break;
            
        }
    }
    if(top>0)//仓璸计
    {
        temp[top] = '\0';
        int num = atoi(temp);
        top = 0;
        num*=nega;
        num*=left;
                    
        c+=num;
        //printf("L%dL\n",num);   
    }
        
    //puts(str);
    
    //printf("%d %d\n",c,aph);
    
    printf("%c=%.3lf\n",target,(double)c/aph*(-1));
    
    //system("pause");
}
