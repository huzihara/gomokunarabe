#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<math.h>
#define clr system("cls");//画面クリア
#define sleep(x) Sleep(x*100);//処理ストップ

void Field(int field[52][52],int x,int y,int kx,int ky,int turn,char key[2][7]);//フィールド出力

int AI(int field[52][52],int x,int y,int kx,int ky,int turn,int think[2],int nolma);//AI

int main()
{
	int nolma=5;
	int com[2]={0,1};
	int think[2][2]={{5,5},{5,5}};
	int x=15,y=15;
	int kx=1,ky=1;
	int tx,ty;
	int look[2]={1,1};
	int field[52][52]={0};//-1...壁 0...置かれてない 1...1Pのマス 2...2Pのマス
	int turn=0;
	int act='\0';
	int i,j,k,l;
	int winner=0;
	int num=0;
	char key[2][7]={{'w','s','a','d','q','e'},{'8','5','4','6','7','9'}};
	
	srand((unsigned int)time(NULL));
	
	
	//設定決める
	while(act!='0')
	{
	
		clr;
		printf("[1]ルール：%d目並べ\n\n",nolma);
		printf("[2]マスの広さ：横%dマス、縦%dマス\n\n",x,y);
		printf("プレイヤー設定\n");
		for(i=0;i<2;i++)
		{
			printf("[%d]%dP：",i+3,i+1);
			if(com[i]==0)
			{
				printf("人間\n");
			}
			else
			{
				printf("コンピュータ(攻め度：%d、守り度：%d、思考：",think[i][0],think[i][1]);
				if(look[i]==1)
				{
					printf("見る)\n");
				}
				else
				{
					printf("見ない)\n");
				}
			}
		}
		printf("\nキーコンフィグ\n");
		printf("＜カーソル移動：上、下、左、右＞＜決定＞＜座標指定＞\n");
		for(i=0;i<2;i++)
		{
			printf("[%d]%dP：　　　　　%c　 %c　 %c　 %c　　  %c　　　　 %c\n",i+5,i+1,key[i][0],key[i][1],key[i][2],key[i][3],key[i][4],key[i][5]);
		}
		printf("\n変更したい項目番号を入力(0でゲームスタート)\n");
		act=getch();
		clr;
		switch(act)
		{
			case '1':
				printf("何目並べ?:");
				scanf("%d",&nolma);
				break;
			case '2':
				printf("横何マス?(50まで):");
				scanf("%d",&x);
				printf("縦何マス?(50まで):");
				scanf("%d",&y);
				break;
			case '3':
				printf("%dPはCOM?(Noなら0):",1);
				scanf("%d",&com[0]);
				if(com[0]!=0)
				{
					printf("攻め度は?:");
					scanf("%d",&think[0][0]);
					printf("守り度は?:");
					scanf("%d",&think[0][1]);
					printf("AIの思考見る?(Noなら0):");
					scanf("%d",&look[0]);
				}
				break;
			case '4':
				printf("%dPはCOM?(Noなら0):",2);
				scanf("%d",&com[1]);
				if(com[1]!=0)
				{
					printf("攻め度は?:");
					scanf("%d",&think[1][0]);
					printf("守り度は?:");
					scanf("%d",&think[1][1]);
					printf("AIの思考見る?(Noなら0):");
					scanf("%d",&look[1]);
				}
				break;
			case '5':
				printf("1Pのキーを<上><下><左><右><決定><座標指定>の順番で連続で入力：");
				scanf("%s",key[0]);
				break;
			case '6':
				printf("2Pのキーを<上><下><左><右><決定><座標指定>の順番で連続で入力：");
				scanf("%s",key[1]);
				break;
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
			while((act!=key[turn][4] || field[ky][kx]!=0) && tx!=89)
			{
				clr;
				Field(field,x,y,kx,ky,turn,key);
				act=getch();
				if(act==key[turn][0] && field[ky-1][kx]!=-1) ky-=1;
				if(act==key[turn][1] && field[ky+1][kx]!=-1) ky+=1;
				if(act==key[turn][2] && field[ky][kx-1]!=-1) kx-=1;
				if(act==key[turn][3] && field[ky][kx+1]!=-1) kx+=1;
				if(act==key[turn][5])
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
		
		
		
		//AIの行動
		
		else
		{
			ky=AI(field,x,y,kx,look[turn],turn,think[turn],nolma);
			kx=ky%100;
			ky=ky/100;
		}
		
		
		
		//置く
		
		if(com[turn]!=0)
		{
			clr;
			Field(field,x,y,kx,ky,turn,key);
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
					for(k=1;k<nolma && k<89;k++)
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
	
	for(k=0;k<nolma;k++)
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
	Field(field,x,y,-1,-1,winner-1,key);
	if(winner!=3) printf("%dPの勝ち!!\n",winner);
	else		  printf("引き分け\n");
	scanf("%d",&i);
	
	
	return 0;
}



void Field(int field[52][52],int x,int y,int kx,int ky,int turn,char key[2][7])//フィールド出力
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
	printf("%dPのターン　%c：上移動、%c：下移動、%c：左移動、%c：右移動%c、決定、%c：座標指定\n",turn+1,key[turn][0],key[turn][1],key[turn][2],key[turn][3],key[turn][4],key[turn][5]);
}




/*AIの思考
・大まかな思考
置けるマスの周りで自分のコマ、相手のコマがそれぞれどのくらい連続しているかを調べて、
それぞれ攻め度、守り度にそって点数を付ける。
全ての置けるマスに点数を付けたら、高い点数のマスを選びそこにコマを置く。
*/

int AI(int field[52][52],int x,int y,int kx,int ky,int turn,int think[2],int nolma)
{
	int i,j,k,l,m,n;
	int field2[52][52]={0};//マスの評価
	int max=-1000000;
	int min=1000000;
	int tmax;
	int fmax;
	int rnum=0;
	int combo=0;
	int ayasi=0;
	int brock=0;
	
	for(i=1;i<=y;i++)//y方向iマス目
	{
		for(j=1;j<=x;j++)//x方向jマス目
		{
			if(field[i][j]==0)//参照しているマスに何も置かれていないなら
			{
				ayasi=0;
				for(n=0;n<2;n++)//n=0:自分、n=1:相手、のコマを見る
				{
					for(k=0;k<4;k++)//縦、横、斜め2つの方向を見る
					{
						combo=2;
						brock=0;
						for(l=-1;l<2;l+=2)//-1と1で見る方向を180度変える
						{
							switch(k)
							{
								case 0://縦
									for(m=1;field[i+m*l][j]==(turn+n)%2+1;m++)//コマの連続が途切れるまで置く候補マスから1マスずつ見る
									{
										combo+=1;
									}
									if(field[i+m*l][j]!=0 && think[n]!=0)//途切れたマスにコマが置いてあったら
									{
										brock++;
									}
									break;
								
								case 1://横
									for(m=1;field[i][j+m*l]==(turn+n)%2+1;m++)
									{
										combo+=1;
									}
									if(field[i][j+m*l]!=0 && think[n]!=0)
									{
										brock++;
									}
									break;
								
								case 2://右下へ伸びる斜め
									for(m=1;field[i+m*l][j+m*l]==(turn+n)%2+1;m++)
									{
										combo+=1;
									}
									if(field[i+m*l][j+m*l]!=0 && think[n]!=0)
									{
										brock++;
									}
									break;
								
								case 3://左下へ伸びる斜め
									for(m=1;field[i+m*l][j-m*l]==(turn+n)%2+1;m++)
									{
										combo+=1;
									}
									if(field[i+m*l][j-m*l]!=0 && think[n]!=0)
									{
										brock++;
									}
									break;
							}
						}
						if(combo-brock>=nolma)//塞がないと詰みなら
						{
							ayasi+=2;
						}
						else if(combo>=nolma-1)//2方向以上に連続していたら塞がないと詰みなら
						{
							ayasi++;
						}
						if(brock>=2 && combo<+1)//両側を塞がれていてリーチもかかっていないなら
						{
							combo=0;
						}
						if(combo>=nolma+1)//コマにリーチがかかっているなら
						{
							field2[i][j]+=2*nolma*think[n];
						}
						field2[i][j]+=combo*think[n];
					}
				}
				if(ayasi>=2)//塞がないと詰みなら
				{
					field2[i][j]+=2*nolma*think[n];
				}
				if(i-nolma>=0 && i+nolma<=y+1 && j-nolma>=0 && j+nolma<=x+1)//壁から離れているなら
				{
					field2[i][j]++;
				}
				if(field2[i][j]>max)//参照しているマスの評価が置けるマスの中で最大なら
				{
					max=field2[i][j];
				}
				if(field2[i][j]<min)//参照しているマスの評価が置けるマスの中で最小なら
				{
					min=field2[i][j];
				}
			}
		}
	}
	
	
	
if(ky!=0)
{
	
	for(n=1;(max-min)/n>=10;n++)//マスの評価を0～9に収めるように割る数をつくる
	{
	}
	
	
	
	//思考表示
	fmax=0;
	clr;
	for(i=0;i<=y+1;i++)
	{
		for(j=0;j<=x+1;j++)
		{
			if(field[i][j]==0)
			{
				if((field2[i][j]-min)/n>fmax)//マスの評価がマスの中で最大値だったら
				{
					fmax=(field2[i][j]-min)/n;
				}
				printf("%2d",(field2[i][j]-min)/n);
			}
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
	
	
	
	tmax=abs(think[0]) > abs(think[1]) ? abs(think[0]) : abs(think[1]);
	while(rnum==0)
	{
		for(i=1;i<=y;i++)
		{
			for(j=1;j<=x;j++)
			{
				if(tmax<10)//思考レベルが10未満のとき
				{
					if(fmax<tmax)
					{
						if((field2[i][j]-min)/n>=fmax && rand()%(x*y)==0 && field[i][j]==0)//マスの評価(0～9)がマスの中で最大値だたら
						{
							rnum=i*100+j;
						}
					}
					if((field2[i][j]-min)/n>=tmax && rand()%(x*y)==0 && field[i][j]==0)//マスの評価(0～9)が思考レベル以上なら
					{
						rnum=i*100+j;
					}
				}
				else//思考レベルが10以上のとき
				{
					if(field2[i][j]==max && rand()%(x*y)==0 && field[i][j]==0)//マスの評価(元々の数値)がマスの中で最大値なら
					{
						rnum=i*100+j;
					}
				}
			}
		}
	}
	return rnum;
}
