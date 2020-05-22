#include <stdio.h>

#include "public.h"

#ifdef DEBUG
#define DPRINTF( fmt, args... )		printf( "<client_reg_fsm_io> " fmt, ##args )  
#else
#define DPRINTF( fmt, args... )		
#endif

extern int client_select_fd[];

void reg_fsm_display_inputname( void )
{
	printf( "Your name: " );
	fflush( stdout );
	return;
}

void reg_fsm_display_inputpassword( void )
{
	printf( "Your password: " );
	fflush( stdout );
	return;
}

void reg_fsm_display_reinputpassword( void )
{
	printf( "Your password again: " );
	fflush( stdout );
	return;
}

void reg_fsm_display_notnew( void )
{
	printf( "new is reserved by system! \n" );
	printf( "Please input yourname again:  " );
	fflush( stdout );

	return;
}

void reg_fsm_display_notguest( void )
{
	printf( "guest is reserved by system! \n" );
	printf( "Please input yourname again:  " );
	fflush( stdout );

	return;
}

extern char username[];

void reg_fsm_ask_server_inputname( void )
{
	char buf[32];
	int conn_fd = client_select_fd[1];

	DPRINTF( "send REG_NAME packet to server ... \n" );
	buf[0] = P0_REG_NAME;
	strcpy( &buf[1], username );

	write( conn_fd, buf, 7 );
	return;
}

