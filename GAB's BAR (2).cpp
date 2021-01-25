#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <string.h>
FILE *fp;
text_info vActual = {0, 0, 79, 24, WHITE, WHITE, C80, 25, 80, 1, 1};
struct stcad{
	char nome [20], email[50],nick[10], excluido;
	int idade, cod;
		struct stquiz{
			int scoreg, scoref,scorec;
		}pontos;
}cad;
int aux;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void menu();
void masc();
void sobre();
void deleta();
void bar();
void saida();
void Consulta();
void tabela();
void margem();
void margem2();
void game();
void FL();
void load();
void textcolor();
void textbackground();
void filmes();
void jogos();
void conhecimentos();
void controle ();
void iluminat();
void harry();
void fquiz();
void gotoxy(int x, int y);
void cursor (int x);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void salvar_dados()
{ 
	char conf;
	gotoxy(20,10);printf("Confirma os dados para gravacao ? (S/N): ");
	//
	do{
	   gotoxy(30,22); 
	   conf = getche();
	}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N' );
    //
	if( conf == 's' || conf == 'S' )
   	{
		if(fwrite(&cad, sizeof(cad), 1, fp) != 1) 
		{
		    gotoxy(18,11);printf("Erro na escrita do arquivo");
		}
		else
		{
			fflush( fp );//descarrega o buffer no disco
			system("cls");gotoxy(25,10);printf("Dados salvos com sucesso!",23);
			Sleep(1000);
			masc();		
		}	
	}
}
void abrir_arquivo(const char modo[3])
{
	if((fp = fopen("dados.bin",modo)) == NULL) 
	{
		gotoxy(18,11);printf("Erro na abertura do arquivo");
	    exit(1);
	}	
}
void mostra_dados()
{
	gotoxy(18,6);printf("%d",cad.cod);
	gotoxy(18,8);puts(cad.nome);
	gotoxy(18,10);printf("%s",cad.email);
	gotoxy(18,12);printf("%d",cad.idade);
	gotoxy(19,7);printf("%s",cad.nick);
}
void alterar()
{
	textcolor(0);
	system("cls");
	abrir_arquivo("rb+");
	int aux_codigo,F, c, a=5;
	stcad cad_aux;
	long fposicao;
	char conf,ano[4];
	do{
			bar();
			gotoxy(43,8);printf("_____________ALTERAR______________");		
			gotoxy(43,9);printf("C¢digo a ser alterado:");
			gotoxy(43,11);printf("NOME:");
			gotoxy(43,13);printf("E-MAIL:");
			gotoxy(43,15);printf("IDADE:");
			gotoxy(43,17);printf("NICK:");
			gotoxy(43,18);printf("_________________________________");
			gotoxy(65,9);scanf("%d", &aux_codigo);
			if(aux_codigo==0)
			{
			break;
			}
			
			
		F = 0;
		do
	    {
			fread( &cad,sizeof(cad),1,fp);
			if ( cad.cod == aux_codigo)//SOMENTE SE NÃO FOI EXCLUIDO	
			{
		   		F = 1;
		   		fposicao = ftell(fp); //guarda a posição do registro atual do arquivo	
				gotoxy(48,11);puts(cad.nome);
				gotoxy(50,13);printf("%s",cad.email);
				gotoxy(49,15);printf("%d",cad.idade);
				gotoxy(48,17);printf("%s",cad.nick);
		   		cad_aux = cad;
		   		
		   		fflush(stdin);
		   		gotoxy(48,11);gets(cad.nome);
				fflush(stdin);
				gotoxy(50,13);gets(cad.email);
				gotoxy(49,15);gets(ano);
				gotoxy(48,17);gets(cad.nick);
				fflush(stdin);
		
				if(ano[0] != '\x0'){
					cad.idade = atoi(ano);
				}
				if (cad.nome[0] == '\x0')
				    strcpy(cad.nome, cad_aux.nome);
				if (cad.nick[0] == '\0')
				    strcpy(cad.nick, cad_aux.nick);
				if (ano[0] == '\0')
				    cad.idade = cad_aux.idade;
				if (cad.email[0] == '\x0')
				    strcpy(cad.email, cad_aux.email);
				gotoxy(49,19); printf("Confirma alteracao ? (S/N): ");
				do{
			    	gotoxy(76,19); conf = getche();
			   	}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N' );
			   	
			   	if( conf == 's' || conf == 'S' ){
					fseek (fp,fposicao-(sizeof(cad)),SEEK_SET);
					fwrite (&cad,sizeof(cad),1,fp);
					fflush (fp);
					}
		   	}
		   	else
		   	{
		   		gotoxy(65,9);printf("NAO ENCONTRADO");Sleep(300);
			   }
		   		
		}while ((!F) && (!feof(fp)));
		if (F == 0){
			gotoxy(65,9);printf("NAO ENCONTRADO");
		}
	
	}while(aux_codigo != 0 || c!=27 );
	system("cls");
	bar();
	
}

int chave(int cod)
{
	int auxcodigo, F;
	rewind(fp); //reposiciona o ponteiro no início do arquivo
	do{
		F=0;
		fflush(stdin);
		gotoxy(50,10);scanf("%d",&auxcodigo);
		while( ( fread( &cad,sizeof(cad),1,fp) == 1 )&& cad.cod != auxcodigo );
	  if( cad.cod == auxcodigo)

		{
		gotoxy(50,10);printf("codigo ja cadastrado");
		Sleep(500);
		gotoxy(50,10);printf("                    "); 
		F=1;
		}
		}while(F==1);
 
		return auxcodigo;
	}
void login(){
	int ponto;
	char conf;
	long fposicao;
	//cad.pontos.scoreg+=ponto;
	int codi;
	char nicks[50];
	system("color 70");
	bar();
	abrir_arquivo("rb+");
	
	do
	{
		gotoxy(43,9); printf("_______________LOGIN______________");
		gotoxy(43,10);printf("CODIGO:");
		gotoxy(43,12);printf("NICK:");
		gotoxy(43,13);printf("__________________________________");
		gotoxy(50,10);scanf("%d",&codi);	
		fread( &cad,sizeof(cad),1,fp);
		if(codi==0)
		{
			system("cls");
			break;
		}
		if ( cad.cod == codi || cad.excluido == 'n')
		{
			gotoxy(48,12);
			printf("%s",cad.nick);
			Sleep(2000);
		}
					fseek (fp,fposicao-(sizeof(cad)),SEEK_SET);
					fwrite (&cad,sizeof(cad),1,fp);
					fflush (fp);		
	}while(codi!=cad.cod && nicks != cad.nick);
}
main()
{
	system("mode con:cols=120 lines=30");
	SetConsoleTitle("GAB'S BAR ! ! ! ! ! ! ! ! !");
	FL();
	system("cls");
	system("color 70");
	menu();
}
void menu()
{	
	system("cls");
	system("color 70");
	int m=10;
	int n;
	int sair;
	sair=1;
	bar();
	do
	{	
		textcolor(0);
		gotoxy(45,9);printf("____________MAIN____________");
		gotoxy(45,10);printf("JOGAR");
		gotoxy(45,12);printf("CADASTRAR");
		gotoxy(45,14);printf("REGISTROS");
		gotoxy(45,16);printf("SOBRE");
		gotoxy(45,18);printf("SAIR");
		gotoxy(45,19);printf("_____________________________");
		gotoxy(43,m); printf("->");
		n=getch();
		switch(n)
	  	 {
			case 72 : 
			gotoxy(43,m);printf("  ");
			m-=2;
			if(m<10)
			{  
		    m=18;	
			}
			gotoxy(45,m); printf("->");
			break;
			case 80 : 
			 gotoxy(43,m);printf("  ");
			 m+=2;
			if( m>18)
			{
			m=10;
			}
			gotoxy(45, m); printf("->");
			break;
		}cursor(1);
			 sair=1;
			if(n==13)
			{
				if(m==10)
				{
					system("cls");				
					game();		
				}
				if(m==12)
				{
					system("cls");
					masc();
				}
				if(m==14)
				{
					system ("cls");
					Consulta();	
				}
				if(m==16)
				{
					system("cls");
					sobre();
				}
				if(m==18)
				{
					system("cls");
					saida();
					system("cls");
					gotoxy(20,10);printf("O B R I G A D O   P O R   U T I L I Z A R !!!");
					Sleep(3000);
					system("cls");
					exit(1);
				}
			}
	}while(sair);cursor(1);	
}
void game(){
	int a1=9, c2;
	system("cls");
	system("color 70");
	//load();
	bar();
	gotoxy(45,8);printf("____________GAME____________");
	gotoxy(45,9);printf("[ ]JOGOS");
	gotoxy(45,11);printf("[ ]FILMES");
	gotoxy(45,13);printf("[ ]CONHECIMENTOS GERAIS");
	gotoxy(45,14);printf("____________________________");
	do{
	gotoxy(46,a1); printf("X");
	c2=getch();
	gotoxy(46,a1); printf(" ");
		switch(c2)
		{
			case 72 : 
				a1-=2;	
				if(a1<9)
				{
					a1=13;	
				}
					gotoxy(46,a1); printf("X");
				break;
			case 80 : 
				a1+=2;
				if(a1>13)
				{
					a1=9;
				}
					gotoxy(46,a1); printf("X");
				break;
		}
		if(c2==13)
		{
			if(a1==9)
			{
				system("cls");
				controle();
				Sleep(1000);
				jogos();
			}
			if(a1==11)
			{
				system("cls");
				harry();
				Sleep(3000);
				system("cls");
				filmes();
			}
			if(a1==13)
			{
				system("cls");
				iluminat();
				Sleep(3000);//
				conhecimentos();	
			}	
		}
	}while(c2!=27);
	system("cls");bar();	
}
void textcolor(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0xf0) | newcolor);
   vActual.attribute = (csbi.wAttributes & 0xf0) | newcolor;
}
void textbackground(int newcolor)
{
   CONSOLE_SCREEN_BUFFER_INFO csbi;

   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
      (csbi.wAttributes & 0x0f) | (newcolor << 4));
   vActual.attribute = (csbi.wAttributes & 0x0f) | (newcolor << 4);
}
void conhecimentos()
{
	int score3=0, f=0;
	char resp;
	long fposicao;
	abrir_arquivo("rb+");
	//questão 1
	bar();
	gotoxy(40,10);printf("\n1. De quem eh a famosa frase");
	gotoxy(40,11);printf("'Penso, logo existo':");
	gotoxy(40,12);printf("a)Platao");
	gotoxy(40,13);printf("b)Galileu Galilei");
    gotoxy(40,14);printf("c)Descartes");
	gotoxy(40,15);printf("d)Socrates");
	gotoxy(40,16);printf("e)Francis Bacon");
	gotoxy(40,19);	printf ("Resposta:");
	gotoxy(49,20);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 2
    bar();
	gotoxy(40,10);printf("2-Quais o menor e o maior pais do mundo:");
	gotoxy(40,11);printf("a)Vaticano e Russia");
	gotoxy(40,12);printf("b)Nauru e China");
	gotoxy(40,13);printf("c)Monaco e Canada");
	gotoxy(40,14);printf("d)Malta e Estados Unidos");
	gotoxy(40,15);printf("e)Sao Marino e India");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
//questao 3
    bar();
	gotoxy(40,10);printf("\n3-O efeito estufa é:");
	gotoxy(40,11);printf("a)O efeito natural de aquecimento da Terra");
	gotoxy(40,12);printf("b)O mesmo que o aquecimento global");
	gotoxy(40,13);printf("c)Pulverizacao de plantas em uma estufa");
	gotoxy(40,14);printf("d)Puluicao nas matas");
	gotoxy(40,15);printf("e)Derretimento das calotas polares");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}	
//questao 4
    bar();
	gotoxy(40,10);printf("4-Quantas casas decimais tem o numero pi:");
	gotoxy(40,11);printf("a)Duas");
	gotoxy(40,12);printf("b)Centenas");
	gotoxy(40,13);printf("c)Trilhares");
	gotoxy(40,14);printf("d)Vinte");
	gotoxy(40,15);printf("e)Milhares");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
//questão 5
    bar();
	gotoxy(40,10);printf("5-Atualmente, quantos elementos quimicos");
	gotoxy(40,11);printf("a tabela periodica possui?");
	gotoxy(40,12);printf("a)113");
	gotoxy(40,13);printf("b)109");
	gotoxy(40,14);printf("c)108");
	gotoxy(40,15);printf("d)118");
	gotoxy(40,16);printf("e)92");
	gotoxy(40,19);	printf ("Resposta:");
	gotoxy(49,20);resp=getchar();
	if (resp =='d'||resp =='D')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
//questão 6
    bar();
	gotoxy(40,10);printf("6-Quais os paises que tem a maior e a");
	gotoxy(40,11);printf("menor expectativa de vida do mundo:");
	gotoxy(40,12);printf("a) Australia e Afeganistao");
	gotoxy(40,13);printf("b)Japao e Serra Leoa");
	gotoxy(40,14);printf("c)Italia e Chade");
	gotoxy(40,15);printf("d)Brasil e Congo");
	gotoxy(40,16);printf("e)Estados Unidos e Angola");
	gotoxy(40,20);	printf ("Resposta:");
	gotoxy(49,21);resp=getchar();;
		if (resp  =='c'||resp=='C')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 7
    bar();
	gotoxy(40,10);printf("7-O que a palavra legend significa em portugues:");
	gotoxy(40,11);printf("a)Legenda");
	gotoxy(40,12);printf("b)Conto");
	gotoxy(40,13);printf("c)Historia");
	gotoxy(40,14);printf("d)Lenda");
	gotoxy(40,15);printf("e)Legendario");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp  =='d'||resp  =='D')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 8
	bar();
	gotoxy(40,10);printf("\n8.Qual o numero de jogadores no basquete?");
	gotoxy(40,11);printf("a)8");
	gotoxy(40,12);printf("b)10");
	gotoxy(40,13);printf("c)9");
	gotoxy(40,14);printf("d)5");
	gotoxy(40,15);printf("e)7");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp  =='e'||resp  =='E')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 9
	bar();
	gotoxy(40,10);printf("9-Quais as duas datas que sao comemoradas em novembro?");
	gotoxy(40,11);printf("a)Independencia do Brasil e Dia da Bandeira");
	gotoxy(40,12);printf("b)Proclamacao da Republica e Dia Nacional da Consciencia Negra");
	gotoxy(40,13);printf("c)Dia do Medico e Dia de Sao Lucas");
	gotoxy(40,14);printf("d)Dia de Finados e Dia Nacional do Livro");
	gotoxy(40,15);printf("e)Black Friday e Dia da Arvore");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='b'||resp  =='B')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
//questão 10
    bar();
	gotoxy(40,10);printf("10-Quanto tempo a luz do Sol demora para chegar a Terra?");
	gotoxy(40,11);printf("a)12 minutos");
	gotoxy(40,12);printf("b)1 dia");
	gotoxy(40,13);printf("c)12 horas");
	gotoxy(40,14);printf("d)8 minutos");
	gotoxy(40,15);printf("e)segundos");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp  =='d'||resp  =='D')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 11
	bar();
	gotoxy(40,10);printf("11-Em que periodo da pre-historia o fogo foi descoberto?");
	gotoxy(40,11);printf("a)Neolitico");
	gotoxy(40,12);printf("b)Paleolitico");
	gotoxy(40,13);printf("c)Idade dos Metais");
	gotoxy(40,14);printf("d)Periodo da Pedra Polida");
	gotoxy(40,15);printf("e)Idade Media");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='b'||resp  =='B')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 12
    bar();
	gotoxy(40,10);printf("12-Em qual local da Asia o portugues é lingua oficial?");
	gotoxy(40,11);printf("a)India");
	gotoxy(40,12);printf("b)Filipinas");
	gotoxy(40,13);printf("c)Mocambique");
	gotoxy(40,14);printf("d)Macau");
	gotoxy(40,15);printf("e)Portugal");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp  =='d'||resp =='D')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}//questão 13
    bar();
	gotoxy(40,10);printf("13-Quantos planetas existem no nosso sistema solar?");
	gotoxy(40,11);printf("a)8");
	gotoxy(40,12);printf("b)6");
	gotoxy(40,13);printf("c)7");
	gotoxy(40,14);printf("d)12");
	gotoxy(40,15);printf("e)10");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp  =='a'||resp  =='A')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 14 
    bar();
	gotoxy(40,10);printf("14-Qual o maior animal terrestre?");
	gotoxy(40,11);printf("a)Baleia Azul");
	gotoxy(40,12);printf("b)Dinossauro");
	gotoxy(40,13);printf("c)Elefante africano");
	gotoxy(40,14);printf("d)Tubarão Branco");
	gotoxy(40,15);printf("e)Girafa");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='c'||resp  =='C')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	//questão 15
    bar();
	gotoxy(40,10);printf("\n15-Qual o meio de transporte mais seguro:");
	gotoxy(40,11);printf("a)Carro");
	gotoxy(40,12);printf("b)Trem");
	gotoxy(40,13);printf("c)Moto");
	gotoxy(40,14);printf("d)Aviao");
	gotoxy(40,15);printf("e)Navil");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,19);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score3+=10;
		fflush(stdin);
		system("cls");
	}
	// result
	bar();
	gotoxy(42,10);printf("Sua pontuacao foi: %d !!!",score3);
	gotoxy(42,11);printf("Parabens!!");
	Sleep(2000);
	int codi;
	char nicks[50];
	system("color 70");
	bar();
	abrir_arquivo("rb+");
	char conf;
	
do{
		gotoxy(43,9); printf("_______________LOGIN______________");
		gotoxy(43,10);printf("CODIGO:");
		gotoxy(43,12);printf("NICK:");
		gotoxy(43,13);printf("__________________________________");
		gotoxy(50,10);scanf("%d",&codi);	
		
		if(codi!=0)
		{
			f=0;
			rewind(fp);
			do
			{
				fread( &cad,sizeof(cad),1,fp);
				if ( cad.cod == codi && cad.excluido == 'n')
				{
					f = 1;
		    		fposicao = ftell(fp);
					gotoxy(48,12);printf("%s",cad.nick);
					gotoxy(43,20);printf("Salvar pontuacao (S/N):");
					fflush(stdin);
					do
					{
						 gotoxy(69,20); conf = getchar();
					}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N'  );
					if( conf == 's' || conf == 'S' )
					{
						fseek (fp,fposicao-(sizeof(cad)),SEEK_SET);
						cad.pontos.scorec=score3;
						f=1;
					    if(fwrite (&cad,sizeof(cad),1,fp)==1)
					    {
					    	fflush (fp);
					    }
					    system("cls");
					    game();
				   	}
				}	
			}while(!feof(fp));
		}
	}while(codi!=cad.cod && nicks != cad.nick);}
void jogos(){
	int score2=0;int f=0;
	long fposicao;
	char resp;
	abrir_arquivo("rb+");	
	//1
	bar();
	gotoxy(40,10);printf("1-Qual desses jogos n%co %c exclusivo",134,130);
	gotoxy(40,11);printf("da PSN:");
	gotoxy(40,12);printf("a)Until Dawn");
	gotoxy(40,13);printf("b)Uncharted");
	gotoxy(40,14);printf("c)Forza Horizon");
	gotoxy(40,15);printf("d)The Last of Us");
	gotoxy(40,16);printf("e)Horizon: Zero Dawn");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//2
	bar();
	gotoxy(40,10);printf("2-Quem %c a m%ce de Kratos",130,134);
	gotoxy(40,11);printf("do jogo God of War:");
	gotoxy(40,12);printf("a)Gaia");
	gotoxy(40,13);printf("b)Calisto");
	gotoxy(40,14);printf("c)Lysandra");
	gotoxy(40,15);printf("d)R%cia",130);
	gotoxy(40,16);printf("e)Hera");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='b'||resp=='B')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//3
	bar();
	gotoxy(40,10);printf("3-Em que ano foi lan%cado o primeiro Sonic:",135);
	gotoxy(40,11);printf("a)1991 ");
	gotoxy(40,12);printf("b)1994");
	gotoxy(40,13);printf("c)1996");
	gotoxy(40,14);printf("d)1999");
	gotoxy(40,15);printf("e)N.D.A");
	gotoxy(40,17);printf ("Resposta:");
	gotoxy(49,17);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//4
	bar();
	gotoxy(40,10);printf("4-Qual %c o nome do MOB do Minecraft que",130);
	gotoxy(40,11);printf("explode quando voc%c chega perto:",136);
	gotoxy(40,12);printf("a)Creeper");
	gotoxy(40,13);printf("b)Zumbi");
	gotoxy(40,14);printf("c)Lobo");
	gotoxy(40,15);printf("d)Enderman");
	gotoxy(40,16);printf("e)Ovelha");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//5
	bar();
	gotoxy(40,10);printf("5-Em Detroit Become Human, voc%c controla",136);
	gotoxy(40,11);printf("de tr%cs personagens que s%co:",136,134);
	gotoxy(40,12);printf("a)Conor - Shelly - MarKus");
	gotoxy(40,13);printf("b)Bryan - Abgail - Zak");
	gotoxy(40,14);printf("c)Kara - Zak - Damian");
	gotoxy(40,15);printf("d)Sara - Markus - Kalvin");
	gotoxy(40,16);printf("e)Conor - Kara - Markus");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp=='e'||resp =='E')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//6
	bar();
	gotoxy(40,10);printf("6-No modo Zombies do Call of Duty");
	gotoxy(40,11);printf("Word War II, voc%c enfrenta:",136);
	gotoxy(40,12);printf("a)Nazis-Zombies");
	gotoxy(40,13);printf("b)Playes-Zombies");
	gotoxy(40,14);printf("c)Humanos");
	gotoxy(40,15);printf("d)Vampiros");
	gotoxy(40,16);printf("e)Aliens");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp=='a'||resp =='A')
	{
		score2+=10;	
		fflush(stdin);
		system("cls");
	}
	//7
	bar();
	gotoxy(40,10);printf("7-Qual %c o nome do personagem principal",130);
	gotoxy(40,11);printf("da saga Zelda:");
	gotoxy(40,12);printf("a)Peach");
	gotoxy(40,13);printf("b)Zelda");
	gotoxy(40,14);printf("c)Link");
	gotoxy(40,15);printf("d)Mario");
	gotoxy(40,16);printf("e)Tails");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score2+=10;	
		fflush(stdin);
		system("cls");
	}
	//8
	bar();
	gotoxy(40,10);printf("9-Qual desses n%Co possui:",134);
	gotoxy(40,11);printf("vers%co mobile:",134);
	gotoxy(40,12);printf("a)Mortal Kombat");
	gotoxy(40,13);printf("b)Minecraft");
	gotoxy(40,14);printf("c)PUBG");
	gotoxy(40,15);printf("d)GTA 5");
	gotoxy(40,16);printf("e)N.D.A");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='e'||resp=='E')	
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//9
	bar();
	gotoxy(40,10);printf("8-Qual desses n%co pertence",134);
	gotoxy(40,11);printf("ao jogo Tekken 7:");
	gotoxy(40,12);printf("a)Akuma");
	gotoxy(40,13);printf("b)Asuka");
	gotoxy(40,14);printf("c)Devil Jin");
	gotoxy(40,15);printf("d)Claudio Serafino");
	gotoxy(40,16);printf("e)Ryu");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp=='e'||resp=='E')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//10
	gotoxy(40,10);printf("10-Qual %c o verdadeiro nome do",130);
	gotoxy(40,11);printf("filho de Kratos em God of War 4:");
	gotoxy(40,12);printf("a)Ateus");
	gotoxy(40,13);printf("b)Perceus");
	gotoxy(40,14);printf("c)Thor");
	gotoxy(40,15);printf("d)Odin");
	gotoxy(40,16);printf("e)Loki");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='e'||resp =='E')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//11
	bar();
	gotoxy(40,10);printf("11-Call of Duty Black Ops 2 retrata:");
	gotoxy(40,11);printf("a)O presente");
	gotoxy(40,12);printf("b)O passado");
	gotoxy(40,13);printf("c)O futuro");
	gotoxy(40,14);printf("d)O passado e o futuro");
	gotoxy(40,15);printf("e)O passado e o presente");
	gotoxy(40,17);	printf ("Resposta:");
	gotoxy(49,17);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//12
	bar();
	gotoxy(40,10);printf("12-Qual desses MOBS n%co %c possivel",134,130);
	gotoxy(40,11);printf("domesticar no minecraft");
	gotoxy(40,12);printf("a)Lobo");
	gotoxy(40,13);printf("b)Cavalo");
	gotoxy(40,14);printf("c)Jaguatirica");
	gotoxy(40,15);printf("d)Ovelha");
	gotoxy(40,16);printf("e)N.D.A");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp=='d'||resp=='D')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//13
	bar();
	gotoxy(40,10);printf("13-Qual desses n%co pertence",134);
	gotoxy(40,11);printf("ao Mortal Kombat:");
	gotoxy(40,12);printf("a)Liu Kang");
	gotoxy(40,13);printf("b)Kung Lao");
	gotoxy(40,14);printf("c)Johnny Cash");
	gotoxy(40,15);printf("d)Sub-Zero");
	gotoxy(40,16);printf("e)N.D.A");
	gotoxy(40,18);printf ("Resposta:");
	gotoxy(49,18);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	//14
	bar();
	gotoxy(40,10);printf("14-Qual n%co %c exclusivo da Xbox:",134,130);
	gotoxy(40,11);printf("a)Halo");
	gotoxy(40,12);printf("b)Gears of War");
	gotoxy(40,13);printf("c)Killer Instinct");
	gotoxy(40,14);printf("d)Resident Evil 7");
	gotoxy(40,15);printf("e)Last Night");
	gotoxy(40,17);printf("Resposta:");
	gotoxy(49,17);resp=getchar();
	if (resp =='d'||resp =='D')
	{	
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	
	//15
	bar();
	gotoxy(40,10);printf("15-Qual n%co pertence ao Resident Evil 6:",134);
	gotoxy(40,11);printf("a)Chris Redfield");
	gotoxy(40,12);printf("b)Leon Kennedy");
	gotoxy(40,13);printf("c)Ada Wong");
	gotoxy(40,14);printf("d)John Muller");
	gotoxy(40,15);printf("e)Sherry Birkin");
	gotoxy(40,17);printf ("Resposta:");
	gotoxy(49,17);resp=getchar();
	if (resp =='d'||resp =='D')
	{
		score2+=10;
		fflush(stdin);
		system("cls");
	}
	
    //result
    bar();
	gotoxy(42,10);printf("Sua pontua%c%co foi: %d !!!",71,134,score2);
	gotoxy(42,11);printf("Parab%cns!!");
	Sleep(2000);
	int codi;
	char nicks[50], conf;
	system("color 70");
	bar();
	abrir_arquivo("rb+");
	
	do{
		gotoxy(43,9); printf("_______________LOGIN______________");
		gotoxy(43,10);printf("CODIGO:");
		gotoxy(43,12);printf("NICK:");
		gotoxy(43,13);printf("__________________________________");
		gotoxy(50,10);scanf("%d",&codi);	
		
		if(codi!=0)
		{
			f=0;
			rewind(fp);
			do
			{
				fread( &cad,sizeof(cad),1,fp);
				if ( cad.cod == codi && cad.excluido == 'n')
				{
					f = 1;
		    		fposicao = ftell(fp);
					gotoxy(48,12);printf("%s",cad.nick);
					gotoxy(43,20);printf("Salvar pontuacao (S/N):");
					fflush(stdin);
					do
					{
						 gotoxy(69,20); conf = getchar();
					}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N'  );
					if( conf == 's' || conf == 'S' )
					{
						fseek (fp,fposicao-(sizeof(cad)),SEEK_SET);
						cad.pontos.scoreg=score2;
						f=1;
					    if(fwrite (&cad,sizeof(cad),1,fp)==1)
					    {
					    	fflush (fp);
					    }
					    system("cls");
					    game();
				   	}
				}	
			}while(!feof(fp));
		}
	}while(codi!=cad.cod && nicks != cad.nick);
}

void filmes()
{

	int score=0, f=0;
	char resp;
	long fposicao;
	abrir_arquivo("rb+");
	//1
	bar();
	gotoxy(42,10);printf("1-No filme 'Thor:Ragnarok', qual "); 
	gotoxy(42,11);printf("a arma de Thor: ");
	gotoxy(42,12);printf("a)Martelo");
	gotoxy(42,13);printf("b)Escudo");
	gotoxy(42,14);printf("c)Espada");
	gotoxy(42,15);printf("d)Chave de fenda");
	gotoxy(42,16);printf("e)Arma de fogo");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//2
	bar();
	gotoxy(42,10);printf("2-Hazel Grace é uma adolescente de 16");
	gotoxy(42,11);printf("anos que tem cancer no pulmao.");
	gotoxy(42,12);printf("Qual o filme:");	
	gotoxy(42,13);printf("a)Para sempre");
	gotoxy(42,14);printf("b)A culpa é das estrelas");
	gotoxy(42,15);printf("c)ABC do amor");
	gotoxy(42,16);printf("d)Titanic");
	gotoxy(42,17);printf("e)Cartas para Julieta");
	gotoxy(42,20);	printf ("Resposta:");
	gotoxy(42,21);resp=getchar();
	if (resp =='b'||resp =='B')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}	
	//3
	bar();
	gotoxy(42,10);printf("3-Quem faz o pistoleiro no filme ");
	gotoxy(42,11);printf("Esquadrão Suicida:");
	gotoxy(42,12);printf("a)Jared Leto");
	gotoxy(42,13);printf("b)Ninguém sabe");
	gotoxy(42,14);printf("c)Will Smith");
	gotoxy(42,15);printf("d)Leonardo DiCaprio");
	gotoxy(42,16);printf("e)Brad Pitt");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//4
	bar();
	gotoxy(41,10);printf("4-no filme 'Capitao America:Guerra Civil',");
	gotoxy(41,11);printf("quem é lançado para o centro da");
	gotoxy(41,12);printf("terra pela Wanda?");
	gotoxy(41,13);printf("a)Capitao America");
	gotoxy(41,14);printf("b)Homem-Formiga");
	gotoxy(41,15);printf("c)Visão");
	gotoxy(41,16);printf("d)Gavião-Arqueiro");
	gotoxy(41,17);printf("e)Maquina de Combate");
	gotoxy(41,20);	printf ("Resposta:");
	gotoxy(41,21);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//5
	bar();
	gotoxy(42,10);printf("5-Qual feitico nao é de Harry Potter");
	gotoxy(42,11);printf("a)Accio");
	gotoxy(42,12);printf("b)Lumos");
	gotoxy(42,13);printf("c)Morsmordre");
	gotoxy(42,14);printf("d)Imperius");
	gotoxy(42,15);printf("e)N.D.A");
	gotoxy(42,18);	printf ("Resposta:");
	gotoxy(42,19);resp=getchar();
		if (resp =='e'||resp =='E')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//6
	bar();
	gotoxy(42,10);printf("6-Em 'O Doador de Memorias',");
	gotoxy(42,11);printf("Taylor Swift interpreta:");
	gotoxy(42,12);printf("a)Fiona");
	gotoxy(42,13);printf("b)Rosemary");
	gotoxy(42,14);printf("c)Ancia Chefe");
	gotoxy(42,15);printf("d)Lilly");
	gotoxy(42,16);printf("e)Gabe");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='b'||resp =='B')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//7
	bar();
	gotoxy(42,10);printf("7-Em 'De Volta Para o Futuro',");
	gotoxy(42,11);printf("qual eh o nome completo do Marty McFly?");
	gotoxy(42,12);printf("a)Martin McFly");
	gotoxy(42,13);printf("b)Martin Douglas McFly");
	gotoxy(42,14);printf("c)Martin William McFly");
	gotoxy(42,15);printf("d)Martin Seamus McFly");
	gotoxy(42,16);printf("e)Martin Dudu McFly");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='d'||resp =='D')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//8
	bar();
	gotoxy(42,10);printf("8-Em 'Divergente', com qual idade os");
	gotoxy(42,11);printf("adolecentes realizam o Teste de Aptidão:");
	gotoxy(42,12);printf("a)20 anos");
	gotoxy(42,13);printf("b)17 anos");
	gotoxy(42,14);printf("c)12 anos");
	gotoxy(42,15);printf("d)16 anos");
	gotoxy(42,16);printf("e)18 anos");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='d'||resp =='D')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}	
	//9
	bar();
	gotoxy(42,10);printf("9-Em 'Operacao Big Hero', ");
	gotoxy(42,11);printf("qual e o nome do irmao de Hiro:");
	gotoxy(42,12);printf("a)Baymax");
	gotoxy(42,13);printf("b)Adamishuki");
	gotoxy(42,14);printf("c)Tadashi");
	gotoxy(42,15);printf("d)Toneshiudu");
	gotoxy(42,16);printf("e)Wasabi");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='c'||resp =='C')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}	
    //10
    bar();
	gotoxy(40,10);printf("10-Em 'Guardioes da Galaxia', quem Drax quer");
	gotoxy(40,11);printf("matar por ter assassinado sua esposa e filho:");
	gotoxy(40,12);printf("a)Thanos");
	gotoxy(40,13);printf("b)Groot");
	gotoxy(40,14);printf("c)Rocket Raccoon");
	gotoxy(40,15);printf("d)Ronan");
	gotoxy(40,16);printf("e)Nebulosa");
	gotoxy(40,18);	printf ("Resposta:");
	gotoxy(49,28);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}		
	//11
	bar();
	gotoxy(42,10);printf("11-Em 'Se Beber, Não Case III', o que Alan");
	gotoxy(42,11);printf("da para Stu na festa de casamento:");
	gotoxy(42,12);printf("a)Um show com Mike Tyson");
	gotoxy(42,13);printf("b)Um barco");
	gotoxy(42,14);printf("c)Um cheque");
	gotoxy(42,15);printf("d)Uma tatuagem");
	gotoxy(42,16);printf("e)Uma flor");
	gotoxy(42,19);printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='a'||resp =='A')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}		
	//12
	bar();
	gotoxy(42,10);printf("O Filme 'As Branquelas'");
	gotoxy(42,11);printf("lançado em qual ano:");
	gotoxy(42,12);printf("a)1999");
	gotoxy(42,13);printf("b)2000");
	gotoxy(42,14);printf("c)2001");
	gotoxy(42,15);printf("d)2004");
	gotoxy(42,16);printf("e)2005");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='d'||resp =='D')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//13
	bar();
	gotoxy(42,10);printf("13-'Meu nome eh Bond, James Bond'");
	gotoxy(42,11);printf("faz parte de qual filme:");
	gotoxy(42,12);printf("a)Missao Impossivel");
	gotoxy(42,13);printf("b)Inspetor Bugiganga");
	gotoxy(42,14);printf("c)Sr. e Sra. Smith");
	gotoxy(42,15);printf("d)007");
	gotoxy(42,16);printf("e)Agente 86");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='d'||resp =='D')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
	//14
	bar();
	gotoxy(42,10);printf("14-A frase 'Eu sou o rei do mundo',");
	gotoxy(42,11);printf("foi dita no filme:");
	gotoxy(42,12);printf("a)Romeu e Julieta");
	gotoxy(42,13);printf("b)E o vento levou");
	gotoxy(42,14);printf("c)Lua Nova");
	gotoxy(42,15);printf("d)Amanhecer - parte 2");
	gotoxy(42,16);printf("e)Titanic");
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='e'||resp =='E')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}	
	//15
	bar();
	gotoxy(42,10);printf("15-No filme 'Lua Nova',");
	gotoxy(42,11);printf("por que Edward se vai:");
	gotoxy(42,12);printf("a)Por medo do pai de Bella");
	gotoxy(42,13);printf("b)Ciumes");
	gotoxy(42,14);printf("c)Para enfrentar os Volturis");
	gotoxy(42,15);printf("d)Para se matar");
	gotoxy(42,16);printf("e)N.D.A");	
	gotoxy(42,19);	printf ("Resposta:");
	gotoxy(42,20);resp=getchar();
	if (resp =='e'||resp =='E')
	{
		score+=10;
		fflush(stdin);
		system("cls");
	}
    // result
    bar();
	gotoxy(42,10);printf("Sua pontuacao foi: %d !!!",score);
	gotoxy(42,11);printf("Parabens!!");
	Sleep(2000);
	int codi;
	char nicks[50];
	system("color 70");
	bar();
	abrir_arquivo("rb+");
	
do{
		gotoxy(43,9); printf("_______________LOGIN______________");
		gotoxy(43,10);printf("CODIGO:");
		gotoxy(43,12);printf("NICK:");
		gotoxy(43,13);printf("__________________________________");
		gotoxy(50,10);scanf("%d",&codi);	
		char conf;
		if(codi!=0)
		{
			f=0;
			rewind(fp);
			do
			{
				fread( &cad,sizeof(cad),1,fp);
				if ( cad.cod == codi && cad.excluido == 'n')
				{
					f = 1;
		    		fposicao = ftell(fp);
					gotoxy(48,12);printf("%s",cad.nick);
					gotoxy(43,20);printf("Salvar pontuacao (S/N):");
					fflush(stdin);
					do
					{
						 gotoxy(69,20); conf = getchar();
					}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N'  );
					if( conf == 's' || conf == 'S' )
					{
						fseek (fp,fposicao-(sizeof(cad)),SEEK_SET);
						cad.pontos.scoref=score;
						f=1;
					    if(fwrite (&cad,sizeof(cad),1,fp)==1)
					    {
					    	fflush (fp);
					    }
					    system("cls");
					    game();
				   	}
				}	
			}while(!feof(fp));
		}
	}while(codi!=cad.cod && nicks != cad.nick);}
void harry(){
	system("color F0");
	//cabelo
	textcolor(BLACK);
	gotoxy(14,2);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,220,223);
	gotoxy(12,3);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(10,4);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(10,5);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,223);
	gotoxy(8,6);printf("%c%c%c%c%c%c%c%c  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,223);
	gotoxy(8,7);printf("%c%c%c%c%c      %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c  %c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,223);
	gotoxy(8,8);printf("%c%c%c            %c%c  %c%c  %c%c%c%c%c%c%c%c  %c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,223);
	gotoxy(8,9);printf("%c%c%c                        %c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,223);
	gotoxy(42,10);printf("%c%c%c%c",219,219,219,219);
	gotoxy(42,11);printf("%c%c%c%c",219,219,219,219);
	gotoxy(42,12);printf("%c%c%c%c",219,219,219,219);
	gotoxy(42,13);printf("%c%c",219,219,219,219);
	
	//óculos
	textcolor(8);gotoxy(13,9);printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy(11,10);printf("%c%c",219,219);
	gotoxy(9,11);printf("%c%c%c%c",219,219,219,219);
	gotoxy(11,12);printf("%c%c",219,219);
	gotoxy(20,10);printf("%c%c",219,219);
	gotoxy(20,11);printf("%c%c",219,219);
	gotoxy(21,11);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(20,12);printf("%c%c",219,219);
	gotoxy(13,13);printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	//
	gotoxy(29,9);printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy(27,10);printf("%c%c",219,219);
	gotoxy(27,11);printf("%c%c",219,219);
	gotoxy(27,12);printf("%c%c",219,219);
	gotoxy(36,10);printf("%c%c",219,219);
	gotoxy(36,11);printf("%c%c%c%c",219,219,219,219);
	gotoxy(36,12);printf("%c%c",219,219);
	gotoxy(29,13);printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);

	gotoxy(24,19);printf("%c%c%c%c",219,219,219,219);
	gotoxy(28,19);printf("%c%c%c%c",219,219,219,219);
	gotoxy(24,20);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy(24,21);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(24,22);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(24,23);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(24,24);printf("%c%c%c%c%c%c",219,219,219,219,219,219);	
	//branco
	textcolor(7);
	gotoxy(24,18);printf("%c%c%c%c",219,219,219,219);
	gotoxy(26,19);printf("%c%c",219,219,219,219);
	gotoxy(27,18);printf("%c%c%c%c",219,219,219,219);
	
	//calça
	gotoxy(24,25);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(24,25);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	
//varinha
	textcolor(RED);

	gotoxy(4,16);printf("%c%c",219,219);
	gotoxy(6,17);printf("%c%c",219,219);
	gotoxy(8,18);printf("%c%c",219,219);
	gotoxy(10,19);printf("%c%c",219,219);
	gotoxy(12,20);printf("%c%c",219,219);
	//gravata
	gotoxy(26,18);printf("%c%c",219,219);
	//roupa
	textcolor(BLACK);
	gotoxy(31,11);printf("%c%c",219,219);
	gotoxy(15,11);printf("%c%c",219,219);
	
	gotoxy(20,18);printf("%c%c%c%c",219,219,219,219);
	gotoxy(18,19);printf("%c%c%c%c%c%c",219,219,219,219);
	gotoxy(16,20);printf("%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy(16,21);printf("%c%c%c%c",219,219,219,219);
	gotoxy(14,22);printf("%c%c%c%c",219,219,219,219);
	gotoxy(22,21);printf("%c%c",219,219,219,219);
	gotoxy(22,22);printf("%c%c",219,219,219,219);
	gotoxy(20,23);printf("%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy(20,24);printf("%c%c%c%c",219,219,219,219,219,219,219,219);
	gotoxy(18,25);printf("%c%c%c%c",219,219,219,219);
	//direito
	gotoxy(30,18);printf("%c%c%c%c%c%c",219,219,219,219,219,219);
	gotoxy(30,19);printf("%c%c%c%c%c%c",219,219,219,219);
	gotoxy(32,20);printf("%c%c%c%c%c%c",219,219,219,219);
	gotoxy(30,21);printf("%c%c%c%c%c%c",219,219,219,219);
	gotoxy(30,22);printf("%c%c%c%c",219,219,219,219);
	gotoxy(30,23);printf("%c%c%c%c",219,219,219,219);
	gotoxy(30,24);printf("%c%c%c%c%c%c",219,219,219,219,219,219);	
	gotoxy(30,25);printf("%c%c%c%c%c%c",219,219,219,219,219,219);;
	//fim
	gotoxy(1,1);textcolor(1);printf("");
}
void controle(){
	//cabo
	system("color 70");
	textcolor(BLACK);
	gotoxy(36,4);
	printf("%c",223);
	gotoxy(37,5);
	printf("%c%c",223,223);
	gotoxy(39,6);
	printf("%c%c%c",223,223,223);
	textcolor(8);
	gotoxy(39,7);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(37,8); 
	printf("%c%c",219,219);gotoxy(82,8);printf("%c%c",219,219);
	gotoxy(36,9);  
	printf("%c%c",219,219);gotoxy(83,9);printf("%c%c",219,219);
	gotoxy(35,10);
	printf("%c%c",219,219);gotoxy(84,10);printf("%c%c",219,219);
	gotoxy(34,11); 
	printf("%c%c",219,219);gotoxy(85,11);printf("%c%c",219,219);
	gotoxy(33,12);
	printf("%c%c",219,219);gotoxy(86,12);printf("%c%c",219,219);
	gotoxy(33,13); 
	printf("%c%c",219,219);gotoxy(86,13);printf("%c%c",219,219);
	gotoxy(33,14);
	printf("%c%c",219,219);gotoxy(86,14);printf("%c%c",219,219,219,219);
	gotoxy(34,15); 
	printf("%c%c",219,219);gotoxy(85,15);printf("%c%c",219,219,219,219);
    gotoxy(35,16);
	printf("%c%c",219,219);gotoxy(84,16);printf("%c%c",219,219,219,219);
	gotoxy(36,17);
	printf("%c%c",219,219);gotoxy(83,17);printf("%c%c",219,219,219,219);
	gotoxy(37,18);
	printf("%c%c     %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c     %c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(39,19);
	printf("%c%c%c%c%c                                 %c%c%c%c%c",223,223,223,223,223,223,223,223,223,223);
	//direcional
	textcolor(BLACK);
	gotoxy(42,11);
	printf("%c%c",219,219);
	gotoxy(38,13);
	printf("%c%c  %c%c  %c%c",219,219,219,219,219,219);
	gotoxy(42,15);
	printf("%c%c",219,219);
	//start/select
	textcolor(8);
	gotoxy(59,13);printf("%c%c   %c%c",223,223,223,223);
	gotoxy(57,14);printf("%c%c   %c%c",223,223,223,223);
	//botoes
	textcolor(1);	gotoxy(77,11);printf("%c%c",219,219);
	textcolor(2);	gotoxy(74,13);printf("%c%c",219,219);
	textcolor(4);	gotoxy(81,13);printf("%c%c",219,219);
	textcolor(6);	gotoxy(78,15);printf("%c%c",219,219);
	//fim
	gotoxy(1,1);textcolor(1);printf("");
}
void iluminat(){
		system("color 72");
	gotoxy(60,5);
	printf("%c",219);
	gotoxy(59,6);
	printf("%c %c",219,219);
	gotoxy(58,7);
	printf("%c   %c",219,219);
	gotoxy(57,8);
	printf("%c     %c",219,219);
	gotoxy(56,9);
	printf("%c       %c",219,219);
	gotoxy(55,10);
	printf("%c   %c%c%c   %c",219,219,219,219,219);
	gotoxy(54,11);
	printf("%c  %c%c   %c%c  %c",219,219,219,219,219,219);
	gotoxy(53,12);
	printf("%c  %c%c  °  %c%c  %c",219,219,219,219,219,219);
	gotoxy(52,13);
	printf("%c  %c%c       %c%c  %c",219,219,219,219,219,219);
	gotoxy(51,14); 
	printf("%c %c%c%c °  O  ° %c%c%c %c",219,219,219,219,219,219,219,219);
    gotoxy(50,15);
	printf("%c    %c%c       %c%c    %c",219,219,219,219,219,219);
	gotoxy(49,16);
	printf("%c      %c%c  °  %c%c      %c",219,219,219,219,219,219);
	gotoxy(48,17);
	printf("%c        %c%c   %c%c        %c",219,219,219,219,219,219);
	gotoxy(47,18);
	printf("%c           %c%c%c           %c",219,219,219,219,219);
	gotoxy(46,19);
	printf("%c                           %c",219,219);
	gotoxy(45,20);
    printf("%c                             %c",219,219);
	gotoxy(44,21);
	printf("%c                               %c",219,219);
	gotoxy(43,22);
	printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	//fim
	textcolor(1);
}
void fquiz(){
	system("cls");
	gotoxy(28,8);
	printf("  %c%c%c%c%c%c%c%c%c       %c%c         %c%c     %c%c%c%c%c%c%c%c%c%c    %c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,9);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c                   %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,10);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c                  %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,11);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c                 %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,12);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c                %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,13);
	printf("%c%c         %c%C     %c%c         %c%c         %c%c               %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,14);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c              %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,15);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c             %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,16);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c            %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,17); 
	printf("%c%c         %c%c     %c%c         %c%c         %c%c           %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
    gotoxy(28,18);
	printf("%c%c         %c%c     %c%c         %c%c         %c%c          %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,19);
	printf("%c%c     %c%c  %c%c     %c%c         %c%c         %c%c         %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,20);
	printf("%c%c      %c%c %c%c     %c%c         %c%c         %c%c        %c%c",219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,21);
	printf(" %c%c%c%c%c%c%c%c%c%c%c        %c%c%c%c%c%c%c%c%c       %c%c%c%c%c%c%c%c%c%c   %c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(28,22);
	printf("           %c%c",219,219);
}
void cursor (int x) { 
	switch (x) {
		case 0: {
			CONSOLE_CURSOR_INFO cursor = {1, FALSE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
		case 1: {
			CONSOLE_CURSOR_INFO cursor = {1, TRUE};
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor);
			break;
		}
	}
}

void gotoxy(int x, int y)
{
  COORD c;
  c.X = x - 1;
  c.Y = y - 1;
  SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE), c);
}	
void load(){
	int t=1;
	do{
		system("cls");
		gotoxy(33,10);printf("%c",223);
		gotoxy(33,14);printf("%c",223);
		system("color 3A");
		gotoxy(33,12);printf("L");
		Sleep(300);
		gotoxy(35,10);printf("%c",223);
		gotoxy(35,14);printf("%c",223);
		system("color 3B");
		gotoxy(35,12);printf("O");
		Sleep(300);
		gotoxy(37,10);printf("%c",223);
		gotoxy(37,14);printf("%c",223);
		system("color 3C");
		gotoxy(37,12);printf("A");
		Sleep(300);
		gotoxy(39,10);printf("%c",223);
		gotoxy(39,14);printf("%c",223);
		system("color 3D");
		gotoxy(39,12);printf("D");
		Sleep(300);
		gotoxy(41,10);printf("%c",223);
		gotoxy(41,14);printf("%c",223);
		system("color 3E");
		gotoxy(41,12);printf("I");
		Sleep(300);
		gotoxy(43,10);printf("%c",223);
		gotoxy(43,14);printf("%c",223);
		system("color 3F");
		gotoxy(43,12);printf("N");
		Sleep(300);
		gotoxy(45,10);printf("%c",223);
		gotoxy(45,14);printf("%c",223);
		system("color 3E");
		gotoxy(45,12);printf("G");
		Sleep(300);	
		system("cls");
		t++;
	}while(t<=3);		
}
void FL()
{	
	fquiz();
	system("color 72");
	fquiz();
	Sleep(500);
	system("color 73");
	Sleep(500);
	fquiz();
	system("color 74");
	Sleep(500);
	system("color 75");
	Sleep(500);
}
 void margem()
 {
 		textcolor(3);
	for(int i=0;i<=120;i++){
		gotoxy(i,1);printf("%c",219);
		gotoxy(i,2);printf("%c",219);
		gotoxy(i,3);printf("%c",219);
		gotoxy(i,30);printf("%c",219);
		gotoxy(i,29);printf("%c",219);
		gotoxy(i,28);printf("%c",219);
	}
	for(int i=0;i<=30;i++){
		gotoxy(1,i);printf("%c",219);
		gotoxy(2,i);printf("%c",219);
		gotoxy(3,i);printf("%c",219);
		gotoxy(4,i);printf("%c",219);
		gotoxy(5,i);printf("%c",219);
		gotoxy(6,i);printf("%c",219);
		gotoxy(115,i);printf("%c",219);
		gotoxy(116,i);printf("%c",219);
		gotoxy(117,i);printf("%c",219);
		gotoxy(118,i);printf("%c",219);
		gotoxy(119,i);printf("%c",219);
		gotoxy(120,i);printf("%c",219);
	}
 }
void margem2()
{
		textcolor(3);
	for(int i=0;i<=120;i++){
		gotoxy(i,1);printf("%c",219);
		gotoxy(i,2);printf("%c",219);
		gotoxy(i,3);printf("%c",219);
		gotoxy(i,30);printf("%c",219);
		gotoxy(i,29);printf("%c",219);
		gotoxy(i,28);printf("%c",219);
	}
	for(int i=0;i<=30;i++){
		gotoxy(1,i);printf("%c",219);
		gotoxy(2,i);printf("%c",219);
		gotoxy(119,i);printf("%c",219);
		gotoxy(120,i);printf("%c",219);
	}
}
void saida()
{
	system("color c0");
	//rua
	gotoxy(1,24);textcolor(7);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	
	gotoxy(1,25);textcolor(8);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	
	gotoxy(1,26);textcolor(8);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

	gotoxy(1,27);textcolor(8);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	
	gotoxy(1,28);textcolor(8);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	
	gotoxy(1,29);textcolor(8);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	
	gotoxy(1,30);textcolor(7);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	
	//faixa de pedestre
	gotoxy(5,27);textcolor(6);textbackground(8);printf("%c%c%c%c%c%c         %c%c%c%c%c%c         %c%c%c%c%c%c          %c%c%c%c%c%c          %c%c%c%c%c%c          %c%c%c%c%c%c          %c%c%c%c%c%c          %c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	//detalhes da parede
	gotoxy(1,1);textcolor(0);textbackground(12);printf("%c%c%c%c%c",220,220,220,220,220);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,2);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,3);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(6,4);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,5);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,5);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,6);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,7);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(6,8);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,9);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,9);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,10);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,11);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(6,12);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,13);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,13);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,14);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,15);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(6,16);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,17);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,18);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(6,20);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,21);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,21);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,22);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,23);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	//porta
	textcolor(0);
	gotoxy(52,12);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,13);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,14);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,15);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,16);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,18);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,20);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,21);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,22);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(52,23);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	//moldura da porta
	textcolor(8);
	gotoxy(51,12);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	for(int i=13;i<=23;i++){
		gotoxy(51,i);printf("%c",219);
	}
	for(int i=13;i<=23;i++){
		gotoxy(68,i);printf("%c",219);
	}	
	//lampada
	gotoxy(102,1);printf("%c",219);
	gotoxy(102,2);printf("%c",219);
	gotoxy(102,3);printf("%c",219);
	gotoxy(101,4);printf("%c%c%c",219,219,219);
	gotoxy(99,5);printf("%c%c%c%c%c%c%c",219,219,219,219,219,219,219);
	//pisca luz
		int y=2;
		int x=6;
		gotoxy(52,9);textbackground(0);textcolor(y);printf("  G   A   B'  s ");
		gotoxy(54,10);textbackground(0);textcolor(y);printf("  B   A   R ");
		y++;
	
		cursor(0);
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(2000);
		x=7;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(100);
		x=6;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(500);
		x=7;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(300);
	
		gotoxy(52,9);textbackground(0);textcolor(y);printf("  G   A   B'  s ");
		gotoxy(54,10);textbackground(0);textcolor(y);printf("  B   A   R ");
		y++;
	
		cursor(0);
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(2000);
		x=7;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(100);
		x=6;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(500);
		x=7;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(300);
		
		gotoxy(52,9);textbackground(0);textcolor(y);printf("  G   A   B'  s ");
		gotoxy(54,10);textbackground(0);textcolor(y);printf("  B   A   R ");
		y++;
	
		cursor(0);
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(2000);
		x=7;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(100);
		x=6;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(500);
		x=7;
		gotoxy(100,6);textcolor(x);printf("%c%c%c%c%c",219,219,219,219,219);
		Sleep(300);
	cursor(0);
}
void Consulta(){
	bar();
	int a=10, c;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	system("cls");
	bar();
	if((fp = fopen("dados.bin", "rb")) == NULL) 
	{
	    gotoxy(18,11);printf("Erro na abertura do arquivo");
	    exit(1);
	}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else
	{
		rewind(fp);
		do
		{
			int nome=9, idade=9, email=9,nick=9, codigo=9, jogos=9, filmes=9, cg=9, status=9, l=10;
			int pesquisa;
			char pesquisa2[200];
			textcolor(0);
			gotoxy(45,9);printf("__________REGISTROS__________");
			gotoxy(45,10);printf("TABELA");
			gotoxy(45,12);printf("UNIT%cRIO",181);
			gotoxy(45,14);printf("PESQUISAR COD :");
			gotoxy(45,16);printf("PESQUISAR NICK :");
			gotoxy(45,18);printf("ALTERAR DADOS",181);
			gotoxy(45,20);printf("EXCLUIR DADOS",181);
			gotoxy(45,21);printf("______________________________");
			gotoxy(43,a);printf("->");
			
			c=getch();
			switch(c)
			{
				case 72:gotoxy(43,a);printf("  ");
					a-=2;
					if(a<10)
					{
						a=20;
					}
					gotoxy(43,a);printf("->");
					break;
				case 80:gotoxy(43,a);printf("  ");
					a+=2;
					if(a>20)
					{
						a=10;
					}
					gotoxy(43,a);printf("->");
					break;
			}	
			//////////////////////////////////////// 
			if(c==13) 
			{
				if(a==10)
				{
					system("cls");
					tabela();
				}
				if(a==16)
				{
					gotoxy(61,a);gets(pesquisa2);				
					system("cls");
					gotoxy(20,10);printf("Procurando...");
					Sleep(1000);
					system("cls");
					abrir_arquivo("rb");
					while(!feof(fp))
					{
						textcolor(0);
						if(fread(&cad ,sizeof(cad), 1, fp)==1 && cad.excluido=='n')
						{
							gotoxy(56,4);printf("CADASTROS");
							if(strstr(cad.nick,pesquisa2)!=NULL)
							{
								gotoxy(3,7);printf("COD");gotoxy(7,7);printf("|");
								gotoxy(12,7);printf("NOME");gotoxy(20,7);printf("|");
								gotoxy(22, 7);printf("IDADE");gotoxy(28,7);printf("|");
								gotoxy(39, 7);printf("E-MAIL");gotoxy(55,7);printf("|");
								gotoxy(58,7);printf("NICK");gotoxy(64,7);printf("|");
								gotoxy(65,7);printf("   CONHECIMENTOS  |  JOGOS  |   FILMES   |");
								gotoxy(109,7);printf("STATUS   |");
								gotoxy(3,8);printf("----|------------|-------|--------------------------|--------|------------------|---------|------------|-----------|");
								gotoxy(3,codigo);printf("%d",cad.cod);gotoxy(7,codigo);printf("|");
								codigo+=2;
								gotoxy(8,nome);puts(cad.nome);gotoxy(20,nome);printf("|");
								nome+=2;
								gotoxy(21,idade);printf("%d",cad.idade);gotoxy(28,idade);printf("|");
								idade+=2;
								gotoxy(29,email);puts(cad.email);gotoxy(55,email);printf("|");
								email+=2;
								gotoxy(56,nick);puts(cad.nick);gotoxy(64,nick);printf("|");
								nick+=2;
								gotoxy(65,cg);printf("%d",&cad.pontos.scorec);gotoxy(83,cg);printf("|");
								cg+=2;
								gotoxy(84,jogos);printf("%d",cad.pontos.scoreg);gotoxy(93,jogos);printf("|");
								jogos+=2;
								gotoxy(94,filmes);printf("%d",cad.pontos.scoref);gotoxy(106,filmes);printf("|");
								filmes+=2;
								gotoxy(110,status);printf("%c",cad.excluido);gotoxy(118,status);printf("|");
								gotoxy(3,l);printf("----|------------|-------|--------------------------|--------|------------------|---------|------------|-----------|");
								l+=2;
								printf("\n");
								}
							}			
						}
						fflush(stdin);
						gotoxy(10,nick+3);printf("Pressione qualquer tecla para continuar");
						getch();
						system("cls");bar();
				}
				if (a==12)
				{
					system("cls");
					abrir_arquivo("rb");
					do
					{	
						textcolor(0);		
						if(fread(&cad, sizeof(cad), 1, fp) == 1)
						{
							gotoxy(25,7);printf("CODIGO:");printf("%d",cad.cod);fflush(stdin);
							gotoxy(25,9);printf("NOME:");printf("%s",cad.nome);
							gotoxy(25,11);printf("EMAIL:");printf("%s",cad.email);
							gotoxy(25,13);printf("IDADE:");printf("%d",cad.idade);fflush(stdin);
							gotoxy(25,15);printf("NICK:");printf("%s",cad.nick);
							gotoxy(25,18);printf("Pressione uma tecla para continuar ou ESC para sair...");
							fflush(stdin);
							getch();
							system("cls");	
						}
						else
						break;
					}while(!feof(fp) || c!=27);
					system("cls");
					bar();
				}
				if (a==18)
				{
					system("cls");
					alterar();
				}
				if (a==20)
				{
					system("cls");
					deleta();
				}
				if (a==14)
				{
					gotoxy(60,a);scanf("%d",&pesquisa);				
					system("cls");
					gotoxy(20,10);printf("Procurando...");
					Sleep(1000);
					system("cls");
					abrir_arquivo("rb");
					while(!feof(fp))
					{
						textcolor(0);
						if(fread(&cad ,sizeof(cad), 1, fp)==1 && cad.excluido=='n')
						{
							gotoxy(56,4);printf("CADASTROS");
							if(cad.cod==pesquisa)
							{
								gotoxy(3,7);printf("COD");gotoxy(7,7);printf("|");
								gotoxy(12,7);printf("NOME");gotoxy(20,7);printf("|");
								gotoxy(22, 7);printf("IDADE");gotoxy(28,7);printf("|");
								gotoxy(39, 7);printf("E-MAIL");gotoxy(55,7);printf("|");
								gotoxy(58,7);printf("NICK");gotoxy(64,7);printf("|");
								gotoxy(65,7);printf("   CONHECIMENTOS  |  JOGOS  |   FILMES   |");
								gotoxy(109,7);printf("STATUS   |");
								gotoxy(3,8);printf("----|------------|-------|--------------------------|--------|------------------|---------|------------|-----------|");
								gotoxy(3,codigo);printf("%d",cad.cod);gotoxy(7,codigo);printf("|");
								codigo+=2;
								gotoxy(8,nome);puts(cad.nome);gotoxy(20,nome);printf("|");
								nome+=2;
								gotoxy(21,idade);printf("%d",cad.idade);gotoxy(28,idade);printf("|");
								idade+=2;
								gotoxy(29,email);puts(cad.email);gotoxy(55,email);printf("|");
								email+=2;
								gotoxy(56,nick);puts(cad.nick);gotoxy(64,nick);printf("|");
								nick+=2;
								gotoxy(65,cg);printf("%d",&cad.pontos.scorec);gotoxy(83,cg);printf("|");
								cg+=2;
								gotoxy(84,jogos);printf("%d",cad.pontos.scoreg);gotoxy(93,jogos);printf("|");
								jogos+=2;
								gotoxy(94,filmes);printf("%d",cad.pontos.scoref);gotoxy(106,filmes);printf("|");
								filmes+=2;
								gotoxy(110,status);printf("%c",cad.excluido);gotoxy(118,status);printf("|");
								gotoxy(3,l);printf("----|------------|-------|--------------------------|--------|------------------|---------|------------|-----------|");
								l+=2;
								printf("\n");
								}
							}			
						}
						fflush(stdin);
						gotoxy(10,nick+3);printf("Pressione qualquer tecla para continuar");
						getch();
						system("cls");bar();
				}
			}
		}while(c!=27);
		system("cls");
		bar();		
	}
}
void mostra_tabela()
{
	gotoxy(56,4);printf("CADASTROS");
	gotoxy(3,7);printf("COD");gotoxy(7,7);printf("|");
	gotoxy(12,7);printf("NOME");gotoxy(20,7);printf("|");
	gotoxy(22, 7);printf("IDADE");gotoxy(28,7);printf("|");
	gotoxy(39, 7);printf("E-MAIL");gotoxy(55,7);printf("|");
	gotoxy(58,7);printf("NICK");gotoxy(64,7);printf("|");
	gotoxy(65,7);printf("   CONHECIMENTOS  |  JOGOS  |   FILMES   |");
	gotoxy(109,7);printf("STATUS   |");
	for(int i=8;i<=22;i+=2)
	{
		gotoxy(3,i);printf("----|------------|-------|--------------------------|--------|------------------|---------|------------|-----------|");
		for(int j=9;j<=21;j+=2)
		{
			gotoxy(3,j);printf("    |            |       |                          |        |                  |         |            |           |");	
		}
	}
}
void tabela(){
	int lin=9,x;
	abrir_arquivo("rb");
	system("cls");
	rewind(fp);
	mostra_tabela();
	long posicao;
	while(!feof(fp))
	
	{
		if(fread(&cad,sizeof(stcad),1,fp)==1)
		{
			posicao=ftell(fp);
			if(lin<23)
			{
				
				gotoxy(3,lin);printf("%d",cad.cod);gotoxy(8,lin);printf("|");
				gotoxy(8,lin);puts(cad.nome);gotoxy(20,lin);printf("|");
				gotoxy(21,lin);printf("%d",cad.idade);gotoxy(28,lin);printf("|");
				gotoxy(29,lin);puts(cad.email);gotoxy(55,lin);printf("|");
				gotoxy(56,lin);puts(cad.nick);gotoxy(64,lin);printf("|");
				gotoxy(65,lin);printf("%d",cad.pontos.scorec);gotoxy(83,lin);printf("|");
				gotoxy(84,lin);printf("%d",cad.pontos.scoreg);gotoxy(93,lin);printf("|");
				gotoxy(94,lin);printf("%d",cad.pontos.scoref);gotoxy(106,lin);printf("|");
				gotoxy(110,lin);printf("%c",cad.excluido);gotoxy(118,lin);printf("|");
				lin+=2;
			}
			else
			{
				gotoxy(115,25);printf(">>>");
				x=getch();
				switch(x)
				{
					case 77:
						lin=9;
						system("cls");
						mostra_tabela();
						fseek(fp,posicao-(sizeof(stcad)),SEEK_SET);
						gotoxy(3,lin);printf("%d",cad.cod);
						gotoxy(8,lin);puts(cad.nome);
						gotoxy(21,lin);printf("%d",cad.idade);
						gotoxy(29,lin);puts(cad.email);
						gotoxy(56,lin);puts(cad.nick);
						gotoxy(65,lin);printf("%d",&cad.pontos.scorec);
						gotoxy(84,lin);printf("%d",cad.pontos.scoreg);
						gotoxy(94,lin);printf("%d",cad.pontos.scoref);
						gotoxy(110,lin);gotoxy(118,lin);
						lin+=2;
						break;
				}
			}
		}
		if(feof(fp))
		{
			getch();system("cls");
		}
	}bar();
}
void bar()
{
	gotoxy(1,1);textcolor(1);textbackground(3);printf("%c%c%c%c%c",220,220,220,220,220);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,2);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         ",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,3);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,4);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,5);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,5);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,6);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,7);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,8);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,9);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,9);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,10);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,11);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,12);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,13);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,13);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,14);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,15);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,16);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,17);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,17);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,18);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,19);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,20);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,21);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,21);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,22);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,23);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,24);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,25);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,25);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,26);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	gotoxy(1,27);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,28);printf("     %c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c     ",219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(1,29);printf("%c%c%c%c%c",220,220,220,220,220);gotoxy(6,29);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219,220,220,220,220,220,220,220,220,220,219);
	gotoxy(1,30);printf("%c        %c         %c         %c         %c         %c         %c         %c         %c         %c         %c         %c          ",219,219,219,219,219,219,219,219,219,219,219,219,219);gotoxy(120,2);printf("%c",219);
	//contorno
	textcolor(0);
	for(int i=33;i<=86;i++){
		gotoxy(i,1);textbackground(4);printf("%c",223);
	}
	for(int i=33;i<=86;i++){
		gotoxy(i,5);printf("%c",220);
	}
	for(int i=1;i<=5;i++){
		gotoxy(33,i);printf("%c",219);
	}
	for(int i=1;i<=5;i++){
		gotoxy(86,i);printf("%c",219);
	}
	for(int i=6;i<=23;i++){
		gotoxy(38,i);printf("%c",219);
	}
	for(int i=6;i<=23;i++){
		gotoxy(81,i);printf("%c",219);
	}
	for(int i=6;i<=23;i++){
		gotoxy(37,i);textcolor(4);printf("%c",219);
	}
	for(int i=6;i<=23;i++){
		gotoxy(82,i);printf("%c",219);
	}
	for(int i=6;i<=23;i++){
		gotoxy(36,i);textcolor(0);printf("%c",219);
	}
	for(int i=6;i<=23;i++){
		gotoxy(83,i);printf("%c",219);
	}
	textcolor(4);gotoxy(34,2);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(34,3);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(34,4);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	textcolor(0);
	for(int i=35;i<=84;i++){
		gotoxy(i,24);printf("%c",219);
	}
	for(int i=24;i<=30;i++){
		gotoxy(35,i);printf("%c",219);
	}
	for(int i=24;i<=30;i++){
		gotoxy(84,i);printf("%c",219);
	}
	for(int i=35;i<=84;i++){
		gotoxy(i,30);printf("%c",219);
	}
	textcolor(8);
	gotoxy(36,25);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(36,26);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(36,27);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);	
	gotoxy(36,28);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	gotoxy(36,29);printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	//caixa
	for(int c=37;c<=82;c++){
		textbackground(7);gotoxy(c,6);printf(" ");
		for(int l=6;l<=23;l++){
			gotoxy(c,l);printf(" ");
		}
	}
	//botoes
	gotoxy(42,26);textcolor(1);printf("%c%c",219,219);
	gotoxy(46,26);textcolor(2);printf("%c%c",219,219);
	gotoxy(50,26);textcolor(4);printf("%c%c",219,219);
	gotoxy(54,26);textcolor(6);printf("%c%c",219,219);
	gotoxy(42,28);textcolor(1);printf("%c%c",219,219);
	gotoxy(46,28);textcolor(2);printf("%c%c",219,219);
	gotoxy(50,28);textcolor(4);printf("%c%c",219,219);
	gotoxy(54,28);textcolor(6);printf("%c%c",219,219);
	//alavanca
	gotoxy(71,26);textcolor(4);printf("%c%c%c",219,219,219);
	gotoxy(71,25);textcolor(0);textbackground(8);printf("%c%c%c",220,220,220);
	gotoxy(71,27);printf("%c%c%c",223,219,223);
	gotoxy(72,28);printf("%c",219);
	gotoxy(71,29);printf("%c%c%c",223,223,223);
	gotoxy(70,26);printf("%c",219);
	gotoxy(74,26);printf("%c",219);
	textbackground(7);
}
void deleta(){
	abrir_arquivo("rb+");
	int aux_codigo,F;
	long fposicao;
	char conf;
	bar();
	do{
		gotoxy(43,9);printf("______________EXCLUIR______________");		
		gotoxy(43,10);printf("C¢DIGO A SER DELETADO:");
		gotoxy(43,12);printf("NOME:");
		gotoxy(43,14);printf("E-MAIL:");
		gotoxy(43,16);printf("IDADE:");
		gotoxy(43,18);printf("NICK:");
		gotoxy(43,21);printf("__________________________________");
		gotoxy(65,10);scanf("%d", &aux_codigo );		
		
		if(aux_codigo!=0){
			F = 0;
			rewind(fp);
		    do{
		    	fread( &cad,sizeof(cad),1,fp);
		    	if ( cad.cod == aux_codigo && cad.excluido == 'n' )
				{
		    		F = 1;
		    		fposicao = ftell(fp);
		    		gotoxy(48,12);puts(cad.nome);
					gotoxy(50,14);printf("%s",cad.email);
					gotoxy(49,16);printf("%d",cad.idade);
					gotoxy(48,18);printf("%s",cad.nick);
					gotoxy(43,20);printf("Confirma exclusao ? (S/N):");
					fflush(stdin);
					do
					{
						 gotoxy(69,20); conf = getchar();
					}while( conf != 's' && conf != 'S' && conf != 'n' && conf != 'N'  );
				   
					if( conf == 's' || conf == 'S' )
					{
					   fseek (fp,fposicao-(sizeof(cad)),SEEK_SET);
					   cad.excluido='s';
					   F=1;
					   
					   if(fwrite (&cad,sizeof(cad),1,fp)==1)
					   {
					   		fflush (fp);
					   }
				   	}
				   	system("cls");
					bar();
				 	break;
				}
			}while(!feof(fp));
		}
		if (F==0 && aux_codigo!=0){
			gotoxy(65,10);printf("Nao encontrado");Sleep(500);gotoxy(65,10);printf("               ");
		}
	}while(aux_codigo!=0);
	system("cls");
	bar();
}
void sobre()
{
	int b=50,a=8, c;
	
	bar();
	textcolor(4);
	gotoxy(b,a);printf("EMPRESA:");
	a+=1;
	textcolor(0);
	gotoxy(b,a);printf("GABS's BAR");
	a+=2;
	textcolor(4);
	gotoxy(b,a);printf("INTEGRANTES:");
	a+=1;
	textcolor(0);
	gotoxy(b,a);printf("GABRIEL DE JESUS");
	a+=2;
	gotoxy(b,a);printf("GABRIEL TONHOLE");
	a+=2;
	gotoxy(b,a);printf("CAMILA DIAS");
	a+=2;
	textcolor(4);
	gotoxy(b,a);printf("ORIENTADORA:");
	a++;
	textcolor(0);
	gotoxy(b,a);printf("ARIANE SCARELLI");
	a+=4;
	gotoxy(73,a);printf("<DIREITA>");
	
	do
	{
		c=getch();
		switch(c)
		{
			case 77:
				system("cls");
				bar();
				gotoxy(40,7);printf("Gab's Bar foi um programa desenvolvido");
				gotoxy(40,9);printf("com o intuito de dar uma interacao com");
				gotoxy(40,11);printf("o usuario muito maior, possibilitando");
				gotoxy(40,13);printf("a escolha do que fazer primeiro, seja");
				gotoxy(40,15);printf("cadastrar o nome ou ate mesmo o nick.");
				gotoxy(40,17);printf("O software apresenta um quiz com tres");
				gotoxy(40,19);printf("temas: Jogos, Filmes e Conhecimentos");
				gotoxy(40,21);printf("Gerais. Apos termino do jogo, sera ");
				gotoxy(75,23);printf("<BAIXO>");
				gotoxy(38,23);printf("<ESQUERDA>");
				break;
			case 80:
				system("cls");
				bar();
				gotoxy(40,7);printf("integrado junto a seus dados os pontos");
				gotoxy(40,9);printf("feitos por voce.");
				gotoxy(40,11);printf("Nos te agradecemos por utilizar <3 !! ");
				gotoxy(76,23);printf("<CIMA>");
				break;
			case 72:
				system("cls");
				bar();
				gotoxy(40,7);printf("Gab's Bar foi um programa desenvolvido");
				gotoxy(40,9);printf("com o intuito de dar uma interacao com");
				gotoxy(40,11);printf("o usuario muito maior, possibilitando");
				gotoxy(40,13);printf("a escolha do que fazer primeiro, seja");
				gotoxy(40,15);printf("cadastrar o nome ou ate mesmo o nick.");
				gotoxy(40,17);printf("O software apresenta um quiz com tres");
				gotoxy(40,19);printf("temas: Jogos, Filmes e Conhecimentos");
				gotoxy(40,21);printf("Gerais. Apos termino do jogo, sera ");
				gotoxy(75,23);printf("<BAIXO>");
				gotoxy(38,23);printf("<ESQUERDA>");
				break;
			case 75:
				system("cls");
				bar();
				textcolor(4);
				gotoxy(50,8);printf("EMPRESA:");
				textcolor(0);
				gotoxy(50,9);printf("GABS's BAR");
				textcolor(4);
				gotoxy(50,11);printf("INTEGRANTES:");
				textcolor(0);
				gotoxy(b,12);printf("GABRIEL DE JESUS");
				gotoxy(b,14);printf("GABRIEL TONHOLE");
				gotoxy(b,16);printf("CAMILA DIAS");
				textcolor(4);
				gotoxy(b,18);printf("ORIENTADORA:");
				textcolor(0);
				gotoxy(b,19);printf("ARIANE SCARELLI");
				gotoxy(73,23);printf("<DIREITA>");
				break;
			case 27:
				system("cls");
				bar();
				break;
		}
	}while(c!=27);	
}
void masc(){

	int a=10, c, contan,contae,contani;
	abrir_arquivo("ab+");	
	int codi, dade;
	bar();fflush(fp);
	textcolor(0);	
	gotoxy(49,6);printf("<ENTER> PARA COLETAR");
	gotoxy(50,7);printf("<ESC> PARA VOLTAR!");
	gotoxy(43,9);printf("____________CADASTRO!____________");
	gotoxy(43,10);printf("CODIGO:");
	gotoxy(43,12);printf("NOME:");
	gotoxy(43,14);printf("EMAIL:");
	gotoxy(43,16);printf("IDADE:");
	gotoxy(43,18);printf("NICK:");
	gotoxy(43,20);printf("SAVE");
	gotoxy(43,21);printf("_________________________________");
	gotoxy(41,a);printf("->");
	do
	{
		c=getch();
		switch(c)
		{
			case 72 : 
				gotoxy(41,a);printf("  ");
				a-=2;
				if(a<10)
				{
					a=20;	
				}
				
				gotoxy(41,a);printf("->");
				break;
			case 80 : 
				gotoxy(41,a);printf("  ");
				a+=2;
				if(a>20)
				{
					a=10;
				}
					
				gotoxy(41,a);printf("->");
				break;
		}
				if(c==13)
		{
			if(a==12)
			{
				
				gotoxy(48,a);
				gets(cad.nome);
				fflush(stdin);
				contan=strlen(cad.nome);
				if(contan==0)
				{
					textcolor(4);gotoxy(43,a);printf("NOME:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("NOME:");
				}
				else
				{
					textcolor(3);gotoxy(43,a);printf("NOME:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("NOME:");
				}
			}
			if(a==14)
			{
				gotoxy(49,a);printf("                           ");
				gotoxy(49,a);gets(cad.email);
				contae=strlen(cad.email);
				if(contae==0)
				{
					textcolor(4);gotoxy(43,a);printf("EMAIL:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("EMAIL:");
				}
				else
				{	
					textcolor(3);gotoxy(43,a);printf("EMAIL:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("EMAIL:");
				}
				
			}
			if(a==10)
			{	
				gotoxy(50,a);printf("                     ");
				cad.cod =chave(codi);fflush(stdin);
			}				
			if(a==16)
			{
				gotoxy(49,a);printf("                           ");
				gotoxy(49,a);scanf("%d",&dade);fflush(stdin);
				cad.idade=dade;
				if(cad.idade <= 0)
				{
					textcolor(4);gotoxy(43,a);printf("IDADE:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("IDADE:");
				}
				else
				{
					textcolor(3);gotoxy(43,a);printf("IDADE:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("IDADE:");
				}				
			}
			if(a==18)
			{
				gotoxy(48,a);printf("                           ");
				gotoxy(48,a);gets(cad.nick);
				contani=strlen(cad.nome);
				if(contani==0)
				{
					textcolor(3);gotoxy(43,a);printf("NICK:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("NICK:");
				}
				else
				{
					textcolor(3);gotoxy(43,a);printf("NICK:");Sleep(1000);textcolor(0);gotoxy(43,a);printf("NICK:");
				}
			}	
			if(a==20)
			{
				
				if(contan == 0 && contae == 0 && contani == 0 && codi <=0 && codi==cad.cod && dade <=0)
				{	
					gotoxy(48,17);printf("Termine de preencher!");Sleep(1000);gotoxy(48,17);printf("                       ");
				}
				else
					system("cls");
					cad.excluido='n';
					salvar_dados();
			}	
			
		}	
	}while(c!=27);
		if(c==27){
			menu();
		}cursor(1);
}
