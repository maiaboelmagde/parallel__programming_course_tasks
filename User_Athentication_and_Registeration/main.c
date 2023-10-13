#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int project_is_running=1;
    char user_name[20][10];
    char password[20][10];

    //set default existed accounts:
    strcpy(user_name[0],"admin");
    strcpy(password[0],"123");

    strcpy(user_name[1],"admin2");
    strcpy(password[1],"456");

    int indx=2;

    while(project_is_running) {
        puts("Choose your operation :  type 1 to login | 2 for Registration  | 0 to stop running ");
        int operation;
        scanf("%d",&operation);

        if(operation==0) {
            project_is_running=0;
        } else if (operation==1) {
            char check_name[10];
            char check_password[10]="";
            puts("Enter your user name");
            scanf("%s",check_name);
            int check =-1;
            for (int i=0; i<strlen(user_name); i++) {
                if(strcmp(user_name[i],check_name)==0) {
                    check=i;
                }
                if(check==-1) {
                    puts ("This user isn't exist , please register or makesure the user_name is correct");
                } else {
                    while(strcmp(check_password,"0")!=0) {
                        puts("Enter your password , or type 0 to back");
                        scanf("%s",check_password);
                        if (strcmp(check_password,password[check])==0) {
                            puts("you Loged in successfully");
                        } else if (strcmp(check_password,"0")!=0) {
                            puts("that password isn't correct , Try again");
                        }
                    }
                }

            }
        } else if( operation==2) {
            if (indx==20) {
                puts("You entered 20 accounts , this program can't store more than that");
            } else {
                char check_name[10];
                char check_password[10]="";
                int check=0;
                while (!check) {
                    puts("Enter your user name");
                    scanf("%s",check_name);
                    int i=0;
                    for (; i<strlen(user_name); i++) {

                        if(strcmp(user_name[i],check_name)==0) {
                            puts("This User name already exist , enter another one");
                            break;
                        }
                    }
                    if (i==strlen(user_name)) {
                        check=1;
                        puts("Enter your password , or type 0 to back");
                        puts("notice : your password can't be '0'");

                        scanf("%s",check_password);
                        if(strcmp(check_password,"0")!=0) {
                            strcpy(user_name[indx],check_name);
                            strcpy(password[indx],check_password);
                            indx++;
                            puts("Sucessful registration  , your user name and password had saved");
                        }
                    }
                }
            }

        } else {
            puts("invalid input ");
        }

    }
    return 0;
}
