#include<stdio.h>
#include<conio.h>
#include<windows.h>
#define clr system("cls");//画面クリア
#define sleep(x) Sleep(x*100);//処理ストップ

void Field(int field[52][52],int x,int y,int kx,int ky,int turn);//フィールド出力

int AI(int field[52][52],int x,int y,int kx,int ky,int turn,int think[2],int combo);//AI

int main()
{
	int combo=5;
	int com[2]={0};
	int think[2][2]={0};
	int x=15,y=15;
	int kx=1,ky=1;
	int tx,ty;
	int look[2]={0};
	
	
	
	//AI作るならこの変数を参照するといいかも
	
	int field[52][52]={0};//-1...壁 0...置かれてない 1...1Pのマス 2...2Pのマス
	
	
	
	
	
	int turn=0;
	int act='\0';
	int i,j,k,l;
	int winner=0;
	int num=0;
	
	
	
	//設定決める
	printf("設定変える?(Noなら0)");
	scanf("%d",&tx);
	if(tx!=0)
	{
		printf("何目並べ?:");
		scanf("%d",&combo);
		printf("横:");
		scanf("%d",&x);
		printf("縦:");
		scanf("%d",&y);
		for(i=0;i<2;i++)
		{
			printf("%dPはCOM?(Noなら0):",i+1);
			scanf("%d",&com[i]);
			if(com[i]!=0)
			{
				printf("攻め度:");
				scanf("%d",&think[i][0]);
				printf("守り度:");
				scanf("%d",&think[i][1]);
				printf("AIの思考見る?(Noなら0):");
				scanf("%d",&look[i]);
			}
		}
	}
	
	
	
	//フィールド作る
	
	for(i=0;i<x+2;i++)
	{
		field[0][i]=-1;
		field[y+1][i]=-1;
	}
	for(i=1;i<=y;i++)
	{
		field[i][0]=-1;
		field[i][x+1]=-1;
	}
	
	
	
	while(winner==0)
	{
		
		
		
		//カーソル移動
		
		if(com[turn]==0)
		{
			while((act!=']' || field[ky][kx]!=0) && tx!=89)
			{
				clr;
				Field(field,x,y,kx,ky,turn);
				act=getch();
				if(act=='w' && field[ky-1][kx]!=-1) ky-=1;
				if(act=='s' && field[ky+1][kx]!=-1) ky+=1;
				if(act=='a' && field[ky][kx-1]!=-1) kx-=1;
				if(act=='d' && field[ky][kx+1]!=-1) kx+=1;
				if(act=='5')
				{
					printf("横何マス目?:");
					scanf("%d",&tx);
					printf("縦何マス目?:");
					scanf("%d",&ty);
					if(field[ty][tx]==0 && ty>0 && ty<=y && tx>0 && tx<=x)
					{
						field[ty][tx]=turn+1;
						act=']';
						tx=89;
					}
					else
					{
						printf("そこには置けません");
						tx=getch();
					}
				}
			}
		}
		
		
		
		//AI
		
		else
		{
			ky=AI(field,x,y,kx,look[turn],turn,think[turn],combo);
			kx=ky%100;
			ky=ky/100;
		}
		
		
		
		//置く
		
		if(com[turn]!=0)
		{
			clr;
			Field(field,x,y,kx,ky,turn);
			printf("AIの置いた座標:(%d,%d)",kx,ky);
			i=getch();
		}
		if(tx!=89) field[ky][kx]=turn+1;
		act='\0';
		tx=0;
		turn=(turn+1)%2;
		num++;
		
		
		
		
		//判定
		
		for(i=1;i<=y && winner==0;i++)
		{
			for(j=1;j<=x && winner==0;j++)
			{
				for(l=0;l<4 && winner==0;l++)
				{
					for(k=1;k<combo && k<89;k++)
					{
						switch(l)
						{
							case 0:
								if(field[i+k][j]!=field[i][j]) k=89;
								break;
							
							case 1:
								if(field[i][j+k]!=field[i][j]) k=89;
								break;
							
							case 2:
								if(field[i+k][j+k]!=field[i][j]) k=89;
								break;
							
							case 3:
								if(field[i+k][j-k]!=field[i][j]) k=89;
								break;
						}
					}
					if(k<89) winner=field[i][j];
				}
			}
		}
		if(num==x*y) winner=3;
		
		
		
	}
	
	
	
	//リザルト
	
	for(k=0;k<combo;k++)
	{
		switch(l-1)
		{
			case 0:
				field[i-1+k][j-1]=winner+2;
				break;
			
			case 1:
				field[i-1][j-1+k]=winner+2;
				break;
			
			case 2:
				field[i-1+k][j-1+k]=winner+2;
				break;
			
			case 3:
				field[i-1+k][j-1-k]=winner+2;
				break;
		}
	}
	clr;
	Field(field,x,y,-1,-1,winner-1);
	if(winner!=3) printf("%dPの勝ち!!\n",winner);
	else		  printf("引き分け\n");
	scanf("%d",&i);
	
	
	return 0;
}



void Field(int field[52][52],int x,int y,int kx,int ky,int turn)//フィールド出力
{
	int i,j;
	
	
	
	//フィールド出力
	
	for(i=0;i<=y+1;i++)
	{
		for(j=0;j<=x+1;j++)
		{
			if(i==ky && j==kx)
			{
				if(field[i][j]==0)
				{
					if(turn==0) printf("★");
					if(turn==1) printf("☆");
				}
				else 			printf("×");
			}
			else
			{
				switch(field[i][j])
				{
					case -1:
						printf("■");
						break;
					
					case 0:
						printf("　");
						break;
					
					case 1:
						printf("●");
						break;
					
					case 2:
						printf("○");
						break;
					
					case 3:
						printf("★");
						break;
					
					case 4:
						printf("☆");
						break;
				}
			}
		}
		puts("");
	}
	printf("%dPのターン w,s,a,d...移動 ]...決定 5...座標(左上が1,1)で決める\n",turn+1);
}





int AI(int field[52][52],int x,int y,int kx,int ky,int turn,int think[2],int combo)//AI
{
	int i,j,k,l,m,n;
	int field2[52][52]={0};
	int max=-1000000;
	int mnum=0;
	int rnum=0;
	int zyuyo=0;
	int ayasi=0;
	int sum=0;
	for(i=1;i<=y;i++)
	{
		for(j=1;j<=x;j++)
		{
			if(field[i][j]==0)
			{
				ayasi=0;
				for(n=0;n<2;n++)
				{
					for(k=0;k<4;k++)
					{
						sum=0;
						zyuyo=0;
						for(l=-1;l<2;l+=2)
						{
							switch(k)
							{
								case 0:
									for(m=1;field[i+m*l][j]==(turn+n)%2+1;m++)
									{
										sum+=1;
									}
									if(field[i+m*l][j]!=0 && think[n]!=0)
									{
										m--;
									}
									break;
								
								case 1:
									for(m=1;field[i][j+m*l]==(turn+n)%2+1;m++)
									{
										sum+=1;
									}
									if(field[i][j+m*l]!=0 && think[n]!=0)
									{
										m--;
									}
									break;
								
								case 2:
									for(m=1;field[i+m*l][j+m*l]==(turn+n)%2+1;m++)
									{
										sum+=1;
									}
									if(field[i+m*l][j+m*l]!=0 && think[n]!=0)
									{
										m--;
									}
									break;
								
								case 3:
									for(m=1;field[i+m*l][j-m*l]==(turn+n)%2+1;m++)
									{
										sum+=1;
									}
									if(field[i+m*l][j-m*l]!=0 && think[n]!=0)
									{
										m--;
									}
									break;
							}
							zyuyo+=m;
						}
						if(zyuyo>=combo-1) ayasi++;
						if(zyuyo>=combo) ayasi+=2;
						if(sum>=combo-1) field2[i][j]+=(50+(10-n*10))*think[n];
						field2[i][j]+=zyuyo*zyuyo*think[n];
					}
				}
				if(ayasi>=2 && n==1)  field2[i][j]+=25*think[n];
				if(i-combo>=0 && i+combo<=y+1 && j-combo>=0 && j+combo<=x+1) field2[i][j]++;
				if(field2[i][j]>max)
				{
					max=field2[i][j];
					mnum=1;
				}
				if(field2[i][j]==max) mnum++;
			}
		}
	}
	
	
	
if(ky!=0)
{
	
	for(n=1;max/n>=10;n++)
	{
	}
	
	clr;
	for(i=0;i<=y+1;i++)
	{
		for(j=0;j<=x+1;j++)
		{
			if(field[i][j]==0) 	printf("%2d",field2[i][j]/n);
			else
			{
				switch(field[i][j])
				{
					case -1:
						printf("■");
						break;
					
					case 1:
						printf("●");
						break;
					
					case 2:
						printf("○");
						break;
				}
			}
		}
		puts("");
	}
	printf("AIの思考 数字が大きいほどそのマスは重要");
	i=getch();
	
}
	
	
	
	
	while(rnum==0)
	{
		for(i=1;i<=y;i++)
		{
			for(j=1;j<=x;j++)
			{
				if(field2[i][j]==max && rand()%mnum==0 && field[i][j]==0) rnum=i*100+j;
			}
		}
	}
	return rnum;
}
