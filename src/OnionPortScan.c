/*
OnionPortScanner - v1.1.0, Copyright (C) 2014-2015 Ned Hecatonchires <xned@safe-mail.net>

Este programa é um software livre; você pode redistribuí-lo e/ou modificá-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software Livre (FSF); 
na versão 3 da Licença, ou (na sua opinião) qualquer versão.

Este programa é distribuído na esperança de que possa ser útil, mas SEM NENHUMA GARANTIA; 
sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO EM PARTICULAR. 
Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU junto com este programa, 
se não, escreva para a Fundação do Software Livre(FSF) Inc., 
51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

   ____        _             _____           _    _____                                 
  / __ \      (_)           |  __ \         | |  / ____|                                
 | |  | |_ __  _  ___  _ __ | |__) |__  _ __| |_| (___   ___ __ _ _ __  _ __   ___ _ __ 
 | |  | | '_ \| |/ _ \| '_ \|  ___/ _ \| '__| __|\___ \ / __/ _` | '_ \| '_ \ / _ \ '__|
 | |__| | | | | | (_) | | | | |  | (_) | |  | |_ ____) | (_| (_| | | | | | | |  __/ |   
  \____/|_| |_|_|\___/|_| |_|_|   \___/|_|   \__|_____/ \___\__,_|_| |_|_| |_|\___|_|   
                                                                                        
                                                                                       

UMA VERSÃO COMPLETA DA LICENSA GPL É DISTRIBUIDA JUNTO COM ESSE PROGRAMA EM UM ARQUIVO
NOMEADO "LICENSE.txt" E TAMBÉM PODE SER ACESSADA ATRAVÉS DO SEGUINTE ENDEREÇO:
<http://gnu.org/licenses/gpl.html>

Este programa foi escrito por NeD Hecatonchires <xned@safe-mail.net> com o intuito de 
realizar um simles escaneamento de portas em servidores da rede Onion.

O OnionPortScanner necessita da instalação do "torsocks" para funcionar, e é necessário
que o Tor esteja em execução.

Agradecimentos:
	Toda comunidade do fórum "Conexão Cyberia - Café & Club"
		<http://conexa0cyberia.wordpress.com>
		<http://fhynv2xw7wbtfj3u.onion>

Atenciosamente,

NeD
*/

#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>
#include <termios.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#ifndef h_addr
#define h_addr h_addr_list[0]
#endif
	
#define MAX_BUFFER_SIZE 1024

void scanHost (void);
void showCopying (void);
void showWarranty (void);
char getch (int j);


int main (int argc, char* argv[]){
	if (argv[1] == NULL || (!strstr(argv[1], "__withTorSocks"))){
		char* programCall = (char*) malloc (MAX_BUFFER_SIZE);
		if (!programCall){
			printf ("Erro ao alocar memoria! Encerrando programa...\n");
			exit (1);
		}
		sprintf (programCall, "torsocks %s __withTorSocks 2> /dev/null", argv[0]);
		system (programCall);
		free (programCall);
		exit (0);
	}
	Lmenu:
	system ("clear");
	__fpurge (stdin);
	printf ("OnionPortScanner v1.1.0\nCopyright (C) 2014-2015 Ned Hecatonchires\n\n");
	printf ("Licença GPLv3: GNU GPL versao 3 ou superior <http://gnu.org/licenses/gpl.html>\n"
			"Este é um software livre e você está convidado a redistribui-lo sob certas\n"
			"condições; O OnionPortScanner não possui QUALQUER GARANTIA; para obter mais\n"
			"detalhes escolha as opcoes 2 ou 3 no menu abaixo.\n");
					
	printf ("   ____        _ \n"
			"  / __ \\      (_)\n"                                         
			" | |  | |_ __  _  ___  _ __\n"                                  
			" | |  | | '_ \\| |/ _ \\| '_ \\ \n"                                 
			" | |__| | | | | | (_) | | | |\n"
			"  \\____/|_| |_|_|\\___/|_|_|_|\n"                                
			"  |  __ \\         | |  / ____|\n"                                
			"  | |__) ___  _ __| |_| (___   ___ __ _ _ __  _ __   ___ _ __\n"
			"  |  ___/ _ \\| '__| __|\\___ \\ / __/ _` | '_ \\| '_ \\ / _ | '__|\n"
			"  | |  | (_) | |  | |_ ____) | (_| (_| | | | | | | |  __| |\n"   
			"  |_|   \\___/|_|   \\__|_____/ \\___\\__,_|_| |_|_| |_|\\___|_|\n\n");   
                                                             
                                                             
	printf ("1 - Iniciar Escaneamento\n"
			"2 - Mostrar licenca\n"
			"3 - Mostrar garantias\n"
			"4 - Sair\n");
	Lchoice:
	__fpurge (stdin);
	char choice = getch (0);
	switch (choice){
			case '1': scanHost ();
					  break;
			case '2': showCopying ();
					  printf ("------PRESSIONE UMA TECLA PARA VOLTAR AO MENU------\n");
					  getch (0);
					  goto Lmenu;
					  break;
			case '3': showWarranty ();
					  printf ("------PRESSIONE UMA TECLA PARA VOLTAR AO MENU------\n");
					  getch (0);
					  goto Lmenu;
					  break;
			case '4': exit (0);
			default : goto Lchoice;
					  break;
	}
	
	return (0);
}

void scanHost (void){
	int sock, firstPort, lastPort;
	struct sockaddr_in addr;
	struct hostent* he;
	char serverAddress[MAX_BUFFER_SIZE];
	printf ("Endereco do servidor para escanear (formato: *.onion)_>  ");
	fgets (serverAddress, MAX_BUFFER_SIZE, stdin);
	serverAddress[strlen(serverAddress)-1] = '\0';
	
	portsSelection:
	printf ("Porta para iniciar o escaneamento_> ");
	__fpurge (stdin);
	scanf ("%5d", &firstPort);
	printf ("Porta para terminar o escaneamento_> ");
	__fpurge (stdin);
	scanf ("%5d", &lastPort);
	
	if (firstPort < 0 || firstPort > 65535 || firstPort > lastPort || lastPort < 0 || lastPort > 65535){
		system ("clear");
		printf ("O intervalo de portas é inválido, utilize portas entre 0 e 65535\n");
		goto portsSelection;
	}
	
	printf ("Resolvendo endereco...\n");
	he = gethostbyname (serverAddress);
	if (!he){
		printf ("Erro ao resolver endereco! Encerrando o programa...\n");
		exit (1);
	}
	memcpy(&addr.sin_addr, he->h_addr, he->h_length);
	addr.sin_family = AF_INET;
	memset (&addr.sin_zero, 0, sizeof (addr.sin_zero));	
	
	system ("clear");
	int k = 0, n = 0;
	printf ("Host: %s\n", serverAddress);
	printf ("Conectando...\n");
	for (int i = firstPort, j = 0; i <= lastPort; i++, j++){
		addr.sin_port = htons (i);
		sock = socket (AF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			printf ("Falha ao criar socket\n");
			exit (0);
		}
		int err = connect (sock, (struct sockaddr*) &addr, sizeof(addr));
		if (err < 0){		
			fflush (stdin);
			printf ("\rEscaneando porta: %-7d", i);
			setvbuf (stdout, NULL, _IONBF, 0); 
		} else {
			printf ("\rPORTA %-7d aberta\n", i);
			k++;
		}
		close (sock);
		n++;
	}
	printf ("\nO escaneamento terminou:\n\t%-3d porta(s) escaneada(s)\n\t%-3d porta(s) aberta(s)\n", n, k);
	return;
}

char getch (int j){
	struct termios oldattr, newattr;
	char ch;
	tcgetattr (STDIN_FILENO, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr (STDIN_FILENO, TCSANOW, &newattr);
	ch = getchar ();
	if (j){
		fputc (ch, stdout);
	}
	tcsetattr (STDIN_FILENO, TCSANOW, &oldattr);
	return (ch);
}

void showWarranty (){
	system ("more data/warranty | more 2>&1");
	printf ("\n\n");
	return;
}

void showCopying (){
	system ("cat data/copying | more 2>&1");
	printf ("\n\n");
	return;
}
