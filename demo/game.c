/*THIS CODE IS MY OWN WORK. IT WAS WRITTEN WITHOUT CONSULTING CODE WRITTEN BY OTHER STUDENTS OR ANY ONE WHO IS NOT AWARE OF MY REFERENCE. 409430012�}�W�� 409430001�����*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<conio.h>
#include<windows.h>

#define size 10000
#define width 189 //from 0 to 188 , so 189 bits in a line
#define upperborder 3
#define lowerborder 50
#define border '='
#define height 4
#define y_height 30
#define jump_height 10

#define Sleep(x) Sleep(x/500)

void hidecursor();
void draw(int x,int y,char *ch);
void draw_bg_color_ini(int current_y[],int y[],int *X,int mode);
void setfullscreen();
void setcursor(int x, int y);
void draw_border();
void move_right(char land[],int y[],char current_land[],int current_y[],int *X,int mode);
void move_left(char land[],int y[],char current_land[],int current_y[],int *X,int mode);
void vertical_jump(int *player_pos_y,int *player_pos_x,int *count);
void move_right_boss(int *player_pos_x,int *player_pos_y);
void move_left_boss(int *player_pos_x,int *player_pos_y);
void vertical_jump_boss(int *player_pos_y,int *player_pos_x,int *count);
void draw_player(int *player_pos_y,int *player_pos_x);
void boss_eye(int *boss_eye_x,int boss_eye_y,int player_pos_x);
void boss_attack_1(int *player_pos_x,int *player_pos_y,int *player_blood,int mon_atk);
void boss_attack_2(int *player_pos_x,int *player_pos_y,int mode,int *player_blood,float mon_atk);
void boss_attack_3(int *player_pos_x,int *player_pos_y,int mode,int *player_blood,float mon_atk);

void hidecursor()
{
	CONSOLE_CURSOR_INFO cursor_info = {1, 0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void print(int x, int y, char *ch,WORD color)
{
 DWORD written;
 HANDLE output =GetStdHandle(STD_OUTPUT_HANDLE);
 COORD pos={x,y};//��J�L�X�F�誺�y��
 WORD attribute=color;
 SetConsoleCursorPosition(output,pos);
 WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&attribute,1,pos,&written);

 WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE),ch,1,pos,&written);
}
void draw(int x,int y,char *ch)
{
	DWORD written;
	HANDLE output =GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x,y};
	SetConsoleCursorPosition(output,pos);
	WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE),ch, 1, pos, &written);
}

void setfullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
void draw_bg_color_ini(int current_y[],int y[],int *X,int mode)
{
	for(int i=0;i<width;i++)//�q�C�@��}�l�A�@�浲�����U�@�� i:x j:y;
	{
		for(int j=upperborder+1;j<lowerborder;j++)
		{
			WORD color;
			if(mode==1)
			{
				color=BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			}
			if(mode==2)
			{
				color=BACKGROUND_RED;
			}
			DWORD written;
			COORD pos={i,j};
			WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);

			if(current_y[i]==j)
			{
				for(int k=j;k<lowerborder;k++)
				{
					if(mode==1)
					{
				    	color=BACKGROUND_GREEN;
					}
					if(mode==2)
					{
						color=BACKGROUND_BLUE | BACKGROUND_RED;
					}
					COORD pos={i,k};
					WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
				}
				break;
			}

		}
	}
}

void setcursor(int x,int y)
{
	HANDLE output =GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {x,y};
	SetConsoleCursorPosition(output,pos);
}
void draw_border()
{
	for(int x=0;x<width;x++)
	{
		setcursor(x,upperborder);
		printf("%c",border);
		setcursor(x,lowerborder);
		printf("%c",border);
	}
}
void move_right(char land[],int y[],char current_land[],int current_y[],int *X,int mode)
{
	for(int i=0;i<width;i++)
	{
		if(current_land[i]!=land[*X-width+1+i+1])//compare to the next one
		{
			draw(i,current_y[i]," ");//clean

			current_land[i]=land[*X-width+1+i+1];//update
			current_y[i]=y[*X-width+1+i+1];

			draw(i,current_y[i],&current_land[i]);//draw new

			for(int j=upperborder+1;j<lowerborder;j++)//draw new background color
			{
				WORD color;
				if(mode==1)
				{
			    	color=BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				}
				if(mode==2)
				{
					color=BACKGROUND_RED;
				}
				DWORD written;
				COORD pos={i,j};
				WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);

				if(current_y[i]==j)
				{
					for(int k=j;k<lowerborder;k++)
					{
						if(mode==1)
						{
							color=BACKGROUND_GREEN;
						}
						if(mode==2)
						{
							color=BACKGROUND_BLUE | BACKGROUND_RED;
						}
						COORD pos={i,k};
						WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
					}
					break;
				}
			}
		}
	}
	*X=*X+1;
}
void move_left(char land[],int y[],char current_land[],int current_y[],int *X,int mode)
{
	for(int i=width-1;i>=0;i--)
	{
		if(current_land[i]!=land[*X-width+i])
		{
			draw(i,current_y[i]," ");//clean

			current_land[i]=land[*X-width+i];//update
			current_y[i]=y[*X-width+i];

			draw(i,current_y[i],&current_land[i]);//draw new

			for(int j=upperborder+1;j<lowerborder;j++)//draw new background color
			{
				WORD color;
				if(mode==1)
				{
					color=BACKGROUND_BLUE | BACKGROUND_INTENSITY;
				}
				if(mode==2)
				{
					color=BACKGROUND_RED;
				}
				DWORD written;
				COORD pos={i,j};
				WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);

				if(current_y[i]==j)
				{
					for(int k=j;k<lowerborder;k++)
					{
						if(mode==1)
						{
							color=BACKGROUND_GREEN;
						}
						if(mode==2)
						{
							color=BACKGROUND_BLUE | BACKGROUND_RED;
						}
						COORD pos={i,k};
						WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
					}
					break;
				}
			}
		}
	}
	*X=*X-1;
}
void vertical_jump(int *player_pos_y,int *player_pos_x,int *count)
{
	static int time=0;

	if(*count==jump_height)
	{
		time=25;
	}

		draw(*player_pos_x,*player_pos_y," ");// clean previous position first
		draw(*player_pos_x,*player_pos_y-1," ");

		*player_pos_y=*player_pos_y-1;

		draw(*player_pos_x,*player_pos_y,"O");
		draw(*player_pos_x,*player_pos_y-1,"o");

		*count=*count-1;

		time=1.2*time;
		Sleep(time);
}

void move_right_boss(int *player_pos_x,int *player_pos_y)
{
	draw(*player_pos_x,*player_pos_y," ");
	draw(*player_pos_x,*player_pos_y-1," ");

	*player_pos_x=*player_pos_x+1;

	draw(*player_pos_x,*player_pos_y,"O");
	draw(*player_pos_x,*player_pos_y-1,"o");
}
void move_left_boss(int *player_pos_x,int *player_pos_y)
{
	draw(*player_pos_x,*player_pos_y," ");
	draw(*player_pos_x,*player_pos_y-1," ");

	*player_pos_x=*player_pos_x-1;

	draw(*player_pos_x,*player_pos_y,"O");
	draw(*player_pos_x,*player_pos_y-1,"o");
}

void draw_player(int *player_pos_y,int *player_pos_x)
{
	draw(*player_pos_x,*player_pos_y,"O");
	draw(*player_pos_x,*player_pos_y-1,"o");
}

void boss_eye(int *boss_eye_x,int boss_eye_y,int player_pos_x)
{
	for(int i=89;i<=99;i++)
	{
		DWORD written;
		WORD color=BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;
		COORD pos={i,15};
		WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
	}
	DWORD written;
	WORD color=0;
	COORD pos={player_pos_x,15};
	WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
}

void boss_attack_1(int *player_pos_x,int *player_pos_y,int *player_blood,int mon_atk)
{
	static int x=94;//bullet pos
	static int y=30;
	static int target_x=94;//player pos
	static int target_y=40;
	static float t=0;

	if(y>=41)//bullet target initialization (restart everytime bullet touch the ground)
	{
		draw(x,y," ");//clean the last bullet before restart
		target_x=*player_pos_x;
		target_y=*player_pos_y;
		t=0;
		y=30;
		x=94;
	}

	draw(x,y," ");
	if(*player_pos_x==79||*player_pos_x==109)
	{
		return;
	}
	if(y<=42)//update bullet pos (parametric equation)
	{
		x=94+(target_x-94)*t;
		y=30+(target_y-30)*t;
		if(*player_pos_x==x&&*player_pos_y==y){
            *player_blood-=mon_atk;
		}
		t=t+0.2;
	}
	draw(x,y,"*");
}

void boss_attack_2(int *player_pos_x,int *player_pos_y,int mode,int *player_blood,float mon_atk)
{
	static int x=0;//bullet pos
	static int y=0;
	static int target_x=79;//player pos
	static int target_y=40;
	static float t=0;
	DWORD written;
	WORD color;

	if(y>=41)//bullet target initialization (restart everytime bullet touch the ground)
	{
		y=15;
		t=0;
		while(y<=42)
		{

			x=78+(target_x-78)*t;
			y=15+(target_y-15)*t;
			t=t+0.01;
			if(*player_pos_x==x&&*player_pos_y==y){
                *player_blood-=mon_atk*0.1;
            }
			COORD pos={x,y};
			if(mode==1)
			{
				color=BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			}
			if(mode==2)
			{
				color=BACKGROUND_RED;
			}
			WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
		}
		if(*player_pos_x==78)
			return;
		draw(x,y," ");//clean the last bullet before restart
		target_x=*player_pos_x;
		target_y=*player_pos_y;
		t=0;
		y=30;
		x=94;
	}

	while(y<=42)
	{

		x=78+(target_x-78)*t;
		y=15+(target_y-15)*t;
		t=t+0.01;
		if(*player_pos_x==x&&*player_pos_y==y){
            *player_blood-=mon_atk*0.1;
		}
		COORD pos={x,y};
		color=BACKGROUND_RED | BACKGROUND_GREEN;
		WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
	}
	//if(y<=42)//update bullet pos (parametric equation)
	Sleep(25);
}

void boss_attack_3(int *player_pos_x,int *player_pos_y,int mode,int *player_blood,float mon_atk)
{
	static int x=0;//bullet pos
	static int y=0;
	static int target_x=110;//player pos
	static int target_y=40;
	static float t=0;
	DWORD written;
	WORD color;

	if(y>=41)//bullet target initialization (restart everytime bullet touch the ground)
	{
		y=15;
		t=0;
		while(y<=42)
		{

			x=110+(target_x-110)*t;
			y=15+(target_y-15)*t;
			t=t+0.01;
			if(*player_pos_x==x&&*player_pos_y==y){
                *player_blood-=mon_atk*0.1;
            }
			COORD pos={x,y};
			if(mode==1)
			{
				color=BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			}
			if(mode==2)
			{
				color=BACKGROUND_RED;
			}
			WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
		}
		if(*player_pos_x==110)
			return;
		draw(x,y," ");//clean the last bullet before restart
		target_x=*player_pos_x;
		target_y=*player_pos_y;


		t=0;
		y=30;
		x=94;
	}

	while(y<=42)
	{

		x=110+(target_x-110)*t;
		y=15+(target_y-15)*t;
		t=t+0.01;
		if(*player_pos_x==x&&*player_pos_y==y){
            *player_blood-=mon_atk*0.1;
		}
		COORD pos={x,y};
		color=BACKGROUND_RED | BACKGROUND_GREEN;
		WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
	}
	//if(y<=42)//update bullet pos (parametric equation)
	Sleep(25);
}
void hit_boss(int player_pos_x,int player_pos_y,int *n,int bullet[3][4]){
    if(*n<3){
        bullet[*n][0]=player_pos_x-1;
        bullet[*n][1]=player_pos_y;
        bullet[*n][2]=1;
        bullet[*n][3]=0;        //move times
        *n+=1;
    }
}
void boss_hurt(int *boss_blood,int bullet[3][4],int mode){
    int i;
    for(i=0;i<3;i++){
        if(bullet[i][3]<50){
            bullet[i][1]-=1;
            bullet[i][3]+=1;
            if(mode==1){
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            else{
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED);
            }
       }
       if(bullet[i][0]+bullet[i][1]<=125&&bullet[i][0]-bullet[i][1]>=63){
        bullet[i][3]=50;
            if(bullet[i][2]){
                *boss_blood-=10;
                 bullet[i][2]=0;
            }


       }
    }
    //show boss blood
    for(i=0;i<*boss_blood;i++){
        if(mode==1){
                for(i=0;i<100;i++){
                        print(40+i,5," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                for(i=0;i<*boss_blood;i++){
                        print(40+i,5," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                }
                print(33,5,"b",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                print(34,5,"o",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                print(35,5,"s",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                print(36,5,"s",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
        else{
                for(i=0;i<100;i++){
                        print(40+i,5," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                }
                for(i=0;i<*boss_blood;i++){
                        print(40+i,5," ",BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                    }
                print(33,5,"b", BACKGROUND_RED);
                print(34,5,"o", BACKGROUND_RED);
                print(35,5,"s", BACKGROUND_RED);
                print(36,5,"s", BACKGROUND_RED);
            }
    }
}
void monaction(int x,int mon_clean[2][3],int mon_x[2][3],int mon_y[10000],int mon2_y[3],int mon_atk,int p[2],int *blood,int mon_blood[2][10],int mon_mod[3],int *t,int player_x,int player_y,int mode){


            int i,j,area=10,eye[2],wing=0;
            int x_adj=-90;
            int mon_size=1,x_new,x_new_f;
            int side_y;
            int isatk=0;


            //near atk
            for(j=0;j<3;j++){
            side_y=mon_y[mon_x[0][j]+x_adj]-mon_size-1;
            if(player_x>=mon_clean[0][j]-1&&player_x<=mon_clean[0][j]+3&&player_y>=mon_y[mon_clean[0][j]]-1&&mon_blood[0][j]>0){
                    isatk=1;
                    *blood-=mon_atk;
            }

            if(mode==1){
                    //clean mon1

                for(i=0;i<6;i++){
                    print(mon_clean[0][j]-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    print(mon_clean[0][j]-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    print(mon_clean[0][j]-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size+1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
                //clean mon2

                for(i=0;i<6;i++){
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]-2," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]+1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                }
            }
            else{
                    //clean mon1

                for(i=0;i<6;i++){
                    print(mon_clean[0][j]-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size-1," ", BACKGROUND_RED);
                    print(mon_clean[0][j]-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size," ", BACKGROUND_RED);
                    print(mon_clean[0][j]-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size+1," ", BACKGROUND_RED);
                }
                //clean mon2

                for(i=0;i<6;i++){
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]-2," ", BACKGROUND_RED);
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]-1," ", BACKGROUND_RED);
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]," ", BACKGROUND_RED);
                    print(mon_clean[1][j]-mon_size+i,mon2_y[j]+1," ", BACKGROUND_RED);
                }
            }


    //patrol

        //mon1
          if(p[0]<area*2&&isatk==0){

                if(*t==3){
                    mon_x[0][j]+=1;
                    eye[0]=1;
                    *t=0;
                    Sleep(1);
                }
                else if(*t<3){
                     eye[0]=1;
                    *t+=1;
                }
            }
            else if(p[0]>=area&&isatk==0){

                if(*t==3){
                    mon_x[0][j]-=1;
                    eye[0]=0;
                    *t=0;
                    Sleep(1);
                }
                else if(*t<3){
                     eye[0]=0;
                    *t+=1;
                }

            }
            if(*t==3&&j==0){
                      p[0]+=1;
                    }
            if(p[0]==area*4){
                p[0]=0;
            }

        //mon2
        if(p[1]<area*2&&mon_mod[j]==0){

                if(*t==1){
                    mon_x[1][j]+=1;
                    eye[1]=1;
                    Sleep(1);
                }
                else if(*t<3){
                     eye[1]=1;
                }
            }
        else if(p[1]>=area&&mon_mod[j]==0){

                if(*t==1){
                    mon_x[1][j]-=1;
                    eye[1]=0;
                    Sleep(1);
                }
                else if(*t<3){
                     eye[1]=0;
                }

            }
            if(*t==3&&j==0){
                p[1]+=1;
                    }
            if(p[1]==area*4){
                p[1]=0;
            }
            if(*t==0||*t==1||*t==2){
                wing=1;
            }

        //print mon1
            x_new=mon_x[0][j]-x+93;
                if(mon_blood[0][j]>0){
                    for(i=0;i<6;i++){
                        print(x_new-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size-1," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                        print(x_new-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                        print(x_new-mon_size+i,mon_y[mon_x[0][j]+x_adj]-1-mon_size+1," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                    }
                    if(isatk){
                        print(x_new+eye[0],side_y,"\\",BACKGROUND_RED | BACKGROUND_INTENSITY);   print(x_new+eye[0]+2,side_y,"/",BACKGROUND_RED | BACKGROUND_INTENSITY);
                    }
                    else{
                        print(x_new+eye[0],side_y,"^",BACKGROUND_RED | BACKGROUND_INTENSITY);   print(x_new+eye[0]+2,side_y,"^",BACKGROUND_RED | BACKGROUND_INTENSITY);
                    }
                    print(x_new+1+eye[0],side_y+1,"-",BACKGROUND_RED | BACKGROUND_INTENSITY);
                }


                //print mon2
                x_new_f=mon_x[1][j]-x+93;

                if(mon_blood[1][j]>0){
                        if(mode==1){
                            for(i=0;i<6;i++){
                                print(x_new_f-mon_size+i,mon2_y[j]-1," ",BACKGROUND_RED );
                                print(x_new_f-mon_size+i,mon2_y[j]," ",BACKGROUND_RED );
                                print(x_new_f-mon_size+i,mon2_y[j]+1," ",BACKGROUND_RED );
                            }

                            if(x_new_f==player_x-1){
                                print(x_new_f+eye[1],mon2_y[j],"V",BACKGROUND_RED );   print(x_new_f+eye[1]+2,mon2_y[j],"V",BACKGROUND_RED);
                            }

                            else{
                                print(x_new_f+eye[1],mon2_y[j],"^",BACKGROUND_RED );   print(x_new_f+eye[1]+2,mon2_y[j],"^",BACKGROUND_RED );
                            }
                            print(x_new_f+1+eye[1],mon2_y[j]+1,"-",BACKGROUND_RED );
                        }
                        else{
                            for(i=0;i<6;i++){
                                print(x_new_f-mon_size+i,mon2_y[j]-1," ",BACKGROUND_GREEN );
                                print(x_new_f-mon_size+i,mon2_y[j]," ",BACKGROUND_GREEN );
                                print(x_new_f-mon_size+i,mon2_y[j]+1," ",BACKGROUND_GREEN );
                            }

                            if(x_new_f==player_x-1){
                                print(x_new_f+eye[1],mon2_y[j],"V",BACKGROUND_GREEN );   print(x_new_f+eye[1]+2,mon2_y[j],"V",BACKGROUND_GREEN);
                            }

                            else{
                                print(x_new_f+eye[1],mon2_y[j],"^",BACKGROUND_GREEN );   print(x_new_f+eye[1]+2,mon2_y[j],"^",BACKGROUND_GREEN );
                            }
                            print(x_new_f+1+eye[1],mon2_y[j]+1,"-",BACKGROUND_GREEN );
                        }

                }


                mon_clean[0][j]=x_new;
                mon_clean[1][j]=x_new_f;
        }

}
void attack(char a,int bullet[3][4],int *n,int *mod,int player_pos_x,int player_pos_y,int mode){
    int i,d;
    if(mode==1){
             //left
        if(a=='j'){
            print(player_pos_x-3,player_pos_y-2,"\\",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            print(player_pos_x-2,player_pos_y-1,"\\",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            Sleep(10);
            print(player_pos_x-2,player_pos_y-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            print(player_pos_x-3,player_pos_y-2," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            for(i=0;i<4;i++){
              print(player_pos_x-5,player_pos_y-1,"-",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }

            Sleep(3);
            for(i=0;i<4;i++){
               print(player_pos_x-5,player_pos_y-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }

            print(player_pos_x-2,player_pos_y,"/",BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            Sleep(10);
            print(player_pos_x-2,player_pos_y," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            *mod=2;
        }
        //right
        else if(a=='k'){
            print(player_pos_x+2,player_pos_y-2,"/",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            print(player_pos_x+1,player_pos_y-1,"/",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            Sleep(3);
            print(player_pos_x+2,player_pos_y-2," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            print(player_pos_x+1,player_pos_y-2," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            for(i=0;i<4;i++){
                print(player_pos_x+1+i,player_pos_y-1,"-",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }


            Sleep(3);
            for(i=0;i<4;i++){
                print(player_pos_x+1+i,player_pos_y-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }

            print(player_pos_x+1,player_pos_y,"\\",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            Sleep(3);
            print(player_pos_x+1,player_pos_y," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);

            *mod=1;
        }
    }
    else{
             //left
        if(a=='j'){
            print(player_pos_x-3,player_pos_y-2,"\\", BACKGROUND_RED);
            print(player_pos_x-2,player_pos_y-1,"\\", BACKGROUND_RED);
            Sleep(10);
            print(player_pos_x-2,player_pos_y-1," ", BACKGROUND_RED);
            print(player_pos_x-3,player_pos_y-2," ", BACKGROUND_RED);
            for(i=0;i<4;i++){
              print(player_pos_x-5,player_pos_y-1,"-", BACKGROUND_RED);
            }

            Sleep(3);
            for(i=0;i<4;i++){
               print(player_pos_x-5,player_pos_y-1," ", BACKGROUND_RED);
            }

            print(player_pos_x-2,player_pos_y,"/", BACKGROUND_RED);

            Sleep(10);
            print(player_pos_x-2,player_pos_y," ", BACKGROUND_RED);

            *mod=2;
        }
        //right
        else if(a=='k'){
            print(player_pos_x+2,player_pos_y-2,"/", BACKGROUND_RED);
            print(player_pos_x+1,player_pos_y-1,"/", BACKGROUND_RED);
            Sleep(3);
            print(player_pos_x+2,player_pos_y-2," ", BACKGROUND_RED);
            print(player_pos_x+1,player_pos_y-2," ", BACKGROUND_RED);
            for(i=0;i<4;i++){
                print(player_pos_x+1+i,player_pos_y-1,"-", BACKGROUND_RED);
            }


            Sleep(3);
            for(i=0;i<4;i++){
                print(player_pos_x+1+i,player_pos_y-1," ", BACKGROUND_RED);
            }

            print(player_pos_x+1,player_pos_y,"\\", BACKGROUND_RED);
            Sleep(3);
            print(player_pos_x+1,player_pos_y," ", BACKGROUND_RED);

            *mod=1;
        }
    }

    if(a=='u'&&*n<3){
        bullet[*n][0]=player_pos_x-1;
        bullet[*n][1]=player_pos_y;
        bullet[*n][2]=0;        //direct
        bullet[*n][3]=0;        //move times
        *n+=1;

    }
    else if(a=='i'&&*n<3){
        bullet[*n][0]=player_pos_x+1;
        bullet[*n][1]=player_pos_y;
        bullet[*n][2]=1;      //direct
        bullet[*n][3]=0;      //move times
        *n+=1;

    }

}
void fill_bullet(int bullet[3][4],int *num,int *t,int player_y){
        int i=0;
    //fill bullet
    if(*num==4){
        *t+=1;
        for(i=0;i<*t/20;i++){
                if(i>0){
                    print(52+i*2,1," ", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                }
            }
        if(*t>=80){
        *num=0;
          *t=0;
        }
    }
    //show num of bullet
    if(*num<=3){
        setcursor(48,1);
        printf("�l�u:");
        for(i=0;i<=*num;i++){
                print(60-i*2,1," ",1);
        }
        if(*num==3){
            *num+=1;
        }
    }
}
void hurt(int abs_x[2][3],int x[2][3],int y[],int mod,int blood[2][10],int bullet[][4],int player_pos_x,int player_y,int mode){
    //bullet
    int i,j;//i for bullet,j for mon
    if(mod==0){
        for(i=0;i<2;i++){
            for(j=0;j<3;j++){
            Sleep(1);
          if(abs(y[abs_x[0][j]]-bullet[i][1])<=10&&bullet[i][3]<30){

                        if(abs(bullet[i][0]-x[0][j])<=2&&blood[0][j]){

                                blood[0][j]-=1;
                                Sleep(1);
                                bullet[i][3]=30;
                                Sleep(1);
                                //show blood
                                if(mode==1){
                                   for(i=0;i<blood[0][j]*2;i++){
                                    print(player_pos_x-15+i,10," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                                    }
                                    print(player_pos_x-1,9,"m",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                    print(player_pos_x,9,"o",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                    print(player_pos_x+1,9,"n",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                }
                                else{
                                    for(i=0;i<blood[0][j]*2;i++){
                                    print(player_pos_x-15+i,10," ",BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                    }
                                    print(player_pos_x-1,9,"m", BACKGROUND_RED);
                                    print(player_pos_x,9,"o", BACKGROUND_RED);
                                    print(player_pos_x+1,9,"n", BACKGROUND_RED);
                                }

                        }
                    }
                    if(bullet[i][0]>=x[1][j]-1&&bullet[i][0]<=x[1][j]+1&&bullet[i][1]>=14&&bullet[i][1]<=17&&bullet[i][3]<30&&blood[1][j]){
                                blood[1][j]-=1;
                                bullet[i][3]=30;

                                //show blood
                                if(mode==1){
                                    for(i=0;i<blood[1][j]*2;i++){
                                        print(player_pos_x-15+i,10," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                                    }
                                    print(player_pos_x-1,9,"b",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                    print(player_pos_x,9,"i",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                    print(player_pos_x+1,9,"r",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                    print(player_pos_x+2,9,"d",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                                }
                                else{
                                    for(i=0;i<blood[1][j]*2;i++){
                                        print(player_pos_x-15+i,10," ",BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                                    }
                                    print(player_pos_x-1,9,"b", BACKGROUND_RED);
                                    print(player_pos_x,9,"i", BACKGROUND_RED);
                                    print(player_pos_x+1,9,"r", BACKGROUND_RED);
                                    print(player_pos_x+2,9,"d", BACKGROUND_RED);
                                }

                    }
            }
        }
    }
    //player_right
    else if(mod==1){
            for(j=0;j<3;j++){
                if(x[0][j]-1>player_pos_x&&x[0][j]<player_pos_x+6){
                blood[0][j]-=1;

                if(mode==1){
                       for(i=0;i<blood[1][j]*2;i++){
                            print(player_pos_x-15+i,10," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                            }
                        print(player_pos_x-1,9,"b",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x,9,"i",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x+1,9,"r",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x+2,9,"d",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                else{
                        for(i=0;i<blood[1][j]*2;i++){
                            print(player_pos_x-15+i,10," ",BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                            }
                        print(player_pos_x-1,9,"b", BACKGROUND_RED);
                        print(player_pos_x,9,"i", BACKGROUND_RED);
                        print(player_pos_x+1,9,"r", BACKGROUND_RED);
                        print(player_pos_x+2,9,"d", BACKGROUND_RED);
                    }
            }
        }
    }
    //player_left
    else if(mod==2){
            for(j=0;j<3;j++){
                if(x[0][j]+1<=player_pos_x&&x[0][j]+1>=player_pos_x-6){
                blood[0][j]-=1;
                if(mode==1){
                        for(i=0;i<blood[1][j]*2;i++){
                            print(player_pos_x-15+i,10," ",BACKGROUND_RED | BACKGROUND_INTENSITY);
                            }
                        print(player_pos_x-1,9,"b",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x,9,"i",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x+1,9,"r",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x+2,9,"d",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                else{
                        for(i=0;i<blood[1][j]*2;i++){
                            print(player_pos_x-15+i,10," ",BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                            }
                        print(player_pos_x-1,9,"b", BACKGROUND_RED);
                        print(player_pos_x,9,"i", BACKGROUND_RED);
                        print(player_pos_x+1,9,"r", BACKGROUND_RED);
                        print(player_pos_x+2,9,"d", BACKGROUND_RED);
                    }
            }
        }
    }
}

void player_bullet(int bullet[3][4],int *n,int mode){
    int i;
    for(i=0;i<*n;i++){
       if(bullet[i][3]<30&&bullet[i][2]==1){
            bullet[i][0]+=1;
            bullet[i][3]+=1;
            if(mode==1){
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            else{
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED);
            }

       }
       else if(bullet[i][3]<30&&bullet[i][2]==0){
            bullet[i][0]-=1;
            bullet[i][3]+=1;
            if(mode==1){
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            else{
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED);
            }
       }
    }
}

void bullet_mon(int bullet[3][2],int *player_blood,int player_pos_x,int player_pos_y,int mon_atk,int mode){
    int i;
    for(i=0;i<3;i++){
        if(bullet[i][1]>=10){
            bullet[i][1]+=1;

            if(mode==1){
                print(bullet[i][0],bullet[i][1]-1,"O",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
            }
            else{
                print(bullet[i][0],bullet[i][1]-1,"O", BACKGROUND_RED);
                Sleep(10);
                print(bullet[i][0],bullet[i][1]-1," ", BACKGROUND_RED);
            }
        }


      //if player get hurt
        if(bullet[i][0]==player_pos_x&&bullet[i][1]>=player_pos_y-1){
            *player_blood-=mon_atk*2;//1 may replace by mon_atk
            bullet[i][1]=0;
        }
        //ensure bullet stop
        if(bullet[i][1]>=player_pos_y){
            bullet[i][1]=0;
        }
    }
}
void mon_throw(int mon_x[2][3],int mon_clean[2][3],int start[3],int mon2_y[3],int y[10000],int player_x,int player_y,int mon_bullet[3][2],int mon_blood[2][10],int mon_mod[3]){
    int i,d;
    for(i=0;i<3;i++){
        //mod judge
       if(mon_clean[1][i]==player_x&&mon_mod[i]==0){
            mon_mod[i]=1;
            start[i]=mon_x[1][i];
       }
       if(abs(mon_x[1][i]-start[i])>=5&&mon_mod[i]==1){
            mon_mod[i]=2;
       }
       if(mon_x[1][i]==start[i]&&mon_mod[i]==2){
        mon_mod[i]=0;
       }
    //action for mod(mod 0 not here)
        //mod1 follow player and atk
       if(mon_mod[i]==1&&mon_blood[1][i]){
        mon_x[1][i]+=player_x-mon_clean[1][i]-1;
            if(mon_bullet[i][1]>=player_y||mon_bullet[i][1]==0){
                mon_bullet[i][0]=mon_clean[1][i]+1;
                mon_bullet[i][1]=15;
            }
       }
       //mod2 go back
       if(mon_mod[i]==2){
        d=start[i]-mon_x[1][i];
        //unit vector
        d=d/abs(d);
        mon_x[1][i]+=d;
       }
       //continue to patrol after arrive start place
       if(mon_mod[i]==2&&mon_x[1][i]==start[i]){
        mon_mod[i]=0;
       }

    }
}
void show_player_blood(int player_blood){
    int i;
    player_blood/=2;
    //clean
    for(i=0;i<25;i++){
          print(7+i,1," ",BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN);
    }
    //print
    setcursor(1,1);
    printf("��q:");
    for(i=0;i<player_blood;i++){
        print(7+i,1," ",BACKGROUND_RED|BACKGROUND_INTENSITY);
    }
}
void end(int i,float clock){
    char c;
    int j;
    if(i==0){
        system("cls");

        //big word
        for(j=0;j<30;j++){
            printf("\n");
        }
        for(j=0;j<60;j++){
            printf(" ");
        }
        printf("------       /\\      |\\    /|   ----      -----  \\        /  ----  -----");

        printf("\n");
        for(j=0;j<60;j++){
            printf(" ");
        }
        printf("|           /  \\     | \\  / |  |          |   |   \\      /  |      |    |");

        printf("\n");
        for(j=0;j<60;j++){
            printf(" ");
        }
        printf("|   ---    /____\\    |  \\/  |  |----      |   |    \\    /   |----  |____|");

        printf("\n");
        for(j=0;j<60;j++){
            printf(" ");
        }
        printf("|     |   /      \\   |      |  |          |   |     \\  /    |      | \\");

        printf("\n");
        for(j=0;j<60;j++){
            printf(" ");
        }
        printf("------|  /        \\  |      |  |----      -----      \\/     |----  |  \\");
        for(j=0;j<18;j++){
           printf("\n");
        }
        setcursor(90,37);
        game_time(&clock);

        Sleep(5000);
        setcursor(80,50);
        printf("click anything to continue");

        c=getch();
        Sleep(100);
        system("cls");
        return;
    }
    else if(i==1){
        system("cls");
        //big word
        for(j=0;j<29;j++){
            printf("\n");
        }
        for(j=0;j<70;j++){
            printf(" ");
        }
        printf("\\   /  -----  |   |     |   |    |  -----  |\\     |");

        printf("\n");
        for(j=0;j<70;j++){
            printf(" ");
        }
        printf(" \\ /   |   |  |   |     |   |    |    |    | \\    |");

        printf("\n");
        for(j=0;j<70;j++){
            printf(" ");
        }
        printf("  |    |   |  |   |     |   |    |    |    |  \\   |");

        printf("\n");
        for(j=0;j<70;j++){
            printf(" ");
        }
        printf("  |    |   |  \\  /       \\  /\\  /     |    |   \\  |");

        printf("\n");
        for(j=0;j<70;j++){
            printf(" ");
        }
        printf("  |    -----   \\/         \\/  \\/    -----  |     \\|");
        for(j=0;j<18;j++){
           printf("\n");
        }
        setcursor(90,37);
        game_time(&clock);

        Sleep(5000);
        setcursor(80,50);
        printf("click anything to continue");

        c=getch();
        Sleep(100);
        system("cls");
        return;
    }
}
void game_time(int *clock1){
    int clock2;
    int m,s;
    int i;
    char c;
        //clock1

        if(*clock1==0){
            Sleep(1000);
            *clock1=clock()/CLOCKS_PER_SEC;
        }
        //clock2
        else{
           clock2=clock()/CLOCKS_PER_SEC;
            clock2-=*clock1;
            clock2+=1;
            m=clock2/60;
            s=clock2-m*60;

            printf("%04d m %02d s\n",m,s);
            Sleep(100);
        }
        //print

    return 0;
}

int main()
{
	srand(time(NULL));
	SetConsoleTitle("�����C���M�D");
	char S; // detect commands
	FILE *f_stage;
	int player_pos_y =29;
	int player_pos_x =94;//half of the width
	char land[size]={0};
	int y[size]={0};
	char current_land[width]={0};
	int current_y[width]={0};
	int x=width-1; // let x be the "current_land" left most x coordinate in "land"
	int flag_ini=0;
	int lock_r=0;
	int lock_l=0;
	int lock_u=0;
	int count=0; // TESTING
	int ACTIVATED=0;
	float land_time=0;
	int mode=2;
	int option1=0;
	int option2=0;
	int temp=0;// 'q','p'
	int trigger_boss=0;
	int boss_eye_x=0;
	int boss_eye_y=0;

	int bullet[3][4],mon_bullet[3][2]={0};
	int num_bullet=4;
	int mod=0;
	int mon_x[2][3],mon2_y[3];

    int p[2]={0},t_fill=80,t_fill_mon;
    int mon_clean[2][3];
    int mon_blood[2][10]={0},boss_blood=100;
    int mon_atk=1;
    int mon_move=0;
    int start[3],mon_mod[3]={0};

    int player_blood=500;
    int kill;
    int i;

    float clock1=0;

    p[1]=5;
    //mon location
    mon_x[0][0]=194;mon_x[0][2]=445;
    mon2_y[0]=15;mon2_y[1]=15;mon2_y[2]=15;
    mon_x[1][0]=225; mon_x[1][1]=314;mon_x[1][2]=427;
    //initial mon blood
     for(int i=0;i<10;i++){
            mon_blood[0][i]=1;
            mon_blood[1][i]=1;
    }

	setfullscreen();
	f_stage=fopen("stage1.txt","r");

	for(int i=0;i<size;i++)//land initialization
	{
		fscanf(f_stage,"%c",&land[i]);
	}
	for(int i=0;i<size;i++)//y coordinates initialization
	{
		if(land[i]=='\\')
		{
			y[i]=y[i-1]+height;
			flag_ini=1;
		}
		if(land[i]=='/')
		{
			y[i]=y[i-1]-height;
			flag_ini=1;
		}
		if(land[i]=='-')
		{
			if(flag_ini==1)
			{
				y[i]=y[i-1];
				continue;
			}
			y[i]=y_height;
		}
		if(land[i]=='<')
		{
			y[i]=y[i-1]+height*3;
		}
		if(land[i]=='>')
		{
			y[i]=y[i-1]-height*3;
		}
		if(land[i]=='U')
		{
			y[i]=y[i-1];
			trigger_boss=i;
		}
		if(land[i]=='A')
		{
			y[i]=y[i-1];
		}
		if(land[i]=='q')
		{
			temp=y[i-1];
			y[i]=lowerborder-1;
		}
		if(land[i]=='p')
		{
			y[i]=temp;
		}
	}
	for(int i=0;i<width;i++)//current initialization
	{
		current_land[i]=land[i];
		current_y[i]=y[i];
	}

/////////////////////////////////////////////////////////////////////////////////////
	while(1)//menu
	{
		hidecursor();
		if(option1==0)
		{
			setcursor(92,26);
			printf("START");
			setcursor(92,29);
			printf("quit");
		}
		else
		{
			setcursor(92,26);
			printf("start");
			setcursor(92,29);
			printf("QUIT");
		}
		S=0;
		if(kbhit())
		{
			S=getch();
		}
		if(S=='s'||S=='S'||S=='w'||S=='W')
		{
			option1=!option1;
		}
		if(option1==0&&S=='\r')
		{
		    clock1=0;
			setcursor(92,26);
			printf("     ");
			setcursor(92,29);
			printf("    ");
			while(1)
			{
				hidecursor();
				if(option2==0)
				{
					setcursor(87,28);
					printf("EASY");
					setcursor(95,28);
					printf("hard");
				}
				else
				{
					setcursor(87,28);
					printf("easy");
					setcursor(95,28);
					printf("HARD");
				}
				S=0;
				if(kbhit())
				{
					S=getch();
				}
				if(S=='a'||S=='A'||S=='d'||S=='D')
				{
					option2=!option2;
				}
				if(option2==0&&S=='\r')
				{
					mode=1;
					mon_atk*=mode;
					break;
				}
				if(option2==1&&S=='\r')
				{
					mode=2;
					mon_atk*=mode;
					break;
				}
				if(S=='\b')
				{
					break;
				}
			}
			setcursor(87,28);
			printf("    ");
			setcursor(95,28);
			printf("    ");
			if(S!='\b')
			{
				break;
			}
		}
		if(option1==1&&S=='\r')
		{
			setcursor(92,26);
			printf("     ");
			setcursor(92,29);
			printf("    ");
			return 0;
		}
	}
///////////////////////////////////////////////////////////////////////////////////////
	draw_border();
	for(int i=0;i<width;i++)
	{
		draw(i,current_y[i],&current_land[i]);
	}
	draw_bg_color_ini(current_y,y,&x,mode);
	game_time(&clock1);
	while(1)//start game
	{
		S=0;



	    monaction(x,mon_clean,mon_x,y,mon2_y,mon_atk,p,&player_blood,mon_blood,mon_mod,&mon_move,player_pos_x,player_pos_y,mode);
	    fill_bullet(bullet,&num_bullet,&t_fill,player_pos_y);
	    mon_throw(mon_x,mon_clean,start,mon2_y,y,player_pos_x,player_pos_y,mon_bullet,mon_blood,mon_mod);
	    bullet_mon(mon_bullet,&player_blood,player_pos_x,player_pos_y,mon_atk,mode);
	    show_player_blood(player_blood);
	    if(mod==1||mod==2){
                hurt(mon_x,mon_clean,y,mod,mon_blood,bullet,player_pos_x,player_pos_y,mode);
                mod=0;
        }
        player_bullet(bullet,&num_bullet,mode);
        hurt(mon_x,mon_clean,y,mod,mon_blood,bullet,player_pos_x,player_pos_y,mode);
		draw_player(&player_pos_y,&player_pos_x);
		hidecursor();
		//player will die if fall into the hole
		if(player_pos_y>=45){
            player_blood-=20;
		}
		//die
        if(player_blood<=0){
            end(0,clock1);
            game_time(&clock1);
            main();
        }
        //check num of kill
        kill=0;
        for(i=0;i<2;i++){
            for(int j=0;j<3;j++){
                if(mon_blood[i][j]<=0){
                    kill++;
                }

            }
        }
        //should kill all mon before boss fight
        if(kill<5&&x>=480){
            move_left(land,y,current_land,current_y,&x,mode);
        }

		if(kbhit())
		{
			S=getch();
			//clean the bar of mon-blood
			for(i=0;i<30;i++){
                    if(mode==1){
                        print(player_pos_x-15+i,9," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                        print(player_pos_x-15+i,10," ",BACKGROUND_BLUE | BACKGROUND_INTENSITY);
                    }
                    else{
                        print(player_pos_x-15+i,9," ", BACKGROUND_RED);
                        print(player_pos_x-15+i,10," ", BACKGROUND_RED);
                    }

                            }
		}
		lock_r=0; // not allow to move when facing wall
		lock_l=0;
		if(player_pos_y>current_y[player_pos_x+1]-1)
		{
			lock_r=1;
		}
		if(player_pos_y>current_y[player_pos_x-1]-1)
		{
			lock_l=1;
		}

		if((S=='d'||S=='D')&&lock_r!=1)
		{
			move_right(land,y,current_land,current_y,&x,mode);
		}

		if((S=='a'||S=='A')&&lock_l!=1)
		{
			move_left(land,y,current_land,current_y,&x,mode);
		}

		if(player_pos_y==current_y[player_pos_x]-1)
		{
			lock_u=0;
		}
		if((S=='w'||S=='W'||ACTIVATED==1)&&lock_u==0)
		{
			if((S=='w'||S=='W')&&count==0)
			{
				count=jump_height;
			}
			ACTIVATED=1;
			vertical_jump(&player_pos_y,&player_pos_x,&count);
			if(count==0)
			{
				ACTIVATED=0;
			}
		}
		//to atk
		if(S=='j'||S=='k'||S=='u'||S=='i'){
                attack(S,bullet,&num_bullet,&mod,player_pos_x,player_pos_y,mode);
            }
        player_bullet(bullet,&num_bullet,mode);
        hurt(mon_x,mon_clean,y,mod,mon_blood,bullet,player_pos_x,player_pos_y,mode);
		/* check if y change when falling */
		if(ACTIVATED==1)
		{
			land_time=50;
		}
		if((player_pos_y<y[x-width/2]-1)&&ACTIVATED==0)
		{
			lock_u=1;
			land_time=land_time/1.1;
			Sleep(land_time);

			draw(player_pos_x,player_pos_y," ");
			draw(player_pos_x,player_pos_y-1," ");

			player_pos_y=player_pos_y+1;

			draw(player_pos_x,player_pos_y,"O");
			draw(player_pos_x,player_pos_y-1,"o");

			if(player_pos_y==current_y[player_pos_x]-1)
			{
				lock_u=0;
			}
		}

		if((x-width/2)==trigger_boss)//execute boss fight
		{
			player_pos_x=94;

			int i=94,j,k=0,temp=94;//draw boss
			for(j=30;j>6;j--)
			{
				for(i=temp;i<=temp+2*k;i++)
				{
					WORD color;
					color=BACKGROUND_RED | BACKGROUND_INTENSITY;;
					DWORD written;
					COORD pos={i,j};
					WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);

					if(((i==79||i==109)&&j==15)||((i==79||i==109||i==110||i==78)&&j==14))
					{
						color=BACKGROUND_RED | BACKGROUND_BLUE ;
						WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
					}

					if((i>=89&&i<=99)&&j==15)
					{
						color=BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
						WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
						if(i==94)
						{
							color=0;
							WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&color, 1, pos, &written);
							boss_eye_x=i;
							boss_eye_y=j;
						}


					}
				}
				temp--;
				k++;
				Sleep(100);
			}

			while(1)//boss fight
			{
			    //die
                if(player_blood<=0){
                    end(0,clock1);
                    game_time(&clock1);
                    main();
                }
                //win
                if(boss_blood<=0){
                    end(1,clock1);
                    game_time(&clock1);
                    main();
                }
                fill_bullet(bullet,&num_bullet,&t_fill,player_pos_y);
			    show_player_blood(player_blood);
			    boss_hurt(&boss_blood,bullet,mode);
				if(abs(player_pos_x-94)<=5)
					boss_eye(&boss_eye_x,boss_eye_y,player_pos_x);

				//f(player_pos_x>78&&player_pos_x<110)

				if(player_pos_x>78&&player_pos_x<110)
				{
					boss_attack_1(&player_pos_x,&player_pos_y,&player_blood,mon_atk);
				}
				Sleep(50);

				if(rand()%5==1&&player_pos_x<=78||player_pos_x==78)
				{
					boss_attack_2(&player_pos_x,&player_pos_y,mode,&player_blood,mon_atk);
				}
				if(rand()%5==1&&player_pos_x>=110||player_pos_x==110)
				{
					boss_attack_3(&player_pos_x,&player_pos_y,mode,&player_blood,mon_atk);
				}

				S=0;
				draw_player(&player_pos_y,&player_pos_x);
				hidecursor();
				if(kbhit())
				{
			    	S=getch();
				}
				lock_r=0; // not allow to move when facing wall
				lock_l=0;
				if(player_pos_y>current_y[player_pos_x+1]-1)
				{
					lock_r=1;
				}
				if(player_pos_y>current_y[player_pos_x-1]-1)
				{
					lock_l=1;
				}

				if((S=='d'||S=='D')&&lock_r!=1)
				{
					move_right_boss(&player_pos_x,&player_pos_y);
				}

				if((S=='a'||S=='A')&&lock_l!=1)
				{
					move_left_boss(&player_pos_x,&player_pos_y);
				}

				if((S=='w'||S=='W'||ACTIVATED==1)&&lock_u==0)
				{
					if((S=='w'||S=='W')&&count==0)
					{
						count=jump_height;
					}
					ACTIVATED=1;
					vertical_jump(&player_pos_y,&player_pos_x,&count);
					if(count==0)
					{
						ACTIVATED=0;
					}
				}
                if(S=='j'||S=='J'){
                    hit_boss(player_pos_x,player_pos_y,&num_bullet,bullet);
                }
				/* check if y change when falling */
				if(ACTIVATED==1)
				{
					land_time=50;
				}
				if((player_pos_y<y[x-width/2]-1)&&ACTIVATED==0)
				{
					lock_u=1;
					land_time=land_time/1.1;
					Sleep(land_time);

					draw(player_pos_x,player_pos_y," ");
					draw(player_pos_x,player_pos_y-1," ");

					player_pos_y=player_pos_y+1;
					if(player_pos_y==current_y[player_pos_x]-1)
					{
						lock_u=0;
					}
					draw(player_pos_x,player_pos_y,"O");
					draw(player_pos_x,player_pos_y-1,"o");
				}
			}
		}
	}
}
